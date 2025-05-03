# 导入环境变量
include env.mk


export ROOT_PATH=$(shell pwd)

SUBDIRS = kernel user tools build-scripts



# todo: 增加参数，判断是否在QEMU中仿真，若是，则启用该环境变量
# export EMULATOR=__QEMU_EMULATION__

# 计算cpu核心数
NPROCS:=1
OS:=$(shell uname -s)

ifeq ($(OS),Linux)
  NPROCS:=$(shell grep -c ^processor /proc/cpuinfo)
endif
ifeq ($(OS),Darwin) # Assume Mac OS X
  NPROCS:=$(shell system_profiler | awk '/Number Of CPUs/{print $4}{next;}')
endif



# 检查是否需要进行fmt --check
# 解析命令行参数  
FMT_CHECK?=0

ifeq ($(FMT_CHECK), 1)
	FMT_CHECK=--check
else
	FMT_CHECK=
endif

# Check if ARCH matches the arch field in dadk-manifest.toml
check_arch:
	@bash tools/check_arch.sh

# ===> Following are oscomp specific
.PHONY: all 
all:
	#@make ARCH=x86_64 ci-build
	@make ARCH=riscv64 ci-build

ci-get-testcase:
ifneq ($(REGET), 1)
	@echo "测试用例已经获取，跳过获取步骤。如需重新获取，请设置 REGET=1"
endif
	@cd oscomp && sh ci-testcase.sh

ci-update-submodules:
	@echo "更新子模块"
	@sudo chown -R $(shell whoami) .
	@git submodule update --recursive --init

ci-build: ci-kernel ci-user ci-gendisk

ci-run: ci-build ci-start

ci-kernel: ci-update-submodules
	@echo "Compile $(ARCH) Kernel..."
	@$(MAKE) -C ./kernel all ARCH=$(ARCH) || (echo "Kernel compilation failed" && exit 1)

ci-user:
	@echo "Compile $(ARCH) User..."
	@$(MAKE) -C ./user all ARCH=$(ARCH) FORCE_UNSAFE_CONFIGURE=1 || (echo "User compilation failed" && exit 1)

ci-gendisk:
	@echo "Generate disk image"
ifeq ($(ARCH),x86_64)
	@bash -c "cd tools && bash grub_auto_install.sh"
endif
	@bash -c "cd oscomp && sudo DADK=$(DADK) ARCH=$(ARCH) bash write_disk_image.sh --bios=legacy"

ci-start:
	@echo "Booting $(ARCH)"
	@cd oscomp && bash ci-start-$(ARCH).sh

.PHONY: kernel user write_diskimage write_diskimage-uefi qemu qemu-nographic qemu-uefi qemu-vnc qemu-uefi-vnc
kernel user write_diskimage write_diskimage-uefi qemu qemu-nographic qemu-uefi qemu-vnc qemu-uefi-vnc run-nographic:
	@echo "The target \"$@\" is deprecated in this branch. Please use ci-* target instead."
	@echo "To see the available targets, run \"make help\"."
	@false

# <===

.PHONY: clean
clean:
	@rm -rf bin
	@list='$(SUBDIRS)'; for subdir in $$list; do \
		echo "Clean in dir: $$subdir";\
		cd $$subdir && $(MAKE) clean;\
		cd .. ;\
	done

.PHONY: ECHO
ECHO:
	@echo "$@"


docs: ECHO
	bash -c "cd docs && make html && cd .."

clean-docs:
	bash -c "cd docs && make clean && cd .."

gdb:
ifeq ($(ARCH), x86_64)
	rust-gdb -n -x tools/.gdbinit
else ifeq ($(ARCH), loongarch64)
	loongarch64-unknown-linux-gnu-gdb -n -x tools/.gdbinit
else
	gdb-multiarch -n -x tools/.gdbinit
endif

# 写入磁盘镜像
write_diskimage: check_arch
	@echo "write_diskimage arch=$(ARCH)"
	bash -c "export ARCH=$(ARCH); cd tools && bash grub_auto_install.sh && sudo DADK=$(DADK) ARCH=$(ARCH) bash $(ROOT_PATH)/tools/write_disk_image.sh --bios=legacy && cd .."

# 写入磁盘镜像(uefi)
write_diskimage-uefi: check_arch
	bash -c "export ARCH=$(ARCH); cd tools && bash grub_auto_install.sh && sudo DADK=$(DADK) ARCH=$(ARCH) bash $(ROOT_PATH)/tools/write_disk_image.sh --bios=uefi && cd .."
# 不编译，直接启动QEMU
qemu: check_arch
	sh -c "cd tools && bash run-qemu.sh --bios=legacy --display=window && cd .."

# 不编译，直接启动QEMU,不显示图像
qemu-nographic: check_arch
	sh -c "cd tools && bash run-qemu.sh --bios=legacy --display=nographic && cd .."

# 不编译，直接启动QEMU(UEFI)
qemu-uefi: check_arch
	sh -c "cd tools && bash run-qemu.sh --bios=uefi --display=window && cd .."
# 不编译，直接启动QEMU,使用VNC Display作为图像输出
qemu-vnc: check_arch
	sh -c "cd tools && bash run-qemu.sh --bios=legacy --display=vnc && cd .."
# 不编译，直接启动QEMU(UEFI),使用VNC Display作为图像输出
qemu-uefi-vnc: check_arch
	sh -c "cd tools && bash run-qemu.sh --bios=uefi --display=vnc && cd .."
	
# 编译并写入磁盘镜像
build: check_arch
	$(MAKE) all -j $(NPROCS)
	$(MAKE) write_diskimage || exit 1

# 在docker中编译，并写入磁盘镜像
docker: check_arch
	@echo "使用docker构建"
	sudo bash tools/build_in_docker.sh || exit 1
	$(MAKE) write_diskimage || exit 1
	
# uefi方式启动
run-uefi: check_arch
	$(MAKE) all -j $(NPROCS)
	$(MAKE) write_diskimage-uefi || exit 1
	$(MAKE) qemu-uefi
	
# 编译并启动QEMU
run: check_arch
	$(MAKE) all -j $(NPROCS)
	$(MAKE) write_diskimage || exit 1
	$(MAKE) qemu

# uefi方式启动，使用VNC Display作为图像输出
run-uefi-vnc: check_arch
	$(MAKE) all -j $(NPROCS)
	$(MAKE) write_diskimage-uefi || exit 1
	$(MAKE) qemu-uefi-vnc
	
# 编译并启动QEMU，使用VNC Display作为图像输出
run-vnc: check_arch
	$(MAKE) all -j $(NPROCS)
	$(MAKE) write_diskimage || exit 1
	$(MAKE) qemu-vnc

run-nographic: check_arch
	$(MAKE) all -j $(NPROCS)
	$(MAKE) write_diskimage || exit 1
	$(MAKE) qemu-nographic

# 在docker中编译，并启动QEMU
run-docker: check_arch
	@echo "使用docker构建并运行"
	sudo bash tools/build_in_docker.sh || exit 1
	$(MAKE) write_diskimage || exit 1
	$(MAKE) qemu

fmt: check_arch
	@echo "格式化代码" 
	FMT_CHECK=$(FMT_CHECK) $(MAKE) fmt -C kernel
	FMT_CHECK=$(FMT_CHECK) $(MAKE) fmt -C user
	FMT_CHECK=$(FMT_CHECK) $(MAKE) fmt -C build-scripts

log-monitor:
	@echo "启动日志监控"
	@sh -c "cd tools/debugging/logmonitor && cargo run --release -- --log-dir $(ROOT_PATH)/logs/ --kernel $(ROOT_PATH)/bin/kernel/kernel.elf" 

.PHONY: update-submodules
update-submodules:
	@echo "更新子模块"
	@git submodule update --recursive --init

.PHONY: update-submodules-by-mirror
update-submodules-by-mirror:
	@echo "从镜像更新子模块"
	@git config --global url."https://git.mirrors.dragonos.org.cn/DragonOS-Community/".insteadOf https://github.com/DragonOS-Community/
	@$(MAKE) update-submodules
	@git config --global --unset url."https://git.mirrors.dragonos.org.cn/DragonOS-Community/".insteadOf

help:
	@echo "用法："
	@echo "  make <target> ARCH=<arch>"
	@echo ""
	@echo "Example:"
	@echo "  make ci-run ARCH=riscv64"
	@echo ""
	@echo "When <arch> is not specified, the default value in env.mk will be used."
	@echo ""
	@echo "Targets:"
	@echo "  make ci-run            - 本地编译，写入磁盘镜像，并在QEMU中运行"
	@echo "  make ci-kernel         - 编译内核"
	@echo "  make ci-gendisk        - 写入磁盘镜像"
	@echo "  make ci-build          - 编译并写入磁盘镜像"
	@echo "  make ci-start          - 不编译，直接启动运行"
	@echo ""
	@echo "其他:"
	@echo "  make all               - 用于 CI 编译"
	@echo "  make clean             - 清理编译产生的文件"
	@echo "  make fmt               - 格式化代码"
	@echo "  make log-monitor       - 启动日志监控"
	@echo "  make docs              - 生成文档"
	@echo "  make clean-docs        - 清理文档"
	@echo ""
	@echo "  make update-submodules - 更新子模块"
	@echo "  make update-submodules-by-mirror - 从镜像更新子模块"


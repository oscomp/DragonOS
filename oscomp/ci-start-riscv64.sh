qemu-system-riscv64 -machine virt -kernel ../tools/arch/riscv64/u-boot-v2023.10-riscv64/u-boot.bin \
                    -m 512M -nographic -smp 2,cores=2,threads=1,sockets=1 -bios default \
                    -no-reboot -device virtio-net-device,netdev=net -netdev user,id=net \
                    -rtc base=utc \
                    -drive file=../bin/riscv64/disk.img,if=none,format=raw,id=x1 \
                    -device virtio-blk-device,drive=x1,bus=virtio-mmio-bus.1
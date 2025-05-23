BINARY_PATH="../bin/x86_64"
MEMORY="512M"
MEMORY_BACKEND="dragonos-qemu-shm.ram"
MEMORY_PREFIX="/dev/shm"
LOG_FILE="../serial_opt.txt"
SHM_OBJECT_PARAM="memory-backend-file,size=${MEMORY},id=${MEMORY_BACKEND},mem-path=${MEMORY_PREFIX}/${MEMORY_BACKEND},share=on "
DISK_IMAGE="${BINARY_PATH}/disk.img"
DRIVE="id=disk,file=${DISK_IMAGE},if=none"

TEST_CASE_IMAGE="${BINARY_PATH}/sdcard-rv.img"
if [ -f ${TEST_CASE_IMAGE} ]; then
    echo "测试用例存在"
    QEMU_SD_PARAM="-drive id=disk1,file=${TEST_CASE_IMAGE},if=none -device virtio-blk-pci,drive=disk1"
else
    echo "测试用例不存在"
    QEMU_SD_PARAM=""
fi

qemu-system-x86_64  --nographic \
                    -kernel ${BINARY_PATH}/kernel/kernel.elf \
                    -d ${DISK_IMAGE} \
                    -m 512M \
                    -smp 2,cores=2,threads=1,sockets=1 \
                    -boot order=d \
                    -d cpu_reset,guest_errors,trace:virtio*,trace:e1000e_rx*,trace:e1000e_tx*,trace:e1000e_irq* \
                    -s -machine q35 \
                    -cpu IvyBridge,apic,x2apic,+fpu,check,+vmx, \
                    -rtc clock=host,base=localtime \
                    -serial chardev:mux \
                    -monitor chardev:mux \
                    -chardev stdio,id=mux,mux=on,signal=off,logfile=${LOG_FILE} \
                    -drive ${DRIVE} -device virtio-blk-pci,drive=disk \
                    ${QEMU_SD_PARAM} \
                    -netdev user,id=hostnet0,hostfwd=tcp::12580-:12580 \
                    -device virtio-net-pci,vectors=5,netdev=hostnet0,id=net0 \
                    -usb -device qemu-xhci,id=xhci,p2=8,p3=4 \
                    -machine accel=kvm \
                    -enable-kvm

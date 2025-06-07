busybox echo "#### OS COMP TEST GROUP START lua ####"

busybox sh test.sh date.lua
busybox sh test.sh file_io.lua
busybox sh test.sh max_min.lua
busybox sh test.sh random.lua
busybox sh test.sh remove.lua
busybox sh test.sh round_num.lua
busybox sh test.sh sin30.lua
busybox sh test.sh sort.lua
busybox sh test.sh strings.lua

busybox echo "#### OS COMP TEST GROUP END lua ####"

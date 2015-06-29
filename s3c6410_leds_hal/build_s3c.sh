make
adb push s3c6410_leds_hal.ko /data/local
adb shell "insmod /data/local/s3c6410_leds_hal.ko"
adb shell "chmod 777 /dev/s3c6410_leds_hal"

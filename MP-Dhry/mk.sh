arm-poky-linux-gnueabi-gcc -march=armv7-a  -mfloat-abi=hard -mfpu=neon -mtune=cortex-a15 -c dhry22.c -o dhry22.o
arm-poky-linux-gnueabi-gcc -march=armv7-a  -mfloat-abi=hard -mfpu=neon -mtune=cortex-a15 -c mpdhry.c -o mpdhry.o
arm-poky-linux-gnueabi-gcc -march=armv7-a  -mfloat-abi=hard -mfpu=neon -mtune=cortex-a15  dhry22.o mpdhry.o -o MP-Dhry -lrt -lc -lm -lpthread 

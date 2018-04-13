#!/bin/bash
wget https://github.com/AOSPA/android_gcc_linux-x86_arm-linux-android-4.9/blob/nougat-caf/bin/arm-linux-androideabi-gcc?raw=true -O gcc
chmod a+x gcc

./gcc get_offsets.c -o get_offsets -m32

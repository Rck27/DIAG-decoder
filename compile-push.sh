#!/bin/bash

export NDK=~/Android/Sdk/ndk/29.0.14206865
export TOOLCHAIN=$NDK/toolchains/llvm/prebuilt/linux-x86_64
export API=29

$TOOLCHAIN/bin/aarch64-linux-android${API}-clang \
  -Iasn1/asn-lte-rrc \
  src/main.c \
  asn1/asn-lte-rrc/*.c \
  -Wno-parentheses \
  -o rrc_decoder_android

adb push rrc_decoder_android /data/local/tmp/rrc_decoder
# adb shell
# chmod +x /data/local/tmp/rrc_decoder
# /data/local/tmp/rrc_decoder
#!/usr/bin/env bash

# Verified on ubuntu 18.04
# mkdir riscv/git, riscv/riscv_newlib, riscv_linux befor running this bash script
export RISCV_DIR=$HOME/Andes/riscv
export ANDES_LLVM_DIR=$HOME/Andes/riscv/llvm-package/source
export LLVM_SRC_DIR=$HOME/Andes/riscv/llvm-project

# More: install cmake from source since the version of cmake in Ubuntu 18.04 is 
# too old.

export GNU_NEWLIB_INSTALL_DIR=$HOME/Andes/riscv/riscv_newlib
export LLVM_NEWLIB_BUILD_DIR=$LLVM_SRC_DIR/build_riscv_newlib

riscv_gnu_toolchain_prerequisites() {
  sudo apt-get install autoconf automake autotools-dev curl python3 libmpc-dev \
  libmpfr-dev libgmp-dev gawk build-essential bison flex texinfo gperf libtool \
  patchutils bc zlib1g-dev libexpat-dev
  if [ ! -f "/usr/bin/python" ]; then
    sudo ln -s /usr/bin/python3 /usr/bin/python
  fi
}

riscv_llvm_prerequisites() {
  sudo apt-get install ninja-build
}

# get Andes llvm from release source
get_llvm_from_package() {
  pushd $RISCV_DIR
  rm -rf llvm-project
  tar -xvf $ANDES_LLVM_DIR/llvm-project.tar.gz
  popd
}

get_llvm_from_patch() {
  pushd $RISCV_DIR
  rm -rf llvm-project
  git clone -b llvmorg-13.0.0 https://github.com/llvm/llvm-project.git
  cd llvm-project
  git am -k $RISCV_DIR/llvm-package/patch/patch/*.patch
  popd
}

get_gnu_toolchain_newlib() {
  pushd $RISCV_DIR
  rm -rf nds64le-elf-newlib-v5d
# nds64le-elf-newlib-v5d.tar.gz is from Andes' pre-build
  tar -xvf nds64le-elf-newlib-v5d.tar.gz
  mv global/tools/Andestech/AndeSight_STD_v500/toolchains/nds64le-elf-newlib-v5d .
  rm -rf global
  popd
}

# DEFAULT_SYSROOT: 
#   https://stackoverflow.com/questions/66357013/compile-clang-with-alternative-sysroot
# LLVM_DEFAULT_TARGET_TRIPLE:  
#   https://clang.llvm.org/docs/CrossCompilation.html#general-cross-compilation-options-in-clang
# Use "clang --sysroot" if did not "cmake -DDEFAULT_SYSROOT"
# $GNU_NEWLIB_INSTALL_DIR/clang --gcc-toolchain=$GNU_NEWLIB_INSTALL_DIR \
#   --sysroot=$GNU_NEWLIB_INSTALL_DIR/sysroot/ --static test.c
build_llvm_toolchain() {
  pushd $LLVM_SRC_DIR
#  rm -rf build_newlib
#  mkdir build_newlib
#  cd build_newlib
#  cmake -G "Ninja" ../llvm \
#  -DCMAKE_INSTALL_PREFIX=$GNU_NEWLIB_INSTALL_DIR \
#  -DLLVM_ENABLE_PROJECTS='clang' \
#  -DCMAKE_BUILD_TYPE=Debug \
#  -DLLVM_OPTIMIZED_TABLEGEN=On \
#  -DLLVM_INSTALL_TOOLCHAIN_ONLY=Off \
#  -DLLVM_TARGETS_TO_BUILD='RISCV' \
#  -DLLVM_PARALLEL_COMPILE_JOBS=4 -DLLVM_PARALLEL_LINK_JOBS=1 \
#  -DLLVM_DEFAULT_TARGET_TRIPLE=riscv64-unknown-elf
#  ninja
#  ninja install
#  popd

  rm -rf build_riscv_newlib
  mkdir build_riscv_newlib
  pushd $LLVM_NEWLIB_BUILD_DIR
  cmake -G "Ninja" -DCMAKE_BUILD_TYPE=Debug -DLLVM_TARGETS_TO_BUILD="RISCV" \
  -DLLVM_ENABLE_PROJECTS="clang"  \
  -DLLVM_OPTIMIZED_TABLEGEN=On -DLLVM_INSTALL_TOOLCHAIN_ONLY=Off \
  -DCMAKE_INSTALL_PREFIX=$GNU_NEWLIB_INSTALL_DIR -DLLVM_PARALLEL_COMPILE_JOBS=4 \
  -DLLVM_PARALLEL_LINK_JOBS=1 -DLLVM_DEFAULT_TARGET_TRIPLE=riscv64-unknown-elf \
  ../llvm
  ninja
  ninja install
  popd
}

#riscv_gnu_toolchain_prerequisites;
#riscv_llvm_prerequisites;
#get_llvm_from_package;
#get_llvm_from_patch;
#get_gnu_toolchain_newlib;
build_llvm_toolchain;

#!/usr/bin/env bash

# Verified on ubuntu 18.04
# mkdir ~/andes/riscv/git, $GNU_NEWLIB_INSTALL_DIR before running this bash script
#export GNU_NEWLIB_INSTALL_DIR=/usr/local/riscv/andes/nds64le-elf-newlib-v5d
export GNU_NEWLIB_INSTALL_DIR=/usr/local/riscv/andes/riscv_newlib

export RISCV_DIR=$HOME/andes/riscv
export ANDES_LLVM_DIR=$RISCV_DIR/llvm-package/source
export LLVM_SRC_DIR=$RISCV_DIR/llvm-project
export GNU_SRC_DIR=$HOME/andes/riscv/git

export LLVM_NEWLIB_BUILD_DIR=$LLVM_SRC_DIR/build_riscv_newlib

# More: install cmake from source since the version of cmake in Ubuntu 18.04 is 
# too old.

riscv_gnu_toolchain_prerequisites() {
  sudo apt-get install autoconf automake autotools-dev curl python3 libmpc-dev \
  libmpfr-dev libgmp-dev gawk build-essential bison flex texinfo gperf libtool \
  patchutils bc zlib1g-dev libexpat-dev
  if [ ! -f "/usr/bin/python" ]; then
    sudo ln -s /usr/bin/python3 /usr/bin/python
  fi
  sudo apt-get install ninja-build
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

get_llvm_from_Phoenix() {
  pushd $RISCV_DIR
  rm -rf Phoenix
  git clone https://gitlab.lightelligence.co/software/Phoenix.git
  rm -rf llvm-project
  ln -s Phoenix/llvm-project llvm-project 
  popd
}

get_prebuild_nds_gnu_toolchain() {
  pushd $RISCV_DIR
  rm -rf nds64le-elf-newlib-v5d
  read -p "token id: " token_id
  curl -k -o ./nds64le-elf-newlib-v5d.tar.gz --request GET --header PRIVATE-TOKEN:$token_id "https://idc-code1.int.lightelligence.co/api/v4/projects/190/packages/generic/Andes/13.0.0/nds64le-elf-newlib-v5d.tar.gz"
# nds64le-elf-newlib-v5d.tar.gz is from Andes' pre-build
  tar -xvf nds64le-elf-newlib-v5d.tar.gz
  mv global/tools/Andestech/AndeSight_STD_v500/toolchains/nds64le-elf-newlib-v5d .
  rm -rf global
  popd
}

build_gnu_toolchain() {
  pushd $GNU_SRC_DIR
  git clone https://github.com/riscv/riscv-gnu-toolchain
  cd riscv-gnu-toolchain
#  Looks branch change from original/rvv-intrinsic to origin/__archive__
#  git checkout -b rvv-intrinsic origin/rvv-intrinsic
# commit 409b951ba6621f2f115aebddfb15ce2dd78ec24f of master branch is work for vadd.vv of vadd1.c
  mkdir build_newlib
  cd build_newlib
# NX27V is 32-64 bits configurable and has HW float point
  ../configure --prefix=$GNU_NEWLIB_INSTALL_DIR \
  --with-arch=rv64gc --with-abi=lp64d
#  --with-multilib-generator="rv32i-ilp32--;rv32imafd-ilp32--;rv64ima-lp64--"
  sudo make -j4
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
  rm -rf $LLVM_NEWLIB_BUILD_DIR
  mkdir $LLVM_NEWLIB_BUILD_DIR
  pushd $LLVM_NEWLIB_BUILD_DIR
  cmake -G "Ninja" -DCMAKE_BUILD_TYPE=Debug -DLLVM_TARGETS_TO_BUILD="RISCV" \
  -DLLVM_ENABLE_PROJECTS="clang"  \
  -DLLVM_OPTIMIZED_TABLEGEN=On -DLLVM_INSTALL_TOOLCHAIN_ONLY=Off \
  -DCMAKE_INSTALL_PREFIX=$GNU_NEWLIB_INSTALL_DIR -DLLVM_PARALLEL_COMPILE_JOBS=4 \
  -DLLVM_PARALLEL_LINK_JOBS=1 -DLLVM_DEFAULT_TARGET_TRIPLE=riscv64-unknown-elf \
  ../llvm
  ninja
  sudo ninja install
  popd
}

#riscv_gnu_toolchain_prerequisites;
#riscv_llvm_prerequisites;
#get_llvm_from_package;
#get_llvm_from_patch;
#get_llvm_from_Phoenix;
#get_prebuild_nds_gnu_toolchain;
build_gnu_toolchain;
build_llvm_toolchain;

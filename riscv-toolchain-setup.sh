#!/usr/bin/env bash

source var-office-riscv-toolchain-setup.sh
#source var-home-riscv-toolchain-setup.sh

check() {
  if [ ! -d "$GNU_SRC_DIR" ]; then
    echo "GNU_SRC_DIR: $GNU_SRC_DIR not exist"
    exit 1
  fi
  if [ -d "$GNU_NEWLIB_INSTALL_DIR" ]; then
    echo "GNU_NEWLIB_INSTALL_DIR: $GNU_NEWLIB_INSTALL_DIR exist. Remove it before running."
    exit 1
  fi
  if [ -d "$GNU_LINUX_INSTALL_DIR" ]; then
    echo "GNU_LINUX_INSTALL_DIR: $GNU_LINUX_INSTALL_DIR exist. Remove it before running."
    exit 1
  fi
  if [ ! -d "$LLVM_NEWLIB_BUILD_DIR" ]; then
    echo "LLVM_NEWLIB_BUILD_DIR: $LLVM_NEWLIB_BUILD_DIR not exist. Create it before running."
    exit 1
  fi
  if [ ! -d "$LLVM_LINUX_BUILD_DIR" ]; then
    echo "LLVM_LINUX_BUILD_DIR: $LLVM_LINUX_BUILD_DIR not exist. Create it before running."
    exit 1
  fi
}

build_gnu_toolchain() {
  pushd $GNU_SRC_DIR
  git clone https://github.com/riscv/riscv-gnu-toolchain
  cd riscv-gnu-toolchain
  git checkout -b rvv-intrinsic origin/rvv-intrinsic
  mkdir build_newlib
  cd build_newlib
  ../configure --prefix=$GNU_NEWLIB_INSTALL_DIR --with-multilib-generator="rv32i-ilp32--;rv32imafd-ilp32--;rv64ima-lp64--"
  make

  cd ..
  mkdir build_linux
  cd build_linux
  ../configure --prefix=$GNU_LINUX_INSTALL_DIR
  make linux
  popd
}

build_llvm_toolchain() {
  pushd $LLVM_NEWLIB_BUILD_DIR
  cmake -G "Ninja" -DCMAKE_BUILD_TYPE=Debug -DLLVM_TARGETS_TO_BUILD="RISCV" -DLLVM_ENABLE_PROJECTS="clang;lld"  -DLLVM_BINUTILS_INCDIR=$GNU_SRC_DIR/riscv-gnu-toolchain/riscv-binutils/include  -DCMAKE_INSTALL_PREFIX=$GNU_NEWLIB_INSTALL_DIR -DLLVM_PARALLEL_COMPILE_JOBS=4  -DLLVM_PARALLEL_LINK_JOBS=1 -DLLVM_DEFAULT_TARGET_TRIPLE=riscv64-unknown-elf -DDEFAULT_SYSROOT=$GNU_NEWLIB_INSTALL_DIR/riscv64-unknown-elf -DLLVM_INSTALL_UTILS=ON ../llvm
  ninja
  ninja install
  popd
  pushd $LLVM_LINUX_BUILD_DIR
  cmake -G "Ninja" -DCMAKE_BUILD_TYPE=Debug -DLLVM_TARGETS_TO_BUILD="RISCV" -DLLVM_ENABLE_PROJECTS="clang;lld"  -DLLVM_BINUTILS_INCDIR=$GNU_SRC_DIR/riscv-gnu-toolchain/riscv-binutils/include  -DCMAKE_INSTALL_PREFIX=$GNU_LINUX_INSTALL_DIR -DLLVM_PARALLEL_COMPILE_JOBS=4  -DLLVM_PARALLEL_LINK_JOBS=1 -DLLVM_DEFAULT_TARGET_TRIPLE=riscv64-unknown-linux-gnu -DDEFAULT_SYSROOT=$GNU_LINUX_INSTALL_DIR/sysroot -DLLVM_INSTALL_UTILS=ON ../llvm
  ninja
  ninja install
  popd
}

check;
build_gnu_toolchain;
build_llvm_toolchain;

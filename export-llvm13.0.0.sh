#!/usr/bin/env bash

rm -rf llvm-project
git clone -b llvmorg-13.0.0 https://github.com/llvm/llvm-project.git
rm -rf llvm-project/.git

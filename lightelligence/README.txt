Test commands:
$ /usr/local/riscv/andes/riscv_newlib/bin/clang++ -menable-experimental-extensions -march=rv64gcv0p10 -O0 -mabi=lp64d nostartfiles ../../crt0.S -lm -o a.adx <input-file> -v
$ bash run.sh

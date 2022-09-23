/*
Compile and run on sc_sim as follows,

terminal A:
~/NX27V_ADP_AE350_Virtua_Platform$ ./sc_sim
terminal B:
$ /usr/local/riscv/andes/riscv_newlib/bin/clang++ -menable-experimental-extensions atoi.c -march=rv64gcv0p10 -O0 -g -mabi=lp64d -o a.adx  -v
$ /usr/local/riscv/andes/riscv_newlib/bin/riscv64-unknown-elf-gdb a.adx
(gdb) target remote :9899
(gdb) load
(gdb) b main
(gdb) c
Breakpoint 1, main () at atoi.c: ...
18    result = atoi("2.1");
(gdb) n
19    return 0;
(gdb) p result
$21 = 2
(gdb) c
Continuing.

pass both link and sc_sim:
pass on both open source riscv-gnu-toolchain with open source clang/llvm 13.0.0 and 13.x

$ ~/riscv/13.0.0/riscv_newlib/bin/clang atoi.c -menable-experimental-extensions -march=rv64gcv0p10 -O0 -g -mabi=lp64d -o a.adx  -v
$ ~/riscv/13.x/riscv_newlib/bin/clang atoi.c -menable-experimental-extensions -march=rv64gcv0p10 -O0 -g -mabi=lp64d -o a.adx  -v

pass link and fail on sc_sim:
$ ~/14.x/riscv/riscv_newlib/bin/clang atoi.c -menable-experimental-extensions -march=rv64gcv1p0 -O0 -g -mabi=lp64d -o a.adx  -v

fail on Andes' pre-build gdb:
$ ~/andes/riscv/nds64le-elf-newlib-v5d/bin/riscv64-elf-gdb a.adx
/u/jonathanchen/andes/riscv/nds64le-elf-newlib-v5d/bin/riscv64-unknown-elf-gdb: error while loading shared libraries: libpython3.4m.so.1.0: cannot open shared object file: No such file or directory
*/

//#include <stdio.h>      /* printf */
#include <stdlib.h>

int main ()
{
  int result;
  result = atoi("2.1");
//  printf ("atoi(2.1): %d.\n", result);
  return 0;
}

/*
~/git/note$ ~/Andes/riscv/nds64le-elf-newlib-v5d/bin/riscv64-elf-g++ atoi.c -march=rv64gv0p10 -O0 -g -mabi=lp64d -mvh -o a.adx -v
~/git/note$ ~/Andes/riscv/nds64le-elf-newlib-v5d/bin/clang atoi.c -menable-experimental-extensions -march=rv64gcv0p10 -O0 -g -mabi=lp64d -o a.adx  -v

terminal A:
~/Andes/nfs/platforms/andes/v_3.2.0/AndeSysC/PA_NX27V_for_Lightelligence/sid_systemc/target/NX27V_ADP_AE350_Virtua_Platform$ ./sc_sim
terminal B:
~/git/note$ ~/Andes/riscv/nds64le-elf-newlib-v5d/bin/riscv64-elf-g++ atoi.c -march=rv64gv0p10 -O0 -g -mabi=lp64d -mvh -o a.adx -v
~/git/note$ ~/Andes/riscv/nds64le-elf-newlib-v5d/bin/clang++ -menable-experimental-extensions atoi.c -march=rv64gcv0p10 -O0 -g -mabi=lp64d -o a.adx  -v
~/git/note$ ~/Andes/nfs/platforms/andes/v_3.2.0/AndeSysC/PA_NX27V_for_Lightelligence/sid_systemc/tool/riscv64-elf-gdb a.adx
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

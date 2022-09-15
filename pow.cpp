/* terminal A:
~/Andes/nfs/platforms/andes/v_3.2.0/AndeSysC/PA_NX27V_for_Lightelligence/sid_systemc/target/NX27V_ADP_AE350_Virtua_Platform$ ./sc_sim
terminal B:
~/git/note$ ~/Andes/riscv/riscv_newlib/bin/riscv64-elf-g++ pow.cpp -march=rv64gv0p10 -O0 -g -mabi=lp64d -mvh -o a.adx -v
~/git/note$ ~/Andes/riscv/riscv_newlib/bin/clang++ -menable-experimental-extensions pow.cpp -march=rv64gcv0p10 -O0 -g -mabi=lp64d -o a.adx  -v
~/git/note$ ~/Andes/nfs/platforms/andes/v_3.2.0/AndeSysC/PA_NX27V_for_Lightelligence/sid_systemc/tool/riscv64-elf-gdb a.adx
(gdb) target remote :9899
(gdb) load
(gdb) b main
(gdb) c
Breakpoint 1, main () at pow.cpp:18
18	  int a = test_global();
(gdb) n
19	  return 0;
(gdb) p a
$1 = 100
(gdb) c
Continuing.
*/

#include <math.h>

int gStart = 3;
int gI = 100;
int test_global()
{
  int res = 0;

  res = pow(gI, 2);

  return res;
}

int main() {
  int a = test_global();
  return 0;
}

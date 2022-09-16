/*
~/git/note$ ~/Andes/riscv/riscv_newlib/bin/riscv64-elf-g++ abs.cpp -march=rv64gv0p10 -O0 -g -mabi=lp64d -mvh -o a.adx -v
~/git/note$ ~/Andes/riscv/riscv_newlib/bin/clang++ abs.cpp -menable-experimental-extensions -march=rv64gcv0p10 -O0 -g -mabi=lp64d -o a.adx  -v
*/

//#include <stdio.h>
#include <math.h>

double ff = 100.6;
double test_math()
{
  int res = 0;

  res = (ff);

  return res;
}

int main() {
  double a = test_math();
//  printf("a: %lf\n", a);
  return 0;
}

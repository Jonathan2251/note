// NOTE: clang -menable-experimental-extensions -march=rv64gcv0p10 -O0 -mabi=lp64d -S test_fail_ace.c -o -

long long int foo() {
// CHECK: call i64 @llvm.riscv.bmc.tensor.matmul
  long long int token = __builtin_riscv_tensor_fail(0/*src0*/, 1/*src1*/);
  return 0;
}

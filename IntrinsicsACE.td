let TargetPrefix = "riscv" in {
def int_riscv_tensor_fail : GCCBuiltin<"__builtin_riscv_tensor_fail">, Intrinsic<
    [/* d */ llvm_i64_ty],
    [/* s0 */ llvm_i64_ty, /* s1 */ llvm_i64_ty],
    [ImmArg<ArgIndex<0>>, ImmArg<ArgIndex<1>>, IntrNoMem, IntrHasSideEffects]
>;
def int_riscv_fg_st : Intrinsic<
    [/* fg_status */ llvm_i64_ty],
    [],
    [IntrNoMem, IntrHasSideEffects]
>;
}

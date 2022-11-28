; ~/andes/riscv/git/Phoenix/llvm-project/build_riscv_newlib/bin/llc -mtriple=riscv64 -mattr=+experimental-v test-vsaddu-rv64.ll -O3 -o -

declare <vscale x 1 x i8> @llvm.riscv.vsaddu.nxv1i8.nxv1i8(
  <vscale x 1 x i8>,
  <vscale x 1 x i8>,
  i64);

define <vscale x 1 x i8> @intrinsic_vsaddu_vv_nxv1i8_nxv1i8_nxv1i8(<vscale x 1 x i8> %0, <vscale x 1 x i8> %1, i64 %2) nounwind {
entry:
  %a = call <vscale x 1 x i8> @llvm.riscv.vsaddu.nxv1i8.nxv1i8(
    <vscale x 1 x i8> %0,
    <vscale x 1 x i8> %1,
    i64 %2)

;  ret <vscale x 1 x i8> %a
  ret <vscale x 1 x i8> %0
}


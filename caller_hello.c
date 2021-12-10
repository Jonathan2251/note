/* jonathanchen@hz-compiler1:/local/git$ /local/riscv_newlib/bin/riscv64-unknown-elf-gcc -c func_hello_start.s 
jonathanchen@hz-compiler1:/local/git$ /local/riscv_newlib/bin/riscv64-unknown-elf-gcc -c caller_hello.c 
jonathanchen@hz-compiler1:/local/git$ /local/riscv_newlib/bin/riscv64-unknown-elf-ld caller_hello.o func_hello_start.o
jonathanchen@hz-compiler1:/local/git$ /local/riscv_newlib/bin/riscv64-unknown-elf-ld caller_hello.o func_hello_start.o -o a.out
jonathanchen@hz-compiler1:/local/git$ /local/git/qemu/build/qemu-riscv64 a.out
Hello World
*/

extern void hello();

int main() {
  hello();
}

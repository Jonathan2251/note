#pragma once
#include <stdint.h>

#if defined(__clang__)
#include "riscv_vector.h"
#endif

/*

List of functions
========================================

Basic fuctions
----------------------------------------
*   void enable_ace();

High level ACE intrinsic functions
----------------------------------------

ACE intrinsic functions
----------------------------------------
*   void ace_bmc_write(const unsigned int adr, unsigned long long dat);
*   unsigned long long ace_bmc_read(const unsigned int adr);
*   void ace_obmc_write(const unsigned int adr, unsigned long long dat);
*   unsigned long long ace_obmc_read(const unsigned int adr);
*   void ace_bmc_write_table(const unsigned int adr, unsigned long long dat);
*   unsigned long long ace_bmc_read_table(const unsigned int adr);
*   void ace_obmc_write_table(const unsigned int adr, unsigned long long dat);
*   unsigned long long ace_obmc_read_table(const unsigned int adr);
*   unsigned long long ace_bmc_tensor_matmul(const unsigned int fusable, const unsigned int t_dst, const unsigned int t_src0, const unsigned int t_src1);
*   unsigned long long ace_obmc_tensor_matmul(const unsigned int fusable, const unsigned int t_dst, const unsigned int t_src0, const unsigned int t_src1);
*   unsigned long long ace_bmc_tensor_conv2d(const unsigned int fusable, const unsigned int t_dst, const unsigned int t_src0, const unsigned int t_src1, const unsigned int extra);
*   unsigned long long ace_obmc_tensor_conv2d(const unsigned int fusable, const unsigned int t_dst, const unsigned int t_src0, const unsigned int t_src1, const unsigned int extra);
*   unsigned long long ace_bmc_tensor_add(const unsigned int fusable, const unsigned int t_dst, const unsigned int t_src0, const unsigned int t_src1);
*   unsigned long long ace_bmc_tensor_sub(const unsigned int fusable, const unsigned int t_dst, const unsigned int t_src0, const unsigned int t_src1);
*   unsigned long long ace_bmc_tensor_mul(const unsigned int fusable, const unsigned int t_dst, const unsigned int t_src0, const unsigned int t_src1);
*   unsigned long long ace_bmc_tensor_lut_lerp(const unsigned int fusable, const unsigned int t_dst, const unsigned int t_src0, const unsigned int tableN);
*   void ace_bmc_tensor_load(const unsigned int t_dst, unsigned long long x_address);
*   void ace_obmc_tensor_load(const unsigned int t_dst, unsigned long long x_address);
*   void ace_bmc_tensor_allocate(const unsigned int t_dst, unsigned long long x_header);
*   void ace_obmc_tensor_allocate(const unsigned int t_dst, unsigned long long x_header);
*   unsigned long long ace_bmc_op_poll(unsigned long long x_token);
*   unsigned long long ace_obmc_op_poll(unsigned long long x_token);
*   unsigned long long ace_bmc_op_select(unsigned long long x_token);
*   unsigned long long ace_obmc_op_select(unsigned long long x_token);
*   void ace_load_lut(const unsigned int table_idx, unsigned long long x_memory_address);
*   void ace_sbarrier();
*   void ace_scmd(unsigned long long bank_sel);
*   void ace_send_msg(const unsigned int mailbox, const unsigned int mailqueue, unsigned long long msg);
*   unsigned long long ace_rd64_addrCtl_idx(const addrCtl_idx addrCtl_idx);
*   void ace_wr64_addrCtl_idx(unsigned long long din, const addrCtl_idx addrCtl_idx);
*   unsigned long long ace_fg_st();

ACR utility intrinsic functions
----------------------------------------
*   addrCtl_t ace_rd_addrCtl (const addrCtl_idx idx);

*   void ace_wr_addrCtl (const addrCtl_idx idx, const addrCtl_t din);


ACM utility intrinsic functions
----------------------------------------

*/

// Define data type for addrCtl //
typedef unsigned long long addrCtl_t;

// Define enumerator for each register of addrCtl //
typedef enum {
	addrCtl_0 = 0,
	addrCtl_1 = 1,
	addrCtl_2 = 2,
	addrCtl_3 = 3,
	addrCtl_4 = 4,
	addrCtl_5 = 5,
	addrCtl_6 = 6,
	addrCtl_7 = 7,
	addrCtl_8 = 8,
	addrCtl_9 = 9,
	addrCtl_10 = 10,
	addrCtl_11 = 11
} addrCtl_idx;

// Define data type for cmdInfo //
typedef unsigned long long cmdInfo_t;

// Define data type for cmdReady //
typedef unsigned char cmdReady_t;

// Define data type for cmdValid //
typedef unsigned char cmdValid_t;

// Define data type for pmail_data //
typedef struct __ace_pmail_data_type__ {
	unsigned long long dword;
	unsigned int msb_10;
} pmail_data_t;

// Define data type for pmail_send //
typedef unsigned char pmail_send_t;

// Define data type for pmail_taken //
typedef unsigned char pmail_taken_t;

// Define data type for req_info //
typedef unsigned long long req_info_t;

// Define data type for req_vld //
typedef unsigned char req_vld_t;

// Define data type for rsp_info //
typedef unsigned int rsp_info_t;

// Define data type for rsp_vld //
typedef unsigned char rsp_vld_t;

// Define data type for sta //
typedef unsigned char sta_t;

// Helper function to setup system register to enable ACE //
static inline void __attribute__((always_inline)) enable_ace() {
  __asm__ __volatile__ (
    "csrr t0, mmisc_ctl\n"
    "xori t0, t0, 0x1\n"
    "ori t0, t0, 0x10\n"
    "csrw mmisc_ctl, t0\n"
    :
    :
    : "memory"
  );
}

#ifdef __cplusplus
#define ACE_OVERLOADED_ARGS ...
#else
#define ACE_OVERLOADED_ARGS
#endif

// Intrinsic function for bmc_write //
static inline void __attribute__ ((always_inline)) 
ace_bmc_write(const unsigned int adr, unsigned long long dat){
	__asm__ __volatile__ (
		"bmc_write %[adr], %[dat]"
		: 
		: [adr] "i" (adr), [dat] "r" (dat)
		: "memory"
	);
}

// Intrinsic function for bmc_read //
static inline unsigned long long __attribute__ ((always_inline)) 
ace_bmc_read(const unsigned int adr){
	unsigned long long x_dst_RetVar;
	__asm__ __volatile__ (
		"bmc_read %[x_dst], %[adr]"
		: [x_dst] "=&r" (x_dst_RetVar)
		: [adr] "i" (adr)
		: "memory"
	);
	return x_dst_RetVar;
}

// Intrinsic function for obmc_write //
static inline void __attribute__ ((always_inline)) 
ace_obmc_write(const unsigned int adr, unsigned long long dat){
	__asm__ __volatile__ (
		"obmc_write %[adr], %[dat]"
		: 
		: [adr] "i" (adr), [dat] "r" (dat)
		: "memory"
	);
}

// Intrinsic function for obmc_read //
static inline unsigned long long __attribute__ ((always_inline)) 
ace_obmc_read(const unsigned int adr){
	unsigned long long x_dst_RetVar;
	__asm__ __volatile__ (
		"obmc_read %[x_dst], %[adr]"
		: [x_dst] "=&r" (x_dst_RetVar)
		: [adr] "i" (adr)
		: "memory"
	);
	return x_dst_RetVar;
}

// Intrinsic function for bmc_write_table //
static inline void __attribute__ ((always_inline)) 
ace_bmc_write_table(const unsigned int adr, unsigned long long dat){
	__asm__ __volatile__ (
		"bmc_write_table %[adr], %[dat]"
		: 
		: [adr] "i" (adr), [dat] "r" (dat)
		: "memory"
	);
}

// Intrinsic function for bmc_read_table //
static inline unsigned long long __attribute__ ((always_inline)) 
ace_bmc_read_table(const unsigned int adr){
	unsigned long long x_dst_RetVar;
	__asm__ __volatile__ (
		"bmc_read_table %[x_dst], %[adr]"
		: [x_dst] "=&r" (x_dst_RetVar)
		: [adr] "i" (adr)
		: "memory"
	);
	return x_dst_RetVar;
}

// Intrinsic function for obmc_write_table //
static inline void __attribute__ ((always_inline)) 
ace_obmc_write_table(const unsigned int adr, unsigned long long dat){
	__asm__ __volatile__ (
		"obmc_write_table %[adr], %[dat]"
		: 
		: [adr] "i" (adr), [dat] "r" (dat)
		: "memory"
	);
}

// Intrinsic function for obmc_read_table //
static inline unsigned long long __attribute__ ((always_inline)) 
ace_obmc_read_table(const unsigned int adr){
	unsigned long long x_dst_RetVar;
	__asm__ __volatile__ (
		"obmc_read_table %[x_dst], %[adr]"
		: [x_dst] "=&r" (x_dst_RetVar)
		: [adr] "i" (adr)
		: "memory"
	);
	return x_dst_RetVar;
}

// Intrinsic function for bmc_tensor_matmul //
static inline unsigned long long __attribute__ ((always_inline)) 
ace_bmc_tensor_matmul(const unsigned int fusable, const unsigned int t_dst, const unsigned int t_src0, const unsigned int t_src1){
	unsigned long long token_RetVar;
	__asm__ __volatile__ (
		"bmc_tensor_matmul %[token], %[fusable], %[t_dst], %[t_src0], %[t_src1]"
		: [token] "=&r" (token_RetVar)
		: [fusable] "i" (fusable), [t_dst] "i" (t_dst), [t_src0] "i" (t_src0), [t_src1] "i" (t_src1)
		: "memory"
	);
	return token_RetVar;
}

// Intrinsic function for obmc_tensor_matmul //
static inline unsigned long long __attribute__ ((always_inline)) 
ace_obmc_tensor_matmul(const unsigned int fusable, const unsigned int t_dst, const unsigned int t_src0, const unsigned int t_src1){
	unsigned long long token_RetVar;
	__asm__ __volatile__ (
		"obmc_tensor_matmul %[token], %[fusable], %[t_dst], %[t_src0], %[t_src1]"
		: [token] "=&r" (token_RetVar)
		: [fusable] "i" (fusable), [t_dst] "i" (t_dst), [t_src0] "i" (t_src0), [t_src1] "i" (t_src1)
		: "memory"
	);
	return token_RetVar;
}

// Intrinsic function for bmc_tensor_conv2d //
static inline unsigned long long __attribute__ ((always_inline)) 
ace_bmc_tensor_conv2d(const unsigned int fusable, const unsigned int t_dst, const unsigned int t_src0, const unsigned int t_src1, const unsigned int extra){
	unsigned long long token_RetVar;
	__asm__ __volatile__ (
		"bmc_tensor_conv2d %[token], %[fusable], %[t_dst], %[t_src0], %[t_src1], %[extra]"
		: [token] "=&r" (token_RetVar)
		: [fusable] "i" (fusable), [t_dst] "i" (t_dst), [t_src0] "i" (t_src0), [t_src1] "i" (t_src1), [extra] "i" (extra)
		: "memory"
	);
	return token_RetVar;
}

// Intrinsic function for obmc_tensor_conv2d //
static inline unsigned long long __attribute__ ((always_inline)) 
ace_obmc_tensor_conv2d(const unsigned int fusable, const unsigned int t_dst, const unsigned int t_src0, const unsigned int t_src1, const unsigned int extra){
	unsigned long long token_RetVar;
	__asm__ __volatile__ (
		"obmc_tensor_conv2d %[token], %[fusable], %[t_dst], %[t_src0], %[t_src1], %[extra]"
		: [token] "=&r" (token_RetVar)
		: [fusable] "i" (fusable), [t_dst] "i" (t_dst), [t_src0] "i" (t_src0), [t_src1] "i" (t_src1), [extra] "i" (extra)
		: "memory"
	);
	return token_RetVar;
}

// Intrinsic function for bmc_tensor_add //
static inline unsigned long long __attribute__ ((always_inline)) 
ace_bmc_tensor_add(const unsigned int fusable, const unsigned int t_dst, const unsigned int t_src0, const unsigned int t_src1){
	unsigned long long token_RetVar;
	__asm__ __volatile__ (
		"bmc_tensor_add %[token], %[fusable], %[t_dst], %[t_src0], %[t_src1]"
		: [token] "=&r" (token_RetVar)
		: [fusable] "i" (fusable), [t_dst] "i" (t_dst), [t_src0] "i" (t_src0), [t_src1] "i" (t_src1)
		: "memory"
	);
	return token_RetVar;
}

// Intrinsic function for bmc_tensor_sub //
static inline unsigned long long __attribute__ ((always_inline)) 
ace_bmc_tensor_sub(const unsigned int fusable, const unsigned int t_dst, const unsigned int t_src0, const unsigned int t_src1){
	unsigned long long token_RetVar;
	__asm__ __volatile__ (
		"bmc_tensor_sub %[token], %[fusable], %[t_dst], %[t_src0], %[t_src1]"
		: [token] "=&r" (token_RetVar)
		: [fusable] "i" (fusable), [t_dst] "i" (t_dst), [t_src0] "i" (t_src0), [t_src1] "i" (t_src1)
		: "memory"
	);
	return token_RetVar;
}

// Intrinsic function for bmc_tensor_mul //
static inline unsigned long long __attribute__ ((always_inline)) 
ace_bmc_tensor_mul(const unsigned int fusable, const unsigned int t_dst, const unsigned int t_src0, const unsigned int t_src1){
	unsigned long long token_RetVar;
	__asm__ __volatile__ (
		"bmc_tensor_mul %[token], %[fusable], %[t_dst], %[t_src0], %[t_src1]"
		: [token] "=&r" (token_RetVar)
		: [fusable] "i" (fusable), [t_dst] "i" (t_dst), [t_src0] "i" (t_src0), [t_src1] "i" (t_src1)
		: "memory"
	);
	return token_RetVar;
}

// Intrinsic function for bmc_tensor_lut_lerp //
static inline unsigned long long __attribute__ ((always_inline)) 
ace_bmc_tensor_lut_lerp(const unsigned int fusable, const unsigned int t_dst, const unsigned int t_src0, const unsigned int tableN){
	unsigned long long token_RetVar;
	__asm__ __volatile__ (
		"bmc_tensor_lut_lerp %[token], %[fusable], %[t_dst], %[t_src0], %[tableN]"
		: [token] "=&r" (token_RetVar)
		: [fusable] "i" (fusable), [t_dst] "i" (t_dst), [t_src0] "i" (t_src0), [tableN] "i" (tableN)
		: "memory"
	);
	return token_RetVar;
}

// Intrinsic function for bmc_tensor_load //
static inline void __attribute__ ((always_inline)) 
ace_bmc_tensor_load(const unsigned int t_dst, unsigned long long x_address){
	__asm__ __volatile__ (
		"bmc_tensor_load %[t_dst], %[x_address]"
		: 
		: [t_dst] "i" (t_dst), [x_address] "r" (x_address)
		: "memory"
	);
}

// Intrinsic function for obmc_tensor_load //
static inline void __attribute__ ((always_inline)) 
ace_obmc_tensor_load(const unsigned int t_dst, unsigned long long x_address){
	__asm__ __volatile__ (
		"obmc_tensor_load %[t_dst], %[x_address]"
		: 
		: [t_dst] "i" (t_dst), [x_address] "r" (x_address)
		: "memory"
	);
}

// Intrinsic function for bmc_tensor_allocate //
static inline void __attribute__ ((always_inline)) 
ace_bmc_tensor_allocate(const unsigned int t_dst, unsigned long long x_header){
	__asm__ __volatile__ (
		"bmc_tensor_allocate %[t_dst], %[x_header]"
		: 
		: [t_dst] "i" (t_dst), [x_header] "r" (x_header)
		: "memory"
	);
}

// Intrinsic function for obmc_tensor_allocate //
static inline void __attribute__ ((always_inline)) 
ace_obmc_tensor_allocate(const unsigned int t_dst, unsigned long long x_header){
	__asm__ __volatile__ (
		"obmc_tensor_allocate %[t_dst], %[x_header]"
		: 
		: [t_dst] "i" (t_dst), [x_header] "r" (x_header)
		: "memory"
	);
}

// Intrinsic function for bmc_op_poll //
static inline unsigned long long __attribute__ ((always_inline)) 
ace_bmc_op_poll(unsigned long long x_token){
	unsigned long long x_dst_RetVar;
	__asm__ __volatile__ (
		"bmc_op_poll %[x_dst], %[x_token]"
		: [x_dst] "=&r" (x_dst_RetVar)
		: [x_token] "r" (x_token)
		: "memory"
	);
	return x_dst_RetVar;
}

// Intrinsic function for obmc_op_poll //
static inline unsigned long long __attribute__ ((always_inline)) 
ace_obmc_op_poll(unsigned long long x_token){
	unsigned long long x_dst_RetVar;
	__asm__ __volatile__ (
		"obmc_op_poll %[x_dst], %[x_token]"
		: [x_dst] "=&r" (x_dst_RetVar)
		: [x_token] "r" (x_token)
		: "memory"
	);
	return x_dst_RetVar;
}

// Intrinsic function for bmc_op_select //
static inline unsigned long long __attribute__ ((always_inline)) 
ace_bmc_op_select(unsigned long long x_token){
	unsigned long long x_dst_RetVar;
	__asm__ __volatile__ (
		"bmc_op_select %[x_dst], %[x_token]"
		: [x_dst] "=&r" (x_dst_RetVar)
		: [x_token] "r" (x_token)
		: "memory"
	);
	return x_dst_RetVar;
}

// Intrinsic function for obmc_op_select //
static inline unsigned long long __attribute__ ((always_inline)) 
ace_obmc_op_select(unsigned long long x_token){
	unsigned long long x_dst_RetVar;
	__asm__ __volatile__ (
		"obmc_op_select %[x_dst], %[x_token]"
		: [x_dst] "=&r" (x_dst_RetVar)
		: [x_token] "r" (x_token)
		: "memory"
	);
	return x_dst_RetVar;
}

// Intrinsic function for load_lut //
static inline void __attribute__ ((always_inline)) 
ace_load_lut(const unsigned int table_idx, unsigned long long x_memory_address){
	__asm__ __volatile__ (
		"load_lut %[table_idx], %[x_memory_address]"
		: 
		: [table_idx] "i" (table_idx), [x_memory_address] "r" (x_memory_address)
		: "memory"
	);
}

// Intrinsic function for sbarrier //
static inline void __attribute__ ((always_inline)) 
ace_sbarrier(){
	__asm__ __volatile__ (
		"sbarrier "
		: 
		: 
		: "memory"
	);
}

// Intrinsic function for scmd //
static inline void __attribute__ ((always_inline)) 
ace_scmd(unsigned long long bank_sel){
	__asm__ __volatile__ (
		"scmd %[bank_sel]"
		: 
		: [bank_sel] "r" (bank_sel)
		: "memory"
	);
}

// Intrinsic function for sxload //
static inline unsigned long long __attribute__ ((always_inline)) 
ace_sxload_idx(const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode){
	unsigned long long data_RetVar;
	__asm__ __volatile__ (
		"sxload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&r" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
	return data_RetVar;
}

// Intrinsic function for sfload //
static inline double __attribute__ ((always_inline)) 
ace_sfload_idx(const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode){
	double data_RetVar;
	__asm__ __volatile__ (
		"sfload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&f" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
	return data_RetVar;
}

// Intrinsic function for svload //
#if defined(__clang__)
static inline vint32mf2_t __attribute__ ((always_inline)) 
ace_svload_i32mf2_st_idx(const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vint32mf2_t data_RetVar;
	vsetvl_e32mf2(vl);
	__asm__ __volatile__ (
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
	return data_RetVar;
}
static inline vint32m1_t __attribute__ ((always_inline)) 
ace_svload_i32m1_st_idx(const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vint32m1_t data_RetVar;
	vsetvl_e32m1(vl);
	__asm__ __volatile__ (
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
	return data_RetVar;
}
static inline vint32m2_t __attribute__ ((always_inline)) 
ace_svload_i32m2_st_idx(const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vint32m2_t data_RetVar;
	vsetvl_e32m2(vl);
	__asm__ __volatile__ (
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
	return data_RetVar;
}
static inline vint32m4_t __attribute__ ((always_inline)) 
ace_svload_i32m4_st_idx(const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vint32m4_t data_RetVar;
	vsetvl_e32m4(vl);
	__asm__ __volatile__ (
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
	return data_RetVar;
}
static inline vint32m8_t __attribute__ ((always_inline)) 
ace_svload_i32m8_st_idx(const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vint32m8_t data_RetVar;
	vsetvl_e32m8(vl);
	__asm__ __volatile__ (
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
	return data_RetVar;
}
static inline vint16mf4_t __attribute__ ((always_inline)) 
ace_svload_i16mf4_st_idx(const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vint16mf4_t data_RetVar;
	vsetvl_e16mf4(vl);
	__asm__ __volatile__ (
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
	return data_RetVar;
}
static inline vint16mf2_t __attribute__ ((always_inline)) 
ace_svload_i16mf2_st_idx(const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vint16mf2_t data_RetVar;
	vsetvl_e16mf2(vl);
	__asm__ __volatile__ (
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
	return data_RetVar;
}
static inline vint16m1_t __attribute__ ((always_inline)) 
ace_svload_i16m1_st_idx(const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vint16m1_t data_RetVar;
	vsetvl_e16m1(vl);
	__asm__ __volatile__ (
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
	return data_RetVar;
}
static inline vint16m2_t __attribute__ ((always_inline)) 
ace_svload_i16m2_st_idx(const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vint16m2_t data_RetVar;
	vsetvl_e16m2(vl);
	__asm__ __volatile__ (
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
	return data_RetVar;
}
static inline vint16m4_t __attribute__ ((always_inline)) 
ace_svload_i16m4_st_idx(const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vint16m4_t data_RetVar;
	vsetvl_e16m4(vl);
	__asm__ __volatile__ (
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
	return data_RetVar;
}
static inline vint16m8_t __attribute__ ((always_inline)) 
ace_svload_i16m8_st_idx(const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vint16m8_t data_RetVar;
	vsetvl_e16m8(vl);
	__asm__ __volatile__ (
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
	return data_RetVar;
}
static inline vint8mf8_t __attribute__ ((always_inline)) 
ace_svload_i8mf8_st_idx(const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vint8mf8_t data_RetVar;
	vsetvl_e8mf8(vl);
	__asm__ __volatile__ (
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
	return data_RetVar;
}
static inline vint8mf4_t __attribute__ ((always_inline)) 
ace_svload_i8mf4_st_idx(const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vint8mf4_t data_RetVar;
	vsetvl_e8mf4(vl);
	__asm__ __volatile__ (
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
	return data_RetVar;
}
static inline vint8mf2_t __attribute__ ((always_inline)) 
ace_svload_i8mf2_st_idx(const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vint8mf2_t data_RetVar;
	vsetvl_e8mf2(vl);
	__asm__ __volatile__ (
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
	return data_RetVar;
}
static inline vint8m1_t __attribute__ ((always_inline)) 
ace_svload_i8m1_st_idx(const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vint8m1_t data_RetVar;
	vsetvl_e8m1(vl);
	__asm__ __volatile__ (
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
	return data_RetVar;
}
static inline vint8m2_t __attribute__ ((always_inline)) 
ace_svload_i8m2_st_idx(const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vint8m2_t data_RetVar;
	vsetvl_e8m2(vl);
	__asm__ __volatile__ (
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
	return data_RetVar;
}
static inline vint8m4_t __attribute__ ((always_inline)) 
ace_svload_i8m4_st_idx(const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vint8m4_t data_RetVar;
	vsetvl_e8m4(vl);
	__asm__ __volatile__ (
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
	return data_RetVar;
}
static inline vint8m8_t __attribute__ ((always_inline)) 
ace_svload_i8m8_st_idx(const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vint8m8_t data_RetVar;
	vsetvl_e8m8(vl);
	__asm__ __volatile__ (
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
	return data_RetVar;
}
static inline vint64m1_t __attribute__ ((always_inline)) 
ace_svload_i64m1_st_idx(const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vint64m1_t data_RetVar;
	vsetvl_e64m1(vl);
	__asm__ __volatile__ (
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
	return data_RetVar;
}
static inline vint64m2_t __attribute__ ((always_inline)) 
ace_svload_i64m2_st_idx(const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vint64m2_t data_RetVar;
	vsetvl_e64m2(vl);
	__asm__ __volatile__ (
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
	return data_RetVar;
}
static inline vint64m4_t __attribute__ ((always_inline)) 
ace_svload_i64m4_st_idx(const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vint64m4_t data_RetVar;
	vsetvl_e64m4(vl);
	__asm__ __volatile__ (
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
	return data_RetVar;
}
static inline vint64m8_t __attribute__ ((always_inline)) 
ace_svload_i64m8_st_idx(const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vint64m8_t data_RetVar;
	vsetvl_e64m8(vl);
	__asm__ __volatile__ (
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
	return data_RetVar;
}
static inline vfloat32mf2_t __attribute__ ((always_inline)) 
ace_svload_f32mf2_st_idx(const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vfloat32mf2_t data_RetVar;
	vsetvl_e32mf2(vl);
	__asm__ __volatile__ (
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
	return data_RetVar;
}
static inline vfloat32m1_t __attribute__ ((always_inline)) 
ace_svload_f32m1_st_idx(const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vfloat32m1_t data_RetVar;
	vsetvl_e32m1(vl);
	__asm__ __volatile__ (
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
	return data_RetVar;
}
static inline vfloat32m2_t __attribute__ ((always_inline)) 
ace_svload_f32m2_st_idx(const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vfloat32m2_t data_RetVar;
	vsetvl_e32m2(vl);
	__asm__ __volatile__ (
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
	return data_RetVar;
}
static inline vfloat32m4_t __attribute__ ((always_inline)) 
ace_svload_f32m4_st_idx(const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vfloat32m4_t data_RetVar;
	vsetvl_e32m4(vl);
	__asm__ __volatile__ (
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
	return data_RetVar;
}
static inline vfloat32m8_t __attribute__ ((always_inline)) 
ace_svload_f32m8_st_idx(const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vfloat32m8_t data_RetVar;
	vsetvl_e32m8(vl);
	__asm__ __volatile__ (
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
	return data_RetVar;
}
static inline vfloat16mf4_t __attribute__ ((always_inline)) 
ace_svload_f16mf4_st_idx(const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vfloat16mf4_t data_RetVar;
	vsetvl_e16mf4(vl);
	__asm__ __volatile__ (
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
	return data_RetVar;
}
static inline vfloat16mf2_t __attribute__ ((always_inline)) 
ace_svload_f16mf2_st_idx(const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vfloat16mf2_t data_RetVar;
	vsetvl_e16mf2(vl);
	__asm__ __volatile__ (
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
	return data_RetVar;
}
static inline vfloat16m1_t __attribute__ ((always_inline)) 
ace_svload_f16m1_st_idx(const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vfloat16m1_t data_RetVar;
	vsetvl_e16m1(vl);
	__asm__ __volatile__ (
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
	return data_RetVar;
}
static inline vfloat16m2_t __attribute__ ((always_inline)) 
ace_svload_f16m2_st_idx(const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vfloat16m2_t data_RetVar;
	vsetvl_e16m2(vl);
	__asm__ __volatile__ (
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
	return data_RetVar;
}
static inline vfloat16m4_t __attribute__ ((always_inline)) 
ace_svload_f16m4_st_idx(const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vfloat16m4_t data_RetVar;
	vsetvl_e16m4(vl);
	__asm__ __volatile__ (
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
	return data_RetVar;
}
static inline vfloat16m8_t __attribute__ ((always_inline)) 
ace_svload_f16m8_st_idx(const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vfloat16m8_t data_RetVar;
	vsetvl_e16m8(vl);
	__asm__ __volatile__ (
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
	return data_RetVar;
}
static inline vfloat64m1_t __attribute__ ((always_inline)) 
ace_svload_f64m1_st_idx(const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vfloat64m1_t data_RetVar;
	vsetvl_e64m1(vl);
	__asm__ __volatile__ (
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
	return data_RetVar;
}
static inline vfloat64m2_t __attribute__ ((always_inline)) 
ace_svload_f64m2_st_idx(const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vfloat64m2_t data_RetVar;
	vsetvl_e64m2(vl);
	__asm__ __volatile__ (
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
	return data_RetVar;
}
static inline vfloat64m4_t __attribute__ ((always_inline)) 
ace_svload_f64m4_st_idx(const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vfloat64m4_t data_RetVar;
	vsetvl_e64m4(vl);
	__asm__ __volatile__ (
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
	return data_RetVar;
}
static inline vfloat64m8_t __attribute__ ((always_inline)) 
ace_svload_f64m8_st_idx(const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vfloat64m8_t data_RetVar;
	vsetvl_e64m8(vl);
	__asm__ __volatile__ (
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
	return data_RetVar;
}
static inline vuint32mf2_t __attribute__ ((always_inline)) 
ace_svload_u32mf2_st_idx(const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vuint32mf2_t data_RetVar;
	vsetvl_e32mf2(vl);
	__asm__ __volatile__ (
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
	return data_RetVar;
}
static inline vuint32m1_t __attribute__ ((always_inline)) 
ace_svload_u32m1_st_idx(const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vuint32m1_t data_RetVar;
	vsetvl_e32m1(vl);
	__asm__ __volatile__ (
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
	return data_RetVar;
}
static inline vuint32m2_t __attribute__ ((always_inline)) 
ace_svload_u32m2_st_idx(const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vuint32m2_t data_RetVar;
	vsetvl_e32m2(vl);
	__asm__ __volatile__ (
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
	return data_RetVar;
}
static inline vuint32m4_t __attribute__ ((always_inline)) 
ace_svload_u32m4_st_idx(const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vuint32m4_t data_RetVar;
	vsetvl_e32m4(vl);
	__asm__ __volatile__ (
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
	return data_RetVar;
}
static inline vuint32m8_t __attribute__ ((always_inline)) 
ace_svload_u32m8_st_idx(const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vuint32m8_t data_RetVar;
	vsetvl_e32m8(vl);
	__asm__ __volatile__ (
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
	return data_RetVar;
}
static inline vuint16mf4_t __attribute__ ((always_inline)) 
ace_svload_u16mf4_st_idx(const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vuint16mf4_t data_RetVar;
	vsetvl_e16mf4(vl);
	__asm__ __volatile__ (
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
	return data_RetVar;
}
static inline vuint16mf2_t __attribute__ ((always_inline)) 
ace_svload_u16mf2_st_idx(const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vuint16mf2_t data_RetVar;
	vsetvl_e16mf2(vl);
	__asm__ __volatile__ (
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
	return data_RetVar;
}
static inline vuint16m1_t __attribute__ ((always_inline)) 
ace_svload_u16m1_st_idx(const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vuint16m1_t data_RetVar;
	vsetvl_e16m1(vl);
	__asm__ __volatile__ (
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
	return data_RetVar;
}
static inline vuint16m2_t __attribute__ ((always_inline)) 
ace_svload_u16m2_st_idx(const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vuint16m2_t data_RetVar;
	vsetvl_e16m2(vl);
	__asm__ __volatile__ (
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
	return data_RetVar;
}
static inline vuint16m4_t __attribute__ ((always_inline)) 
ace_svload_u16m4_st_idx(const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vuint16m4_t data_RetVar;
	vsetvl_e16m4(vl);
	__asm__ __volatile__ (
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
	return data_RetVar;
}
static inline vuint16m8_t __attribute__ ((always_inline)) 
ace_svload_u16m8_st_idx(const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vuint16m8_t data_RetVar;
	vsetvl_e16m8(vl);
	__asm__ __volatile__ (
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
	return data_RetVar;
}
static inline vuint8mf8_t __attribute__ ((always_inline)) 
ace_svload_u8mf8_st_idx(const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vuint8mf8_t data_RetVar;
	vsetvl_e8mf8(vl);
	__asm__ __volatile__ (
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
	return data_RetVar;
}
static inline vuint8mf4_t __attribute__ ((always_inline)) 
ace_svload_u8mf4_st_idx(const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vuint8mf4_t data_RetVar;
	vsetvl_e8mf4(vl);
	__asm__ __volatile__ (
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
	return data_RetVar;
}
static inline vuint8mf2_t __attribute__ ((always_inline)) 
ace_svload_u8mf2_st_idx(const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vuint8mf2_t data_RetVar;
	vsetvl_e8mf2(vl);
	__asm__ __volatile__ (
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
	return data_RetVar;
}
static inline vuint8m1_t __attribute__ ((always_inline)) 
ace_svload_u8m1_st_idx(const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vuint8m1_t data_RetVar;
	vsetvl_e8m1(vl);
	__asm__ __volatile__ (
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
	return data_RetVar;
}
static inline vuint8m2_t __attribute__ ((always_inline)) 
ace_svload_u8m2_st_idx(const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vuint8m2_t data_RetVar;
	vsetvl_e8m2(vl);
	__asm__ __volatile__ (
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
	return data_RetVar;
}
static inline vuint8m4_t __attribute__ ((always_inline)) 
ace_svload_u8m4_st_idx(const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vuint8m4_t data_RetVar;
	vsetvl_e8m4(vl);
	__asm__ __volatile__ (
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
	return data_RetVar;
}
static inline vuint8m8_t __attribute__ ((always_inline)) 
ace_svload_u8m8_st_idx(const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vuint8m8_t data_RetVar;
	vsetvl_e8m8(vl);
	__asm__ __volatile__ (
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
	return data_RetVar;
}
static inline vuint64m1_t __attribute__ ((always_inline)) 
ace_svload_u64m1_st_idx(const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vuint64m1_t data_RetVar;
	vsetvl_e64m1(vl);
	__asm__ __volatile__ (
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
	return data_RetVar;
}
static inline vuint64m2_t __attribute__ ((always_inline)) 
ace_svload_u64m2_st_idx(const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vuint64m2_t data_RetVar;
	vsetvl_e64m2(vl);
	__asm__ __volatile__ (
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
	return data_RetVar;
}
static inline vuint64m4_t __attribute__ ((always_inline)) 
ace_svload_u64m4_st_idx(const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vuint64m4_t data_RetVar;
	vsetvl_e64m4(vl);
	__asm__ __volatile__ (
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
	return data_RetVar;
}
static inline vuint64m8_t __attribute__ ((always_inline)) 
ace_svload_u64m8_st_idx(const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vuint64m8_t data_RetVar;
	vsetvl_e64m8(vl);
	__asm__ __volatile__ (
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
	return data_RetVar;
}
#endif

// Intrinsic function for svload //
#if defined(__clang__)
static inline vint32mf2_t __attribute__ ((always_inline)) 
ace_svload_i32mf2_m_st_idx(vbool64_t ace_rvv_mask, vint32mf2_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vint32mf2_t data_RetVar;
	vsetvl_e32mf2(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask), "[data]" (ace_rvv_maskoff)
		: "memory", "v0"
	);
	return data_RetVar;
}
static inline vint32m1_t __attribute__ ((always_inline)) 
ace_svload_i32m1_m_st_idx(vbool32_t ace_rvv_mask, vint32m1_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vint32m1_t data_RetVar;
	vsetvl_e32m1(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask), "[data]" (ace_rvv_maskoff)
		: "memory", "v0"
	);
	return data_RetVar;
}
static inline vint32m2_t __attribute__ ((always_inline)) 
ace_svload_i32m2_m_st_idx(vbool16_t ace_rvv_mask, vint32m2_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vint32m2_t data_RetVar;
	vsetvl_e32m2(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask), "[data]" (ace_rvv_maskoff)
		: "memory", "v0"
	);
	return data_RetVar;
}
static inline vint32m4_t __attribute__ ((always_inline)) 
ace_svload_i32m4_m_st_idx(vbool8_t ace_rvv_mask, vint32m4_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vint32m4_t data_RetVar;
	vsetvl_e32m4(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask), "[data]" (ace_rvv_maskoff)
		: "memory", "v0"
	);
	return data_RetVar;
}
static inline vint32m8_t __attribute__ ((always_inline)) 
ace_svload_i32m8_m_st_idx(vbool4_t ace_rvv_mask, vint32m8_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vint32m8_t data_RetVar;
	vsetvl_e32m8(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask), "[data]" (ace_rvv_maskoff)
		: "memory", "v0"
	);
	return data_RetVar;
}
static inline vint16mf4_t __attribute__ ((always_inline)) 
ace_svload_i16mf4_m_st_idx(vbool64_t ace_rvv_mask, vint16mf4_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vint16mf4_t data_RetVar;
	vsetvl_e16mf4(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask), "[data]" (ace_rvv_maskoff)
		: "memory", "v0"
	);
	return data_RetVar;
}
static inline vint16mf2_t __attribute__ ((always_inline)) 
ace_svload_i16mf2_m_st_idx(vbool32_t ace_rvv_mask, vint16mf2_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vint16mf2_t data_RetVar;
	vsetvl_e16mf2(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask), "[data]" (ace_rvv_maskoff)
		: "memory", "v0"
	);
	return data_RetVar;
}
static inline vint16m1_t __attribute__ ((always_inline)) 
ace_svload_i16m1_m_st_idx(vbool16_t ace_rvv_mask, vint16m1_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vint16m1_t data_RetVar;
	vsetvl_e16m1(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask), "[data]" (ace_rvv_maskoff)
		: "memory", "v0"
	);
	return data_RetVar;
}
static inline vint16m2_t __attribute__ ((always_inline)) 
ace_svload_i16m2_m_st_idx(vbool8_t ace_rvv_mask, vint16m2_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vint16m2_t data_RetVar;
	vsetvl_e16m2(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask), "[data]" (ace_rvv_maskoff)
		: "memory", "v0"
	);
	return data_RetVar;
}
static inline vint16m4_t __attribute__ ((always_inline)) 
ace_svload_i16m4_m_st_idx(vbool4_t ace_rvv_mask, vint16m4_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vint16m4_t data_RetVar;
	vsetvl_e16m4(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask), "[data]" (ace_rvv_maskoff)
		: "memory", "v0"
	);
	return data_RetVar;
}
static inline vint16m8_t __attribute__ ((always_inline)) 
ace_svload_i16m8_m_st_idx(vbool2_t ace_rvv_mask, vint16m8_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vint16m8_t data_RetVar;
	vsetvl_e16m8(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask), "[data]" (ace_rvv_maskoff)
		: "memory", "v0"
	);
	return data_RetVar;
}
static inline vint8mf8_t __attribute__ ((always_inline)) 
ace_svload_i8mf8_m_st_idx(vbool64_t ace_rvv_mask, vint8mf8_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vint8mf8_t data_RetVar;
	vsetvl_e8mf8(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask), "[data]" (ace_rvv_maskoff)
		: "memory", "v0"
	);
	return data_RetVar;
}
static inline vint8mf4_t __attribute__ ((always_inline)) 
ace_svload_i8mf4_m_st_idx(vbool32_t ace_rvv_mask, vint8mf4_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vint8mf4_t data_RetVar;
	vsetvl_e8mf4(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask), "[data]" (ace_rvv_maskoff)
		: "memory", "v0"
	);
	return data_RetVar;
}
static inline vint8mf2_t __attribute__ ((always_inline)) 
ace_svload_i8mf2_m_st_idx(vbool16_t ace_rvv_mask, vint8mf2_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vint8mf2_t data_RetVar;
	vsetvl_e8mf2(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask), "[data]" (ace_rvv_maskoff)
		: "memory", "v0"
	);
	return data_RetVar;
}
static inline vint8m1_t __attribute__ ((always_inline)) 
ace_svload_i8m1_m_st_idx(vbool8_t ace_rvv_mask, vint8m1_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vint8m1_t data_RetVar;
	vsetvl_e8m1(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask), "[data]" (ace_rvv_maskoff)
		: "memory", "v0"
	);
	return data_RetVar;
}
static inline vint8m2_t __attribute__ ((always_inline)) 
ace_svload_i8m2_m_st_idx(vbool4_t ace_rvv_mask, vint8m2_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vint8m2_t data_RetVar;
	vsetvl_e8m2(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask), "[data]" (ace_rvv_maskoff)
		: "memory", "v0"
	);
	return data_RetVar;
}
static inline vint8m4_t __attribute__ ((always_inline)) 
ace_svload_i8m4_m_st_idx(vbool2_t ace_rvv_mask, vint8m4_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vint8m4_t data_RetVar;
	vsetvl_e8m4(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask), "[data]" (ace_rvv_maskoff)
		: "memory", "v0"
	);
	return data_RetVar;
}
static inline vint8m8_t __attribute__ ((always_inline)) 
ace_svload_i8m8_m_st_idx(vbool1_t ace_rvv_mask, vint8m8_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vint8m8_t data_RetVar;
	vsetvl_e8m8(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask), "[data]" (ace_rvv_maskoff)
		: "memory", "v0"
	);
	return data_RetVar;
}
static inline vint64m1_t __attribute__ ((always_inline)) 
ace_svload_i64m1_m_st_idx(vbool64_t ace_rvv_mask, vint64m1_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vint64m1_t data_RetVar;
	vsetvl_e64m1(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask), "[data]" (ace_rvv_maskoff)
		: "memory", "v0"
	);
	return data_RetVar;
}
static inline vint64m2_t __attribute__ ((always_inline)) 
ace_svload_i64m2_m_st_idx(vbool32_t ace_rvv_mask, vint64m2_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vint64m2_t data_RetVar;
	vsetvl_e64m2(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask), "[data]" (ace_rvv_maskoff)
		: "memory", "v0"
	);
	return data_RetVar;
}
static inline vint64m4_t __attribute__ ((always_inline)) 
ace_svload_i64m4_m_st_idx(vbool16_t ace_rvv_mask, vint64m4_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vint64m4_t data_RetVar;
	vsetvl_e64m4(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask), "[data]" (ace_rvv_maskoff)
		: "memory", "v0"
	);
	return data_RetVar;
}
static inline vint64m8_t __attribute__ ((always_inline)) 
ace_svload_i64m8_m_st_idx(vbool8_t ace_rvv_mask, vint64m8_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vint64m8_t data_RetVar;
	vsetvl_e64m8(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask), "[data]" (ace_rvv_maskoff)
		: "memory", "v0"
	);
	return data_RetVar;
}
static inline vfloat32mf2_t __attribute__ ((always_inline)) 
ace_svload_f32mf2_m_st_idx(vbool64_t ace_rvv_mask, vfloat32mf2_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vfloat32mf2_t data_RetVar;
	vsetvl_e32mf2(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask), "[data]" (ace_rvv_maskoff)
		: "memory", "v0"
	);
	return data_RetVar;
}
static inline vfloat32m1_t __attribute__ ((always_inline)) 
ace_svload_f32m1_m_st_idx(vbool32_t ace_rvv_mask, vfloat32m1_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vfloat32m1_t data_RetVar;
	vsetvl_e32m1(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask), "[data]" (ace_rvv_maskoff)
		: "memory", "v0"
	);
	return data_RetVar;
}
static inline vfloat32m2_t __attribute__ ((always_inline)) 
ace_svload_f32m2_m_st_idx(vbool16_t ace_rvv_mask, vfloat32m2_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vfloat32m2_t data_RetVar;
	vsetvl_e32m2(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask), "[data]" (ace_rvv_maskoff)
		: "memory", "v0"
	);
	return data_RetVar;
}
static inline vfloat32m4_t __attribute__ ((always_inline)) 
ace_svload_f32m4_m_st_idx(vbool8_t ace_rvv_mask, vfloat32m4_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vfloat32m4_t data_RetVar;
	vsetvl_e32m4(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask), "[data]" (ace_rvv_maskoff)
		: "memory", "v0"
	);
	return data_RetVar;
}
static inline vfloat32m8_t __attribute__ ((always_inline)) 
ace_svload_f32m8_m_st_idx(vbool4_t ace_rvv_mask, vfloat32m8_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vfloat32m8_t data_RetVar;
	vsetvl_e32m8(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask), "[data]" (ace_rvv_maskoff)
		: "memory", "v0"
	);
	return data_RetVar;
}
static inline vfloat16mf4_t __attribute__ ((always_inline)) 
ace_svload_f16mf4_m_st_idx(vbool64_t ace_rvv_mask, vfloat16mf4_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vfloat16mf4_t data_RetVar;
	vsetvl_e16mf4(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask), "[data]" (ace_rvv_maskoff)
		: "memory", "v0"
	);
	return data_RetVar;
}
static inline vfloat16mf2_t __attribute__ ((always_inline)) 
ace_svload_f16mf2_m_st_idx(vbool32_t ace_rvv_mask, vfloat16mf2_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vfloat16mf2_t data_RetVar;
	vsetvl_e16mf2(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask), "[data]" (ace_rvv_maskoff)
		: "memory", "v0"
	);
	return data_RetVar;
}
static inline vfloat16m1_t __attribute__ ((always_inline)) 
ace_svload_f16m1_m_st_idx(vbool16_t ace_rvv_mask, vfloat16m1_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vfloat16m1_t data_RetVar;
	vsetvl_e16m1(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask), "[data]" (ace_rvv_maskoff)
		: "memory", "v0"
	);
	return data_RetVar;
}
static inline vfloat16m2_t __attribute__ ((always_inline)) 
ace_svload_f16m2_m_st_idx(vbool8_t ace_rvv_mask, vfloat16m2_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vfloat16m2_t data_RetVar;
	vsetvl_e16m2(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask), "[data]" (ace_rvv_maskoff)
		: "memory", "v0"
	);
	return data_RetVar;
}
static inline vfloat16m4_t __attribute__ ((always_inline)) 
ace_svload_f16m4_m_st_idx(vbool4_t ace_rvv_mask, vfloat16m4_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vfloat16m4_t data_RetVar;
	vsetvl_e16m4(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask), "[data]" (ace_rvv_maskoff)
		: "memory", "v0"
	);
	return data_RetVar;
}
static inline vfloat16m8_t __attribute__ ((always_inline)) 
ace_svload_f16m8_m_st_idx(vbool2_t ace_rvv_mask, vfloat16m8_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vfloat16m8_t data_RetVar;
	vsetvl_e16m8(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask), "[data]" (ace_rvv_maskoff)
		: "memory", "v0"
	);
	return data_RetVar;
}
static inline vfloat64m1_t __attribute__ ((always_inline)) 
ace_svload_f64m1_m_st_idx(vbool64_t ace_rvv_mask, vfloat64m1_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vfloat64m1_t data_RetVar;
	vsetvl_e64m1(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask), "[data]" (ace_rvv_maskoff)
		: "memory", "v0"
	);
	return data_RetVar;
}
static inline vfloat64m2_t __attribute__ ((always_inline)) 
ace_svload_f64m2_m_st_idx(vbool32_t ace_rvv_mask, vfloat64m2_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vfloat64m2_t data_RetVar;
	vsetvl_e64m2(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask), "[data]" (ace_rvv_maskoff)
		: "memory", "v0"
	);
	return data_RetVar;
}
static inline vfloat64m4_t __attribute__ ((always_inline)) 
ace_svload_f64m4_m_st_idx(vbool16_t ace_rvv_mask, vfloat64m4_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vfloat64m4_t data_RetVar;
	vsetvl_e64m4(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask), "[data]" (ace_rvv_maskoff)
		: "memory", "v0"
	);
	return data_RetVar;
}
static inline vfloat64m8_t __attribute__ ((always_inline)) 
ace_svload_f64m8_m_st_idx(vbool8_t ace_rvv_mask, vfloat64m8_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vfloat64m8_t data_RetVar;
	vsetvl_e64m8(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask), "[data]" (ace_rvv_maskoff)
		: "memory", "v0"
	);
	return data_RetVar;
}
static inline vuint32mf2_t __attribute__ ((always_inline)) 
ace_svload_u32mf2_m_st_idx(vbool64_t ace_rvv_mask, vuint32mf2_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vuint32mf2_t data_RetVar;
	vsetvl_e32mf2(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask), "[data]" (ace_rvv_maskoff)
		: "memory", "v0"
	);
	return data_RetVar;
}
static inline vuint32m1_t __attribute__ ((always_inline)) 
ace_svload_u32m1_m_st_idx(vbool32_t ace_rvv_mask, vuint32m1_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vuint32m1_t data_RetVar;
	vsetvl_e32m1(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask), "[data]" (ace_rvv_maskoff)
		: "memory", "v0"
	);
	return data_RetVar;
}
static inline vuint32m2_t __attribute__ ((always_inline)) 
ace_svload_u32m2_m_st_idx(vbool16_t ace_rvv_mask, vuint32m2_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vuint32m2_t data_RetVar;
	vsetvl_e32m2(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask), "[data]" (ace_rvv_maskoff)
		: "memory", "v0"
	);
	return data_RetVar;
}
static inline vuint32m4_t __attribute__ ((always_inline)) 
ace_svload_u32m4_m_st_idx(vbool8_t ace_rvv_mask, vuint32m4_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vuint32m4_t data_RetVar;
	vsetvl_e32m4(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask), "[data]" (ace_rvv_maskoff)
		: "memory", "v0"
	);
	return data_RetVar;
}
static inline vuint32m8_t __attribute__ ((always_inline)) 
ace_svload_u32m8_m_st_idx(vbool4_t ace_rvv_mask, vuint32m8_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vuint32m8_t data_RetVar;
	vsetvl_e32m8(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask), "[data]" (ace_rvv_maskoff)
		: "memory", "v0"
	);
	return data_RetVar;
}
static inline vuint16mf4_t __attribute__ ((always_inline)) 
ace_svload_u16mf4_m_st_idx(vbool64_t ace_rvv_mask, vuint16mf4_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vuint16mf4_t data_RetVar;
	vsetvl_e16mf4(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask), "[data]" (ace_rvv_maskoff)
		: "memory", "v0"
	);
	return data_RetVar;
}
static inline vuint16mf2_t __attribute__ ((always_inline)) 
ace_svload_u16mf2_m_st_idx(vbool32_t ace_rvv_mask, vuint16mf2_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vuint16mf2_t data_RetVar;
	vsetvl_e16mf2(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask), "[data]" (ace_rvv_maskoff)
		: "memory", "v0"
	);
	return data_RetVar;
}
static inline vuint16m1_t __attribute__ ((always_inline)) 
ace_svload_u16m1_m_st_idx(vbool16_t ace_rvv_mask, vuint16m1_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vuint16m1_t data_RetVar;
	vsetvl_e16m1(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask), "[data]" (ace_rvv_maskoff)
		: "memory", "v0"
	);
	return data_RetVar;
}
static inline vuint16m2_t __attribute__ ((always_inline)) 
ace_svload_u16m2_m_st_idx(vbool8_t ace_rvv_mask, vuint16m2_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vuint16m2_t data_RetVar;
	vsetvl_e16m2(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask), "[data]" (ace_rvv_maskoff)
		: "memory", "v0"
	);
	return data_RetVar;
}
static inline vuint16m4_t __attribute__ ((always_inline)) 
ace_svload_u16m4_m_st_idx(vbool4_t ace_rvv_mask, vuint16m4_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vuint16m4_t data_RetVar;
	vsetvl_e16m4(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask), "[data]" (ace_rvv_maskoff)
		: "memory", "v0"
	);
	return data_RetVar;
}
static inline vuint16m8_t __attribute__ ((always_inline)) 
ace_svload_u16m8_m_st_idx(vbool2_t ace_rvv_mask, vuint16m8_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vuint16m8_t data_RetVar;
	vsetvl_e16m8(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask), "[data]" (ace_rvv_maskoff)
		: "memory", "v0"
	);
	return data_RetVar;
}
static inline vuint8mf8_t __attribute__ ((always_inline)) 
ace_svload_u8mf8_m_st_idx(vbool64_t ace_rvv_mask, vuint8mf8_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vuint8mf8_t data_RetVar;
	vsetvl_e8mf8(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask), "[data]" (ace_rvv_maskoff)
		: "memory", "v0"
	);
	return data_RetVar;
}
static inline vuint8mf4_t __attribute__ ((always_inline)) 
ace_svload_u8mf4_m_st_idx(vbool32_t ace_rvv_mask, vuint8mf4_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vuint8mf4_t data_RetVar;
	vsetvl_e8mf4(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask), "[data]" (ace_rvv_maskoff)
		: "memory", "v0"
	);
	return data_RetVar;
}
static inline vuint8mf2_t __attribute__ ((always_inline)) 
ace_svload_u8mf2_m_st_idx(vbool16_t ace_rvv_mask, vuint8mf2_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vuint8mf2_t data_RetVar;
	vsetvl_e8mf2(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask), "[data]" (ace_rvv_maskoff)
		: "memory", "v0"
	);
	return data_RetVar;
}
static inline vuint8m1_t __attribute__ ((always_inline)) 
ace_svload_u8m1_m_st_idx(vbool8_t ace_rvv_mask, vuint8m1_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vuint8m1_t data_RetVar;
	vsetvl_e8m1(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask), "[data]" (ace_rvv_maskoff)
		: "memory", "v0"
	);
	return data_RetVar;
}
static inline vuint8m2_t __attribute__ ((always_inline)) 
ace_svload_u8m2_m_st_idx(vbool4_t ace_rvv_mask, vuint8m2_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vuint8m2_t data_RetVar;
	vsetvl_e8m2(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask), "[data]" (ace_rvv_maskoff)
		: "memory", "v0"
	);
	return data_RetVar;
}
static inline vuint8m4_t __attribute__ ((always_inline)) 
ace_svload_u8m4_m_st_idx(vbool2_t ace_rvv_mask, vuint8m4_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vuint8m4_t data_RetVar;
	vsetvl_e8m4(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask), "[data]" (ace_rvv_maskoff)
		: "memory", "v0"
	);
	return data_RetVar;
}
static inline vuint8m8_t __attribute__ ((always_inline)) 
ace_svload_u8m8_m_st_idx(vbool1_t ace_rvv_mask, vuint8m8_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vuint8m8_t data_RetVar;
	vsetvl_e8m8(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask), "[data]" (ace_rvv_maskoff)
		: "memory", "v0"
	);
	return data_RetVar;
}
static inline vuint64m1_t __attribute__ ((always_inline)) 
ace_svload_u64m1_m_st_idx(vbool64_t ace_rvv_mask, vuint64m1_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vuint64m1_t data_RetVar;
	vsetvl_e64m1(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask), "[data]" (ace_rvv_maskoff)
		: "memory", "v0"
	);
	return data_RetVar;
}
static inline vuint64m2_t __attribute__ ((always_inline)) 
ace_svload_u64m2_m_st_idx(vbool32_t ace_rvv_mask, vuint64m2_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vuint64m2_t data_RetVar;
	vsetvl_e64m2(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask), "[data]" (ace_rvv_maskoff)
		: "memory", "v0"
	);
	return data_RetVar;
}
static inline vuint64m4_t __attribute__ ((always_inline)) 
ace_svload_u64m4_m_st_idx(vbool16_t ace_rvv_mask, vuint64m4_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vuint64m4_t data_RetVar;
	vsetvl_e64m4(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask), "[data]" (ace_rvv_maskoff)
		: "memory", "v0"
	);
	return data_RetVar;
}
static inline vuint64m8_t __attribute__ ((always_inline)) 
ace_svload_u64m8_m_st_idx(vbool8_t ace_rvv_mask, vuint64m8_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vuint64m8_t data_RetVar;
	vsetvl_e64m8(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svload %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: [data] "=&vr" (data_RetVar)
		: [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask), "[data]" (ace_rvv_maskoff)
		: "memory", "v0"
	);
	return data_RetVar;
}
#endif

// Intrinsic function for sxstore //
static inline void __attribute__ ((always_inline)) 
ace_sxstore_idx(unsigned long long data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode){
	__asm__ __volatile__ (
		"sxstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "r" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
}

// Intrinsic function for sfstore //
static inline void __attribute__ ((always_inline)) 
ace_sfstore_idx(double data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode){
	__asm__ __volatile__ (
		"sfstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "f" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
}

// Intrinsic function for svstore //
#if defined(__clang__)
static inline void __attribute__ ((always_inline)) 
ace_svstore_i32mf2_st_idx(vint32mf2_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e32mf2(vl);
	__asm__ __volatile__ (
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_i32m1_st_idx(vint32m1_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e32m1(vl);
	__asm__ __volatile__ (
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_i32m2_st_idx(vint32m2_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e32m2(vl);
	__asm__ __volatile__ (
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_i32m4_st_idx(vint32m4_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e32m4(vl);
	__asm__ __volatile__ (
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_i32m8_st_idx(vint32m8_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e32m8(vl);
	__asm__ __volatile__ (
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_i16mf4_st_idx(vint16mf4_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e16mf4(vl);
	__asm__ __volatile__ (
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_i16mf2_st_idx(vint16mf2_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e16mf2(vl);
	__asm__ __volatile__ (
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_i16m1_st_idx(vint16m1_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e16m1(vl);
	__asm__ __volatile__ (
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_i16m2_st_idx(vint16m2_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e16m2(vl);
	__asm__ __volatile__ (
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_i16m4_st_idx(vint16m4_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e16m4(vl);
	__asm__ __volatile__ (
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_i16m8_st_idx(vint16m8_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e16m8(vl);
	__asm__ __volatile__ (
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_i8mf8_st_idx(vint8mf8_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e8mf8(vl);
	__asm__ __volatile__ (
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_i8mf4_st_idx(vint8mf4_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e8mf4(vl);
	__asm__ __volatile__ (
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_i8mf2_st_idx(vint8mf2_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e8mf2(vl);
	__asm__ __volatile__ (
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_i8m1_st_idx(vint8m1_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e8m1(vl);
	__asm__ __volatile__ (
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_i8m2_st_idx(vint8m2_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e8m2(vl);
	__asm__ __volatile__ (
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_i8m4_st_idx(vint8m4_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e8m4(vl);
	__asm__ __volatile__ (
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_i8m8_st_idx(vint8m8_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e8m8(vl);
	__asm__ __volatile__ (
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_i64m1_st_idx(vint64m1_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e64m1(vl);
	__asm__ __volatile__ (
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_i64m2_st_idx(vint64m2_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e64m2(vl);
	__asm__ __volatile__ (
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_i64m4_st_idx(vint64m4_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e64m4(vl);
	__asm__ __volatile__ (
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_i64m8_st_idx(vint64m8_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e64m8(vl);
	__asm__ __volatile__ (
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_f32mf2_st_idx(vfloat32mf2_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e32mf2(vl);
	__asm__ __volatile__ (
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_f32m1_st_idx(vfloat32m1_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e32m1(vl);
	__asm__ __volatile__ (
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_f32m2_st_idx(vfloat32m2_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e32m2(vl);
	__asm__ __volatile__ (
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_f32m4_st_idx(vfloat32m4_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e32m4(vl);
	__asm__ __volatile__ (
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_f32m8_st_idx(vfloat32m8_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e32m8(vl);
	__asm__ __volatile__ (
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_f16mf4_st_idx(vfloat16mf4_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e16mf4(vl);
	__asm__ __volatile__ (
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_f16mf2_st_idx(vfloat16mf2_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e16mf2(vl);
	__asm__ __volatile__ (
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_f16m1_st_idx(vfloat16m1_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e16m1(vl);
	__asm__ __volatile__ (
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_f16m2_st_idx(vfloat16m2_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e16m2(vl);
	__asm__ __volatile__ (
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_f16m4_st_idx(vfloat16m4_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e16m4(vl);
	__asm__ __volatile__ (
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_f16m8_st_idx(vfloat16m8_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e16m8(vl);
	__asm__ __volatile__ (
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_f64m1_st_idx(vfloat64m1_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e64m1(vl);
	__asm__ __volatile__ (
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_f64m2_st_idx(vfloat64m2_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e64m2(vl);
	__asm__ __volatile__ (
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_f64m4_st_idx(vfloat64m4_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e64m4(vl);
	__asm__ __volatile__ (
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_f64m8_st_idx(vfloat64m8_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e64m8(vl);
	__asm__ __volatile__ (
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_u32mf2_st_idx(vuint32mf2_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e32mf2(vl);
	__asm__ __volatile__ (
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_u32m1_st_idx(vuint32m1_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e32m1(vl);
	__asm__ __volatile__ (
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_u32m2_st_idx(vuint32m2_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e32m2(vl);
	__asm__ __volatile__ (
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_u32m4_st_idx(vuint32m4_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e32m4(vl);
	__asm__ __volatile__ (
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_u32m8_st_idx(vuint32m8_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e32m8(vl);
	__asm__ __volatile__ (
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_u16mf4_st_idx(vuint16mf4_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e16mf4(vl);
	__asm__ __volatile__ (
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_u16mf2_st_idx(vuint16mf2_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e16mf2(vl);
	__asm__ __volatile__ (
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_u16m1_st_idx(vuint16m1_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e16m1(vl);
	__asm__ __volatile__ (
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_u16m2_st_idx(vuint16m2_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e16m2(vl);
	__asm__ __volatile__ (
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_u16m4_st_idx(vuint16m4_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e16m4(vl);
	__asm__ __volatile__ (
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_u16m8_st_idx(vuint16m8_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e16m8(vl);
	__asm__ __volatile__ (
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_u8mf8_st_idx(vuint8mf8_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e8mf8(vl);
	__asm__ __volatile__ (
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_u8mf4_st_idx(vuint8mf4_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e8mf4(vl);
	__asm__ __volatile__ (
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_u8mf2_st_idx(vuint8mf2_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e8mf2(vl);
	__asm__ __volatile__ (
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_u8m1_st_idx(vuint8m1_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e8m1(vl);
	__asm__ __volatile__ (
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_u8m2_st_idx(vuint8m2_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e8m2(vl);
	__asm__ __volatile__ (
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_u8m4_st_idx(vuint8m4_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e8m4(vl);
	__asm__ __volatile__ (
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_u8m8_st_idx(vuint8m8_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e8m8(vl);
	__asm__ __volatile__ (
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_u64m1_st_idx(vuint64m1_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e64m1(vl);
	__asm__ __volatile__ (
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_u64m2_st_idx(vuint64m2_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e64m2(vl);
	__asm__ __volatile__ (
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_u64m4_st_idx(vuint64m4_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e64m4(vl);
	__asm__ __volatile__ (
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_u64m8_st_idx(vuint64m8_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e64m8(vl);
	__asm__ __volatile__ (
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
}
#endif

// Intrinsic function for svstore //
#if defined(__clang__)
static inline void __attribute__ ((always_inline)) 
ace_svstore_i32mf2_m_st_idx(vbool64_t ace_rvv_mask, vint32mf2_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e32mf2(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask)
		: "memory", "v0"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_i32m1_m_st_idx(vbool32_t ace_rvv_mask, vint32m1_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e32m1(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask)
		: "memory", "v0"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_i32m2_m_st_idx(vbool16_t ace_rvv_mask, vint32m2_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e32m2(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask)
		: "memory", "v0"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_i32m4_m_st_idx(vbool8_t ace_rvv_mask, vint32m4_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e32m4(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask)
		: "memory", "v0"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_i32m8_m_st_idx(vbool4_t ace_rvv_mask, vint32m8_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e32m8(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask)
		: "memory", "v0"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_i16mf4_m_st_idx(vbool64_t ace_rvv_mask, vint16mf4_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e16mf4(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask)
		: "memory", "v0"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_i16mf2_m_st_idx(vbool32_t ace_rvv_mask, vint16mf2_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e16mf2(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask)
		: "memory", "v0"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_i16m1_m_st_idx(vbool16_t ace_rvv_mask, vint16m1_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e16m1(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask)
		: "memory", "v0"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_i16m2_m_st_idx(vbool8_t ace_rvv_mask, vint16m2_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e16m2(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask)
		: "memory", "v0"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_i16m4_m_st_idx(vbool4_t ace_rvv_mask, vint16m4_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e16m4(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask)
		: "memory", "v0"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_i16m8_m_st_idx(vbool2_t ace_rvv_mask, vint16m8_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e16m8(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask)
		: "memory", "v0"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_i8mf8_m_st_idx(vbool64_t ace_rvv_mask, vint8mf8_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e8mf8(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask)
		: "memory", "v0"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_i8mf4_m_st_idx(vbool32_t ace_rvv_mask, vint8mf4_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e8mf4(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask)
		: "memory", "v0"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_i8mf2_m_st_idx(vbool16_t ace_rvv_mask, vint8mf2_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e8mf2(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask)
		: "memory", "v0"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_i8m1_m_st_idx(vbool8_t ace_rvv_mask, vint8m1_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e8m1(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask)
		: "memory", "v0"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_i8m2_m_st_idx(vbool4_t ace_rvv_mask, vint8m2_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e8m2(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask)
		: "memory", "v0"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_i8m4_m_st_idx(vbool2_t ace_rvv_mask, vint8m4_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e8m4(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask)
		: "memory", "v0"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_i8m8_m_st_idx(vbool1_t ace_rvv_mask, vint8m8_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e8m8(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask)
		: "memory", "v0"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_i64m1_m_st_idx(vbool64_t ace_rvv_mask, vint64m1_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e64m1(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask)
		: "memory", "v0"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_i64m2_m_st_idx(vbool32_t ace_rvv_mask, vint64m2_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e64m2(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask)
		: "memory", "v0"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_i64m4_m_st_idx(vbool16_t ace_rvv_mask, vint64m4_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e64m4(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask)
		: "memory", "v0"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_i64m8_m_st_idx(vbool8_t ace_rvv_mask, vint64m8_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e64m8(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask)
		: "memory", "v0"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_f32mf2_m_st_idx(vbool64_t ace_rvv_mask, vfloat32mf2_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e32mf2(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask)
		: "memory", "v0"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_f32m1_m_st_idx(vbool32_t ace_rvv_mask, vfloat32m1_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e32m1(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask)
		: "memory", "v0"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_f32m2_m_st_idx(vbool16_t ace_rvv_mask, vfloat32m2_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e32m2(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask)
		: "memory", "v0"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_f32m4_m_st_idx(vbool8_t ace_rvv_mask, vfloat32m4_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e32m4(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask)
		: "memory", "v0"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_f32m8_m_st_idx(vbool4_t ace_rvv_mask, vfloat32m8_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e32m8(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask)
		: "memory", "v0"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_f16mf4_m_st_idx(vbool64_t ace_rvv_mask, vfloat16mf4_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e16mf4(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask)
		: "memory", "v0"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_f16mf2_m_st_idx(vbool32_t ace_rvv_mask, vfloat16mf2_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e16mf2(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask)
		: "memory", "v0"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_f16m1_m_st_idx(vbool16_t ace_rvv_mask, vfloat16m1_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e16m1(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask)
		: "memory", "v0"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_f16m2_m_st_idx(vbool8_t ace_rvv_mask, vfloat16m2_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e16m2(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask)
		: "memory", "v0"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_f16m4_m_st_idx(vbool4_t ace_rvv_mask, vfloat16m4_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e16m4(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask)
		: "memory", "v0"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_f16m8_m_st_idx(vbool2_t ace_rvv_mask, vfloat16m8_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e16m8(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask)
		: "memory", "v0"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_f64m1_m_st_idx(vbool64_t ace_rvv_mask, vfloat64m1_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e64m1(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask)
		: "memory", "v0"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_f64m2_m_st_idx(vbool32_t ace_rvv_mask, vfloat64m2_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e64m2(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask)
		: "memory", "v0"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_f64m4_m_st_idx(vbool16_t ace_rvv_mask, vfloat64m4_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e64m4(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask)
		: "memory", "v0"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_f64m8_m_st_idx(vbool8_t ace_rvv_mask, vfloat64m8_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e64m8(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask)
		: "memory", "v0"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_u32mf2_m_st_idx(vbool64_t ace_rvv_mask, vuint32mf2_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e32mf2(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask)
		: "memory", "v0"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_u32m1_m_st_idx(vbool32_t ace_rvv_mask, vuint32m1_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e32m1(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask)
		: "memory", "v0"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_u32m2_m_st_idx(vbool16_t ace_rvv_mask, vuint32m2_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e32m2(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask)
		: "memory", "v0"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_u32m4_m_st_idx(vbool8_t ace_rvv_mask, vuint32m4_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e32m4(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask)
		: "memory", "v0"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_u32m8_m_st_idx(vbool4_t ace_rvv_mask, vuint32m8_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e32m8(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask)
		: "memory", "v0"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_u16mf4_m_st_idx(vbool64_t ace_rvv_mask, vuint16mf4_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e16mf4(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask)
		: "memory", "v0"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_u16mf2_m_st_idx(vbool32_t ace_rvv_mask, vuint16mf2_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e16mf2(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask)
		: "memory", "v0"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_u16m1_m_st_idx(vbool16_t ace_rvv_mask, vuint16m1_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e16m1(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask)
		: "memory", "v0"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_u16m2_m_st_idx(vbool8_t ace_rvv_mask, vuint16m2_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e16m2(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask)
		: "memory", "v0"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_u16m4_m_st_idx(vbool4_t ace_rvv_mask, vuint16m4_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e16m4(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask)
		: "memory", "v0"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_u16m8_m_st_idx(vbool2_t ace_rvv_mask, vuint16m8_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e16m8(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask)
		: "memory", "v0"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_u8mf8_m_st_idx(vbool64_t ace_rvv_mask, vuint8mf8_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e8mf8(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask)
		: "memory", "v0"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_u8mf4_m_st_idx(vbool32_t ace_rvv_mask, vuint8mf4_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e8mf4(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask)
		: "memory", "v0"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_u8mf2_m_st_idx(vbool16_t ace_rvv_mask, vuint8mf2_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e8mf2(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask)
		: "memory", "v0"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_u8m1_m_st_idx(vbool8_t ace_rvv_mask, vuint8m1_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e8m1(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask)
		: "memory", "v0"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_u8m2_m_st_idx(vbool4_t ace_rvv_mask, vuint8m2_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e8m2(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask)
		: "memory", "v0"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_u8m4_m_st_idx(vbool2_t ace_rvv_mask, vuint8m4_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e8m4(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask)
		: "memory", "v0"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_u8m8_m_st_idx(vbool1_t ace_rvv_mask, vuint8m8_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e8m8(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask)
		: "memory", "v0"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_u64m1_m_st_idx(vbool64_t ace_rvv_mask, vuint64m1_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e64m1(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask)
		: "memory", "v0"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_u64m2_m_st_idx(vbool32_t ace_rvv_mask, vuint64m2_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e64m2(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask)
		: "memory", "v0"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_u64m4_m_st_idx(vbool16_t ace_rvv_mask, vuint64m4_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e64m4(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask)
		: "memory", "v0"
	);
}
static inline void __attribute__ ((always_inline)) 
ace_svstore_u64m8_m_st_idx(vbool8_t ace_rvv_mask, vuint64m8_t data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode, size_t vl){
	vsetvl_e64m8(vl);
	__asm__ __volatile__ (
		"vmv1r.v v0, %[ace_rvv_mask]\n\t"
		"svstore %[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "vr" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode), [ace_rvv_mask] "vm" (ace_rvv_mask)
		: "memory", "v0"
	);
}
#endif

// Intrinsic function for send_msg //
static inline void __attribute__ ((always_inline)) 
ace_send_msg(const unsigned int mailbox, const unsigned int mailqueue, unsigned long long msg){
	__asm__ __volatile__ (
		"send_msg %[mailbox], %[mailqueue], %[msg]"
		: 
		: [mailbox] "i" (mailbox), [mailqueue] "i" (mailqueue), [msg] "r" (msg)
		: "memory"
	);
}

// Intrinsic function for fg_st //
static inline unsigned long long __attribute__ ((always_inline)) 
ace_fg_st(){
	unsigned long long fg_status_RetVar;
	__asm__ __volatile__ (
		"fg_st %[fg_status]"
		: [fg_status] "=&r" (fg_status_RetVar)
		: 
		: "memory"
	);
	return fg_status_RetVar;
}

// Utility functions for addrCtl //
static inline addrCtl_t __attribute__ ((always_inline)) ace_rd_addrCtl (const addrCtl_idx idx) {
	addrCtl_t dout;
	__asm__ __volatile__ (
		"rd64_addrCtl %0, addrCtl_%1\n"
		: "=&r" (dout)
		: "i" (idx)
		: "memory"
	);
	return dout;
}

static inline void __attribute__ ((always_inline)) ace_wr_addrCtl (const addrCtl_idx idx, const addrCtl_t din) {
	__asm__ __volatile__ (
		"wr64_addrCtl %0, addrCtl_%1\n"
		: 
		: "r" (din), "i" (idx)
		: "memory"
	);
}

// Load byte with zero extend to XRF
static inline unsigned long long __attribute__ ((always_inline)) ace_sxload_e8_zx_idx(const addrCtl_idx addrCtl, const unsigned int mode) {
	return ace_sxload_idx(addrCtl, 32, mode);
}

// Load byte with sign extend to XRF
static inline unsigned long long __attribute__ ((always_inline)) ace_sxload_e8_sx_idx(const addrCtl_idx addrCtl, const unsigned int mode) {
	return ace_sxload_idx(addrCtl, 48, mode);
}

// Load halfword with zero extend to XRF
static inline unsigned long long __attribute__ ((always_inline)) ace_sxload_e16_zx_idx(const addrCtl_idx addrCtl, const unsigned int mode) {
	return ace_sxload_idx(addrCtl, 37, mode);
}

// Load halfword with sign extend to XRF
static inline unsigned long long __attribute__ ((always_inline)) ace_sxload_e16_sx_idx(const addrCtl_idx addrCtl, const unsigned int mode) {
	return ace_sxload_idx(addrCtl, 53, mode);
}

// Load word with zero extend to XRF
static inline unsigned long long __attribute__ ((always_inline)) ace_sxload_e32_zx_idx(const addrCtl_idx addrCtl, const unsigned int mode) {
	return ace_sxload_idx(addrCtl, 38, mode);
}

// Load word with sign extend to XRF
static inline unsigned long long __attribute__ ((always_inline)) ace_sxload_e32_sx_idx(const addrCtl_idx addrCtl, const unsigned int mode) {
	return ace_sxload_idx(addrCtl, 54, mode);
}

// Load nibble (4-bit) with zero extend to XRF
static inline unsigned long long __attribute__ ((always_inline)) ace_sxload_e4_zx_idx(const addrCtl_idx addrCtl, const unsigned int mode) {
	return ace_sxload_idx(addrCtl, 40, mode);
}

// Load nibble (4-bit) with sign extend to XRF
static inline unsigned long long __attribute__ ((always_inline)) ace_sxload_e4_sx_idx(const addrCtl_idx addrCtl, const unsigned int mode) {
	return ace_sxload_idx(addrCtl, 56, mode);
}

// Load double word to XRF
static inline unsigned long long __attribute__ ((always_inline)) ace_sxload_e64_idx(const addrCtl_idx addrCtl, const unsigned int mode) {
	return ace_sxload_idx(addrCtl, 39, mode);
}

// Load FP16 to FRF
static inline double __attribute__ ((always_inline)) ace_sfload_f16_idx(const addrCtl_idx addrCtl, const unsigned int mode) {
	return ace_sfload_idx(addrCtl, 33, mode);
}

// Load FP32 to FRF
static inline double __attribute__ ((always_inline)) ace_sfload_f32_idx(const addrCtl_idx addrCtl, const unsigned int mode) {
	return ace_sfload_idx(addrCtl, 34, mode);
}

// Load FP64 to FRF
static inline double __attribute__ ((always_inline)) ace_sfload_f64_idx(const addrCtl_idx addrCtl, const unsigned int mode) {
	return ace_sfload_idx(addrCtl, 35, mode);
}


#if defined(__clang__)
// Streaming Port Wrapper Functions 
static inline vint32mf2_t __attribute__ ((always_inline)) ace_svload_i32mf2_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_i32mf2_st_idx(addrCtl, 38, mode, vl);
}

static inline vint32m1_t __attribute__ ((always_inline)) ace_svload_i32m1_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_i32m1_st_idx(addrCtl, 38, mode, vl);
}

static inline vint32m2_t __attribute__ ((always_inline)) ace_svload_i32m2_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_i32m2_st_idx(addrCtl, 38, mode, vl);
}

static inline vint32m4_t __attribute__ ((always_inline)) ace_svload_i32m4_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_i32m4_st_idx(addrCtl, 38, mode, vl);
}

static inline vint32m8_t __attribute__ ((always_inline)) ace_svload_i32m8_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_i32m8_st_idx(addrCtl, 38, mode, vl);
}

static inline vint16mf4_t __attribute__ ((always_inline)) ace_svload_i16mf4_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_i16mf4_st_idx(addrCtl, 37, mode, vl);
}

static inline vint16mf2_t __attribute__ ((always_inline)) ace_svload_i16mf2_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_i16mf2_st_idx(addrCtl, 37, mode, vl);
}

static inline vint16m1_t __attribute__ ((always_inline)) ace_svload_i16m1_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_i16m1_st_idx(addrCtl, 37, mode, vl);
}

static inline vint16m2_t __attribute__ ((always_inline)) ace_svload_i16m2_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_i16m2_st_idx(addrCtl, 37, mode, vl);
}

static inline vint16m4_t __attribute__ ((always_inline)) ace_svload_i16m4_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_i16m4_st_idx(addrCtl, 37, mode, vl);
}

static inline vint16m8_t __attribute__ ((always_inline)) ace_svload_i16m8_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_i16m8_st_idx(addrCtl, 37, mode, vl);
}

static inline vint8mf8_t __attribute__ ((always_inline)) ace_svload_i8mf8_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_i8mf8_st_idx(addrCtl, 32, mode, vl);
}

static inline vint8mf4_t __attribute__ ((always_inline)) ace_svload_i8mf4_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_i8mf4_st_idx(addrCtl, 32, mode, vl);
}

static inline vint8mf2_t __attribute__ ((always_inline)) ace_svload_i8mf2_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_i8mf2_st_idx(addrCtl, 32, mode, vl);
}

static inline vint8m1_t __attribute__ ((always_inline)) ace_svload_i8m1_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_i8m1_st_idx(addrCtl, 32, mode, vl);
}

static inline vint8m2_t __attribute__ ((always_inline)) ace_svload_i8m2_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_i8m2_st_idx(addrCtl, 32, mode, vl);
}

static inline vint8m4_t __attribute__ ((always_inline)) ace_svload_i8m4_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_i8m4_st_idx(addrCtl, 32, mode, vl);
}

static inline vint8m8_t __attribute__ ((always_inline)) ace_svload_i8m8_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_i8m8_st_idx(addrCtl, 32, mode, vl);
}

static inline vint64m1_t __attribute__ ((always_inline)) ace_svload_i64m1_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_i64m1_st_idx(addrCtl, 39, mode, vl);
}

static inline vint64m2_t __attribute__ ((always_inline)) ace_svload_i64m2_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_i64m2_st_idx(addrCtl, 39, mode, vl);
}

static inline vint64m4_t __attribute__ ((always_inline)) ace_svload_i64m4_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_i64m4_st_idx(addrCtl, 39, mode, vl);
}

static inline vint64m8_t __attribute__ ((always_inline)) ace_svload_i64m8_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_i64m8_st_idx(addrCtl, 39, mode, vl);
}

static inline vfloat32mf2_t __attribute__ ((always_inline)) ace_svload_f32mf2_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_f32mf2_st_idx(addrCtl, 38, mode, vl);
}

static inline vfloat32m1_t __attribute__ ((always_inline)) ace_svload_f32m1_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_f32m1_st_idx(addrCtl, 38, mode, vl);
}

static inline vfloat32m2_t __attribute__ ((always_inline)) ace_svload_f32m2_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_f32m2_st_idx(addrCtl, 38, mode, vl);
}

static inline vfloat32m4_t __attribute__ ((always_inline)) ace_svload_f32m4_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_f32m4_st_idx(addrCtl, 38, mode, vl);
}

static inline vfloat32m8_t __attribute__ ((always_inline)) ace_svload_f32m8_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_f32m8_st_idx(addrCtl, 38, mode, vl);
}

static inline vfloat16mf4_t __attribute__ ((always_inline)) ace_svload_f16mf4_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_f16mf4_st_idx(addrCtl, 37, mode, vl);
}

static inline vfloat16mf2_t __attribute__ ((always_inline)) ace_svload_f16mf2_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_f16mf2_st_idx(addrCtl, 37, mode, vl);
}

static inline vfloat16m1_t __attribute__ ((always_inline)) ace_svload_f16m1_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_f16m1_st_idx(addrCtl, 37, mode, vl);
}

static inline vfloat16m2_t __attribute__ ((always_inline)) ace_svload_f16m2_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_f16m2_st_idx(addrCtl, 37, mode, vl);
}

static inline vfloat16m4_t __attribute__ ((always_inline)) ace_svload_f16m4_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_f16m4_st_idx(addrCtl, 37, mode, vl);
}

static inline vfloat16m8_t __attribute__ ((always_inline)) ace_svload_f16m8_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_f16m8_st_idx(addrCtl, 37, mode, vl);
}

static inline vfloat64m1_t __attribute__ ((always_inline)) ace_svload_f64m1_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_f64m1_st_idx(addrCtl, 39, mode, vl);
}

static inline vfloat64m2_t __attribute__ ((always_inline)) ace_svload_f64m2_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_f64m2_st_idx(addrCtl, 39, mode, vl);
}

static inline vfloat64m4_t __attribute__ ((always_inline)) ace_svload_f64m4_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_f64m4_st_idx(addrCtl, 39, mode, vl);
}

static inline vfloat64m8_t __attribute__ ((always_inline)) ace_svload_f64m8_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_f64m8_st_idx(addrCtl, 39, mode, vl);
}

static inline vuint32mf2_t __attribute__ ((always_inline)) ace_svload_u32mf2_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_u32mf2_st_idx(addrCtl, 38, mode, vl);
}

static inline vuint32m1_t __attribute__ ((always_inline)) ace_svload_u32m1_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_u32m1_st_idx(addrCtl, 38, mode, vl);
}

static inline vuint32m2_t __attribute__ ((always_inline)) ace_svload_u32m2_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_u32m2_st_idx(addrCtl, 38, mode, vl);
}

static inline vuint32m4_t __attribute__ ((always_inline)) ace_svload_u32m4_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_u32m4_st_idx(addrCtl, 38, mode, vl);
}

static inline vuint32m8_t __attribute__ ((always_inline)) ace_svload_u32m8_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_u32m8_st_idx(addrCtl, 38, mode, vl);
}

static inline vuint16mf4_t __attribute__ ((always_inline)) ace_svload_u16mf4_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_u16mf4_st_idx(addrCtl, 37, mode, vl);
}

static inline vuint16mf2_t __attribute__ ((always_inline)) ace_svload_u16mf2_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_u16mf2_st_idx(addrCtl, 37, mode, vl);
}

static inline vuint16m1_t __attribute__ ((always_inline)) ace_svload_u16m1_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_u16m1_st_idx(addrCtl, 37, mode, vl);
}

static inline vuint16m2_t __attribute__ ((always_inline)) ace_svload_u16m2_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_u16m2_st_idx(addrCtl, 37, mode, vl);
}

static inline vuint16m4_t __attribute__ ((always_inline)) ace_svload_u16m4_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_u16m4_st_idx(addrCtl, 37, mode, vl);
}

static inline vuint16m8_t __attribute__ ((always_inline)) ace_svload_u16m8_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_u16m8_st_idx(addrCtl, 37, mode, vl);
}

static inline vuint8mf8_t __attribute__ ((always_inline)) ace_svload_u8mf8_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_u8mf8_st_idx(addrCtl, 32, mode, vl);
}

static inline vuint8mf4_t __attribute__ ((always_inline)) ace_svload_u8mf4_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_u8mf4_st_idx(addrCtl, 32, mode, vl);
}

static inline vuint8mf2_t __attribute__ ((always_inline)) ace_svload_u8mf2_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_u8mf2_st_idx(addrCtl, 32, mode, vl);
}

static inline vuint8m1_t __attribute__ ((always_inline)) ace_svload_u8m1_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_u8m1_st_idx(addrCtl, 32, mode, vl);
}

static inline vuint8m2_t __attribute__ ((always_inline)) ace_svload_u8m2_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_u8m2_st_idx(addrCtl, 32, mode, vl);
}

static inline vuint8m4_t __attribute__ ((always_inline)) ace_svload_u8m4_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_u8m4_st_idx(addrCtl, 32, mode, vl);
}

static inline vuint8m8_t __attribute__ ((always_inline)) ace_svload_u8m8_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_u8m8_st_idx(addrCtl, 32, mode, vl);
}

static inline vuint64m1_t __attribute__ ((always_inline)) ace_svload_u64m1_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_u64m1_st_idx(addrCtl, 39, mode, vl);
}

static inline vuint64m2_t __attribute__ ((always_inline)) ace_svload_u64m2_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_u64m2_st_idx(addrCtl, 39, mode, vl);
}

static inline vuint64m4_t __attribute__ ((always_inline)) ace_svload_u64m4_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_u64m4_st_idx(addrCtl, 39, mode, vl);
}

static inline vuint64m8_t __attribute__ ((always_inline)) ace_svload_u64m8_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_u64m8_st_idx(addrCtl, 39, mode, vl);
}

static inline vint32mf2_t __attribute__ ((always_inline)) ace_svload_i32mf2_m_idx(vbool64_t ace_rvv_mask, vint32mf2_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_i32mf2_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 6, mode, vl);
}

static inline vint32m1_t __attribute__ ((always_inline)) ace_svload_i32m1_m_idx(vbool32_t ace_rvv_mask, vint32m1_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_i32m1_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 6, mode, vl);
}

static inline vint32m2_t __attribute__ ((always_inline)) ace_svload_i32m2_m_idx(vbool16_t ace_rvv_mask, vint32m2_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_i32m2_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 6, mode, vl);
}

static inline vint32m4_t __attribute__ ((always_inline)) ace_svload_i32m4_m_idx(vbool8_t ace_rvv_mask, vint32m4_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_i32m4_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 6, mode, vl);
}

static inline vint32m8_t __attribute__ ((always_inline)) ace_svload_i32m8_m_idx(vbool4_t ace_rvv_mask, vint32m8_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_i32m8_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 6, mode, vl);
}

static inline vint16mf4_t __attribute__ ((always_inline)) ace_svload_i16mf4_m_idx(vbool64_t ace_rvv_mask, vint16mf4_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_i16mf4_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 5, mode, vl);
}

static inline vint16mf2_t __attribute__ ((always_inline)) ace_svload_i16mf2_m_idx(vbool32_t ace_rvv_mask, vint16mf2_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_i16mf2_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 5, mode, vl);
}

static inline vint16m1_t __attribute__ ((always_inline)) ace_svload_i16m1_m_idx(vbool16_t ace_rvv_mask, vint16m1_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_i16m1_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 5, mode, vl);
}

static inline vint16m2_t __attribute__ ((always_inline)) ace_svload_i16m2_m_idx(vbool8_t ace_rvv_mask, vint16m2_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_i16m2_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 5, mode, vl);
}

static inline vint16m4_t __attribute__ ((always_inline)) ace_svload_i16m4_m_idx(vbool4_t ace_rvv_mask, vint16m4_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_i16m4_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 5, mode, vl);
}

static inline vint16m8_t __attribute__ ((always_inline)) ace_svload_i16m8_m_idx(vbool2_t ace_rvv_mask, vint16m8_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_i16m8_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 5, mode, vl);
}

static inline vint8mf8_t __attribute__ ((always_inline)) ace_svload_i8mf8_m_idx(vbool64_t ace_rvv_mask, vint8mf8_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_i8mf8_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 0, mode, vl);
}

static inline vint8mf4_t __attribute__ ((always_inline)) ace_svload_i8mf4_m_idx(vbool32_t ace_rvv_mask, vint8mf4_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_i8mf4_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 0, mode, vl);
}

static inline vint8mf2_t __attribute__ ((always_inline)) ace_svload_i8mf2_m_idx(vbool16_t ace_rvv_mask, vint8mf2_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_i8mf2_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 0, mode, vl);
}

static inline vint8m1_t __attribute__ ((always_inline)) ace_svload_i8m1_m_idx(vbool8_t ace_rvv_mask, vint8m1_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_i8m1_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 0, mode, vl);
}

static inline vint8m2_t __attribute__ ((always_inline)) ace_svload_i8m2_m_idx(vbool4_t ace_rvv_mask, vint8m2_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_i8m2_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 0, mode, vl);
}

static inline vint8m4_t __attribute__ ((always_inline)) ace_svload_i8m4_m_idx(vbool2_t ace_rvv_mask, vint8m4_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_i8m4_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 0, mode, vl);
}

static inline vint8m8_t __attribute__ ((always_inline)) ace_svload_i8m8_m_idx(vbool1_t ace_rvv_mask, vint8m8_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_i8m8_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 0, mode, vl);
}

static inline vint64m1_t __attribute__ ((always_inline)) ace_svload_i64m1_m_idx(vbool64_t ace_rvv_mask, vint64m1_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_i64m1_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 7, mode, vl);
}

static inline vint64m2_t __attribute__ ((always_inline)) ace_svload_i64m2_m_idx(vbool32_t ace_rvv_mask, vint64m2_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_i64m2_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 7, mode, vl);
}

static inline vint64m4_t __attribute__ ((always_inline)) ace_svload_i64m4_m_idx(vbool16_t ace_rvv_mask, vint64m4_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_i64m4_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 7, mode, vl);
}

static inline vint64m8_t __attribute__ ((always_inline)) ace_svload_i64m8_m_idx(vbool8_t ace_rvv_mask, vint64m8_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_i64m8_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 7, mode, vl);
}

static inline vfloat32mf2_t __attribute__ ((always_inline)) ace_svload_f32mf2_m_idx(vbool64_t ace_rvv_mask, vfloat32mf2_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_f32mf2_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 6, mode, vl);
}

static inline vfloat32m1_t __attribute__ ((always_inline)) ace_svload_f32m1_m_idx(vbool32_t ace_rvv_mask, vfloat32m1_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_f32m1_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 6, mode, vl);
}

static inline vfloat32m2_t __attribute__ ((always_inline)) ace_svload_f32m2_m_idx(vbool16_t ace_rvv_mask, vfloat32m2_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_f32m2_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 6, mode, vl);
}

static inline vfloat32m4_t __attribute__ ((always_inline)) ace_svload_f32m4_m_idx(vbool8_t ace_rvv_mask, vfloat32m4_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_f32m4_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 6, mode, vl);
}

static inline vfloat32m8_t __attribute__ ((always_inline)) ace_svload_f32m8_m_idx(vbool4_t ace_rvv_mask, vfloat32m8_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_f32m8_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 6, mode, vl);
}

static inline vfloat16mf4_t __attribute__ ((always_inline)) ace_svload_f16mf4_m_idx(vbool64_t ace_rvv_mask, vfloat16mf4_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_f16mf4_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 5, mode, vl);
}

static inline vfloat16mf2_t __attribute__ ((always_inline)) ace_svload_f16mf2_m_idx(vbool32_t ace_rvv_mask, vfloat16mf2_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_f16mf2_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 5, mode, vl);
}

static inline vfloat16m1_t __attribute__ ((always_inline)) ace_svload_f16m1_m_idx(vbool16_t ace_rvv_mask, vfloat16m1_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_f16m1_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 5, mode, vl);
}

static inline vfloat16m2_t __attribute__ ((always_inline)) ace_svload_f16m2_m_idx(vbool8_t ace_rvv_mask, vfloat16m2_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_f16m2_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 5, mode, vl);
}

static inline vfloat16m4_t __attribute__ ((always_inline)) ace_svload_f16m4_m_idx(vbool4_t ace_rvv_mask, vfloat16m4_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_f16m4_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 5, mode, vl);
}

static inline vfloat16m8_t __attribute__ ((always_inline)) ace_svload_f16m8_m_idx(vbool2_t ace_rvv_mask, vfloat16m8_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_f16m8_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 5, mode, vl);
}

static inline vfloat64m1_t __attribute__ ((always_inline)) ace_svload_f64m1_m_idx(vbool64_t ace_rvv_mask, vfloat64m1_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_f64m1_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 7, mode, vl);
}

static inline vfloat64m2_t __attribute__ ((always_inline)) ace_svload_f64m2_m_idx(vbool32_t ace_rvv_mask, vfloat64m2_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_f64m2_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 7, mode, vl);
}

static inline vfloat64m4_t __attribute__ ((always_inline)) ace_svload_f64m4_m_idx(vbool16_t ace_rvv_mask, vfloat64m4_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_f64m4_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 7, mode, vl);
}

static inline vfloat64m8_t __attribute__ ((always_inline)) ace_svload_f64m8_m_idx(vbool8_t ace_rvv_mask, vfloat64m8_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_f64m8_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 7, mode, vl);
}

static inline vuint32mf2_t __attribute__ ((always_inline)) ace_svload_u32mf2_m_idx(vbool64_t ace_rvv_mask, vuint32mf2_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_u32mf2_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 6, mode, vl);
}

static inline vuint32m1_t __attribute__ ((always_inline)) ace_svload_u32m1_m_idx(vbool32_t ace_rvv_mask, vuint32m1_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_u32m1_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 6, mode, vl);
}

static inline vuint32m2_t __attribute__ ((always_inline)) ace_svload_u32m2_m_idx(vbool16_t ace_rvv_mask, vuint32m2_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_u32m2_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 6, mode, vl);
}

static inline vuint32m4_t __attribute__ ((always_inline)) ace_svload_u32m4_m_idx(vbool8_t ace_rvv_mask, vuint32m4_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_u32m4_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 6, mode, vl);
}

static inline vuint32m8_t __attribute__ ((always_inline)) ace_svload_u32m8_m_idx(vbool4_t ace_rvv_mask, vuint32m8_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_u32m8_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 6, mode, vl);
}

static inline vuint16mf4_t __attribute__ ((always_inline)) ace_svload_u16mf4_m_idx(vbool64_t ace_rvv_mask, vuint16mf4_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_u16mf4_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 5, mode, vl);
}

static inline vuint16mf2_t __attribute__ ((always_inline)) ace_svload_u16mf2_m_idx(vbool32_t ace_rvv_mask, vuint16mf2_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_u16mf2_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 5, mode, vl);
}

static inline vuint16m1_t __attribute__ ((always_inline)) ace_svload_u16m1_m_idx(vbool16_t ace_rvv_mask, vuint16m1_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_u16m1_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 5, mode, vl);
}

static inline vuint16m2_t __attribute__ ((always_inline)) ace_svload_u16m2_m_idx(vbool8_t ace_rvv_mask, vuint16m2_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_u16m2_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 5, mode, vl);
}

static inline vuint16m4_t __attribute__ ((always_inline)) ace_svload_u16m4_m_idx(vbool4_t ace_rvv_mask, vuint16m4_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_u16m4_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 5, mode, vl);
}

static inline vuint16m8_t __attribute__ ((always_inline)) ace_svload_u16m8_m_idx(vbool2_t ace_rvv_mask, vuint16m8_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_u16m8_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 5, mode, vl);
}

static inline vuint8mf8_t __attribute__ ((always_inline)) ace_svload_u8mf8_m_idx(vbool64_t ace_rvv_mask, vuint8mf8_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_u8mf8_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 0, mode, vl);
}

static inline vuint8mf4_t __attribute__ ((always_inline)) ace_svload_u8mf4_m_idx(vbool32_t ace_rvv_mask, vuint8mf4_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_u8mf4_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 0, mode, vl);
}

static inline vuint8mf2_t __attribute__ ((always_inline)) ace_svload_u8mf2_m_idx(vbool16_t ace_rvv_mask, vuint8mf2_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_u8mf2_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 0, mode, vl);
}

static inline vuint8m1_t __attribute__ ((always_inline)) ace_svload_u8m1_m_idx(vbool8_t ace_rvv_mask, vuint8m1_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_u8m1_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 0, mode, vl);
}

static inline vuint8m2_t __attribute__ ((always_inline)) ace_svload_u8m2_m_idx(vbool4_t ace_rvv_mask, vuint8m2_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_u8m2_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 0, mode, vl);
}

static inline vuint8m4_t __attribute__ ((always_inline)) ace_svload_u8m4_m_idx(vbool2_t ace_rvv_mask, vuint8m4_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_u8m4_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 0, mode, vl);
}

static inline vuint8m8_t __attribute__ ((always_inline)) ace_svload_u8m8_m_idx(vbool1_t ace_rvv_mask, vuint8m8_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_u8m8_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 0, mode, vl);
}

static inline vuint64m1_t __attribute__ ((always_inline)) ace_svload_u64m1_m_idx(vbool64_t ace_rvv_mask, vuint64m1_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_u64m1_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 7, mode, vl);
}

static inline vuint64m2_t __attribute__ ((always_inline)) ace_svload_u64m2_m_idx(vbool32_t ace_rvv_mask, vuint64m2_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_u64m2_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 7, mode, vl);
}

static inline vuint64m4_t __attribute__ ((always_inline)) ace_svload_u64m4_m_idx(vbool16_t ace_rvv_mask, vuint64m4_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_u64m4_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 7, mode, vl);
}

static inline vuint64m8_t __attribute__ ((always_inline)) ace_svload_u64m8_m_idx(vbool8_t ace_rvv_mask, vuint64m8_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_u64m8_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 7, mode, vl);
}

static inline vuint8mf8_t __attribute__ ((always_inline)) ace_svload_e4mf8_zx_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_u8mf8_st_idx(addrCtl, 40, mode, vl);
}

static inline vuint8mf4_t __attribute__ ((always_inline)) ace_svload_e4mf4_zx_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_u8mf4_st_idx(addrCtl, 40, mode, vl);
}

static inline vuint8mf2_t __attribute__ ((always_inline)) ace_svload_e4mf2_zx_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_u8mf2_st_idx(addrCtl, 40, mode, vl);
}

static inline vuint8m1_t __attribute__ ((always_inline)) ace_svload_e4m1_zx_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_u8m1_st_idx(addrCtl, 40, mode, vl);
}

static inline vuint8m2_t __attribute__ ((always_inline)) ace_svload_e4m2_zx_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_u8m2_st_idx(addrCtl, 40, mode, vl);
}

static inline vuint8m4_t __attribute__ ((always_inline)) ace_svload_e4m4_zx_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_u8m4_st_idx(addrCtl, 40, mode, vl);
}

static inline vuint8m8_t __attribute__ ((always_inline)) ace_svload_e4m8_zx_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_u8m8_st_idx(addrCtl, 40, mode, vl);
}

static inline vint8mf8_t __attribute__ ((always_inline)) ace_svload_e4mf8_sx_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_i8mf8_st_idx(addrCtl, 56, mode, vl);
}

static inline vint8mf4_t __attribute__ ((always_inline)) ace_svload_e4mf4_sx_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_i8mf4_st_idx(addrCtl, 56, mode, vl);
}

static inline vint8mf2_t __attribute__ ((always_inline)) ace_svload_e4mf2_sx_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_i8mf2_st_idx(addrCtl, 56, mode, vl);
}

static inline vint8m1_t __attribute__ ((always_inline)) ace_svload_e4m1_sx_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_i8m1_st_idx(addrCtl, 56, mode, vl);
}

static inline vint8m2_t __attribute__ ((always_inline)) ace_svload_e4m2_sx_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_i8m2_st_idx(addrCtl, 56, mode, vl);
}

static inline vint8m4_t __attribute__ ((always_inline)) ace_svload_e4m4_sx_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_i8m4_st_idx(addrCtl, 56, mode, vl);
}

static inline vint8m8_t __attribute__ ((always_inline)) ace_svload_e4m8_sx_idx(const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_i8m8_st_idx(addrCtl, 56, mode, vl);
}

static inline vuint8mf8_t __attribute__ ((always_inline)) ace_svload_e4mf8_zx_m_idx(vbool64_t ace_rvv_mask, vuint8mf8_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_u8mf8_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 8, mode, vl);
}

static inline vuint8mf4_t __attribute__ ((always_inline)) ace_svload_e4mf4_zx_m_idx(vbool32_t ace_rvv_mask, vuint8mf4_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_u8mf4_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 8, mode, vl);
}

static inline vuint8mf2_t __attribute__ ((always_inline)) ace_svload_e4mf2_zx_m_idx(vbool16_t ace_rvv_mask, vuint8mf2_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_u8mf2_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 8, mode, vl);
}

static inline vuint8m1_t __attribute__ ((always_inline)) ace_svload_e4m1_zx_m_idx(vbool8_t ace_rvv_mask, vuint8m1_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_u8m1_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 8, mode, vl);
}

static inline vuint8m2_t __attribute__ ((always_inline)) ace_svload_e4m2_zx_m_idx(vbool4_t ace_rvv_mask, vuint8m2_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_u8m2_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 8, mode, vl);
}

static inline vuint8m4_t __attribute__ ((always_inline)) ace_svload_e4m4_zx_m_idx(vbool2_t ace_rvv_mask, vuint8m4_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_u8m4_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 8, mode, vl);
}

static inline vuint8m8_t __attribute__ ((always_inline)) ace_svload_e4m8_zx_m_idx(vbool1_t ace_rvv_mask, vuint8m8_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_u8m8_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 8, mode, vl);
}

static inline vint8mf8_t __attribute__ ((always_inline)) ace_svload_e4mf8_sx_m_idx(vbool64_t ace_rvv_mask, vint8mf8_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_i8mf8_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 24, mode, vl);
}

static inline vint8mf4_t __attribute__ ((always_inline)) ace_svload_e4mf4_sx_m_idx(vbool32_t ace_rvv_mask, vint8mf4_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_i8mf4_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 24, mode, vl);
}

static inline vint8mf2_t __attribute__ ((always_inline)) ace_svload_e4mf2_sx_m_idx(vbool16_t ace_rvv_mask, vint8mf2_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_i8mf2_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 24, mode, vl);
}

static inline vint8m1_t __attribute__ ((always_inline)) ace_svload_e4m1_sx_m_idx(vbool8_t ace_rvv_mask, vint8m1_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_i8m1_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 24, mode, vl);
}

static inline vint8m2_t __attribute__ ((always_inline)) ace_svload_e4m2_sx_m_idx(vbool4_t ace_rvv_mask, vint8m2_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_i8m2_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 24, mode, vl);
}

static inline vint8m4_t __attribute__ ((always_inline)) ace_svload_e4m4_sx_m_idx(vbool2_t ace_rvv_mask, vint8m4_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_i8m4_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 24, mode, vl);
}

static inline vint8m8_t __attribute__ ((always_inline)) ace_svload_e4m8_sx_m_idx(vbool1_t ace_rvv_mask, vint8m8_t ace_rvv_maskoff, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	return ace_svload_i8m8_m_st_idx(ace_rvv_mask, ace_rvv_maskoff, addrCtl, 24, mode, vl);
}

#endif
// Store byte from XRF
static inline void __attribute__ ((always_inline)) ace_sxstore_e8_idx(unsigned long long data, const addrCtl_idx addrCtl, const unsigned int mode) {
	ace_sxstore_idx(data, addrCtl, 32, mode);
}

// Store halfword from XRF
static inline void __attribute__ ((always_inline)) ace_sxstore_e16_idx(unsigned long long data, const addrCtl_idx addrCtl, const unsigned int mode) {
	ace_sxstore_idx(data, addrCtl, 37, mode);
}

// Store word from XRF
static inline void __attribute__ ((always_inline)) ace_sxstore_e32_idx(unsigned long long data, const addrCtl_idx addrCtl, const unsigned int mode) {
	ace_sxstore_idx(data, addrCtl, 38, mode);
}

// Store double word from XRF
static inline void __attribute__ ((always_inline)) ace_sxstore_e64_idx(unsigned long long data, const addrCtl_idx addrCtl, const unsigned int mode) {
	ace_sxstore_idx(data, addrCtl, 39, mode);
}

// Store FP16 from FRF
static inline void __attribute__ ((always_inline)) ace_sfstore_f16_idx(double data, const addrCtl_idx addrCtl, const unsigned int mode) {
	ace_sfstore_idx(data, addrCtl, 33, mode);
}

// Store FP32 from FRF
static inline void __attribute__ ((always_inline)) ace_sfstore_f32_idx(double data, const addrCtl_idx addrCtl, const unsigned int mode) {
	ace_sfstore_idx(data, addrCtl, 34, mode);
}

// Store FP64 from FRF
static inline void __attribute__ ((always_inline)) ace_sfstore_f64_idx(double data, const addrCtl_idx addrCtl, const unsigned int mode) {
	ace_sfstore_idx(data, addrCtl, 35, mode);
}


#if defined(__clang__)
// Streaming Port Wrapper Functions 
static inline void __attribute__ ((always_inline)) ace_svstore_i32mf2_idx(vint32mf2_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_i32mf2_st_idx(data, addrCtl, 38, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_i32m1_idx(vint32m1_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_i32m1_st_idx(data, addrCtl, 38, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_i32m2_idx(vint32m2_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_i32m2_st_idx(data, addrCtl, 38, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_i32m4_idx(vint32m4_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_i32m4_st_idx(data, addrCtl, 38, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_i32m8_idx(vint32m8_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_i32m8_st_idx(data, addrCtl, 38, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_i16mf4_idx(vint16mf4_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_i16mf4_st_idx(data, addrCtl, 37, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_i16mf2_idx(vint16mf2_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_i16mf2_st_idx(data, addrCtl, 37, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_i16m1_idx(vint16m1_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_i16m1_st_idx(data, addrCtl, 37, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_i16m2_idx(vint16m2_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_i16m2_st_idx(data, addrCtl, 37, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_i16m4_idx(vint16m4_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_i16m4_st_idx(data, addrCtl, 37, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_i16m8_idx(vint16m8_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_i16m8_st_idx(data, addrCtl, 37, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_i8mf8_idx(vint8mf8_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_i8mf8_st_idx(data, addrCtl, 32, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_i8mf4_idx(vint8mf4_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_i8mf4_st_idx(data, addrCtl, 32, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_i8mf2_idx(vint8mf2_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_i8mf2_st_idx(data, addrCtl, 32, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_i8m1_idx(vint8m1_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_i8m1_st_idx(data, addrCtl, 32, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_i8m2_idx(vint8m2_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_i8m2_st_idx(data, addrCtl, 32, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_i8m4_idx(vint8m4_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_i8m4_st_idx(data, addrCtl, 32, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_i8m8_idx(vint8m8_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_i8m8_st_idx(data, addrCtl, 32, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_i64m1_idx(vint64m1_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_i64m1_st_idx(data, addrCtl, 39, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_i64m2_idx(vint64m2_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_i64m2_st_idx(data, addrCtl, 39, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_i64m4_idx(vint64m4_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_i64m4_st_idx(data, addrCtl, 39, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_i64m8_idx(vint64m8_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_i64m8_st_idx(data, addrCtl, 39, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_f32mf2_idx(vfloat32mf2_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_f32mf2_st_idx(data, addrCtl, 38, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_f32m1_idx(vfloat32m1_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_f32m1_st_idx(data, addrCtl, 38, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_f32m2_idx(vfloat32m2_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_f32m2_st_idx(data, addrCtl, 38, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_f32m4_idx(vfloat32m4_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_f32m4_st_idx(data, addrCtl, 38, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_f32m8_idx(vfloat32m8_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_f32m8_st_idx(data, addrCtl, 38, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_f16mf4_idx(vfloat16mf4_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_f16mf4_st_idx(data, addrCtl, 37, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_f16mf2_idx(vfloat16mf2_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_f16mf2_st_idx(data, addrCtl, 37, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_f16m1_idx(vfloat16m1_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_f16m1_st_idx(data, addrCtl, 37, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_f16m2_idx(vfloat16m2_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_f16m2_st_idx(data, addrCtl, 37, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_f16m4_idx(vfloat16m4_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_f16m4_st_idx(data, addrCtl, 37, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_f16m8_idx(vfloat16m8_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_f16m8_st_idx(data, addrCtl, 37, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_f64m1_idx(vfloat64m1_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_f64m1_st_idx(data, addrCtl, 39, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_f64m2_idx(vfloat64m2_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_f64m2_st_idx(data, addrCtl, 39, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_f64m4_idx(vfloat64m4_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_f64m4_st_idx(data, addrCtl, 39, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_f64m8_idx(vfloat64m8_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_f64m8_st_idx(data, addrCtl, 39, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_u32mf2_idx(vuint32mf2_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_u32mf2_st_idx(data, addrCtl, 38, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_u32m1_idx(vuint32m1_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_u32m1_st_idx(data, addrCtl, 38, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_u32m2_idx(vuint32m2_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_u32m2_st_idx(data, addrCtl, 38, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_u32m4_idx(vuint32m4_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_u32m4_st_idx(data, addrCtl, 38, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_u32m8_idx(vuint32m8_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_u32m8_st_idx(data, addrCtl, 38, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_u16mf4_idx(vuint16mf4_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_u16mf4_st_idx(data, addrCtl, 37, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_u16mf2_idx(vuint16mf2_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_u16mf2_st_idx(data, addrCtl, 37, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_u16m1_idx(vuint16m1_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_u16m1_st_idx(data, addrCtl, 37, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_u16m2_idx(vuint16m2_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_u16m2_st_idx(data, addrCtl, 37, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_u16m4_idx(vuint16m4_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_u16m4_st_idx(data, addrCtl, 37, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_u16m8_idx(vuint16m8_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_u16m8_st_idx(data, addrCtl, 37, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_u8mf8_idx(vuint8mf8_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_u8mf8_st_idx(data, addrCtl, 32, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_u8mf4_idx(vuint8mf4_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_u8mf4_st_idx(data, addrCtl, 32, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_u8mf2_idx(vuint8mf2_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_u8mf2_st_idx(data, addrCtl, 32, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_u8m1_idx(vuint8m1_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_u8m1_st_idx(data, addrCtl, 32, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_u8m2_idx(vuint8m2_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_u8m2_st_idx(data, addrCtl, 32, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_u8m4_idx(vuint8m4_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_u8m4_st_idx(data, addrCtl, 32, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_u8m8_idx(vuint8m8_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_u8m8_st_idx(data, addrCtl, 32, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_u64m1_idx(vuint64m1_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_u64m1_st_idx(data, addrCtl, 39, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_u64m2_idx(vuint64m2_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_u64m2_st_idx(data, addrCtl, 39, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_u64m4_idx(vuint64m4_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_u64m4_st_idx(data, addrCtl, 39, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_u64m8_idx(vuint64m8_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_u64m8_st_idx(data, addrCtl, 39, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_i32mf2_m_idx(vbool64_t ace_rvv_mask, vint32mf2_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_i32mf2_m_st_idx(ace_rvv_mask, data, addrCtl, 6, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_i32m1_m_idx(vbool32_t ace_rvv_mask, vint32m1_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_i32m1_m_st_idx(ace_rvv_mask, data, addrCtl, 6, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_i32m2_m_idx(vbool16_t ace_rvv_mask, vint32m2_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_i32m2_m_st_idx(ace_rvv_mask, data, addrCtl, 6, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_i32m4_m_idx(vbool8_t ace_rvv_mask, vint32m4_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_i32m4_m_st_idx(ace_rvv_mask, data, addrCtl, 6, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_i32m8_m_idx(vbool4_t ace_rvv_mask, vint32m8_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_i32m8_m_st_idx(ace_rvv_mask, data, addrCtl, 6, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_i16mf4_m_idx(vbool64_t ace_rvv_mask, vint16mf4_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_i16mf4_m_st_idx(ace_rvv_mask, data, addrCtl, 5, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_i16mf2_m_idx(vbool32_t ace_rvv_mask, vint16mf2_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_i16mf2_m_st_idx(ace_rvv_mask, data, addrCtl, 5, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_i16m1_m_idx(vbool16_t ace_rvv_mask, vint16m1_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_i16m1_m_st_idx(ace_rvv_mask, data, addrCtl, 5, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_i16m2_m_idx(vbool8_t ace_rvv_mask, vint16m2_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_i16m2_m_st_idx(ace_rvv_mask, data, addrCtl, 5, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_i16m4_m_idx(vbool4_t ace_rvv_mask, vint16m4_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_i16m4_m_st_idx(ace_rvv_mask, data, addrCtl, 5, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_i16m8_m_idx(vbool2_t ace_rvv_mask, vint16m8_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_i16m8_m_st_idx(ace_rvv_mask, data, addrCtl, 5, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_i8mf8_m_idx(vbool64_t ace_rvv_mask, vint8mf8_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_i8mf8_m_st_idx(ace_rvv_mask, data, addrCtl, 0, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_i8mf4_m_idx(vbool32_t ace_rvv_mask, vint8mf4_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_i8mf4_m_st_idx(ace_rvv_mask, data, addrCtl, 0, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_i8mf2_m_idx(vbool16_t ace_rvv_mask, vint8mf2_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_i8mf2_m_st_idx(ace_rvv_mask, data, addrCtl, 0, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_i8m1_m_idx(vbool8_t ace_rvv_mask, vint8m1_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_i8m1_m_st_idx(ace_rvv_mask, data, addrCtl, 0, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_i8m2_m_idx(vbool4_t ace_rvv_mask, vint8m2_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_i8m2_m_st_idx(ace_rvv_mask, data, addrCtl, 0, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_i8m4_m_idx(vbool2_t ace_rvv_mask, vint8m4_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_i8m4_m_st_idx(ace_rvv_mask, data, addrCtl, 0, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_i8m8_m_idx(vbool1_t ace_rvv_mask, vint8m8_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_i8m8_m_st_idx(ace_rvv_mask, data, addrCtl, 0, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_i64m1_m_idx(vbool64_t ace_rvv_mask, vint64m1_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_i64m1_m_st_idx(ace_rvv_mask, data, addrCtl, 7, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_i64m2_m_idx(vbool32_t ace_rvv_mask, vint64m2_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_i64m2_m_st_idx(ace_rvv_mask, data, addrCtl, 7, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_i64m4_m_idx(vbool16_t ace_rvv_mask, vint64m4_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_i64m4_m_st_idx(ace_rvv_mask, data, addrCtl, 7, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_i64m8_m_idx(vbool8_t ace_rvv_mask, vint64m8_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_i64m8_m_st_idx(ace_rvv_mask, data, addrCtl, 7, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_f32mf2_m_idx(vbool64_t ace_rvv_mask, vfloat32mf2_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_f32mf2_m_st_idx(ace_rvv_mask, data, addrCtl, 6, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_f32m1_m_idx(vbool32_t ace_rvv_mask, vfloat32m1_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_f32m1_m_st_idx(ace_rvv_mask, data, addrCtl, 6, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_f32m2_m_idx(vbool16_t ace_rvv_mask, vfloat32m2_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_f32m2_m_st_idx(ace_rvv_mask, data, addrCtl, 6, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_f32m4_m_idx(vbool8_t ace_rvv_mask, vfloat32m4_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_f32m4_m_st_idx(ace_rvv_mask, data, addrCtl, 6, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_f32m8_m_idx(vbool4_t ace_rvv_mask, vfloat32m8_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_f32m8_m_st_idx(ace_rvv_mask, data, addrCtl, 6, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_f16mf4_m_idx(vbool64_t ace_rvv_mask, vfloat16mf4_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_f16mf4_m_st_idx(ace_rvv_mask, data, addrCtl, 5, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_f16mf2_m_idx(vbool32_t ace_rvv_mask, vfloat16mf2_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_f16mf2_m_st_idx(ace_rvv_mask, data, addrCtl, 5, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_f16m1_m_idx(vbool16_t ace_rvv_mask, vfloat16m1_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_f16m1_m_st_idx(ace_rvv_mask, data, addrCtl, 5, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_f16m2_m_idx(vbool8_t ace_rvv_mask, vfloat16m2_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_f16m2_m_st_idx(ace_rvv_mask, data, addrCtl, 5, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_f16m4_m_idx(vbool4_t ace_rvv_mask, vfloat16m4_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_f16m4_m_st_idx(ace_rvv_mask, data, addrCtl, 5, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_f16m8_m_idx(vbool2_t ace_rvv_mask, vfloat16m8_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_f16m8_m_st_idx(ace_rvv_mask, data, addrCtl, 5, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_f64m1_m_idx(vbool64_t ace_rvv_mask, vfloat64m1_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_f64m1_m_st_idx(ace_rvv_mask, data, addrCtl, 7, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_f64m2_m_idx(vbool32_t ace_rvv_mask, vfloat64m2_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_f64m2_m_st_idx(ace_rvv_mask, data, addrCtl, 7, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_f64m4_m_idx(vbool16_t ace_rvv_mask, vfloat64m4_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_f64m4_m_st_idx(ace_rvv_mask, data, addrCtl, 7, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_f64m8_m_idx(vbool8_t ace_rvv_mask, vfloat64m8_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_f64m8_m_st_idx(ace_rvv_mask, data, addrCtl, 7, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_u32mf2_m_idx(vbool64_t ace_rvv_mask, vuint32mf2_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_u32mf2_m_st_idx(ace_rvv_mask, data, addrCtl, 6, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_u32m1_m_idx(vbool32_t ace_rvv_mask, vuint32m1_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_u32m1_m_st_idx(ace_rvv_mask, data, addrCtl, 6, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_u32m2_m_idx(vbool16_t ace_rvv_mask, vuint32m2_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_u32m2_m_st_idx(ace_rvv_mask, data, addrCtl, 6, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_u32m4_m_idx(vbool8_t ace_rvv_mask, vuint32m4_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_u32m4_m_st_idx(ace_rvv_mask, data, addrCtl, 6, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_u32m8_m_idx(vbool4_t ace_rvv_mask, vuint32m8_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_u32m8_m_st_idx(ace_rvv_mask, data, addrCtl, 6, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_u16mf4_m_idx(vbool64_t ace_rvv_mask, vuint16mf4_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_u16mf4_m_st_idx(ace_rvv_mask, data, addrCtl, 5, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_u16mf2_m_idx(vbool32_t ace_rvv_mask, vuint16mf2_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_u16mf2_m_st_idx(ace_rvv_mask, data, addrCtl, 5, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_u16m1_m_idx(vbool16_t ace_rvv_mask, vuint16m1_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_u16m1_m_st_idx(ace_rvv_mask, data, addrCtl, 5, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_u16m2_m_idx(vbool8_t ace_rvv_mask, vuint16m2_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_u16m2_m_st_idx(ace_rvv_mask, data, addrCtl, 5, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_u16m4_m_idx(vbool4_t ace_rvv_mask, vuint16m4_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_u16m4_m_st_idx(ace_rvv_mask, data, addrCtl, 5, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_u16m8_m_idx(vbool2_t ace_rvv_mask, vuint16m8_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_u16m8_m_st_idx(ace_rvv_mask, data, addrCtl, 5, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_u8mf8_m_idx(vbool64_t ace_rvv_mask, vuint8mf8_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_u8mf8_m_st_idx(ace_rvv_mask, data, addrCtl, 0, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_u8mf4_m_idx(vbool32_t ace_rvv_mask, vuint8mf4_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_u8mf4_m_st_idx(ace_rvv_mask, data, addrCtl, 0, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_u8mf2_m_idx(vbool16_t ace_rvv_mask, vuint8mf2_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_u8mf2_m_st_idx(ace_rvv_mask, data, addrCtl, 0, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_u8m1_m_idx(vbool8_t ace_rvv_mask, vuint8m1_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_u8m1_m_st_idx(ace_rvv_mask, data, addrCtl, 0, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_u8m2_m_idx(vbool4_t ace_rvv_mask, vuint8m2_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_u8m2_m_st_idx(ace_rvv_mask, data, addrCtl, 0, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_u8m4_m_idx(vbool2_t ace_rvv_mask, vuint8m4_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_u8m4_m_st_idx(ace_rvv_mask, data, addrCtl, 0, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_u8m8_m_idx(vbool1_t ace_rvv_mask, vuint8m8_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_u8m8_m_st_idx(ace_rvv_mask, data, addrCtl, 0, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_u64m1_m_idx(vbool64_t ace_rvv_mask, vuint64m1_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_u64m1_m_st_idx(ace_rvv_mask, data, addrCtl, 7, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_u64m2_m_idx(vbool32_t ace_rvv_mask, vuint64m2_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_u64m2_m_st_idx(ace_rvv_mask, data, addrCtl, 7, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_u64m4_m_idx(vbool16_t ace_rvv_mask, vuint64m4_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_u64m4_m_st_idx(ace_rvv_mask, data, addrCtl, 7, mode, vl);
}

static inline void __attribute__ ((always_inline)) ace_svstore_u64m8_m_idx(vbool8_t ace_rvv_mask, vuint64m8_t data, const addrCtl_idx addrCtl, const unsigned int mode, size_t vl) {
	ace_svstore_u64m8_m_st_idx(ace_rvv_mask, data, addrCtl, 7, mode, vl);
}

#endif

// Intrinsic function for svload //
static inline void __attribute__ ((always_inline)) 
ace_svload_idx(const unsigned int data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode){
	__asm__ __volatile__ (
		"svload v%[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "i" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
}

// Intrinsic function for svstore //
static inline void __attribute__ ((always_inline)) 
ace_svstore_idx(const unsigned int data, const addrCtl_idx addrCtl, const unsigned int func, const unsigned int mode){
	__asm__ __volatile__ (
		"svstore v%[data], addrCtl_%[addrCtl], %[func], %[mode]"
		: 
		: [data] "i" (data), [addrCtl] "i" (addrCtl), [func] "i" (func), [mode] "i" (mode)
		: "memory"
	);
}

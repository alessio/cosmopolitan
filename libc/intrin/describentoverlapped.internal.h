#ifndef COSMOPOLITAN_LIBC_INTRIN_DESCRIBENTOVERLAPPED_INTERNAL_H_
#define COSMOPOLITAN_LIBC_INTRIN_DESCRIBENTOVERLAPPED_INTERNAL_H_
#include "libc/mem/alloca.h"
#include "libc/nt/struct/overlapped.h"
#if !(__ASSEMBLER__ + __LINKER__ + 0)
COSMOPOLITAN_C_START_

const char *DescribeNtOverlapped(char[128], const struct NtOverlapped *);
#define DescribeNtOverlapped(x) DescribeNtOverlapped(alloca(128), x)

COSMOPOLITAN_C_END_
#endif /* !(__ASSEMBLER__ + __LINKER__ + 0) */
#endif /* COSMOPOLITAN_LIBC_INTRIN_DESCRIBENTOVERLAPPED_INTERNAL_H_ */

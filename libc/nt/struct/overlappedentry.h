#ifndef COSMOPOLITAN_LIBC_NT_STRUCT_OVERLAPPEDENTRY_H_
#define COSMOPOLITAN_LIBC_NT_STRUCT_OVERLAPPEDENTRY_H_
#include "libc/nt/struct/overlapped.h"
#if !(__ASSEMBLER__ + __LINKER__ + 0)
COSMOPOLITAN_C_START_

struct NtOverlappedEntry {
  uint64_t lpCompletionKey;
  struct NtOverlapped *lpOverlapped;
  uint32_t *Internal;
  uint32_t dwNumberOfBytesTransferred;
};

COSMOPOLITAN_C_END_
#endif /* !(__ASSEMBLER__ + __LINKER__ + 0) */
#endif /* COSMOPOLITAN_LIBC_NT_STRUCT_OVERLAPPEDENTRY_H_ */

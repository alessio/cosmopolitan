#include "libc/nt/codegen.h"
.imp	kernel32,__imp_DuplicateHandle,DuplicateHandle

	.text.windows
        .ftrace1
DuplicateHandle:
        .ftrace2
#ifdef __x86_64__
	push	%rbp
	mov	%rsp,%rbp
	mov	__imp_DuplicateHandle(%rip),%rax
	jmp	__sysv2nt8
#elif defined(__aarch64__)
	mov	x0,#0
	ret
#endif
	.endfn	DuplicateHandle,globl
	.previous

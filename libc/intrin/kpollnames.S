/*-*- mode:unix-assembly; indent-tabs-mode:t; tab-width:8; coding:utf-8     -*-│
│vi: set et ft=asm ts=8 tw=8 fenc=utf-8                                     :vi│
╞══════════════════════════════════════════════════════════════════════════════╡
│ Copyright 2020 Justine Alexandra Roberts Tunney                              │
│                                                                              │
│ Permission to use, copy, modify, and/or distribute this software for         │
│ any purpose with or without fee is hereby granted, provided that the         │
│ above copyright notice and this permission notice appear in all copies.      │
│                                                                              │
│ THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL                │
│ WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED                │
│ WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE             │
│ AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL         │
│ DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR        │
│ PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER               │
│ TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR             │
│ PERFORMANCE OF THIS SOFTWARE.                                                │
╚─────────────────────────────────────────────────────────────────────────────*/
#include "libc/fmt/magnumstrs.internal.h"
#include "libc/macros.internal.h"

	.macro	.e e s
	.long	\e - kPollNames
	.long	.L\@ - kPollNames
	.rodata.str1.1
.L\@:	.string	"\s"
	.previous
	.endm

	.section .rodata,"a",@progbits
	.balign	4
	.underrun
kPollNames:
        .e	POLLNVAL	"POLLNVAL"
	.e	POLLWRNORM	"POLLWRNORM"
	.e	POLLWRBAND	"POLLWRBAND"
	.e	POLLRDNORM	"POLLRDNORM"
	.e	POLLRDHUP	"POLLRDHUP"
	.e	POLLRDBAND	"POLLRDBAND"
	.e	POLLHUP		"POLLHUP"
	.e	POLLERR		"POLLERR"
	.e	POLLPRI		"POLLPRI"
	.e	POLLOUT		"POLLOUT"
	.e	POLLIN		"POLLIN"
	.endobj	kPollNames,globl,hidden
	.overrun

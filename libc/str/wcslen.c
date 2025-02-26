/*-*- mode:c;indent-tabs-mode:nil;c-basic-offset:2;tab-width:8;coding:utf-8 -*-│
│vi: set net ft=c ts=2 sts=2 sw=2 fenc=utf-8                                :vi│
╞══════════════════════════════════════════════════════════════════════════════╡
│ Copyright 2021 Justine Alexandra Roberts Tunney                              │
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
#include "libc/dce.h"
#include "libc/intrin/asan.internal.h"
#include "libc/str/str.h"

typedef wchar_t xmm_t __attribute__((__vector_size__(16), __aligned__(16)));

/**
 * Returns length of NUL-terminated wide string.
 *
 * @param s is non-null NUL-terminated wide string pointer
 * @return number of wide characters (excluding NUL)
 * @asyncsignalsafe
 */
size_t wcslen(const wchar_t *s) {
#if defined(__x86_64__) && !defined(__chibicc__)
  size_t n;
  xmm_t z = {0};
  unsigned m, k = (uintptr_t)s & 15;
  const xmm_t *p = (const xmm_t *)((uintptr_t)s & -16);
  if (IsAsan()) __asan_verify(s, 4);
  m = __builtin_ia32_pmovmskb128(*p == z) >> k << k;
  while (!m) m = __builtin_ia32_pmovmskb128(*++p == z);
  n = (const wchar_t *)p + (__builtin_ctzl(m) >> 2) - s;
  if (IsAsan()) __asan_verify(s, n);
  return n;
#else
  size_t n = 0;
  while (*s++) ++n;
  return n;
#endif
}

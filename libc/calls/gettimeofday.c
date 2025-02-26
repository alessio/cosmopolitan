/*-*- mode:c;indent-tabs-mode:nil;c-basic-offset:2;tab-width:8;coding:utf-8 -*-│
│vi: set net ft=c ts=2 sts=2 sw=2 fenc=utf-8                                :vi│
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
#include "libc/calls/struct/timespec.h"
#include "libc/calls/struct/timeval.h"
#include "libc/sysv/consts/clock.h"
#include "libc/time/struct/timezone.h"

/**
 * Returns system wall time in microseconds, e.g.
 *
 *     int64_t t;
 *     char p[20];
 *     struct tm tm;
 *     struct timeval tv;
 *     gettimeofday(&tv, 0);
 *     t = tv.tv_sec;
 *     gmtime_r(&t, &tm);
 *     iso8601(p, &tm);
 *     printf("%s\n", p);
 *
 * @param tv points to timeval that receives result if non-null
 * @param tz is completely ignored
 * @return 0 on success, or -1 w/ errno
 * @raise EFAULT if `tv` points to invalid memory
 * @see	clock_gettime() for nanosecond precision
 * @see	strftime() for string formatting
 * @asyncsignalsafe
 * @vforksafe
 */
int gettimeofday(struct timeval *tv, struct timezone *tz) {
  if (tv) {
    struct timespec ts;
    if (clock_gettime(CLOCK_REALTIME, &ts) != -1) {
      tv->tv_sec = ts.tv_sec;
      tv->tv_usec = (ts.tv_nsec + 999) / 1000;
      return 0;
    } else {
      return -1;
    }
  } else {
    return 0;
  }
}

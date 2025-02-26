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
#include "libc/calls/struct/sysinfo.h"
#include "libc/calls/syscall_support-nt.internal.h"
#include "libc/nt/accounting.h"
#include "libc/nt/struct/memorystatusex.h"
#include "libc/nt/struct/systeminfo.h"
#include "libc/nt/synchronization.h"
#include "libc/nt/systeminfo.h"

textwindows int sys_sysinfo_nt(struct sysinfo *info) {
  struct NtMemoryStatusEx memstat;
  struct NtSystemInfo sysinfo;
  GetSystemInfo(&sysinfo);
  memstat.dwLength = sizeof(struct NtMemoryStatusEx);
  if (GlobalMemoryStatusEx(&memstat)) {
    info->mem_unit = 1;
    info->totalram = memstat.ullTotalPhys;
    info->freeram = memstat.ullAvailPhys;
    info->procs = sysinfo.dwNumberOfProcessors;
    info->uptime = GetTickCount64() / 1000;
    return 0;
  } else {
    return __winerr();
  }
}

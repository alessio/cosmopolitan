/*-*- mode:c;indent-tabs-mode:nil;c-basic-offset:2;tab-width:8;coding:utf-8 -*-│
│vi: set net ft=c ts=2 sts=2 sw=2 fenc=utf-8                                :vi│
╞══════════════════════════════════════════════════════════════════════════════╡
│ Copyright 2023 Justine Alexandra Roberts Tunney                              │
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
#include "libc/proc/posix_spawn.h"
#include "libc/proc/posix_spawn.internal.h"

/**
 * Specifies process group into which child process is placed.
 *
 * Setting `pgroup` to zero will ensure newly created processes are
 * placed within their own brand new process group.
 *
 * This setter also sets the `POSIX_SPAWN_SETPGROUP` flag.
 *
 * @param attr was initialized by posix_spawnattr_init()
 * @param pgroup is the process group id, or 0 for self
 * @return 0 on success, or errno on error
 */
int posix_spawnattr_setpgroup(posix_spawnattr_t *attr, int pgroup) {
  (*attr)->flags |= POSIX_SPAWN_SETPGROUP;
  (*attr)->pgroup = pgroup;
  return 0;
}

#if 0
/*─────────────────────────────────────────────────────────────────╗
│ To the extent possible under law, Justine Tunney has waived      │
│ all copyright and related or neighboring rights to this file,    │
│ as it is written in the following disclaimers:                   │
│   • http://unlicense.org/                                        │
│   • http://creativecommons.org/publicdomain/zero/1.0/            │
╚─────────────────────────────────────────────────────────────────*/
#endif
#include "libc/calls/struct/sigaction.h"
#include "libc/calls/struct/sigaltstack.h"
#include "libc/calls/struct/siginfo.h"
#include "libc/calls/struct/ucontext.internal.h"
#include "libc/calls/ucontext.h"
#include "libc/intrin/kprintf.h"
#include "libc/limits.h"
#include "libc/mem/gc.internal.h"
#include "libc/mem/mem.h"
#include "libc/runtime/runtime.h"
#include "libc/runtime/sysconf.h"
#include "libc/sysv/consts/sa.h"
#include "libc/sysv/consts/sig.h"
#include "libc/sysv/consts/ss.h"
#include "libc/testlib/testlib.h"
#include "libc/thread/thread.h"

/**
 * stack overflow recovery technique #3
 * rewrite thread cpu state to call pthread_exit
 * this method returns gracefully from signal handlers
 * unfortunately it relies on cpu architecture knowledge
 *
 * @see test/libc/thread/stackoverflow1_test.c
 * @see test/libc/thread/stackoverflow2_test.c
 * @see test/libc/thread/stackoverflow3_test.c
 */

volatile bool smashed_stack;

void Exiter(void *rc) {
  struct sigaltstack ss;
  ASSERT_SYS(0, 0, sigaltstack(0, &ss));
  ASSERT_EQ(0, ss.ss_flags);
  pthread_exit(rc);
}

void CrashHandler(int sig, siginfo_t *si, void *arg) {
  ucontext_t *ctx = arg;
  struct sigaltstack ss;
  ASSERT_SYS(0, 0, sigaltstack(0, &ss));
  ASSERT_EQ(SS_ONSTACK, ss.ss_flags);
  kprintf("kprintf avoids overflowing %G %p\n", si->si_signo, si->si_addr);
  smashed_stack = true;
  ASSERT_TRUE(__is_stack_overflow(si, ctx));
  //
  // the backtrace will look like this
  //
  //   0x000000000042561d: pthread_exit at pthread_exit.c:99
  //   0x0000000000418777: Exiter at stackoverflow2_test.c:40
  //   0x00000000004186d8: CrashHandler at stackoverflow2_test.c:49
  //   0x000000000041872a: StackOverflow at stackoverflow2_test.c:53
  //   0x000000000041872a: StackOverflow at stackoverflow2_test.c:53
  //   0x000000000041872a: StackOverflow at stackoverflow2_test.c:53
  //   ...
  //
  ctx->uc_mcontext.ARG0 = 123;
  ctx->uc_mcontext.PC = (long)Exiter;
  ctx->uc_mcontext.SP += 32768;
  ctx->uc_mcontext.SP &= -16;
  ctx->uc_mcontext.SP -= 8;
}

int StackOverflow(int f(), int n) {
  if (n < INT_MAX) {
    return f(f, n + 1) - 1;
  } else {
    return INT_MAX;
  }
}

int (*pStackOverflow)(int (*)(), int) = StackOverflow;

void *MyPosixThread(void *arg) {
  struct sigaction sa;
  struct sigaltstack ss;
  ss.ss_flags = 0;
  ss.ss_size = sysconf(_SC_MINSIGSTKSZ) + 4096;
  ss.ss_sp = gc(malloc(ss.ss_size));
  ASSERT_SYS(0, 0, sigaltstack(&ss, 0));
  sa.sa_flags = SA_SIGINFO | SA_ONSTACK;  // <-- important
  sigemptyset(&sa.sa_mask);
  sa.sa_sigaction = CrashHandler;
  sigaction(SIGBUS, &sa, 0);
  sigaction(SIGSEGV, &sa, 0);
  exit(pStackOverflow(pStackOverflow, 0));
  return 0;
}

int main(int argc, char *argv[]) {
  void *res;
  pthread_t th;
  struct sigaltstack ss;
  smashed_stack = false;
  pthread_create(&th, 0, MyPosixThread, 0);
  pthread_join(th, &res);
  ASSERT_EQ((void *)123L, res);
  ASSERT_TRUE(smashed_stack);
  ASSERT_SYS(0, 0, sigaltstack(0, &ss));
  ASSERT_EQ(SS_DISABLE, ss.ss_flags);
}

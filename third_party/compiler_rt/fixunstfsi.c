/* clang-format off */
/* ===-- fixunstfsi.c - Implement __fixunstfsi -----------------------------===
 *
 *                     The LLVM Compiler Infrastructure
 *
 * This file is dual licensed under the MIT and the University of Illinois Open
 * Source Licenses. See LICENSE.TXT for details.
 *
 * ===----------------------------------------------------------------------===
 */

__static_yoink("huge_compiler_rt_license");

#define QUAD_PRECISION
#include "third_party/compiler_rt/fp_lib.inc"

#if defined(CRT_HAS_128BIT) && defined(CRT_LDBL_128BIT)
typedef su_int fixuint_t;
#include "third_party/compiler_rt/fp_fixuint_impl.inc"

COMPILER_RT_ABI su_int
__fixunstfsi(fp_t a) {
    return __fixuint(a);
}
#endif

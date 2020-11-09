# 1 "a.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 364 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "a.c" 2
# 1 "/data/data/com.termux/files/usr/include/stdio.h" 1 3 4
/*	$OpenBSD: stdio.h,v 1.35 2006/01/13 18:10:09 miod Exp $	*/
/*	$NetBSD: stdio.h,v 1.18 1996/04/25 18:29:21 jtc Exp $	*/

/*-
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Chris Torek.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)stdio.h	5.17 (Berkeley) 6/3/91
 */





# 1 "/data/data/com.termux/files/usr/include/sys/cdefs.h" 1 3 4
/*	$NetBSD: cdefs.h,v 1.58 2004/12/11 05:59:00 christos Exp $	*/

/*
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Berkeley Software Design, Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)cdefs.h	8.8 (Berkeley) 1/9/95
 */
# 61 "/data/data/com.termux/files/usr/include/sys/cdefs.h" 3 4
/*
 * The __CONCAT macro is used to concatenate parts of symbol names, e.g.
 * with "#define OLD(foo) __CONCAT(old,foo)", OLD(foo) produces oldfoo.
 * The __CONCAT macro is a bit tricky -- make sure you don't put spaces
 * in between its arguments.  __CONCAT can also concatenate double-quoted
 * strings produced by the __STRING macro, but this only works with ANSI C.
 */
# 97 "/data/data/com.termux/files/usr/include/sys/cdefs.h" 3 4
/*
 * GNU C version 2.96 added explicit branch prediction so that
 * the CPU back-end can hint the processor and also so that
 * code blocks can be reordered such that the predicted path
 * sees a more linear flow, thus improving cache behavior, etc.
 *
 * The following two macros provide us with a way to use this
 * compiler feature.  Use __predict_true() if you expect the expression
 * to evaluate to true, and __predict_false() if you expect the
 * expression to evaluate to false.
 *
 * A few notes about usage:
 *
 *	* Generally, __predict_false() error condition checks (unless
 *	  you have some _strong_ reason to do otherwise, in which case
 *	  document it), and/or __predict_true() `no-error' condition
 *	  checks, assuming you want to optimize for the no-error case.
 *
 *	* Other than that, if you don't know the likelihood of a test
 *	  succeeding from empirical or other `hard' evidence, don't
 *	  make predictions.
 *
 *	* These are meant to be used in places that are run `a lot'.
 *	  It is wasteful to make predictions in code that is run
 *	  seldomly (e.g. at subsystem initialization time) as the
 *	  basic block reordering that this affects can often generate
 *	  larger code.
 */
# 147 "/data/data/com.termux/files/usr/include/sys/cdefs.h" 3 4
/*
 * Some BSD source needs these macros.
 * Originally they embedded the rcs versions of each source file
 * in the generated binary. We strip strings during build anyway,.
 */






/*
 * With bionic, you always get all C and POSIX API.
 *
 * If you want BSD and/or GNU extensions, _BSD_SOURCE and/or _GNU_SOURCE are
 * expected to be defined by callers before *any* standard header file is
 * included.
 *
 * In our header files we test against __USE_BSD and __USE_GNU.
 */
# 176 "/data/data/com.termux/files/usr/include/sys/cdefs.h" 3 4
/*
 * _FILE_OFFSET_BITS 64 support.
 * See https://android.googlesource.com/platform/bionic/+/master/docs/32-bit-abi.md
 */
# 192 "/data/data/com.termux/files/usr/include/sys/cdefs.h" 3 4
/*
 * For LP32, `long double` == `double`. Historically many `long double` functions were incorrect
 * on x86, missing on most architectures, and even if they are present and correct, linking to
 * them just bloats your ELF file by adding extra relocations. The __BIONIC_LP32_USE_LONG_DOUBLE
 * macro lets us test the headers both ways (and adds an escape valve).
 *
 * Note that some functions have their __RENAME_LDBL commented out as a sign that although we could
 * use __RENAME_LDBL it would actually cause the function to be introduced later because the
 * `long double` variant appeared before the `double` variant.
 */






/*
 * On all architectures, `struct stat` == `struct stat64`, but LP32 didn't gain the *64 functions
 * until API level 21.
 */






/* glibc compatibility. */






/*
 * When _FORTIFY_SOURCE is defined, automatic bounds checking is
 * added to commonly used libc functions. If a buffer overrun is
 * detected, the program is safely aborted.
 *
 * https://android-developers.googleblog.com/2017/04/fortify-in-android.html
 */
# 247 "/data/data/com.termux/files/usr/include/sys/cdefs.h" 3 4
// As we move some FORTIFY checks to be always on, __bos needs to be
// always available.
# 286 "/data/data/com.termux/files/usr/include/sys/cdefs.h" 3 4
/* Further increase sharing for some inline functions */





/* Intended for use in unevaluated contexts, e.g. diagnose_if conditions. */






/* Intended for use in evaluated contexts. */
# 316 "/data/data/com.termux/files/usr/include/sys/cdefs.h" 3 4
/* Used to tag non-static symbols that are private and never exposed by the shared library. */


/*
 * Used to tag symbols that should be hidden for 64-bit,
 * but visible to preserve binary compatibility for LP32.
 */






/* Used to rename functions so that the compiler emits a call to 'x' rather than the function this was applied to. */
# 347 "/data/data/com.termux/files/usr/include/sys/cdefs.h" 3 4
/*
 * Used when we need to check for overflow when multiplying x and y. This
 * should only be used where __size_mul_overflow can not work, because it makes
 * assumptions that __size_mul_overflow doesn't (x and y are positive, ...),
 * *and* doesn't make use of compiler intrinsics, so it's probably slower than
 * __size_mul_overflow.
 */



# 1 "/data/data/com.termux/files/usr/include/android/versioning.h" 1 3 4
/*
 * Copyright (C) 2016 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
# 357 "/data/data/com.termux/files/usr/include/sys/cdefs.h" 2 3 4
# 1 "/data/data/com.termux/files/usr/include/android/api-level.h" 1 3 4
/*
 * Copyright (C) 2008 The Android Open Source Project
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */



/**
 * @file android/api-level.h
 * @brief Functions and constants for dealing with multiple API levels.
 *
 * See
 * https://android.googlesource.com/platform/bionic/+/master/docs/defines.md.
 */





/**
 * Magic version number for an Android OS build which has not yet turned
 * into an official release, for comparison against `__ANDROID_API__`. See
 * https://android.googlesource.com/platform/bionic/+/master/docs/defines.md.
 */


/* This #ifndef should never be true except when doxygen is generating docs. */

/**
 * `__ANDROID_API__` is the API level being targeted. For the OS,
 * this is `__ANDROID_API_FUTURE__`. For the NDK, this is set by the
 * compiler system based on the API level you claimed to target.
 */




/**
 * `__ANDROID_NDK__` is defined for code that's built by the NDK
 * rather than as part of the OS. "Built by the NDK" is an ambiguous idea,
 * so you might prefer to check `__ANDROID__`, `__BIONIC__`, `__linux__`,
 * or `__NDK_MAJOR__` instead, depending on exactly what you're trying to say.
 *
 * `__ANDROID_NDK__` is intended to capture "this code is being built for
 * Android, but targeting a specific API level". This is true for all code built
 * by the NDK proper, but also for OS code that sets `sdk_version` in its build
 * file. This distinction might matter to you if, for example, your code could
 * be built as part of an app *or* as part of the OS.
 */



/** Names the Gingerbread API level (9), for comparison against `__ANDROID_API__`. */


/** Names the Ice-Cream Sandwich API level (14), for comparison against `__ANDROID_API__`. */


/** Names the Jellybean API level (16), for comparison against `__ANDROID_API__`. */


/** Names the Jellybean MR1 API level (17), for comparison against `__ANDROID_API__`. */


/** Names the Jellybean MR2 API level (18), for comparison against `__ANDROID_API__`. */


/** Names the KitKat API level (19), for comparison against `__ANDROID_API__`. */


/** Names the Lollipop API level (21), for comparison against `__ANDROID_API__`. */


/** Names the Lollipop MR1 API level (22), for comparison against `__ANDROID_API__`. */


/** Names the Marshmallow API level (23), for comparison against `__ANDROID_API__`. */


/** Names the Nougat API level (24), for comparison against `__ANDROID_API__`. */


/** Names the Nougat MR1 API level (25), for comparison against `__ANDROID_API__`. */


/** Names the Oreo API level (26), for comparison against `__ANDROID_API__`. */


/** Names the Oreo MR1 API level (27), for comparison against `__ANDROID_API__`. */


/** Names the Pie API level (28), for comparison against `__ANDROID_API__`. */


/**
 * Names the "Q" API level (29), for comparison against `__ANDROID_API__`.
 * This release was called Android 10 publicly, not to be (but sure to be)
 * confused with API level 10.
 */


/** Names the "R" API level (30), for comparison against `__ANDROID_API__`. */


/**
 * Returns the `targetSdkVersion` of the caller, or `__ANDROID_API_FUTURE__`
 * if there is no known target SDK version (for code not running in the
 * context of an app).
 *
 * The returned values correspond to the named constants in `<android/api-level.h>`,
 * and is equivalent to the AndroidManifest.xml `targetSdkVersion`.
 *
 * See also android_get_device_api_level().
 *
 * Available since API level 24.
 */


int android_get_application_target_sdk_version() __attribute__((annotate("introduced_in=" "24")));





// android_get_device_api_level is a static inline before API level 29.


# 1 "/data/data/com.termux/files/usr/include/bits/get_device_api_level_inlines.h" 1 3 4
/*
 * Copyright (C) 2018 The Android Open Source Project
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
# 37 "/data/data/com.termux/files/usr/include/bits/get_device_api_level_inlines.h" 3 4
// Avoid circular dependencies since this is exposed from <sys/cdefs.h>.
int __system_property_get(const char* __name, char* __value);
int atoi(const char* __s) __attribute__((__pure__));

static __inline int android_get_device_api_level() {
  char value[92] = { 0 };
  if (__system_property_get("ro.build.version.sdk", value) < 1) return -1;
  int api_level = atoi(value);
  return (api_level > 0) ? api_level : -1;
}
# 151 "/data/data/com.termux/files/usr/include/android/api-level.h" 2 3 4
# 358 "/data/data/com.termux/files/usr/include/sys/cdefs.h" 2 3 4

# 1 "/data/data/com.termux/files/usr/include/android/ndk-version.h" 1 3 4



/**
 * Major version of this NDK.
 *
 * For example: 16 for r16.
 */


/**
 * Minor version of this NDK.
 *
 * For example: 0 for r16 and 1 for r16b.
 */


/**
 * Set to 0 if this is a release build, or 1 for beta 1,
 * 2 for beta 2, and so on.
 */


/**
 * Build number for this NDK.
 *
 * For a local development build of the NDK, this is -1.
 */


/**
 * Set to 1 if this is a canary build, 0 if not.
 */
# 360 "/data/data/com.termux/files/usr/include/sys/cdefs.h" 2 3 4
# 42 "/data/data/com.termux/files/usr/include/stdio.h" 2 3 4
# 1 "/data/data/com.termux/files/usr/include/sys/types.h" 1 3 4
/*
 * Copyright (C) 2008 The Android Open Source Project
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */





# 1 "/data/data/com.termux/files/usr/lib/clang/10.0.1/include/stddef.h" 1 3 4
/*===---- stddef.h - Basic type definitions --------------------------------===
 *
 * Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
 * See https://llvm.org/LICENSE.txt for license information.
 * SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
 *
 *===-----------------------------------------------------------------------===
 */
# 17 "/data/data/com.termux/files/usr/lib/clang/10.0.1/include/stddef.h" 3 4
/* Always define miscellaneous pieces when modules are available. */
# 26 "/data/data/com.termux/files/usr/lib/clang/10.0.1/include/stddef.h" 3 4
/* __need_wint_t is intentionally not defined here. */




/* Always define ptrdiff_t when modules are available. */



typedef long int ptrdiff_t;






/* Always define size_t when modules are available. */



typedef long unsigned int size_t;





/* ISO9899:2011 7.20 (C11 Annex K): Define rsize_t if __STDC_WANT_LIB_EXT1__ is
 * enabled. */
# 66 "/data/data/com.termux/files/usr/lib/clang/10.0.1/include/stddef.h" 3 4
/* Always define wchar_t when modules are available. */







typedef unsigned int wchar_t;
# 102 "/data/data/com.termux/files/usr/lib/clang/10.0.1/include/stddef.h" 3 4
# 1 "/data/data/com.termux/files/usr/lib/clang/10.0.1/include/__stddef_max_align_t.h" 1 3 4
/*===---- __stddef_max_align_t.h - Definition of max_align_t for modules ---===
 *
 * Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
 * See https://llvm.org/LICENSE.txt for license information.
 * SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
 *
 *===-----------------------------------------------------------------------===
 */
# 18 "/data/data/com.termux/files/usr/lib/clang/10.0.1/include/__stddef_max_align_t.h" 3 4
// Define 'max_align_t' to match the GCC definition.
typedef struct {
  long long __clang_max_align_nonce1
      __attribute__((__aligned__(__alignof__(long long))));
  long double __clang_max_align_nonce2
      __attribute__((__aligned__(__alignof__(long double))));
} max_align_t;
# 103 "/data/data/com.termux/files/usr/lib/clang/10.0.1/include/stddef.h" 2 3 4





/* Some C libraries expect to see a wint_t here. Others (notably MinGW) will use
__WINT_TYPE__ directly; accommodate both by requiring __need_wint_t */
# 33 "/data/data/com.termux/files/usr/include/sys/types.h" 2 3 4
# 1 "/data/data/com.termux/files/usr/lib/clang/10.0.1/include/stdint.h" 1 3 4
/*===---- stdint.h - Standard header for sized integer types --------------===*\
 *
 * Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
 * See https://llvm.org/LICENSE.txt for license information.
 * SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
 *
\*===----------------------------------------------------------------------===*/


// AIX system headers need stdint.h to be re-enterable while _STD_TYPES_T
// is defined until an inclusion of it without _STD_TYPES_T occurs, in which
// case the header guard macro is defined.




/* If we're hosted, fall back to the system's stdint.h, which might have
 * additional definitions.
 */


// C99 7.18.3 Limits of other integer types
//
//  Footnote 219, 220: C++ implementations should define these macros only when
//  __STDC_LIMIT_MACROS is defined before <stdint.h> is included.
//
//  Footnote 222: C++ implementations should define these macros only when
//  __STDC_CONSTANT_MACROS is defined before <stdint.h> is included.
//
// C++11 [cstdint.syn]p2:
//
//  The macros defined by <cstdint> are provided unconditionally. In particular,
//  the symbols __STDC_LIMIT_MACROS and __STDC_CONSTANT_MACROS (mentioned in
//  footnotes 219, 220, and 222 in the C standard) play no role in C++.
//
// C11 removed the problematic footnotes.
//
// Work around this inconsistency by always defining those macros in C++ mode,
// so that a C library implementation which follows the C99 standard can be
// used in C++.
# 52 "/data/data/com.termux/files/usr/lib/clang/10.0.1/include/stdint.h" 3 4
# 1 "/data/data/com.termux/files/usr/include/stdint.h" 1 3 4
/*
 * Copyright (C) 2008 The Android Open Source Project
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */





# 1 "/data/data/com.termux/files/usr/include/bits/wchar_limits.h" 1 3 4
/*
 * Copyright (C) 2014 The Android Open Source Project
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */



/**
 * @file bits/wchar_limits.h
 * @brief `wchar_t` limits.
 */



/** The maximum value of a `wchar_t`. */


/* As of 3.4, clang still doesn't define __WCHAR_MIN__. */

/** The minimum value of a `wchar_t`. */
# 33 "/data/data/com.termux/files/usr/include/stdint.h" 2 3 4
# 1 "/data/data/com.termux/files/usr/lib/clang/10.0.1/include/stddef.h" 1 3 4
/*===---- stddef.h - Basic type definitions --------------------------------===
 *
 * Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
 * See https://llvm.org/LICENSE.txt for license information.
 * SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
 *
 *===-----------------------------------------------------------------------===
 */
# 34 "/data/data/com.termux/files/usr/include/stdint.h" 2 3 4


typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef short __int16_t;
typedef unsigned short __uint16_t;
typedef int __int32_t;
typedef unsigned int __uint32_t;

typedef long __int64_t;
typedef unsigned long __uint64_t;






typedef long __intptr_t;
typedef unsigned long __uintptr_t;





typedef __int8_t int8_t;
typedef __uint8_t uint8_t;

typedef __int16_t int16_t;
typedef __uint16_t uint16_t;

typedef __int32_t int32_t;
typedef __uint32_t uint32_t;

typedef __int64_t int64_t;
typedef __uint64_t uint64_t;

typedef __intptr_t intptr_t;
typedef __uintptr_t uintptr_t;

typedef int8_t int_least8_t;
typedef uint8_t uint_least8_t;

typedef int16_t int_least16_t;
typedef uint16_t uint_least16_t;

typedef int32_t int_least32_t;
typedef uint32_t uint_least32_t;

typedef int64_t int_least64_t;
typedef uint64_t uint_least64_t;

typedef int8_t int_fast8_t;
typedef uint8_t uint_fast8_t;

typedef int64_t int_fast64_t;
typedef uint64_t uint_fast64_t;


typedef int64_t int_fast16_t;
typedef uint64_t uint_fast16_t;
typedef int64_t int_fast32_t;
typedef uint64_t uint_fast32_t;







typedef uint64_t uintmax_t;
typedef int64_t intmax_t;

/* Keep the kernel from trying to define these types... */
# 53 "/data/data/com.termux/files/usr/lib/clang/10.0.1/include/stdint.h" 2 3 4
# 34 "/data/data/com.termux/files/usr/include/sys/types.h" 2 3 4


# 1 "/data/data/com.termux/files/usr/include/linux/types.h" 1 3 4
/****************************************************************************
 ****************************************************************************
 ***
 ***   This header was automatically generated from a Linux kernel header
 ***   of the same name, to make information necessary for userspace to
 ***   call into the kernel available to libc.  It contains only constants,
 ***   structures, and macros generated from the original header, and thus,
 ***   contains no copyrightable information.
 ***
 ***   To edit the content of this header, modify the corresponding
 ***   source file (e.g. under external/kernel-headers/original/) then
 ***   run bionic/libc/kernel/tools/update_all.py
 ***
 ***   Any manual change here will be lost the next time this script will
 ***   be run. You've been warned!
 ***
 ****************************************************************************
 ****************************************************************************/



# 1 "/data/data/com.termux/files/usr/include/aarch64-linux-android/asm/types.h" 1 3 4
/****************************************************************************
 ****************************************************************************
 ***
 ***   This header was automatically generated from a Linux kernel header
 ***   of the same name, to make information necessary for userspace to
 ***   call into the kernel available to libc.  It contains only constants,
 ***   structures, and macros generated from the original header, and thus,
 ***   contains no copyrightable information.
 ***
 ***   To edit the content of this header, modify the corresponding
 ***   source file (e.g. under external/kernel-headers/original/) then
 ***   run bionic/libc/kernel/tools/update_all.py
 ***
 ***   Any manual change here will be lost the next time this script will
 ***   be run. You've been warned!
 ***
 ****************************************************************************
 ****************************************************************************/

# 1 "/data/data/com.termux/files/usr/include/asm-generic/types.h" 1 3 4
/****************************************************************************
 ****************************************************************************
 ***
 ***   This header was automatically generated from a Linux kernel header
 ***   of the same name, to make information necessary for userspace to
 ***   call into the kernel available to libc.  It contains only constants,
 ***   structures, and macros generated from the original header, and thus,
 ***   contains no copyrightable information.
 ***
 ***   To edit the content of this header, modify the corresponding
 ***   source file (e.g. under external/kernel-headers/original/) then
 ***   run bionic/libc/kernel/tools/update_all.py
 ***
 ***   Any manual change here will be lost the next time this script will
 ***   be run. You've been warned!
 ***
 ****************************************************************************
 ****************************************************************************/



# 1 "/data/data/com.termux/files/usr/include/asm-generic/int-ll64.h" 1 3 4
/****************************************************************************
 ****************************************************************************
 ***
 ***   This header was automatically generated from a Linux kernel header
 ***   of the same name, to make information necessary for userspace to
 ***   call into the kernel available to libc.  It contains only constants,
 ***   structures, and macros generated from the original header, and thus,
 ***   contains no copyrightable information.
 ***
 ***   To edit the content of this header, modify the corresponding
 ***   source file (e.g. under external/kernel-headers/original/) then
 ***   run bionic/libc/kernel/tools/update_all.py
 ***
 ***   Any manual change here will be lost the next time this script will
 ***   be run. You've been warned!
 ***
 ****************************************************************************
 ****************************************************************************/



# 1 "/data/data/com.termux/files/usr/include/aarch64-linux-android/asm/bitsperlong.h" 1 3 4
/****************************************************************************
 ****************************************************************************
 ***
 ***   This header was automatically generated from a Linux kernel header
 ***   of the same name, to make information necessary for userspace to
 ***   call into the kernel available to libc.  It contains only constants,
 ***   structures, and macros generated from the original header, and thus,
 ***   contains no copyrightable information.
 ***
 ***   To edit the content of this header, modify the corresponding
 ***   source file (e.g. under external/kernel-headers/original/) then
 ***   run bionic/libc/kernel/tools/update_all.py
 ***
 ***   Any manual change here will be lost the next time this script will
 ***   be run. You've been warned!
 ***
 ****************************************************************************
 ****************************************************************************/




# 1 "/data/data/com.termux/files/usr/include/asm-generic/bitsperlong.h" 1 3 4
/****************************************************************************
 ****************************************************************************
 ***
 ***   This header was automatically generated from a Linux kernel header
 ***   of the same name, to make information necessary for userspace to
 ***   call into the kernel available to libc.  It contains only constants,
 ***   structures, and macros generated from the original header, and thus,
 ***   contains no copyrightable information.
 ***
 ***   To edit the content of this header, modify the corresponding
 ***   source file (e.g. under external/kernel-headers/original/) then
 ***   run bionic/libc/kernel/tools/update_all.py
 ***
 ***   Any manual change here will be lost the next time this script will
 ***   be run. You've been warned!
 ***
 ****************************************************************************
 ****************************************************************************/
# 23 "/data/data/com.termux/files/usr/include/aarch64-linux-android/asm/bitsperlong.h" 2 3 4
# 22 "/data/data/com.termux/files/usr/include/asm-generic/int-ll64.h" 2 3 4

typedef __signed__ char __s8;
typedef unsigned char __u8;
typedef __signed__ short __s16;
typedef unsigned short __u16;
typedef __signed__ int __s32;
typedef unsigned int __u32;

__extension__ typedef __signed__ long long __s64;
__extension__ typedef unsigned long long __u64;
# 22 "/data/data/com.termux/files/usr/include/asm-generic/types.h" 2 3 4
# 20 "/data/data/com.termux/files/usr/include/aarch64-linux-android/asm/types.h" 2 3 4
# 22 "/data/data/com.termux/files/usr/include/linux/types.h" 2 3 4

# 1 "/data/data/com.termux/files/usr/include/linux/posix_types.h" 1 3 4
/****************************************************************************
 ****************************************************************************
 ***
 ***   This header was automatically generated from a Linux kernel header
 ***   of the same name, to make information necessary for userspace to
 ***   call into the kernel available to libc.  It contains only constants,
 ***   structures, and macros generated from the original header, and thus,
 ***   contains no copyrightable information.
 ***
 ***   To edit the content of this header, modify the corresponding
 ***   source file (e.g. under external/kernel-headers/original/) then
 ***   run bionic/libc/kernel/tools/update_all.py
 ***
 ***   Any manual change here will be lost the next time this script will
 ***   be run. You've been warned!
 ***
 ****************************************************************************
 ****************************************************************************/



# 1 "/data/data/com.termux/files/usr/include/linux/stddef.h" 1 3 4
/****************************************************************************
 ****************************************************************************
 ***
 ***   This header was automatically generated from a Linux kernel header
 ***   of the same name, to make information necessary for userspace to
 ***   call into the kernel available to libc.  It contains only constants,
 ***   structures, and macros generated from the original header, and thus,
 ***   contains no copyrightable information.
 ***
 ***   To edit the content of this header, modify the corresponding
 ***   source file (e.g. under external/kernel-headers/original/) then
 ***   run bionic/libc/kernel/tools/update_all.py
 ***
 ***   Any manual change here will be lost the next time this script will
 ***   be run. You've been warned!
 ***
 ****************************************************************************
 ****************************************************************************/

# 1 "/data/data/com.termux/files/usr/include/linux/compiler_types.h" 1 3 4
/*
 * The compiler.h file has been split into compiler.h and compiler_types.h.
 * However, to compile bionic we only need the compiler.h.
 */

# 1 "/data/data/com.termux/files/usr/include/linux/compiler.h" 1 3 4



/*
 * This file is not currently in the Linux kernel tree.
 * Upstream uapi headers refer to <linux/compiler.h> but there is
 * no such uapi file. We've sent this upstream, and are optimistically
 * adding it to bionic in the meantime. This should be replaced by
 * a scrubbed header from external/kernel-headers when possible.
 *
 * An alternative to this file is to check in a symbolic link to the
 * non-uapi <linux/compiler.h>. That's fine for building bionic too.
 */
# 6 "/data/data/com.termux/files/usr/include/linux/compiler_types.h" 2 3 4
# 20 "/data/data/com.termux/files/usr/include/linux/stddef.h" 2 3 4
# 22 "/data/data/com.termux/files/usr/include/linux/posix_types.h" 2 3 4


typedef struct {
  unsigned long fds_bits[1024 / (8 * sizeof(long))];
} __kernel_fd_set;
typedef void(* __kernel_sighandler_t) (int);
typedef int __kernel_key_t;
typedef int __kernel_mqd_t;

# 1 "/data/data/com.termux/files/usr/include/aarch64-linux-android/asm/posix_types.h" 1 3 4
/****************************************************************************
 ****************************************************************************
 ***
 ***   This header was automatically generated from a Linux kernel header
 ***   of the same name, to make information necessary for userspace to
 ***   call into the kernel available to libc.  It contains only constants,
 ***   structures, and macros generated from the original header, and thus,
 ***   contains no copyrightable information.
 ***
 ***   To edit the content of this header, modify the corresponding
 ***   source file (e.g. under external/kernel-headers/original/) then
 ***   run bionic/libc/kernel/tools/update_all.py
 ***
 ***   Any manual change here will be lost the next time this script will
 ***   be run. You've been warned!
 ***
 ****************************************************************************
 ****************************************************************************/


typedef unsigned short __kernel_old_uid_t;
typedef unsigned short __kernel_old_gid_t;


# 1 "/data/data/com.termux/files/usr/include/asm-generic/posix_types.h" 1 3 4
/****************************************************************************
 ****************************************************************************
 ***
 ***   This header was automatically generated from a Linux kernel header
 ***   of the same name, to make information necessary for userspace to
 ***   call into the kernel available to libc.  It contains only constants,
 ***   structures, and macros generated from the original header, and thus,
 ***   contains no copyrightable information.
 ***
 ***   To edit the content of this header, modify the corresponding
 ***   source file (e.g. under external/kernel-headers/original/) then
 ***   run bionic/libc/kernel/tools/update_all.py
 ***
 ***   Any manual change here will be lost the next time this script will
 ***   be run. You've been warned!
 ***
 ****************************************************************************
 ****************************************************************************/




typedef long __kernel_long_t;
typedef unsigned long __kernel_ulong_t;


typedef __kernel_ulong_t __kernel_ino_t;


typedef unsigned int __kernel_mode_t;


typedef int __kernel_pid_t;


typedef int __kernel_ipc_pid_t;


typedef unsigned int __kernel_uid_t;
typedef unsigned int __kernel_gid_t;


typedef __kernel_long_t __kernel_suseconds_t;


typedef int __kernel_daddr_t;


typedef unsigned int __kernel_uid32_t;
typedef unsigned int __kernel_gid32_t;






typedef unsigned int __kernel_old_dev_t;







typedef __kernel_ulong_t __kernel_size_t;
typedef __kernel_long_t __kernel_ssize_t;
typedef __kernel_long_t __kernel_ptrdiff_t;



typedef struct {
  int val[2];
} __kernel_fsid_t;

typedef __kernel_long_t __kernel_off_t;
typedef long long __kernel_loff_t;
typedef __kernel_long_t __kernel_time_t;
typedef long long __kernel_time64_t;
typedef __kernel_long_t __kernel_clock_t;
typedef int __kernel_timer_t;
typedef int __kernel_clockid_t;
typedef char * __kernel_caddr_t;
typedef unsigned short __kernel_uid16_t;
typedef unsigned short __kernel_gid16_t;
# 25 "/data/data/com.termux/files/usr/include/aarch64-linux-android/asm/posix_types.h" 2 3 4
# 31 "/data/data/com.termux/files/usr/include/linux/posix_types.h" 2 3 4
# 24 "/data/data/com.termux/files/usr/include/linux/types.h" 2 3 4


typedef __u16 __le16;
typedef __u16 __be16;
typedef __u32 __le32;
typedef __u32 __be32;
typedef __u64 __le64;
typedef __u64 __be64;
typedef __u16 __sum16;
typedef __u32 __wsum;



typedef unsigned __poll_t;
# 37 "/data/data/com.termux/files/usr/include/sys/types.h" 2 3 4


# 1 "/data/data/com.termux/files/usr/include/bits/pthread_types.h" 1 3 4
/*
 * Copyright (C) 2008 The Android Open Source Project
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */






# 1 "/data/data/com.termux/files/usr/include/sys/types.h" 1 3 4
/*
 * Copyright (C) 2008 The Android Open Source Project
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
# 34 "/data/data/com.termux/files/usr/include/bits/pthread_types.h" 2 3 4

typedef struct {
  uint32_t flags;
  void* stack_base;
  size_t stack_size;
  size_t guard_size;
  int32_t sched_policy;
  int32_t sched_priority;

  char __reserved[16];

} pthread_attr_t;


typedef struct {

  int64_t __private[4];



} pthread_barrier_t;



typedef int pthread_barrierattr_t;


typedef struct {

  int32_t __private[12];



} pthread_cond_t;

typedef long pthread_condattr_t;

typedef int pthread_key_t;

typedef struct {

  int32_t __private[10];



} pthread_mutex_t;

typedef long pthread_mutexattr_t;

typedef int pthread_once_t;

typedef struct {

  int32_t __private[14];



} pthread_rwlock_t;

typedef long pthread_rwlockattr_t;


typedef struct {

  int64_t __private;



} pthread_spinlock_t;


typedef long pthread_t;
# 40 "/data/data/com.termux/files/usr/include/sys/types.h" 2 3 4

/* gids, uids, and pids are all 32-bit. */
typedef __kernel_gid32_t __gid_t;
typedef __gid_t gid_t;
typedef __kernel_uid32_t __uid_t;
typedef __uid_t uid_t;
typedef __kernel_pid_t __pid_t;
typedef __pid_t pid_t;
typedef uint32_t __id_t;
typedef __id_t id_t;

typedef unsigned long blkcnt_t;
typedef unsigned long blksize_t;
typedef __kernel_caddr_t caddr_t;
typedef __kernel_clock_t clock_t;

typedef __kernel_clockid_t __clockid_t;
typedef __clockid_t clockid_t;

typedef __kernel_daddr_t daddr_t;
typedef unsigned long fsblkcnt_t;
typedef unsigned long fsfilcnt_t;

typedef __kernel_mode_t __mode_t;
typedef __mode_t mode_t;

typedef __kernel_key_t __key_t;
typedef __key_t key_t;

typedef __kernel_ino_t __ino_t;
typedef __ino_t ino_t;

typedef uint64_t ino64_t;

typedef uint32_t __nlink_t;
typedef __nlink_t nlink_t;

typedef void* __timer_t;
typedef __timer_t timer_t;

typedef __kernel_suseconds_t __suseconds_t;
typedef __suseconds_t suseconds_t;

/* useconds_t is 32-bit on both LP32 and LP64. */
typedef uint32_t __useconds_t;
typedef __useconds_t useconds_t;





typedef uint64_t dev_t;


/* This historical accident means that we had a 32-bit time_t on 32-bit architectures. */
typedef __kernel_time_t __time_t;
typedef __time_t time_t;

/* This historical accident means that we had a 32-bit off_t on 32-bit architectures. */
/* See https://android.googlesource.com/platform/bionic/+/master/docs/32-bit-abi.md */

typedef int64_t off_t;
typedef off_t loff_t;
typedef loff_t off64_t;
# 114 "/data/data/com.termux/files/usr/include/sys/types.h" 3 4
/* LP64 still has a 32-bit socklen_t. */
typedef uint32_t __socklen_t;

typedef __socklen_t socklen_t;

typedef __builtin_va_list __va_list;



/* Traditionally, bionic's ssize_t was "long int". This caused GCC to emit warnings when you
 * pass a ssize_t to a printf-style function. The correct type is __kernel_ssize_t, which is
 * "int", which isn't an ABI change for C code (because they're the same size) but is an ABI
 * change for C++ because "int" and "long int" mangle to "i" and "l" respectively. So until
 * we can fix the ABI, this change should not be propagated to the NDK. http://b/8253769. */
typedef __kernel_ssize_t ssize_t;


typedef unsigned int uint_t;
typedef unsigned int uint;


typedef unsigned char u_char;
typedef unsigned short u_short;
typedef unsigned int u_int;
typedef unsigned long u_long;

typedef uint32_t u_int32_t;
typedef uint16_t u_int16_t;
typedef uint8_t u_int8_t;
typedef uint64_t u_int64_t;
# 43 "/data/data/com.termux/files/usr/include/stdio.h" 2 3 4

# 1 "/data/data/com.termux/files/usr/lib/clang/10.0.1/include/stdarg.h" 1 3 4
/*===---- stdarg.h - Variable argument handling ----------------------------===
 *
 * Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
 * See https://llvm.org/LICENSE.txt for license information.
 * SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
 *
 *===-----------------------------------------------------------------------===
 */





typedef __builtin_va_list va_list;






/* GCC always defines __va_copy, but does not define va_copy unless in c99 mode
 * or -ansi is not specified, since it was not part of C90.
 */
# 32 "/data/data/com.termux/files/usr/lib/clang/10.0.1/include/stdarg.h" 3 4
typedef __builtin_va_list __gnuc_va_list;
# 45 "/data/data/com.termux/files/usr/include/stdio.h" 2 3 4
# 1 "/data/data/com.termux/files/usr/lib/clang/10.0.1/include/stddef.h" 1 3 4
/*===---- stddef.h - Basic type definitions --------------------------------===
 *
 * Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
 * See https://llvm.org/LICENSE.txt for license information.
 * SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
 *
 *===-----------------------------------------------------------------------===
 */
# 46 "/data/data/com.termux/files/usr/include/stdio.h" 2 3 4

# 1 "/data/data/com.termux/files/usr/include/string.h" 1 3 4
/*
 * Copyright (C) 2008 The Android Open Source Project
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */






# 1 "/data/data/com.termux/files/usr/lib/clang/10.0.1/include/stddef.h" 1 3 4
/*===---- stddef.h - Basic type definitions --------------------------------===
 *
 * Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
 * See https://llvm.org/LICENSE.txt for license information.
 * SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
 *
 *===-----------------------------------------------------------------------===
 */
# 34 "/data/data/com.termux/files/usr/include/string.h" 2 3 4
# 1 "/data/data/com.termux/files/usr/include/xlocale.h" 1 3 4
/*
 * Copyright (C) 2014 The Android Open Source Project
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */



/**
 * @file xlocale.h
 * @brief `locale_t` definition.
 *
 * Most users will want `<locale.h>` instead. `<xlocale.h>` is used by the C
 * library itself to export the `locale_t` type without exporting the
 * `<locale.h>` functions in other headers that export locale-sensitive
 * functions (such as `<string.h>`).
 */



/* If we just use void* in the typedef, the compiler exposes that in error messages. */
struct __locale_t;

/**
 * The `locale_t` type that represents a locale.
 */
typedef struct __locale_t* locale_t;
# 35 "/data/data/com.termux/files/usr/include/string.h" 2 3 4

# 1 "/data/data/com.termux/files/usr/include/bits/strcasecmp.h" 1 3 4
/*
 * Copyright (C) 2016 The Android Open Source Project
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */



/**
 * @file bits/strcasecmp.h
 * @brief Case-insensitive string comparison.
 */







/**
 * [strcasecmp(3)](http://man7.org/linux/man-pages/man3/strcasecmp.3.html) compares two strings
 * ignoring case.
 *
 * Returns an integer less than, equal to, or greater than zero if the first string is less than,
 * equal to, or greater than the second string (ignoring case).
 */
int strcasecmp(const char* __s1, const char* __s2) __attribute__((__pure__));

/**
 * Like strcasecmp() but taking a `locale_t`.
 */


int strcasecmp_l(const char* __s1, const char* __s2, locale_t __l) __attribute__((__pure__)) __attribute__((annotate("introduced_in=" "23")));



/**
 * [strncasecmp(3)](http://man7.org/linux/man-pages/man3/strncasecmp.3.html) compares the first
 * `n` bytes of two strings ignoring case.
 *
 * Returns an integer less than, equal to, or greater than zero if the first `n` bytes of the
 * first string is less than, equal to, or greater than the first `n` bytes of the second
 * string (ignoring case).
 */
int strncasecmp(const char* __s1, const char* __s2, size_t __n) __attribute__((__pure__));

/**
 * Like strncasecmp() but taking a `locale_t`.
 */


int strncasecmp_l(const char* __s1, const char* __s2, size_t __n, locale_t __l) __attribute__((__pure__)) __attribute__((annotate("introduced_in=" "23")));
# 37 "/data/data/com.termux/files/usr/include/string.h" 2 3 4




# 1 "/data/data/com.termux/files/usr/include/strings.h" 1 3 4
/*	$NetBSD: strings.h,v 1.10 2005/02/03 04:39:32 perry Exp $	*/

/*-
 * Copyright (c) 1998 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Klaus Klein.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *        This product includes software developed by the NetBSD
 *        Foundation, Inc. and its contributors.
 * 4. Neither the name of The NetBSD Foundation nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */



/**
 * @file strings.h
 * @brief Extra string functions.
 */
# 54 "/data/data/com.termux/files/usr/include/strings.h" 3 4
/** Deprecated. Use memmove() instead. */

static __inline__ __attribute__((__always_inline__)) void __bionic_bcopy(const void* b1, void* b2, size_t len) {
  __builtin_memmove(b2, b1, len);
}

/** Deprecated. Use memset() instead. */

static __inline__ __attribute__((__always_inline__)) void __bionic_bzero(void* b, size_t len) {
  __builtin_memset(b, 0, len);
}


/**
 * [ffs(3)](http://man7.org/linux/man-pages/man3/ffs.3.html) finds the first set bit in `__i`.
 *
 * Returns 0 if no bit is set, or the index of the lowest set bit (counting from 1) otherwise.
 */
int ffs(int __i) __attribute__((annotate("introduced_in_x86=" "18")));
# 81 "/data/data/com.termux/files/usr/include/strings.h" 3 4
# 1 "/data/data/com.termux/files/usr/include/android/legacy_strings_inlines.h" 1 3 4
/*
 * Copyright (C) 2017 The Android Open Source Project
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
# 82 "/data/data/com.termux/files/usr/include/strings.h" 2 3 4
# 42 "/data/data/com.termux/files/usr/include/string.h" 2 3 4


void* memccpy(void* __dst, const void* __src, int __stop_char, size_t __n);
void* memchr(const void* __s, int __ch, size_t __n) __attribute__((__pure__));




void* memrchr(const void* __s, int __ch, size_t __n) __attribute__((__pure__));

int memcmp(const void* __lhs, const void* __rhs, size_t __n) __attribute__((__pure__));
void* memcpy(void*, const void*, size_t);



void* mempcpy(void* __dst, const void* __src, size_t __n) __attribute__((annotate("introduced_in=" "23")));



void* memmove(void* __dst, const void* __src, size_t __n);
void* memset(void* __dst, int __ch, size_t __n);
void* memmem(const void* __haystack, size_t __haystack_size, const void* __needle, size_t __needle_size) __attribute__((__pure__));

char* strchr(const char* __s, int __ch) __attribute__((__pure__));


char* __strchr_chk(const char* __s, int __ch, size_t __n) __attribute__((annotate("introduced_in=" "18")));
# 82 "/data/data/com.termux/files/usr/include/string.h" 3 4
char* strchrnul(const char* __s, int __ch) __attribute__((__pure__)) __attribute__((annotate("introduced_in=" "24")));





char* strrchr(const char* __s, int __ch) __attribute__((__pure__));


char* __strrchr_chk(const char* __s, int __ch, size_t __n) __attribute__((annotate("introduced_in=" "18")));



size_t strlen(const char* __s) __attribute__((__pure__));


size_t __strlen_chk(const char* __s, size_t __n) __attribute__((annotate("introduced_in=" "17")));



int strcmp(const char* __lhs, const char* __rhs) __attribute__((__pure__));


char* stpcpy(char* __dst, const char* __src) __attribute__((annotate("introduced_in=" "21")));


char* strcpy(char* __dst, const char* __src);
char* strcat(char* __dst, const char* __src);
char* strdup(const char* __s);

char* strstr(const char* __haystack, const char* __needle) __attribute__((__pure__));




char* strcasestr(const char* __haystack, const char* __needle) __attribute__((__pure__));

char* strtok(char* __s, const char* __delimiter);
char* strtok_r(char* __s, const char* __delimiter, char** __pos_ptr);

char* strerror(int __errno_value);


char* strerror_l(int __errno_value, locale_t __l) __attribute__((annotate("introduced_in=" "23")));



char* strerror_r(int __errno_value, char* __buf, size_t __n) __asm__("__gnu_strerror_r") __attribute__((annotate("introduced_in=" "23")));




size_t strnlen(const char* __s, size_t __n) __attribute__((__pure__));
char* strncat(char* __dst, const char* __src, size_t __n);
char* strndup(const char* __s, size_t __n);
int strncmp(const char* __lhs, const char* __rhs, size_t __n) __attribute__((__pure__));


char* stpncpy(char* __dst, const char* __src, size_t __n) __attribute__((annotate("introduced_in=" "21")));


char* strncpy(char* __dst, const char* __src, size_t __n);

size_t strlcat(char* __dst, const char* __src, size_t __n);
size_t strlcpy(char* __dst, const char* __src, size_t __n);

size_t strcspn(const char* __s, const char* __reject) __attribute__((__pure__));
char* strpbrk(const char* __s, const char* __accept) __attribute__((__pure__));
char* strsep(char** __s_ptr, const char* __delimiter);
size_t strspn(const char* __s, const char* __accept);

char* strsignal(int __signal);

int strcoll(const char* __lhs, const char* __rhs) __attribute__((__pure__));
size_t strxfrm(char* __dst, const char* __src, size_t __n);


int strcoll_l(const char* __lhs, const char* __rhs, locale_t __l) __attribute__((__pure__)) __attribute__((annotate("introduced_in=" "21")));
size_t strxfrm_l(char* __dst, const char* __src, size_t __n, locale_t __l) __attribute__((annotate("introduced_in=" "21")));





/*
 * glibc has a basename in <string.h> that's different to the POSIX one in <libgen.h>.
 * It doesn't modify its argument, and in C++ it's const-correct.
 */
# 180 "/data/data/com.termux/files/usr/include/string.h" 3 4
char* basename(const char* __path) __asm__("__gnu_basename") __attribute__((annotate("introduced_in=" "23")));
# 190 "/data/data/com.termux/files/usr/include/string.h" 3 4
/* Const-correct overloads. Placed after FORTIFY so we call those functions, if possible. */
# 48 "/data/data/com.termux/files/usr/include/stdio.h" 2 3 4
# 1 "/data/data/com.termux/files/usr/include/aarch64-linux-android/asm/fcntl.h" 1 3 4
/****************************************************************************
 ****************************************************************************
 ***
 ***   This header was automatically generated from a Linux kernel header
 ***   of the same name, to make information necessary for userspace to
 ***   call into the kernel available to libc.  It contains only constants,
 ***   structures, and macros generated from the original header, and thus,
 ***   contains no copyrightable information.
 ***
 ***   To edit the content of this header, modify the corresponding
 ***   source file (e.g. under external/kernel-headers/original/) then
 ***   run bionic/libc/kernel/tools/update_all.py
 ***
 ***   Any manual change here will be lost the next time this script will
 ***   be run. You've been warned!
 ***
 ****************************************************************************
 ****************************************************************************/







# 1 "/data/data/com.termux/files/usr/include/asm-generic/fcntl.h" 1 3 4
/****************************************************************************
 ****************************************************************************
 ***
 ***   This header was automatically generated from a Linux kernel header
 ***   of the same name, to make information necessary for userspace to
 ***   call into the kernel available to libc.  It contains only constants,
 ***   structures, and macros generated from the original header, and thus,
 ***   contains no copyrightable information.
 ***
 ***   To edit the content of this header, modify the corresponding
 ***   source file (e.g. under external/kernel-headers/original/) then
 ***   run bionic/libc/kernel/tools/update_all.py
 ***
 ***   Any manual change here will be lost the next time this script will
 ***   be run. You've been warned!
 ***
 ****************************************************************************
 ****************************************************************************/
# 121 "/data/data/com.termux/files/usr/include/asm-generic/fcntl.h" 3 4
struct f_owner_ex {
  int type;
  __kernel_pid_t pid;
};
# 148 "/data/data/com.termux/files/usr/include/asm-generic/fcntl.h" 3 4
struct flock {
  short l_type;
  short l_whence;
  __kernel_off_t l_start;
  __kernel_off_t l_len;
  __kernel_pid_t l_pid;

};





struct flock64 {
  short l_type;
  short l_whence;
  __kernel_loff_t l_start;
  __kernel_loff_t l_len;
  __kernel_pid_t l_pid;

};
# 26 "/data/data/com.termux/files/usr/include/aarch64-linux-android/asm/fcntl.h" 2 3 4
# 49 "/data/data/com.termux/files/usr/include/stdio.h" 2 3 4

# 1 "/data/data/com.termux/files/usr/include/bits/seek_constants.h" 1 3 4
/*
 * Copyright (C) 2016 The Android Open Source Project
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */



/**
 * @file bits/seek_constants.h
 * @brief The `SEEK_` constants.
 */

/** Seek to an absolute offset. */

/** Seek relative to the current offset. */

/** Seek relative to the end of the file. */




/**
 * Seek to the first data (non-hole) location in the file
 * greater than or equal to the given offset.
 *
 * See [lseek(2)](http://man7.org/linux/man-pages/man2/lseek.2.html).
 */


/**
 * Seek to the first hole (non-data) location in the file
 * greater than or equal to the given offset.
 *
 * See [lseek(2)](http://man7.org/linux/man-pages/man2/lseek.2.html).
 */
# 51 "/data/data/com.termux/files/usr/include/stdio.h" 2 3 4

# 1 "/data/data/com.termux/files/usr/include/bits/struct_file.h" 1 3 4
/*
 * Copyright (C) 2016 The Android Open Source Project
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */







struct __sbuf {
 unsigned char* _base;
 size_t _size;
};







typedef int64_t _struct_file_off_t;





/** The opaque structure implementing `FILE`. Do not make any assumptions about its content. */
struct __sFILE {
 unsigned char *_p; /* current position in (some) buffer */
 int _r; /* read space left for getc() */
 int _w; /* write space left for putc() */

 int _flags; /* flags, below; this FILE is free if 0 */
 int _file; /* fileno, if Unix descriptor, else -1 */




 struct __sbuf _bf; /* the buffer (at least 1 byte, if !NULL) */
        int _lbfsize; /* 0 or -_bf._size, for inline putc */

       /* operations */
       void *_cookie; /* cookie passed to io functions */
 int (*_close)(void *);
 int (*_read)(void *, char *, int);
 _struct_file_off_t (*_seek)(void *, _struct_file_off_t, int);
 int (*_write)(void *, const char *, int);

 /* extension data, to avoid further ABI breakage */
 struct __sbuf _ext;
 /* data for long sequences of ungetc() */
 unsigned char *_up; /* saved _p when _p is doing ungetc data */
 int _ur; /* saved _r when _r is counting ungetc data */

 /* tricks to meet minimum requirements even when malloc() fails */
 unsigned char _ubuf[3]; /* guarantee an ungetc() buffer */
 unsigned char _nbuf[1]; /* guarantee a getc() buffer */

 /* separate buffer for fgetln() when line crosses buffer boundary */
 struct __sbuf _lb; /* buffer for fgetln() */

 /* Unix stdio files get aligned to block boundaries on fseek() */
 int _blksize; /* stat.st_blksize (may be != _bf._size) */
 _struct_file_off_t _offset; /* current lseek offset */
};




 /* RD and WR are never simultaneously asserted */
# 53 "/data/data/com.termux/files/usr/include/stdio.h" 2 3 4



typedef off_t fpos_t;
typedef off64_t fpos64_t;

struct __sFILE;
typedef struct __sFILE FILE;


extern FILE* stdin __attribute__((annotate("introduced_in=" "23")));
extern FILE* stdout __attribute__((annotate("introduced_in=" "23")));
extern FILE* stderr __attribute__((annotate("introduced_in=" "23")));

/* C99 and earlier plus current C++ standards say these must be macros. */
# 80 "/data/data/com.termux/files/usr/include/stdio.h" 3 4
/*
 * The following three definitions are for ANSI C, which took them
 * from System V, which brilliantly took internal interface macros and
 * made them official arguments to setvbuf(), without renaming them.
 * Hence, these ugly _IOxxx names are *supposed* to appear in user code.
 *
 * Although numbered as their counterparts above, the implementation
 * does not rely on this.
 */







/*
 * FOPEN_MAX is a minimum maximum, and is the number of streams that
 * stdio can provide without attempting to allocate further resources
 * (which could fail).  Do not use this for anything.
 */






void clearerr(FILE* __fp);
int fclose(FILE* __fp);
int feof(FILE* __fp);
int ferror(FILE* __fp);
int fflush(FILE* __fp);
int fgetc(FILE* __fp);
char* fgets(char* __buf, int __size, FILE* __fp);
int fprintf(FILE* __fp , const char* __fmt, ...) __attribute__((__format__(printf, 2, 3)));
int fputc(int __ch, FILE* __fp);
int fputs(const char* __s, FILE* __fp);
size_t fread(void* __buf, size_t __size, size_t __count, FILE* __fp);
int fscanf(FILE* __fp, const char* __fmt, ...) __attribute__((__format__(scanf, 2, 3)));
size_t fwrite(const void* __buf, size_t __size, size_t __count, FILE* __fp);
int getc(FILE* __fp);
int getchar(void);


ssize_t getdelim(char** __line_ptr, size_t* __line_length_ptr, int __delimiter, FILE* __fp) __attribute__((annotate("introduced_in=" "18")));
ssize_t getline(char** __line_ptr, size_t* __line_length_ptr, FILE* __fp) __attribute__((annotate("introduced_in=" "18")));



void perror(const char* __msg);
int printf(const char* __fmt, ...) __attribute__((__format__(printf, 1, 2)));
int putc(int __ch, FILE* __fp);
int putchar(int __ch);
int puts(const char* __s);
int remove(const char* __path);
void rewind(FILE* __fp);
int scanf(const char* __fmt, ...) __attribute__((__format__(scanf, 1, 2)));
void setbuf(FILE* __fp, char* __buf);
int setvbuf(FILE* __fp, char* __buf, int __mode, size_t __size);
int sscanf(const char* __s, const char* __fmt, ...) __attribute__((__format__(scanf, 2, 3)));
int ungetc(int __ch, FILE* __fp);
int vfprintf(FILE* __fp, const char* __fmt, va_list __args) __attribute__((__format__(printf, 2, 0)));
int vprintf(const char* __fp, va_list __args) __attribute__((__format__(printf, 1, 0)));


int dprintf(int __fd, const char* __fmt, ...) __attribute__((__format__(printf, 2, 3))) __attribute__((annotate("introduced_in=" "21")));
int vdprintf(int __fd, const char* __fmt, va_list __args) __attribute__((__format__(printf, 2, 0))) __attribute__((annotate("introduced_in=" "21")));
# 163 "/data/data/com.termux/files/usr/include/stdio.h" 3 4
int sprintf(char* __s, const char* __fmt, ...)
    __attribute__((__format__(printf, 2, 3))) ;
int vsprintf(char* __s, const char* __fmt, va_list __args)
    __attribute__((__format__(printf, 2, 0))) ;
char* tmpnam(char* __s)
    __attribute__((deprecated("tempnam is unsafe, use mkstemp or tmpfile instead")));

char* tempnam(const char* __dir, const char* __prefix)
    __attribute__((deprecated("tempnam is unsafe, use mkstemp or tmpfile instead")));

/**
 * [rename(2)](http://man7.org/linux/man-pages/man2/rename.2.html) changes
 * the name or location of a file.
 *
 * Returns 0 on success, and returns -1 and sets `errno` on failure.
 */
int rename(const char* __old_path, const char* __new_path);

/**
 * [renameat(2)](http://man7.org/linux/man-pages/man2/renameat.2.html) changes
 * the name or location of a file, interpreting relative paths using an fd.
 *
 * Returns 0 on success, and returns -1 and sets `errno` on failure.
 */
int renameat(int __old_dir_fd, const char* __old_path, int __new_dir_fd, const char* __new_path);



/**
 * Flag for [renameat2(2)](http://man7.org/linux/man-pages/man2/renameat2.2.html)
 * to fail if the new path already exists.
 */


/**
 * Flag for [renameat2(2)](http://man7.org/linux/man-pages/man2/renameat2.2.html)
 * to atomically exchange the two paths.
 */


/**
 * Flag for [renameat2(2)](http://man7.org/linux/man-pages/man2/renameat2.2.html)
 * to create a union/overlay filesystem object.
 */


/**
 * [renameat2(2)](http://man7.org/linux/man-pages/man2/renameat2.2.html) changes
 * the name or location of a file, interpreting relative paths using an fd,
 * with optional `RENAME_` flags.
 *
 * Returns 0 on success, and returns -1 and sets `errno` on failure.
 */
# 224 "/data/data/com.termux/files/usr/include/stdio.h" 3 4
int fseek(FILE* __fp, long __offset, int __whence);
long ftell(FILE* __fp);

/* See https://android.googlesource.com/platform/bionic/+/master/docs/32-bit-abi.md */
# 249 "/data/data/com.termux/files/usr/include/stdio.h" 3 4
int fgetpos(FILE* __fp, fpos_t* __pos);
int fsetpos(FILE* __fp, const fpos_t* __pos);
int fseeko(FILE* __fp, off_t __offset, int __whence);
off_t ftello(FILE* __fp);

FILE* funopen(const void* __cookie,
              int (*__read_fn)(void*, char*, int),
              int (*__write_fn)(void*, const char*, int),
              fpos_t (*__seek_fn)(void*, fpos_t, int),
              int (*__close_fn)(void*));




int fgetpos64(FILE* __fp, fpos64_t* __pos) __attribute__((annotate("introduced_in=" "24")));
int fsetpos64(FILE* __fp, const fpos64_t* __pos) __attribute__((annotate("introduced_in=" "24")));
int fseeko64(FILE* __fp, off64_t __offset, int __whence) __attribute__((annotate("introduced_in=" "24")));
off64_t ftello64(FILE* __fp) __attribute__((annotate("introduced_in=" "24")));





FILE* funopen64(const void* __cookie,
                int (*__read_fn)(void*, char*, int),
                int (*__write_fn)(void*, const char*, int),
                fpos64_t (*__seek_fn)(void*, fpos64_t, int),
                int (*__close_fn)(void*)) __attribute__((annotate("introduced_in=" "24")));




FILE* fopen(const char* __path, const char* __mode);


FILE* fopen64(const char* __path, const char* __mode) __attribute__((annotate("introduced_in=" "24")));


FILE* freopen(const char* __path, const char* __mode, FILE* __fp);


FILE* freopen64(const char* __path, const char* __mode, FILE* __fp) __attribute__((annotate("introduced_in=" "24")));



FILE* tmpfile64(void) __attribute__((annotate("introduced_in=" "24")));



int snprintf(char* __buf, size_t __size, const char* __fmt, ...) __attribute__((__format__(printf, 3, 4)));
int vfscanf(FILE* __fp, const char* __fmt, va_list __args) __attribute__((__format__(scanf, 2, 0)));
int vscanf(const char* __fmt , va_list __args) __attribute__((__format__(scanf, 1, 0)));
int vsnprintf(char* __buf, size_t __size, const char* __fmt, va_list __args) __attribute__((__format__(printf, 3, 0)));
int vsscanf(const char* __s, const char* __fmt, va_list __args) __attribute__((__format__(scanf, 2, 0)));



/* Needed by gnulibs freading(). */


/* Used by perl, fish, and others. */
static __inline__ char* ctermid(char* s) {
 if (s == 0) return (char*) "/dev/tty";
 strcpy(s, "/dev/tty");
 return s;
}

FILE* fdopen(int __fd, const char* __mode);
int fileno(FILE* __fp);
int pclose(FILE* __fp);
FILE* popen(const char* __command, const char* __mode);
void flockfile(FILE* __fp);
int ftrylockfile(FILE* __fp);
void funlockfile(FILE* __fp);
int getc_unlocked(FILE* __fp);
int getchar_unlocked(void);
int putc_unlocked(int __ch, FILE* __fp);
int putchar_unlocked(int __ch);



FILE* fmemopen(void* __buf, size_t __size, const char* __mode) __attribute__((annotate("introduced_in=" "23")));
FILE* open_memstream(char** __ptr, size_t* __size_ptr) __attribute__((annotate("introduced_in=" "23")));




int asprintf(char** __s_ptr, const char* __fmt, ...) __attribute__((__format__(printf, 2, 3)));
char* fgetln(FILE* __fp, size_t* __length_ptr);
int fpurge(FILE* __fp);
void setbuffer(FILE* __fp, char* __buf, int __size);
int setlinebuf(FILE* __fp);
int vasprintf(char** __s_ptr, const char* __fmt, va_list __args) __attribute__((__format__(printf, 2, 0)));


void clearerr_unlocked(FILE* __fp) __attribute__((annotate("introduced_in=" "23")));
int feof_unlocked(FILE* __fp) __attribute__((annotate("introduced_in=" "23")));
int ferror_unlocked(FILE* __fp) __attribute__((annotate("introduced_in=" "23")));




int fileno_unlocked(FILE* __fp) __attribute__((annotate("introduced_in=" "24")));
# 383 "/data/data/com.termux/files/usr/include/stdio.h" 3 4
int open(const char*, int, ...);
extern pid_t getpid();
extern int unlink(const char*);
void free(void* p);
uint32_t arc4random(void);
static __inline__ FILE* tmpfile() {
 int p = getpid();
 char* path;
 int i;
 for (i = 0; i < 100; i++) {
  unsigned int r = arc4random();
  if (asprintf(&path, "/data/data/com.termux/files/usr/tmp/tmpfile.%d-%u", p, r) == -1) return ((void*)0);
  int fd = open(path, 00000002 | 00000100 | 00000200 | 0400000, 0600);
  if (fd >= 0) {
   FILE* result = fdopen(fd, "w+");
   unlink(path);
   free(path);
   return result;
  }
  free(path);
 }
 return ((void*)0);
}
# 2 "a.c" 2

int main() {
    puts("HELLO WORLD");

    return 0;
}

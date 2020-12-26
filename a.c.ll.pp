# 1 "a.c.ll"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4

# 1 "/usr/include/stdc-predef.h" 3 4
/* Copyright (C) 1991-2018 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */




/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */

/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
# 52 "/usr/include/stdc-predef.h" 3 4
/* wchar_t uses Unicode 10.0.0.  Version 10.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2017, fifth edition, plus
   the following additions from Amendment 1 to the fifth edition:
   - 56 emoji characters
   - 285 hentaigana
   - 3 additional Zanabazar Square characters */
# 1 "<command-line>" 2
# 1 "a.c.ll"

# 1 "a.c.ll"
; ModuleID = 'Module a.c.pp'
source_filename = "Module a.c.pp"

%_IO_FILE = type {}
%_IO_cookie_io_functions_t = type { i64 (i8*, i8*, i64)*, i64 (i8*, i8*, i64)*, i32 (i8*, i64*, i32)*, i32 (i8*)* }
%__builtin_va_list = type { i32, i32, i8*, i8* }
%_G_fpos_t = type { i64, %anonmous_struct1 }
%anonmous_struct1 = type { i32, %anonmous_union0 }
%anonmous_union0 = type { i32 }
%_G_fpos64_t = type { i64, %anonmous_struct1 }
%obstack = type {}
%__locale_struct = type { i64, i64, [13 x %__locale_data*], i16*, i32*, i32*, [13 x i8*] }
%__locale_data = type {}
%anonmous_struct6 = type { i64 }
%timeval = type { i64, i64 }
%timespec = type { i64, i64 }
%anonmous_struct5 = type { i64 }
%random_data = type { i32*, i32*, i32*, i32, i32, i32, i32* }
%drand48_data = type { [3 x i16], [3 x i16], i16, i16, i64 }
%anonmous_struct2 = type { i32, i32 }
%anonmous_struct3 = type { i64, i64 }
%anonmous_struct4 = type { i64, i64 }

@stdin = external externally_initialized global %_IO_FILE*, align 8
@stdout = external externally_initialized global %_IO_FILE*, align 8
@stderr = external externally_initialized global %_IO_FILE*, align 8
@sys_nerr = external externally_initialized global i32, align 4
@sys_errlist = external externally_initialized global i8**, align 8
@_sys_nerr = external externally_initialized global i32, align 4
@_sys_errlist = external externally_initialized global i8**, align 8
@gLVTable0 = internal global [512 x i8*] zeroinitializer, align 8
@gLVTable1 = internal global [512 x i8*] zeroinitializer, align 8
@gLVTable2 = internal global [512 x i8*] zeroinitializer, align 8
@gLVTable3 = internal global [512 x i8*] zeroinitializer, align 8
@gLVTable4 = internal global [512 x i8*] zeroinitializer, align 8
@gLVTable5 = internal global [512 x i8*] zeroinitializer, align 8
@gLVTable6 = internal global [512 x i8*] zeroinitializer, align 8
@global_string = private constant [3 x i8] c"OK\00", align 1
@global_string.1 = private constant [4 x i8] c"%d\0A\00", align 1

; Function Attrs: nounwind
declare void @llvm.va_start(i8*) #0

declare void @__builtin_va_start(i8*)

; Function Attrs: nounwind
declare void @llvm.va_end(i8*) #0

declare void @__builtin_va_end(i8*)

declare void @__builtin_memmove(i8*, i8*, i64, i1)

; Function Attrs: argmemonly nounwind
declare void @llvm.memmove.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i1) #1

declare void @__builtin_memcpy(i8*, i8*, i64, i1)

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture writeonly, i8* nocapture readonly, i64, i1) #1

declare void @__builtin_memset(i8*, i8, i64, i1)

; Function Attrs: argmemonly nounwind
declare void @llvm.memset.p0i8.i64(i8* nocapture writeonly, i8, i64, i1) #1

declare i32 @remove(i8*)

declare i32 @rename(i8*, i8*)

declare i32 @renameat(i32, i8*, i32, i8*)

declare i32 @renameat2(i32, i8*, i32, i8*, i32)

declare %_IO_FILE* @tmpfile()

declare %_IO_FILE* @tmpfile64()

declare i8* @tmpnam(i8*)

declare i8* @tmpnam_r(i8*)

declare i8* @tempnam(i8*, i8*)

declare i32 @fclose(%_IO_FILE*)

declare i32 @fflush(%_IO_FILE*)

declare i32 @fflush_unlocked(%_IO_FILE*)

declare i32 @fcloseall()

declare %_IO_FILE* @fopen(i8*, i8*)

declare %_IO_FILE* @freopen(i8*, i8*, %_IO_FILE*)

declare %_IO_FILE* @fopen64(i8*, i8*)

declare %_IO_FILE* @freopen64(i8*, i8*, %_IO_FILE*)

declare %_IO_FILE* @fdopen(i32, i8*)

declare %_IO_FILE* @fopencookie(i8*, i8*, %_IO_cookie_io_functions_t)

declare %_IO_FILE* @fmemopen(i8*, i64, i8*)

declare %_IO_FILE* @open_memstream(i8**, i64*)

declare void @setbuf(%_IO_FILE*, i8*)

declare i32 @setvbuf(%_IO_FILE*, i8*, i32, i64)

declare void @setbuffer(%_IO_FILE*, i8*, i64)

declare void @setlinebuf(%_IO_FILE*)

declare i32 @fprintf(%_IO_FILE*, i8*, ...)

declare i32 @printf(i8*, ...)

declare i32 @sprintf(i8*, i8*, ...)

declare i32 @vfprintf(%_IO_FILE*, i8*, %__builtin_va_list*)

declare i32 @vprintf(i8*, %__builtin_va_list*)

declare i32 @vsprintf(i8*, i8*, %__builtin_va_list*)

declare i32 @snprintf(i8*, i64, i8*, ...)

declare i32 @vsnprintf(i8*, i64, i8*, %__builtin_va_list*)

declare i32 @vasprintf(i8**, i8*, %__builtin_va_list*)

declare i32 @__asprintf(i8**, i8*, ...)

declare i32 @asprintf(i8**, i8*, ...)

declare i32 @vdprintf(i32, i8*, %__builtin_va_list*)

declare i32 @dprintf(i32, i8*, ...)

declare i32 @fscanf(%_IO_FILE*, i8*, ...)

declare i32 @scanf(i8*, ...)

declare i32 @sscanf(i8*, i8*, ...)

declare i32 @vfscanf(%_IO_FILE*, i8*, %__builtin_va_list*)

declare i32 @vscanf(i8*, %__builtin_va_list*)

declare i32 @vsscanf(i8*, i8*, %__builtin_va_list*)

declare i32 @fgetc(%_IO_FILE*)

declare i32 @getc(%_IO_FILE*)

declare i32 @getchar()

declare i32 @getc_unlocked(%_IO_FILE*)

declare i32 @getchar_unlocked()

declare i32 @fgetc_unlocked(%_IO_FILE*)

declare i32 @fputc(i32, %_IO_FILE*)

declare i32 @putc(i32, %_IO_FILE*)

declare i32 @putchar(i32)

declare i32 @fputc_unlocked(i32, %_IO_FILE*)

declare i32 @putc_unlocked(i32, %_IO_FILE*)

declare i32 @putchar_unlocked(i32)

declare i32 @getw(%_IO_FILE*)

declare i32 @putw(i32, %_IO_FILE*)

declare i8* @fgets(i8*, i32, %_IO_FILE*)

declare i8* @fgets_unlocked(i8*, i32, %_IO_FILE*)

declare i64 @__getdelim(i8**, i64*, i32, %_IO_FILE*)

declare i64 @getdelim(i8**, i64*, i32, %_IO_FILE*)

declare i64 @getline(i8**, i64*, %_IO_FILE*)

declare i32 @fputs(i8*, %_IO_FILE*)

declare i32 @puts(i8*)

declare i32 @ungetc(i32, %_IO_FILE*)

declare i64 @fread(i8*, i64, i64, %_IO_FILE*)

declare i64 @fwrite(i8*, i64, i64, %_IO_FILE*)

declare i32 @fputs_unlocked(i8*, %_IO_FILE*)

declare i64 @fread_unlocked(i8*, i64, i64, %_IO_FILE*)

declare i64 @fwrite_unlocked(i8*, i64, i64, %_IO_FILE*)

declare i32 @fseek(%_IO_FILE*, i64, i32)

declare i64 @ftell(%_IO_FILE*)

declare void @rewind(%_IO_FILE*)

declare i32 @fseeko(%_IO_FILE*, i64, i32)

declare i64 @ftello(%_IO_FILE*)

declare i32 @fgetpos(%_IO_FILE*, %_G_fpos_t*)

declare i32 @fsetpos(%_IO_FILE*, %_G_fpos_t*)

declare i32 @fseeko64(%_IO_FILE*, i64, i32)

declare i64 @ftello64(%_IO_FILE*)

declare i32 @fgetpos64(%_IO_FILE*, %_G_fpos64_t*)

declare i32 @fsetpos64(%_IO_FILE*, %_G_fpos64_t*)

declare void @clearerr(%_IO_FILE*)

declare i32 @feof(%_IO_FILE*)

declare i32 @ferror(%_IO_FILE*)

declare void @clearerr_unlocked(%_IO_FILE*)

declare i32 @feof_unlocked(%_IO_FILE*)

declare i32 @ferror_unlocked(%_IO_FILE*)

declare void @perror(i8*)

declare i32 @fileno(%_IO_FILE*)

declare i32 @fileno_unlocked(%_IO_FILE*)

declare %_IO_FILE* @popen(i8*, i8*)

declare i32 @pclose(%_IO_FILE*)

declare i8* @ctermid(i8*)

declare i8* @cuserid(i8*)

declare i32 @obstack_printf(%obstack*, i8*, ...)

declare i32 @obstack_vprintf(%obstack*, i8*, %__builtin_va_list*)

declare void @flockfile(%_IO_FILE*)

declare i32 @ftrylockfile(%_IO_FILE*)

declare void @funlockfile(%_IO_FILE*)

declare i32 @__uflow(%_IO_FILE*)

declare i32 @__overflow(%_IO_FILE*, i32)

declare i64 @__ctype_get_mb_cur_max()

declare double @atof(i8*)

declare i32 @atoi(i8*)

declare i64 @atol(i8*)

declare i64 @atoll(i8*)

declare double @strtod(i8*, i8**)

declare float @strtof(i8*, i8**)

declare i64 @strtold(i8*, i8**)

declare float @strtof32(i8*, i8**)

declare double @strtof64(i8*, i8**)

declare double @strtof32x(i8*, i8**)

declare i64 @strtof64x(i8*, i8**)

declare i64 @strtol(i8*, i8**, i32)

declare i64 @strtoul(i8*, i8**, i32)

declare i64 @strtoq(i8*, i8**, i32)

declare i64 @strtouq(i8*, i8**, i32)

declare i64 @strtoll(i8*, i8**, i32)

declare i64 @strtoull(i8*, i8**, i32)

declare i32 @strfromd(i8*, i64, i8*, double)

declare i32 @strfromf(i8*, i64, i8*, float)

declare i32 @strfroml(i8*, i64, i8*, i64)

declare i32 @strfromf32(i8*, i64, i8*, float)

declare i32 @strfromf64(i8*, i64, i8*, double)

declare i32 @strfromf32x(i8*, i64, i8*, double)

declare i32 @strfromf64x(i8*, i64, i8*, i64)

declare i64 @strtol_l(i8*, i8**, i32, %__locale_struct*)

declare i64 @strtoul_l(i8*, i8**, i32, %__locale_struct*)

declare i64 @strtoll_l(i8*, i8**, i32, %__locale_struct*)

declare i64 @strtoull_l(i8*, i8**, i32, %__locale_struct*)

declare double @strtod_l(i8*, i8**, %__locale_struct*)

declare float @strtof_l(i8*, i8**, %__locale_struct*)

declare i64 @strtold_l(i8*, i8**, %__locale_struct*)

declare float @strtof32_l(i8*, i8**, %__locale_struct*)

declare double @strtof64_l(i8*, i8**, %__locale_struct*)

declare double @strtof32x_l(i8*, i8**, %__locale_struct*)

declare i64 @strtof64x_l(i8*, i8**, %__locale_struct*)

declare i8* @l64a(i64)

declare i64 @a64l(i8*)

define internal i16 @__bswap_16(i16 %__bsx) {
entry:
  %__bsx1 = alloca i16
  store i16 %__bsx, i16* %__bsx1, align 2
  %0 = bitcast i16* %__bsx1 to i8*
  store i8* %0, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable0, i32 0, i32 0), align 8
  %__bsx2 = load i16, i16* %__bsx1, align 2
  %rshifttmp = ashr i16 %__bsx2, 8
  %andtmp = and i16 %rshifttmp, 255
  %__bsx3 = load i16, i16* %__bsx1, align 2
  %andtmp4 = and i16 %__bsx3, 255
  %lshifttmp = shl i16 %andtmp4, 8
  %ortmp = or i16 %andtmp, %lshifttmp
  ret i16 %ortmp
}

define internal i32 @__bswap_32(i32 %__bsx) {
entry:
  %__bsx1 = alloca i32
  store i32 %__bsx, i32* %__bsx1, align 4
  %0 = bitcast i32* %__bsx1 to i8*
  store i8* %0, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable1, i32 0, i32 0), align 8
  %__bsx2 = load i32, i32* %__bsx1, align 4
  %andtmp = and i32 %__bsx2, -16777216
  %rshifttmp = ashr i32 %andtmp, 24
  %__bsx3 = load i32, i32* %__bsx1, align 4
  %andtmp4 = and i32 %__bsx3, 16711680
  %rshifttmp5 = ashr i32 %andtmp4, 8
  %ortmp = or i32 %rshifttmp, %rshifttmp5
  %__bsx6 = load i32, i32* %__bsx1, align 4
  %andtmp7 = and i32 %__bsx6, 65280
  %lshifttmp = shl i32 %andtmp7, 8
  %ortmp8 = or i32 %ortmp, %lshifttmp
  %__bsx9 = load i32, i32* %__bsx1, align 4
  %andtmp10 = and i32 %__bsx9, 255
  %lshifttmp11 = shl i32 %andtmp10, 24
  %ortmp12 = or i32 %ortmp8, %lshifttmp11
  ret i32 %ortmp12
}

define internal i64 @__bswap_64(i64 %__bsx) {
entry:
  %__bsx1 = alloca i64
  store i64 %__bsx, i64* %__bsx1
  %0 = bitcast i64* %__bsx1 to i8*
  store i8* %0, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable2, i32 0, i32 0), align 8
  %__bsx2 = load i64, i64* %__bsx1
  %andtmp = and i64 %__bsx2, 4294967295
  %rshifttmp = ashr i64 %andtmp, 56
  %__bsx3 = load i64, i64* %__bsx1
  %andtmp4 = and i64 %__bsx3, 0
  %rshifttmp5 = ashr i64 %andtmp4, 40
  %ortmp = or i64 %rshifttmp, %rshifttmp5
  %__bsx6 = load i64, i64* %__bsx1
  %andtmp7 = and i64 %__bsx6, 0
  %rshifttmp8 = ashr i64 %andtmp7, 24
  %ortmp9 = or i64 %ortmp, %rshifttmp8
  %__bsx10 = load i64, i64* %__bsx1
  %andtmp11 = and i64 %__bsx10, 0
  %rshifttmp12 = ashr i64 %andtmp11, 8
  %ortmp13 = or i64 %ortmp9, %rshifttmp12
  %__bsx14 = load i64, i64* %__bsx1
  %andtmp15 = and i64 %__bsx14, 4278190080
  %lshifttmp = shl i64 %andtmp15, 8
  %ortmp16 = or i64 %ortmp13, %lshifttmp
  %__bsx17 = load i64, i64* %__bsx1
  %andtmp18 = and i64 %__bsx17, 16711680
  %lshifttmp19 = shl i64 %andtmp18, 24
  %ortmp20 = or i64 %ortmp16, %lshifttmp19
  %__bsx21 = load i64, i64* %__bsx1
  %andtmp22 = and i64 %__bsx21, 65280
  %lshifttmp23 = shl i64 %andtmp22, 40
  %ortmp24 = or i64 %ortmp20, %lshifttmp23
  %__bsx25 = load i64, i64* %__bsx1
  %andtmp26 = and i64 %__bsx25, 255
  %lshifttmp27 = shl i64 %andtmp26, 56
  %ortmp28 = or i64 %ortmp24, %lshifttmp27
  ret i64 %ortmp28
}

define internal i16 @__uint16_identity(i16 %__x) {
entry:
  %__x1 = alloca i16
  store i16 %__x, i16* %__x1, align 2
  %0 = bitcast i16* %__x1 to i8*
  store i8* %0, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable3, i32 0, i32 0), align 8
  %__x2 = load i16, i16* %__x1, align 2
  ret i16 %__x2
}

define internal i32 @__uint32_identity(i32 %__x) {
entry:
  %__x1 = alloca i32
  store i32 %__x, i32* %__x1, align 4
  %0 = bitcast i32* %__x1 to i8*
  store i8* %0, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable4, i32 0, i32 0), align 8
  %__x2 = load i32, i32* %__x1, align 4
  ret i32 %__x2
}

define internal i64 @__uint64_identity(i64 %__x) {
entry:
  %__x1 = alloca i64
  store i64 %__x, i64* %__x1
  %0 = bitcast i64* %__x1 to i8*
  store i8* %0, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable5, i32 0, i32 0), align 8
  %__x2 = load i64, i64* %__x1
  ret i64 %__x2
}

declare i32 @select(i32, %anonmous_struct6*, %anonmous_struct6*, %anonmous_struct6*, %timeval*)

declare i32 @pselect(i32, %anonmous_struct6*, %anonmous_struct6*, %anonmous_struct6*, %timespec*, %anonmous_struct5*)

declare i64 @random()

declare void @srandom(i32)

declare i8* @initstate(i32, i8*, i64)

declare i8* @setstate(i8*)

declare i32 @random_r(%random_data*, i32*)

declare i32 @srandom_r(i32, %random_data*)

declare i32 @initstate_r(i32, i8*, i64, %random_data*)

declare i32 @setstate_r(i8*, %random_data*)

declare i32 @rand()

declare void @srand(i32)

declare i32 @rand_r(i32*)

declare double @drand48()

declare double @erand48([3 x i16])

declare i64 @lrand48()

declare i64 @nrand48([3 x i16])

declare i64 @mrand48()

declare i64 @jrand48([3 x i16])

declare void @srand48(i64)

declare i16* @seed48([3 x i16])

declare void @lcong48([7 x i16])

declare i32 @drand48_r(%drand48_data*, double*)

declare i32 @erand48_r([3 x i16], %drand48_data*, double*)

declare i32 @lrand48_r(%drand48_data*, i64*)

declare i32 @nrand48_r([3 x i16], %drand48_data*, i64*)

declare i32 @mrand48_r(%drand48_data*, i64*)

declare i32 @jrand48_r([3 x i16], %drand48_data*, i64*)

declare i32 @srand48_r(i64, %drand48_data*)

declare i32 @seed48_r([3 x i16], %drand48_data*)

declare i32 @lcong48_r([7 x i16], %drand48_data*)

declare i8* @malloc(i64)

declare i8* @calloc(i64, i64)

declare i8* @realloc(i8*, i64)

declare i8* @reallocarray(i8*, i64, i64)

declare void @free(i8*)

declare i8* @alloca(i64)

declare i8* @valloc(i64)

declare i32 @posix_memalign(i8**, i64, i64)

declare i8* @aligned_alloc(i64, i64)

declare void @abort()

declare i32 @atexit(void ()*)

declare i32 @at_quick_exit(void ()*)

declare i32 @on_exit(void (i32, i8*)*, i8*)

declare void @exit(i32)

declare void @quick_exit(i32)

declare void @_Exit(i32)

declare i8* @getenv(i8*)

declare i8* @secure_getenv(i8*)

declare i32 @putenv(i8*)

declare i32 @setenv(i8*, i8*, i32)

declare i32 @unsetenv(i8*)

declare i32 @clearenv()

declare i8* @mktemp(i8*)

declare i32 @mkstemp(i8*)

declare i32 @mkstemp64(i8*)

declare i32 @mkstemps(i8*, i32)

declare i32 @mkstemps64(i8*, i32)

declare i8* @mkdtemp(i8*)

declare i32 @mkostemp(i8*, i32)

declare i32 @mkostemp64(i8*, i32)

declare i32 @mkostemps(i8*, i32, i32)

declare i32 @mkostemps64(i8*, i32, i32)

declare i32 @system(i8*)

declare i8* @canonicalize_file_name(i8*)

declare i8* @realpath(i8*, i8*)

declare i8* @bsearch(i8*, i8*, i64, i64, i32 (i8*, i8*)*)

declare void @qsort(i8*, i64, i64, i32 (i8*, i8*)*)

declare void @qsort_r(i8*, i64, i64, i32 (i8*, i8*, i8*)*, i8*)

declare i32 @abs(i32)

declare i64 @labs(i64)

declare i64 @llabs(i64)

declare %anonmous_struct2 @div(i32, i32)

declare %anonmous_struct3 @ldiv(i64, i64)

declare %anonmous_struct4 @lldiv(i64, i64)

declare i8* @ecvt(double, i32, i32*, i32*)

declare i8* @fcvt(double, i32, i32*, i32*)

declare i8* @gcvt(double, i32, i8*)

declare i8* @qecvt(i64, i32, i32*, i32*)

declare i8* @qfcvt(i64, i32, i32*, i32*)

declare i8* @qgcvt(i64, i32, i8*)

declare i32 @ecvt_r(double, i32, i32*, i32*, i8*, i64)

declare i32 @fcvt_r(double, i32, i32*, i32*, i8*, i64)

declare i32 @qecvt_r(i64, i32, i32*, i32*, i8*, i64)

declare i32 @qfcvt_r(i64, i32, i32*, i32*, i8*, i64)

declare i32 @mblen(i8*, i64)

declare i32 @mbtowc(i32*, i8*, i64)

declare i32 @wctomb(i8*, i32)

declare i64 @mbstowcs(i32*, i8*, i64)

declare i64 @wcstombs(i8*, i32*, i64)

declare i32 @rpmatch(i8*)

declare i32 @getsubopt(i8**, i8**, i8**)

declare i32 @posix_openpt(i32)

declare i32 @grantpt(i32)

declare i32 @unlockpt(i32)

declare i8* @ptsname(i32)

declare i32 @ptsname_r(i32, i8*, i64)

declare i32 @getpt()

declare i32 @getloadavg(double*, i32)

define i32 @main() {
entry:
  %a = alloca i32
  %0 = bitcast i32* %a to i8*
  store i8* %0, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable6, i32 0, i32 0), align 8
  store i32 123, i32* %a, align 4
  %a1 = load i32, i32* %a, align 4
  %b = alloca i32*
  %1 = bitcast i32** %b to i8*
  store i8* %1, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable6, i32 0, i32 1), align 8
  store i32* %a, i32** %b, align 8
  %c = alloca i32
  %2 = bitcast i32* %c to i8*
  store i8* %2, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable6, i32 0, i32 2), align 8
  store i32 234, i32* %c, align 4
  %c2 = load i32, i32* %c, align 4
  %d = alloca i32*
  %3 = bitcast i32** %d to i8*
  store i8* %3, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable6, i32 0, i32 3), align 8
  store i32* %c, i32** %d, align 8
  %d3 = load i32*, i32** %d, align 8
  store i32* %d3, i32** %b, align 8
  %derefference_value = load i32, i32* %d3, align 8
  %d4 = load i32*, i32** %d, align 8
  %eqtmpX = icmp eq i32* %d4, inttoptr (i32 234 to i32*)
  br i1 %eqtmpX, label %cond_jump_then, label %cond_end

cond_jump_then: ; preds = %entry
  %4 = call i32 @puts(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @global_string, i32 0, i32 0))
  br label %cond_end

cond_end: ; preds = %cond_jump_then, %entry
  %d5 = load i32*, i32** %d, align 8
  %e = alloca i32**
  %5 = bitcast i32*** %e to i8*
  store i8* %5, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable6, i32 0, i32 4), align 8
  store i32** %d, i32*** %e, align 8
  %e6 = load i32**, i32*** %e, align 8
  %derefference_value7 = load i32*, i32** %e6, align 8
  %6 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @global_string.1, i32 0, i32 0), i32* %derefference_value7)
  ret i32 0
}

attributes #0 = { nounwind }
attributes #1 = { argmemonly nounwind }

!llvm.module.flags = !{!0, !1}

!0 = !{i32 2, !"Debug Info Version", i32 3}
!1 = !{i32 2, !"Dwarf Version", i32 2}

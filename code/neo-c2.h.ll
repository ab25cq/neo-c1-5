; ModuleID = 'Module code/HelloWorld.c.pp'
source_filename = "Module code/HelloWorld.c.pp"

%_IO_FILE = type {}
%_IO_cookie_io_functions_t = type { i32 (i8*, i8*, i64)*, i32 (i8*, i8*, i64)*, i32 (i8*, i64*, i32)*, i32 (i8*)* }
%__builtin_va_list = type { i32, i32, i8*, i8* }
%_G_fpos_t = type { i64, %anonmous_struct1 }
%anonmous_struct1 = type { i32, [4 x i8], %anonmous_union0 }
%anonmous_union0 = type { i32 }
%_G_fpos64_t = type { i64, %anonmous_struct1 }
%obstack = type {}
%__locale_struct = type { [13 x %__locale_data*], i16*, i32*, i32*, [13 x i8*] }
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
@__environ = external externally_initialized global i8**, align 8
@environ = external externally_initialized global i8**, align 8
@optarg = external externally_initialized global i8*, align 8
@optind = external externally_initialized global i32, align 4
@opterr = external externally_initialized global i32, align 4
@optopt = external externally_initialized global i32, align 4
@gLVTable6 = internal global [512 x i8*] zeroinitializer, align 8

; Function Attrs: nounwind
declare void @llvm.va_start(i8*) #0

declare void @__builtin_va_start(i8*)

; Function Attrs: nounwind
declare void @llvm.va_end(i8*) #0

declare void @__builtin_va_end(i8*)

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

declare i32 @access(i8*, i32)

declare i32 @euidaccess(i8*, i32)

declare i32 @eaccess(i8*, i32)

declare i32 @faccessat(i32, i8*, i32, i32)

declare i64 @lseek(i32, i64, i32)

declare i64 @lseek64(i32, i64, i32)

declare i32 @close(i32)

declare i64 @read(i32, i8*, i64)

declare i64 @write(i32, i8*, i64)

declare i64 @pread(i32, i8*, i64, i64)

declare i64 @pwrite(i32, i8*, i64, i64)

declare i64 @pread64(i32, i8*, i64, i64)

declare i64 @pwrite64(i32, i8*, i64, i64)

declare i32 @pipe([2 x i32])

declare i32 @pipe2([2 x i32], i32)

declare i32 @alarm(i32)

declare i32 @sleep(i32)

declare i32 @ualarm(i32, i32)

declare i32 @usleep(i32)

declare i32 @pause()

declare i32 @chown(i8*, i32, i32)

declare i32 @fchown(i32, i32, i32)

declare i32 @lchown(i8*, i32, i32)

declare i32 @fchownat(i32, i8*, i32, i32, i32)

declare i32 @chdir(i8*)

declare i32 @fchdir(i32)

declare i8* @getcwd(i8*, i64)

declare i8* @get_current_dir_name()

declare i8* @getwd(i8*)

declare i32 @dup(i32)

declare i32 @dup2(i32, i32)

declare i32 @dup3(i32, i32, i32)

declare i32 @execve(i8*, i8**, i8**)

declare i32 @fexecve(i32, i8**, i8**)

declare i32 @execv(i8*, i8**)

declare i32 @execle(i8*, i8*, ...)

declare i32 @execl(i8*, i8*, ...)

declare i32 @execvp(i8*, i8**)

declare i32 @execlp(i8*, i8*, ...)

declare i32 @execvpe(i8*, i8**, i8**)

declare i32 @nice(i32)

declare void @_exit(i32)

declare i64 @pathconf(i8*, i32)

declare i64 @fpathconf(i32, i32)

declare i64 @sysconf(i32)

declare i64 @confstr(i32, i8*, i64)

declare i32 @getpid()

declare i32 @getppid()

declare i32 @getpgrp()

declare i32 @__getpgid(i32)

declare i32 @getpgid(i32)

declare i32 @setpgid(i32, i32)

declare i32 @setpgrp()

declare i32 @setsid()

declare i32 @getsid(i32)

declare i32 @getuid()

declare i32 @geteuid()

declare i32 @getgid()

declare i32 @getegid()

declare i32 @getgroups(i32, i32*)

declare i32 @group_member(i32)

declare i32 @setuid(i32)

declare i32 @setreuid(i32, i32)

declare i32 @seteuid(i32)

declare i32 @setgid(i32)

declare i32 @setregid(i32, i32)

declare i32 @setegid(i32)

declare i32 @getresuid(i32*, i32*, i32*)

declare i32 @getresgid(i32*, i32*, i32*)

declare i32 @setresuid(i32, i32, i32)

declare i32 @setresgid(i32, i32, i32)

declare i32 @fork()

declare i32 @vfork()

declare i8* @ttyname(i32)

declare i32 @ttyname_r(i32, i8*, i64)

declare i32 @isatty(i32)

declare i32 @ttyslot()

declare i32 @link(i8*, i8*)

declare i32 @linkat(i32, i8*, i32, i8*, i32)

declare i32 @symlink(i8*, i8*)

declare i64 @readlink(i8*, i8*, i64)

declare i32 @symlinkat(i8*, i32, i8*)

declare i64 @readlinkat(i32, i8*, i8*, i64)

declare i32 @unlink(i8*)

declare i32 @unlinkat(i32, i8*, i32)

declare i32 @rmdir(i8*)

declare i32 @tcgetpgrp(i32)

declare i32 @tcsetpgrp(i32, i32)

declare i8* @getlogin()

declare i32 @getlogin_r(i8*, i64)

declare i32 @setlogin(i8*)

declare i32 @getopt(i32, i8**, i8*)

declare i32 @gethostname(i8*, i64)

declare i32 @sethostname(i8*, i64)

declare i32 @sethostid(i64)

declare i32 @getdomainname(i8*, i64)

declare i32 @setdomainname(i8*, i64)

declare i32 @vhangup()

declare i32 @revoke(i8*)

declare i32 @profil(i16*, i64, i64, i32)

declare i32 @acct(i8*)

declare i8* @getusershell()

declare void @endusershell()

declare void @setusershell()

declare i32 @daemon(i32, i32)

declare i32 @chroot(i8*)

declare i8* @getpass(i8*)

declare i32 @fsync(i32)

declare i32 @syncfs(i32)

declare i64 @gethostid()

declare void @sync()

declare i32 @getpagesize()

declare i32 @getdtablesize()

declare i32 @truncate(i8*, i64)

declare i32 @truncate64(i8*, i64)

declare i32 @ftruncate(i32, i64)

declare i32 @ftruncate64(i32, i64)

declare i32 @brk(i8*)

declare i8* @sbrk(i64)

declare i64 @syscall(i64, ...)

declare i32 @lockf(i32, i32, i64)

declare i32 @lockf64(i32, i32, i64)

declare i64 @copy_file_range(i32, i64*, i32, i64*, i64, i32)

declare i32 @fdatasync(i32)

declare i8* @crypt(i8*, i8*)

declare void @swab(i8*, i8*, i64)

declare i32 @getentropy(i8*, i64)

define internal i8* @xsprintf(i8* %msg, ...) {
entry:
  %msg1 = alloca i8*
  store i8* %msg, i8** %msg1, align 8
  %0 = bitcast i8** %msg1 to i8*
  store i8* %0, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable6, i32 0, i32 0), align 8
  %args = alloca [1 x %__builtin_va_list]
  %1 = bitcast [1 x %__builtin_va_list]* %args to i8*
  store i8* %1, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable6, i32 0, i32 1), align 8
  %msg2 = load i8*, i8** %msg1, align 8
  %2 = getelementptr inbounds [1 x %__builtin_va_list], [1 x %__builtin_va_list]* %args, i32 0, i32 0
  %3 = bitcast %__builtin_va_list* %2 to i8*
  call void @llvm.va_start(i8* %3)
  %tmp = alloca i8*
  %4 = bitcast i8** %tmp to i8*
  store i8* %4, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable6, i32 0, i32 2), align 8
  %5 = getelementptr inbounds [1 x %__builtin_va_list], [1 x %__builtin_va_list]* %args, i32 0, i32 0
  %msg3 = load i8*, i8** %msg1, align 8
  %tmp4 = load i8*, i8** %tmp, align 8
  %6 = call i32 @vasprintf(i8** %tmp, i8* %msg3, %__builtin_va_list* %5)
  %len = alloca i32
  %7 = bitcast i32* %len to i8*
  store i8* %7, i8** getelementptr inbounds ([512 x i8*], [512 x i8*]* @gLVTable6, i32 0, i32 3), align 8
  store i32 %6, i32* %len, align 4
  %8 = getelementptr inbounds [1 x %__builtin_va_list], [1 x %__builtin_va_list]* %args, i32 0, i32 0
  %9 = bitcast %__builtin_va_list* %8 to i8*
  call void @llvm.va_end(i8* %9)
  %tmp5 = load i8*, i8** %tmp, align 8
  ret i8* %tmp5
}

attributes #0 = { nounwind }

!llvm.module.flags = !{!0, !1}

!0 = !{i32 2, !"Debug Info Version", i32 3}
!1 = !{i32 2, !"Dwarf Version", i32 2}

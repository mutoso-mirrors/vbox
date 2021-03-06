/*
 * Standard I/O definitions.
 *
 * Derived from the mingw header written by Colin Peters.
 * Modified for Wine use by Jon Griffiths and Francois Gouget.
 * This file is in the public domain.
 */

/*
 * Sun LGPL Disclaimer: For the avoidance of doubt, except that if any license choice
 * other than GPL or LGPL is available it will apply instead, Sun elects to use only
 * the Lesser General Public License version 2.1 (LGPLv2) at this time for any software where
 * a choice of LGPL license versions is made available with the language indicating
 * that LGPLv2 or any later version may be used, or where a choice of which version
 * of the LGPL is applied is otherwise unspecified.
 */

#ifndef __WINE_STDIO_H
#define __WINE_STDIO_H

#include <crtdefs.h>

#ifndef RC_INVOKED
#include <stdarg.h>
#endif

#include <pshpack8.h>

/* file._flag flags */
#define _IOREAD          0x0001
#define _IOWRT           0x0002
#define _IOMYBUF         0x0008
#define _IOEOF           0x0010
#define _IOERR           0x0020
#define _IOSTRG          0x0040
#define _IORW            0x0080

#ifndef NULL
#ifdef  __cplusplus
#define NULL  0
#else
#define NULL  ((void *)0)
#endif
#endif

#define STDIN_FILENO  0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

/* more file._flag flags, but these conflict with Unix */
#define _IOFBF    0x0000
#define _IONBF    0x0004
#define _IOLBF    0x0040

#define EOF       (-1)
#define FILENAME_MAX 260
#define TMP_MAX   0x7fff
#define FOPEN_MAX 20
#define L_tmpnam  260

#define BUFSIZ    512

#ifndef SEEK_SET
#define SEEK_SET  0
#define SEEK_CUR  1
#define SEEK_END  2
#endif

#ifndef _FILE_DEFINED
#define _FILE_DEFINED
typedef struct _iobuf
{
  char* _ptr;
  int   _cnt;
  char* _base;
  int   _flag;
  int   _file;
  int   _charbuf;
  int   _bufsiz;
  char* _tmpfname;
} FILE;
#endif  /* _FILE_DEFINED */

#ifndef _FPOS_T_DEFINED
typedef __int64 DECLSPEC_ALIGN(8) fpos_t;
#define _FPOS_T_DEFINED
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _STDIO_DEFINED
# ifdef __i386__
FILE* __cdecl __p__iob(void);
#  define _iob (__p__iob())
# else
FILE* __cdecl __iob_func(void);
#  define _iob (__iob_func())
# endif
#endif /* _STDIO_DEFINED */

#define stdin              (_iob+STDIN_FILENO)
#define stdout             (_iob+STDOUT_FILENO)
#define stderr             (_iob+STDERR_FILENO)

#ifndef _STDIO_DEFINED
#define _STDIO_DEFINED
int    __cdecl _fcloseall(void);
FILE*  __cdecl _fdopen(int,const char*);
int    __cdecl _fgetchar(void);
int    __cdecl _filbuf(FILE*);
int    __cdecl _fileno(FILE*);
int    __cdecl _flsbuf(int,FILE*);
int    __cdecl _flushall(void);
int    __cdecl _fputchar(int);
FILE*  __cdecl _fsopen(const char*,const char*,int);
int    __cdecl _getmaxstdio(void);
int    __cdecl _getw(FILE*);
int    __cdecl _pclose(FILE*);
FILE*  __cdecl _popen(const char*,const char*);
int    __cdecl _putw(int,FILE*);
int    __cdecl _rmtmp(void);
int    __cdecl _setmaxstdio(int);
int    __cdecl _snprintf(char*,size_t,const char*,...);
char*  __cdecl _tempnam(const char*,const char*);
int    __cdecl _unlink(const char*);
int    __cdecl _vscprintf(const char*,__ms_va_list);
int    __cdecl _vsnprintf(char*,size_t,const char*,__ms_va_list);

void   __cdecl clearerr(FILE*);
int    __cdecl fclose(FILE*);
int    __cdecl feof(FILE*);
int    __cdecl ferror(FILE*);
int    __cdecl fflush(FILE*);
int    __cdecl fgetc(FILE*);
int    __cdecl fgetpos(FILE*,fpos_t*);
char*  __cdecl fgets(char*,int,FILE*);
FILE*  __cdecl fopen(const char*,const char*);
int    __cdecl fprintf(FILE*,const char*,...);
int    __cdecl fputc(int,FILE*);
int    __cdecl fputs(const char*,FILE*);
size_t __cdecl fread(void*,size_t,size_t,FILE*);
FILE*  __cdecl freopen(const char*,const char*,FILE*);
int    __cdecl fscanf(FILE*,const char*,...);
int    __cdecl fseek(FILE*,__msvcrt_long,int);
int    __cdecl fsetpos(FILE*,fpos_t*);
__msvcrt_long __cdecl ftell(FILE*);
size_t __cdecl fwrite(const void*,size_t,size_t,FILE*);
int    __cdecl getc(FILE*);
int    __cdecl getchar(void);
char*  __cdecl gets(char*);
void   __cdecl perror(const char*);
int    __cdecl printf(const char*,...);
int    __cdecl putc(int,FILE*);
int    __cdecl putchar(int);
int    __cdecl puts(const char*);
int    __cdecl remove(const char*);
int    __cdecl rename(const char*,const char*);
void   __cdecl rewind(FILE*);
int    __cdecl scanf(const char*,...);
void   __cdecl setbuf(FILE*,char*);
int    __cdecl setvbuf(FILE*,char*,int,size_t);
int    __cdecl sprintf(char*,const char*,...);
int    __cdecl sscanf(const char*,const char*,...);
FILE*  __cdecl tmpfile(void);
char*  __cdecl tmpnam(char*);
int    __cdecl ungetc(int,FILE*);
int    __cdecl vfprintf(FILE*,const char*,__ms_va_list);
int    __cdecl vprintf(const char*,__ms_va_list);
int    __cdecl vsprintf(char*,const char*,__ms_va_list);

#ifndef _WSTDIO_DEFINED
#define _WSTDIO_DEFINED
wint_t   __cdecl _fgetwchar(void);
wint_t   __cdecl _fputwchar(wint_t);
wchar_t* __cdecl _getws(wchar_t*);
int      __cdecl _putws(const wchar_t*);
int      __cdecl _snwprintf(wchar_t*,size_t,const wchar_t*,...);
int      __cdecl _vscwprintf(const wchar_t*,__ms_va_list);
int      __cdecl _vsnwprintf(wchar_t*,size_t,const wchar_t*,__ms_va_list);
FILE*    __cdecl _wfdopen(int,const wchar_t*);
FILE*    __cdecl _wfopen(const wchar_t*,const wchar_t*);
FILE*    __cdecl _wfreopen(const wchar_t*,const wchar_t*,FILE*);
FILE*    __cdecl _wfsopen(const wchar_t*,const wchar_t*,int);
void     __cdecl _wperror(const wchar_t*);
FILE*    __cdecl _wpopen(const wchar_t*,const wchar_t*);
int      __cdecl _wremove(const wchar_t*);
wchar_t* __cdecl _wtempnam(const wchar_t*,const wchar_t*);
wchar_t* __cdecl _wtmpnam(wchar_t*);

wint_t   __cdecl fgetwc(FILE*);
wchar_t* __cdecl fgetws(wchar_t*,int,FILE*);
wint_t   __cdecl fputwc(wint_t,FILE*);
int      __cdecl fputws(const wchar_t*,FILE*);
int      __cdecl fwprintf(FILE*,const wchar_t*,...);
int      __cdecl fputws(const wchar_t*,FILE*);
int      __cdecl fwscanf(FILE*,const wchar_t*,...);
wint_t   __cdecl getwc(FILE*);
wint_t   __cdecl getwchar(void);
wchar_t* __cdecl getws(wchar_t*);
wint_t   __cdecl putwc(wint_t,FILE*);
wint_t   __cdecl putwchar(wint_t);
int      __cdecl putws(const wchar_t*);
int      __cdecl swprintf(wchar_t*,const wchar_t*,...);
int      __cdecl swscanf(const wchar_t*,const wchar_t*,...);
wint_t   __cdecl ungetwc(wint_t,FILE*);
int      __cdecl vfwprintf(FILE*,const wchar_t*,__ms_va_list);
int      __cdecl vswprintf(wchar_t*,const wchar_t*,__ms_va_list);
int      __cdecl vwprintf(const wchar_t*,__ms_va_list);
int      __cdecl wprintf(const wchar_t*,...);
int      __cdecl wscanf(const wchar_t*,...);
#endif /* _WSTDIO_DEFINED */

#endif /* _STDIO_DEFINED */

#ifdef __cplusplus
}
#endif


static inline FILE* fdopen(int fd, const char *mode) { return _fdopen(fd, mode); }
static inline int fgetchar(void) { return _fgetchar(); }
static inline int fileno(FILE* file) { return _fileno(file); }
static inline int fputchar(int c) { return _fputchar(c); }
static inline int pclose(FILE* file) { return _pclose(file); }
static inline FILE* popen(const char* command, const char* mode) { return _popen(command, mode); }
static inline char* tempnam(const char *dir, const char *prefix) { return _tempnam(dir, prefix); }
#ifndef _UNLINK_DEFINED
static inline int unlink(const char* path) { return _unlink(path); }
#define _UNLINK_DEFINED
#endif
static inline int vsnprintf(char *buffer, size_t size, const char *format, __ms_va_list args) { return _vsnprintf(buffer,size,format,args); }

static inline wint_t fgetwchar(void) { return _fgetwchar(); }
static inline wint_t fputwchar(wint_t wc) { return _fputwchar(wc); }
static inline int getw(FILE* file) { return _getw(file); }
static inline int putw(int val, FILE* file) { return _putw(val, file); }
static inline FILE* wpopen(const wchar_t* command,const wchar_t* mode) { return _wpopen(command, mode); }

#include <poppack.h>

#endif /* __WINE_STDIO_H */

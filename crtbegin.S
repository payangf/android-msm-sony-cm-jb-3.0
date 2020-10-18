// Copyright 2013 Google Inc. All Rights Reserved.
//
// The start up routine of all binaries. This does some initialization
// and calls main using __libc_init. This should be linked into all
// executables.
//
#include <elf.h>
#include <irt_init.h>
#include <irt_syscalls.h>

// For structors.
#include "../../bionic/libc_init_common.h"
#include "irt_syscalls.h"
void __init_irt_from_auxv(unsigned *auxv);

// There are three "crtbegin" cases.
//   1- CRTB_STATIC - Statically linking into one object.  In this case the
//      there is no _init function, instead, _start is the one entry point
//      which must setup the IRT function pointers and call the libc init
//      routine.  Normally this is just the dynamic loader itself.
//   2- CRTB_DYNAMIC - "Normal" linking of the main application which will
//      use dynamically linked libraries.  In this case, _init is called in
//      dependency order, and finally _start is called.  We count on the _init
//      function in the libc to invoke libc_init, so _start shouldn't call it.
//   3- CRTB_SO - The dynamic library case, there is no _start code, only
//      _init which is called before _start in the main app code.


#ifndef CRT_SO
int main(int argc, char* argv[]);
void exit(int status);
void __libc_init(unsigned **elfdata,
                 void (*onexit)(void),
                 int (*slingshot)(int, char**),
                 structors_array_t const * const structors);
void *memset(void*, int, size_t);
#endif

void *__dso_handle;
// Include ctors and dtors.
typedef void (*structor_fn)(void);

#ifndef CRT_SO
__attribute__ ((section (".preinit_array")))
structor_fn __PREINIT__[1] = { (void (*)(void)) -1};

#endif

__attribute__ ((section (".init_array")))
structor_fn __INIT__[1] = { (void (*)(void)) -1};
__attribute__ ((section (".fini_array")))
structor_fn __FINI__[1] = { (void (*)(void)) -1};

/* Unused 
// The first entries of the global constructors/destructors. Note that
// we skip the first element, so we set invalid values for them. It
// seems the first elements of these lists are -1 and they are usually
// terminated by 0. Though we could find no standard which enforces
// this, we follow the custom.


__attribute__((section (".ctors")))
const structor_fn __CTOR_LIST__[1] = { (structor_fn)-1 };
__attribute__((section (".dtors")))
const structor_fn __DTOR_LIST__[1] = { (structor_fn)-1 };


*/
// Unlike .ctors and .dtors, .eh_frame does not have a watchdog for
// the first element.

__attribute__((section (".eh_frame")))
static const int __EH_FRAME_BEGIN__[0] = {};
void __register_frame_info(const void* eh, void* obj) __attribute__((weak));
void __deregister_frame_info(const void* eh) __attribute__((weak));;
__attribute__((unused, section(".init"), visibility("hidden")))
void _init(void) {
  // This is the max size of "struct object" in
  // http://gcc.gnu.org/git/?p=gcc.git;a=blob;f=libgcc/unwind-dw2-fde.h;h=2bbc60a837c8e3a5d62cdd44f2ae747731f9c8f8;hb=HEAD
  // This buffer is used by libgcc. Unfortunately, it seems there are
  // no way to get the size of this struct.
  // Note that bionic/libc/arch-x86/bionic/crtbegin.S uses 24
  // (sizeof(void*) * 6) for this buffer, but we use 28 here because
  // it seems there can be one more element if
  // DWARF2_OBJECT_END_PTR_EXTENSION is enabled.
  static char buf[sizeof(void*) * 7];
  // Register the info in .eh_frame to libgcc. Though we are disabling
  // C++ exceptions, we want to do this for _Unwind_Backtrace.
  if (__register_frame_info != 0)
    __register_frame_info(__EH_FRAME_BEGIN__, buf);
  // Constructors are run for us, so we only need to register frame info.
}
// We only run destructors here if we are a dynamically linked library.
// Otherwise, libc will call it for us.
#ifdef CRT_SO
__attribute__((unused, section(".fini"), visibility("hidden")))
void _fini(void) {
  const structor_fn *iter = __FINI__;
  while (*++iter)
    (**iter)();
  if (__deregister_frame_info != 0)
    __deregister_frame_info(__EH_FRAME_BEGIN__);
}
#endif
#ifdef __x86_64__
void* __attribute__ ((const)) __nacl_read_tp () {
  return __nacl_irt_tls_get();
}
void* __nacl_add_tp(ptrdiff_t off) {
  return (char*) __nacl_irt_tls_get() + off;
}
#endif
// If we this is not the dynamic library case then we are expecting a
// _start and exit routine.
#ifndef CRT_SO
// Bionic ignores onexit, so this function must not be called.
static void onexit(void) {
  static const char msg[] = "onexit must not be called!\n";
  static const int kStderrFd = 2;
  write(kStderrFd, msg, sizeof(msg) - 1);
  exit(1);
}
#endif
#ifndef CRT_SO
void _start(unsigned **info) {
  int envc = (int)info[1];
  int argc = (int)info[2];
  char **argv = (char**)&info[3];
  char **envp = argv + argc + 1;
  unsigned *auxv = (unsigned *)(envp + envc + 1);
  static char buf[sizeof(void*) * 7];
#ifndef CRT_DYNAMIC
  __init_irt_from_auxv(auxv);
#endif
  _init();
  structors_array_t structors;
  memset(&structors, 0, sizeof(structors));
  structors.preinit_array = __PREINIT__;
  structors.init_array = __INIT__;
  structors.fini_array = __FINI__;
  __libc_init(&info[2], onexit, main, &structors);
}
#endif

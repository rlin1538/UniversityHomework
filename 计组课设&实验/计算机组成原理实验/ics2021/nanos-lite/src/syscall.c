#include "common.h"
#include "syscall.h"
#include "fs.h"

int mm_brk(uint32_t new_brk);

static inline uintptr_t sys_none() {
  return 1;
}

static inline uintptr_t sys_open(uintptr_t pathname, uintptr_t flags, uintptr_t mode) {
  //TODO();
  return fs_open((const char *)pathname,(int)flags,(int)mode);
}

static inline uintptr_t sys_write(uintptr_t fd, uintptr_t buf, uintptr_t len) {
  /*if (fd == 1 || fd == 2)
  {
    char* buff = (char*)buf;
    for (int i = 0; i < len; i++) _putc(buff[i]);
  }
  return len;*/
  return fs_write(fd,(void *)buf,len);
}

static inline uintptr_t sys_read(uintptr_t fd, uintptr_t buf, uintptr_t len) {
  //TODO();
  //fs_read(fd,(void *)buf,len);
  return fs_read((int)fd,(void *)buf,(size_t)len);
}

static inline uintptr_t sys_lseek(uintptr_t fd, uintptr_t offset, uintptr_t whence) {
  return fs_lseek((int)fd, (off_t)offset, (int)whence);
}

static inline uintptr_t sys_close(uintptr_t fd) {
  //TODO();
  return fs_close(fd);
}

static inline uintptr_t sys_brk(uintptr_t new_brk) {
  //TODO();
  return mm_brk(new_brk);	//pa3.2
}

_RegSet* do_syscall(_RegSet *r) {
  uintptr_t a[4];
  a[0] = SYSCALL_ARG1(r);
  a[1] = SYSCALL_ARG2(r);
  a[2] = SYSCALL_ARG3(r);
  a[3] = SYSCALL_ARG4(r);

  switch (a[0]) {
    case SYS_none:
      SYSCALL_ARG1(r) = sys_none();
      //Log("CALL SYS_none");
      break;
    case SYS_exit:
      _halt(a[2]);
      SYSCALL_ARG1(r) = 1;
      //Log("CALL SYS_exit");
      break;
    case SYS_write:
      SYSCALL_ARG1(r) = sys_write(a[1],a[2],a[3]);
     // Log("CALL SYS_write");
      break;
    case SYS_brk:
      SYSCALL_ARG1(r) = sys_brk(a[1]);
     // Log("CALL SYS_brk");
      break;
    case SYS_open:
      SYSCALL_ARG1(r) = sys_open(a[1],a[2],a[3]);
     // Log("CALL SYS_open");
      break;
    case SYS_read:
      SYSCALL_ARG1(r) = sys_read(a[1],a[2],a[3]);
     // Log("CALL SYS_read");
      break;
    case SYS_lseek:
      SYSCALL_ARG1(r) = sys_lseek(a[1],a[2],a[3]);
      //Log("CALL SYS_lseek");
      break;
    case SYS_close:
      SYSCALL_ARG1(r) = sys_close(a[1]);
      //Log("CALL SYS_close");
      break;
    default: panic("Unhandled syscall ID = %d", a[0]);
  }

  return NULL;
}

#include "common.h"
#include "fs.h"

#define DEFAULT_ENTRY ((void *)0x8048000)

extern void ramdisk_read(void *buf, off_t offset, size_t len);
extern void ramdisk_write(const void *buf, off_t offset, size_t len);
extern size_t get_ramdisk_size();

uintptr_t loader(_Protect *as, const char *filename) {
  //ramdisk_read(DEFAULT_ENTRY, 0, get_ramdisk_size());
  int fd = fs_open(filename,0,0);
  size_t len = fs_filesz(fd);
  printf("open file:%s\n",filename);
  
  void *va = DEFAULT_ENTRY;
  int page_num = len / PGSIZE + 1;
  
  for (int i = 0; i < page_num; i++)
  {
    void *pa = new_page();
    Log("Map va to pa: 0x%08x to 0x%08x", va, pa);
    _map(as,va,pa);
    fs_read(fd,pa,PGSIZE);
    va += PGSIZE;
  }
  
  fs_close(fd);
  return (uintptr_t)DEFAULT_ENTRY;
}

#include "nemu.h"

#define PMEM_SIZE (128 * 1024 * 1024)

#define pmem_rw(addr, type) *(type *)({\
    Assert(addr < PMEM_SIZE, "physical address(0x%08x) is out of bound", addr); \
    guest_to_host(addr); \
    })

uint8_t pmem[PMEM_SIZE];

paddr_t page_translate(vaddr_t vaddr);

/* Memory accessing interfaces */

uint32_t paddr_read(paddr_t addr, int len) {
  int mmio_id;
  mmio_id  = is_mmio(addr);
  if (mmio_id != -1)
  {
    return mmio_read(addr,len,mmio_id);
  }
  else
    return pmem_rw(addr, uint32_t) & (~0u >> ((4 - len) << 3));
}

void paddr_write(paddr_t addr, int len, uint32_t data) {
  int mmio_id;
  mmio_id = is_mmio(addr);
  if (mmio_id != -1)
  {
    mmio_write(addr,len,data,mmio_id);
  }
  else
    memcpy(guest_to_host(addr), &data, len);
}

uint32_t vaddr_read(vaddr_t addr, int len) {
  if(cpu.cr0.paging) {
        if (len != 1 && len != 2 && len != 4) {
            /* this is a special case, you can handle it later. */
            assert(0);
        }
        else {
            paddr_t paddr = page_translate(addr);
            return paddr_read(paddr, len);
        }
    }
    else
        return paddr_read(addr, len);
	//return paddr_read(addr, len);
}

void vaddr_write(vaddr_t addr, int len, uint32_t data) {
  if(cpu.cr0.paging) {
        if (len != 1 && len != 2 && len != 4) {
            /* this is a special case, you can handle it later. */
            assert(0);
        }
        else {
            paddr_t paddr = page_translate(addr);
            paddr_write(paddr, len,data);
        }
    }
    else
        paddr_write(addr, len,data);
	//  paddr_write(addr, len, data);
}

paddr_t page_translate(vaddr_t vaddr)
{
  if (cpu.cr0.protect_enable && cpu.cr0.paging)
  {
//    Log("Translate vaddr: 0x%x\n",vaddr);
    paddr_t pde_base = cpu.cr3.page_directory_base;
    PDE page_dir;
    page_dir.val = paddr_read((pde_base << 12) + ((vaddr >> 22) << 2), 4);

    if (!page_dir.present)
    {
      printf("Invalid page_dir:0x%x\n", page_dir.val);
      assert(0);
    }
    PTE page_table;
    page_table.val = paddr_read((page_dir.page_frame << 12) + ((vaddr >> 10) & 0xffc), 4);

    if (!page_table.present)
    {
      printf("Invalid page_table:0x%x\n", page_table.val);
      assert(0);
    }

    if (page_dir.accessed == 0)
    {
      page_dir.accessed = 1;
      paddr_write(page_dir.page_frame, 4, vaddr & 0xfffff000);
    }
    if (page_table.accessed == 0 || (page_table.dirty == 0 && page_table.read_write == 1))
    {
      page_table.accessed = 1;
      page_table.dirty = 1;
      paddr_write(page_table.page_frame, 4, vaddr & 0xfffff000);
    }
    return (page_table.page_frame << 12) + (vaddr & 0xfff);
  }
  else
    return vaddr;
}

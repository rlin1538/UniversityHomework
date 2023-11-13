#include "cpu/exec.h"
#include "memory/mmu.h"

void raise_intr(uint8_t NO, vaddr_t ret_addr) {
  /* TODO: Trigger an interrupt/exception with ``NO''.
   * That is, use ``NO'' to index the IDT.
   */

  union
  {
    GateDesc val;
    struct
    {
      uint32_t a, b;
    };
  } temp;

  temp.a = vaddr_read(cpu.idtr.base + NO * 8, 4);
  temp.b = vaddr_read(cpu.idtr.base + NO * 8 + 4, 4);
  if (temp.val.present)
    decoding.jmp_eip = (temp.val.offset_15_0 & 0xffff) | ((temp.val.offset_31_16 & 0xffff) << 16);
  else
    assert(0);

  decoding.is_jmp = 1;
  rtl_push(&cpu.eflags.val);
  t1 = cpu.cs;
  rtl_push(&t1);
  rtl_push(&ret_addr);
}

void dev_raise_intr() {
}

#include "cpu/exec.h"

void diff_test_skip_qemu();
void diff_test_skip_nemu();

make_EHelper(lidt) {
  cpu.idtr.limit = vaddr_read(id_dest->addr, 2);
  if (decoding.is_operand_size_16)
    cpu.idtr.base = vaddr_read(id_dest->addr + 2, 3);
  else
    cpu.idtr.base = vaddr_read(id_dest->addr + 2, 4);

  print_asm_template1(lidt);
}

make_EHelper(mov_r2cr) {
  if (id_dest->reg == R_EAX)
    cpu.cr0.val = id_src->val;
  else if (id_dest->reg == R_EBX)
    cpu.cr3.val = id_src->val;
  else
    assert(0);

  print_asm("movl %%%s,%%cr%d", reg_name(id_src->reg, 4), id_dest->reg);
}

make_EHelper(mov_cr2r) {
  if (id_src->reg == R_EAX)
    operand_write(id_dest,&cpu.cr0.val);
  else if (id_src->reg == R_EBX)
    operand_write(id_dest,&cpu.cr3.val);
  else
    assert(0);

  print_asm("movl %%cr%d,%%%s", id_src->reg, reg_name(id_dest->reg, 4));

#ifdef DIFF_TEST
  diff_test_skip_qemu();
#endif
}

make_EHelper(int) {
  raise_intr(id_dest->val,decoding.seq_eip);

  print_asm("int %s", id_dest->str);

#ifdef DIFF_TEST
  diff_test_skip_nemu();
#endif
}

make_EHelper(iret) {
  rtl_pop(&t0);
  decoding.is_jmp=1;
  decoding.jmp_eip=t0;

  rtl_pop(&t0);
  cpu.cs=t0;

  rtl_pop(&t0);
  cpu.eflags.val=t0;
//  printf("finish iret to %08x\ncpu.eax= %d\n",decoding.jmp_eip,cpu.eax);
  print_asm("iret");
}

uint32_t pio_read(ioaddr_t, int);
void pio_write(ioaddr_t, int, uint32_t);

make_EHelper(in) {
  t2 = pio_read(id_src->val,id_src->width);
  operand_write(id_dest,&t2);

  print_asm_template2(in);

#ifdef DIFF_TEST
  diff_test_skip_qemu();
#endif
}

make_EHelper(out) {
  pio_write(id_dest->val,id_src->width,id_src->val);

  print_asm_template2(out);

#ifdef DIFF_TEST
  diff_test_skip_qemu();
#endif
}

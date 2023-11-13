#include "cpu/exec.h"

make_EHelper(test) {
  rtl_and(&t2, &id_dest->val, &id_src->val);
  cpu.eflags.CF = 0;
  cpu.eflags.OF = 0;

  rtl_update_ZFSF(&t2, id_dest->width);

  print_asm_template2(test);
}

make_EHelper(and) {
  rtl_and(&t2, &id_dest->val, &id_src->val);
  cpu.eflags.CF = 0;
  cpu.eflags.OF = 0;
  operand_write(id_dest, &t2);

  rtl_update_ZFSF(&t2, id_dest->width);
  
  print_asm_template2(and);
}

make_EHelper(xor) {
  rtl_xor(&t2,&id_dest->val,&id_src->val);
  operand_write(id_dest,&t2);
  cpu.eflags.CF=0;
  cpu.eflags.OF=0;
  rtl_update_ZFSF(&t2,id_dest->width);

  print_asm_template2(xor);
}

make_EHelper(or) {
  rtl_or(&t2,&id_dest->val,&id_src->val);
  cpu.eflags.CF = 0;
  cpu.eflags.OF = 0;
  operand_write(id_dest, &t2);

  rtl_update_ZFSF(&t2, id_dest->width);

  print_asm_template2(or);
}

make_EHelper(sar) {
  rtl_sext(&id_src->val,&id_src->val,id_src->width);
  rtl_sar(&t2,&id_dest->val,&id_src->val);
  operand_write(id_dest, &t2);

  rtl_update_ZFSF(&t2, id_dest->width);
  // unnecessary to update CF and OF in NEMU

  print_asm_template2(sar);
}

make_EHelper(shl) {
  rtl_shl(&t2,&id_dest->val,&id_src->val);
  operand_write(id_dest, &t2);

  rtl_update_ZFSF(&t2, id_dest->width);
  // unnecessary to update CF and OF in NEMU

  print_asm_template2(shl);
}

make_EHelper(shr) {
  rtl_shr(&t2,&id_dest->val,&id_src->val);
  operand_write(id_dest, &t2);

  rtl_update_ZFSF(&t2, id_dest->width);
  // unnecessary to update CF and OF in NEMU

  print_asm_template2(shr);
}

make_EHelper(setcc) {
  uint8_t subcode = decoding.opcode & 0xf;
  rtl_setcc(&t2, subcode);
  operand_write(id_dest, &t2);

  print_asm("set%s %s", get_cc_name(subcode), id_dest->str);
}

make_EHelper(not) {
  rtl_mv(&t2,&id_dest->val);
  rtl_not(&t2);
  operand_write(id_dest,&t2);

  print_asm_template1(not);
}

make_EHelper(rol) {
  rtl_mv(&t2,&id_dest->val);
  for (t0 = 0; t0 < id_src->val; t0++)
  {
    rtl_msb(&t1,&t2,id_dest->width);
    rtl_shli(&t2,&t2,1);
    rtl_add(&t2,&t2,&t1);
    rtl_set_CF(&t1);
  }
  operand_write(id_dest,&t2);
  
  
  print_asm_template2(rol);
}

#include "monitor/watchpoint.h"
#include "monitor/expr.h"
#include "nemu.h"

#include <stdlib.h>

#define NR_WP 32

static WP wp_pool[NR_WP];
static WP *head, *free_;

void init_wp_pool() {
  int i;
  for (i = 0; i < NR_WP; i ++) {
    wp_pool[i].NO = i;
    wp_pool[i].next = &wp_pool[i + 1];
  }
  wp_pool[NR_WP - 1].next = NULL;

  head = NULL;
  free_ = wp_pool;
}

/* TODO: Implement the functionality of watchpoint */
WP *new_wp()
{
  if (free_ == NULL)
    assert(0);

  WP *temp;
  temp = free_;
  free_ = free_->next;

  temp->next = head;
  head = temp;

  return temp;
}
bool free_wp(int num)
{
  WP *p;
  WP *pre;

  for (p = head; p != NULL; p = p->next)
  {
    if (p->NO == num)
    {
      if (p == head)
        head = head->next;
      else
        pre->next = p->next;
      p->next = free_;
      free_ = p;
      return true;
    }
    pre = p;
  }

  return false;
}

int set_watchpoint(char *e) //给予一个表达式e，构造以该表达式为监视目标的监视点，并返回编号
{
  WP *temp;
  temp=new_wp();

  if (temp->expr != NULL)
    free(temp->expr);
  temp->expr = (char *)malloc(sizeof(char) * strlen(e) + 1);
  strcpy(temp->expr, e);
  bool isSuccess;
  temp->old_val = expr(e, &isSuccess);

  printf("Set watchpoint #%d\nexpr      = %s\nold value = 0x%08x\n",temp->NO,temp->expr,temp->old_val);

  return temp->NO;
}
bool delete_watchpoint(int NO) //给予一个监视点编号，从已使用的监视点中归还该监视点到池中
{
  return free_wp(NO);
}

void list_watchpoint(void) //显示当前在使用状态中的监视点列表
{
  WP* p;
  p=head;

  printf("NO Expr               Old Value\n");
  while (p!=NULL)
  {
    printf("%-2d%-20s0x%x\n",p->NO,p->expr,p->old_val);
    p=p->next;	
  }
  return;
}

WP *scan_watchpoint(void) //扫描所有使用中的监视点，返回触发的监视点指针，若无触发返回NULL
{
  WP *temp=NULL;
  WP *p;
  bool t;
  p = head;
  static vaddr_t cur_eip = 0x100000;

  while (p != NULL)
  {
    p->new_val = expr(p->expr, &t);
    if (p->new_val != p->old_val)
    {
      printf("Hit watchpoint %d at address 0x%08x\nexpr      = %s\nold value = 0x%08x\nnew value = 0x%08x\nprogram paused\n", p->NO,cur_eip,p->expr,p->old_val,p->new_val);
      p->old_val = p->new_val;
      temp=p;
    }

    p = p->next;
  }
  cur_eip=cpu.eip;

  return temp;
}


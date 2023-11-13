#include "monitor/watchpoint.h"
#include "monitor/expr.h"
#include "nemu.h" //����cpu.eip

#define NR_WP 32

static WP wp_pool[NR_WP];
static WP *head, *free_;

void init_wp_pool()
{
  int i;
  for (i = 0; i < NR_WP; i++)
  {
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

int set_watchpoint(char *e) //����һ�����ʽe�������Ըñ��ʽΪ����Ŀ��ļ��ӵ㣬�����ر��
{
  WP *temp;
  temp=new_wp();

  if (temp->expr != NULL)
    free(temp->expr);
  temp->expr = (char *)malloc(sizeof(char) * strlen(e) + 1);
  strcpy(temp->expr, e);
  bool isSuccess;
  temp->old_val = expr(e, &isSuccess);

  printf("Set watchpoint #%d\nexpr      = %s\nold value = 0x%x\n",temp->NO,temp->expr,temp->old_val);

  return temp->NO;
}
bool delete_watchpoint(int NO) //����һ�����ӵ��ţ�����ʹ�õļ��ӵ��й黹�ü��ӵ㵽����
{
  return free_wp(NO);
}

void list_watchpoint(void) //��ʾ��ǰ��ʹ��״̬�еļ��ӵ��б�
{
  WP* p;
  p=head;

  printf("NO Expr                Old Value\n");
  while (p!=NULL)
    printf("%-3d%-20s0x%x\n",p->NO,p->expr,p->old_val);
    p=p->next;
  return;
}

WP *scan_watchpoint(void) //ɨ������ʹ���еļ��ӵ㣬���ش����ļ��ӵ�ָ�룬���޴�������NULL
{
  WP *temp=NULL;
  WP *p;
  bool t;
  p = head;
  static vaddr_t cur_eip=0x100000;

  while (p != NULL)
  {
    p->new_val = expr(p->expr, &t);
    if (p->new_val != p->old_val)
    {
      printf("Hit watchpoint %d at address 0x%08x\nexpr      = %s\nold value = 0x%08x\nnew value = 0x%08x\nprogram paused\n", 
      p->NO,cur_eip,p->expr,p->old_val,p->new_val);
      p->old_val = p->new_val;
      temp=p;
    }

    p = p->next;
  }
  cur_eip=cpu.eip;

  return temp;
}

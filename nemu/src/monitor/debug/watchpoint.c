#include "monitor/watchpoint.h"
#include "monitor/expr.h"

#define NR_WP 32

static WP wp_list[NR_WP];
static WP *head, *free_;

void init_wp_list() {
	int i;
	for(i = 0; i < NR_WP; i ++) {
		wp_list[i].NO = i;
		wp_list[i].next = &wp_list[i + 1];
	}
	wp_list[NR_WP - 1].next = NULL;

	head = NULL;
	free_ = wp_list;
}

WP* new_wp()
{	
	if (free_ == NULL)
	{
		printf("All watch points have been used!\n");
		return NULL;
	}
	WP* tmp = free_;
	free_ = free_ -> next;
	tmp->next = head;
	head = tmp;
	return tmp;
}

bool free_wp(int num)
{
	if (head == NULL)
	{
		printf("No watch point num %d.\n", num);
		return 0;
	}
	WP* tmp;
	if (head->NO == num)
	{//链表中第一个节点就是需要删除的监视点
		tmp = head;
		head = head->next;
		tmp->next = free_->next;//将删除的监视点插入到free表中
		free_->next = tmp;
		return 1;
	}
	tmp = head;
	//枚举之后的每一个监视点
	while (tmp->next != NULL)
		if (tmp->next->NO == num)
		{
			WP *wpToDel = tmp->next;
			tmp->next = wpToDel->next;
			wpToDel->next = free_->next;//将删除的监视点插入到free表中
			free_->next = wpToDel;
			return 1;
		}
	printf("No watch point num %d.\n", num);
	return 0;
}

int check_wp()
{
	//check every watch point to see whether it has changed.
	WP* wp = head;
	int count = 0;
	while (wp != NULL)
	{
		bool success = true;
		uint32_t newValue = expr(wp->expr, &success);
		if (newValue != wp->oldValue)
		{
			printf("Hardware watch point %d: %s\n", wp->NO, wp->expr);
			printf("Old value = %u\n", wp->oldValue);
			printf("New value = %u\n\n", newValue);
			wp->oldValue = newValue;
			count++;
		}
		wp = wp->next;
	}
	return count;
}

void show_wp()
{
	printf("Num     Type		  What\n");
	WP* wp = head;
	while (wp != NULL)
	{
		printf("%3d     watchpoint        %s\n", wp->NO, wp->expr);
		wp = wp->next;
	}
}

/* TODO: Implement the functionality of watchpoint */



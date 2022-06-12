//
// Created by ChrisWhite on 2022/6/11.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct ListNode {
    int data;
    struct ListNode *next;
} ListNode;

typedef struct LinkList {
    ListNode head; //虚拟头节点 中间指针可以指向它 待插入索引值是哪位就走几步
    int length;
} LinkList;

//初始化链表节点
ListNode *init_listnode(int val) {
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));
    p->data = val;
    p->next = NULL;
    return p;
}

//插入节点
int insert(LinkList *l, int ind, int val) {
    if (l == NULL) return 0;
    if (ind < 0 || ind > l->length) return 0;
    ListNode *p = &(l->head), *node = init_listnode(val);
    while(ind--) {
        p = p->next;
    }
    node->next = p->next;
    p->next = node;
    l->length += 1;
    return 1;
}

//销毁链表节点
void clear_listnode(ListNode *node) {
    if(node == NULL) return;
    free(node);
    return;
}

//删除节点
int erase(LinkList *l, int ind) {
    if (l == NULL) return 0;
    if (ind < 0 || ind >= l->length) return 0;
    ListNode *p = &(l->head), *q;
    while (ind--) {
        p = p->next;
    }
    //p已经指向待删除节点的前一节点
    q = p->next->next; //q指向待删除节点的下一节点
    clear_listnode(p->next);
    p->next = q;
    l->length -= 1;
    return 1;
}

//初始化链表
LinkList  *init_linklist() {
    LinkList  *l = (LinkList *)malloc(sizeof(LinkList));
    l->head.next = NULL;
    l->length = 0;
    return l;
}

//销毁链表
void clear_linklist(LinkList *l) {
    if (l == NULL) return;
    ListNode *p = l->head.next, *q;
    while (p) { //C中NULL是一个宏为0
        q = p->next;
        clear_listnode(p);
        p = q;
    }
    free(l);
    return;
}

void output(LinkList *l) {
    printf("LinkList(%d):", l->length);
    for (ListNode *p = l->head.next; p; p = p->next) {
        printf("%d -> ", p->data);
    }
    printf("NULL\n");
    return;
}

#define MAX_OP 30

int main(void)
{
    srand(time(0));

    LinkList *l = init_linklist();
    for (int i = 0; i < MAX_OP; i++) {
        int op = rand() % 3;
        int ind = rand() % (l->length + 1); //没办法向index为length + 1处插入
        int val = rand() % 100;
        switch (op) {
            case 0:
            case 1: {
                printf("insert %d at %d to LinkList = %d\n",
                       val, ind, insert(l, ind, val));
            } break;
            case 2: {
                printf("erase item at %d from LinkList = %d\n",
                       ind, erase(l, ind));
            } break;
        }
        output(l);
        printf("\n");
    }
    clear_linklist(l);
    return 0;
}
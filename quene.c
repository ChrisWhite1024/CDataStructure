//
// Created by ChrisWhite on 2022/6/13.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Quene {
    int *data;
    int head, tail;
    int length, cnt;
} Quene;

Quene *init(int n) {
    Quene *q = (Quene *)malloc(sizeof(Quene)); //malloc不会设置内存为0，calloc会设置分配的内存为0
    q->data = (int *)calloc(n, sizeof(int));
    q->head = q->tail = q->cnt = 0; //尾指针指向第一个无数据的区域，尾指针减去头指针为队列中元素数量
    q->length = n;
    return q;
}

int empty(Quene *q) {
    return q->cnt == 0;
}

int front(Quene *q) {
    return q->data[q->head];
}

int push(Quene *q, int val) {
    if (q == NULL) return 0;
    if (q->cnt == q->length) return 0;
    q->data[q->tail++] = val;
    if (q->tail == q->length) q->tail -= q->length;
    q->cnt += 1;
    return 1;
}

int pop(Quene *q) {
    if (q == NULL) return 0;
    if (empty(q)) return 0;
    q->head++;
    if (q->head == q->length) q->head -= q->length;
    q->cnt -= 1;
    return 1;
}

void clear(Quene *q) {
    if(q == NULL) return;
    free(q->data);
    free(q);
    return;
}

void output(Quene *q) {
    printf("quene = [");
    for (int i = q->head, j = 0; j < q->cnt; j++) {
        int ind = (i + j) % q->length;
        printf(" %d", q->data[ind]);
    }
    printf("]\n");
}

int main(void)
{
    srand(time(0));
    #define MAX_OP 20
    Quene *q = init(MAX_OP);
    for (int  i = 0; i < MAX_OP; i++) {
        int val = rand() % 100, op = rand() % 2;
        switch (op) {
            case 0: {
                printf("push %d to quene = ", val);
                printf("%d\n", push(q, val));
            } break;
            case 1: {
                printf("pop %d from quene = ", front(q));
                printf("%d\n", pop(q));
            } break;
        }
        output(q);
    }
    printf("head : %d, tail : %d, count : %d\n", q->head, q->tail, q->cnt);
    for (int i = 0; i < MAX_OP; i++) {
        int val = rand() % 100;
        printf("push %d to quene = %d\n", val, push(q, val));
    }
    output(q);
    return 0;
}
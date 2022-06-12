//
// Created by ChrisWhite on 2022/6/11.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Vector {
  int *data;
  int size, length;
} Vector;

//初始化
Vector *init(int n) {
    Vector *vec = (Vector *)malloc(sizeof(Vector));
    vec->data = (int *)malloc(sizeof(int) * n);
    vec->size = n;
    vec->length = 0;
    return vec;
}

//清除
void clear(Vector *vec) {
    if (vec == NULL) return;
    free(vec->data);
    free(vec);
    return;
}

//插入
int insert(Vector *vec, int ind, int val) {
    if (vec == NULL) return 0; //判断输入合法性
    if (vec->length == vec->size) {
        if (!expand(vec)) return 0;
        printf("expand vector size to %d success\n", vec->size);
    }
    if (ind < 0 || ind > vec->length) return 0;
    for (int i = vec->length; i > ind; i--) { //index为length的位置是空的
        vec->data[i] = vec->data[i - 1];
    }
    vec->data[ind] = val;
    vec->length += 1;
    return 1;
}

//删除
int erase(Vector *vec, int ind) {
    if (vec == NULL) return 0;
    if (vec->length == 0) return 0;
    if (ind < 0 || ind >= vec->length) return 0;
    for (int i = ind + 1; i < vec->length; i++) {
        vec->data[i - 1] = vec->data[i];
    }
    vec->length -= 1;
    return 1;
}

//输出
void output(Vector *vec) {
    printf("Vector(%d) = [", vec->length);
    for (int i = 0; i < vec->length; i++) {
        if (i != 0) printf(", ");
        printf("%d", vec->data[i]);
    }
    printf("]\n");
    return;
}

//扩容
int expand(Vector *vec) {
    int new_size = vec->size *= 2;
    int *p = (int *)realloc(vec->data, sizeof(int) * new_size); //若不判断realloc失败会造成内存泄漏
    if (p == NULL) return 0;
    vec->size = new_size;
    vec->data = p;
    return 1;
}

int main(void)
{
    srand(time(0));
    #define MAX_OP 20
    Vector *vec = init(1);
    int op, ind, val;
    for (int i = 0; i < MAX_OP; i++) {
        op = rand() % 2;
        ind = rand() % (vec->length + 3); //生成非法数据
        val = rand() % 100;
        switch (op) {
            //case 2:
            //case 3: 按概率生成
            case 0: {
                printf("insert %d at %d to vector = %d\n", val, ind, insert(vec, ind, val));
            } break;
            case 1: {
                printf("erase item at %d from vector = %d\n", ind, erase(vec, ind));
            } break;
        }
        output(vec);
    }
    return 0;
}
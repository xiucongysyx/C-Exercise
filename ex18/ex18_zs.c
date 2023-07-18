#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void die(const char *message)
{
    if(errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }

    exit(1);
}

typedef int (*compare_cb)(int a, int b); //定义了一个函数指针

int *bubble_sort(int *number, int count, compare_cb cmp) //冒泡排序函数
{
    int temp = 0;
    int i = 0;
    int j = 0;
    int *target = malloc(count * sizeof(int)); //给指针target分配空间，用于存储传入的数据。

    if(!target) die("Memory error.");

    memcpy(target, number, count * sizeof(int)); //使用memcpy函数将指针name中的数据传递给指针target

    for(i = 0; i < count; i++) { //使用冒泡排序为所有的数据排序
        for(j = 0; j < count; j++) {
            if(cmp(target[j], target[j+1]) > 0) {
                    temp = target[j+1];
                    target[j+1] = target[j];
                    target[j] = temp;
            }
        }
    }
    return target; //返回值为一个指针,*target是第一个数据,那么target就是该组数据第一个数据的地址
}

int sorted_order(int a, int b) //如果cmp是这个函数的话，那么就是从小到大排序。
{
    return a - b;
}

int reverse_order(int a, int b) //如果cmp是这个函数的话就是逆向排序。
{
    return b - a;
}

int strange_order(int a, int b) //如果cmp是这个函数的话，就是奇怪排序。
{
    if(a == 0 || b == 0) { //如果a和b都不为0，则返回0，否则返回a和b的余数。
        return 0;
    } else {
        return a % b;
    }
}

void test_sorting(int *numbers, int count, compare_cb cmp) //测试函数，用于测试程序
{
    int i = 0;
    int *sorted = bubble_sort(numbers, count, cmp); //首先对输入的数据冒泡排序，规则基于cmp。
    if(!sorted) die("Failed to sort as requested.");

    printf("sorting start.");
    for(i = 0; i < count; i++) { //然后将排序后的数据打印出来
        printf("%d ", sorted[i]);
    }
    printf("sorting end.\n");

    free(sorted);
}

int main(int argc, char *argv[])
{
    if(argc < 2) die("USAGE: ex18 4 3 1 5 6");

    int count = argc - 1; //输入参数的个数为argc-1
    int i = 0;
    char **inputs = argv + 1; //

    int *numbers = malloc(count * sizeof(int));
    if(!numbers) die("Memory error.");
    for(i = 0; i < count; i++) {
        numbers[i] = atoi(inputs[i]);
    }

    test_sorting(numbers, count, sorted_order);
    test_sorting(numbers, count, reverse_order);
    test_sorting(numbers, count, strange_order);

    free(numbers);

    return 0;
}
                   
                   

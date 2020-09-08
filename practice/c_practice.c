/*
compile
gcc -g -Wall -pedantic -std=gnu99 .\practice\c_practice.c -o main
*/
#include <stdio.h>
#include <stdbool.h>
#include "c_practice.h"

// Example: find intersection of two rectangles
float min(float f1, float f2)
{
    // compare f1 to f2
    if (f1 < f2)
    {
        // if f1 is smaller than f2, then f1 is your answer
        return f1;
    }
    else
    {
        // otherwise, f2 is your answer
        return f2;
    }
}

float max(float f1, float f2)
{
    // compare f1 to f2
    if (f1 > f2)
    {
        // if f1 is larger than f2, then f1 is your answer
        return f1;
    }
    else
    {
        // otherwise, f2 is your answer
        return f2;
    }
}

// To find the intersection of two rectangles, r1 and r2:
rect_t intersection(rect_t r1, rect_t r2)
{
    // Make a rectangle (called ans) with
    rect_t ans;
    // left: maximum of r1's left and r2's left
    ans.left = max(r1.left, r2.left);
    // bottom: maximum or r1's bottom and r2's bottom
    ans.bottom = max(r1.bottom, r2.bottom);
    // right: minimum of r1's right and r2's right
    ans.right = min(r1.right, r2.right);
    // top: minimum of r1's top and r2's top
    ans.top = min(r1.top, r2.top);
    // The rectangle called ans is your answer
    return ans;
}

// Example: swap two values
int zip1 = 15213;
int zip2 = 98195;

void call_swap()
{
    swap(&zip1, &zip2);
    printf("zip1=%d, zip2=%d\n", zip1, zip2);
}

void swap(int *xp, int *yp)
{
    int t0 = *xp;
    int t1 = *yp;
    *xp = t1;
    *yp = t0;
}

// Example: factorial fucntion
// sfact(5) = 5 x 4 x 3 x 2 x 1
void s_helper(int x, int *accum)
{
    if (x < 1)
        return;
    else
    {
        int z = *accum * x;
        printf("%d = %d x %d\n", z, *accum, x);
        *accum = z;
        s_helper(x - 1, accum);
    }
}

int sfact(int x)
{
    int val = 1;
    s_helper(x, &val);
    return val;
}

// Example: is N a prime number
bool isPrimeNumber(int n){
    if (n <= 1) {
        return FALSE;
    }
    for (int i = 2; i < n; i++) {
        if (n % i == 0) {
            return FALSE;
        }
    }
    return TRUE;
}

void left_shift_test(){
    int addr, mask, pattern, pattern_comp;
    addr = 0x6000000;
    mask = 0x4;
    pattern = 0;
    pattern_comp = ~pattern;
    printf("write 0x%x @ add 0x%x\n", pattern, addr);
    for (int i = 0; i < 30; i++) {
        printf("write 0x%x @ 0x%x\n", pattern_comp, addr | mask);
        mask = mask << 1;
    }
}

/*
simple task scheduler
sContext (task context) keeps track of 2 task groups
task group1: array of 2 functions (each entry a function pointer)
    const Func_t *funcs;    // funcs is pointer to function pointers, with address fixed (constant)
task group2: 1 function pointer
    Func_t funcs;           // func is function pointer
use sContext to run the tasks of each task group
*/
bool group1task1(){
    printf("this is group 1 task 1\n");
    return true;
}
bool group1task2(){
    printf("this is group 1 task 2\n");
    return true;
}
bool group2task1(){
    printf("this is group 2 task 1\n");
    return true;
}
const Func_t tasks1[2] = {group1task1, group1task2};
const Func_t tasks2 = group2task1;

static Context_t sContext;

void init(){
    sContext.taskGroup1.funcs = tasks1;
    sContext.taskGroup2.func = tasks2;
}

void simple_scheduler() {
    init();
    sContext.taskGroup1.funcs[0]();
    sContext.taskGroup1.funcs[1]();
    sContext.taskGroup2.func();
}

// test i-- and --i
// i--: 3, 2, 1, 0 (compare then subtract 1)
// --i: 3, 2, 1 (subtract 1 then compare)
void decrement() {
    int i = 4;
    while (--i > 0) {
        printf("i: %d\n", i);
    }
}

int main(){
    //simple_scheduler();
    decrement();
    return 0;
}
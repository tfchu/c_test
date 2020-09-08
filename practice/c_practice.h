struct rect_tag
{
    float left;
    float bottom;
    float top;
    float right;
};
typedef struct rect_tag rect_t;

rect_t intersection(rect_t r1, rect_t r2); 

void swap(int *xp, int *yp);

int sfact(int x);

//typedef char bool;
#ifndef FALSE
    #define FALSE 0
#endif

#ifndef TRUE
    #define TRUE 1
#endif
bool isPrimeNumber(int N);
void left_shift_test();

// simple task scheduler
typedef bool (*Func_t)();

typedef struct TaskGroup1_t {
    const Func_t *funcs;
} TaskGroup1_t;

typedef struct TaskGroup2_t {
    Func_t func;
} TaskGroup2_t;

typedef struct Context_t {
    TaskGroup1_t taskGroup1;
    TaskGroup2_t taskGroup2;
} Context_t;

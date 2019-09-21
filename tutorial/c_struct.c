#include <stdio.h>

struct s1{
    char c;
    int i[2];
    double v;
} *p1;

struct s2{
    double v;
    int i[2];
    char c;
} *p2;

struct s3{
    double v;
    int i[2];
    char c;
};

void structure_size_test(){

    printf("size of s1 is %lu bytes\n", sizeof(*p1));
    printf("starting address of s1 is %p\n", p1);
    printf("starting address of s1.c is %p\n", &p1->c);
    printf("starting address of s1.i[0] is %p\n", &p1->i[0]);
    printf("starting address of s1.i[1] is %p\n", &p1->i[1]);
    printf("starting address of s1.v is %p\n", &p1->v);

    printf("size of s2 is %lu bytes\n", sizeof(*p2));
    //printf("starting address of s2 is %lu\n", p2);
    printf("starting address of s2.v is %p\n", &p2->v);
    printf("starting address of s2.i[0] is %p\n", &p2->i[0]);
    printf("starting address of s2.i[1] is %p\n", &p2->i[1]);
    printf("starting address of s2.c is %p\n", &p2->c);

    // struct s3 s;
    // s.v = 3.1415;
    // s.i[0] = 1;
    // s.i[1] = 2;
    // s.c = 'a';    
    // struct s3 *p = &s;
    // printf("size of s is %lu bytes\n", sizeof(*p));
    // printf("starting address of s is %p\n", p);
    // printf("starting address of s.v is %p\n", &p->v);
    // printf("starting address of s.i[0] is %p\n", &p->i[0]);
    // printf("starting address of s.i[1] is %p\n", &p->i[1]);
    // printf("starting address of s.c is %p\n", &p->c);
}

// struct declaration
struct Point{
    int x; 
    int y;  // or int x, y;
} pt;       // variable p1 is declared with struct declaration

struct Point2{
    int x, y;
};

void use_struct(){
    // pt = {0, 1}; // this does not work, declare and initialization must be done together

    struct Point2 p2 = {.x = 0, .y = 1};    // variable p2 is declared separately + designated initialization 
    printf("%d\n", p2.x);
    printf("%d\n", p2.y);

    struct Point *ptr = &p2;    // struct pointer
    printf("%d\n", ptr->x);             // ptr->x is shorthand for (*ptr).x
    printf("%d\n", ptr->y);
}
#include <stdio.h>
#include <string.h>
#include "c_tutorial.h"

// #define is in header file (note. without ";")
void preprocessor_test(){
    bool logic;
    logic = TRUE;
    printf("True is %d\n", logic);
    logic = FALSE;
    printf("False is %d\n", logic);
}

void data_type_long_test(){
    long int i;
    printf("size is %lu", sizeof(i));
}

/*
 * Unary arithmetic: next pointer address depends on type
 * only +, -, ~, !
 */
void pointer_test(){
	char *ptr;	// type char 1 bytes
	char str[] = "Hello World";
	ptr = str; 	// or &str
	printf("str is @%p\n", str);	//000000000022FE04
	printf("pointer arithmetic: %p %p\n", ptr, ptr+1);	//000000000022FE04 000000000022FE05 (+1 is 1 byte)

    int *p;		// type int 4 bytes
    int arr[5] = {5, 4, 3, 2, 1};
    p = arr;	// or &arr
    printf("arr is @%p\n", arr);	//e.g. @000000000022FDF0
	printf("pointer arithmetic: %p %p\n", p, p+1);		//e.g. 000000000022FDF0 000000000022FDF4 (+1 is 4 byte)
}

// pointer to pointer
void pointer_test1(){
	int i;
	int *ptr;
	int **ptrptr; 	// pointer to a pointer
	i = 284;
	ptr = &i;
	ptrptr = &ptr;

	printf("%p\n", ptr);	// 000000000022FE14
	printf("%d\n", *ptr);	// 284
	printf("%p\n", ptrptr);	// 000000000022FE08
	printf("%p\n", *ptrptr);	// 000000000022FE14 (use %p to force format the value to 8-byte hex)
}

// return pointer
int * pointer_test2(){
    int i;
    int *ptr;
    i = 284;
    ptr = &i;
    return ptr;
}

void run_pointer_test2(){
    int *ptr;
    ptr = pointer_test2();

	printf("%p\n", ptr);    // 000000000022FDD4
	printf("%d\n", *ptr);   // 284
}

// relationship between array and pointer
void array_test(){
	int arr[5] = {5, 4, 3, 2, 1};	// or arr[0] = 5, arr[1] = 4, ... 
	int *ptr;
	int i;

	ptr = arr;	// or ptr = &arr, or ptr = &arr[0]
    // print element address with arr
    // output: 000000000022FDF0, 000000000022FDF4, 000000000022FDF8, 000000000022FDFC, 000000000022FE00
    // if using arr[i], then print int 5, 4, 3, 2, 1 formatted as 8-byte like pointer
    for (i = 0; i < 5; i++){
        printf("%p\n", &arr[i]);    
    }   
	// print element values with variable arr
	for (i = 0; i < 5; i++){
		printf("%d\n", arr[i]);
	}   // 5 4 3 2 1

	printf("array address: ptr = %p, arr = %p\n", ptr, arr);	// 000000000022FDF0, 000000000022FDF0

	// print element address with pointer
	for (i = 0; i < 5; i++){
		/* output is NOT 22FDF0, 22FDF1, 22FDF2, 22FDF3, 22FDF4
		   output is 22FDF0, 22FDF4, 22FDF8, 22FDFC, 22FE00, increase by 4 as int is 4 bytes
		   so do not use "ptr + i*4"
		   if using short (2 byte), then increase by 2 (22FDF0, 22FDFD2, ...) */
		printf("%p\n", ptr + i);
	}
	// print element values with pointer
	for (i = 0; i < 5; i++){
		printf("%d\n", *(ptr + i)); 
	}
}

/*
 * string is an array of char. end char is "\0"
 * 1. for &: if operand is [] type, & is not evaluated
 * 		e.g. char str[];
 * 		str and &str are the same because & is not evaluated
 * 2. ptr = &str: a pointer ptr to pointer &str
 * 		addresses of ptr and &str are different
 */
void string_test(){
    // same as char *str = "Hello World";
	char *ptr;
	char str[] = "Hello World";
	ptr = str; // or ptr = &str

    int i;
	// str and &str are the same
	printf("%p %p\n", str, &str);	//0x7fff5d5d445c 0x7fff5d5d445c

    // print string
    printf("%s\n", ptr);    //Hello World

    // print string
    for (i = 0; i < strlen(str); i++){
        printf("%c\n", str[i]);
    }
}

/*	ptr				str
 *  (char *)		(char [])
 *  ptr type: (char *), pointer to char
 *  str type: (char []), array of char
 */
void sizeof_test(){
	char *ptr;
	char str[] = "Hello World";
	ptr = str;
	printf("%lu\n", sizeof(ptr));    // 8 (bytes) (8 bytes for 64-bit system)
    printf("%lu\n", sizeof(str));    // 12 (bytes) (str is 11 char + "\0", so 12 characters = 12 bytes)
    printf("%lu\n", strlen(str));    // 11 (chars), str is 11 characters withtout "\0"
}

/*
 * sizeof operator
 */
struct A{
	int x, y, z;
};

struct B;	// forward declaration (no definition)

void sizeof_struct_test1(){
	printf("%lu\n", sizeof(struct A));   // 12 (3 int, 4 bytes each)

	// declaration
	struct A a;		// *a is also ok
    a.x = 3; a.y = 4; a.z = 5;
	// &a has the same value as &a.x, but unable to use &a to get values. &a is not a pointer
	printf("%lu\n", sizeof(&a));     // 8 (8 bytes for 64-bit system)
    printf("%lu\n", sizeof(a));      // 12 (size of struct A = 12 bytes)
	printf("%p\n", &a);             // 000000000022FE14
    printf("%p\n", &a.x);           // 000000000022FE14
    printf("%p\n", &a.y);           // 000000000022FE18
    printf("%p\n", &a.z);           // 000000000022FE1C
    printf("%d\n", *(&a));          // 2293232 or 0x22FDF0, same for *(&a+1), *(&a+2). what is this? 

    // what is *ptr, *(&ptr), ptr
    struct A *ptr;
    ptr = &a; 
	printf("%lu\n", sizeof(ptr));    // 8 (8 bytes for 64-bit system)
    printf("%lu\n", sizeof(&ptr));   // 8 (8 bytes for 64-bit system) 
    printf("%lu\n", sizeof(*ptr));   // 12 (size of struct A = 12 bytes)
	printf("%p\n", ptr);            // 000000000022FE14
    printf("%p\n", &ptr->x);        // 000000000022FE14
    printf("%p\n", &ptr->y);        // 000000000022FE18
    printf("%p\n", &ptr->z);        // 000000000022FE1C
    printf("%p\n", &ptr);           // 000000000022FE08, address of the struct A
    printf("%d\n", *ptr);           // 2293232 or 0x22FDF0, same for *(ptr+1), *(ptr+2). what is this? 
    printf("%d\n", ptr->x);         // 3

	struct B *b;
	// if operand is 'struct B', compiler error
	//		error: invalid application of 'sizeof' to an incomplete type 'struct B'
	//		note: forward declaration of 'struct B'
	//		spec: sizeof operator shall not be applied to function type or an incomplete type
	// if operand is b, ok to compile -> 8 (bytes)
	// if operand is &b, ok to compile -> 8 (bytes)
	printf("%lu\n", sizeof(&b));		// 8
}

struct test {
    int a; int b;
    char c; char d;
    float e;
}; 

void sizeof_struct_test2(){
    struct test t;
    // int 4 bytes, char 1 byte, float 4 bytes -> 14 bytes
    // output is 16 byte due to structure padding, data is aligned as 4 bytes package
    printf("%lu\n", sizeof(t));  // 16 (bytes)
    printf("%p\n", &t.a);       // 000000000022FE10
    printf("%p\n", &t.b);       // 000000000022FE14
    printf("%p\n", &t.c);       // 000000000022FE18
    printf("%p\n", &t.d);       // 000000000022FE19, pad 2 empty bytes FE1A, FE1B
    printf("%p\n", &t.e);       // 000000000022FE1C
}

// test structure
struct Rectangule {
	unsigned int length, width;
}; 	// structure ends with ";"

void struct_test(){
	struct Rectangule rect[2];	// a structure array of 2 elements
	int i;

	rect[0].length = 10;
	rect[0].width = 5;
	rect[1].length = 3;
	rect[1].width = 2;

	for (i = 0; i < 2; i++){
		printf("rect%d:\n", i);
		printf("  length = %u\n", rect[i].length);
		printf("  width = %u\n", rect[i].width);
	}
}

// MyStruct defined in header
void typedef_struct_test(){
    MS ms;

    ms.i = 1; ms.j = 2, ms.k = 3;
    printf("%d\n", ms.i);
    printf("%d\n", ms.j);
    printf("%d\n", ms.k);
}


extern int j;   // declared but not defined, telling compiler that it will be found at "link time"
                // j is defined in static_extern.c. if this is not compiled together, link error occurs. 

void declaration_definition_test(){
    // define i
    int i; 
    printf("%p\n", &i);             // 000000000022FE1C
    printf("%lu\n", sizeof(i));    // 4

    printf("%p\n", &j);             // 000000000040502C
    printf("%lu\n", sizeof(j));    // 4
    printf("%d\n", j);              // 10, defined in static_extern.c
}

union Data {
    int i;
    float f;
    char str[6];
};

// only one union member can contain a value at any given time
// max size is allocated. in this case 6 char or 6 bytes
// due to 4-byte alignment, 2 byte is padded so total is 6 + 2 = 8 bytes
void sizeof_union_test(){
    union Data data;
    printf("%lu\n", sizeof(data));   // 8 (bytes)
}

// only one union member can contain a value at any given time
// when a new member is defined, previously defined members are corrupted
void union_test(){
    union Data data;
    data.i = 2;
    data.f = 2.5;
    strcpy(data.str, "Hi");

    printf("%d\n", data.i);     // 1073768776 (corrupted, no longer 2)
    printf("%f\n", data.f);     // 2.006426 (corrupted, no longer 2.5)
    printf("%s\n", data.str);   // Hi (correct)
}
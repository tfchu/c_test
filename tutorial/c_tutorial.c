#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "c_tutorial.h"
#include "c_struct.h"

// preprocessor starts with "#". compiler replaces text or pre-processes it
// e.g. use "#define" to define TRUE and FALSE (note. without ";") in header file
// statement between #ifdef/#endif, #ifndef/#endif is kept/removed depending on whether the variable is defined or not
// note. bool is a new type equal to char
void preprocessor_test()
{
    bool logic;
    logic = TRUE;
    printf("True is %d\n", logic);  // 1
    logic = FALSE;
    printf("False is %d\n", logic); // 0

    #ifdef TRUE
        printf("TRUE is defined");
    #endif
    #ifdef FALSE
        printf("FALSE is defined");
    #endif
}

void data_type_long_test()
{
    long int i;
    printf("size is %lu", sizeof(i));
}

/*
 * Unary arithmetic: next pointer address depends on type
 * only +, -, ~, !
 */
void pointer_test()
{
    char *ptr; // type char 1 bytes
    char str[] = "Hello World";
    ptr = str;                                           // or &str
    printf("str is @%p\n", str);                         //000000000022FE04
    printf("pointer arithmetic: %p %p\n", ptr, ptr + 1); //000000000022FE04 000000000022FE05 (+1 is 1 byte)

    int *p; // type int 4 bytes
    int arr[5] = {5, 4, 3, 2, 1};
    p = arr;                                         // or &arr
    printf("arr is @%p\n", arr);                     //e.g. @000000000022FDF0
    printf("pointer arithmetic: %p %p\n", p, p + 1); //e.g. 000000000022FDF0 000000000022FDF4 (+1 is 4 byte)
}

// pointer to pointer
void pointer_test1()
{
    int i;
    int *ptr;
    int **ptrptr; // pointer to a pointer
    i = 284;
    ptr = &i;
    ptrptr = &ptr;

    printf("%p\n", ptr);     // 000000000022FE14
    printf("%d\n", *ptr);    // 284
    printf("%p\n", ptrptr);  // 000000000022FE08
    printf("%p\n", *ptrptr); // 000000000022FE14 (use %p to force format the value to 8-byte hex)
}

// return pointer
int *pointer_test2()
{
    int i;
    int *ptr;
    i = 284;
    ptr = &i;
    return ptr;
}

void run_pointer_test2()
{
    int *ptr;
    ptr = pointer_test2();

    printf("%p\n", ptr);  // 000000000022FDD4
    printf("%d\n", *ptr); // 284
}

// pointer as function parameter
// pointer_test3 parameter is a pointer to int, which is address of any integer type
// passing pointer as parameter is similar to pass-by-object, 
void pointer_test3(int *value) {
    printf("%d @ 0x%p\n", *value, (void *)value);   // 10 @ 0x000000000022FE1C
}
void pointer_test3_compare(int value) {
    printf("%d @ 0x%p\n", value, (void *)&value);
}

void run_pointer_test3() {
    int i = 10;
    printf("original %d @ 0x%p\n", i, (void *)&i);  // original 10 @ 0x000000000022FE1C
    pointer_test3(&i);                              // 10 @ 0x000000000022FE1C
    pointer_test3_compare(i);                       // 10 @ 0x000000000022FDF0
}

// relationship between array and pointer
void simple_array()
{
    int arr[5] = {5, 4, 3, 2, 1}; // or arr[0] = 5, arr[1] = 4, ...
    int *ptr;
    int i;

    ptr = arr; // or ptr = &arr, or ptr = &arr[0]
    // print element address with arr
    // output: 000000000022FDF0, 000000000022FDF4, 000000000022FDF8, 000000000022FDFC, 000000000022FE00
    // if using arr[i], then print int 5, 4, 3, 2, 1 formatted as 8-byte like pointer
    for (i = 0; i < 5; i++)
    {
        printf("%p\n", (void *)&arr[i]);
    }
    // print element values with variable arr
    for (i = 0; i < 5; i++)
    {
        printf("%d\n", arr[i]);
    } // 5 4 3 2 1

    printf("array address: ptr = %p, arr = %p\n", (void *)ptr, (void *)arr); // 000000000022FDF0, 000000000022FDF0

    // print element address with pointer
    for (i = 0; i < 5; i++)
    {
        /* output is NOT 22FDF0, 22FDF1, 22FDF2, 22FDF3, 22FDF4
		   output is 22FDF0, 22FDF4, 22FDF8, 22FDFC, 22FE00, increase by 4 as int is 4 bytes
		   so do not use "ptr + i*4"
		   if using short (2 byte), then increase by 2 (22FDF0, 22FDFD2, ...) */
        printf("%p\n", ptr + i);
    }
    // print element values with pointer
    for (i = 0; i < 5; i++)
    {
        printf("%d\n", *(ptr + i));
    }
}

void array_unknown_size(int size)
{
    int *array;
    array = malloc(size * sizeof(int));   // size = 5 (elements)
    for(int i = 0; i < size; i++){
        array[i] = i * 2;
    }
    for(int i = 0; i < size; i++) {
        printf("%d\n", array[i]);
    }
    printf("sizeof: %d", sizeof(array)/sizeof(array[0]));
}

void array_cpy()
{
    int src[5], dst[5];
    for(int i = 0; i < 5; i++) {
        src[i] = i * 3;
    }
    memcpy(dst, src, sizeof(dst));
    for(int i = 0; i < 5; i++) {
        printf("%d\n", dst[i]);
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
void simple_string()
{
    // same as char *str = "Hello World";
    char *ptr;
    char str[] = "Hello World";
    ptr = str; // or ptr = &str

    int i;
    // str and &str are the same
    printf("%p %p\n", str, &str); //0x7fff5d5d445c 0x7fff5d5d445c

    // print string
    printf("%s\n", ptr); //Hello World

    // print string
    for (i = 0; i < strlen(str); i++)
    {
        printf("%c\n", str[i]);
    }
}

/*	ptr             str
 *  (char *)        (char [])
 *  ptr type: (char *), pointer to char
 *  str type: (char []), array of char
 */
void sizeof_test()
{
    printf("size of int: %lu\n", sizeof(int));  // 4 (bytes) for int

    char *ptr;
    char str[] = "Hello World";
    ptr = str;
    printf("size of ptr: %lu\n", sizeof(ptr)); // 8 (bytes) (8 bytes for 64-bit system)
    printf("size of string: %lu\n", sizeof(str)); // 12 (bytes) (str is 11 char + "\0", so 12 characters = 12 bytes)
    printf("strlen: %lu\n", strlen(str)); // 11 (chars), str is 11 characters withtout "\0"

    struct BitStruct bs;
    // struct
    printf("size of MS_t: %lu\n", sizeof(MS_t));    // declared in header, 12 (3 int)
    printf("size_of bs: %lu\n", sizeof(bs));    // declared in header, 1 (1 char), 4 if using int
    // enum
    printf("size of enum: %lu\n", sizeof(PIN_t)); // declared in header, 4 (1 int)
}

// simple structure
struct Rectangle
{
    unsigned int length, width;
}; // structure ends with ";"

void simple_struct()
{
    // struct declaration and initialization
    struct Rectangle r = {1, 5}; // initialized according to the order of memebers
    printf("r's length = %u, width = %u\n", r.length, r.width);

    // struct declaration and designated initialization
    struct Rectangle r2 = {.width = 5, .length = 1}; // initialized by member name
    printf("r2's length = %u, width = %u\n", r2.length, r2.width);

    // struct array
    struct Rectangle arr[2]; // a structure array of 2 elements
    int i;

    arr[0].length = 10;
    arr[0].width = 5;
    arr[1].length = 3;
    arr[1].width = 2;

    for (i = 0; i < 2; i++)
    {
        printf("rect%d:\n", i);
        printf("  length = %u\n", arr[i].length);
        printf("  width = %u\n", arr[i].width);
    }
}

/*
 | 4 | 4 | 1 | 1 | 2 | 4 | bytes, total 16 bytes
 | a | b | c | d | p | e | variables, "p" for padding
*/
struct s
{
    int a;
    int b;
    char c;
    char d;
    float e;
};

void struct_padding()
{
    struct s my_struct;
    // int 4 bytes, char 1 byte, float 4 bytes -> 14 bytes
    // output is 16 byte due to structure padding, data is aligned as 4 bytes package
    printf("%lu\n", sizeof(my_struct)); // 16 (bytes)
    printf("%p\n", &my_struct);         // 000000000022FE10
    printf("%p\n", &my_struct.a);       // 000000000022FE10
    printf("%p\n", &my_struct.b);       // 000000000022FE14
    printf("%p\n", &my_struct.c);       // 000000000022FE18
    printf("%p\n", &my_struct.d);       // 000000000022FE19, pad 2 empty bytes FE1A, FE1B
    printf("%p\n", &my_struct.e);       // 000000000022FE1C
}

/*
 * sizeof operator
 */
struct A
{
    int x, y, z;
};

struct B; // forward declaration (no definition)

void struct_pointer()
{
    printf("%lu\n", sizeof(struct A)); // 12 (3 int, 4 bytes each)

    // declaration
    struct A a; // *a is also ok
    a.x = 3;
    a.y = 4;
    a.z = 5;
    // &a has the same value as &a.x, but unable to use &a to get values. &a is not a pointer
    printf("%lu\n", sizeof(&a)); // 8 (8 bytes for 64-bit system)
    printf("%lu\n", sizeof(a));  // 12 (size of struct A = 12 bytes)
    printf("%p\n", &a);          // 000000000022FE14
    printf("%p\n", &a.x);        // 000000000022FE14
    printf("%p\n", &a.y);        // 000000000022FE18
    printf("%p\n", &a.z);        // 000000000022FE1C
    //printf("%d\n", *(&a));          // 2293232 or 0x22FDF0, same for *(&a+1), *(&a+2). what is this?

    // what is *ptr, *(&ptr), ptr
    struct A *a_ptr;
    a_ptr = &a;
    printf("%lu\n", sizeof(a_ptr));  // 8 (8 bytes for 64-bit system)
    printf("%lu\n", sizeof(*a_ptr)); // 12 (size of struct A = 12 bytes)
    printf("%p\n", a_ptr);           // 000000000022FE14
    printf("%p\n", &a_ptr->x);       // 000000000022FE14
    printf("%p\n", &a_ptr->y);       // 000000000022FE18
    printf("%p\n", &a_ptr->z);       // 000000000022FE1C
    printf("%p\n", &a_ptr);          // 000000000022FE08, address of the struct A?
    //printf("%d\n", *a_ptr);           // 2293232 or 0x22FDF0, same for *(ptr+1), *(ptr+2). what is this?
    printf("%d\n", a_ptr->x); // get value of x, 3

    struct B *b;
    // if operand is 'struct B', compiler error
    //		error: invalid application of 'sizeof' to an incomplete type 'struct B'
    //		note: forward declaration of 'struct B'
    //		spec: sizeof operator shall not be applied to function type or an incomplete type
    // if operand is b, ok to compile -> 8 (bytes)
    // if operand is &b, ok to compile -> 8 (bytes)
    printf("%lu\n", sizeof(&b)); // 8
}

// MyStruct defined in header c_tutorial.h
void typedef_struct()
{
    MS_t ms;

    ms.i = 1;
    ms.j = 2, ms.k = 3;
    printf("%d\n", ms.i);
    printf("%d\n", ms.j);
    printf("%d\n", ms.k);
}

/*
 simple union
*/
union Data {
    int i;
    float f;
    char str[6];
};

// only one union member can contain a value at any given time
// max size is allocated. in this case 6 char or 6 bytes
// due to 4-byte (dw) alignment, 2 byte is padded so total is 6 + 2 = 8 bytes
void sizeof_union()
{
    union Data data;
    printf("%lu\n", sizeof(data)); // 8 (bytes)
}

// only one union member can contain a value at any given time
// when a new member is defined, previously defined members are corrupted
void simple_union()
{
    union Data data;
    data.i = 2;
    data.f = 2.5;
    strcpy(data.str, "Hi");

    printf("%d\n", data.i);   // 1073768776 (corrupted, no longer 2)
    printf("%f\n", data.f);   // 2.006426 (corrupted, no longer 2.5)
    printf("%s\n", data.str); // Hi (correct)
}

// struct in union, modifying struct modifies variable as "only one union member can contain a value at any given time"
// init tu (10-bit a=1, 4-bit b=2, 18-bit c=3), bits in memory
// | 0000 0000 0000 0000 | 1100 1000 0000 0001 | = 51201 (dec) @ 0x22FE1C
// |                        c    b           a |
// modify_complex_union_ptr(&tu): modify with pointer &tu
// | 0000 0000 0000 0000 | 0100 1000 0000 0011 | = 18453 (dec) @ 0x22FE1C
// |                        c    b           a |
// modify_complex_union_val(tu): modify again with value tu
// a new union is created at differnt location (original is not changed)
// | 0000 0000 0000 0000 | 1100 1000 0000 0001 | = 51201 (dec) @ 0x22FDF0
// |                        c    b           a |
void complex_union()
{
    TEST_UNION tu;
    printf("original address: 0x%p\n", &tu);    // 0x000000000022FE1C

    tu.dw = 0;
    printf("Original DW value: %d\n", tu.dw);   // 0

    tu.bit.a = 1;   // 10-bit
    tu.bit.b = 2;   // 4-bit
    tu.bit.c = 3;   // 18-bit

    printf("New DW value: %d\n", tu.dw);        // 51201, original

    modify_complex_union_ptr(&tu);
    printf("New DW value: %d\n", tu.dw);        // 18435, modified

    modify_complex_union_val(tu);
    printf("New DW value: %d\n", tu.dw);        // 18435, unmodified
}
// simulate pass-by-reference by passing the address of a variable
inline void modify_complex_union_ptr(TEST_UNION *tu)
{
    tu->bit.a = 3;
    tu->bit.b = 2;
    tu->bit.c = 1;
}

// C language is pass-by-value without exception
// A function is NOT able to change the actual parameters value
// when value of "tu" is passed, a new location is created to store it, modification is made at new location
inline void modify_complex_union_val(TEST_UNION tu)
{
    tu.bit.a = 1;
    tu.bit.b = 2;
    tu.bit.c = 3;
    printf("new address: 0x%p\n", &tu);           // 0x000000000022FDF0
}

/*
 declaration vs definition
*/
extern int j; // declared but not defined, telling compiler that it will be found at "link time"
              // j is defined in static_extern.c. if this is not compiled together, link error occurs.

void declaration_definition()
{
    // define i
    int i;
    printf("%p\n", &i);         // 000000000022FE1C
    printf("%lu\n", sizeof(i)); // 4

    printf("%p\n", &j);         // 000000000040502C
    printf("%lu\n", sizeof(j)); // 4
    printf("%d\n", j);          // 10, defined in static_extern.c
}

// volatile
volatile int buff[192];

void volatile_test() {
    
}

// struct array
typedef struct
{
    char element: 6;    // lower 6 bit of character
    char :2;            // upper 2-bit default to 1, has no name
} entry_t;

void struct_array(){
    entry_t arr[2][2] = {
        {
            {.element = '1'}, {.element = '2'}
        }, 
        {
            {.element = '3'}, {.element = '4'}
        }
    };

    /* upper 2-bit default to 1
    ± @ 000000000022FE14, due to '1' (ascii 49) | (1 << 6 | 1 << 7) = 241 (±)
    ≥ @ 000000000022FE15, due to '2' (ascii 50) | (1 << 6 | 1 << 7) = 242 (≥)
    ≤ @ 000000000022FE16, due to '3' (ascii 50) | (1 << 6 | 1 << 7) = 243 (≤)
    ⌠ @ 000000000022FE17, due to '4' (ascii 50) | (1 << 6 | 1 << 7) = 244 (⌠)
    */
    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 2; j++){
            printf("%c @ %p\n", arr[i][j].element, &arr[i][j]);
        }
    }
    
}

// consider endianess
// array in memory: |01 00 00 00|02 00 00 00|03 00 00 00|04 00 00 00|05 00 00 00|06 00 00 00|...
// struct:          | a  b  c  d|     e     |           f           | unused
// so (byte) a=0x01, b=0x00, c=0x00, e=0x00000002, f=0x00000004_00000003
// CAST_TO_STRUCT* cts = (CAST_TO_STRUCT *)arr; // CAST_TO_STRUCT has less bytes than arr, so cts is truncated arr
// CAST_TO_STRUCT* cts = arr; // gets warning due to incompatible pointer type but OK
// CAST_TO_STRUCT cts = (CAST_TO_STRUCT)arr;  // casting to CAST_TO_STRUCT is not allowed
void array_cast_to_struct() {
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    CAST_TO_STRUCT* cts = (CAST_TO_STRUCT *) arr;    // start from arr[1]: (CAST_TO_STRUCT *) &arr[1]
    //pCAST_TO_STRUCT cts = (pCAST_TO_STRUCT)arr;   // same as above

    // %02x: pad with leading 0s, total 2 digits, hex format 
    printf("%02x %02x %02x %02x %04x %08I64x\n", cts->a, cts->b, cts->c, cts->d, cts->e, cts->f);

    // output is same as above
    CAST_TO_STRUCT_BIT* ctsb = (CAST_TO_STRUCT_BIT *)arr;
    printf("%02x %02x %02x %02x %04x %08I64x\n", ctsb->a, ctsb->b, ctsb->c, ctsb->d, ctsb->e, ctsb->f);
}

void function_with_macro() {
    int var = ALIGN(18, 4);
    printf("macro function: %d\n", var);
}

// UINT8 data[] = &data; this caused compile error due to array length not specified
// pass &data to data[] caused only compile warning (incompatible pointer type)
// memory layout: enum element is 4 bytes and each array element is 1 byte
// |data[0] data[1] data[2] data[3]|
// |     enum element e.g. reg1    |
enum reg {reg1, reg2, reg3, reg4};  // enum stored as int (4 bytes), value = 0, 1, 2, 3
void function_enum_to_array(UINT8 data[], UINT8 len) {
    printf("length = %d bytes\n", len);
    for (UINT32 i = 0; i < len; i++) {
        printf("data[%d] = 0x%x\n", i, data[i]);    // if reg3, then data[0]=0x2, data[1|2|3]=0x0
    }
}
void test_enum_to_array(enum reg data) {
    function_enum_to_array(&data, sizeof(data));    // pass address of enum element &data to array parameter UINT8 data[]
}
void main_enum_to_array() {
    test_enum_to_array(reg3); 
}

// after a enum is typedef'ed, variable can be called directly, i.e. PIN1,PIN2,PIN3
// enum name 'pins' is used to indicate type if necessary
// regular enum variables can also be called directly
void use_enum_string(PIN_t pin, enum reg r) {
    // typedef'ed enum (declared in header)
    printf("%d\n", PIN1);   // 0
    printf("%d\n", PIN2);   // 1
    printf("%d\n", PIN3);   // 2
    printf("you selected typedef'ed enum %d\n", pin);   // 0

    // regular enum (declared above)
    printf("%d\n", reg1);   // 0
    printf("%d\n", reg2);   // 1
    printf("%d\n", reg3);   // 2
    printf("you selected regular enum %d\n", reg1);   // 0
}

void pass_enum_string_to_function() {
    use_enum_string(PIN1, reg1);
}

//
NEW_STRUCT init_struct(NEW_STRUCT ns) {
    ns.cts.a = 0;
    ns.cts.b = 1;
    ns.cts.c = 2;
    ns.cts.d = 3;
    ns.cts.e = 4;
    ns.cts.f = 5;
    return ns;
}

// https://stackoverflow.com/questions/12958931/warning-x-may-be-used-uninitialized-in-this-function
NEW_STRUCT_PTR init_struct_ptr(NEW_STRUCT_PTR nsp) {
    CAST_TO_STRUCT cts;
    cts.a = 5;
    cts.b = 4;
    cts.c = 3;
    cts.d = 2;
    cts.e = 1;
    cts.f = 0;

    nsp.pcts = &cts;
    return nsp;
}

void struct_or_structptr() {
    NEW_STRUCT ns;
    ns = init_struct(ns);
    printf("address: 0x%p\n", &ns);
    printf("value: %d %d %d %d %d %ld\n", ns.cts.a, ns.cts.b, ns.cts.c, ns.cts.d, ns.cts.e, ns.cts.f);
    ns.cts.a = 5;
    ns.cts.b = 4;
    ns.cts.c = 3;
    ns.cts.d = 2;
    ns.cts.e = 1;
    ns.cts.f = 0;
    printf("value: %d %d %d %d %d %ld\n", ns.cts.a, ns.cts.b, ns.cts.c, ns.cts.d, ns.cts.e, ns.cts.f);
    
    NEW_STRUCT_PTR nsp; 
    nsp = init_struct_ptr(nsp);
    printf("address: 0x%p\n", &nsp);
    printf("pointer: %d %d %d %d %d %ld\n", nsp.pcts->a, nsp.pcts->b, nsp.pcts->c, nsp.pcts->d, nsp.pcts->e, nsp.pcts->f);
    nsp.pcts->a = 0;
    nsp.pcts->b = 1;
    nsp.pcts->c = 2;
    nsp.pcts->d = 3;
    nsp.pcts->e = 4;
    nsp.pcts->f = 5;
    printf("pointer: %d %d %d %d %d %ld\n", nsp.pcts->a, nsp.pcts->b, nsp.pcts->c, nsp.pcts->d, nsp.pcts->e, nsp.pcts->f);
}

// function pointer test
// 2 types of function pointer declaration (to be used as parameters in another function)
//   one with typedef (in c_tutorial.h) (1st parameter of exec_func)
//   one in function parameter (2nd parameter of exec_func)
// call_func() passes 2 function pointers (sfunc, efunc) to exec_func() which executes the two functions
// note. write functions first. if needed, use function pointer to pass them as parameters to another function
void sfunc(char greeting[], char name[]) {
    printf("%s, %s\n", greeting, name);
}

void efunc(char bye[]) {
    printf("%s\n", bye);
}

void exec_func(start_function_t start_func, void (*end_func)(char bye[])) {
    start_func("Hi", "Tony");
    end_func("Good Bye");
}

void call_func() {
    exec_func(sfunc, efunc);  // &sfunc, &efunc also ok
}

// function pointer test 2
// typedef a function pointer, use it to declare a new variable
// then use the new variable like a function
int add (int a, int b) {
    return a + b;
}

typedef int (*add_integer_t)(int, int);   // function pointer/type: return int, typename add_integer, 2 params of int

void function_ptr_test2() {
    add_integer_t addition = add;       // add_integer is a new type (function pointer), used to declare new variable
    int c = addition(1, 2);             // call add() via new variable
    printf("Result is %d\n", c);        // 3
    printf("address of addition: 0x%p\n", (void *)&addition);   // 0x000000000022FE10
    printf("address of add: 0x%p\n", &add);                     // 0x00000000004024E0
}

// function pointer 3
// one struct member is function pointer type (add_integer_t)
// c is a + b or c = exec(a, b) where exec = &add (address of add() function)
typedef struct {
    int a;
    int b;
    add_integer_t exec;
    int c;
} member_and_func;

// assign member a&b value, and function pointer
member_and_func *function_ptr_test2_assign(add_integer_t exec) {
    member_and_func *mf = malloc(4 * sizeof(int));  // struct pointer requires initialization first, int 4 byte, func ptr 2 byte?
                                                    // 4 can be even changed to any value (e.g. 1) and code still works
    mf->a = 5;
    mf->b = 8;
    mf->exec = exec;
    printf("a: 0x%p\n", (void *)&mf->a);                    // 0x0000000000717E20
    printf("b: 0x%p\n", (void *)&mf->b);                    // 0x0000000000717E24
    printf("add_integer: 0x%p\n", &mf->exec);               // 0x0000000000717E28 (!!) only 2 bytes
    printf("c: 0x%p\n", (void *)&mf->c);                    // 0x0000000000717E30
    return mf;
}

// assign exact function ptr to struct function ptr, and member c value (add(a, b))
void function_ptr_test3() {
    member_and_func *mf = function_ptr_test2_assign(add);
    mf->c = mf->exec(mf->a, mf->b);
    printf("Result is %d\n", mf->c);                        // 13
}

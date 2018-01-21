typedef char bool;

typedef struct MyStruct{
    int i;
    int j;
    int k;
} MS;

/* or

struct MyStruct{
    int i, j, k;
}; 
typedef struct MyStruct MS;

*/

#ifndef FALSE
    #define FALSE 0
#endif

#ifndef TRUE
    #define TRUE 1
#endif

void typedef_struct_test();
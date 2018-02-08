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

void preprocessor_test(); 
void data_type_long_test();
void pointer_test();
void pointer_test1();
void run_pointer_test2();
void simple_array();
void simple_string();
void sizeof_test();
void simple_struct();
void struct_padding();
void struct_pointer();
void typedef_struct();
void sizeof_union();
void simple_union();
void declaration_definition();
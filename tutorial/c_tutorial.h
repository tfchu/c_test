typedef char bool;

typedef struct MyStruct{
    int i;
    int j;
    int k;
} MS_t;

struct BitStruct {
    char a: 2;   // 2bit
    char b: 3;   // 3bit
    char c: 3;   // 3bit
};

/* or

struct MyStruct{
    int i, j, k;
}; 
typedef struct MyStruct MS_t;

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
void run_pointer_test3();
void simple_array();
void array_unknown_size(int size);
void array_cpy();
void simple_string();
void sizeof_test();
void simple_struct();
void struct_padding();
void struct_pointer();
void typedef_struct();
void sizeof_union();
void simple_union();
void complex_union();
void declaration_definition();
void struct_array();
void array_cast_to_struct();
void function_with_macro();
void main_enum_to_array();
void pass_enum_string_to_function();
void function_ptr_test2();
void function_ptr_test3();

#define ALIGN(x, y) (DIV((x), (y)) * (y))
#define DIV(x, y)   (((x)%(y)!=0) ? (x)/(y) + 1 : (x)/(y))

typedef unsigned char UINT8;
typedef unsigned int UINT32;

typedef enum {
    PIN1, 
    PIN2,
    PIN3
} PIN_t;

typedef void (*start_function_t)(char greeting[], char name[]);
void call_func();
void structure_size_test();

typedef union {
    struct {
        int a: 10;  // 10-bit
        int b: 4;   // 4-bit
        int c: 18;  // 18-bit
    } bit;
    int dw;
} TEST_UNION, *pTEST_UNION;

typedef struct {
    char a;         // 1 byte
    char b; 
    char c; 
    char d;
    int e;          // 4 bytes
    long long f;    // 8 bytes
} CAST_TO_STRUCT, *pCAST_TO_STRUCT;

typedef struct {
    int a: 8;
    int b: 8;
    int c: 8;
    int d: 8;
    int e: 32;
    long long int f: 64;    // int up to 32 bits
} CAST_TO_STRUCT_BIT;

typedef struct {
    CAST_TO_STRUCT cts;
} NEW_STRUCT;

typedef struct {
    CAST_TO_STRUCT *pcts;
} NEW_STRUCT_PTR;

NEW_STRUCT init_struct(NEW_STRUCT ns);
NEW_STRUCT_PTR init_struct_ptr();
void struct_or_structptr();
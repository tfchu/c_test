/*
 * main.c
 *
 *  Created on: Jun 3, 2017
 *      Author: tfchu
 */
#include<stdio.h>

void fun(){
	printf("%s", "a function");
}

// case01: sizeof(ptr) and sizeof(str)
void case01(){
	char *ptr;
	char str[] = "Hello World";
	ptr 		= 	str;
	printf("%u %u %u\n", sizeof(ptr), sizeof(str), strlen(str));
	printf("%p %p\n", ptr, str);
	printf("%x %x\n", ptr, str);
	printf("%p\n", &*ptr);
/*	ptr				str
 *  (char *)		(char [])
 *  ptr type: (char *), pointer to char
 *  str type: (char []), array of char
 *  sizeof(ptr): 8, size of the pointer, 8 bytes for 64-bit system
 *  sizeof(str): 12, 12 characters in the array, each char is 1 byte
 *  strlen(str): 11
 */
}

/*
 * 1. for &: if operand is [] type, & is not evaluated
 * 		e.g. char str[];
 * 		str and &str are the same because & is not evaluated
 * 2. ptr = &str: a pointer ptr to pointer &str
 * 		addresses of ptr and &str are different
 */
void case02(){
	char *ptr;
	char str[] = "Hello World";
	ptr = &str;
	// full pointer
	printf("%p %p\n", str, &str);	//e.g. 0x7fff5d5d445c 0x7fff5d5d445c
	// last 4 bytes of pointer
	printf("%x %x\n", str, &str);	//e.g. 5d5d445c 5d5d445c
	// pointer ptr to pointer &str
	printf("%x %x\n", str, &ptr);	//e.g. 5d5d445c 5d5d4450
}

/*
 * Unary arithmetic: depends on type
 * only +, -, ~, !
 */
void case03(){
	char *ptr;	// type char 1 bytes
	int *p;		// type int 4 bytes
	char str[] = "Hello World";
	ptr = str; 	// or &str
	p = str;	// or &str
	printf("%x\n", str);	//e.g. 573ce45c
	// (each memory address represents 1 byte)
	// ptr is char (1 byte), +1: move by one size of char
	printf("%x %x\n", ptr, ptr+1);	//e.g. 573ce45c 573ce45d
	// p is int (4 bytes), +1: move by one size of int
	printf("%x %x\n", p, p+1);		//e.g. 573ce45c 573ce460
}

/*
 * sizeof operator
 */
struct A{
	int x, y, z;
};
struct B;	// forward declaration (no definition)
void case04(){
	// struct A has 3 int, each with 4 bytes -> 12 bytes total
	printf("%d\n", sizeof(struct A));

	// declaration
	struct A a;		// *a is also ok
	// if using struct A a, output = 8, 12
	// 		sizeof(&a): address is 8 bytes for 64-bit system
	//		sizeof(a): a is of type struct A, size is same as struct A = 12 bytes
	//		&a: a is not a pointer, pointer value does not exist
	// if using struct A *a, output = 8, 8
	// 		sizeof(&a): address is 8 bytes for 64-bit system
	// 		sizeof(a): a is a pointer, which is 8 bytes for 64-bit system
	//		&a is the address of the struct
	printf("%d %d\n", sizeof(&a), sizeof(a));
	printf("%p %p\n", a, &a);

	struct B *b;
	// if operand is 'struct B', compiler error
	//		error: invalid application of 'sizeof' to an incomplete type 'struct B'
	//		note: forward declaration of 'struct B'
	//		spec: sizeof operator shall not be applied to function type or an incomplete type
	// if operand is b, ok to compile -> 8 (bytes)
	// if operand is &b, ok to compile -> 8 (bytes)
	printf("%d\n", sizeof(&b));		// 8
}

void test(){
	int v = 10;
	printf("Address of v is %p\n", &v);
	printf("Value of v is %d\n", v);

	// assign int type to *ptr ->
	// syntax becomes same as int type, not pointer type
	// &ptr is the address, ptr is the value
	int *ptr = 10;
	printf("Address is %p\n", &ptr);
	printf("Value is %d\n", ptr);

	// assign pointer type to p
	// then p is a pointer, *p is the value
	int *p;
	p = &v;
	printf("Address is %p\n", p);
	printf("Value is %d\n", *p);
}

int main(){

	test();
}



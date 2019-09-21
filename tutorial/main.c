/*
 * main.c
 *
 *  Created on: Jun 3, 2017
 *      Author: tfchu
 */
//#include <stdio.h>
//#include "memtest86p.h"
#include "c_tutorial.h"
#include "c_practice.h"

int main(){
	//printf("%lu", rand(0));
	//typedef_struct_test();

	//init_v();
	//run_addr_tst1();
	//run_modtst();
	//run_movinv1();

	// c_practice.c
/* 	rect_t r1; 
	rect_t r2; 
	rect_t r3; 
	r1.left = -1; r1.bottom = -1; r1.right = 3; r1.top = 3; 
	r2.left = 0; r2.bottom = 0; r2.right = 2; r2.top = 2; 
	r3 = intersection(r1, r2);
	printf("intersection is: (left) %f, (bottom) %f, (right) %f, (top) %f\n", r3.left, r3.bottom, r3.right, r3.top); */

	//call_swap();

	//sfact(5);

	// int N = 29393;
	// if(isPrimeNumber(29393)){
	// 	printf("%d is a prime number\n", N);
	// } else {
	// 	printf("%d is NOT a prime number\n", N);
	// }
	// return 0;

	//simple_struct();

	/* gpio test
	int id, dir, src;
	int ctrl0, ctrl1, ctrl2, oe;

	id = 2;		// gpio bit 2
	dir = 0;	// out
	src = 1;	// ?

	ctrl0 = 0xff8ff7fc;
	ctrl1 = 0;
	ctrl2 = 0;
	ctrl0 = (ctrl0 & ~(1 << id)) | ((src & 1) << id);
	ctrl1 = (ctrl1 & ~(1 << id)) | (((src & 2) >> 1) << id);
	ctrl2 = (ctrl2 & ~(1 << id)) | (((src & 4) >> 2) << id);
	printf("ctrl0=%x\nctrl1=%x\nctrl2=%x\n", ctrl0, ctrl1, ctrl2);

	oe = 0xf16ff607;
	oe = (oe & ~(1 << id)) | (dir << id);
	printf("oe=%x\n", oe);

	// set [id] to 1 if value = 1, set [id] to 0 if value = 0
	int data;
	data = 0x00617203;
	printf("value = 1: %x\n", data | (1 << id));
	printf("value = 0: %x\n", data & ~(1 << id));
	*/

	// c_tutorial
	//complex_union();
	//struct_array();

	//array_cast_to_struct();
	//function_with_macro();
	//main_enum_to_array();
	//pass_enum_string_to_function();
	//left_shift_test();
	//struct_or_structptr();
	//run_pointer_test3();

	//function_pointer_test();
	//array_unknown_size(5);
	//function_ptr_test2();
	//function_ptr_test3();
	//array_cpy();
	//sizeof_test();
	//call_func();
}
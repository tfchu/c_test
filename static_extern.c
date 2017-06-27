/*
demonstrate static and extern keywords

Object linkage types: 
    - external: objects that can be accessed across all modules, e.g. objects at file or global scope
        - can be changed with "extern"
    - internal: objects that can only be accessed from the compilation unit
        - define with "static"
    - none: objects at local scope, e.g. local varialbe and function parameters
Note. By default, the declaration and definition of a C function have “extern” prepended with them.

storage duration types (lifetime): 
    - static: objects remain available through the whole program runtime
        - can be set with "static"
    - automatic: the duration for object with no linkage

in this example, if i1, i2, i3 is not defined, then the header file is needed due to "extern"
*/
#include<stdio.h>
//#include"static_extern.h"

int i1 = 1;         // definition, external linkage
static int i2 = 2;  // definition, internal linkage
int i3;             // tentative defintion, external linkage

int i1;             // tentative defintion, refers to previous
static int i2;      // tentative defintion, refers to previous
int i3 = 3;         // tentative defintion, refers to previous

extern int i1;      // refers to previous, whose linkage is external
extern int i2;      // refers to previous, whose linkage is inernal
extern int i3;      // refers to previous, whose linkage is external

int main(void){
    printf("%d\n", i1);
    printf("%d\n", i2);
    printf("%d\n", i3);
    printf("%s\n", "done");
    return 0;
}
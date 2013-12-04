//#ifndef MM_STRUCT
//#define unsigned int UINT32
#include<stdio.h>
#include "ll_list.h"
#if 0
typedef struct virtual_mm{
	int ml;
        int type;
	char val[4];	
}vm;
typedef struct list_vm{
	int sn;
	vm *v;
}lvm;
lvm *master=0;
#endif



void save_data()
{
	//printf("test\n");
        create_list();
}



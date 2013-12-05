//#ifndef MM_STRUCT
//#define unsigned int UINT32
#include<stdio.h>
//#include "ll_list.h"
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

#define VAL_SIZE 1
typedef class virtual_mm{
public:
	unsigned int ml;//memory location
    int type;// type
	int state;// state number
	//char val[VAL_SIZE];
	char val;
	virtual_mm* next;
      //  virtual_mm* prev;
	virtual_mm()
	{
		ml = 0;
		type = -1;
#if 0
		for(int i = 0;i<VAL_SIZE;i++)
		{
			val[i] =0;
		}
#else
		val = 0;
#endif
		next = 0;
	}
}vm;


void save_data()
{
	//printf("test\n");
  //      create_list();
}



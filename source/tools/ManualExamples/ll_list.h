#include<stdio.h>
#include<stdlib.h>
void create_list()
{ 
//        printf("called from another file\n");
	return;
}

#define VAL_SIZE 4
typedef class virtual_mm{
public:
	unsigned int ml;
        int type;
	int state;
	char val[VAL_SIZE];
	virtual_mm* next;
	virtual_mm()
	{
		ml = 0;
		type = -1;
		for(int i = 0;i<VAL_SIZE;i++)
		{
			val[i] =0;
		}
		next = 0;
	}
}vm;

vm *head = NULL;
vm *curr = NULL;

#if 1
void copy_vm(vm *p,int ml,int type,int state,char *v, vm* next)
{
	p->ml = ml;
	p->type = type;
	p->state = state;
        p->next = next;
	if(v)
	{
		for(int i = 0 ;i<VAL_SIZE;i++)
		{
			p->val[i] = *(v+i); 
		}
	}
}
vm* get_new_vm()
{
	vm* v = (vm* )malloc(sizeof(vm)); 
	return v;
}
vm* create_list(vm* v)
{
    printf("\n creating list with headnode as [%x]\n",v->ml);
    vm *ptr = (vm*)malloc(sizeof(vm));
    if(NULL == ptr)
    {
        printf("\n Node creation failed \n");
        exit(-1);
    }
    copy_vm(ptr,v->ml,v->type,v->state,NULL,NULL);
    head = curr = ptr;
    return ptr;
}

void copy_vm_to_vm(vm *from,vm * to)
{
	to->ml = from->ml;
	to->type = from->type;
	to->state = from->state;
    //to->next = from->next;
	//if(v)
	{
		for(int i = 0 ;i<VAL_SIZE;i++)
		{
			to->val[i] = from->val[i]; 
		}
	}
}
vm* add_to_list(vm* v)
{
    if(NULL == head)
    {
		return (create_list(v));
    }

//    printf("\n Adding node to end of list with value [%x][%d][%d]\n",v->ml,v->type,v->state);
    
    vm *ptr = (vm* )malloc(sizeof(vm));
    if(NULL == ptr)
    {
        printf("\n Node creation failed \n");
        //return NULL;
		exit(0);
    }
	copy_vm_to_vm(v,ptr);
    ptr->next = NULL;

    //if(add_to_end)
    {
        curr->next = ptr;
        curr = ptr;
    }
    return ptr;
}

void print_list(void)
{
    vm *ptr = head;

    printf("\n -------Printing list Start------- \n");
    while(ptr != NULL)
    {
		printf("\n [mem_location:%d] [type:%d] [state:%d] \n",ptr->ml,ptr->type,ptr->state);
        ptr = ptr->next;
    }
    printf("\n -------Printing list End------- \n");

    return;
}

#endif

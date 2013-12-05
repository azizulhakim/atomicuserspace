#include<stdio.h>
#include<stdlib.h>
#include "mm_struct.h"
void create_list()
{ 
//        printf("called from another file\n");
	return;
}

vm *head = NULL;
vm *curr = NULL;
FILE *fp=NULL;


#if 1
void copy_vm(vm *p,int ml,int type,int state,char *v, vm* next)
{
	p->ml = ml;
	p->type = type;
	p->state = state;
        p->next = next;
        //p->prev= prev;
#if 0
	if(v)
	{

		for(int i = 0 ;i<VAL_SIZE;i++)
		{
			p->val[i] = *(v+i); 
		}


		//val = 0;

	}
#else
	p->val = 0;
#endif

}
void copy_vm_data(vm *p,int ml,int type,int state,char *v, vm* next)
{
	p->ml = ml;
	p->type = type;
	p->state = state;
        p->next = next;
#if 0
	if(v)
	{

		for(int i = 0 ;i<VAL_SIZE;i++)
		{
			p->val[i] = *(v+i); 
		}


		//val = 0;

	}
#else
	p->val = 0;
#endif

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
#if 0
	{
		for(int i = 0 ;i<VAL_SIZE;i++)
		{
			to->val[i] = from->val[i]; 
		}
	}
#else
	to->val = from->val;
#endif
}

void create_vm_node(vm* v,unsigned int m_addr, char data, int type, int state)
{
	v->ml=m_addr;
	v->val = data;
	v->type = type;
	v->state = state;
	v->next = NULL;
}

void set_fp(FILE *flp)
{
	fp=flp;
}

vm* add_single_node(vm* v)
{
    if(NULL == head)
    {
		return (create_list(v));
    }
    
	if(fp)
	
		fprintf(fp,"[%x][%x][%d][%d]\n",v->ml,v->val,v->type,v->state);
    
    //printf("\n Adding node to end of list with value [%x][%d][%d][%d]\n",v->ml,v->val,v->type,v->state);
    
    //if(add_to_end)
    {
        curr->next = v;
        curr = v;
    }
    return v;
}

void add_to_list(void *addr, int type, int state)
{
    unsigned int a = (unsigned int)addr;
    unsigned char* pt = (unsigned char *)addr;
	//printf("addr:[%x]\n",a);
	for(int i=0;i<type;i++)
	{
		char data = *pt;
        //int data=(int)d;
        vm* v = get_new_vm();
		if(v)
        	create_vm_node(v,a,data,type,state );
		else
		{
			printf("sorry can not allocate new node.\n");
			exit(0);
		}
		add_single_node(v);
		pt=pt+1;
		a++;
	}	
	//return v;

//    printf("\n Adding node to end of list with value [%x][%d][%d]\n",v->ml,v->type,v->state);
    
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

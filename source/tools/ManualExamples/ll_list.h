#include<stdio.h>
#include<stdlib.h>
#include "mm_struct.h"
void create_list()
{ 
//        printf("called from another file\n");
	return;
}

vm *head = NULL;
vm *head_state = NULL; // set head_state = curr in save_state() function
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
	head_state = head;
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

vm* search_in_list(unsigned int ml)
{
	vm *ptr = NULL;
	if(head_state && head_state->next)
		ptr = head_state->next;
	else 
		return NULL;

    //vm *tmp = NULL;
    //bool found = false;

    //printf("\n Searching the list for value [%x] \n",ml);

	while(ptr!= NULL)
    {
        if(ptr->ml == ml) //&& ptr->state == state_number)
        {
            //found = true;
            //break;
			return ptr;
        }
        else
        {
           // tmp = ptr;
            ptr = ptr->next;
        }
    }

    {
        return NULL;
    }
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
	vm * s = search_in_list(v->ml);
	if(s)
	{
		
		s->state = v->state;
		s->ml = v->ml;
		s->val = v->val;
	}
	//else
    //if(add_to_end)
	else
    {
        curr->next = v;
		
        curr = v;
    }
    return v;
}

vm* add_single_node2(unsigned int m_addr, char data, int type, int state)
{

    
	//printf("\n Adding node to end of list with value [%x][%d][%d][%d]\n",v->ml,v->val,v->type,v->state);
	vm * s = search_in_list(m_addr);
	if(s)
	{
		printf("matched found:%x\n",m_addr);
		//s->state = state;
		s->ml = m_addr;
		s->val = data;
	}
	//else
    //if(add_to_end)
	else
    {
		s = get_new_vm();
		if(s)
			create_vm_node(s,m_addr,data,type,state );
		else
		{
			printf("sorry can not allocate new node.\n");
			exit(0);
		}
		if(NULL == head)
		{
			return (create_list(s));
		}
	
        curr->next = s;
		
        curr = s;
    }
    return s;
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
#if 0
        vm* v = get_new_vm();
		if(v)
        	create_vm_node(v,a,data,type,state );
		else
		{
			printf("sorry can not allocate new node.\n");
			exit(0);
		}
#endif
		add_single_node2(a,data,type,state );
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

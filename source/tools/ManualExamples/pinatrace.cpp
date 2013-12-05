/*BEGIN_LEGAL 
Intel Open Source License 

Copyright (c) 2002-2013 Intel Corporation. All rights reserved.
 
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:

Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer.  Redistributions
in binary form must reproduce the above copyright notice, this list of
conditions and the following disclaimer in the documentation and/or
other materials provided with the distribution.  Neither the name of
the Intel Corporation nor the names of its contributors may be used to
endorse or promote products derived from this software without
specific prior written permission.
 
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE INTEL OR
ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
END_LEGAL */
/* ===================================================================== */
/*
  @ORIGINAL_AUTHOR: Robert Cohn
*/

/* ===================================================================== */
/*! @file
 *  This file contains an ISA-portable PIN tool for tracing memory accesses.
 */

//#include "pin.H"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>
#include "pin.H"
//#include "mm_struct.h"
#include "ll_list.h"
/* ===================================================================== */
/* Global Variables */
/* ===================================================================== */

std::ofstream TraceFile;
FILE * trace;// = fopen("pinatrace.out", "w");
const char *bin_name;
static VOID * WriteAddr; 
static INT32 WriteSize;

/* ===================================================================== */
/* Commandline Switches */
/* ===================================================================== */

KNOB<string> KnobOutputFile(KNOB_MODE_WRITEONCE, "pintool",
    "o", "pinatrace.out", "specify trace file name");
KNOB<BOOL> KnobValues(KNOB_MODE_WRITEONCE, "pintool",
    "values", "1", "Output memory values reads and written");

/* ===================================================================== */
/* Print Help Message                                                    */
/* ===================================================================== */

static INT32 Usage()
{
    cerr <<
        "This tool produces a memory address trace.\n"
        "For each (dynamic) instruction reading or writing to memory the the ip and ea are recorded\n"
        "\n";

    cerr << KNOB_BASE::StringKnobSummary();

    cerr << endl;

    return -1;
}


static VOID EmitMem(VOID * ea, INT32 size)
{
    if (!KnobValues)
        return;
    
    switch(size)
    {
      case 0:
        TraceFile << setw(1);
        break;
        
      case 1:
        TraceFile << static_cast<UINT32>(*static_cast<UINT8*>(ea));
        break;
        
      case 2:
        TraceFile << *static_cast<UINT16*>(ea);
        break;
        
      case 4:
        TraceFile << *static_cast<UINT32*>(ea);
        break;
        
      case 8:
        TraceFile << *static_cast<UINT64*>(ea);
        break;
        
      default:
        TraceFile.unsetf(ios::showbase);
        TraceFile << setw(1) << "0x";
        for (INT32 i = 0; i < size; i++)
        {
            TraceFile << static_cast<UINT32>(static_cast<UINT8*>(ea)[i]);
        }
        TraceFile.setf(ios::showbase);
        break;
    }
}

static VOID RecordMem(VOID * ip, CHAR r, VOID * addr, INT32 size, BOOL isPrefetch)
{
    TraceFile << ip << ": " << r << " " << setw(2+2*sizeof(ADDRINT)) << addr << " "
              << dec << setw(2) << size << " "
              << hex << setw(2+2*sizeof(ADDRINT));
    if (!isPrefetch)
        EmitMem(addr, size);
    TraceFile << endl;
}
int get_type(int size) //dummy, fill it out
{
            
	return size;
}

int get_state() //dummy, fill it out
{
	return 0;
}

const char * StripPath(const char * path)
{
    const char * file = strrchr(path,'/');
    if (file)
        return file+1;
    else
        return path;
}
#if 1
//VOID save_state(void * counter,ADDRINT r) 
VOID save_state() //save the state to a file. Function is called automatically whenever a dummy save() is called from the loaded application
{
	//printf("saving state %p %x\n",counter,r);
	printf("saving state\n");
}

VOID restore_state(ADDRINT s) //restore memory state to state s
{
	int st_n = (int)s;
	//printf("saving state %p %x\n",counter,r);
	printf("restoring state: %d\n",st_n);
}


#endif

    


VOID Routine(RTN rtn, VOID *v)
{
    string _name;
    string _image;
    _name = RTN_Name(rtn);
    _image = StripPath(IMG_Name(SEC_Img(RTN_Sec(rtn))).c_str());
    ADDRINT _address = RTN_Address(rtn);
     RTN_Open(rtn);
	//int dummy=0;
	//printf(">>>>>procedure:[%s][%s][%s][%d][%d]\n",_name.c_str(),_image.c_str(),bin_name,strcmp(_name.c_str(),"save"),strcmp(_image.c_str(),bin_name));	
	if(strcmp(_name.c_str(),"save")==0 && strcmp(_image.c_str(),bin_name)==0)
	{
		printf("procedure matched:[%s][%s][%x]\n",_name.c_str(),_image.c_str(),_address);	
		RTN_InsertCall(rtn, IPOINT_BEFORE, (AFUNPTR)save_state, IARG_END);
 //       RTN_InsertCall(rtn, IPOINT_BEFORE, (AFUNPTR)save_state, IARG_PTR, v,IARG_END);


	}
	
	if(strcmp(_name.c_str(),"restore")==0 && strcmp(_image.c_str(),bin_name)==0)
	{
		printf("procedure matched:[%s][%s][%x]\n",_name.c_str(),_image.c_str(),_address);	
		//RTN_InsertCall(rtn, IPOINT_BEFORE, (AFUNPTR)save_state, IARG_END);
        RTN_InsertCall(rtn, IPOINT_BEFORE, (AFUNPTR)restore_state,IARG_FUNCARG_ENTRYPOINT_VALUE, 0,IARG_END);


	}
	
	RTN_Close(rtn);

}
static VOID RecordWriteAddrSize(VOID * addr, INT32 size,VOID * p)
{
    WriteAddr = addr;
    WriteSize = size;
    //unsigned int a = (unsigned int)addr;
    //TraceFile << a <<" "<<a+1<<" "<<a+2<<" "<<a+3<< ": " <<  size << " "<<p <<" ";
    //printf("%p\n",*addr);
    //int *p = a;
    fprintf(trace,"%p:",p);
   // fprintf(trace,"%p: W %x %x %x %x %x \n", p, a, a +1 ,a+2, a+3, size);
    //fprintf() 
//    unsigned char* pt = a;
    //TraceFile << i << ": " << j<<" ";
//  
#if 0
    if(size==4)
    {
		unsigned char* pt = (unsigned char *)addr;
		char i = *pt;
        char j = *(pt+1);
        char c = *(pt+2);
        char d = *(pt+3); 
		int i1=(int)i;
		int j1=(int)j;
		int c1=(int)c;
		int d1=(int)d;
		
        fprintf(trace,"%x %x %x %x\n",i1,j1,c1,d1);
    }
#endif
   //<<*(addr+1)  <<  *(addr+2) << *(addr+3) <<" ";
   // create_data(pt,size);
    //copy_vm(v,a,type,state,NULL,NULL);
    //copy_vm_data(v,addr,type,state,NULL); //
    set_fp(trace);
	int type = get_type(size);
	int state = get_state(); 
    add_to_list(addr,type,state);
    //exit(0);
    //save_data();
    TraceFile << endl;
}


static VOID RecordMemWrite(VOID * ip)
{
    RecordMem(ip, 'W', WriteAddr, WriteSize, false);
}

VOID Instruction(INS ins, VOID *v)
{
    // instruments stores using a predicated call, i.e.
    // the call happens iff the store will be actually executed
    if (INS_IsMemoryWrite(ins))
    {
        INS_InsertPredicatedCall(
            ins, IPOINT_BEFORE, (AFUNPTR)RecordWriteAddrSize,
            IARG_MEMORYWRITE_EA,
            IARG_MEMORYWRITE_SIZE,
            IARG_INST_PTR,
            IARG_END);
        
#if 0
        if (INS_HasFallThrough(ins))
        {
            INS_InsertCall(
                ins, IPOINT_AFTER, (AFUNPTR)RecordMemWrite,
                IARG_INST_PTR,
                IARG_END);
        }
        if (INS_IsBranchOrCall(ins))
        {
            INS_InsertCall(
                ins, IPOINT_TAKEN_BRANCH, (AFUNPTR)RecordMemWrite,
                IARG_INST_PTR,
                IARG_END);
        }
#endif
        
    }
}

/* ===================================================================== */

VOID Fini(INT32 code, VOID *v)
{
    TraceFile << "#eof" << endl;
    
    TraceFile.close();
    if(trace)
	 fclose(trace);
}

/* ===================================================================== */
/* Main                                                                  */
/* ===================================================================== */

int main(int argc, char *argv[])
{
    string trace_header = string("#\n"
                                 "# Memory Access Trace Generated By Pin\n"
                                 "#\n");
    
	// Initialize symbol table code, needed for rtn instrumentation
    PIN_InitSymbols();

    if( PIN_Init(argc,argv) )
    {
        return Usage();
    }
    
	bin_name = StripPath(argv[argc-1]);
    printf("bin name: %s\n",bin_name);
    trace = fopen("pinatrace2.out", "w");

    TraceFile.open(KnobOutputFile.Value().c_str());
    TraceFile.write(trace_header.c_str(),trace_header.size());
    TraceFile.setf(ios::showbase);
    
    INS_AddInstrumentFunction(Instruction, 0);
    RTN_AddInstrumentFunction(Routine, 0);
    PIN_AddFiniFunction(Fini, 0);

    // Never returns
	
    PIN_StartProgram();
    
    RecordMemWrite(0);
    RecordWriteAddrSize(0, 0,0);
    
    return 0;
}

/* ===================================================================== */
/* eof */
/* ===================================================================== */

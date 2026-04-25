#include <stdio.h>
#include "read_and_write.h"
#include "storage_manage.h"
#include "start_manage.h"

/*
1024 bytes are for managing start pointers of messages
480 messages are allowed
*/

// this is to store the message
int store_message(int length,char msg[],int memory[1024][1024][8],int register_no)
{
    if(register_no<0||register_no>=480)
        return -3;
    int info=read(0,register_no/8,memory);
    if(((info>>(7-register_no%8))&1)==1)
        return -2;
    int ptr=store(length,msg,0,memory);
    if(ptr==-1)
        return -1;
    write(0,register_no/8,info|(1<<(7-register_no%8)),memory);
    write(0,60+register_no*2,ptr>>8,memory);
    write(0,61+register_no*2,ptr&((1<<8)-1),memory);
    return 0;
}

// this is to delete a message
int delet_message(int memory[1024][1024][8],int register_no)
{
    if(register_no<0||register_no>=480)
        return -3;
    int info=read(0,register_no/8,memory);
    if(((info>>(7-register_no%8))&1)==0)
        return -2;
    int ptr=(read(0,60+register_no*2,memory)<<8)|(read(0,61+register_no*2,memory));
    delet(ptr,memory);
    write(0,register_no/8,info^(1<<(7-register_no%8)),memory);
    return 0;
}
#include "storage_manage.h"
#include "read_and_write.h"

// this is for storing locations of messages
int store(int length,char msg[],int ctr,int memory[1024][1024][8])
{
    if(ctr==length)
        return 0;
    for(int i=1;i<1024;i++)
    {
        for(int j=0;j<64;j++)
        {
            if(((read(i,j*16,memory)>>7)&1)==1)
                continue;
            int info=(1<<7)|(msg[ctr]);
            ctr++;
            write(i,j*16,info,memory);
            for(int k=j*16+1;k<j*16+14;k++)
            {
                if(ctr<length)
                {
                    info=msg[ctr];
                    ctr++;
                    write(i,k,info,memory);
                }
                else
                    break;
            }
            info=store(length,msg,ctr,memory);
            write(i,j*16+14,info>>8,memory);
            write(i,j*16+15,info&((1<<8)-1),memory);
            return (j<<10)|i;
        }
    }
    return -1;
}

// this us for deleting
int delet(int ptr,int memory[1024][1024][8])
{
    if(ptr==0)
        return 0;
    int j=ptr>>10;
    int i=ptr&((1<<10)-1);
    if(j<0||j>+64||i<0||i>+1024)
        return -1;
    write(i,j*16,0,memory);
    ptr=(read(i,j*16+14,memory)<<8)+read(i,j*16+15,memory);
    return delet(ptr,memory);
}
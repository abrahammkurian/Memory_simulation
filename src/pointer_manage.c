#include "storage_manage.h"
#include "pointer_manage.h"

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
            write(i,j*16+15,info&255,memory);
            return (j<<10)|i;
        }
    }
    return -1;
}
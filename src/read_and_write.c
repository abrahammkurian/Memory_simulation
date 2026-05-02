#include "read_and_write.h"

memory[1024][1024][8];

// writing will be done here
int write(int x,int y,int info)
{
    for(int i=0;i<8;i++)
        memory[x][y][i]=(info>>i)&1;
    return 0;
}

// reading will be done here
int read(int x,int y)
{
    int info=0;
    for(int i=0;i<8;i++)
        info=info|(memory[x][y][i]<<i);
    return info;
}
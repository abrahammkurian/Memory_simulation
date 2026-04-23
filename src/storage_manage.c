#include "storage_manage.h"

// writing will be done here
int write(int x,int y,int info,int memory[1024][1024][8])
{
    if(x>=0&&x<1024&&y>=0&&y<1024&&info>=0&&info<256)
    {
        for(int i=0;i<8;i++)
            memory[x][y][i]=(info>>i)&1;
        return 0;
    }
    return -1;
}

// reading will be done here
int read(int x,int y,int memory[1024][1024][8])
{
    int info=0;
    if(x>=0&&x<1024&&y>=0&&y<1024)
    {
        for(int i=0;i<8;i++)
        {
            if(memory[x][y][i]==0||memory[x][y][i]==1)
                info=info|(memory[x][y][i]<<i);
            else
                return -1;
        }
        return info;
    }
    return -1;
}
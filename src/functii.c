#include "functii.h"
// pentru functia de selectare a taskului

int selectare(char nume[])
{
    int i,nr=0;
    for(i=0;i<strlen(nume);i++)
    {
        if(nume[i]>='0' && nume[i]<='9')
        {
            nr += nr * 10 + (int)nume[i]-48;
        }
    }
    
    if(nr <=5) return 1;
    if(nr >=6 && nr <= 10) return 2;
    if(nr >=11 && nr <= 15) return 3;
    else return 4;
}
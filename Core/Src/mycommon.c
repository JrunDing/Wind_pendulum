#include <stdint.h>
#include "mycommon.h"



int16_t myAbs(int16_t p)
{
    int16_t q;
    q=p>0?p:(-p);
    return q;
}


void myLimit(int *val,int min,int max)
{
    if(*val<0)
    {
        if(*val>(-min))
        {
            *val=-min;
        }
        if(*val<(-max))
        {
            *val=-max;
        }
    }
    if(*val>0)
    {
        if(*val>max)
        {
            *val=max;
        }
        if(*val<min)
        {
            *val=min;
        }
    }
}



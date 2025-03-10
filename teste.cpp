#include "./lib/branqs.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    setSPIdelay(1);
    int x = getSPIdelay();

    printf("%d\n", x);

    while(1)
    {
        setDigitalOutput(0, 0);
        setDigitalOutput(0, 255);
    }
    return 0;
}
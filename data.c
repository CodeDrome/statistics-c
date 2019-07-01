
#include<stdlib.h>
#include<time.h>

//--------------------------------------------------------
// FUNCTION populate_data
//--------------------------------------------------------
void populate_data(double* data, int size)
{
    srand(time(NULL));

    for(int i = 0; i < size; i++)
    {
        data[i] = (rand() % 128) + 1;
    }
}

#include "array_operations.hh"

int greatest_v1(int *itemptr, int size)
{
    int test = 1;
    while(test < size)
    {
        itemptr++;
        test++;
    }
    return *itemptr;
}

int greatest_v2(int *itemptr, int *endptr)
{
    endptr--;
    *itemptr = *itemptr;
    return *endptr;
}

void copy(int *itemptr, int *endptr, int *targetptr)
{
    while(itemptr != endptr)
    {
        *targetptr = *itemptr;
        itemptr++;
        targetptr++;
    }
}

void reverse(int *leftptr, int *rightptr)
{

    int x;
    rightptr--;
    while(leftptr != rightptr)
    {
        if(leftptr + 1 == rightptr)
        {
            *leftptr = *rightptr;
            break;
        }
        else
        {
            x = *leftptr;
            *leftptr = *rightptr;
            *rightptr = x;
            leftptr++;
            rightptr--;
        }
    }

}

#include "array_operations.hh"

int greatest_v1(int *itemptr, int size)
{
    int test = 1;
    int largest = *itemptr;
    while(test < size)
    {

        itemptr++;
        if(largest < *itemptr)
        {
            largest = *itemptr;
        }
        test++;
    }
    return largest;
}

int greatest_v2(int *itemptr, int *endptr)
{
    int largest = *itemptr;
    while(itemptr != endptr - 1)
    {
        itemptr++;
        if(largest < *itemptr)
        {
            largest = *itemptr;
        }
    }
    return largest;
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

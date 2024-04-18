#include <iostream>
#define TYPE int
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;


	    TYPE* sort(TYPE* arr,int first,int last,bool up=true)
	    {



	    	for (int i = first; i < last; i++)
	    	    {
	    	        int j = i + 1;
	    	        TYPE tmp = arr[j];

	    	        if(up)
	    	        {
	    	        	 while (j > first && tmp < arr[j-1])
	    	        		{
	    	        		   arr[j] = arr[j-1];
	    	        	       j--;
	    	        	    }
	    	        	 arr[j] = tmp;

	    	        }
	    	        else
	    	        {
	    	       	    while (j > first && tmp > arr[j-1])
	    	       	    		{
	    	          		   arr[j] = arr[j-1];
	    	       	 	       j--;
	    	       	    	    }
	    	       	   arr[j] = tmp;

	    	       	 }




	    	    }
	    	return arr;

	    }



TYPE * Merge(TYPE* arr1,TYPE*arr2,int first1, int last1, int first2,int last2)
{
    int firstin=first1,secondin=first2;
    int current = 0;
    TYPE *merged = new TYPE [last1-first1+1 + last2-first2+1];
    while(firstin<=last1&&secondin<=last2)
    {
        //printf("Comparing %d:%d with %d:%d\n",firstin,arr1[firstin],secondin,arr2[secondin]);
        if(arr1[firstin]<arr2[secondin])
        {
            merged[current++] = arr1[firstin++];

        }
        else
        {
            merged[current++] = arr2[secondin++];

        }
    }

    while(secondin<=last2)
    {
            merged[current++] = arr2[secondin++];
    }

    while(firstin<=last1)
    {
            merged[current++] = arr1[firstin++];
    }


    return merged;
}

void WriteArray(TYPE*arr,int first,int last)
{
	for(int i = first;i<=last;i++)
	{
		printf("%d, ",arr[i]);

	}
	printf("\r\n");

}

int** GenerateIndexes(TYPE*source,TYPE**&arr,int arrlength,int&threadcount)
{
    printf("Length %d sorted by %d threads\n",arrlength,threadcount);
     if(threadcount>arrlength)
    {
        threadcount=arrlength;
    }
    int**indexes = new int*[2];
    for(int i =0;i<2;i++)
    {
        indexes[i] =new int [threadcount];
    }

    int part = arrlength/threadcount;
    int real = part;
    int first=0,last = 0;
    for(int i = 0;i<threadcount;i++)
    {
        if(i<arrlength%threadcount)
        {
            real = part+1;
        }
        else
        {
            real = part;
        }
        last = first + real-1;
        indexes[0][i] = first;
        indexes[1][i] = last;

        arr[i] = sort(source,first,last);
         printf("Sorted %d\n",i);
        //WriteArray(arr[i],first,last);
       // printf("%d - %d\n",first,last);
        first +=real;
    }
    return indexes;
}

TYPE* MultiMerge(TYPE** arrays,int num,int*starts,int*ends)
{

    TYPE* multimerged = arrays[0];/*
        multimerged = Merge(multimerged,arrays[1],starts[0],ends[0] ,starts[1],ends[1]);
        multimerged = Merge(multimerged,arrays[2],starts[0],ends[1] ,starts[2],ends[2]);
        multimerged = Merge(multimerged,arrays[3],starts[0],ends[2] ,starts[3],ends[3]);
        multimerged = Merge(multimerged,arrays[4],starts[0],ends[3] ,starts[4],ends[4]);*/
         /*printf("%d\t%d\t%d\t%d\n",starts[0],ends[0] ,starts[1],ends[1]);
        printf("%d\t%d\t%d\t%d\n",starts[0],ends[1] ,starts[2],ends[2]);
        printf("%d\t%d\t%d\t%d\n",starts[0],ends[2] ,starts[3],ends[3]);
        printf("%d\t%d\t%d\t%d\n",starts[0],ends[3] ,starts[4],ends[4]);*/
    for(int i = 0;i<num-1;i++)
    {
       // printf("TEST:\t%d\t%d\t%d\t%d\n",starts[0],ends[i] ,starts[i+1],ends[i+1]);
        multimerged = Merge(multimerged,arrays[i+1],starts[0],ends[i] ,starts[i+1],ends[i+1]);

    }

    return multimerged;

}


int main()
{
    srand(time(nullptr));
     int length = 79262,threads = 86;
    TYPE* arr = new TYPE[length];
    printf("Generating\n");
    for(int i = 0;i<length;i++)
    {
        arr[i] = rand()%400-200;
    }
    //arr[8] = 1000000;
 printf("Generated\n");
    //WriteArray(arr,0,length-1);
    TYPE** sorts = new TYPE*[threads];
     printf("Sorting\n");
    int** startsends = GenerateIndexes(arr,sorts,length,threads);
    //WriteArray(startsends[0],0,threads-1);
   // WriteArray(startsends[1],0,threads-1);

    TYPE* merged = MultiMerge(sorts,threads,startsends[0],startsends[1]);

   // WriteArray(merged,0,length-1);
    printf("Sorted\n");

    delete [] arr;
    for(int i = 0;i<threads;i++)
    {
        delete []sorts[i];
    }
    for(int i = 0;i<2;i++)
    {

       delete []startsends[i];
    }
    delete [] sorts;
    delete []startsends;
    delete [] merged;
    return 0;
}

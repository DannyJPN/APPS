#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

void WriteArray(int [],int,int,int);
void BubbleSort(int[],int,int,int);
void  SelectSort(int[],int,int,int);
void  InsertSort(int[],int,int,int);
void QuickSort(int[],int,int,int);
int* BubbleSorted(int arr[],int begin,int end,int size)
{
    int* array = new int[size];
    copy(arr,arr+size,array);
    BubbleSort(array,begin,end,sizeof(array)/sizeof(int));

    return array;
}
int*  SelectSorted(int arr[],int begin,int end,int size)
{
   int* array = new int[size];
    copy(arr,arr+size,array);
    SelectSort(array,begin,end,sizeof(array)/sizeof(int));

    return array;
}
int*  InsertSorted(int arr[],int begin,int end,int size)
{
    int* array = new int[size];
    copy(arr,arr+size,array);
    InsertSort(array,begin,end,sizeof(array)/sizeof(int));

    return array;
}
int* QuickSorted(int arr[],int begin,int end,int size)
{
    int* array = new int[size];
    copy(arr,arr+size,array);
    QuickSort(array,begin,end,sizeof(array)/sizeof(int));

    return array;
}

void WriteArray(int* array,int border1,int border2,int size)
{

    for(int i =0;i<size;i++)
    {
        cout<<array[i]<<",";
        if(i+1==border1||i+1==border2)
        {
            cout<<"\t";
        }
    }
    cout<<endl;
}

int * Merge(int* arr1,int*arr2,int size1,int size2)
{
    int firstin=0,secondin=0;
    int current = 0;
    int *merged = new int [size1+size2];
    while(firstin<size1&&secondin<size2)
    {
        if(arr1[firstin]<arr2[secondin])
        {
            merged[current++] = arr1[firstin++];

        }
        else
        {
            merged[current++] = arr2[secondin++];

        }
    }

    while(secondin<size2)
    {
            merged[current++] = arr2[secondin++];
    }

    while(firstin<size1)
    {
            merged[current++] = arr1[firstin++];
   }


    return merged;
}

int main()
{
    srand(time(nullptr));
    int size = rand()%3 +2;
    int*bub=new int [size];
    int*sel=new int [size];
    int*in=new int [size];
    int*qui=new int [size];

  for(int i = 0;i<size;i++)
    {
        bub[i] = rand()%1000 -500;
        sel[i] = rand()%1000 -500;
        in[i] = rand()%1000 -500;
        qui[i] = rand()%1000 -500;

    }


    WriteArray(bub,0,size,size);
    WriteArray(sel,0,size,size);
    WriteArray(in,0,size,size);
    WriteArray(qui,0,size,size);


    int*bubs=BubbleSorted(bub,0,size-1,size);
    int*sels=SelectSorted(sel,0,size-1,size);
    int*ins=InsertSorted(in,0,size-1,size);
    int*quis=QuickSorted(qui,0,size,size);
cout<<"________________________________________"<<endl;
    WriteArray(bubs,0,size,size);
    WriteArray(sels,0,size,size);
    WriteArray(ins,0,size,size);
    WriteArray(quis,0,size,size);
cout<<"________________________________________"<<endl;
    int* bubsel = Merge(bubs,sels,size,size);
    WriteArray(bubsel,0,size*2,size*2);
    int* bubselin = Merge(bubsel,ins,2*size,size);
    WriteArray(bubselin,0,size*3,size*3);
    int* bubselinqui = Merge(bubselin,quis,3*size,size);
    WriteArray(bubselinqui,0,size*4,size*4);

delete bub,sel,in,qui;
delete bubs,sels,ins,quis;

    return 0;
}




void  BubbleSort(int array[],int begin,int end,int size)
{
for(int i = begin; i < end ; i++)
    {
        for(int j = begin; j < end  ; j++)
        {
            if(array[j+1] < array[j]){
                int tmp = array[j + 1];
                array[j + 1] = array[j];
                array[j] = tmp;
            }
        }

    }
}

void InsertSort(int array[],int begin,int end,int size)
{

for (int i = begin; i < end; i++)
    {
        int j = i + 1;
        int tmp = array[j];
        while (j > begin && tmp < array[j-1])
        {
            array[j] = array[j-1];
            j--;
        }
        array[j] = tmp;
    }
}

void SelectSort(int array[],int begin,int end,int size)
{

 for (int i = begin; i < end; i++)
    {
         int maxIndex = i;
         for (int j = i + 1; j < end+1; j++)
         {
             if (array[j] < array[maxIndex]) maxIndex = j;
         }
         int tmp = array[i];
         array[i] = array[maxIndex];
         array[maxIndex] = tmp;
     }
}
void QuickSort(int array[],int begin,int end,int size)
{
 if(begin < end){
        int boundary = begin;
        for(int i = begin + 1; i < end; i++){
            if(array[i] < array[begin]){
                swap(array[i], array[++boundary]);
            }
        }
        swap(array[begin],array[ boundary]);
        QuickSort(array, begin, boundary,size);
        QuickSort(array, boundary + 1, end,size);
    }
}




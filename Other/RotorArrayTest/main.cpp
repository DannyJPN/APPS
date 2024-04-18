#include <iostream>

using namespace std;

void rot(int a[],int size,bool dir)
{
   if(dir)
        {
        int p = a[size-1];
        for(int i = size-1;i>0;i--)
        {
            a[i]=a[i-1];
        }
        a[0]=p;

        }
    else
        {
             int p = a[0];
            for(int i = 0;i<size-1;i++)
            {
                a[i]=a[i+1];
            }
            a[size-1]=p;
        }




}

void write(int a[],int size)
{
for(int i =0;i<size;i++)
    {
    cout<<a[i]<<",";
    }
    cout<<endl;
}

int main()
{
    int ar[] ={1,2,3,4,5,6,7,8,9,10};

    for(int i =0;i<5;i++)
    {
    write(ar,sizeof(ar)/4);
    rot(ar,sizeof(ar)/4,true);
    }
    cout<<"_____________________"<<endl;
for(int i =0;i<5;i++)
    {
    write(ar,sizeof(ar)/4);
    rot(ar,sizeof(ar)/4,false);
    }



    return 0;
}

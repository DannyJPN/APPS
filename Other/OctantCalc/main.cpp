#include <iostream>
#include <cmath>
using namespace std;

int Octant(int& x,int& y)
{
    if(abs(x)> abs(y))
    {
        //1,4,5,8
        if(x>=0 && y>=0)
        {
            return 1;
        }
        else if(x<0 && y>=0)
        {
            return 4;
        }
        else if(x<0 && y<0)
        {
            return 5;
        }
        else if(x>=0 && y<0)
        {
            return 8;
        }


    }
    else
    {
        //2,3,6,7
        if(x>=0 && y>=0)
        {
            return 2;
        }
        else if(x<0 && y>=0)
        {
            return 3;
        }
        else if(x<0 && y<0)
        {
            return 6;
        }
        else if(x>=0 && y<0)
        {
            return 7;
        }

    }
    return 0;

}





int main()
{

int x=-6;
int y=-6;
    int o = Octant(x,y);
    cout<<o<<endl;


    return 0;
}

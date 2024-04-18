#include <iostream>
#include <string>
using namespace std;

 class Point
{
public:
    int x,y;
    Point(int x,int y)
    {
        this->x=x;
        this->y = y;
    }
    Point()
    {
     Point(0,0) ;
    }
    void ToString()
    {
        cout<<"X:"<<this->x<<"\tY:"<<this->y<<endl;
    }
};

void Exchange(int&a,int&b)
{
    int p = a;
    a=b;
    b=p;
}
Point CalcPoint(Point*& point,int octant)
{
switch(octant)
    {
    case 1:{    break;}

    case 2:{Exchange(point->x,point->y);  break;}

    case 3:{Exchange(point->x,point->y); point->x *= -1;break;}

    case 4:{point->x *= -1; break;}

    case 5:{point->x *= -1;point->y *= -1;break;}

    case 6:{Exchange(point->x,point->y);point->x *= -1;point->y *= -1;break;}

    case 7:{Exchange(point->x,point->y);point->y *= -1;break;}

    case 8:{point->y *= -1;break;}

    default:{break;}




    }


}
Point RevertPoint(Point*& point,int originoctant)
{
switch(originoctant)
    {
    case 1:{    break;}

    case 2:{Exchange(point->x,point->y);  break;}

    case 3:{point->x *= -1;Exchange(point->x,point->y); break;}

    case 4:{point->x *= -1; break;}

    case 5:{point->x *= -1;point->y *= -1;break;}

    case 6:{Exchange(point->x,point->y);point->x *= -1;point->y *= -1;break;}

    case 7:{point->y *= -1;Exchange(point->x,point->y);break;}

    case 8:{point->y *= -1;break;}

    default:{break;}




    }


}



int main()
{

    for(int i = 1;i<9;i++)
    {
        Point * p = new Point(2,4);
    p->ToString();
    CalcPoint(p,i);
    cout<<"to "<<i<<". octant"<<endl;
    p->ToString();
    RevertPoint(p,i);
    cout<<"from "<<i<<". octant"<<endl;
    p->ToString();
delete p;
cout<<"_____________________________"<<endl;
    }


    return 0;
}

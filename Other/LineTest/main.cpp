

// **************************************************************************
//
//               Demo program for labs
//
// Subject:      Computer Architectures and Parallel systems
// Author:       Petr Olivka, petr.olivka@vsb.cz, 08/2016
// Organization: Department of Computer Science, FEECS,
//               VSB-Technical University of Ostrava, CZ
//
// File:         Main program for LCD module
//
// **************************************************************************

//#include "mbed.h"

//Serial pc( USBTX, USBRX );
#include <stdlib.h>
//#include "lcd_lib.h"
#include "stdio.h"
// two dimensional array with fixed size font
//extern uint8_t font8x8[ 256 ][ 8 ];
class AbstPoint
{
public:
    int x;
    int y;
    AbstPoint(int xx,int yy)
    {
        x=xx;
        y=yy;
    }
};


class Point
{
public:
    int x,y;
    int forecolor,backcolor; //0xRRGGBB
    Point(int xp,int yp,int fore,int back):x(xp),y(yp),forecolor(fore),backcolor(back)
    {

    }
    void LCD_put_pixel(int x,int y,int c)
    {

        printf("X:%d\tY:%d\tColor: %x\n",x,y,c);
    }
    virtual void Display(int x=0,int y=0)
    {


        LCD_put_pixel(x,y,To16(forecolor));

    }
    virtual void Hide(int x=0,int y=0)
    {
        LCD_put_pixel(x,y,To16(backcolor));

    }
    int To16(int color32)
    {
        int r = (color32 >> 16)& 0x0000FF,g=(color32 >>8)& 0x0000FF,b=color32 & 0x0000FF;
        int rgb16 = (b >>3)| ((g >>2) <<5) | ((r>>3)<<11);
        return rgb16;
    }

};

class Line: public Point
{
    public:
        int xk,yk;
    Line(int x1,int y1,int x2,int y2,int fore,int back):Point(x1,y1,fore,back),xk(x2),yk(y2)
    {


    }
    void Display(int x1 = 0,int y1 =0,int x2 =0,int y2 =0)
    {
        int x, y, dx, dy, p;
        //AbstPoint *abst;
        dx = x2 - x1;
        dy = y2 - y1;

    int origin = Octant(dx,dy);

        printf("Octant:%d\n",origin);



        switch(origin)
        {
        case 1:
            {
            y = y1;
             p = 2 * dy - dx;         // prediktor

                for (x = x1; x <= x2; x++)
                {
                    //printf("X:%d\tY:%d\n",x,y);
                    Point::Display(x,y);
                    if (p >= 0)
                    {
                        y++;             // presun na dalsi radek
                        p = p + 2 * dy - 2 * dx;
                    }
                    else
                    {
                        p = p + 2 * dy;
                    }
                }

            break;


            }

        case 2:
            {
                x = x1;
                 p = 2 * dx - dy;         // prediktor

                for (y = y1; y <= y2; y++)
                {
                    //printf("X:%d\tY:%d\n",x,y);
                    Point::Display(x,y);
                    if (p >= 0)
                    {
                        x++;             // presun na dalsi radek
                        p = p + 2 * dx - 2 * dy;
                    }
                    else
                    {
                        p = p + 2 * dx;
                    }
                }





            break;
            }

        case 3:
            {
                x = x1;
                 p = -2 * dx - dy;         // prediktor

                for (y = y1; y <= y2; y++)
                {
                    //printf("X:%d\tY:%d\n",x,y);
                    Point::Display(x,y);
                    if (p >= 0)
                    {
                        x--;             // presun na dalsi radek
                        p = p - 2 * dx - 2 * dy;
                    }
                    else
                    {
                        p = p + -2 * dx;
                    }
                }
            break;
            }

        case 4:
            {
                 y = y1;
             p = 2 * dy + dx;         // prediktor

                for (x = x1; x >= x2; x--)
                {
                    //printf("X:%d\tY:%d\n",x,y);
                    Point::Display(x,y);
                    if (p >= 0)
                    {
                        y++;             // presun na dalsi radek
                        p = p + 2 * dy + 2 * dx;
                    }
                    else
                    {
                        p = p + 2 * dy;
                    }
                }

            break;
            }

        case 5:
            {
               y = y1;
             p = -2 * dy + dx;         // prediktor

                for (x = x1; x >= x2; x--)
                {
                    //printf("X:%d\tY:%d\n",x,y);
                    Point::Display(x,y);
                    if (p >= 0)
                    {
                        y--;             // presun na dalsi radek
                        p = p - 2 * dy + 2 * dx;
                    }
                    else
                    {
                        p = p - 2 * dy;
                    }
                }


            break;
            }

        case 6:
            {
               x = x1;
                 p = -2 * dx + dy;         // prediktor

                for (y = y1; y >= y2; y--)
                {
                    //printf("X:%d\tY:%d\n",x,y);
                    Point::Display(x,y);
                    if (p >= 0)
                    {
                        x--;             // presun na dalsi radek
                        p = p - 2 * dx + 2 * dy;
                    }
                    else
                    {
                        p = p - 2 * dx;
                    }
                }


            break;
            }

        case 7:
            {
                 x = x1;
                 p = 2 * dx + dy;         // prediktor

                for (y = y1; y >= y2; y--)
                {
                    //printf("X:%d\tY:%d\n",x,y);
                    Point::Display(x,y);
                    if (p >= 0)
                    {
                        x++;             // presun na dalsi radek
                        p = p + 2 * dx + 2 * dy;
                    }
                    else
                    {
                        p = p + 2 * dx;
                    }
                }



            break;
            }

        case 8:
            {
               y = y1;
             p = -2 * dy - dx;         // prediktor

                for (x = x1; x <= x2; x++)
                {
                    //printf("X:%d\tY:%d\n",x,y);
                    Point::Display(x,y);
                    if (p >= 0)
                    {
                        y--;             // presun na dalsi radek
                        p = p - 2 * dy - 2 * dx;
                    }
                    else
                    {
                        p = p - 2 * dy;
                    }
                }


            break;
            }




        }






    }


    int Octant(int x,int y)
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


};




int main()
{


Line *l1=new Line(100,100,120,110,0x00FF00,0x0000FF);
l1->Display(l1->x, l1->y,l1->xk,l1->yk);
printf("_________________________________\n");
Line *l2=new Line(100,100,120,130,0x00FF00,0x0000FF);
l2->Display(l2->x, l2->y,l2->xk,l2->yk);
printf("_________________________________\n");
Line *l3=new Line(100,100,90,120,0x00FF00,0x0000FF);
l3->Display(l3->x, l3->y,l3->xk,l3->yk);
printf("_________________________________\n");
Line *l4=new Line(100,100,80,110,0x00FF00,0x0000FF);
l4->Display(l4->x, l4->y,l4->xk,l4->yk);
printf("_________________________________\n");

Line *l5=new Line(100,100,80,90,0x00FF00,0x0000FF);
l5->Display(l5->x, l5->y,l5->xk,l5->yk);
printf("_________________________________\n");
Line *l6=new Line(100,100,90,80,0x00FF00,0x0000FF);
l6->Display(l6->x, l6->y,l6->xk,l6->yk);
printf("_________________________________\n");
Line *l7=new Line(100,100,110,80,0x00FF00,0x0000FF);
l7->Display(l7->x, l7->y,l7->xk,l7->yk);
printf("_________________________________\n");
Line *l8=new Line(100,100,120,90,0x00FF00,0x0000FF);
l8->Display(l8->x, l8->y,l8->xk,l8->yk);
printf("_________________________________\n");


    return 0;
}

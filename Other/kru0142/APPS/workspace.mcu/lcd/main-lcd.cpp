

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

#include "mbed.h"

Serial pc( USBTX, USBRX );
#include <stdlib.h>
#include "lcd_lib.h"
#include "stdio.h"
// two dimensional array with fixed size font
extern uint8_t font8x8[ 256 ][ 8 ];



class Point
{
public:
    int x,y;
    int forecolor,backcolor; //0xRRGGBB
    Point(int xp,int yp,int fore,int back):x(xp),y(yp),forecolor(fore),backcolor(back)
    {

    }/*
    void LCD_put_pixel(int x,int y,int c)
    {

        printf("X:%d\tY:%d\tColor: %x\n",x,y,c);
    }*/
    virtual void Display(int x=0,int y=0)
    {


        LCD_put_pixel(x,y,To16(forecolor));

    }
    virtual void Hide(int x=0,int y=0)
    {

        //LCD_put_pixel(x,y,To16(backcolor));
    	int p =forecolor;
    	forecolor=backcolor;
    	backcolor=p;
    	Display(x,y);
    	 p =forecolor;
    	    	forecolor=backcolor;
    	    	backcolor=p;


    }
    int To16(int color32)
    {
        int r = (color32 >> 16)& 0x0000FF,g=(color32 >>8)& 0x0000FF,b=color32 & 0x0000FF;
        int rgb16 = (b >>3)| ((g >>2) <<5) | ((r>>3)<<11);
        return rgb16;
    }

};

class Symbol: public Point
{
public:
    char sym;
    Symbol(int x,int y,int fore,int back,char s):sym(s),Point(x,y,fore,back)
    {


    }
    virtual void Display(int x0 = 0,int y0 =0)
    {

        for(int j = 0;j<8;j++)
        {
            for(int i = 0;i<8;i++)
            {
                if(font8x8[sym][j] & (1<<i))
                {
                    Point::Display(x0+4*i, y0+4*j);
                    Point::Display(x0+4*i+1,y0+ 4*j);
                    Point::Display(x0+4*i, y0+4*j+1);
                    Point::Display(x0+4*i+1, y0+4*j+1);

                }

                else
                    {
                    Point::Hide(x0+4*i,y0+4*j);
                    Point::Hide(x0+4*i+1,y0+4*j);
                    Point::Hide(x0+4*i,y0+4*j+1);
                    Point::Hide(x0+4*i+1,y0+4*j+1);

                    }


            }



        }

    }

};

class Line: public Point
{
    public:
    Line(int x1,int y1,int x2,int y2,int fore,int back):Point(x1,y1,fore,back),xk(x2),yk(y2)
    {


    }

    void Hide(int x1 = 0,int y1 =0,int x2 =0,int y2 =0)
        {
    	int p =this->forecolor;
this->forecolor=this->backcolor;
this->backcolor=p;
		this->Display(x1, y1, x2, y2);
		p =this->forecolor;
		this->forecolor=this->backcolor;
		this->backcolor=p;

        }

    void Display(int x1 = 0,int y1 =0,int x2 =0,int y2 =0)
    {

    	 int x, y, dx, dy, p;
    	        //AbstPoint *abst;
    	        dx = x2 - x1;
    	        dy = y2 - y1;

    	    int origin = Octant(dx,dy);

    	        //System.out.println("Octant: "+origin);



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

    int xk,yk;





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

class Circle: public Point
{
public:
    Circle(int x1,int y1,int r,int fore,int back):Point(x1,y1,fore,back),R(r)
    {


    }
    void Display(int x0 = 0,int y0 =0)
    {
        int x = R-1;
        int y = 0;
        int dx = 1;
        int dy = 1;
        int err = dx - (R << 1);

        while (x >= y)
        {
            Point::Display(x0 + x, y0 + y);
           Point::Display(x0 + y, y0 + x);
            Point::Display(x0 - y, y0 + x);
            Point::Display(x0 - x, y0 + y);
            Point::Display(x0 - x, y0 - y);
            Point::Display(x0 - y, y0 - x);
           Point::Display(x0 + y, y0 - x);
            Point::Display(x0 + x, y0 - y);

            if (err <= 0)
            {
                y++;
                err += dy;
                dy += 2;
            }

            if (err > 0)
            {
                x--;
                dx += 2;
                err += dx - (R << 1);
            }
        }
    }
    int R;

};

class Rectangle
{
public:
	int x,y;
	int width,height;
	int fore,back;
	Rectangle(int xp,int yp,int w,int h,int forecolor,int backcolor)
	{
		x=xp;
		y=yp;
		width=w;
		height = h;
		fore=forecolor;
		back=backcolor;
	}

	void Display()
	{
		Line a(x,y,x+width,y,fore,back);
		Line b(x+width,y,x+width,y+height,fore,back);
		Line c(x+width,y+height,x,y+height,fore,back);
		Line d(x,y+height,x,y,fore,back);
		a.Display(a.x,a.y,a.xk,a.yk);
		b.Display(b.x,b.y,b.xk,b.yk);
		c.Display(c.x,c.y,c.xk,c.yk);
		d.Display(d.x,d.y,d.xk,d.yk);


	}

};

class Clock:public Circle
{

public:

	int angle=225;
	int jump;
	double ToRad(int angle)
	{
		return angle*3.14/180;

	}


	Clock(int x1,int y1,int r,int fore,int back,int j):Circle(x1,y1,r,fore,back)
	{
		jump = j;
	}

	void Display(int x0 = 0,int y0 =0)
	{
		Rectangle frame (this->x-this->R,this->y-this->R,2*this->R,this->R,this->forecolor,this->backcolor);
		frame.Display();
		Line first(this->x,this->y,this->R*cos(ToRad(225))+this->x,this->R*sin(ToRad(225))+this->y,this->forecolor,this->backcolor);
		Line second(this->x,this->y,this->R*cos(ToRad(315))+this->x,this->R*sin(ToRad(315))+this->y,this->forecolor,this->backcolor);
		first.Display(first.x,first.y,first.xk,first.yk);
		second.Display(second.x,second.y,second.xk,second.yk);
		Line prevhand(this->x,this->y,this->R*cos(ToRad(angle-90/jump))+this->x,this->R*sin(ToRad(angle-90/jump))+this->y,this->forecolor,0x000000);
		prevhand.Hide(prevhand.x,prevhand.y,prevhand.xk,prevhand.yk);
		if(angle > 315)
		{
			angle=225;
		}

		Line hand(this->x,this->y,this->R*cos(ToRad(angle))+this->x,this->R*sin(ToRad(angle))+this->y,this->forecolor,this->backcolor);
		hand.Display(hand.x,hand.y,hand.xk,hand.yk);




		int x = R-1;
		        int y = 0;
		        int dx = 1;
		        int dy = 1;
		        int err = dx - (R << 1);

		        while (x >= y)
		        {

		            Point::Display(x0 - y, y0 - x);
		           Point::Display(x0 + y, y0 - x);


		            if (err <= 0)
		            {
		                y++;
		                err += dy;
		                dy += 2;
		            }

		            if (err > 0)
		            {
		                x--;
		                dx += 2;
		                err += dx - (R << 1);
		            }
		        }


	}


};








int main()
{
    LCD_init();             // LCD initialization

    LCD_clear();            // LCD clear screen

/*  int color_red = 0xF800;
    int color_green = 0x07E0;
    int color_blue = 0x001F;
    int color_white = 0xFFFF;

    // simple animation display four color square using LCD_put_pixel function
    int limit = 200;
    for ( int ofs = 0; ofs < 20; ofs++ ) // square offset in x and y axis
        for ( int i = 0; i < limit; i++ )
        {
            LCD_put_pixel( ofs + i,     ofs + 0,     color_red );
            LCD_put_pixel( ofs + 0,     ofs + i,     color_green );
            LCD_put_pixel( ofs + i,     ofs + limit, color_blue );
            LCD_put_pixel( ofs + limit, ofs + i,     color_white );
        }
*/
/*
Circle *c = new Circle(100,60,50,0xFF0000,0x0000FF);
c->Display(c->x, c->y);

Symbol *s = new Symbol(60,60,0x0000FF,0xFFFFFF,'X');
s->Display(s->x,s->y);

Line *l1=new Line(100,100,120,60,0x00FF00,0x0000FF);
l1->Display(l1->x, l1->y,l1->xk,l1->yk);

Line *l2=new Line(100,100,120,170,0x00FF00,0x0000FF);
l2->Display(l2->x, l2->y,l2->xk,l2->yk);

Line *l3=new Line(100,100,50,160,0x00FF00,0x0000FF);
l3->Display(l3->x, l3->y,l3->xk,l3->yk);

Line *l4=new Line(100,100,30,60,0x00FF00,0x0000FF);
l4->Display(l4->x, l4->y,l4->xk,l4->yk);

Rectangle *r = new Rectangle(100,100,200,100,0x123456,0xABCDEF);
r->Display();
*/
    Clock* cl1 = new Clock(50,60,50,0x00FF00,0xFF0000,60);
    cl1->Display(cl1->x,cl1->y);
    Clock* cl2 = new Clock(150,60,50,0x00FF00,0xFF0000,60);
    cl2->Display(cl2->x,cl2->y);
    Clock* cl3 = new Clock(250,60,50,0x00FF00,0xFF0000,24);
    cl3->Display(cl3->x,cl3->y);


DigitalIn KIT_Button1( PTC9 );
	DigitalIn KIT_Button2( PTC10 );
	DigitalIn KIT_Button3( PTC11 );
	DigitalIn KIT_Button4( PTC12 );
while(true)
{
	if(!KIT_Button1)
	{
		cl1->angle+=(90/(cl1->jump));

		if(cl1->angle>315)
		{
			cl2->angle+=(90/(cl2->jump));



		}
		if(cl2->angle>315)
		{
				cl3->angle+=(90/(cl3->jump));



		}
		cl1->Display(cl1->x,cl1->y);
		cl2->Display(cl2->x,cl2->y);
		cl3->Display(cl3->x,cl3->y);

	}

}








    return 0;
}

// **************************************************************************
//
//               Demo program for labs
//
// Subject:      Computer Architectures and Parallel systems
// Author:       Petr Olivka, petr.olivka@vsb.cz, 08/2016
// Organization: Department of Computer Science, FEECS,
//               VSB-Technical University of Ostrava, CZ
//
// File:         Main program for LEDs
//
// **************************************************************************

#include "mbed.h"

#define T 24
Ticker tick,tick2;
class LED : public DigitalOut
	{
	public:
		int T0;
		LED(PinName pin): DigitalOut(pin)
		{
			//..
		}

		void SetBrightness(int percentage)
		{
				T0 = T - (T*percentage)/100 ;

		}
		void Blink(int t)
		{
			//if(t==0)
			{
				//write(t<T0?1:0);
                if(t < T0)
                {
                    write(0);
                }
                else
                {
                    write(1);
                }
			}
		}




	};

	class PWM
	{
		public:
		LED* leds;
		int ledc;
		int t;
		int brights[8];

		PWM(LED* ledarray,int nleds)
		{
			leds = ledarray;
			ledc = nleds;
			t=0;
			//brights = new int[8];


			for(int i = 0;i<ledc;i++)
			{
				brights[i]=0;

			}

		}






		void Blink()
		{

			for(int i = 0;i<ledc;i++)
			{

					leds[i].SetBrightness(brights[i]);



				leds[i].Blink(t);



			}
			if(++t >= T)
			{
				t=0;

			}
		}

	};


int main()
{
	// LEDs on K64F-KIT - instances of class DigitalOut
	LED KIT_LED1( PTA1 );
	LED KIT_LED2( PTA2 );

	LED upLED1( PTC0 );
	LED upLED2( PTC1 );
	LED upLED3( PTC2 );
	LED upLED4( PTC3 );
	LED upLED5( PTC4 );
	LED upLED6( PTC5 );
	LED upLED7( PTC7 );
	LED upLED8( PTC8 );
	//LED KITLEDS[2] = {KIT_LED1,KIT_LED2};
	LED LEDS [8] ={upLED1,upLED2,upLED3,upLED4,upLED5,upLED6,upLED7,upLED8};
	// Button on K64F-KIT - instance of class DigitalIn
	DigitalIn KIT_Button1( PTC9 );
	DigitalIn KIT_Button2( PTC10 );
	DigitalIn KIT_Button3( PTC11 );
	DigitalIn KIT_Button4( PTC12 );
	LED RGB1 [] = {PTB2,PTB3,PTB9};
	LED RGB2 [] = {PTB11,PTB18,PTB19};
int orig = 0;

	//Other variables
PWM pwm(LEDS,8);
PWM pwm2(RGB2,3);
pwm2.brights[2]=orig;
tick.attach_us(callback(&pwm,&PWM::Blink),1000);
tick2.attach_us(callback(&pwm2,&PWM::Blink),1000);


	//short ledcount=0;




int index =0;

	int period = 24;
    while( 1 )
    {
    	/*int delay = 500;

    	KIT_LED1 = !KIT_LED1; 	// invert LED1 state

    	if ( KIT_Button1 == 0 ) 	// button pressed?
    	{
    		delay /= 10;		// speed up blinking
    		KIT_LED2 = !KIT_LED2;
    	}
    	else
    		KIT_LED2 = 0; 		// LED2 off

    	wait_ms( delay );
    	int delay = 500;
    	if ( KIT_Button1 == 0) 	// button pressed?
    	    {


    		for	(short i = 0;i <= ledcount;i++)
    		    {
    				LEDS[i]=1;
    			}



    		if(ledcount<8)
    		{
    			ledcount++;

    		}
    		else
    		{
    			ledcount = 1;
    			for	(short i = 1;i < 8;i++)
    			    {
    			    	LEDS[i]=0;
    			    }
    		}

    		wait_ms(delay);

    	   	}*/
//_________________________________________________________________________________________

     /*  KIT_LED1.write(!KIT_LED1.read());
       wait_ms(period/2);*/

//_________________________________________________________________________________________

    	/*while(!KIT_Button1)
    		{
    		pwm.light = false;
    		    	wait_ms(100);
    		}
    	while(!KIT_Button2)
    		{
    		pwm.light = true;
    		wait_ms(100);
    		}*/
//___________________________________________________________________



    	if(!KIT_Button1)
    	{
    		wait_ms(100);

    		for(int i =0;i<3;i++)
    		{
    			index = 0;
    			while(index < 8)
    			    {

    			    	while(pwm.brights[index]<100)
    			   		{
    		    			pwm.brights[index]+=10;
    			    		wait_ms(10);

    			   		}
    			    		index++;


    			    }




    			    wait_ms(100);
    			    while(--index>=0 )
    			    {

    			    	while(pwm.brights[index]>=0)
    			    	{
    			    		   pwm.brights[index]-=10;
    			    		   wait_ms(10);

    			    	}



    			    }
    		/*	    for(int i = 0;i<8;i++)
    			    {

    			    	pwm.brights[i]=0;
    			    }*/


    		}





    	}






    	if(!KIT_Button2)
    	    	{
    	    		wait_ms(100);

    	    		for(int i =0;i<3;i++)
    	    		{
    	    			index = 8;
    	    			while(--index>=0)
    	    			    {

    	    			    	while(pwm.brights[index]<100)
    	    			   		{
    	    		    			pwm.brights[index]+=10;
    	    			    		wait_ms(10);

    	    			   		}
    	    			    		index++;


    	    			    }




    	    			    wait_ms(100);
    	    			    while( index < 8)
    	    			    {

    	    			    	while(pwm.brights[index]>=0)
    	    			    	{
    	    			    		   pwm.brights[index]-=10;
    	    			    		   wait_ms(10);

    	    			    	}



    	    			    }
    	    		/*	    for(int i = 0;i<8;i++)
    	    			    {

    	    			    	pwm.brights[i]=0;
    	    			    }*/


    	    		}





    	    	}

    	while(!KIT_Button3)
    	{
    		wait_ms(100);
    		pwm2.brights[2]=100;

    	}
    	pwm2.brights[2]=orig;

    	if(!KIT_Button4)
    	{
    		wait_ms(50);
    		for(int i =0;i<3;i++)
    		    	{
    		    		RGB1[i].write(!(RGB1[i].read()));

    		    	}
    		orig = orig==0?20:0;

    	}

    }
}


short CountLeds(DigitalOut LEDS [])
{
	short count = 0;
for	(short i = 0;i <= 8;i++)
    {
		if(LEDS[i]==1) count++;
	}
return count;
}

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

// ***********************************************************************
//
// Demo program for education in subject
// Computer Architectures and Parallel Systems.
// Petr Olivka, dep. of Computer Science, FEI, VSB-TU Ostrava
// email:petr.olivka@vsb.cz
//
// Example of CUDA Technology Usage with unified memory.
//
// Image transformation from RGB to BW schema. 
// Image manipulation is performed by OpenCV library. 
//
// ***********************************************************************

#include <stdio.h>
#include <cuda_device_runtime_api.h>
#include <cuda_runtime.h>
#include "opencv2/opencv.hpp"
#include "pic_type.h"
#include "uni_mem_allocator.h"
#include "font12x20_lsb.h"
using namespace cv;

// Function prototype from .cu file
void cu_run_grayscale( CUDA_Pic bgr_pic, CUDA_Pic bw_pic );
void cu_run_rotate(CUDA_Pic original,CUDA_Pic rotated,int rotationnum);
void cu_run_shrink(CUDA_Pic orig,CUDA_Pic shrunk,int widthheight);
void cu_insertimage( CUDA_Pic bigPic, CUDA_Pic smallPic, int2 position );
void DisplayFont(Mat& font);
void Display(int x0,int y0,int sym,Mat& text,unsigned char op);
void cu_run_rotaround(CUDA_Pic bkg,CUDA_Pic ins,float deg,int2 pos);

//uint16_t font12x20 [ 256 ][ 20 ];
int main( int numarg, char **arg )
{
	int shrunkby = 3;
	// Uniform Memory allocator for Mat
	UniformAllocator allocator;
	cv::Mat::setDefaultAllocator( &allocator );

	if ( numarg < 2 ) 
	{
		printf( "Enter picture filename!\n" );
		return 1;
	}

	// Load image
	Mat cv_bgr = imread( arg[ 1 ], CV_LOAD_IMAGE_COLOR );
    
	if ( !cv_bgr.data )
	{
		printf( "Unable to read file '%s'\n", arg[ 1 ] );
		return 1;
	}

    const   char* t = "text";
	// create empty BW image
	Mat cv_bw( cv_bgr.size(), CV_8UC3 );
	Mat cv_rot(cv_bgr.cols,cv_bgr.rows,CV_8UC3 );
    //Mat cv_font(40,256*24,CV_8UC4);
    Mat cv_text(40,strlen(t)*24,CV_8UC4);
      printf( "Delka %d \n",(int)(strlen(t)) );
		
	int shrunkcols = cv_bgr.cols;
	int shrunkrows=cv_bgr.rows;
	switch(shrunkby)
	{

			case 1:
			{
				shrunkcols/=2;
				break;
			}
			case 2:
			{
				shrunkrows/=2;
				break;
			}
			case 3:
			{
				shrunkcols/=2;
				shrunkrows/=2;
				break;
			}
			default:break;

	}


	Mat cv_shrunk(shrunkrows,shrunkcols,CV_8UC3 );
	//printf("Original: %d %d\n",cv_bgr.cols,cv_bgr.rows);
	//printf("Shrunk: %d %d\n",cv_shrunk.cols,cv_shrunk.rows);
    printf("Text Channel: %d\n",cv_text.channels());
    

	// data for CUDA
	CUDA_Pic pic_bgr, pic_bw,pic_rot,pic_shr,pic_text;
	/*pic_bgr.Size.x = pic_bw.Size.x = cv_bgr.size().width;
	pic_bgr.Size.y = pic_bw.Size.y = cv_bgr.size().height;
	pic_bgr.P_uchar3 = ( uchar3 * ) cv_bgr.data;
	pic_bw.P_uchar3 = ( uchar3 * ) cv_bw.data;
	*/
	pic_bgr.setMat(cv_bgr);
	pic_bw.setMat(cv_bw);
	pic_rot.setMat(cv_rot);
	pic_shr.setMat(cv_shrunk);
    pic_text.setMat(cv_text);
	// Function calling from .cu file
	cu_run_grayscale( pic_bgr, pic_bw );
	cu_run_rotate(pic_bgr,pic_rot,3);
	cu_run_shrink(pic_bgr,pic_shr,shrunkby);
   //DisplayFont(cv_font);
    
    for(int i =0;i<strlen(t);i++)
    {
        Display(i*24,0,t[i],cv_text,255);

    }
    int textx = 200,texty=100;
    printf("BGR size: %d %d \t TEXT LT: %d %d RB: %d %d \n",cv_bgr.cols,cv_bgr.rows,textx,texty,textx+cv_text.cols,texty+cv_text.rows);
    if ( cv_text.channels() != 4 )
			{printf( "Text does not contain alpha channel!\n" );}
    else
    {
        cu_insertimage( pic_bgr, pic_text, { textx, texty } );
        
    }

	// Show the Color and BW image
	imshow( "Color", cv_bgr );
	imshow( "GrayScale", cv_bw );
	imshow( "Rotated", cv_rot );
	imshow( "Shrunk", cv_shrunk );
    //imshow( "Font" ,cv_font);
    imshow( "Text" ,cv_text);



  CUDA_Pic pic_bckg;   
    Mat cv_bgrd= imread( arg[ 1 ], CV_LOAD_IMAGE_COLOR );
    Mat cv_res;
    
    for(int i = 0;255-i*10>0;i++)
    {
    waitKey(100);
   
     for(int a =0;a<strlen(t);a++)
    {
        Display(a*24,0,t[a],cv_text,255-i*10);

    }
    pic_text.setMat(cv_text);

    cv_res = cv_bgrd.clone();
    pic_bckg.setMat(cv_res);
    cu_run_rotaround(pic_text,pic_bckg,i*10,{100,230});
  
    imshow("Rotation",cv_res);
    
    }
    imshow("test",cv_bgrd);
	waitKey( 0 );
}

void DisplayFont(Mat& font)
    {
        uchar4 fore,back ;
        back = {0,0,0,0};
        fore = {25,25,55,255};
        int y0=0;
        int x0=0;
    for(int sym = 0;sym <256;sym++)
    {
        
        for(int j = 0;j<20;j++)
        {
            for(int i = 0;i<12;i++)
            {
                if(font12x20[sym][j] & (1<<i))
                {
                   font.at<uchar4>( y0+2*j,x0+2*i)=fore;
                    font.at<uchar4>(y0+ 2*j,x0+2*i+1 )=fore;
                    font.at<uchar4>(y0+2*j+1,x0+2*i  )=fore;
                    font.at<uchar4>( y0+2*j+1,x0+2*i+1 )=fore;
                }

                else
                    {
                   
                  font.at<uchar4>( y0+2*j,x0+2*i)=back;
                    font.at<uchar4>(y0+ 2*j,x0+2*i+1 )=back;
                    font.at<uchar4>(y0+2*j+1,x0+2*i  )=back;
                    font.at<uchar4>( y0+2*j+1,x0+2*i+1 )=back;

                    }


            }



        }
        x0+=24;

    }

      

    }



void Display(int x0,int y0,int sym,Mat& font,unsigned char op)
    {
      uchar4 fore,back ;
        back = {0,0,200,0};
        fore = {0,255,0,op};
     
        for(int j = 0;j<20;j++)
        {
            for(int i = 0;i<12;i++)
            {
                if(font12x20[sym][j] & (1<<i))
                {
                   font.at<uchar4>( y0+2*j,x0+2*i)=fore;
                    font.at<uchar4>(y0+ 2*j,x0+2*i+1 )=fore;
                    font.at<uchar4>(y0+2*j+1,x0+2*i  )=fore;
                    font.at<uchar4>( y0+2*j+1,x0+2*i+1 )=fore;
                }

                else
                    {
                   
                  font.at<uchar4>( y0+2*j,x0+2*i)=back;
                    font.at<uchar4>(y0+ 2*j,x0+2*i+1 )=back;
                    font.at<uchar4>(y0+2*j+1,x0+2*i  )=back;
                    font.at<uchar4>( y0+2*j+1,x0+2*i+1 )=back;

                    }


            }



        }
     

    

      

    }


// ***********************************************************************
//
// Demo program for education in subject
// Computer Architectures and Parallel Systems.
// Petr Olivka, dep. of Computer Science, FEI, VSB-TU Ostrava
// email:petr.olivka@vsb.cz
//
// Example of CUDA Technology Usage.
//
// Image interface for CUDA
//
// ***********************************************************************

#pragma once
#include "opencv2/opencv.hpp"
// Structure definition for exchanging data between Host and Device
struct CUDA_Pic
{
  uint3 Size;			// size of picture
  union {
	  void   *P_void;		// data of picture
	  uchar1 *P_uchar1;		// data of picture
	  uchar3 *P_uchar3;		// data of picture
	  uchar4 *P_uchar4;		// data of picture
  };

  __host__ __device__ uchar1& at1(int y,int x)
    {

  	  return P_uchar1[y * Size.x + x] ;
    }
  __host__ __device__ uchar3& at3(int y,int x)
    {

  	  return P_uchar3[y * Size.x + x] ;
    }
  __host__ __device__ uchar4& at4(int y,int x)
    {

  	  return P_uchar4[y * Size.x + x ];
    }

  __host__  void setMat(cv::Mat& m)
  {
	  Size.x = m.size().width;
	  Size.y = m.size().height;
        switch(m.channels())
        {
            case 1:
                {
                P_uchar1 = (uchar1*) m.data;
                break;
                }
            case 3:
                {
                P_uchar3 = (uchar3*) m.data;
                break;
                }
            case 4:
                {
                P_uchar4 = (uchar4*) m.data;
                break;
                }

        }
      
  }


};

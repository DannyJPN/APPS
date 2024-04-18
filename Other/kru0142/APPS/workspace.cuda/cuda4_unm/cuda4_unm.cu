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
//
// ***********************************************************************

#include <stdio.h>
#include <cuda_device_runtime_api.h>
#include <cuda_runtime.h>
#include "pic_type.h"
#include "animation.h"

// Demo kernel to transform RGB color schema to BW schema
__global__ void kernel_grayscale( CUDA_Pic colorPic, CUDA_Pic bwPic )
{
	// X,Y coordinates and check image dimensions
	int y = blockDim.y * blockIdx.y + threadIdx.y;
	int x = blockDim.x * blockIdx.x + threadIdx.x;
	if ( y >= colorPic.Size.y ) return;
	if ( x >= colorPic.Size.x ) return;

	// Get point from color picture
	//uchar3 bgr = colorPic.P_uchar3[ y * colorPic.Size.x + x ];
	uchar3 bgr = colorPic.at3(y,x);

	// Store BW point to new image
	//bwPic.P_uchar1[ y * bwPic.Size.x + x ].x = bgr.x * 0.11 + bgr.y * 0.59 + bgr.z * 0.30;
if( y <= x*colorPic.Size.y/colorPic.Size.x)
{
	bwPic.at3(y,x).x = bgr.x;
	bwPic.at3(y,x).y = bgr.y;
	bwPic.at3(y,x).z = bgr.z;

}
else
{
	bwPic.at3(y,x).x = 	bwPic.at3(y,x).y = 	bwPic.at3(y,x).z = bgr.x * 0.11 + bgr.y * 0.59 + bgr.z * 0.30;


}






	//bwPic.at1(y,x).x = bgr.x * 0.11 + bgr.y * 0.59 + bgr.z * 0.30;




}








__global__ void kernel_rotate( CUDA_Pic original, CUDA_Pic rotated,int rotnum)
{
	// X,Y coordinates and check image dimensions
	int y = blockDim.y * blockIdx.y + threadIdx.y;
	int x = blockDim.x * blockIdx.x + threadIdx.x;
	if ( y >= original.Size.y ) return;
	if ( x >= original.Size.x ) return;
	if ( y >= rotated.Size.x ) return;
	if ( x >= rotated.Size.y ) return;

	// Get point from color picture
	//uchar3 bgr = colorPic.P_uchar3[ y * colorPic.Size.x + x ];
	uchar3 bgr = original.at3(y,x);

	// Store BW point to new image
	//bwPic.P_uchar1[ y * bwPic.Size.x + x ].x = bgr.x * 0.11 + bgr.y * 0.59 + bgr.z * 0.30;

	if(rotnum ==1 )
	{
		rotated.at3(original.Size.x - x,y).x = bgr.x;
		rotated.at3(original.Size.x - x,y).y = bgr.y;
		rotated.at3(original.Size.x - x,y).z = bgr.z;

	}
	else if(rotnum ==3)
	{
		rotated.at3(x,original.Size.y-y).x = bgr.x;
		rotated.at3(x,original.Size.y-y).y = bgr.y;
		rotated.at3(x,original.Size.y-y).z = bgr.z;

	}










	//bwPic.at1(y,x).x = bgr.x * 0.11 + bgr.y * 0.59 + bgr.z * 0.30;




}

__global__ void kernel_shrink( CUDA_Pic original, CUDA_Pic shrunk,int widthheight)
{
	// X,Y coordinates and check image dimensions
	int y = blockDim.y * blockIdx.y + threadIdx.y;
	int x = blockDim.x * blockIdx.x + threadIdx.x;
	if ( y >= original.Size.y ) return;
	if ( x >= original.Size.x ) return;

	// Get point from color picture
	//uchar3 bgr = colorPic.P_uchar3[ y * colorPic.Size.x + x ];


	// Store BW point to new image
	//bwPic.P_uchar1[ y * bwPic.Size.x + x ].x = bgr.x * 0.11 + bgr.y * 0.59 + bgr.z * 0.30;

	//printf("WIDTHHEIGHT = %d\n",widthheight);
	//printf("Taking TOP x:%d,y:%d into X:%d,Y%d\n",x,y*2-1,x,y);
	//printf("Taking BOT x:%d,y:%d into X:%d,Y%d\n",x,y*2,x,y);


	if(widthheight ==1 )
	{
		uchar3 bgrl = original.at3(y,x*2);
		uchar3 bgrr = original.at3(y,x*2+1);

		shrunk.at3(y,x).x = (bgrl.x+bgrr.x)/2;
		shrunk.at3(y,x).y = (bgrl.y+bgrr.y)/2;
		shrunk.at3(y,x).z = (bgrl.z+bgrr.z)/2;

	}
	else if(widthheight ==2 )
	{
		uchar3 bgrt = original.at3(y*2,x);
		uchar3 bgrb = original.at3(y*2+1,x);

		shrunk.at3(y,x).x = (bgrt.x+bgrb.x)/2;
		shrunk.at3(y,x).y = (bgrt.y+bgrb.y)/2;
		shrunk.at3(y,x).z = (bgrt.z+bgrb.z)/2;

	}
	else if(widthheight ==3)
		{
			uchar3 bgrtl = original.at3(y*2,x*2);
			uchar3 bgrbr = original.at3(y*2+1,x*2+1);
			uchar3 bgrbl = original.at3(y*2+1,x*2);
			uchar3 bgrtr = original.at3(y*2,x*2+1);

			shrunk.at3(y,x).x = bgrtl.x;//(bgrtl.x+bgrbl.x +bgrtr.x+bgrbr.x)/4;
			shrunk.at3(y,x).y = bgrtl.y;//(bgrtl.y+bgrbl.y+bgrtr.y+bgrbr.y)/4;
			shrunk.at3(y,x).z = bgrtl.z;//(bgrtl.z+bgrbl.z+bgrtr.z+bgrbr.z)/4;

		}









	//bwPic.at1(y,x).x = bgr.x * 0.11 + bgr.y * 0.59 + bgr.z * 0.30;




}






void cu_run_grayscale( CUDA_Pic colorPic, CUDA_Pic bwPic )
{
	cudaError_t cerr;

	// Grid creation, size of grid must be equal or greater than images
	int block_size = 16;
	dim3 blocks( ( colorPic.Size.x + block_size - 1 ) / block_size, ( colorPic.Size.y + block_size - 1 ) / block_size );
	dim3 threads( block_size, block_size );
	kernel_grayscale<<< blocks, threads >>>( colorPic, bwPic );

	if ( ( cerr = cudaGetLastError() ) != cudaSuccess )
		printf( "CUDA Error [%d] - '%s'\n", __LINE__, cudaGetErrorString( cerr ) );

	cudaDeviceSynchronize();
}
void cu_run_rotate( CUDA_Pic original, CUDA_Pic rotated,int rotnum)
{
	cudaError_t cerr;

	// Grid creation, size of grid must be equal or greater than images
	int block_size = 16;
	dim3 blocks( ( original.Size.x + block_size - 1 ) / block_size, ( original.Size.y + block_size - 1 ) / block_size );
	dim3 threads( block_size, block_size );

		kernel_rotate<<< blocks, threads >>>( original, rotated ,rotnum);




	if ( ( cerr = cudaGetLastError() ) != cudaSuccess )
		printf( "CUDA Error [%d] - '%s'\n", __LINE__, cudaGetErrorString( cerr ) );

	cudaDeviceSynchronize();
}
void cu_run_shrink( CUDA_Pic original, CUDA_Pic shrunk,int widthheight)
{
	cudaError_t cerr;

	// Grid creation, size of grid must be equal or greater than images
	int block_size = 16;
	dim3 blocks( ( shrunk.Size.x + block_size - 1 ) / block_size, ( shrunk.Size.y + block_size - 1 ) / block_size );
	dim3 threads( block_size, block_size );

		kernel_shrink<<< blocks, threads >>>( original, shrunk ,widthheight);




	if ( ( cerr = cudaGetLastError() ) != cudaSuccess )
		printf( "CUDA Error [%d] - '%s'\n", __LINE__, cudaGetErrorString( cerr ) );

	cudaDeviceSynchronize();
}






__global__  void kernel_insertimage( CUDA_Pic bigPic, CUDA_Pic smallPic, int2 position )
{
    
	// X,Y coordinates and check image dimensions
	int y = blockDim.y * blockIdx.y + threadIdx.y;
	int x = blockDim.x * blockIdx.x + threadIdx.x;
	if ( y >= smallPic.Size.y ) { return;}
	if ( x >= smallPic.Size.x ) { return;}
	int by = y + position.y;
	int bx = x + position.x;
	if ( by >= bigPic.Size.y || by < 0 ) { return;}
	if ( bx >= bigPic.Size.x || bx < 0 ) { return;}

	// Get point from small image
	uchar4 fg_bgra = smallPic.P_uchar4[ y * smallPic.Size.x + x ];
   // printf("Uchar4 x = %d,y = %d,z = %d,w = %d",fg_bgra.x,fg_bgra.y,fg_bgra.z,fg_bgra.w);	
    uchar3 bg_bgr = bigPic.P_uchar3[ by * bigPic.Size.x + bx ];
   // printf("Uchar3 x = %d,y = %d,z = %d",bg_bgr.x,bg_bgr.y,bg_bgr.z);
	uchar3 bgr = { 0, 0, 0 };

	// compose point from small and big image according alpha channel
	bgr.x = fg_bgra.x * fg_bgra.w / 255 + bg_bgr.x * ( 255 - fg_bgra.w ) / 255;
	bgr.y = fg_bgra.y * fg_bgra.w / 255 + bg_bgr.y * ( 255 - fg_bgra.w ) / 255;
	bgr.z = fg_bgra.z * fg_bgra.w / 255 + bg_bgr.z * ( 255 - fg_bgra.w ) / 255;

	// Store point into image
	bigPic.P_uchar3[ by * bigPic.Size.x + bx ] = bgr;
}

void cu_insertimage( CUDA_Pic bigPic, CUDA_Pic smallPic, int2 position )
{
	cudaError_t cerr;

	// Grid creation, size of grid must be equal or greater than images
	int block_size = 32;
	dim3 blocks( ( smallPic.Size.x + block_size - 1 ) / block_size, ( smallPic.Size.y + block_size - 1 ) / block_size );
	dim3 threads( block_size, block_size );
	kernel_insertimage<<< blocks, threads >>>( bigPic, smallPic, position );

	if ( ( cerr = cudaGetLastError() ) != cudaSuccess )
		printf( "CUDA Error [%d] - '%s'\n", __LINE__, cudaGetErrorString( cerr ) );

	cudaDeviceSynchronize();
}







__global__ void kernel_rotaround( CUDA_Pic colorPic, CUDA_Pic bwPic,  float degr, int2 position ) 
{ 
     // X,Y coordinates and check image dimensions
	int y = blockDim.y * blockIdx.y + threadIdx.y;
	int x = blockDim.x * blockIdx.x + threadIdx.x;
	if ( y >= colorPic.Size.y ) { return;}
	if ( x >= colorPic.Size.x ) { return;}



 float deg = degr*3.14/180; 
  
 
    int xc =colorPic.Size.x/2; 
    int yc =colorPic.Size.y/2; 
 
    int nx = ((float)x-xc)*cos(deg) - ((float)y-yc)*sin(deg) + xc*2+position.x; 
    int ny = ((float)x-xc)*sin(deg) + ((float)y-yc)*cos(deg) + yc*2+position.y; 

	// Get point from small image
	uchar4 fg_bgra = colorPic.at4(y,x);
   // printf("Uchar4 x = %d,y = %d,z = %d,w = %d",fg_bgra.x,fg_bgra.y,fg_bgra.z,fg_bgra.w);	
    uchar3 bg_bgr = bwPic.at3(ny,ny);
   // printf("Uchar3 x = %d,y = %d,z = %d",bg_bgr.x,bg_bgr.y,bg_bgr.z);
	uchar3 bgr = { 0, 0, 0 };

	// compose point from small and big image according alpha channel
    bgr.x = fg_bgra.x * fg_bgra.w / 255 + bg_bgr.x * ( 255 - fg_bgra.w ) / 255;
	bgr.y = fg_bgra.y * fg_bgra.w / 255 + bg_bgr.y * ( 255 - fg_bgra.w ) / 255;
	bgr.z = fg_bgra.z * fg_bgra.w / 255 + bg_bgr.z * ( 255 - fg_bgra.w ) / 255;
   
if (nx >= 0 && nx < bwPic.Size.x && ny >= 0 && ny < bwPic.Size.y) 
{
	
    bwPic.P_uchar3[ ny * bwPic.Size.x + nx ] = bgr;
}
	
} 


void cu_run_rotaround( CUDA_Pic colorPic, CUDA_Pic bwPic, float degr, int2 position ) 
{ 
    cudaError_t cerr; 
 
    int block_size = 16; 
    dim3 blocks( ( colorPic.Size.x + block_size - 1 ) / block_size, ( colorPic.Size.y + block_size - 1 ) / block_size ); 
    dim3 threads( block_size, block_size ); 
    kernel_rotaround<<< blocks, threads >>>( colorPic, bwPic, degr ,position); 
 
    if ( ( cerr = cudaGetLastError() ) != cudaSuccess ) 
        printf( "CUDA Error [%d] - '%s'\n", __LINE__, cudaGetErrorString( cerr ) ); 
 
    cudaDeviceSynchronize(); 
} 













// ********************************************************************* 
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
// ********************************************************************* 
 
#include <stdio.h> 
#include <cuda_device_runtime_api.h> 
#include <cuda_runtime.h> 
#include <math.h> 
#include "pic_type.h" 
 
// Demo kernel to transform RGB color schema to BW schema 
 
__global__ void kernel_zmenseni( CUDA_Pic colorPic, CUDA_Pic bwPic ) 
{ 
    // X,Y coordinates and check image dimensions 
    int y = blockDim.y * blockIdx.y + threadIdx.y; 
    int x = blockDim.x * blockIdx.x + threadIdx.x; 
    if ( y >= colorPic.Size.y ) return; 
    if ( x >= colorPic.Size.x ) return; 
 
 
    uchar3 bgr[4]; 
    bgr[0] = colorPic.P_uchar3[y * colorPic.Size.x + x]; 
    bgr[1] = colorPic.P_uchar3[y * colorPic.Size.x + x + 1]; 
    bgr[2] = colorPic.P_uchar3[(y + 1) * colorPic.Size.x + x]; 
    bgr[3] = colorPic.P_uchar3[(y + 1) * colorPic.Size.x + x + 1]; 
 
    uchar3 bgr_small; 
    bgr_small.x = (bgr[0].x + bgr[1].x + bgr[2].x + bgr[3].x) / 4; 
    bgr_small.y = (bgr[0].y + bgr[1].y + bgr[2].y + bgr[3].y) / 4; 
    bgr_small.z = (bgr[0].z + bgr[1].z + bgr[2].z + bgr[3].z) / 4; 
    bwPic.P_uchar3[(y/2) * bwPic.Size.x + (x/2)] = bgr_small; 
 
} 
 
 
 
 
__global__ void kernel_rotace( CUDA_Pic colorPic, CUDA_Pic bwPic,  float degr ) 
{ 
     int y = blockDim.y * blockIdx.y + threadIdx.y; 
    int x = blockDim.x * blockIdx.x + threadIdx.x; 
    if ( y >= colorPic.Size.y ) return; 
    if ( x >= colorPic.Size.x ) return; 
 
 
 
    uchar3 bgr = colorPic.P_uchar3[ y * colorPic.Size.x + x ]; 
    float deg = degr*3.14/180; 
    int i = blockIdx.x * blockDim.x + threadIdx.x; 
    int j = blockIdx.y * blockDim.y + threadIdx.y; 
 
    int xc = colorPic.Size.x - colorPic.Size.x/2; 
    int yc = colorPic.Size.y - colorPic.Size.y/2; 
 
    int newx = ((float)i-xc)*cos(deg) - ((float)j-yc)*sin(deg) + xc*2; 
    int newy = ((float)i-xc)*sin(deg) + ((float)j-yc)*cos(deg) + yc*2; 
    if (newx >= 0 && newx < bwPic.Size.x && newy >= 0 && newy < bwPic.Size.y) 
    { 
        bwPic.P_uchar3[newy*bwPic.Size.x+newx]=bgr; 
    } 
} 
 
 
__global__ void kernel_zvetseni1( CUDA_Pic colorPic, CUDA_Pic bwPic ) 
{ 
    int y = blockDim.y * blockIdx.y + threadIdx.y; 
    int x = blockDim.x * blockIdx.x + threadIdx.x; 
    if ( y >= colorPic.Size.y ) return; 
    if ( x >= colorPic.Size.x ) return; 
    if ( y < 0) return; 
    if ( x < 0 ) return; 
 
    int x1 = x, y1=y; 
 
    bwPic.P_uchar3[y * colorPic.Size.x + x] = colorPic.P_uchar3[y * colorPic.Size.x + x]; 
 
    //bwPic.P_uchar3[y * bwPic.Size.x + x] = colorPic.P_uchar3[y * colorPic.Size.x + x]; 
    /*bwPic.P_uchar3[(y1) * bwPic.Size.x + (x1+1)] = colorPic.P_uchar3[y * colorPic.Size.x + x]; 
    bwPic.P_uchar3[(y1+1) * bwPic.Size.x + (x1)] = colorPic.P_uchar3[y * colorPic.Size.x + x]; 
    bwPic.P_uchar3[(y1+1) * bwPic.Size.x + (x1+1)] = colorPic.P_uchar3[y * colorPic.Size.x + x];*/ 
 
 
} 
 
 
__global__ void kernel_zvetseni2( CUDA_Pic colorPic, CUDA_Pic bwPic ) 
{ 
    int y = blockDim.y * blockIdx.y + threadIdx.y; 
    int x = blockDim.x * blockIdx.x + threadIdx.x; 
    if ( y >= colorPic.Size.y ) return; 
    if ( x >= colorPic.Size.x ) return; 
 
 
    uchar3 bgr[4]; 
    bgr[0] = colorPic.P_uchar3[y * colorPic.Size.x + x]; 
    bgr[1] = colorPic.P_uchar3[y * colorPic.Size.x + x + 1]; 
    bgr[2] = colorPic.P_uchar3[(y + 1) * colorPic.Size.x + x]; 
    bgr[3] = colorPic.P_uchar3[(y + 1) * colorPic.Size.x + x + 1]; 
 
    uchar3 p1, p2, p3, p4; 
 
    p1.x = bgr[0].x; 
    p1.y = bgr[0].y; 
    p1.z = bgr[0].z; 
 
    p2.x = (bgr[0].x + bgr[1].x )/2; 
    p2.y = (bgr[0].y + bgr[1].y )/2; 
    p2.z = (bgr[0].z + bgr[1].z )/2; 
 
    p3.x = (bgr[0].x + bgr[2].x )/2; 
    p3.y = (bgr[0].y + bgr[2].y )/2; 
    p3.z = (bgr[0].z + bgr[2].z )/2; 
 
    p4.x = (bgr[0].x + bgr[3].x )/2; 
    p4.y = (bgr[0].y + bgr[3].y )/2; 
    p4.z = (bgr[0].z + bgr[3].z )/2; 
 
    int x1 = 2*x, y1=2*y; 
 
    bwPic.P_uchar3[(y1) * bwPic.Size.x + (x1)] = p1; 
    bwPic.P_uchar3[(y1) * bwPic.Size.x + (x1+1)] = p2; 
    bwPic.P_uchar3[(y1+1) * bwPic.Size.x + (x1)] = p3; 
    bwPic.P_uchar3[(y1+1) * bwPic.Size.x + (x1+1)] = p4; 
} 
 
__global__ void kernel_zacerneni( CUDA_Pic colorPic) 
{ 
    int y = blockDim.y * blockIdx.y + threadIdx.y; 
    int x = blockDim.x * blockIdx.x + threadIdx.x; 
    if ( y >= colorPic.Size.y ) return; 
    if ( x >= colorPic.Size.x ) return; 
 
    uchar3 bgr = colorPic.P_uchar3[ y * colorPic.Size.x + x ]; 
 
    bgr.x = 0; 
    bgr.y = 0; 
    bgr.z = 0; 
 
    colorPic.P_uchar3[ y * colorPic.Size.x + x ] = bgr; 
 
} 
 
 
void cu_run_zmenseni( CUDA_Pic colorPic, CUDA_Pic bwPic) 
{ 
    cudaError_t cerr; 
 
    int block_size = 16; 
    dim3 blocks( ( colorPic.Size.x + block_size - 1 ) / block_size, ( colorPic.Size.y + block_size - 1 ) / block_size ); 
    dim3 threads( block_size, block_size ); 
    kernel_zmenseni<<< blocks, threads >>>( colorPic, bwPic); 
 
    if ( ( cerr = cudaGetLastError() ) != cudaSuccess ) 
        printf( "CUDA Error [%d] - '%s'\n", __LINE__, cudaGetErrorString( cerr ) ); 
 
    cudaDeviceSynchronize(); 
} 
 
void cu_run_rotace( CUDA_Pic colorPic, CUDA_Pic bwPic, float degr ) 
{ 
    cudaError_t cerr; 
 
    int block_size = 16; 
    dim3 blocks( ( colorPic.Size.x + block_size - 1 ) / block_size, ( colorPic.Size.y + block_size - 1 ) / block_size ); 
    dim3 threads( block_size, block_size ); 
    kernel_rotace<<< blocks, threads >>>( colorPic, bwPic, degr ); 
 
    if ( ( cerr = cudaGetLastError() ) != cudaSuccess ) 
        printf( "CUDA Error [%d] - '%s'\n", __LINE__, cudaGetErrorString( cerr ) ); 
 
    cudaDeviceSynchronize(); 
} 
 
void cu_run_zvetseni1( CUDA_Pic colorPic, CUDA_Pic bwPic ) 
{ 
    cudaError_t cerr; 
 
    int block_size = 16; 
    dim3 blocks( ( colorPic.Size.x + block_size - 1 ) / block_size, ( colorPic.Size.y + block_size - 1 ) / block_size ); 
    dim3 threads( block_size, block_size ); 
    kernel_zvetseni1<<< blocks, threads >>>( colorPic, bwPic ); 
 
    if ( ( cerr = cudaGetLastError() ) != cudaSuccess ) 
        printf( "CUDA Error [%d] - '%s'\n", __LINE__, cudaGetErrorString( cerr ) ); 
 
    cudaDeviceSynchronize(); 
} 
 
void cu_run_zacerneni( CUDA_Pic colorPic) 
{ 
    cudaError_t cerr; 
 
    int block_size = 16; 
    dim3 blocks( ( colorPic.Size.x + block_size - 1 ) / block_size, ( colorPic.Size.y + block_size - 1 ) / block_size ); 
    dim3 threads( block_size, block_size ); 
    kernel_zacerneni<<< blocks, threads >>>( colorPic ); 
 
    if ( ( cerr = cudaGetLastError() ) != cudaSuccess ) 
        printf( "CUDA Error [%d] - '%s'\n", __LINE__, cudaGetErrorString( cerr ) ); 
 
    cudaDeviceSynchronize(); 
} 
 
 
void cu_run_zvetseni2( CUDA_Pic colorPic, CUDA_Pic bwPic1 ) 
{ 
    cudaError_t cerr; 
 
    int block_size = 16; 
    dim3 blocks( ( colorPic.Size.x + block_size - 1 ) / block_size, ( colorPic.Size.y + block_size - 1 ) / block_size ); 
    dim3 threads( block_size, block_size ); 
    kernel_zvetseni2<<< blocks, threads >>>( colorPic, bwPic1 ); 
 
    if ( ( cerr = cudaGetLastError() ) != cudaSuccess ) 
        printf( "CUDA Error [%d] - '%s'\n", __LINE__, cudaGetErrorString( cerr ) ); 
 
    cudaDeviceSynchronize(); 
}

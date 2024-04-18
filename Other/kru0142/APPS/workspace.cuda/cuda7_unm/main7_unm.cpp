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
// Image manipulation is performed by OpenCV library.  
// 
// ********************************************************************* 
 
#include <stdio.h> 
#include <cuda_device_runtime_api.h> 
#include <cuda_runtime.h> 
#include "opencv2/opencv.hpp" 
#include "pic_type.h" 
#include "uni_mem_allocator.h" 
 
using namespace cv; 
 
// Function prototype from .cu file 
void cu_run_rotace( CUDA_Pic bgr_pic, CUDA_Pic bw_pic, float degr ); 
void cu_run_zvetseni1( CUDA_Pic bgr_pic, CUDA_Pic bw_pic ); 
void cu_run_zvetseni2( CUDA_Pic bgr_pic, CUDA_Pic bw_pic2 ); 
void cu_run_zacerneni( CUDA_Pic colorPic); 
void cu_run_zmenseni( CUDA_Pic colorPic, CUDA_Pic bwPic); 
 
int main( int numarg, char **arg ) 
{ 
    UniformAllocator allocator; 
    cv::Mat::setDefaultAllocator( &allocator ); 
 
    if ( numarg < 2 )  
    { 
        printf( "Enter picture filename!\n" ); 
        return 1; 
    } 
 
    Mat cv_bgr = imread( arg[ 1 ], CV_LOAD_IMAGE_COLOR ); 
 
    if ( !cv_bgr.data ) 
    { 
        printf( "Unable to read file '%s'\n", arg[ 1 ] ); 
        return 1; 
    } 
 
    Mat cv_bw( cv_bgr.size()*2, CV_8UC3 ); 
 
    CUDA_Pic pic_bgr, pic_bw, pic_bw1, pic_bw2; 
    pic_bgr.Size.x = cv_bgr.size().width; 
    pic_bgr.Size.y = cv_bgr.size().height; 
 
    pic_bw.Size.x = cv_bw.size().width; 
    pic_bw.Size.y = cv_bw.size().height; 
 
 
    pic_bgr.P_uchar3 = ( uchar3 * ) cv_bgr.data; 
    pic_bw.P_uchar3 = ( uchar3 * ) cv_bw.data; 
 
 
    int x = 0; 
    float degr = 0; 
    int j = 0; 
    bool zmenseni = true; 
 
 
    //cu_run_zvetseni1(pic_bgr, pic_bw); 
 
    while(x == 0){ 
 
        waitKey( 1 ); 
        cu_run_zacerneni(pic_bw); 
        cu_run_rotace( pic_bgr, pic_bw, degr); 
 
        if(j == 3){ 
            j = 0; 
            zmenseni = !zmenseni; 
        } 
 
 
        if(zmenseni){ 
            waitKey( 200); 
            cu_run_zmenseni(pic_bw, pic_bgr); 
 
        } 
        else{ 
            waitKey( 200); 
            cu_run_zvetseni1(pic_bw, pic_bgr); 
        } 
        j++; 
 
 
        degr+=5; 
 
        if(degr == 720*4){ 
            x = 5; 
        } 
        imshow( "rotace", cv_bw ); 
 
 
    } 
 
 
 
 
 
    //cu_run_zvetseni1( pic_bgr, pic_bw1 ); 
    //cu_run_zvetseni2( pic_bgr, pic_bw2 ); 
 
 
    //imshow( "original", cv_bgr ); 
 
    //imshow( "zvetseni1", cv_bw1 ); 
    //imshow( "zvetseni2", cv_bw2 ); 
    waitKey( 0 ); 
} 

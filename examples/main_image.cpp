//
// Created by demo02 on 18-3-14.
//

#include "include/ImgLoader.h"

#include <opencv2/core.hpp>
#include <opencv/highgui.h>

#define FNAME   "../debug/image_consistency_check/dog.jpg"

int main(){
    ImgLoader img_loader;
    img_loader.SetImageSize(448, 448, 3);
    img_loader.Imread(FNAME);

    long cnt = 0;

    unsigned char *** img_org;
    img_org = (unsigned char ***) malloc(sizeof(unsigned char **) * img_loader.size_h_);
    for (int i=0; i<img_loader.size_h_; i++){
        img_org[i] = (unsigned char **) malloc(sizeof(unsigned char *) * img_loader.size_w_);
        for (int j=0; j<img_loader.size_w_; j++)
            img_org[i][j] = (unsigned char *) malloc(sizeof(unsigned char) * img_loader.num_channels_);
    }
    // Read and Create RGB Matrix
    for (int i=0; i<img_loader.size_h_; i++)
        for (int j=0; j<img_loader.size_w_; j++)
            for (int k=0; k<img_loader.num_channels_; k++)
                img_org[i][j][k] = (unsigned char) int(img_loader.data_[cnt++] * 255);

    // RGB2BGR


    for (int i=0; i<img_loader.size_h_; i++)
        for (int j=0; j<img_loader.size_w_; j++) {
            unsigned char tmp = img_org[i][j][0];
            img_org[i][j][0] = img_org[i][j][2];
            img_org[i][j][2] = tmp;
        }

    cnt = 0;

    char *img_array_org;
    img_array_org = (char *) malloc(sizeof(char) * img_loader.size_h_ * img_loader.size_w_ * img_loader.num_channels_);
    for (int i=0; i<img_loader.size_h_; i++)
        for (int j=0; j<img_loader.size_w_; j++)
            for (int k=0; k<img_loader.num_channels_; k++)
                img_array_org[cnt++] = img_org[i][j][k];

    IplImage *img_cv_org = cvCreateImage(cvSize(img_loader.size_w_, img_loader.size_h_), IPL_DEPTH_8U, 3);
    img_cv_org -> imageData = (char *) img_array_org;

    cvShowImage("Original", img_cv_org);

    //Resize
    int new_size[3] = {480, 640, 3};
    img_loader.Imresize(new_size);
    img_loader.Draw_rectangle(100, 160, 230, 250, IMG_U8_RED);
    unsigned char *** img;
    img = (unsigned char ***) malloc(sizeof(unsigned char **) * img_loader.size_h_);
    for (int i=0; i<img_loader.size_h_; i++){
        img[i] = (unsigned char **) malloc(sizeof(unsigned char *) * img_loader.size_w_);
        for (int j=0; j<img_loader.size_w_; j++)
            img[i][j] = (unsigned char *) malloc(sizeof(unsigned char) * img_loader.num_channels_);
    }


    cnt = 0;
    // Read and Create BGR Matrix
    for (int i=0; i<img_loader.size_h_; i++)
        for (int j=0; j<img_loader.size_w_; j++)
            for (int k=0; k<img_loader.num_channels_; k++)
                img[i][j][k] = (unsigned char) int(img_loader.data_[cnt++] * 255);

    // RGB2BGR
    for (int i=0; i<img_loader.size_h_; i++)
        for (int j=0; j<img_loader.size_w_; j++) {
            unsigned char tmp = img[i][j][2];
            img[i][j][2] = img[i][j][0];
            img[i][j][0] = tmp;
        }

    char *img_array;
    img_array = (char *) malloc(sizeof(char) * img_loader.size_h_ * img_loader.size_w_ * img_loader.num_channels_);
    cnt = 0;
    for (int i=0; i<img_loader.size_h_; i++)
        for (int j=0; j<img_loader.size_w_; j++)
            for (int k=0; k<img_loader.num_channels_; k++)
                img_array[cnt++] = img[i][j][k];

    IplImage *img_cv = cvCreateImage(cvSize(img_loader.size_w_, img_loader.size_h_), IPL_DEPTH_8U, 3);
    img_cv -> imageData = (char *) img_array;

    cvShowImage("Resized", img_cv);
    cvWaitKey(0);
    cvReleaseImage(&img_cv_org);
    cvReleaseImage(&img_cv);

    return 0;

}
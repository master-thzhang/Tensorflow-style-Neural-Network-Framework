//
// Created by demo02 on 18-3-14.
//

#include "include/ImgLoader.h"

#include <opencv2/core.hpp>
#include <opencv/highgui.h>
#include <iostream>

#define FNAME   "../debug/image_consistency_check/dog.jpg"

#define MAXBOX  1000



double GetIOU(double *bbox_gt, double *bbox_predicted) {
    int bbox_gt_int[4];
    int bbox_predicted_int[4];
    bbox_gt_int[0] = int(bbox_gt[0]);
    bbox_predicted_int[0] = int(bbox_predicted[0]);
    bbox_gt_int[1] = int(bbox_gt[1]);
    bbox_predicted_int[1] = int(bbox_predicted[1]);
    bbox_gt_int[2] = int(bbox_gt[2]);
    bbox_predicted_int[2] = int(bbox_predicted[2]);
    bbox_gt_int[3] = int(bbox_gt[3]);
    bbox_predicted_int[3] = int(bbox_predicted[3]);
    int x1 = std::max(bbox_gt_int[0], bbox_predicted_int[0]);
    int y1 = std::max(bbox_gt_int[1], bbox_predicted_int[1]);
    int x2 = std::min(bbox_gt_int[2], bbox_predicted_int[2]);
    int y2 = std::min(bbox_gt_int[3], bbox_predicted_int[3]);
    std::cout << "bbox gt:" << bbox_gt_int[0] << "\t" << bbox_gt_int[1] << "\t" << bbox_gt_int[2] << "\t" << bbox_gt_int[3] << std::endl;
    std::cout << "bbox predicted:" << bbox_predicted_int[0] << "\t" << bbox_predicted_int[1] << "\t" << bbox_predicted_int[2] << "\t" << bbox_predicted_int[3] << std::endl;
    if ((x1 > x2) || (y1 > y2))
        return 0.0;
    int w = abs(x2 - x1) + 1;
    int h = abs(y2 - y1) + 1;
    int inter = w * h;
    int aarea = (abs(bbox_gt_int[2] - bbox_gt_int[0]) + 1) * (abs(bbox_gt_int[3] - bbox_gt_int[1]) + 1);
    int barea = (abs(bbox_predicted_int[2] - bbox_predicted_int[0]) + 1) * (abs(bbox_predicted_int[3] - bbox_predicted_int[1]) + 1);
    return (double) (inter + 0.0) / (aarea + barea - inter + 0.0);
}

void DoNMS(int num, double **array, double thresh, double **dst, int dst_size, int size_h, int size_w){
    // Array is stored in [7x7x2, 5] format.
    if (num>MAXBOX)
        std::cerr << "Too many proposals! Stopping..." << std::endl;

    for (int i=0; i<num-1; i++)
        for (int j=i+1; j<num; j++)
            if (array[i][4]<array[j][4]){
                double tmp = array[i][4];
                array[i][4] = array[j][4];
                array[j][4] = tmp;
            }

    bool *vi;
    vi = (bool *) malloc(sizeof(bool) * num);

    for (int i=0; i<MAXBOX; i++)
        vi[i] = true;

    for (int i=0; i<num-1; i++)
        for (int j=i+1; j<num; j++){
            if (vi[j]){
                double bbox1[4];
                double bbox2[4];
                bbox1[0] = int(array[i][0]);
                bbox1[1] = int(array[i][1]);
                bbox1[2] = int(array[i][2]);
                bbox1[3] = int(array[i][3]);
                bbox2[0] = int(array[j][0]);
                bbox2[1] = int(array[j][1]);
                bbox2[2] = int(array[j][2]);
                bbox2[3] = int(array[j][3]);
                double result = GetIOU(bbox1, bbox2);
                if (result > thresh){
                    vi[j] = false;
                }
            }
        }
    int cnt = 0;
    for (int i=0; i<num; i++){
        if (vi[i]){
            for (int j=0; j<5; j++){
                dst[cnt][j] = array[i][j];
            }
            cnt ++;
            if (cnt == dst_size)
                return;
        }
    }
}




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
    img_loader.Add_label_from_collection(400, 500, 3, 'c', IMG_U8_WHITE, IMG_U8_RED);
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
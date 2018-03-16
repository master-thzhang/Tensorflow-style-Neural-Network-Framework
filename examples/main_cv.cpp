//
// Created by demo02 on 18-3-9.
//

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include <vector>

#define FNAME   "../debug/image_consistency_check/dog.jpg"

int main(){
#define FP1_W   "../debug/image_consistency_check/OpenCV/channel1.txt"
#define FP2_W   "../debug/image_consistency_check/OpenCV/channel2.txt"
#define FP3_W   "../debug/image_consistency_check/OpenCV/channel3.txt"

    FILE *fp1;
    fp1 = fopen(FP1_W, "w");
    FILE *fp2;
    fp2 = fopen(FP2_W, "w");
    FILE *fp3;
    fp3 = fopen(FP3_W, "w");
    cv::Mat img = cv::imread(FNAME, CV_32FC3);

    long cnt = 0;
    for (int i=0; i<img.rows; i++)
        for (int j=0; j<img.cols; j++)
            for (int k=0; k<img.channels(); k++){
                if (cnt % 3 == 1){
                    fprintf(fp1, "%lf\n", double(img.at<cv::Vec3b>(i, j)[k]) / 255.);
                    cnt += 1;
                }
                else if (cnt % 3 == 2){
                    fprintf(fp2, "%lf\n", double(img.at<cv::Vec3b>(i, j)[k]) / 255.);
                    cnt += 1;
                }
                else {
                    fprintf(fp3, "%lf\n", double(img.at<cv::Vec3b>(i, j)[k]) / 255.);
                    cnt += 1;
                }
        }

}


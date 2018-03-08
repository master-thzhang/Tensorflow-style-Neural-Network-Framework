//
// Created by demo02 on 18-1-30.
//

#ifndef FORWARD_IMAGE_PROC_H
#define FORWARD_IMAGE_PROC_H

#include <iostream>

void get_next_batch(char *img_name, char *label_name, float *image_data, float *bbox_gt, int *shape_input){
    FILE *fp;
    fp = fopen(img_name, "r");
    // BGR To RGB
    int cnt = 0;
    for (int i=0; i<shape_input[0]; i++)
        for (int j=0; j<shape_input[1]; j++)
            for (int k=0; k<shape_input[2]; k++){
                fscanf(fp, "%f", &image_data[cnt++]);
            }
    fclose(fp);

    float bbox_in[4];
    FILE *fp2;
    fp2 = fopen(label_name, "r");
    fscanf(fp2, "%f", &bbox_in[0]);
    fscanf(fp2, "%f", &bbox_in[1]);
    fscanf(fp2, "%f", &bbox_in[2]);
    fscanf(fp2, "%f", &bbox_in[3]);
    bbox_gt[0] = bbox_in[0] - bbox_in[2] / 2;
    bbox_gt[1] = bbox_in[1] - bbox_in[3] / 2;
    bbox_gt[2] = bbox_in[0] + bbox_in[2] / 2;
    bbox_gt[3] = bbox_in[1] + bbox_in[3] / 2;

}

#endif //FORWARD_IMAGE_PROC_H

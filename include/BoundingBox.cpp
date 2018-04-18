//
// Created by demo02 on 18-4-4.
//

#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <iostream>
#include "BoundingBox.h"


BoundingBox::BoundingBox() {
    n = 0;
    values = (float **) malloc(sizeof(float*) * MAX_BBOX);
    for (int i=0; i<MAX_BBOX; i++)
        values[i] = (float *) malloc(sizeof(float) * BBOX_ITEM);
    for (int i=0; i<MAX_BBOX; i++)
        for (int j=0; j<BBOX_ITEM; j++)
            values[i][j] = -1;
}

float tmp[BBOX_ITEM];
void BoundingBox::Bboxread(char *fname, int height, int width) {
    FILE *fp;
    fp = fopen(fname, "r");
    int cnt = 0;
    while (!feof(fp)){

        for (int i=0; i<BBOX_ITEM; i++)
            fscanf(fp, "%f", &tmp[i]);
        values[cnt][0] = int(tmp[0]);
        values[cnt][1] = (tmp[1] - tmp[3] / 2) * width;
        values[cnt][2] = (tmp[2] - tmp[4] / 2) * height;
        values[cnt][3] = (tmp[1] + tmp[3] / 2) * width;
        values[cnt][4] = (tmp[2] + tmp[4] / 2) * height;
        cnt ++;
        if (cnt == MAX_BBOX)
            break;
    }
    n = cnt - 1;
    fclose(fp);
}

void BoundingBox::sortLower() {
    for (int i=0; i<n-1; i++)
        for (int j=i+1; j<n; j++)
            if (values[i][1] < values[j][1]){
                for (int k=0; k<BBOX_ITEM; k++){
                    float tmp = values[i][k];
                    values[i][k] = values[j][k];
                    values[j][k] = tmp;
                }
            }
}


#define IOU_TH  0.4

void BboxEval(BoundingBox bbox1, BoundingBox bbox2, float *avg_iou, float *avg_recall, float *avg_precision){
    bbox1.sortLower();
    bbox2.sortLower();
    int min_n = std::min(bbox1.n, bbox2.n);
    float IOU_avg = 0;
    int tot = bbox2.n;
    int tot_positive = bbox1.n;
    int recall = 0;
    int cnt = 0;
    for (int i=0; i<min_n; i++){
        float bbox_gt[4];
        float bbox_predicted[4];
        for (int k=0; k<4; k++){
            bbox_gt[k] = bbox1.values[i][k+1];
            bbox_predicted[k] = bbox2.values[i][k+1];
        }
        if (bbox_predicted[1] == -1)
            continue;
        std::cout << "BOX " << i << std::endl;
        float IOU_res = GetIOU(bbox_gt, bbox_predicted);
        std::cout << "IOU:" << IOU_res << std::endl;
        std::cout << "Class gt: "  << bbox1.values[i][0] << "  Class predicted: " << bbox2.values[i][0] << std::endl;
        IOU_avg += IOU_res;
        cnt += 1;
        if ((IOU_res > IOU_TH) && (bbox1.values[i][0] == bbox2.values[i][0]))
            recall += 1;

    }
    if (tot == 0) tot = 1;
    if (cnt == 0) cnt = 1;
    if (tot_positive == 0) tot_positive = 1;
    std::cout << "Recall: " << float(recall) / float(tot_positive) << " Precision: " << float(recall) / float(tot)
              << " IOU Avg:" << IOU_avg / float(cnt) << std::endl;
    *(avg_iou) += IOU_avg / float(cnt);
    *(avg_precision) += float(recall) / float(tot);
    *(avg_recall)+= float(recall) / float(tot_positive);
}

float GetIOU(float *bbox_gt, float *bbox_predicted) {
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
    return (float) (inter + 0.0) / (aarea + barea - inter + 0.0);
}

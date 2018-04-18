//
// Created by demo02 on 18-4-4.
//

#ifndef FORWARD_BOUNDINGBOX_H
#define FORWARD_BOUNDINGBOX_H

#define MAX_BBOX    10
#define BBOX_ITEM   5

class BoundingBox {
public:
    BoundingBox();
    void Bboxread(char *fname, int height, int width);
    int n;
    float **values;
    void sortLower();

};

void BboxEval(BoundingBox bbox1, BoundingBox bbox2, float *avg_iou, float *avg_recall, float *avg_precision);

float GetIOU(float *bbox_gt, float *bbox_predicted);

#endif //FORWARD_BOUNDINGBOX_H

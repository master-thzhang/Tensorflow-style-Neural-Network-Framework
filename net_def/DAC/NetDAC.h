//
// Created by demo02 on 18-3-7.
//

#ifndef FORWARD_NETDAC_H
#define FORWARD_NETDAC_H

#include "../../include/Network.h"

class NetDAC:Network {
public:
    NetDAC();
    void SetNet();
    void FeedInput(const int *shape, float *data, int bits, int shift_l);
    void FetchResult(float *dst);

    // Forward
    void Forward();
    void FixedForward();
    // Pruning
    void Prune_Weights();
    // Weight writer
    void Weight_Writer();
    // Activation Writer
    void Activation_Writer();
    // IOU Calc
    float GetIOU(float *bbox_gt, float *bbox_predicted);


private:
    // w=weights, b=bias, a=activation
    float ***input_data;
    float ****conv1_1_w;
    float *conv1_1_b;
    float ***conv1_1_a;;
    float ****conv1_2_w;
    float *conv1_2_b;
    float ***conv1_2_a;
    float ****conv1_3_w;
    float *conv1_3_b;
    float ***conv1_3_a;

    float ***pool1_a;

    float ****conv2_1_w;
    float *conv2_1_b;
    float ***conv2_1_a;
    float ****conv2_2_w;
    float *conv2_2_b;
    float ***conv2_2_a;

    float ***pool2_a;

    float ****conv3_1_w;
    float *conv3_1_b;
    float ***conv3_1_a;
    float ****conv3_2_w;
    float *conv3_2_b;
    float ***conv3_2_a;

    float ***pool3_a;

    float ****conv4_1_w;
    float *conv4_1_b;
    float ***conv4_1_a;

    float *conv_flat;

    float *fc1_a;
    float **fc1_w;
    float *fc1_b;


    float *fc2_a;
    float **fc2_w;
    float *fc2_b;



};


#endif //FORWARD_NETDAC_H

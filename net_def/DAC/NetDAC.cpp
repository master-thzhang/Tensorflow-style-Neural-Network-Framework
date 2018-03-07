//
// Created by demo02 on 18-3-7.
//

#include <iostream>
#include "NetDAC.h"
#include "DAC_include2.h"
#include "NETNAME_DAC.h"

#define IMG_H   360
#define IMG_W   640

NetDAC::NetDAC() {
    // Allocate memory for pointers
    AllocateMem(&input_data, shape_input);
    AllocateMem(&conv1_1_w, shape_conv1_1);
    AllocateMem(&conv1_1_b, shape_conv1_1_b);
    AllocateMem(&conv1_1_a, shape_act_1_1);
    AllocateMem(&conv1_2_w, shape_conv1_2);
    AllocateMem(&conv1_2_b, shape_conv1_2_b);
    AllocateMem(&conv1_2_a, shape_act_1_2);
    AllocateMem(&conv1_3_w, shape_conv1_3);
    AllocateMem(&conv1_3_b, shape_conv1_3_b);
    AllocateMem(&conv1_3_a, shape_act_1_3);
    AllocateMem(&pool1_a, shape_act_1);
    AllocateMem(&conv2_1_w, shape_conv2_1);
    AllocateMem(&conv2_1_b, shape_conv2_1_b);
    AllocateMem(&conv2_1_a, shape_act_2_1);
    AllocateMem(&conv2_2_w, shape_conv2_2);
    AllocateMem(&conv2_2_b, shape_conv2_2_b);
    AllocateMem(&conv2_2_a, shape_act_2_2);
    AllocateMem(&pool2_a, shape_act_2);
    AllocateMem(&conv3_1_w, shape_conv3_1);
    AllocateMem(&conv3_1_b, shape_conv3_1_b);
    AllocateMem(&conv3_1_a, shape_act_3_1);
    AllocateMem(&conv3_2_w, shape_conv3_2);
    AllocateMem(&conv3_2_b, shape_conv3_2_b);
    AllocateMem(&conv3_2_a, shape_act_3_2);
    AllocateMem(&pool3_a, shape_act_3);
    AllocateMem(&conv4_1_w, shape_conv4_1);
    AllocateMem(&conv4_1_b, shape_conv4_1_b);
    AllocateMem(&conv4_1_a, shape_act_4_1);
    AllocateMem(&conv_flat, shape_flat);
    AllocateMem(&fc1_w, shape_fc1);
    AllocateMem(&fc1_b, shape_fc1_b);
    AllocateMem(&fc1_a, shape_fc1_a);
    AllocateMem(&fc2_w, shape_fc2);
    AllocateMem(&fc2_b, shape_fc2_b);
    AllocateMem(&fc2_a, shape_fc2_a);
}

void NetDAC::SetNet() {
    SetLayer(shape_conv1_1,   WEIGHT_FILENAME[0], conv1_1_w, CONV1_1_BIT, CONV1_1_W_SHL);
    SetLayer(shape_conv1_1_b, WEIGHT_FILENAME[1], conv1_1_b, CONV1_1_BIT, CONV1_1_B_SHL);
    SetLayer(shape_conv1_2,   WEIGHT_FILENAME[2], conv1_2_w, CONV1_2_BIT, CONV1_2_W_SHL);
    SetLayer(shape_conv1_2_b, WEIGHT_FILENAME[3], conv1_2_b, CONV1_2_BIT, CONV1_2_B_SHL);
    SetLayer(shape_conv1_3,   WEIGHT_FILENAME[4], conv1_3_w, CONV1_3_BIT, CONV1_3_W_SHL);
    SetLayer(shape_conv1_3_b, WEIGHT_FILENAME[5], conv1_3_b, CONV1_3_BIT, CONV1_3_B_SHL);
    SetLayer(shape_conv2_1,   WEIGHT_FILENAME[6], conv2_1_w, CONV2_1_BIT, CONV2_1_W_SHL);
    SetLayer(shape_conv2_1_b, WEIGHT_FILENAME[7], conv2_1_b, CONV2_1_BIT, CONV2_1_B_SHL);
    SetLayer(shape_conv2_2,   WEIGHT_FILENAME[8], conv2_2_w, CONV2_2_BIT, CONV2_2_W_SHL);
    SetLayer(shape_conv2_2_b, WEIGHT_FILENAME[9], conv2_2_b, CONV2_2_BIT, CONV2_2_B_SHL);
    SetLayer(shape_conv3_1,   WEIGHT_FILENAME[10], conv3_1_w, CONV3_1_BIT, CONV3_1_W_SHL);
    SetLayer(shape_conv3_1_b, WEIGHT_FILENAME[11], conv3_1_b, CONV3_1_BIT, CONV3_1_B_SHL);
    SetLayer(shape_conv3_2,   WEIGHT_FILENAME[12], conv3_2_w, CONV3_2_BIT, CONV3_2_W_SHL);
    SetLayer(shape_conv3_2_b, WEIGHT_FILENAME[13], conv3_2_b, CONV3_2_BIT, CONV3_2_B_SHL);
    SetLayer(shape_conv4_1,   WEIGHT_FILENAME[14], conv4_1_w, CONV4_1_BIT, CONV4_1_W_SHL);
    SetLayer(shape_conv4_1_b, WEIGHT_FILENAME[15], conv4_1_b, CONV4_1_BIT, CONV4_1_B_SHL);
    SetLayer(shape_fc1,   WEIGHT_FILENAME[16], fc1_w, FC1_BIT, FC1_W_SHL);
    SetLayer(shape_fc1_b, WEIGHT_FILENAME[17], fc1_b, FC1_BIT, FC1_B_SHL);
    SetLayer(shape_fc2,   WEIGHT_FILENAME[18], fc2_w, FC2_BIT, FC2_W_SHL);
    SetLayer(shape_fc2_b, WEIGHT_FILENAME[19], fc2_b, FC2_BIT, FC2_B_SHL);
}

void NetDAC::FeedInput(const int *shape, float *data, int bits, int shift_l) {
    FeedData(shape, data, input_data, bits, shift_l);
}

void NetDAC::Forward() {
    Conv2d(shape_input, input_data, shape_act_1_1, conv1_1_a, shape_conv1_1, stride_conv1_1, pad_conv1_1, conv1_1_w, conv1_1_b, "conv1_1");
    ReLU(shape_act_1_1, conv1_1_a);

    Conv2d(shape_act_1_1, conv1_1_a, shape_act_1_2, conv1_2_a, shape_conv1_2, stride_conv1_2, pad_conv1_2, conv1_2_w, conv1_2_b, "conv1_2");
    ReLU(shape_act_1_2, conv1_2_a);

    Conv2d(shape_input, conv1_2_a, shape_act_1_3, conv1_3_a, shape_conv1_3, stride_conv1_3, pad_conv1_3, conv1_3_w, conv1_3_b, "conv1_3");
    ReLU(shape_act_1_3, conv1_3_a);

    MaxPool(shape_act_1_3, conv1_3_a, shape_act_1, pool1_a, ksize_pool1, stride_pool1);

    Conv2d(shape_act_1, pool1_a, shape_act_2_1, conv2_1_a, shape_conv2_1, stride_conv2_1, pad_conv2_1, conv2_1_w, conv2_1_b, "conv2_1");
    ReLU(shape_act_2_1, conv2_1_a);

    Conv2d(shape_act_2_1, conv2_1_a, shape_act_2_2, conv2_2_a, shape_conv2_2, stride_conv2_2, pad_conv2_2, conv2_2_w, conv2_2_b, "conv2_2");
    ReLU(shape_act_2_2, conv2_2_a);

    MaxPool(shape_act_2_2, conv2_2_a, shape_act_2, pool2_a, ksize_pool2, stride_pool2);

    Conv2d(shape_act_2, pool2_a, shape_act_3_1, conv3_1_a, shape_conv3_1, stride_conv3_1, pad_conv3_1, conv3_1_w, conv3_1_b, "conv3_1");
    ReLU(shape_act_3_1, conv3_1_a);

    Conv2d(shape_act_3_1, conv3_1_a, shape_act_3_2, conv3_2_a, shape_conv3_2, stride_conv3_2, pad_conv3_2, conv3_2_w, conv3_2_b, "conv3_2");
    ReLU(shape_act_3_2, conv3_2_a);

    MaxPool(shape_act_3_2, conv3_2_a, shape_act_3, pool3_a, ksize_pool3, stride_pool3);

    Conv2d(shape_act_3, pool3_a, shape_act_4_1, conv4_1_a, shape_conv4_1, stride_conv4_1, pad_conv4_1, conv4_1_w, conv4_1_b, "conv4_1");
    ReLU(shape_act_4_1, conv4_1_a);

    Reshape(shape_act_4_1, conv4_1_a, shape_flat, conv_flat);

    InnerProduct(shape_flat, conv_flat, shape_fc1_a, fc1_a, fc1_w, fc1_b, shape_fc1, "fc1");
    ReLU(shape_fc1_a, fc1_a);

    InnerProduct(shape_fc1_a, fc1_a, shape_fc2_a, fc2_a, fc2_w, fc2_b, shape_fc2, "fc2");
    ReLU(shape_fc2_a, fc2_a);
}

void NetDAC::FixedForward() {
    FixedConv2d(shape_input, input_data, shape_act_1_1, conv1_1_a, shape_conv1_1, stride_conv1_1,
                pad_conv1_1, conv1_1_w, conv1_1_b, CONV1_1_BIT, "conv1_1");
    ReLU(shape_act_1_1, conv1_1_a);

    FixedConv2d(shape_act_1_1, conv1_1_a, shape_act_1_2, conv1_2_a, shape_conv1_2, stride_conv1_2,
                pad_conv1_2, conv1_2_w, conv1_2_b, CONV1_2_BIT, "conv1_2");
    ReLU(shape_act_1_2, conv1_2_a);

    FixedConv2d(shape_input, conv1_2_a, shape_act_1_3, conv1_3_a, shape_conv1_3, stride_conv1_3,
                pad_conv1_3, conv1_3_w, conv1_3_b, CONV1_3_BIT, "conv1_3");
    ReLU(shape_act_1_3, conv1_3_a);

    MaxPool(shape_act_1_3, conv1_3_a, shape_act_1, pool1_a, ksize_pool1, stride_pool1);

    FixedConv2d(shape_act_1, pool1_a, shape_act_2_1, conv2_1_a, shape_conv2_1, stride_conv2_1,
                pad_conv2_1, conv2_1_w, conv2_1_b, CONV2_1_BIT, "conv2_1");
    ReLU(shape_act_2_1, conv2_1_a);

    FixedConv2d(shape_act_2_1, conv2_1_a, shape_act_2_2, conv2_2_a, shape_conv2_2, stride_conv2_2,
                pad_conv2_2, conv2_2_w, conv2_2_b, CONV2_2_BIT, "conv2_2");
    ReLU(shape_act_2_2, conv2_2_a);

    MaxPool(shape_act_2_2, conv2_2_a, shape_act_2, pool2_a, ksize_pool2, stride_pool2);

    FixedConv2d(shape_act_2, pool2_a, shape_act_3_1, conv3_1_a, shape_conv3_1, stride_conv3_1,
                pad_conv3_1, conv3_1_w, conv3_1_b, CONV3_1_BIT, "conv3_1");
    ReLU(shape_act_3_1, conv3_1_a);

    FixedConv2d(shape_act_3_1, conv3_1_a, shape_act_3_2, conv3_2_a, shape_conv3_2, stride_conv3_2, pad_conv3_2, conv3_2_w, conv3_2_b,
                CONV3_2_BIT, "conv3_2");
    ReLU(shape_act_3_2, conv3_2_a);

    MaxPool(shape_act_3_2, conv3_2_a, shape_act_3, pool3_a, ksize_pool3, stride_pool3);

    FixedConv2d(shape_act_3, pool3_a, shape_act_4_1, conv4_1_a, shape_conv4_1, stride_conv4_1,
                pad_conv4_1, conv4_1_w, conv4_1_b, CONV4_1_BIT, "conv4_1");
    ReLU(shape_act_4_1, conv4_1_a);

    Reshape(shape_act_4_1, conv4_1_a, shape_flat, conv_flat);

    FixedInnerProduct(shape_flat, conv_flat, shape_fc1_a, fc1_a, fc1_w, fc1_b, shape_fc1, FC1_BIT, "fc1");
    ReLU(shape_fc1_a, fc1_a);

    FixedInnerProduct(shape_fc1_a, fc1_a, shape_fc2_a, fc2_a, fc2_w, fc2_b, shape_fc2, FC2_BIT, "fc2");
    ReLU(shape_fc2_a, fc2_a);
}

void NetDAC::Prune_Weights() {
    float ratio = 0;
    float tot = 0;
    ratio += Pruning(conv1_1_w, CONV1_1_TH, shape_conv1_1, "conv1_1_w");
    tot += shape_conv1_1[0] * shape_conv1_1[1] * shape_conv1_1[2] * shape_conv1_1[3];
    //ratio += Pruning(conv1_1_b, CONV1_1_TH, shape_conv1_1_b, "conv1_1_b");
    tot += shape_conv1_1_b[0];
    ratio += Pruning(conv1_2_w, CONV1_2_TH, shape_conv1_2, "conv1_2_w");
    tot += shape_conv1_2[0] * shape_conv1_2[1] * shape_conv1_2[2] * shape_conv1_2[3];
    //ratio += Pruning(conv1_2_b, CONV1_2_TH, shape_conv1_2_b, "conv1_2_b");
    tot += shape_conv1_2_b[0];
    ratio += Pruning(conv1_3_w, CONV1_3_TH, shape_conv1_3, "conv1_3_w");
    tot += shape_conv1_3[0] * shape_conv1_3[1] * shape_conv1_3[2] * shape_conv1_3[3];
    //ratio += Pruning(conv1_3_b, CONV1_3_TH, shape_conv1_3_b, "conv1_3_b");
    tot += shape_conv1_3[0];
    ratio += Pruning(conv2_1_w, CONV2_1_TH, shape_conv2_1, "conv2_1_w");
    tot += shape_conv2_1[0] * shape_conv2_1[1] * shape_conv2_1[2] * shape_conv2_1[3];
    //ratio += Pruning(conv2_1_b, CONV2_1_TH, shape_conv2_1_b, "conv2_1_b");
    tot += shape_conv2_1_b[0];
    ratio += Pruning(conv2_2_w, CONV2_2_TH, shape_conv2_2, "conv2_2_w");
    tot += shape_conv2_2[0] * shape_conv2_2[1] * shape_conv2_2[2] * shape_conv2_2[3];
    //ratio += Pruning(conv2_2_b, CONV2_2_TH, shape_conv2_2_b, "conv2_2_b");
    tot += shape_conv2_2_b[0];
    ratio += Pruning(conv3_1_w, CONV3_1_TH, shape_conv3_1, "conv3_1_w");
    tot += shape_conv3_1[0] * shape_conv3_1[1] * shape_conv3_1[2] * shape_conv3_1[3];
    //ratio += Pruning(conv3_1_b, CONV3_1_TH, shape_conv3_1_b, "conv3_1_b");
    tot += shape_conv3_1_b[0];
    ratio += Pruning(conv3_2_w, CONV3_2_TH, shape_conv3_2, "conv3_2_w");
    tot += shape_conv3_2[0] * shape_conv3_2[1] * shape_conv3_2[2] * shape_conv3_2[3];
    //ratio += Pruning(conv3_2_b, CONV3_2_TH, shape_conv3_2_b, "conv3_2_b");
    tot += shape_conv3_2_b[0];
    ratio += Pruning(conv4_1_w, CONV4_1_TH, shape_conv4_1, "conv4_1_w");
    tot += shape_conv4_1[0] * shape_conv4_1[1] * shape_conv4_1[2] * shape_conv4_1[3];
    //ratio += Pruning(conv4_1_b, CONV4_1_TH, shape_conv4_1_b, "conv4_1_b");
    tot += shape_conv4_1_b[0];
    ratio += Pruning(fc1_w, FC1_TH, shape_fc1, "fc1_w");
    tot += shape_fc1[0] * shape_fc1[1];
    //ratio += Pruning(fc1_b, FC1_TH, shape_fc1_b, "fc1_b");
    tot += shape_fc1_b[0];
    ratio += Pruning(fc2_w, FC2_TH, shape_fc2, "fc2_w");
    tot += shape_fc2[0] * shape_fc2[1];
    //ratio += Pruning(fc2_b, FC2_TH, shape_fc2_b, "fc2_b");
    tot += shape_fc2[0];
    std::cout << tot << " parameters total, " << ratio << " parameters pruned" << std::endl;
    std::cout << ratio / tot * 100 << " percent Prune rate" << std::endl;
}

void NetDAC::Weight_Writer() {
    DumpWeights(shape_conv1_1, WEIGHT_FILENAME_OUT[0], conv1_1_w);
    DumpWeights(shape_conv1_1_b, WEIGHT_FILENAME_OUT[1], conv1_1_b);
    DumpWeights(shape_conv1_2, WEIGHT_FILENAME_OUT[2], conv1_2_w);
    DumpWeights(shape_conv1_2_b, WEIGHT_FILENAME_OUT[3], conv1_2_b);
    DumpWeights(shape_conv1_3, WEIGHT_FILENAME_OUT[4], conv1_3_w);
    DumpWeights(shape_conv1_3_b, WEIGHT_FILENAME_OUT[5], conv1_3_b);
    DumpWeights(shape_conv2_1, WEIGHT_FILENAME_OUT[6], conv2_1_w);
    DumpWeights(shape_conv2_1_b, WEIGHT_FILENAME_OUT[7], conv2_1_b);
    DumpWeights(shape_conv2_2, WEIGHT_FILENAME_OUT[8], conv2_2_w);
    DumpWeights(shape_conv2_2_b, WEIGHT_FILENAME_OUT[9], conv2_2_b);
    DumpWeights(shape_conv3_1, WEIGHT_FILENAME_OUT[10], conv3_1_w);
    DumpWeights(shape_conv3_1_b, WEIGHT_FILENAME_OUT[11], conv3_1_b);
    DumpWeights(shape_conv3_2, WEIGHT_FILENAME_OUT[12], conv3_2_w);
    DumpWeights(shape_conv3_2_b, WEIGHT_FILENAME_OUT[13], conv3_2_b);
    DumpWeights(shape_conv4_1, WEIGHT_FILENAME_OUT[14], conv4_1_w);
    DumpWeights(shape_conv4_1_b, WEIGHT_FILENAME_OUT[15], conv4_1_b);
    DumpWeights(shape_fc1, WEIGHT_FILENAME_OUT[16], fc1_w);
    DumpWeights(shape_fc1_b, WEIGHT_FILENAME_OUT[17], fc1_b);
    DumpWeights(shape_fc2, WEIGHT_FILENAME_OUT[18], fc2_w);
    DumpWeights(shape_fc2_b, WEIGHT_FILENAME_OUT[19], fc2_b);
}

void NetDAC::Activation_Writer() {
    DumpActivation(shape_input, INPUT_DUMP, input_data);
    DumpActivation(shape_act_1_1, ACTIVATION_FILENAME_OUT[0], conv1_1_a);
    DumpActivation(shape_act_1_2, ACTIVATION_FILENAME_OUT[1], conv1_2_a);
    DumpActivation(shape_act_1_3, ACTIVATION_FILENAME_OUT[2], conv1_3_a);
    DumpActivation(shape_act_2_1, ACTIVATION_FILENAME_OUT[3], conv2_1_a);
    DumpActivation(shape_act_2_2, ACTIVATION_FILENAME_OUT[4], conv2_2_a);
    DumpActivation(shape_act_3_1, ACTIVATION_FILENAME_OUT[5], conv3_1_a);
    DumpActivation(shape_act_3_2, ACTIVATION_FILENAME_OUT[6], conv3_2_a);
    DumpActivation(shape_act_4_1, ACTIVATION_FILENAME_OUT[7], conv4_1_a);
    DumpActivation(shape_fc1_a, ACTIVATION_FILENAME_OUT[8], fc1_a);
    DumpActivation(shape_fc2_a, ACTIVATION_FILENAME_OUT[9], fc2_a);
}

void NetDAC::FetchResult(float *dst) {
    float ans[4];
    for (int i=0; i<4; i++)
        ans[i] = 0;
    for (int i=0; i<5; i++){
        ans[0] += 0.2 * fc2_a[0+4*i];
        ans[1] += 0.2 * fc2_a[1+4*i];
        ans[2] += 0.2 * fc2_a[2+4*i];
        ans[3] += 0.2 * fc2_a[3+4*i];

    }
    dst[0] = ans[0] - ans[2] * ans[2] * ans[2] * ans[2] / 2;
    dst[1] = ans[1] - ans[3] * ans[3] * ans[3] * ans[3] / 2;
    dst[2] = ans[0] + ans[2] * ans[2] * ans[2] * ans[2] / 2;
    dst[3] = ans[1] + ans[3] * ans[3] * ans[3] * ans[3] / 2;
}

float NetDAC::GetIOU(float *bbox_gt, float *bbox_predicted) {
    int bbox_gt_int[4];
    int bbox_predicted_int[4];
    bbox_gt_int[0] = int(bbox_gt[0] * IMG_H);
    bbox_predicted_int[0] = int(bbox_predicted[0] * IMG_H);
    bbox_gt_int[1] = int(bbox_gt[1] * IMG_W);
    bbox_predicted_int[1] = int(bbox_predicted[1] * IMG_W);
    bbox_gt_int[2] = int(bbox_gt[2] * IMG_H);
    bbox_predicted_int[2] = int(bbox_predicted[2] * IMG_H);
    bbox_gt_int[3] = int(bbox_gt[3] * IMG_W);
    bbox_predicted_int[3] = int(bbox_predicted[3] * IMG_W);
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
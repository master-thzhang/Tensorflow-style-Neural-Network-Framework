
#include <iostream>
#include "Network.h"
#include "quantize.h"
#include "../include/DAC_include2.h"
#include "../include/NETNAME.h"

#define IMG_H   360
#define IMG_W   640

Network::Network() {
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

void Network::AllocateMem(float *****src, const int *shape){
    *src = (float ****) malloc(sizeof(float ***) * shape[0]);
    for (int i=0; i<shape[0]; i++){
        (*src)[i] = (float ***) malloc(sizeof(float **) * shape[1]);
        for (int j=0; j<shape[1]; j++){
            (*src)[i][j] = (float **) malloc(sizeof(float *) * shape[2]);
            for (int k=0; k<shape[2]; k++)
                (*src)[i][j][k] = (float *) malloc(sizeof(float) * shape[3]);
        }
    }
}

void Network::AllocateMem(float ****src, const int *shape){
    *src = (float ***) malloc(sizeof(float **) * shape[0]);
    for (int i=0; i<shape[0]; i++){
        (*src)[i] = (float **) malloc(sizeof(float *) * shape[1]);
        for (int j=0; j<shape[1]; j++)
            (*src)[i][j] = (float *) malloc(sizeof(float) * shape[2]);
    }
}


void Network::AllocateMem(float ***src, const int *shape){
    *src = (float **) malloc(sizeof(float *) * shape[0]);
    for (int i=0; i<shape[0]; i++){
        (*src)[i] = (float *) malloc(sizeof(float) * shape[1]);
    }
}

void Network::AllocateMem(float **src, const int *shape) {
    *src = (float *) malloc(sizeof(float) * shape[0]);
}




void Network::FeedData(const int *shape, float *data, float *dst, const int bits, const int shift_l) {
    int cnt = 0;
    for (int d1=0; d1<shape[0]; d1++)
        dst[d1] = quantize(data[cnt++], bits, shift_l);
}


void Network::FeedData(const int *shape, float *data, float **dst, const int bits, const int shift_l) {
    long cnt = 0;
    for (int d1=0; d1<shape[0]; d1++)
        for (int d2=0; d2<shape[1]; d2++)
            dst[d1][d2] = quantize(data[cnt++], bits, shift_l);
}


void Network::FeedData(const int *shape, float *data, float ***dst, const int bits, const int shift_l) {
    long cnt = 0;
    for (int d1=0; d1<shape[0]; d1++)
        for (int d2=0; d2<shape[1]; d2++)
            for (int d3=0; d3<shape[2]; d3++)
                    dst[d1][d2][d3]= quantize(data[cnt++], bits, shift_l);
}

void Network::FeedData(const int *shape, float *data, float ****dst, const int bits, const int shift_l) {
    long cnt = 0;
    for (int d1=0; d1<shape[0]; d1++)
        for (int d2=0; d2<shape[1]; d2++)
            for (int d3=0; d3<shape[2]; d3++)
                for (int d4=0; d4<shape[3]; d4++)
                    dst[d1][d2][d3][d4] = quantize(data[cnt++], bits, shift_l);
}

void Network::FeedInput(const int *shape, float *data, int bits, const int shift_l) {
    FeedData(shape, data, input_data, bits, shift_l);
}

void Network::FetchResult(float *dst) {
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

void Network::Reshape(const int *shape_src, float **src, const int *shape_dst, float ***dst) {
    int axis0 = 0;
    int axis1 = 0;
    for (int d1=0; d1<shape_dst[0]; d1++)
        for (int d2=0; d2<shape_dst[1]; d2++)
            for (int d3=0; d3<shape_dst[2]; d3++){
                dst[d1][d2][d3] = src[axis0][axis1++];
                if (axis1 == shape_src[1]){
                    axis1 = 0;
                    axis0 ++;
                }
            }
}

void Network::Reshape(const int *shape_src, float ***src, const int *shape_dst, float *dst) {
    int cnt = 0;
    for (int d1=0; d1<shape_src[0]; d1++)
        for (int d2=0; d2<shape_src[1]; d2++)
            for (int d3=0; d3<shape_src[2]; d3++){
                dst[cnt++] = src[d1][d2][d3];
            }
}

void Network::Conv2d(const int *shape_src, float ***src, const int *shape_dst, float ***dst, const int *kernal_size,
                     const int *stride, const int *padding, float ****weights, const float *bias, const std::string name) {
    // weights format: H,W,I,O
    std::cout << "Executing Convolution " << name << std::endl;
    for (int d1 = 0; d1 < shape_src[0]; d1++)                                               // H
        for (int d2 = 0; d2 < shape_src[1]; d2++)                                           // W
            for (int d3 = 0; d3 < kernal_size[3]; d3++) {                                   // OUT
                dst[d1][d2][d3] = bias[d3];
                for (int d4 = 0; d4 < kernal_size[2]; d4++)                                 // IN
                    for (int k1 = 0; k1 < kernal_size[0]; k1++)                             // H
                        for (int k2 = 0; k2 < kernal_size[1]; k2++) {                       // W
                            if ((d1 + k1 * stride[1] - padding[0] >= shape_src[0]) ||
                                (d2 + k2 * stride[2] - padding[1] >= shape_src[1]))
                                break;
                            if ((d1 + k1 * stride[1] - padding[0] < 0) || (d2 + k2 * stride[2] - padding[1] < 0))
                                continue;
                            dst[d1][d2][d3] += src[d1 + k1 * stride[1] - padding[0]][d2 + k2 * stride[2] -
                                                                                     padding[1]][d4] * weights[k1][k2][d4][d3];
                        }
            }

}

void Network::FixedConv2d(const int *shape_src, float ***src, const int *shape_dst, float ***dst, const int *kernal_size,
                     const int *stride, const int *padding, float ****weights, const float *bias, int bits,
                     const std::string name) {
    // weights format: H,W,I,O
    float max = -10.0;
    float min = 10.0;
    std::cout << "Executing Convolution " << name << std::endl;
    for (int d1 = 0; d1 < shape_src[0]; d1++)                                               // H
        for (int d2 = 0; d2 < shape_src[1]; d2++)                                           // W
            for (int d3 = 0; d3 < kernal_size[3]; d3++) {                                   // OUT
                dst[d1][d2][d3] = bias[d3];
                for (int d4 = 0; d4 < kernal_size[2]; d4++)                                 // IN
                    for (int k1 = 0; k1 < kernal_size[0]; k1++)                             // H
                        for (int k2 = 0; k2 < kernal_size[1]; k2++) {                       // W
                            if ((d1 + k1 * stride[1] - padding[0] >= shape_src[0]) ||
                                (d2 + k2 * stride[2] - padding[1] >= shape_src[1]))
                                break;
                            if ((d1 + k1 * stride[1] - padding[0] < 0) || (d2 + k2 * stride[2] - padding[1] < 0))
                                continue;
                            dst[d1][d2][d3] += src[d1 + k1 * stride[1] - padding[0]]
                                                        [d2 + k2 * stride[2] - padding[1]][d4] * weights[k1][k2][d4][d3];
                            if (dst[d1][d2][d3] > max)
                                max = dst[d1][d2][d3];
                            if (dst[d1][d2][d3] < min)
                                min = dst[d1][d2][d3];
                        }
                dst[d1][d2][d3] = quantize(dst[d1][d2][d3], bits, 0);
            }
    std::cout << name << "Max value during addition: " << max << " , Min value during addition: " << min << std::endl;

}

void Network::ReLU(const int *shape, float **data) {
    for (int d1=0; d1<shape[0]; d1++)
        for (int d2=0; d2<shape[1]; d2++)
            data[d1][d2] = data[d1][d2]>0 ? data[d1][d2] : 0;
}

void Network::ReLU(const int *shape, float ***data) {
    for (int d1=0; d1<shape[0]; d1++)
        for (int d2=0; d2<shape[1]; d2++)
            for (int d3=0; d3<shape[2]; d3++)
                data[d1][d2][d3] = data[d1][d2][d3]>0 ? data[d1][d2][d3] : 0;
}

void Network::ReLU(const int *shape, float *data) {
    for (int d1=0; d1<shape[0]; d1++)
        data[d1] = data[d1]>0 ? data[d1] : 0;
}


void Network::InnerProduct(const int *shape_src, float *src, const int *shape_dst, float *dst, float **weights,
                           const float *bias, const int *ndim, const std::string name) {
    if (shape_src[0] != ndim[0]){
        std::cerr << "InnerProduct weight size mismatch!" << std::endl;
    }
    std::cout << "Executing InnerProduct " << name << std::endl;
    for (int d2=0; d2<ndim[1]; d2++) {
        dst[d2] = bias[d2];
        for (int d1 = 0; d1 < ndim[0]; d1++)
            dst[d2] += weights[d1][d2] * src[d1];
    }
}

void Network::FixedInnerProduct(const int *shape_src, float *src, const int *shape_dst, float *dst, float **weights,
                           const float *bias, const int *ndim, int bits,
                           const std::string name) {
    if (shape_src[0] != ndim[0]){
        std::cerr << "InnerProduct weight size mismatch!" << std::endl;
    }
    float max = -10.0;
    float min = 10.0;
    std::cout << "Executing InnerProduct " << name << std::endl;
    for (int d2=0; d2<ndim[1]; d2++) {
        dst[d2] = bias[d2];
        for (int d1 = 0; d1 < ndim[0]; d1++) {
            dst[d2] += weights[d1][d2] * src[d1];
            if (dst[d2] > max)
                max = dst[d2];
            if (dst[d2] < min)
                min = dst[d2];
        }
        dst[d2] = quantize(dst[d2], bits, 0);
    }
    std::cout << name << "Max value during addition: " << max << " , Min value during addition: " << min << std::endl;
}

void Network::MaxPool(const int *shape_src, float ***src, const int *shape_dst, float ***dst, const int *ksize, const int *stride) {
    for (int d3=0; d3<shape_src[2]; d3++)
        for (int d1=0; d1<shape_dst[0]; d1++)
            for (int d2=0; d2<shape_dst[1]; d2++){
                float maxn = 0.0;
                for (int k1=0; k1<ksize[1]; k1++)
                    for (int k2=0; k2<ksize[2]; k2++)
                        if (src[d1*stride[1]+k1][d2*stride[2]+k2][d3]>maxn)
                            maxn = src[d1*stride[1]+k1][d2*stride[2]+k2][d3];
                dst[d1][d2][d3] = maxn;
            }
}


void Network::SetLayer(const int *shape, char *Wname, float ****dst, int bits, int shift_l) {
    long num_of_inputs = shape[0] * shape[1] * shape[2] * shape[3];
    auto *data = new float [num_of_inputs];
    long cnt = 0;
    freopen(Wname, "r", stdin);
    float min = 10.0;
    float max = -10.0;
    for (long i=0; i<num_of_inputs; i++){
        scanf("%f", &data[i]);
        if (data[i] < min){
            min = data[i];
        }
        if (data[i] > max){
            max = data[i];
        }
    }
    std::cout << Wname << " Weight max: " << max << " , Weight min: " << min << std::endl;
    FeedData(shape, data, dst, bits, shift_l);
    delete [] data;
    fclose(stdin);
}

void Network::SetLayer(const int *shape, char *Wname, float ***dst, int bits, int shift_l) {
    long num_of_inputs = shape[0] * shape[1] * shape[2];
    auto *data = new float [num_of_inputs];
    long cnt = 0;
    float min = 10.0;
    float max = -10.0;
    freopen(Wname, "r", stdin);
    for (long i=0; i<num_of_inputs; i++){
        scanf("%f", &data[i]);
        if (data[i] < min){
            min = data[i];
        }
        if (data[i] > max){
            max = data[i];
        }
    }
    std::cout << Wname << " Weight max: " << max << " , Weight min: " << min << std::endl;
    FeedData(shape, data, dst, bits, shift_l);
    delete [] data;
    fclose(stdin);
}

void Network::SetLayer(const int *shape, char *Wname, float **dst, int bits, int shift_l) {
    long num_of_inputs = shape[0] * shape[1];
    auto *data = new float [num_of_inputs];
    long cnt = 0;
    float min = 10.0;
    float max = -10.0;
    freopen(Wname, "r", stdin);
    for (long i=0; i<num_of_inputs; i++){
        scanf("%f", &data[i]);
        if (data[i] < min){
            min = data[i];
        }
        if (data[i] > max){
            max = data[i];
        }
    }
    std::cout << Wname << " Weight max: " << max << " , Weight min: " << min << std::endl;
    FeedData(shape, data, dst, bits, shift_l);
    delete [] data;
    fclose(stdin);
}

void Network::SetLayer(const int *shape, char *Wname, float *dst, int bits, int shift_l) {
    long num_of_inputs = shape[0];
    auto *data = new float [num_of_inputs];
    long cnt = 0;
    float min = 10.0;
    float max = -10.0;
    freopen(Wname, "r", stdin);
    for (long i=0; i<num_of_inputs; i++){
        scanf("%f", &data[i]);
        if (data[i] < min){
            min = data[i];
        }
        if (data[i] > max){
            max = data[i];
        }
    }
    std::cout << Wname << " Weight max: " << max << " , Weight min: " << min << std::endl;
    FeedData(shape, data, dst, bits, shift_l);
    delete [] data;
    fclose(stdin);
}

void Network::SetNet() {
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

void Network::Forward() {
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

void Network::FixedForward() {
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

float Network::GetIOU(float *bbox_gt, float *bbox_predicted){
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

void Network::DumpActivation(const int *shape, char *fname, float *data) {
    //freopen(fname, "w", stdout);
    FILE *fp;
    fp = fopen(fname, "w");
    for (int i=0; i<shape[0]; i++){
        fprintf(fp, "%f", data[i]);
        fprintf(fp, "\n");
    }
    fclose(fp);
}

void Network::DumpActivation(const int *shape, char *fname, float ***data) {
    FILE *fp;
    fp = fopen(fname, "w");
    for (int i=0; i<shape[0]; i++)
        for (int j=0; j<shape[1]; j++)
            for (int k=0; k<shape[2]; k++) {
                fprintf(fp, "%f", data[i][j][k]);
                fprintf(fp, "\n");
    }
    fclose(fp);
}

void Network::Activation_Writer() {
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

void Network::Weight_Writer() {
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

void Network::DumpWeights(const int *shape, char *fname, float *data) {
    FILE *fp;
    fp = fopen(fname, "w");
    for (int i=0; i<shape[0]; i++){
        fprintf(fp, "%.12f", data[i]);
        fprintf(fp, "\n");
    }
    fclose(fp);
}

void Network::DumpWeights(const int *shape, char *fname, float **data) {
    FILE *fp;
    fp = fopen(fname, "w");
    for (int i=0; i<shape[0]; i++)
        for (int j=0; j<shape[1]; j++){
            fprintf(fp, "%.12f", data[i][j]);
            fprintf(fp, "\n");
    }
    fclose(fp);
}

void Network::DumpWeights(const int *shape, char *fname, float ****data) {
    FILE *fp;
    fp = fopen(fname, "w");
    for (int i=0; i<shape[0]; i++)
        for (int j=0; j<shape[1]; j++)
            for (int k=0; k<shape[2]; k++)
                for (int l=0; l<shape[3]; l++){
                    fprintf(fp, "%.12f", data[i][j][k][l]);
                    fprintf(fp, "\n");
        }
    fclose(fp);
}

float Network::Pruning(float *data, float d_th, const int shape[], const char *name) {
    float cnt = 0;
    float pruned = 0;
    for (int i=0; i<shape[0]; i++){
        if (fabsf(data[i]) < d_th){
            data[i] = 0;
            pruned += 1;
        }
        cnt += 1;
    }
    std::cout << pruned / cnt * 100 << " percent pruned for layer " << name << std::endl;
    return pruned;
}


float Network::Pruning(float **data, float d_th, const int shape[], const char *name) {
    float cnt = 0;
    float pruned = 0;
    for (int i=0; i<shape[0]; i++)
        for (int j=0; j<shape[1]; j++) {
            if (fabsf(data[i][j]) < d_th){
                data[i][j] = 0;
                pruned += 1;
            }
            cnt += 1;
        }
    std::cout << pruned / cnt * 100 << " percent pruned for layer " << name << std::endl;
    return pruned;
}


float Network::Pruning(float ***data, float d_th, const int shape[], const char *name) {
    float cnt = 0;
    float pruned = 0;
    for (int i=0; i<shape[0]; i++)
        for (int j=0; j<shape[1]; j++)
            for (int k=0; k<shape[2]; k++) {
                if (fabsf(data[i][j][k]) < d_th){
                    data[i][j][k] = 0;
                    pruned += 1;
                }
                cnt += 1;
            }
    std::cout << pruned / cnt * 100 << " percent pruned for layer " << name << std::endl;
    return pruned;
}

float Network::Pruning(float ****data, float d_th, const int shape[], const char *name) {
    float cnt = 0;
    float pruned = 0;
    for (int i=0; i<shape[0]; i++)
        for (int j=0; j<shape[1]; j++)
            for (int k=0; k<shape[2]; k++)
                for (int l=0; l<shape[3]; l++) {
                if (fabsf(data[i][j][k][l]) < d_th){
                    data[i][j][k][l] = 0;
                    pruned += 1;
                }
                cnt += 1;
            }
    std::cout << pruned / cnt * 100 << " percent pruned for layer " << name << std::endl;
    return pruned;
}

void Network::Prune_Weights() {
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

void Network::LeakyReLU(const int *shape, float *data, float alpha) {
    for (int i=0; i<shape[0]; i++){
        float maxn, minn;
        if (data[i]>0) {
            maxn = data[i];
            minn = 0;
        }
        else{
            maxn = 0;
            minn = data[i];
        }
        data[i] = maxn + alpha * minn;
    }
}

void Network::LeakyReLU(const int *shape, float **data, float alpha) {
    for (int i=0; i<shape[0]; i++)
        for (int j=0; j<shape[1]; j++){
            float maxn, minn;
            if (data[i][j]>0) {
                maxn = data[i][j];
                minn = 0;
            }
            else{
                maxn = 0;
                minn = data[i][j];
            }
            data[i][j] = maxn + alpha * minn;
        }
}

void Network::LeakyReLU(const int *shape, float ***data, float alpha) {
    for (int i=0; i<shape[0]; i++)
        for (int j=0; j<shape[1]; j++)
            for (int k=0; k<shape[2]; k++){
                float maxn, minn;
                if (data[i][j]>0) {
                    maxn = data[i][j][k];
                    minn = 0;
                }
                else{
                    maxn = 0;
                    minn = data[i][j][k];
                }
                data[i][j][k] = maxn + alpha * minn;
            }
}

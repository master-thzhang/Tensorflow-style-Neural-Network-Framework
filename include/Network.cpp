
#include <iostream>
#include <assert.h>
#include "Network.h"
#include "quantize.h"

#include "gpu_include/GPU_def.h"
#include "gpu_include/cuda_init.h"



Network::Network() {
#ifndef CPU_ONLY
_gpu_init_CUDA();
#endif

}

void Network::AllocateMem(float *****src, int *shape){
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

void Network::AllocateMem(float ****src, int *shape){
    *src = (float ***) malloc(sizeof(float **) * shape[0]);
    for (int i=0; i<shape[0]; i++){
        (*src)[i] = (float **) malloc(sizeof(float *) * shape[1]);
        for (int j=0; j<shape[1]; j++)
            (*src)[i][j] = (float *) malloc(sizeof(float) * shape[2]);
    }
}


void Network::AllocateMem(float ***src, int *shape){
    *src = (float **) malloc(sizeof(float *) * shape[0]);
    for (int i=0; i<shape[0]; i++){
        (*src)[i] = (float *) malloc(sizeof(float) * shape[1]);
    }
}

void Network::AllocateMem(int ***src, int *shape){
    *src = (int **) malloc(sizeof(int *) * shape[0]);
    for (int i=0; i<shape[0]; i++){
        (*src)[i] = (int *) malloc(sizeof(int) * shape[1]);
    }
}

void Network::AllocateMem(float **src, int *shape) {
    *src = (float *) malloc(sizeof(float) * shape[0]);
}




void Network::FeedData(int *shape, float *data, float *dst, int bits, int shift_l) {
    int cnt = 0;
    for (int d1=0; d1<shape[0]; d1++)
        dst[d1] = quantize(data[cnt++], bits, shift_l);
}


void Network::FeedData(int *shape, float *data, float **dst, int bits, int shift_l) {
    long cnt = 0;
    for (int d1=0; d1<shape[0]; d1++)
        for (int d2=0; d2<shape[1]; d2++)
            dst[d1][d2] = quantize(data[cnt++], bits, shift_l);
}


void Network::FeedData(int *shape, float *data, float ***dst, int bits, int shift_l) {
    long cnt = 0;
    for (int d1=0; d1<shape[0]; d1++)
        for (int d2=0; d2<shape[1]; d2++)
            for (int d3=0; d3<shape[2]; d3++)
                    dst[d1][d2][d3]= quantize(data[cnt++], bits, shift_l);
}

void Network::FeedData(int *shape, float *data, float ****dst, int bits, int shift_l) {
    long cnt = 0;
    for (int d1=0; d1<shape[0]; d1++)
        for (int d2=0; d2<shape[1]; d2++)
            for (int d3=0; d3<shape[2]; d3++)
                for (int d4=0; d4<shape[3]; d4++)
                    dst[d1][d2][d3][d4] = quantize(data[cnt++], bits, shift_l);
}



void Network::Reshape(int *shape_src, float **src, int *shape_dst, float ***dst) {
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


void Network::Reshape(int *shape_src, float ***src, int *shape_dst, float *dst) {
    int cnt = 0;
    for (int d1=0; d1<shape_src[0]; d1++)
        for (int d2=0; d2<shape_src[1]; d2++)
            for (int d3=0; d3<shape_src[2]; d3++){
                dst[cnt++] = src[d1][d2][d3];
            }
}

void Network::Reshape(int *shape_src, float ****src, int *shape_dst, float *dst) {
    int cnt = 0;
    for (int d1=0; d1<shape_src[0]; d1++)
        for (int d2=0; d2<shape_src[1]; d2++)
            for (int d3=0; d3<shape_src[2]; d3++)
                for (int d4=0; d4<shape_src[3]; d4++){
                    dst[cnt++] = src[d1][d2][d3][d4];
            }
}

void Network::Conv2d(int *shape_src, float ***src, int *shape_dst, float ***dst, int *kernal_size,
                     int *stride, int *padding, float ****weights, float *bias, const std::string name) {
    // weights format: H,W,I,O
#ifdef CPU_ONLY
    float max = -100.0;
    float min = 100.0;
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
                            if (dst[d1][d2][d3] > max)
                                max = dst[d1][d2][d3];
                            if (dst[d1][d2][d3] < min)
                                min = dst[d1][d2][d3];
                        }
            }
    std::cout << name << "Max value during addition: " << max << " , Min value during addition: " << min << std::endl;
#else
    Conv2d_GPU(shape_src, src, shape_dst, dst, kernal_size, stride, padding, weights, bias, name);
#endif
}

void Network::FixedConv2d(int *shape_src, float ***src, int *shape_dst, float ***dst, int *kernal_size,
                     int *stride, int *padding, float ****weights, float *bias, int bits,
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

void Network::ReLU(int *shape, float **data) {
    for (int d1=0; d1<shape[0]; d1++)
        for (int d2=0; d2<shape[1]; d2++)
            data[d1][d2] = data[d1][d2]>0 ? data[d1][d2] : 0;
}

void Network::ReLU(int *shape, float ***data) {
    for (int d1=0; d1<shape[0]; d1++)
        for (int d2=0; d2<shape[1]; d2++)
            for (int d3=0; d3<shape[2]; d3++)
                data[d1][d2][d3] = data[d1][d2][d3]>0 ? data[d1][d2][d3] : 0;
}

void Network::ReLU(int *shape, float *data) {
    for (int d1=0; d1<shape[0]; d1++)
        data[d1] = data[d1]>0 ? data[d1] : 0;
}


void Network::InnerProduct(int *shape_src, float *src, int *shape_dst, float *dst, float **weights,
                           float *bias, int *ndim, const std::string name) {
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
    }
    std::cout << name << "Max value during addition: " << max << " , Min value during addition: " << min << std::endl;

}

void Network::FixedInnerProduct(int *shape_src, float *src, int *shape_dst, float *dst, float **weights,
                           float *bias, int *ndim, int bits,
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

void Network::MaxPool(int *shape_src, float ***src, int *shape_dst, float ***dst, int *ksize, int *stride) {
    for (int d3=0; d3<shape_src[2]; d3++)
        for (int d1=0; d1<shape_dst[0]; d1++)
            for (int d2=0; d2<shape_dst[1]; d2++){
                float maxn = -900.0;
                for (int k1=0; k1<ksize[1]; k1++)
                    for (int k2=0; k2<ksize[2]; k2++) {
                        if ((d1 * stride[1] + k1 >= shape_src[0]) || (d2 * stride[2] + k2 >= shape_src[1]))
                            continue;
                        if (src[d1 * stride[1] + k1][d2 * stride[2] + k2][d3] > maxn)
                            maxn = src[d1 * stride[1] + k1][d2 * stride[2] + k2][d3];
                    }
                dst[d1][d2][d3] = maxn;
            }
}


void Network::SetLayer(int *shape, char *Wname, float ****dst, int bits, int shift_l) {
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

void Network::SetLayer(int *shape, char *Wname, float ***dst, int bits, int shift_l) {
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

void Network::SetLayer(int *shape, char *Wname, float **dst, int bits, int shift_l) {
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

void Network::SetLayer(int *shape, char *Wname, float *dst, int bits, int shift_l) {
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


void Network::DumpActivation(int *shape, char *fname, float *data) {
    //freopen(fname, "w", stdout);
    FILE *fp;
    fp = fopen(fname, "w");
    for (int i=0; i<shape[0]; i++){
        fprintf(fp, "%f,", data[i]);
        fprintf(fp, "\n");
    }
    fclose(fp);
}

void Network::DumpActivation(int *shape, char *fname, int ****data) {
    FILE *fp;
    fp = fopen(fname, "w");
    for (int i=0; i<shape[0]; i++)
        for (int j=0; j<shape[1]; j++)
            for (int k=0; k<shape[2]; k++)
                for (int l=0; l<shape[2]; l++){
                    fprintf(fp, "%d", data[i][j][k][l]);
                    fprintf(fp, "\n");
                }
    fclose(fp);
}

void Network::DumpActivation(int *shape, char *fname, float ***data) {
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


void Network::DumpWeights(int *shape, char *fname, float *data) {
    FILE *fp;
    fp = fopen(fname, "w");
    for (int i=0; i<shape[0]; i++){
        fprintf(fp, "%.12f", data[i]);
        fprintf(fp, "\n");
    }
    fclose(fp);
}

void Network::DumpWeights(int *shape, char *fname, float **data) {
    FILE *fp;
    fp = fopen(fname, "w");
    for (int i=0; i<shape[0]; i++)
        for (int j=0; j<shape[1]; j++){
            fprintf(fp, "%.12f", data[i][j]);
            fprintf(fp, "\n");
    }
    fclose(fp);
}

void Network::DumpWeights(int *shape, char *fname, float ****data) {
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

float Network::Pruning(float *data, float d_th, int shape[], const char *name) {
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


float Network::Pruning(float **data, float d_th, int shape[], const char *name) {
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


float Network::Pruning(float ***data, float d_th, int shape[], const char *name) {
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

float Network::Pruning(float ****data, float d_th, int shape[], const char *name) {
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

void Network::LeakyReLU(int *shape, float *data, float alpha) {
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

void Network::LeakyReLU(int *shape, float **data, float alpha) {
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

void Network::LeakyReLU(int *shape, float ***data, float alpha) {
    for (int i=0; i<shape[0]; i++)
        for (int j=0; j<shape[1]; j++)
            for (int k=0; k<shape[2]; k++){
                float maxn, minn;
                if (data[i][j][k]>0) {
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

void Network::Transpose3D(int *shape_src, float ***src, int *shape_dst, float ***dst, int *cfg) {
    if ((cfg[0] == 2) && (cfg[1] == 0) && (cfg[2] == 1)){
        Transpose3D_201(shape_src, src, shape_dst, dst);
    }
}

void Network::Transpose3D_201(int *shape_src, float ***src, int *shape_dst, float ***dst) {
    for (int d1=0; d1<shape_src[0]; d1++)
        for (int d2=0; d2<shape_src[1]; d2++)
            for (int d3=0; d3<shape_src[2]; d3++)
                dst[d3][d1][d2] = src[d1][d2][d3];
}

void Network::Conv2d_GPU(int *shape_src, float ***src, int *shape_dst, float ***dst, int *kernal_size,
                         int *stride, int *padding, float ****weights, float *bias,
                         const std::string name) {
#ifndef CPU_ONLY
    // First reshape array to 1D
    std::cout << "GPU layer " << name << std::endl;
    int shape_reshape_src[1] = {shape_src[0]*shape_src[1]*shape_src[2]};
    float *reshape_src;
    AllocateMem(&reshape_src, shape_reshape_src);
    Reshape(shape_src, src, shape_reshape_src, reshape_src);
    int shape_reshape_weight[1] = {kernal_size[0] * kernal_size[1] * shape_src[2] * shape_dst[2]};
    float *reshape_weight;
    AllocateMem(&reshape_weight, shape_reshape_weight);
    int shape_weight[4] = {kernal_size[0], kernal_size[1], shape_src[2], shape_dst[2]};
    Reshape(shape_weight, weights, shape_reshape_weight, reshape_weight);
    float *reshape_dst;
    int shape_dst_reshape[1] = {shape_dst[0] * shape_dst[1] * shape_dst[2]};
    AllocateMem(&reshape_dst, shape_dst_reshape);
    conv2d_GPU_def(reshape_src, shape_src, reshape_weight, kernal_size, bias, reshape_dst, shape_dst, stride, padding);
    long cnt = 0;
    for (int i=0; i<shape_dst[0]; i++)
        for (int j=0; j<shape_dst[1]; j++)
            for (int k=0; k<shape_dst[2]; k++)
                dst[i][j][k] = reshape_dst[cnt++];
    free(reshape_dst);
    free(reshape_src);
#endif
}

void Network::InnerProduct_GPU(int *shape_src, float *src, int *shape_dst, float *dst, float **weights,
                               float *bias, int *ndim, std::string name) {

}

void Network::Softmax(int *shape, float *data) {
    float sum = 0;
    for (int i=0; i<shape[0]; i++)
        sum += exp(data[i]);
    for (int i=0; i<shape[0]; i++)
        data[i] = exp(data[i]) / sum;
}

void Network::L2norm(int *shape, float ***data, int axis) {
    if (axis == 0){
        for (int d1=0; d1<shape[1]; d1++)
            for (int d2=0; d2<shape[2]; d2++) {
                float sum = 0;
                for (int i=0; i<shape[0]; i++)
                    sum += data[i][d1][d2] * data[i][d1][d2];
                for (int i=0; i<shape[0]; i++)
                    data[i][d1][d2] = data[i][d1][d2] / sqrt(sum);
            }
    }
    else if (axis == 1){
        for (int d1=0; d1<shape[0]; d1++)
            for (int d2=0; d2<shape[2]; d2++) {
                float sum = 0;
                for (int i=0; i<shape[1]; i++)
                    sum += data[d1][i][d2] * data[d1][i][d2];
                for (int i=0; i<shape[1]; i++)
                    data[d1][i][d2] = data[d1][i][d2] / sqrt(sum);
            }
    }
    else if (axis == 2){
        for (int d1=0; d1<shape[0]; d1++)
            for (int d2=0; d2<shape[1]; d2++) {
                float sum = 0;
                for (int i=0; i<shape[2]; i++)
                    sum += data[d1][d2][i] * data[d1][d2][i];
                for (int i=0; i<shape[2]; i++)
                    data[d1][d2][i] = data[d1][d2][i] / sqrt(sum);
            }
    }
}


// NCHW to NHWC
void Network::Channel_to_last(int *shape_src, float ***src, int *shape_dst, float ***dst) {
    assert(shape_src[1] == shape_dst[3]);
    for (int i=0; i<shape_src[0]; i++)
        for (int j=0; j<shape_src[1]; j++)
            for (int k=0; k<shape_src[2]; k++)
                dst[j][k][i] = src[i][j][k];
}


void Network::pad2d(int *shape_src, float ***src, int *shape_dst, float ***dst, int *padding, int format) {
// 0: HWC format, 1: CHW format
    assert(shape_src[2] == shape_dst[2]);
    if (format == 0){
        for (int i=0; i<shape_src[2]; i++){
            for (int j=0; j<shape_src[1]; j++){
                for (int k=0; k<padding[0]; k++){
                    dst[0 + k][j][i] = 0;
                    dst[shape_src[0]+padding[0] + k][j][i] = 0;
                }
            }
            for (int j=0; j<shape_src[0]; j++){
                for (int k=0; k<padding[1]; k++){
                    dst[j][0+k][i] = 0;
                    dst[j][shape_src[1]+padding[1] + k][i] = 0;
                }
            }
            for (int j=0; j<shape_src[0]; j++)
                for (int k=0; k<shape_src[1]; k++)
                    dst[j+padding[0]][k+padding[1]][i] = src[j][k][i];
        }

    }
    else{
        for (int i=0; i<shape_src[0]; i++){
            for (int j=0; j<shape_src[2]; j++){
                for (int k=0; k<padding[0]; k++){
                    dst[i][0 + k][j] = 0;
                    dst[i][shape_src[1]+padding[0] + k][j] = 0;
                }
            }
            for (int j=0; j<shape_src[1]; j++){
                for (int k=0; k<padding[1]; k++){
                    dst[i][j][0+k] = 0;
                    dst[i][j][shape_src[2]+padding[1]+k] = 0;
                }
            }
            for (int j=0; j<shape_src[1]; j++)
                for (int k=0; k<shape_src[2]; k++)
                    dst[i][j+padding[0]][k+padding[1]] = src[i][j][k];
        }

    }



}

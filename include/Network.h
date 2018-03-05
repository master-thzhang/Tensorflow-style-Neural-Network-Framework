
#ifndef FORWARD_NETWORK_H
#define FORWARD_NETWORK_H


class Network {
public:
    Network();
    // Allocator
    void AllocateMem(float *****src, const int *shape);
    void AllocateMem(float ****src, const int *shape);
    void AllocateMem(float ***src, const int *shape);
    void AllocateMem(float **src, const int *shape);
    // Initialize weights

    void FeedData(const int *shape, float *data, float *dst, int bits, int shift_l);
    void FeedData(const int *shape, float *data, float **dst, int bits, int shift_l);
    void FeedData(const int *shape, float *data, float ***dst, int bits, int shift_l);
    void FeedData(const int *shape, float *data, float ****dst, int bits, int shift_l);
    void SetNet();

    void FeedInput(const int *shape, float *data, int bits, int shift_l);
    void FetchResult(float *dst);
    float GetIOU(float *bbox_gt, float *bbox_predicted);

    void SetLayer(const int *shape, char *Wname, float ****dst, int bits, int shift_l);
    void SetLayer(const int *shape, char *Wname, float ***dst, int bits, int shift_l);
    void SetLayer(const int *shape, char *Wname, float **dst, int bits, int shift_l);
    void SetLayer(const int *shape, char *Wname, float *dst, int bits, int shift_l);

    // Layers
    void Reshape(const int *shape_src, float **src, const int *shape_dst, float ***dst);
    void Reshape(const int *shape_src, float ***src, const int *shape_dst, float *dst);
    void Conv2d(const int *shape_src, float ***src, const int *shape_dst, float ***dst, const int *kernal_size,
                const int *stride, const int *padding, float ****weights, const float *bias, const std::string name);
    void InnerProduct(const int *shape_src, float *src, const int *shape_dst, float *dst, float **weights,
                      const float *bias, const int *ndim, const std::string name);
    void MaxPool(const int *shape_src, float ***src, const int *shape_dst, float ***dst, const int *ksize, const int *stride);
    void ReLU(const int *shape, float **data);
    void ReLU(const int *shape, float ***data);
    void ReLU(const int *shape, float *data);

    void LeakyReLU(const int *shape, float *data);
    void LeakyReLU(const int *shape, float **data);
    void LeakyReLU(const int *shape, float ***data);

    // Fixed Layers
    void FixedConv2d(const int *shape_src, float ***src, const int *shape_dst, float ***dst, const int *kernal_size,
                const int *stride, const int *padding, float ****weights, const float *bias, int bits, const std::string name);
    void FixedInnerProduct(const int *shape_src, float *src, const int *shape_dst, float *dst, float **weights,
                      const float *bias, const int *ndim, int bits, const std::string name);
    // Forward
    void Forward();
    void FixedForward();
    // Dump Activation
    void DumpActivation(const int *shape, char *fname, float ***data);
    void DumpActivation(const int *shape, char *fname, float *data);
    void Activation_Writer();
    // Dump Weights
    void DumpWeights(const int *shape, char *fname, float *data);
    void DumpWeights(const int *shape, char *fname, float **data);
    void DumpWeights(const int *shape, char *fname, float ****data);
    void Weight_Writer();

    // Pruning
    float Pruning(float *data, float d_th, const int shape[], const char *name);
    float Pruning(float **data, float d_th, const int shape[], const char *name);
    float Pruning(float ***data, float d_th, const int shape[], const char *name);
    float Pruning(float ****data, float d_th, const int shape[], const char *name);
    void Prune_Weights();

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


#endif //FORWARD_NETWORK_H

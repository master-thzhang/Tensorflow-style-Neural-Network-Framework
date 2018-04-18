
#ifndef FORWARD_NETWORK_H
#define FORWARD_NETWORK_H


class Network {
public:
    Network();
    // Allocator
    void AllocateMem(float *****src, int *shape);
    void AllocateMem(float ****src, int *shape);
    void AllocateMem(float ***src, int *shape);
    void AllocateMem(float **src, int *shape);
    void AllocateMem(int ***src, int *shape);

    // Initialize weights
    void FeedData(int *shape, float *data, float *dst, int bits, int shift_l);
    void FeedData(int *shape, float *data, float **dst, int bits, int shift_l);
    void FeedData(int *shape, float *data, float ***dst, int bits, int shift_l);
    void FeedData(int *shape, float *data, float ****dst, int bits, int shift_l);

    void SetLayer(int *shape, char *Wname, float ****dst, int bits, int shift_l);
    void SetLayer(int *shape, char *Wname, float ***dst, int bits, int shift_l);
    void SetLayer(int *shape, char *Wname, float **dst, int bits, int shift_l);
    void SetLayer(int *shape, char *Wname, float *dst, int bits, int shift_l);

    // Layers
    void Reshape(int *shape_src, float **src, int *shape_dst, float ***dst);
    void Reshape(int *shape_src, float ***src, int *shape_dst, float *dst);
    void Reshape(int *shape_src, float ****src, int *shape_dst, float *dst);
    void Conv2d(int *shape_src, float ***src, int *shape_dst, float ***dst, int *kernal_size,
                int *stride, int *padding, float ****weights, float *bias, std::string name);
    void InnerProduct(int *shape_src, float *src, int *shape_dst, float *dst, float **weights,
                      float *bias, int *ndim, std::string name);
    void MaxPool(int *shape_src, float ***src, int *shape_dst, float ***dst, int *ksize, int *stride);
    void ReLU(int *shape, float **data);
    void ReLU(int *shape, float ***data);
    void ReLU(int *shape, float *data);

    void LeakyReLU(int *shape, float *data, float alpha);
    void LeakyReLU(int *shape, float **data, float alpha);
    void LeakyReLU(int *shape, float ***data, float alpha);

    // Fixed Layers
    void FixedConv2d(int *shape_src, float ***src, int *shape_dst, float ***dst, int *kernal_size,
                int *stride, int *padding, float ****weights, float *bias, int bits, std::string name);
    void FixedInnerProduct(int *shape_src, float *src, int *shape_dst, float *dst, float **weights,
                      float *bias, int *ndim, int bits, std::string name);

    // Dump Activation
    static void DumpActivation(int *shape, char *fname, int ****data);
    void DumpActivation(int *shape, char *fname, float ***data);
    void DumpActivation(int *shape, char *fname, float *data);

    // Dump Weights
    void DumpWeights(int *shape, char *fname, float *data);
    void DumpWeights(int *shape, char *fname, float **data);
    void DumpWeights(int *shape, char *fname, float ****data);

    // Pruning
    float Pruning(float *data, float d_th, int shape[], const char *name);
    float Pruning(float **data, float d_th, int shape[], const char *name);
    float Pruning(float ***data, float d_th, int shape[], const char *name);
    float Pruning(float ****data, float d_th, int shape[], const char *name);

    // Transpose
    void Transpose3D(int shape_src[], float ***src, int shape_dst[], float ***dst, int cfg[]);

    // GPU forward section
    void Conv2d_GPU(int *shape_src, float ***src, int *shape_dst, float ***dst, int *kernal_size,
                    int *stride, int *padding, float ****weights, float *bias, const std::string name);
    void InnerProduct_GPU(int *shape_src, float *src, int *shape_dst, float *dst, float **weights,
                      float *bias, int *ndim, std::string name);

    // Math
    void Softmax(int *shape, float *data);

    void L2norm(int *shape, float ***data, int axis);

    void Channel_to_last(int *shape_src, float ***src, int *shape_dst, float ***dst);

    void pad2d(int *shape_src, float ***src, int *shape_dst, float ***dst, int *padding, int format);

private:
    void Transpose3D_201(int shape_src[], float ***src, int shape_dst[], float ***dst);


};


#endif //FORWARD_NETWORK_H

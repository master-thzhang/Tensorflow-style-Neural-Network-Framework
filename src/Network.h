
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

    void SetLayer(const int *shape, char *Wname, float ****dst, int bits, int shift_l);
    void SetLayer(const int *shape, char *Wname, float ***dst, int bits, int shift_l);
    void SetLayer(const int *shape, char *Wname, float **dst, int bits, int shift_l);
    void SetLayer(const int *shape, char *Wname, float *dst, int bits, int shift_l);

    // Layers
    void Reshape(const int *shape_src, float **src, const int *shape_dst, float ***dst);
    void Reshape(const int *shape_src, float ***src, const int *shape_dst, float *dst);
    void Conv2d(const int *shape_src, float ***src, const int *shape_dst, float ***dst, const int *kernal_size,
                const int *stride, const int *padding, float ****weights, const float *bias, std::string name);
    void InnerProduct(const int *shape_src, float *src, const int *shape_dst, float *dst, float **weights,
                      const float *bias, const int *ndim, std::string name);
    void MaxPool(const int *shape_src, float ***src, const int *shape_dst, float ***dst, const int *ksize, const int *stride);
    void ReLU(const int *shape, float **data);
    void ReLU(const int *shape, float ***data);
    void ReLU(const int *shape, float *data);

    void LeakyReLU(const int *shape, float *data, float alpha);
    void LeakyReLU(const int *shape, float **data, float alpha);
    void LeakyReLU(const int *shape, float ***data, float alpha);

    // Fixed Layers
    void FixedConv2d(const int *shape_src, float ***src, const int *shape_dst, float ***dst, const int *kernal_size,
                const int *stride, const int *padding, float ****weights, const float *bias, int bits, std::string name);
    void FixedInnerProduct(const int *shape_src, float *src, const int *shape_dst, float *dst, float **weights,
                      const float *bias, const int *ndim, int bits, std::string name);

    // Dump Activation
    void DumpActivation(const int *shape, char *fname, float ***data);
    void DumpActivation(const int *shape, char *fname, float *data);

    // Dump Weights
    void DumpWeights(const int *shape, char *fname, float *data);
    void DumpWeights(const int *shape, char *fname, float **data);
    void DumpWeights(const int *shape, char *fname, float ****data);

    // Pruning
    float Pruning(float *data, float d_th, const int shape[], const char *name);
    float Pruning(float **data, float d_th, const int shape[], const char *name);
    float Pruning(float ***data, float d_th, const int shape[], const char *name);
    float Pruning(float ****data, float d_th, const int shape[], const char *name);

    // Transpose
    void Transpose3D(const int shape_src[], float ***src, const int shape_dst[], float ***dst, int cfg[]);

private:
    void Transpose3D_201(const int shape_src[], float ***src, const int shape_dst[], float ***dst);


};


#endif //FORWARD_NETWORK_H

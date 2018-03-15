
#ifndef FORWARD_NETWORK_H
#define FORWARD_NETWORK_H


class Network {
public:
    Network();
    // Allocator
    void AllocateMem(double *****src, const int *shape);
    void AllocateMem(double ****src, const int *shape);
    void AllocateMem(double ***src, const int *shape);
    void AllocateMem(double **src, const int *shape);
    // Initialize weights

    void FeedData(const int *shape, double *data, double *dst, int bits, int shift_l);
    void FeedData(const int *shape, double *data, double **dst, int bits, int shift_l);
    void FeedData(const int *shape, double *data, double ***dst, int bits, int shift_l);
    void FeedData(const int *shape, double *data, double ****dst, int bits, int shift_l);

    void SetLayer(const int *shape, char *Wname, double ****dst, int bits, int shift_l);
    void SetLayer(const int *shape, char *Wname, double ***dst, int bits, int shift_l);
    void SetLayer(const int *shape, char *Wname, double **dst, int bits, int shift_l);
    void SetLayer(const int *shape, char *Wname, double *dst, int bits, int shift_l);

    // Layers
    void Reshape(const int *shape_src, double **src, const int *shape_dst, double ***dst);
    void Reshape(const int *shape_src, double ***src, const int *shape_dst, double *dst);
    void Conv2d(const int *shape_src, double ***src, const int *shape_dst, double ***dst, const int *kernal_size,
                const int *stride, const int *padding, double ****weights, const double *bias, std::string name);
    void InnerProduct(const int *shape_src, double *src, const int *shape_dst, double *dst, double **weights,
                      const double *bias, const int *ndim, std::string name);
    void MaxPool(const int *shape_src, double ***src, const int *shape_dst, double ***dst, const int *ksize, const int *stride);
    void ReLU(const int *shape, double **data);
    void ReLU(const int *shape, double ***data);
    void ReLU(const int *shape, double *data);

    void LeakyReLU(const int *shape, double *data, double alpha);
    void LeakyReLU(const int *shape, double **data, double alpha);
    void LeakyReLU(const int *shape, double ***data, double alpha);

    // Fixed Layers
    void FixedConv2d(const int *shape_src, double ***src, const int *shape_dst, double ***dst, const int *kernal_size,
                const int *stride, const int *padding, double ****weights, const double *bias, int bits, std::string name);
    void FixedInnerProduct(const int *shape_src, double *src, const int *shape_dst, double *dst, double **weights,
                      const double *bias, const int *ndim, int bits, std::string name);

    // Dump Activation
    void DumpActivation(const int *shape, char *fname, double ***data);
    void DumpActivation(const int *shape, char *fname, double *data);

    // Dump Weights
    void DumpWeights(const int *shape, char *fname, double *data);
    void DumpWeights(const int *shape, char *fname, double **data);
    void DumpWeights(const int *shape, char *fname, double ****data);

    // Pruning
    double Pruning(double *data, double d_th, const int shape[], const char *name);
    double Pruning(double **data, double d_th, const int shape[], const char *name);
    double Pruning(double ***data, double d_th, const int shape[], const char *name);
    double Pruning(double ****data, double d_th, const int shape[], const char *name);

    // Transpose
    void Transpose3D(const int shape_src[], double ***src, const int shape_dst[], double ***dst, int cfg[]);

private:
    void Transpose3D_201(const int shape_src[], double ***src, const int shape_dst[], double ***dst);


};


#endif //FORWARD_NETWORK_H

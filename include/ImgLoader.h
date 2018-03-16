//
// Created by demo02 on 18-3-9.
//

#ifndef FORWARD_IMGLOADER_H
#define FORWARD_IMGLOADER_H


class ImgLoader {
public:
    ImgLoader();
    void SetImageSize(int size_w, int size_h, int num_channels);
    void MemAlloc();
    void Imread(char *fname);
    void Imresize(double ratio);
    void ImWrite2txt_RGB();
    void FetchData(int shape[], unsigned char ***data);
    double *data_;
    int size_w_, size_h_, num_channels_;
private:
    void Imresize(int ratio_numerator, int ratio_denumerator);
    void Upsampling(int sample_ratio);
    void Downsampling(int sample_ratio);
};


#endif //FORWARD_IMGLOADER_H

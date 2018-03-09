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
    void ImWrite2txt_RGB();
private:
    float *data_;
    int size_w_, size_h_, num_channels_;
};


#endif //FORWARD_IMGLOADER_H

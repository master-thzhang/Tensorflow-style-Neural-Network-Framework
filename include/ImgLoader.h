//
// Created by demo02 on 18-3-9.
//

#ifndef FORWARD_IMGLOADER_H
#define FORWARD_IMGLOADER_H

#define IMG_U8_BLACK    0
#define IMG_U8_WHITE    1
#define IMG_U8_RED      2
#define IMG_U8_GREEN    3
#define IMG_U8_BLUE     4
#define IMG_U8_YELLO    5
#define IMG_U8_PURPLE   6

#define IMG_U8_NO       7

class ImgLoader {
public:
    ImgLoader();
    ~ImgLoader();
    void SetImageSize(int size_w, int size_h, int num_channels);
    void MemAlloc();
    void Imread(char *fname);
    void ImWrite2txt_RGB();
    void FetchData(int shape[], unsigned char ***data);
    void Imresize(int *shape);
    

    // Draw shape
    void Draw_rectangle(int xmin, int xmax, int ymin, int ymax, int COLOR);

    // Add Label
    void Add_label_from_collection(int xmin, int ymin, int font_size, char ch, int COLOR_FG, int COLOR_BG);


    // Data segment
    float *data_;
    int size_w_, size_h_, num_channels_;
};


#endif //FORWARD_IMGLOADER_H

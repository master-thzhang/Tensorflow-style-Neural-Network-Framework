//
// Created by demo02 on 18-3-9.
//

//#include <cstdlib>
#include "ImgLoader.h"
#include "font.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <csignal>


#include "jpeglib.h"



float absf(float x){
    return x>0? x: -x;
}


ImgLoader::ImgLoader() {
    size_h_ = 0;
    size_w_ = 0;
    num_channels_ = 0;
}

ImgLoader::~ImgLoader() {
    delete [] data_;

}

void ImgLoader::SetImageSize(int size_w, int size_h, int num_channels) {
    size_h_ = size_h;
    size_w_ = size_w;
    num_channels_ = num_channels;
    MemAlloc();
}

void ImgLoader::MemAlloc() {
    long memcnt = size_h_ * size_w_ * num_channels_;
    data_ = (float *) malloc(sizeof(float) * memcnt);
}

void ImgLoader::Imread(char *fname) {
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    JSAMPROW row_pointer[1];
    FILE *infile = fopen(fname, "rb" );
    unsigned long location = 0;
    int i = 0;
    if ( !infile )
    {
        printf("Error opening jpeg file %s\n!", fname);
        //return NULL;
    }
    cinfo.err = jpeg_std_error( &jerr );
    jpeg_create_decompress( &cinfo );
    jpeg_stdio_src( &cinfo, infile );
    jpeg_read_header( &cinfo, TRUE );
    jpeg_start_decompress( &cinfo );
    row_pointer[0] = (unsigned char *)malloc( cinfo.output_width*cinfo.num_components );
    if ((size_w_ != cinfo.image_width) || (size_h_ != cinfo.image_height) || (num_channels_ != cinfo.num_components)){
        if ((size_w_ != 0) && (size_w_ != cinfo.image_width)){
            std::cout << "Warning: JPG width is not the same as default settings." << std::endl;
            size_w_ = cinfo.image_width;
        }
        if ((size_h_ != 0) && (size_h_ != cinfo.image_height)){
            std::cout << "Warning: JPG height is not the same as default settings." << std::endl;
            size_h_ = cinfo.image_height;
        }
        if ((num_channels_ != 0) && (num_channels_ != cinfo.num_components)){
            std::cout << "Warning: JPG channel is not the same as default settings." << std::endl;
            num_channels_ = cinfo.num_components;
        }
        delete [] data_;
        long memcnt = size_h_ * size_w_ * num_channels_;
        data_ = (float *) malloc(sizeof(float) * memcnt);
    }
    while( cinfo.output_scanline < cinfo.image_height )
    {
        jpeg_read_scanlines( &cinfo, row_pointer, 1 );
        for( i=0; i<cinfo.image_width*cinfo.num_components;i++)
            data_[location++] = float(float(row_pointer[0][i]) / 256.);
    }
    jpeg_finish_decompress( &cinfo );
    jpeg_destroy_decompress( &cinfo );
    fclose( infile );
    free( row_pointer[0] );



}

void ImgLoader::ImWrite2txt_RGB() {
#define FP1_W   "../debug/image_consistency_check/ImgLoader/channel1.txt"
#define FP2_W   "../debug/image_consistency_check/ImgLoader/channel2.txt"
#define FP3_W   "../debug/image_consistency_check/ImgLoader/channel3.txt"

    FILE *fp1;
    fp1 = fopen(FP1_W, "w");
    FILE *fp2;
    fp2 = fopen(FP2_W, "w");
    FILE *fp3;
    fp3 = fopen(FP3_W, "w");
    for (long i=0; i<size_w_*size_h_*num_channels_; i++)
        if (i % 3 ==1)
            fprintf(fp1, "%f\n", data_[i]);
        else if (i % 3 == 2)
            fprintf(fp2, "%f\n", data_[i]);
        else
            fprintf(fp3, "%f\n", data_[i]);
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
}


void ImgLoader::FetchData(int *shape, unsigned char ***data) {
    shape[0] = size_h_;
    shape[1] = size_w_;
    shape[2] = num_channels_;
    int cnt = 0;
    for (int i=0; i<size_h_; i++)
        for (int j=0; j<size_w_; j++)
            for (int k=0; k<num_channels_; k++)
                data[i][j][k] = (unsigned char) int(data_[cnt++] * 256);
}


void ImgLoader::Imresize(int *shape) {
// Baseline: 23ms
    float time = 0;

#define TRIES   1
    for (int i2=0; i2<TRIES; i2++){
        float start = clock();
        int new_size_h_ = shape[0];
        int new_size_w_ = shape[1];
        int new_num_channels_ = shape[2];

        float ratio_h = float(new_size_h_) / float(size_h_);
        float ratio_w = float(new_size_w_) / float(size_w_);

        float ratio_h_inverse = 1 / ratio_h;
        float ratio_w_inverse = 1 / ratio_w;

        float *data_new;
        data_new = (float *) malloc(sizeof(float *) * new_size_h_ * new_size_w_ * new_num_channels_);

        long offset1 = num_channels_;
        long offset2 = size_w_ * num_channels_;
        long offset3 = new_size_w_ * new_num_channels_;
        for (int k = 0; k < new_num_channels_; k++) {
            float height_axis = -ratio_h_inverse;
            long id_i = -offset3;
            for (int i = 0; i < new_size_h_; i++) {
                height_axis += ratio_h_inverse;
                float width_axis = -ratio_w_inverse;
                float height_axis_int = int(height_axis);
                float h_0_dis = height_axis - height_axis_int;
                float h_1_dis = height_axis_int + 1 - height_axis;
                id_i += offset3;
                long id = id_i + k - offset1;
                for (int j = 0; j < new_size_w_; j++) {
                    width_axis += ratio_w_inverse;
                    float width_axis_int = int(width_axis);
                    float w_0_dis = width_axis - width_axis_int;
                    float w_1_dis = width_axis_int + 1 - width_axis;
                    long q11_id = int(height_axis) * offset2 + int(width_axis) * offset1 + k;
                    id += offset1;
                    if ((height_axis + 1 >= new_size_h_) || (width_axis + 1 >= new_size_w_))
                        data_new[id] = data_[q11_id];

                    else
                        data_new[id] =
                                (h_0_dis) * (w_0_dis) * data_[q11_id] +
                                (h_0_dis) * (w_1_dis) * data_[q11_id + offset1] +
                                (h_1_dis) * (w_0_dis) * data_[q11_id + offset2] +
                                (h_1_dis) * (w_1_dis) * data_[q11_id + offset1 + offset2];
                }
            }
        }
        delete[] data_;
        size_w_ = new_size_w_;
        size_h_ = new_size_h_;
        num_channels_ = new_num_channels_;
        data_ = (float *) malloc(sizeof(float *) * new_size_h_ * new_size_w_ * new_num_channels_);
        for (int i = 0; i < new_size_h_ * new_size_w_ * num_channels_; i++) {
            if (absf(data_new[i])<1.1)
                data_[i] = data_new[i];
            //std::cout << data_[i] << std::endl;
        }
        delete[] data_new;
        float end = clock();
        time += (end - start) / 1000;
    }
    std::cout << time / TRIES << " ms elapsed for Bilinear Interpolation" << std::endl;

}




void ImgLoader::Draw_rectangle(int xmin, int xmax, int ymin, int ymax, int COLOR) {
    float dat[3];
    if (COLOR==IMG_U8_BLACK){
        dat[0] = 0;
        dat[1] = 0;
        dat[2] = 0;
    }
    else if (COLOR==IMG_U8_BLUE){
        dat[0] = 0;
        dat[1] = 0;
        dat[2] = 1;
    }
    else if (COLOR==IMG_U8_WHITE){
        dat[0] = 1;
        dat[1] = 1;
        dat[2] = 1;
    }
    else if (COLOR==IMG_U8_GREEN){
        dat[0] = 0;
        dat[1] = 1;
        dat[2] = 0;
    }
    else if (COLOR==IMG_U8_PURPLE){
        dat[0] = 1;
        dat[1] = 0;
        dat[2] = 1;
    }
    else if (COLOR==IMG_U8_YELLO){
        dat[0] = 0;
        dat[1] = 1;
        dat[2] = 1;
    }
    else if (COLOR==IMG_U8_RED){
        dat[0] = 1;
        dat[1] = 0;
        dat[2] = 0;
    }
    else{
        std::cerr << "Color not implemented error!" << std::endl;
        exit(1);
    }

    for (int k=0; k<num_channels_; k++){
        for (int i=xmin; i<xmax; i++){
            data_[ymin*size_w_*num_channels_+i*num_channels_+k] = dat[k];
            data_[ymax*size_w_*num_channels_+i*num_channels_+k] = dat[k];
        }
        for (int i=ymin; i<ymax; i++){
            data_[i*size_w_*num_channels_+xmin*num_channels_+k] = dat[k];
            data_[i*size_w_*num_channels_+xmax*num_channels_+k] = dat[k];
        }
    }
}

void ImgLoader::Add_label_from_collection(int xmin, int ymin, int font_size, char ch, int COLOR_FG, int COLOR_BG) {



        for (int i=0; i<FONT_SHAPE_H; i++)
            for (int j=0; j<FONT_SHAPE_W; j++){
                long index_data = (i+xmin) * size_w_ * num_channels_ + (j+ymin) * num_channels_;
                long index_label = i*FONT_SHAPE_W + j;
                int code = 0;
                if ((int(ch) >= 65) && (int(ch) <= 90)){
                    code = font_upper[int(ch)-65][i/(FONT_SHAPE_H/16)] & (1 << (8-j/(FONT_SHAPE_W/8)));
                }
                else {
                    code = font_lower[int(ch)-97][i/(FONT_SHAPE_H/16)] & (1 << (8-j/(FONT_SHAPE_W/8)));
                }
                if (code != 0){
                    if (COLOR_FG==IMG_U8_BLACK){
                        data_[index_data+0] = 0;
                        data_[index_data+1] = 0;
                        data_[index_data+2] = 0;
                    }
                    else if (COLOR_FG==IMG_U8_BLUE){
                        data_[index_data+0] = 0;
                        data_[index_data+1] = 0;
                        data_[index_data+2] = 1;
                    }
                    else if (COLOR_FG==IMG_U8_WHITE){
                        data_[index_data+0] = 1;
                        data_[index_data+1] = 1;
                        data_[index_data+2] = 1;
                    }
                    else if (COLOR_FG==IMG_U8_GREEN){
                        data_[index_data+0] = 0;
                        data_[index_data+1] = 1;
                        data_[index_data+2] = 0;
                    }
                    else if (COLOR_FG==IMG_U8_PURPLE){
                        data_[index_data+0] = 1;
                        data_[index_data+1] = 0;
                        data_[index_data+2] = 1;
                    }
                    else if (COLOR_FG==IMG_U8_YELLO){
                        data_[index_data+0] = 0;
                        data_[index_data+1] = 1;
                        data_[index_data+2] = 1;
                    }
                    else if (COLOR_FG==IMG_U8_RED){
                        data_[index_data+0] = 1;
                        data_[index_data+1] = 0;
                        data_[index_data+2] = 0;
                    }
                }
                else
                 {
                    if (COLOR_BG == IMG_U8_BLACK) {
                        data_[index_data + 0] = 0;
                        data_[index_data + 1] = 0;
                        data_[index_data + 2] = 0;
                    } else if (COLOR_BG == IMG_U8_BLUE) {
                        data_[index_data + 0] = 0;
                        data_[index_data + 1] = 0;
                        data_[index_data + 2] = 1;
                    } else if (COLOR_BG == IMG_U8_WHITE) {
                        data_[index_data + 0] = 1;
                        data_[index_data + 1] = 1;
                        data_[index_data + 2] = 1;
                    } else if (COLOR_BG == IMG_U8_GREEN) {
                        data_[index_data + 0] = 0;
                        data_[index_data + 1] = 1;
                        data_[index_data + 2] = 0;
                    } else if (COLOR_BG == IMG_U8_PURPLE) {
                        data_[index_data + 0] = 1;
                        data_[index_data + 1] = 0;
                        data_[index_data + 2] = 1;
                    } else if (COLOR_BG == IMG_U8_YELLO) {
                        data_[index_data + 0] = 0;
                        data_[index_data + 1] = 1;
                        data_[index_data + 2] = 1;
                    } else if (COLOR_BG == IMG_U8_RED) {
                        data_[index_data + 0] = 1;
                        data_[index_data + 1] = 0;
                        data_[index_data + 2] = 0;
                    }
                }
            }


}


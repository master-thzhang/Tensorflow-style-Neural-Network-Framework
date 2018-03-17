//
// Created by demo02 on 18-3-9.
//

//#include <cstdlib>
#include "ImgLoader.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <csignal>


#include "jpeglib.h"


double absf(double x){
    return x>0? x: -x;
}




ImgLoader::ImgLoader() {
    size_h_ = 0;
    size_w_ = 0;
    num_channels_ = 0;
}

void ImgLoader::SetImageSize(int size_w, int size_h, int num_channels) {
    size_h_ = size_h;
    size_w_ = size_w;
    num_channels_ = num_channels;
    MemAlloc();
}

void ImgLoader::MemAlloc() {
    long memcnt = size_h_ * size_w_ * num_channels_;
    data_ = (double *) malloc(sizeof(double) * memcnt);
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
        data_ = (double *) malloc(sizeof(double) * memcnt);
    }
    while( cinfo.output_scanline < cinfo.image_height )
    {
        jpeg_read_scanlines( &cinfo, row_pointer, 1 );
        for( i=0; i<cinfo.image_width*cinfo.num_components;i++)
            data_[location++] = double(row_pointer[0][i]) / 255.;
    }
    jpeg_finish_decompress( &cinfo );
    jpeg_destroy_decompress( &cinfo );
    free( row_pointer[0] );
    fclose( infile );

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
            fprintf(fp1, "%lf\n", data_[i]);
        else if (i % 3 == 2)
            fprintf(fp2, "%lf\n", data_[i]);
        else
            fprintf(fp3, "%lf\n", data_[i]);
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
                data[i][j][k] = (unsigned char) int(data_[cnt++] * 255);
}

void ImgLoader::Imresize(int *shape) {
    int new_size_h_ = shape[0];
    int new_size_w_ = shape[1];
    int new_num_channels_ = shape[2];

    double ratio_h = double(new_size_h_) / double(size_h_);
    double ratio_w = double(new_size_w_) / double(size_w_);

    double *data_new;
    data_new = (double *) malloc(sizeof(double *) * new_size_h_ * new_size_w_ * new_num_channels_);
    for (int k=0; k<new_num_channels_; k++)
        for (int i=0; i<new_size_h_; i++)
            for (int j=0; j<new_size_w_; j++){
                double height_axis = double(i) / ratio_h;
                double width_axis = double(j) / ratio_w;
                int q11_id = int(height_axis) * size_w_ * num_channels_ + int(width_axis) * num_channels_ + k;
                int q12_id = int(height_axis) * size_w_ * num_channels_ + int(width_axis+1) * num_channels_ + k;
                int q21_id = int(height_axis+1) * size_w_ * num_channels_ + int(width_axis) * num_channels_ + k;
                int q22_id = int(height_axis+1) * size_w_ * num_channels_ + int(width_axis+1) * num_channels_ + k;
                int id = i*new_size_w_*new_num_channels_ + j*new_num_channels_ + k;
                data_new[id] = (height_axis-int(height_axis))*(width_axis-int(width_axis)) * data_[q11_id] +
                        (height_axis-int(height_axis))*(int(width_axis) + 1 - width_axis) * data_[q12_id] +
                        (int(height_axis)+1-height_axis)*(width_axis-int(width_axis)) * data_[q21_id] +
                        (int(height_axis)+1-height_axis)*(int(width_axis) + 1 - width_axis) * data_[q21_id];
            }
    delete [] data_;
    size_w_ = new_size_w_;
    size_h_ = new_size_h_;
    num_channels_ = new_num_channels_;
    data_ = (double *) malloc(sizeof(double *) * new_size_h_ * new_size_w_ * new_num_channels_);
    for (int i=0; i<new_size_h_*new_size_w_*num_channels_; i++)
        data_[i] = data_new[i];
    delete [] data_new;

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
    ImgLoader img_label;
    char fname[19] = "../labels/32_0.jpg";
    fname[10] = char(48+int(ch)/10);
    fname[11] = char(48+int(ch)%10);
    fname[12] = '_';
    fname[13] = char(font_size+48);
    fname[14] = '.';
    fname[15] = 'j';
    fname[16] = 'p';
    fname[17] = 'g';
    fname[18] = '\0';
    img_label.SetImageSize(100, 100, 3);
    img_label.Imread(fname);
    if (img_label.num_channels_ == 1){
        for (int i=0; i<img_label.size_h_; i++)
            for (int j=0; j<img_label.size_w_; j++){
                long index_data = (i+xmin) * size_w_ * num_channels_ + (j+ymin) * num_channels_;
                long index_label = i*img_label.size_w_ + j;
                if (img_label.data_[index_label] < .1){
                    if (COLOR_FG==IMG_U8_BLACK){
                        data_[index_data+0] = 0;
                        data_[index_data+1] = 0;
                        data_[index_data+2] = 0;
                    }
                    else if (COLOR_FG==IMG_U8_BLUE){
                        data_[index_data+0] = 0;
                        data_[index_data+1] = 0;
                        data_[index_data+2] = 1 * img_label.data_[index_label];
                    }
                    else if (COLOR_FG==IMG_U8_WHITE){
                        data_[index_data+0] = 1 * img_label.data_[index_label];
                        data_[index_data+1] = 1 * img_label.data_[index_label];
                        data_[index_data+2] = 1 * img_label.data_[index_label];
                    }
                    else if (COLOR_FG==IMG_U8_GREEN){
                        data_[index_data+0] = 0;
                        data_[index_data+1] = 1 * img_label.data_[index_label];
                        data_[index_data+2] = 0;
                    }
                    else if (COLOR_FG==IMG_U8_PURPLE){
                        data_[index_data+0] = 1 * img_label.data_[index_label];
                        data_[index_data+1] = 0;
                        data_[index_data+2] = 1 * img_label.data_[index_label];
                    }
                    else if (COLOR_FG==IMG_U8_YELLO){
                        data_[index_data+0] = 0;
                        data_[index_data+1] = 1 * img_label.data_[index_label];
                        data_[index_data+2] = 1 * img_label.data_[index_label];
                    }
                    else if (COLOR_FG==IMG_U8_RED){
                        data_[index_data+0] = 1 * img_label.data_[index_label];
                        data_[index_data+1] = 0;
                        data_[index_data+2] = 0;
                    }
                }
                else if (img_label.data_[index_label] > .1) {
                    if (COLOR_BG == IMG_U8_BLACK) {
                        data_[index_data + 0] = 0;
                        data_[index_data + 1] = 0;
                        data_[index_data + 2] = 0;
                    } else if (COLOR_BG == IMG_U8_BLUE) {
                        data_[index_data + 0] = 0;
                        data_[index_data + 1] = 0;
                        data_[index_data + 2] = 1. * img_label.data_[index_label];
                    } else if (COLOR_BG == IMG_U8_WHITE) {
                        data_[index_data + 0] = 1. * img_label.data_[index_label];
                        data_[index_data + 1] = 1. * img_label.data_[index_label];
                        data_[index_data + 2] = 1. * img_label.data_[index_label];
                    } else if (COLOR_BG == IMG_U8_GREEN) {
                        data_[index_data + 0] = 0;
                        data_[index_data + 1] = 1. * img_label.data_[index_label];
                        data_[index_data + 2] = 0;
                    } else if (COLOR_BG == IMG_U8_PURPLE) {
                        data_[index_data + 0] = 1. * img_label.data_[index_label];
                        data_[index_data + 1] = 0;
                        data_[index_data + 2] = 1. * img_label.data_[index_label];
                    } else if (COLOR_BG == IMG_U8_YELLO) {
                        data_[index_data + 0] = 0;
                        data_[index_data + 1] = 1. * img_label.data_[index_label];
                        data_[index_data + 2] = 1. * img_label.data_[index_label];
                    } else if (COLOR_BG == IMG_U8_RED) {
                        data_[index_data + 0] = 1. * img_label.data_[index_label];
                        data_[index_data + 1] = 0;
                        data_[index_data + 2] = 0;
                    }
                }
            }
    }
    else if (img_label.num_channels_ == 3){
        for (int k=0; k<img_label.num_channels_; k++)
            for (int i=0; i<img_label.size_h_; i++)
                for (int j=0; j<img_label.size_w_; j++){
                    long index_data = (i+xmin) * size_w_ * num_channels_ + (j+ymin) * num_channels_ + k;
                    long index_label = i*img_label.size_w_*img_label.num_channels_ + j*img_label.num_channels_+k;
                    data_[index_data] = img_label.data_[index_label];
                }
    }
}


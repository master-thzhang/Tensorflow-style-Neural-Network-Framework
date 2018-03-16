//
// Created by demo02 on 18-3-9.
//

//#include <cstdlib>
#include "ImgLoader.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>


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

void ImgLoader::Imresize(int ratio_numerator, int ratio_denumerator) {
    Upsampling(ratio_numerator);
    Downsampling(ratio_denumerator);
}

void ImgLoader::Imresize(double ratio) {
    int ratio_num = int(ratio*9999);
    int ratio_denum = 1;
    for (int i=1; i<100; i++)
        for (int j=1; j<100; j++)
            if (absf((double(j) / double(i)) - ratio) < absf((double(ratio_num) / double(ratio_denum)) - ratio)){
                ratio_denum = i;
                ratio_num = j;
            }
    std::cout << "Up sampling ratio: " << ratio_num << "  Downsamling ratio: " << ratio_denum << std::endl;
    Imresize(ratio_num, ratio_denum);
}

void ImgLoader::Upsampling(int sample_ratio) {
    double *data_gen;
    data_gen = (double *) malloc(size_h_ * size_w_ * num_channels_ * sample_ratio * sample_ratio * sizeof(double *));
    for (int k=0; k<num_channels_; k++)
        for (int i=0; i<size_h_; i++)
            for (int j=0; j<size_w_; j++)
                for (int d1=0; d1<sample_ratio; d1++)
                    for (int d2=0; d2<sample_ratio; d2++){
                        long index = ((i*sample_ratio+d1)*size_w_*sample_ratio*num_channels_ + (j*sample_ratio+d2) * num_channels_ + k);
                        long index_q11 = (i*size_w_*num_channels_) + (j*num_channels_) + k;
                        long index_q12 = (i*size_w_*num_channels_) + ((j+1)*num_channels_) + k;
                        long index_q21 = ((i+1)*size_w_*num_channels_) + (j*num_channels_) + k;
                        long index_q22 = ((i+1)*size_w_*num_channels_) + ((j+1)*num_channels_) + k;
                        data_gen[index] = double((data_[index_q11] * (sample_ratio-d1) * (sample_ratio-d2)
                                          + data_[index_q12] * (sample_ratio-d1) * d2
                                          + data_[index_q21] * d1 * (sample_ratio-d2)
                                          + data_[index_q22] * d1 * d2) * (1. / double(sample_ratio) / double(sample_ratio)));
                    }
    delete [] data_;
    size_h_ = size_h_ * sample_ratio;
    size_w_ = size_w_ * sample_ratio;
    data_ = (double *) malloc(size_h_ * size_w_ * num_channels_ * sizeof(double *));
    for (int p=0; p<size_h_*size_w_*num_channels_; p++)
        data_[p] = data_gen[p];
    delete [] data_gen;
}

void ImgLoader::Downsampling(int sample_ratio) {
    double *data_gen;
    data_gen = (double *) malloc(size_h_ * size_w_ * num_channels_ / sample_ratio / sample_ratio * sizeof(double *));
    for (int k=0; k<num_channels_; k++)
        for (int i=0; i<size_h_; i++)
            for (int j=0; j<size_w_; j++)
                if ((i % sample_ratio == 0) && (j % sample_ratio == 0)){
                    long index = (i*size_w_*num_channels_/sample_ratio/sample_ratio) + (j*num_channels_/sample_ratio) + k;
                    long index_src = (i*size_w_*num_channels_) + (j*num_channels_) + k;
                    data_gen[index] = data_[index_src];
                }
    delete [] data_;
    size_h_ = size_h_ / sample_ratio;
    size_w_ = size_w_ / sample_ratio;
    data_ = (double *) malloc(size_h_ * size_w_ * num_channels_ * sizeof(double *));
    for (int p=0; p<size_h_*size_w_*num_channels_; p++)
        data_[p] = data_gen[p];
    delete [] data_gen;

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
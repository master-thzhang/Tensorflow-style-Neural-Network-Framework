//
// Created by demo02 on 18-3-9.
//

//#include <cstdlib>
#include "ImgLoader.h"
#include <cstdio>
#include <cstdlib>

#include "jpeglib.h"


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
    while( cinfo.output_scanline < cinfo.image_height )
    {
        jpeg_read_scanlines( &cinfo, row_pointer, 1 );
        for( i=0; i<cinfo.image_width*cinfo.num_components;i++)
            data_[location++] = float(row_pointer[0][i]) / 255.;
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
            fprintf(fp1, "%f\n", data_[i]);
        else if (i % 3 == 2)
            fprintf(fp2, "%f\n", data_[i]);
        else
            fprintf(fp3, "%f\n", data_[i]);
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
}


//
// Created by jsyang on 18-3-8.
//

#include <iostream>
#include <cstring>
#include "src/image_proc.h"
#include "net_def/YOLO&PP/NetYOLO.h"


#define FILENAME    "/home/jsyang/data_yolo/dog.jpg"

#define IN_H        448
#define IN_W        448
#define IN_I        3
#define IN_BIT      32




int image_input[3] = {IN_H, IN_W, IN_I};



int main(){



    ImgLoader img;
    img.SetImageSize(448, 448, 3);
    img.Imread(FILENAME);
    //img.ImWrite2txt_RGB();
    //img.Imresize(0.7);




    NetYOLO net;
    net.SetNet();
    double image_data[IN_H*IN_W*IN_I];
    net.TransImg(image_input, img.data_);
    img.ImWrite2txt_RGB();
    net.FeedInput(image_input, img.data_, IN_BIT, 0);
    net.Forward();
    net.PostProcess();

}
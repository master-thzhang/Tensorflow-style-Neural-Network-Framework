#include <iostream>
#include <cstring>
#include "src/image_proc.h"
#include "net_def/DAC/NetDAC.h"


#define FILE_PATH   "/home/demo02/2018_DAC_Dataset/Dataset/test.txt"

#define IN_H        251
#define IN_W        448
#define IN_I        3
#define IN_BIT      8

//#define PRUNE

#define ActivationWriter

//#define WeightWriter

int image_input[3] = {IN_H, IN_W, IN_I};

int main() {
    NetDAC net;
    net.SetNet();

#ifdef PRUNE
    net.Prune_Weights();
#endif

#ifdef WeightWriter
    net.Weight_Writer();
#endif

    float IOU_avg = 0;
    long case_cnt = 0;
    char fname[255] = FILE_PATH;
    FILE *fp;
    fp = fopen(fname, "r");
    char img_name[255];
    float image_data[IN_H*IN_W*IN_I];
    float bbox_gt[4];
    float bbox_predicted[4];
    while (!feof(fp)){
        fscanf(fp, "%s", img_name);
        std::string img_name_str;
        img_name_str = img_name;
        img_name_str.replace(img_name_str.find("jpg"), 3, "txt");
        img_name_str.replace(img_name_str.find("2018_DAC_Dataset/Dataset"), 24, "Forward/test_cases");
        std::string label_name_str;
        label_name_str = img_name;
        label_name_str.replace(label_name_str.find("jpg"), 3, "txt");
        label_name_str.replace(label_name_str.find("JPEGImages"), 10, "labels");
        char label_name[255];
        strncpy(label_name, label_name_str.c_str(), 255);
        strncpy(img_name, img_name_str.c_str(), 255);
        get_next_batch(img_name, label_name, image_data, bbox_gt, image_input);
        net.FeedInput(image_input, image_data, IN_BIT, 0);
        //net.Forward();
        net.FixedForward();
#ifdef ActivationWriter
        net.Activation_Writer();
#endif
        net.FetchResult(bbox_predicted);

        case_cnt += 1;
        float curr_IOU = net.GetIOU(bbox_gt, bbox_predicted);
        IOU_avg += curr_IOU;
        std::cout << "Current IOU:" << curr_IOU << std::endl;
        if (case_cnt == 1000)
            break;
    }
    std::cout << "Average IOU:" << IOU_avg / case_cnt << std::endl;
    return 0;
}

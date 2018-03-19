//
// Created by jsyang on 18-3-8.
//

#include <iostream>
#include "NetYOLO.h"
#include "YOLO_include.h"
#include "NETNAME_YOLO.h"

#define IMG_H   448
#define IMG_W   448



NetYOLO::NetYOLO() {
    // Allocate memory for pointers
    AllocateMem(&input_data, shape_input);
    AllocateMem(&conv1_1_w, shape_conv1_1);
    AllocateMem(&conv1_1_b, shape_conv1_1_b);
    AllocateMem(&conv1_1_a, shape_act_1_1);
    AllocateMem(&pool1_a,   shape_act_1);
    AllocateMem(&conv2_1_w, shape_conv2_1);
    AllocateMem(&conv2_1_b, shape_conv2_1_b);
    AllocateMem(&conv2_1_a, shape_act_2_1);
    AllocateMem(&pool2_a,   shape_act_2);
    AllocateMem(&conv3_1_w, shape_conv3_1);
    AllocateMem(&conv3_1_b, shape_conv3_1_b);
    AllocateMem(&conv3_1_a, shape_act_3_1);
    AllocateMem(&pool3_a,   shape_act_3);
    AllocateMem(&conv4_1_w, shape_conv4_1);
    AllocateMem(&conv4_1_b, shape_conv4_1_b);
    AllocateMem(&conv4_1_a, shape_act_4_1);
    AllocateMem(&pool4_a,   shape_act_4);
    AllocateMem(&conv5_1_w, shape_conv5_1);
    AllocateMem(&conv5_1_b, shape_conv5_1_b);
    AllocateMem(&conv5_1_a, shape_act_5_1);
    AllocateMem(&pool5_a,   shape_act_5);
    AllocateMem(&conv6_1_w, shape_conv6_1);
    AllocateMem(&conv6_1_b, shape_conv6_1_b);
    AllocateMem(&conv6_1_a, shape_act_6_1);
    AllocateMem(&pool6_a,   shape_act_6);
    AllocateMem(&conv7_1_w, shape_conv7_1);
    AllocateMem(&conv7_1_b, shape_conv7_1_b);
    AllocateMem(&conv7_1_a, shape_act_7_1);
    AllocateMem(&conv7_2_w, shape_conv7_2);
    AllocateMem(&conv7_2_b, shape_conv7_2_b);
    AllocateMem(&conv7_2_a, shape_act_7_2);
    AllocateMem(&conv7_3_w, shape_conv7_3);
    AllocateMem(&conv7_3_b, shape_conv7_3_b);
    AllocateMem(&conv7_3_a, shape_act_7_3);
    AllocateMem(&conv_trans, shape_transpose);
    AllocateMem(&conv_flat, shape_flat);
    AllocateMem(&fc1_w, shape_fc1);
    AllocateMem(&fc1_b, shape_fc1_b);
    AllocateMem(&fc1_a, shape_fc1_a);
    AllocateMem(&fc2_w, shape_fc2);
    AllocateMem(&fc2_b, shape_fc2_b);
    AllocateMem(&fc2_a, shape_fc2_a);
    AllocateMem(&fc3_w, shape_fc3);
    AllocateMem(&fc3_b, shape_fc3_b);
    AllocateMem(&fc3_a, shape_fc3_a);
    //AllocateMem(&predicts, shape_predicts);
    AllocateMem(&p_classes, shape_classes_data);
    AllocateMem(&confidence, shape_confidence_data);
    AllocateMem(&coordinate, shape_coordinate_data);
    AllocateMem(&Probability, shape_Probability);
    AllocateMem(&index, shape_index);
    AllocateMem(&index_coord, shape_index_coord);
    AllocateMem(&max_coordinate, shape_max_coord);
}



void NetYOLO::SetNet() {
    SetLayer(shape_conv1_1,   WEIGHT_FILENAME[0], conv1_1_w, CONV1_1_BIT, CONV1_1_W_SHL);
    SetLayer(shape_conv1_1_b, WEIGHT_FILENAME[1], conv1_1_b, CONV1_1_BIT, CONV1_1_B_SHL);
    SetLayer(shape_conv2_1,   WEIGHT_FILENAME[2], conv2_1_w, CONV2_1_BIT, CONV2_1_W_SHL);
    SetLayer(shape_conv2_1_b, WEIGHT_FILENAME[3], conv2_1_b, CONV2_1_BIT, CONV2_1_B_SHL);
    SetLayer(shape_conv3_1,   WEIGHT_FILENAME[4], conv3_1_w, CONV3_1_BIT, CONV3_1_W_SHL);
    SetLayer(shape_conv3_1_b, WEIGHT_FILENAME[5], conv3_1_b, CONV3_1_BIT, CONV3_1_B_SHL);
    SetLayer(shape_conv4_1,   WEIGHT_FILENAME[6], conv4_1_w, CONV4_1_BIT, CONV4_1_W_SHL);
    SetLayer(shape_conv4_1_b, WEIGHT_FILENAME[7], conv4_1_b, CONV4_1_BIT, CONV4_1_B_SHL);
    SetLayer(shape_conv5_1,   WEIGHT_FILENAME[8], conv5_1_w, CONV5_1_BIT, CONV5_1_W_SHL);
    SetLayer(shape_conv5_1_b, WEIGHT_FILENAME[9], conv5_1_b, CONV5_1_BIT, CONV5_1_B_SHL);
    SetLayer(shape_conv6_1,   WEIGHT_FILENAME[10], conv6_1_w, CONV6_1_BIT, CONV6_1_W_SHL);
    SetLayer(shape_conv6_1_b, WEIGHT_FILENAME[11], conv6_1_b, CONV6_1_BIT, CONV6_1_B_SHL);
    SetLayer(shape_conv7_1,   WEIGHT_FILENAME[12], conv7_1_w, CONV7_1_BIT, CONV7_1_W_SHL);
    SetLayer(shape_conv7_1_b, WEIGHT_FILENAME[13], conv7_1_b, CONV7_1_BIT, CONV7_1_B_SHL);
    SetLayer(shape_conv7_2,   WEIGHT_FILENAME[14], conv7_2_w, CONV7_2_BIT, CONV7_2_W_SHL);
    SetLayer(shape_conv7_2_b, WEIGHT_FILENAME[15], conv7_2_b, CONV7_2_BIT, CONV7_2_B_SHL);
    SetLayer(shape_conv7_3,   WEIGHT_FILENAME[16], conv7_3_w, CONV7_3_BIT, CONV7_3_W_SHL);
    SetLayer(shape_conv7_3_b, WEIGHT_FILENAME[17], conv7_3_b, CONV7_3_BIT, CONV7_3_B_SHL);
    SetLayer(shape_fc1,   WEIGHT_FILENAME[18], fc1_w, FC1_BIT, FC1_W_SHL);
    SetLayer(shape_fc1_b, WEIGHT_FILENAME[19], fc1_b, FC1_BIT, FC1_B_SHL);
    SetLayer(shape_fc2,   WEIGHT_FILENAME[20], fc2_w, FC2_BIT, FC2_W_SHL);
    SetLayer(shape_fc2_b, WEIGHT_FILENAME[21], fc2_b, FC2_BIT, FC2_B_SHL);
    SetLayer(shape_fc3,   WEIGHT_FILENAME[22], fc3_w, FC3_BIT, FC3_W_SHL);
    SetLayer(shape_fc3_b, WEIGHT_FILENAME[23], fc3_b, FC3_BIT, FC3_B_SHL);
}


void NetYOLO::FeedInput(const int *shape, double *data, int bits, int shift_l) {
    FeedData(shape, data, input_data, bits, shift_l);
}


void NetYOLO::Forward() {
    Conv2d(shape_input, input_data, shape_act_1_1, conv1_1_a, shape_conv1_1, stride_conv1_1, pad_conv1_1, conv1_1_w, conv1_1_b, "conv1_1");
    LeakyReLU(shape_act_1_1, conv1_1_a, .1);

    MaxPool(shape_act_1_1, conv1_1_a, shape_act_1, pool1_a, ksize_pool1, stride_pool1);

    Conv2d(shape_act_1, pool1_a, shape_act_2_1, conv2_1_a, shape_conv2_1, stride_conv2_1, pad_conv2_1, conv2_1_w, conv2_1_b, "conv2_1");
    LeakyReLU(shape_act_2_1, conv2_1_a, .1);

     MaxPool(shape_act_2_1, conv2_1_a, shape_act_2, pool2_a, ksize_pool2, stride_pool2);

    Conv2d(shape_act_2, pool2_a, shape_act_3_1, conv3_1_a, shape_conv3_1, stride_conv3_1, pad_conv3_1, conv3_1_w, conv3_1_b, "conv3_1");
    LeakyReLU(shape_act_3_1, conv3_1_a, .1);

    MaxPool(shape_act_3_1, conv3_1_a, shape_act_3, pool3_a, ksize_pool3, stride_pool3);

    Conv2d(shape_act_3, pool3_a, shape_act_4_1, conv4_1_a, shape_conv4_1, stride_conv4_1, pad_conv4_1, conv4_1_w, conv4_1_b, "conv4_1");
    LeakyReLU(shape_act_4_1, conv4_1_a, .1);

    MaxPool(shape_act_4_1, conv4_1_a, shape_act_4, pool4_a, ksize_pool4, stride_pool4);

    Conv2d(shape_act_4, pool4_a, shape_act_5_1, conv5_1_a, shape_conv5_1, stride_conv5_1, pad_conv5_1, conv5_1_w, conv5_1_b, "conv5_1");
    LeakyReLU(shape_act_5_1, conv5_1_a, .1);

    MaxPool(shape_act_5_1, conv5_1_a, shape_act_5, pool5_a, ksize_pool5, stride_pool5);

    Conv2d(shape_act_5, pool5_a, shape_act_6_1, conv6_1_a, shape_conv6_1, stride_conv6_1, pad_conv6_1, conv6_1_w, conv6_1_b, "conv6_1");
    LeakyReLU(shape_act_6_1, conv6_1_a, .1);

    MaxPool(shape_act_6_1, conv6_1_a, shape_act_6, pool6_a, ksize_pool6, stride_pool6);

    Conv2d(shape_act_6, pool6_a, shape_act_7_1, conv7_1_a, shape_conv7_1, stride_conv7_1, pad_conv7_1, conv7_1_w, conv7_1_b, "conv7_1");
    LeakyReLU(shape_act_7_1, conv7_1_a, .1);

    Conv2d(shape_act_7_1, conv7_1_a, shape_act_7_2, conv7_2_a, shape_conv7_2, stride_conv7_2, pad_conv7_2, conv7_2_w, conv7_2_b, "conv7_2");
    LeakyReLU(shape_act_7_2, conv7_2_a, .1);

    Conv2d(shape_act_7_2, conv7_2_a, shape_act_7_3, conv7_3_a, shape_conv7_3, stride_conv7_3, pad_conv7_3, conv7_3_w, conv7_3_b, "conv7_3");
    LeakyReLU(shape_act_7_3, conv7_3_a, .1);

    Transpose3D(shape_act_7_3, conv7_3_a, shape_transpose, conv_trans, transpose_cfg);

    Reshape(shape_transpose, conv_trans, shape_flat, conv_flat);

    InnerProduct(shape_flat, conv_flat, shape_fc1_a, fc1_a, fc1_w, fc1_b, shape_fc1, "fc1");
    LeakyReLU(shape_fc1_a, fc1_a, .1);

    InnerProduct(shape_fc1_a, fc1_a, shape_fc2_a, fc2_a, fc2_w, fc2_b, shape_fc2, "fc2");
    LeakyReLU(shape_fc2_a, fc2_a, .1);

    InnerProduct(shape_fc2_a, fc2_a, shape_fc3_a, fc3_a, fc3_w, fc3_b, shape_fc3, "fc3");
    //printf("1. fc3 is %d \n",fc3_a);
    //LeakyReLU(shape_fc3_a, fc3_a, .1);
}




void NetYOLO::PostProcess() {
    int num = 0;

    Trans1Dto3D(shape_classes, fc3_a, shape_classes_data, p_classes, "classes ");
    Trans1Dto3D(shape_confidence, fc3_a, shape_confidence_data, confidence, "confidence ");
    Trans1Dto3D(shape_coordinate, fc3_a, shape_coordinate_data, coordinate, "coordinate ");
    GetProbability(confidence, p_classes, shape_Probability, Probability);
    GetMax(shape_Probability, Probability, index, num);
    GetMax_Coord(coordinate, index, num, index_coord);
    double **predict_box;
#define  BOXN   5
    predict_box = (double **) malloc(sizeof(double *) * BOXN);
    for (int i=0; i<BOXN; i++)
        predict_box[i] = (double *) malloc(sizeof(double) * BOXN);
    DoNMS(num, index_coord, .4, predict_box, BOXN);
    for (int i=0; i<BOXN; i++){
        std::cout << predict_box[i][0] << " " << predict_box[i][1] << " "
                  << predict_box[i][2] << " " << predict_box[i][3] << " "
                  << "Confidence:" << predict_box[i][4] << " " << "class:" << predict_box[i][5] << std::endl;
    }
#undef BOXN


}




void NetYOLO::TransImg(const int *shape, double *data) {
    for (int i=0; i<shape[0]*shape[1]*shape[2]; i++){
        data[i] = data[i]*2 - 1;
    }
}




void NetYOLO::Trans1Dto3D(const int *shape, double *data, const int *shape_dst, double ***dst, std::string name) {
    int cnt = shape[0];
    for (int d1=0; d1<shape_dst[0]; d1++){
        for (int d2=0; d2<shape_dst[1]; d2++){
            for (int d3=0; d3<shape_dst[2]; d3++){
                dst[d1][d2][d3] = data[cnt];
                cnt += 1;
                //printf("d1 is %d \n", d1);
                //printf("d2 is %d \n", d2);
                //printf("d3 is %d \n", d3);
                //printf("data is %lf \n",dst[d1][d2][d3]);
            }
        }
    }



}


void NetYOLO::GetProbability(double ***data_1,double ***data_2, const int *shape_dst,  double ****dst) {
    //printf("start P  \n");
    for (int d1=0; d1<shape_dst[0]; d1++){
        //printf("d1 is %d \n", d1);
        for (int d2=0; d2<shape_dst[1]; d2++){
            //printf("d2 is %d \n", d2);
            for (int d3=0; d3<shape_dst[2]; d3++){
                //printf("d3 is %d \n", d3);
                for (int d4=0; d4<shape_dst[3]; d4++){
                    //printf("d4 is %d \n", d4);
                    //printf("data_1 is %lf \n", data_1[d1][d2][d3]);
                    //printf("data_2 is %lf \n", data_2[d1][d2][d4]);
                    dst[d1][d2][d3][d4] = data_1[d1][d2][d3]*data_2[d1][d2][d4];
                    //printf("dst is %lf \n", dst[d1][d2][d3][d4]);
                }
            }
        }
    }
}


void NetYOLO::GetMax(const int *shape, double ****data, double **dst, int &num) {
    printf("start Max  \n");
    double prob = .01;
    double index_1 = 0;
    double index_2 = 0;
    double index_3 = 0;
    double index_4 = 0;
    double index_5 = 0;

    for (int d1=0; d1<shape[0]; d1++){
        for (int d2=0; d2<shape[1]; d2++){
            for (int d3=0; d3<shape[2]; d3++){
                double temp = 0;
                for (int d4=0; d4<shape[3]; d4++){
                    if (temp < data[d1][d2][d3][d4]){
                        temp = data[d1][d2][d3][d4];
                        index_1 = d1;
                        index_2 = d2;
                        index_3 = d3;
                        index_4 = d4;
                        index_5 = temp;

                        //printf("max__ is %lf \n",temp);
                        //printf("index0 is %d \n",index_1);
                        //printf("index1 is %d \n",index_2);
                        //printf("index2 is %d \n",index_3);
                        //printf("index3 is %d \n",index_4);
                    }
                }
                if (temp > prob) {
                    dst[num][0] = index_1;
                    dst[num][1] = index_2;
                    dst[num][2] = index_3;
                    dst[num][3] = index_4;
                    dst[num][4] = index_5;
                    printf("number is %d\n", num);
                    printf("max is %lf \n",temp);
                    printf("index0 is %lf \n",dst[num][0]);
                    printf("index1 is %lf \n",dst[num][1]);
                    printf("index2 is %lf \n",dst[num][2]);
                    printf("index3 is %lf \n",dst[num][3]);
                    printf("index4 is %lf \n",dst[num][4]);
                    num += 1;
                }
            }
        }
    }
}


void NetYOLO::GetMax_Coord(double ***coord, double **data, int &num, double **dst) {
    printf("1\n");
    printf("num is %d\n",num);
    int index_1 = 0;
    int index_2 = 0;
    int index_3 = 0;
    double xcenter = 0;
    double ycenter = 0;
    double w = 0;
    double h = 0;
    double xmin = 0;
    double ymin = 0;
    double xmax = 0;
    double ymax = 0;

    for (int number=0; number<num; number++){
        printf("2\n");
        index_1 = int(data[number][0]);
        index_2 = int(data[number][1]);
        index_3 = int(data[number][2]);
        for (int i = 0; i < COORDINATE; i++) {
            printf("confidence is %d\n", index_3);
            max_coordinate[i] = coord[index_1][index_2][index_3*4+i];
            printf("i is %d\n", i);
            printf("coordinate is %lf\n", max_coordinate[i]);
        }

        xcenter = max_coordinate[0];
        ycenter = max_coordinate[1];
        w = max_coordinate[2];
        h = max_coordinate[3];

        xcenter = (index[number][1] + xcenter) * (448 / 7.0);
        ycenter = (index[number][0] + ycenter) * (448 / 7.0);

        w = w * 448;
        h = h * 448;

        xmin = xcenter - w / 2.0;
        ymin = ycenter - h / 2.0;

        xmax = xmin + w;
        ymax = ymin + h;

        dst[number][0] = (xmin>0)?xmin:0;           //xmin
        dst[number][1] = (ymin>0)?ymin:0;           //ymin
        dst[number][2] = (xmax<448)?xmax:448;       //xmax
        dst[number][3] = (ymax<448)?ymax:448;       //ymax
        dst[number][4] = data[number][4];           //prob
        dst[number][5] = data[number][3];           //classes
        printf("xmin is %lf\n",dst[number][0]);
        printf("ymin is %lf\n",dst[number][1]);
        printf("xmax is %lf\n",dst[number][2]);
        printf("ymax is %lf\n",dst[number][3]);
        printf("confidence is %lf\n",dst[number][4]);
        printf("class is %lf\n", dst[number][5]);
        printf("number is %d\n",number);
    }
}



/*
void NetYOLO::draw_box_width(const int *shape, float ***img, int x1, int y1, int x2, int y2, int w, float r, float g,
                             float b) {
    int i;
    for(i = 0; i < w; ++i){
        draw_box(shape, img, x1+i, y1+i, x2-i, y2-i, r, g, b);
    }

}


void NetYOLO::draw_box(const int *shape, float ***img, int x1, int y1, int x2, int y2, float r, float g, float b) {
    int i;
    if(x1 < 0) x1 = 0;
    if(x1 >= shape[0]) x1 = shape[0]-1;   //shape[0] = w  , shape[1] = h  , shape[2] = c
    if(x2 < 0) x2 = 0;
    if(x2 >= shape[0]) x2 = shape[0]-1;

    if(y1 < 0) y1 = 0;
    if(y1 >= shape[1]) y1 = shape[1]-1;
    if(y2 < 0) y2 = 0;
    if(y2 >= shape[1]) y2 = shape[1]-1;

    for(i = x1; i <= x2; ++i){
        img[i][y1][0] = r;
        img[i][y2][0] = r;

        img[i][y1][1] = g;
        img[i][y2][1] = g;

        img[i][y1][0] = b;
        img[i][y2][0] = b;
    }

    for(i = y1; i <= y2; ++i){
        img[x1][i][0] = r;
        img[x2][i][0] = r;

        img[x1][i][1] = g;
        img[x2][i][1] = g;

        img[x1][i][0] = b;
        img[x2][i][0] = b;
    }


}
*/



double NetYOLO::GetIOU(double *bbox_gt, double *bbox_predicted) {
    int bbox_gt_int[4];
    int bbox_predicted_int[4];
    bbox_gt_int[0] = int(bbox_gt[0]);
    bbox_predicted_int[0] = int(bbox_predicted[0]);
    bbox_gt_int[1] = int(bbox_gt[1]);
    bbox_predicted_int[1] = int(bbox_predicted[1]);
    bbox_gt_int[2] = int(bbox_gt[2]);
    bbox_predicted_int[2] = int(bbox_predicted[2]);
    bbox_gt_int[3] = int(bbox_gt[3]);
    bbox_predicted_int[3] = int(bbox_predicted[3]);
    int x1 = std::max(bbox_gt_int[0], bbox_predicted_int[0]);
    int y1 = std::max(bbox_gt_int[1], bbox_predicted_int[1]);
    int x2 = std::min(bbox_gt_int[2], bbox_predicted_int[2]);
    int y2 = std::min(bbox_gt_int[3], bbox_predicted_int[3]);
    std::cout << "bbox gt:" << bbox_gt_int[0] << "\t" << bbox_gt_int[1] << "\t" << bbox_gt_int[2] << "\t" << bbox_gt_int[3] << std::endl;
    std::cout << "bbox predicted:" << bbox_predicted_int[0] << "\t" << bbox_predicted_int[1] << "\t" << bbox_predicted_int[2] << "\t" << bbox_predicted_int[3] << std::endl;
    if ((x1 > x2) || (y1 > y2))
        return 0.0;
    int w = abs(x2 - x1) + 1;
    int h = abs(y2 - y1) + 1;
    int inter = w * h;
    int aarea = (abs(bbox_gt_int[2] - bbox_gt_int[0]) + 1) * (abs(bbox_gt_int[3] - bbox_gt_int[1]) + 1);
    int barea = (abs(bbox_predicted_int[2] - bbox_predicted_int[0]) + 1) * (abs(bbox_predicted_int[3] - bbox_predicted_int[1]) + 1);
    return (double) (inter + 0.0) / (aarea + barea - inter + 0.0);
}

void NetYOLO::DoNMS(int num, double **array, double thresh, double **dst, int dst_size){
    // Array is stored in [7x7x2, 5] format.
    if (num>MAXBOX)
        std::cerr << "Too many proposals! Stopping..." << std::endl;

    for (int i=0; i<num-1; i++)
        for (int j=i+1; j<num; j++)
            if (array[i][4] < array[j][4])
            for (int k=0; k<6; k++){
                    double tmp = array[i][k];
                    array[i][k] = array[j][k];
                    array[j][k] = tmp;
            }

    bool *vi;
    vi = (bool *) malloc(sizeof(bool) * num);

    for (int i=0; i<MAXBOX; i++)
        vi[i] = true;

    for (int i=0; i<num-1; i++)
        for (int j=i+1; j<num; j++){
            if (vi[j]){
                double bbox1[4];
                double bbox2[4];
                bbox1[0] = int(array[i][0]);
                bbox1[1] = int(array[i][1]);
                bbox1[2] = int(array[i][2]);
                bbox1[3] = int(array[i][3]);
                bbox2[0] = int(array[j][0]);
                bbox2[1] = int(array[j][1]);
                bbox2[2] = int(array[j][2]);
                bbox2[3] = int(array[j][3]);
                double result = GetIOU(bbox1, bbox2);
                if (result > thresh){
                    vi[j] = false;
                }
            }
        }
    int cnt = 0;
    for (int i=0; i<num; i++){
        if (vi[i]){
            for (int j=0; j<6; j++){
                dst[cnt][j] = array[i][j];
            }
            cnt ++;
            if (cnt == dst_size)
                return;
        }
    }
}
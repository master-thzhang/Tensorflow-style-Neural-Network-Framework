//
// Created by jsyang on 18-3-8.
//

#ifndef FORWARD_NETYOLO_H
#define FORWARD_NETYOLO_H

#include "../../include/Network.h"
#include "../../include/ImgLoader.h"

#define MAXBOX 1000


class NetYOLO:Network {
public:
    NetYOLO();
    void SetNet();
    void FeedInput(const int *shape, double *data, int bits, int shift_l);
    void TransImg(const int *shape, double *data);
    //void FetchResult(double *dst);


    // Forward
    void Forward();
    void PostProcess();
    //void FixedForward();
    // Pruning
    //void Prune_Weights();
    // Weight writer
    //void Weight_Writer();
    // Activation Writer
    //void Activation_Writer();
    // IOU Calc
    //double GetIOU(double *bbox_gt, double *bbox_predicted);


    //Post Process
    void Trans1Dto3D(const int *shape, double *data, const int *shape_dst, double ***dst, std::string name);
    //void DividePredicts(const int *shape, double ***data, const int *shape_dst, double ***dst, std::string name);
    void GetProbability(double ***data_1, double ***data_2, const int *shape_dst,double ****dst);
    void GetMax(const int *shape, double ****data, double **dst, int &num);
    void GetMax_Coord(double ***coord, double **data, int &num, double **dst);


    double GetIOU(double *bbox_gt, double *bbox_predicted);
    void DoNMS(int num, double **array, double thresh, double **dst, int dst_size);

    //Image Process
    //void draw_box_width(const int *shape, float ***img, int x1, int y1, int x2, int y2, int w, float r, float g, float b);
    //void draw_box(const int *shape, float ***img, int x1, int y1, int x2, int y2, float r, float g, float b);


private:
    // w=weights, b=bias, a=activation
    double ***input_data;
    double ****conv1_1_w;
    double *conv1_1_b;
    double ***conv1_1_a;;

    double ***pool1_a;

    double ****conv2_1_w;
    double *conv2_1_b;
    double ***conv2_1_a;;

    double ***pool2_a;

    double ****conv3_1_w;
    double *conv3_1_b;
    double ***conv3_1_a;;

    double ***pool3_a;

    double ****conv4_1_w;
    double *conv4_1_b;
    double ***conv4_1_a;;

    double ***pool4_a;

    double ****conv5_1_w;
    double *conv5_1_b;
    double ***conv5_1_a;;

    double ***pool5_a;

    double ****conv6_1_w;
    double *conv6_1_b;
    double ***conv6_1_a;;

    double ***pool6_a;


    double ****conv7_1_w;
    double *conv7_1_b;
    double ***conv7_1_a;
    double ****conv7_2_w;
    double *conv7_2_b;
    double ***conv7_2_a;
    double ****conv7_3_w;
    double *conv7_3_b;
    double ***conv7_3_a;

    double ***conv_trans;

    double *conv_flat;

    double *fc1_a;
    double **fc1_w;
    double *fc1_b;


    double *fc2_a;
    double **fc2_w;
    double *fc2_b;

    double *fc3_a;
    double **fc3_w;
    double *fc3_b;


    //double ***predicts;
    double ***p_classes;
    double ***confidence;
    double ***coordinate;

    double ****Probability;

    double **index;
    double **index_coord;
    double *max_coordinate;

};








#endif //FORWARD_NETYOLO_H

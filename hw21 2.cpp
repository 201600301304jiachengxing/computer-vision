//
// Created by apple on 2018/9/19.
//
#include <iostream>
#include <opencv2/opencv.hpp>
#include <math.h>

using namespace std;
using namespace cv;

int ave;
int bve = 32;

int main(){
    Mat img = imread("/Users/apple/Desktop/aaa.jpg");
    Mat nimg = Mat::zeros(img.size(),img.type());

    float mean[3];
    cv:Scalar tempVal = cv::mean(img);
    mean[0] = tempVal.val[0];
    mean[1] = tempVal.val[1];
    mean[2] = tempVal.val[2];
    //img.convertTo(img,CV_32FC3);
    for(int y=0;y<img.rows;y++)
        for(int x=0;x<img.cols;x++)
            for(int c=0;c<3;c++){
                ave = mean[c]/8;
                //nimg.at<Vec3b>(y,x)[c] = img.at<Vec3b>(y,x)[c];
                nimg.at<Vec3b>(y,x)[c] = 255/(1+exp((-img.at<Vec3b>(y,x)[c]-ave)/bve));
            }

     imshow("out",nimg);
     waitKey(0);
     imwrite("/Users/apple/Desktop/aaa2.jpg",nimg);

}


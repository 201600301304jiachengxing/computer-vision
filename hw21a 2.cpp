//
// Created by apple on 2018/9/20.
//

#include<opencv2/opencv.hpp>
#include <iostream>
#include<opencv2/core.hpp>
#include <cmath>

using namespace std;
using namespace cv;

void  on_Constract(int, void *);

Mat bmg0,img0;
int avr = 40;
int bvr = 4096;

int main() {
    img0 = imread("/Users/apple/Desktop/abc.jpg");
    img0.copyTo(bmg0);

    namedWindow("slider");
    createTrackbar("avr：", "slider", &avr, 145, on_Constract);
    setTrackbarMin("avr", "slider", 1);//设置滑块的最小值
    setTrackbarMax("avr", "slider", 145);//设置滑块的最大值
    createTrackbar("bvr","slider",&bvr, 8192, on_Constract);
    setTrackbarMin("bvr", "slider", 1024);//设置滑块的最小值
    setTrackbarMax("bvr", "slider", 8192);//设置滑块的最大值

    while (char(waitKey(1) != 'q'));
    return 0;
}

void  on_Constract(int, void *) {

    for (int i = 0; i < img0.rows; i++) {
        for (int j = 0; j < img0.cols; j++) {
            for (int c = 0; c < 3; c++)
            bmg0.at<Vec3b>(i, j)[c] = saturate_cast<uchar>(255/(1+exp(-(avr*img0.at<Vec3b>(i, j)[c] )/bvr)));
        }
    }
    imshow("slider", bmg0);
}
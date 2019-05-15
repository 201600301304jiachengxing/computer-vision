//
// Created by apple on 2018/10/30.
//

#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include <cmath>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

#pragma comment(lib,"opencv_core2410d.lib")
#pragma comment(lib,"opencv_highgui2410d.lib")
#pragma comment(lib,"opencv_imgproc2410d.lib")

using namespace std;
using namespace cv;

int main71()
{
    Mat input = cv::imread("/Users/apple/Desktop/f.jpg");
    Mat output(input.size(),CV_8U);
    int pos=50;
    if (input.empty())
        return -1;
    cvtColor(input, input, CV_BGR2GRAY);
    Canny(input,output,pos,pos*2,3);
    imshow("out",output);
    imwrite("/Users/apple/Desktop/f0.jpg",output);
    waitKey(0); //等待按键
    return 0;
}
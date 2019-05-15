//
// Created by apple on 2018/10/24.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include <cmath>
#include <string>

using namespace std;
using namespace cv;

int main(){
    Mat input=imread("/Users/apple/Desktop/timg.jpg");
    cvtColor(input,input,CV_BGR2GRAY);
    threshold(input,input,128,255,THRESH_BINARY);
    Mat output;

    distanceTransform(input,output,CV_DIST_L12,CV_DIST_MASK_PRECISE);
    normalize(output,output,0,1,cv::NORM_MINMAX);
    imshow("out",output);
    //imwrite("/Users/apple/Desktop/a1.png",output);
    waitKey(0);
}





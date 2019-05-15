#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
int main() {
    Mat fImage1 = imread("/Users/apple/Desktop/a.png");
    Mat bImage = imread("/Users/apple/Desktop/ppp.png");
    Mat alpha = imread("/Users/apple/Desktop/a.png");
    Mat outImage = Mat::zeros(fImage1.size(), fImage1.type()); //输出图像

    //输出图像预处理
    resize(bImage,bImage,fImage1.size());
    fImage1.convertTo(fImage1,CV_32FC3);
    bImage.convertTo(bImage,CV_32FC3);
    alpha.convertTo(alpha,CV_32FC3,1.0/255);

    multiply(alpha,fImage1,fImage1); //in1*alpha
    multiply(Scalar::all(1.0)-alpha,bImage,bImage); //in2*alpha
    add(fImage1,bImage,outImage);
    imshow("out",outImage/255);
    waitKey(0);
    imwrite("/Users/apple/Desktop/ppp1.png",outImage);
    return 0;
}
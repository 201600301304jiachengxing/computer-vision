#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
int main() {
    Mat fImage1 = imread("/Users/apple/Desktop/a.png");
    Mat bImage = imread("/Users/apple/Desktop/ppp.png");
    Mat fImage = Mat::zeros(fImage1.size(), fImage1.type());
    Mat outImage = Mat::zeros(fImage1.size(), fImage1.type()); //输出图像

    //输出图像预处理
    resize(bImage,bImage,fImage1.size());

    //alpha通道提取
    vector<Mat> channel; //储存各个通道
    split(fImage1,channel);
    Mat alpha = channel.at(3); //前三个为色彩通道，第四个为alpha通道
    imshow("alpha",alpha);
    cvWaitKey(0);
    imwrite("/Users/apple/Desktop/alpha.jpg",alpha);

    //alpha混合，out=alpha*in1+（1-alpha）*in2
    channel.pop_back();
    merge(channel,fImage);
    fImage1.convertTo(fImage1,CV_32FC3);
    bImage.convertTo(bImage,CV_32FC3);
    alpha.convertTo(alpha,CV_32FC3,2.0/255);

    //alpha混合
    vector<Mat> alchan;
    alchan.push_back(alpha);
    alchan.push_back(alpha);
    alchan.push_back(alpha);
    merge(alchan,alpha);

    multiply(alpha,fImage,fImage); //in1*alpha
    multiply(Scalar::all(1.0)-alpha,bImage,bImage); //in2*(1-alpha)
    add(fImage,bImage,outImage);
    imshow("out",outImage);
    waitKey(0);
    imwrite("/Users/apple/Desktop/ppp2.png",outImage);
    return 0;
}
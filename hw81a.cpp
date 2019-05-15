//
// Created by apple on 2018/11/14.
//

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <cmath>
using namespace cv;
using namespace std;

int main81()
{
    const Mat srcImage = imread("/Users/apple/Desktop/12.jpg");
    if (!srcImage.data)
    {
        printf("could not load image...\n");
        return -1;
    }

    Mat srcGray;
    Mat imageSobelX;
    Mat imageSobelY;

    //灰度图
    cvtColor(srcImage,srcGray,CV_BGR2GRAY);
    //梯度
    Sobel(srcGray,imageSobelX,srcImage.depth(),1,0,3);
    Sobel(srcGray,imageSobelY,srcImage.depth(),0,1,3);

    Mat imageXX = Mat(srcGray.size(), CV_64F);
    Mat imageYY = Mat(srcGray.size(), CV_64F);
    Mat imageXY = Mat(srcGray.size(), CV_64F);
    Mat harris0 = Mat(srcGray.size(), CV_64F);

    //计算各方向的梯度的平方与乘积
    for(int i=0;i<srcGray.rows;i++)
    {
        for(int j=0;j<srcGray.cols;j++)
        {
            double XX = imageSobelX.at<uchar>(i, j) * imageSobelX.at<uchar>(i, j);
            double YY = imageSobelY.at<uchar>(i, j) * imageSobelY.at<uchar>(i, j);
            double XY = imageSobelX.at<uchar>(i, j) * imageSobelY.at<uchar>(i, j);
            imageXX.at<double>(i,j) = XX;
            imageYY.at<double>(i,j) = YY;
            imageXY.at<double>(i,j) = XY;
            //cout<<(float)imageXX.at<double>(i,j)<<" "<<(float)imageSobelX.at<uchar>(i,j)<<" "<<XX<<endl;
        }
    }

    //高斯滤波XX YY XY
    GaussianBlur(imageXX, imageXX, Size(7,7), 0, 0);
    GaussianBlur(imageYY, imageYY, Size(7,7), 0, 0);
    GaussianBlur(imageXY, imageXY, Size(7,7), 0, 0);

    //取alpha参数为0.04
    double k = 0.04;
    for (int i=0;i<harris0.rows;i++){
        for (int j=0;j<harris0.cols;j++){
            double a = imageXX.at<double>(i, j);
            double b = imageYY.at<double>(i, j);
            double c = imageXY.at<double>(i, j);
            double r = abs(a*b - c*c - k*(a + b)*(a + b));
            harris0.at<double>(i, j) = r;
        }
    }
    int t = 8e+7;
    int r = 5;
    for (int i = r; i < srcGray.rows - r; i++)
    {
        for (int j = r; j < srcGray.cols - r; j++)
        {
            int flag = 1;
            if((int)harris0.at<double>(i, j) > t){
                for(int y = i - r;y < i + r; y++){
                    for(int x = j - r;x < j + r; x++){
                        if (harris0.at<double>(i, j) < harris0.at<double>(y, x)){
                            flag = 0;
                        }
                    }
                }
                if (flag == 1){
                    circle(srcImage, Point(j, i), 3, Scalar(0,0,255), 2, 2, 0);
                }
            }
        }
    }
    imshow("Result", srcImage);
    imwrite("/Users/apple/Desktop/2ak.jpg",srcImage);
    waitKey(0);
    return 0;
}
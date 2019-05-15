//
// Created by apple on 2018/11/1.
//

#include <opencv2/opencv.hpp>
#include <math.h>
#include <iostream>

using namespace std;
using namespace cv;

int thresh = 130;
int max_count = 255;
Mat img, img_gray;
const char* output_title = "Harris Corner Dectction Result";
void Harris_Demo(int, void *);

int main(int argv, char** argc) {
    img = imread("/Users/apple/Desktop/13.jpg");
    if (img.empty()) {
        printf("colud not load image...");
        return -1;
    }
    namedWindow("input image", CV_WINDOW_AUTOSIZE);
    imshow("input image", img);
    //以上是图像处理的标准开头
    namedWindow(output_title, CV_WINDOW_AUTOSIZE);
    cvtColor(img, img_gray, CV_BGR2GRAY);

    createTrackbar("Threshold", output_title, &thresh, max_count, Harris_Demo);
    Harris_Demo(0, 0);

    waitKey(0);
    return 0;
}

void Harris_Demo(int, void *) {

    Mat dst, norm_dst, normScaleDst;
    dst = Mat::zeros(img_gray.size(), CV_32FC1);
    //harris角点核心函数
    int blockSize = 2;
    int ksize = 3;
    int k = 0.04;

    cornerHarris(img_gray, dst, blockSize, ksize, k, BORDER_DEFAULT);
    //上述输出的取值范围并不是0-255 需要按照最大最小值进行归一化
    normalize(dst, norm_dst, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
    convertScaleAbs(norm_dst, normScaleDst);

    Mat resultImg = img.clone();
    //用彩色来显示
    for (int row = 0; row < resultImg.rows; row++) {
        //定义每一行的指针
        uchar* currentRow = normScaleDst.ptr(row);
        for (int col = 0; col < resultImg.cols; col++) {
            int value = (int)*currentRow;
            if (value > thresh) {
                circle(resultImg, Point(col, row), 2, Scalar(0, 0, 255), 2, 8, 0);
            }
            currentRow++;
        }
    }
    imshow(output_title, resultImg);
}
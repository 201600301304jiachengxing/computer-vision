//
// Created by apple on 2018/9/20.
//

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(){
    Mat fm0 = imread("/Users/apple/Desktop/h1.png");
    Mat bm0 = imread("/Users/apple/Desktop/h2.png");
    Mat imga = Mat::zeros(fm0.size(),fm0.type());

    for(int y=0;y<fm0.rows;y++)
        for(int x=0;x<fm0.cols;x++)
            for(int c=0;c<3;c++){
                imga.at<Vec3b>(y,x)[c]=abs(fm0.at<Vec3b>(y,x)[c]-bm0.at<Vec3b>(y,x)[c]);
            }
    cvtColor(imga,imga,CV_BGR2GRAY);
    threshold(imga,imga,32,255,THRESH_BINARY);

    Mat imgb = imga;
    int sum = 0;
    int conv[5][5] = {{1,4,16,4,1},{4,16,32,16,4},{16,32,64,32,16},{4,16,32,16,4},{1,4,16,4,1}};
    int csum = 0;
    for(int i=0;i<5;i++) {
        for(int j=0;j<5;j++) {
            csum = csum + conv[i][j];
        }
    }

    for(int y=2;y<fm0.rows-2;y++) {
        for(int x=2;x<fm0.cols-2;x++) {
            sum = 0;
            for(int i=y-2;i<=y+2;i++){
                for(int j=x-2;j<=x+2;j++) {
                    sum = sum + conv[i+2-y][j+2-x]*imga.at<uchar>(i,j);
                }
            }
            imgb.at<uchar>(y,x) = 255*((sum/csum)>96?1:0);
        }
    }
    //imshow("out",imgb);
    //waitKey(0);
    //imwrite("/Users/apple/Desktop/hp.png",imgb);

    Mat imgc = imga;
    int conv_h[9] = {1,4,16,32,64,32,16,4,1};
    sum = 0;
    int csum_h = 0;
    for(int i=0;i<9;i++) {
        csum_h = csum_h + conv_h[i];
    }

    for(int y=0;y<fm0.rows;y++) {
        for(int x=8;x<fm0.cols-8;x++) {
            sum = 0;
            for(int i=y-4;i<y+4;i++){
                sum = sum + conv_h[i+4-y]*imga.at<uchar>(i,x);
            }
            imgc.at<uchar>(y,x) = 255*((sum/csum_h)>128?1:0);
        }
    }
    //imshow("out",imgc);
    //waitKey(0);
    //imwrite("/Users/apple/Desktop/hp1.png",imgc);

    Mat imgd = imga;
    for(int y=0;y<fm0.rows;y++) {
        for(int x=0;x<fm0.cols;x++) {
            imgd.at<uchar>(y,x) = 255*((imga.at<uchar>(y,x)+imgb.at<uchar>(y,x)+imgc.at<uchar>(y,x))>=255?1:0);
        }
    }

    imshow("out",imgd);
    waitKey(0);
    imwrite("/Users/apple/Desktop/hp2.png",imgd);

}
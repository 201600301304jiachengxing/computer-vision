//
// Created by apple on 2018/9/19.
//

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


int main(){
    Mat fm = imread("/Users/apple/Desktop/h1.png");
    Mat bm = imread("/Users/apple/Desktop/h2.png");
    Mat img = Mat::zeros(fm.size(),fm.type());
    //resize(bm,bm,fm.size());

    //float mean[3];
    //cv:Scalar tempVal = cv::mean(bm);
    //mean[0] = tempVal.val[0];
    //mean[1] = tempVal.val[1];
    //mean[2] = tempVal.val[2];
    //cout<<mean[0]<<endl;
    //cout<<mean[1]<<endl;
    //cout<<mean[2]<<endl;

    for(int y=0;y<fm.rows;y++)
        for(int x=0;x<fm.cols;x++)
            for(int c=0;c<3;c++){
                img.at<Vec3b>(y,x)[c]=abs(fm.at<Vec3b>(y,x)[c]-bm.at<Vec3b>(y,x)[c]);
            }
    cvtColor(img,img,CV_BGR2GRAY);
    threshold(img,img,32,255,THRESH_BINARY);
    imshow("out",img);
    waitKey(0);
    imwrite("/Users/apple/Desktop/h.png",img);

}
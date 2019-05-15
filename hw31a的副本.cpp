//
// Created by apple on 2018/9/26.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include <cmath>

using namespace std;
using namespace cv;

Mat in_image;

void WarpAffine1(const float t[2][3]){
    if (t[0][0]*t[1][1]-t[0][1]*t[1][0]==0.0){
        return;
    }
    //定位并确定新图像大小
    int bor_y[4];
    int bor_x[4];
    int point[4][2] = {{0,0},{0,in_image.cols},{in_image.rows,0},{in_image.rows,in_image.cols}};
    for(int k=0;k<4;k++){
        bor_x[k] = point[k][1]*t[0][0]+point[k][0]*t[0][1]+t[0][2];//x
        bor_y[k] = point[k][1]*t[1][0]+point[k][0]*t[1][1]+t[1][2];//y
    }
    int maxy=bor_x[0];
    int maxx=bor_x[0];
    int miny=bor_y[0];
    int minx=bor_y[0];
    for(int k=1;k<4;k++){
        if (bor_y[k]>maxy){
            maxy=bor_y[k];
        }
        if (bor_y[k]<miny){
            miny=bor_y[k];
        }
        if (bor_x[k]>maxx){
            maxx=bor_x[k];
        }
        if (bor_x[k]<minx){
            minx=bor_x[k];
        }
    }

    Mat out_image = Mat::zeros(Size((maxx-minx+1),(maxy-miny+1)),in_image.type());

    //双线性插值
    for(int y=0;y<out_image.rows;y++){
        for(int x=0;x<out_image.cols;x++){
            for(int k=0;k<3;k++){
                float y1 = y + miny + 1;
                float x1 = x + minx + 1;
                float real_y = (t[1][0]*(x1-t[0][2])-t[0][0]*(y1-t[1][2]))/(t[0][1]*t[1][0]-t[0][0]*t[1][1]);
                float real_x = (t[0][1]*(y1-t[1][2])-t[1][1]*(x1-t[0][2]))/(t[0][1]*t[1][0]-t[0][0]*t[1][1]);
                int sy = (int)(real_y);
                int sx = (int)(real_x);
                if ((sx>=0)&&(sy>=0)&&(sx<in_image.cols-1)&&(sy<in_image.rows-1)){
                    float h1 = (real_x-sx)*in_image.at<Vec3b>(sy,sx+1)[k]+(sx+1-real_x)*in_image.at<Vec3b>(sy,sx)[k];
                    float h2 = (real_x-sx)*in_image.at<Vec3b>(sy+1,sx+1)[k]+(sx+1-real_x)*in_image.at<Vec3b>(sy+1,sx)[k];
                    float h = (real_y-sy)*h2+(sy+1-real_y)*h1;
                    out_image.at<Vec3b>(y,x)[k] = (int)(h+0.5);
                }else{
                    out_image.at<Vec3b>(y,x)[k] = 0;
                }
            }
        }
    }
    in_image = out_image;
}

int main(){
    in_image = imread("/Users/apple/Desktop/a.png");
    float cy = (float)in_image.rows/2;
    float cx = (float)in_image.cols/2;

    float t0[2][3] = {{1,0,-cx},{0,1,-cy}};
    WarpAffine1(t0);
    float t1[2][3] = {{0.8,0.6,0},{-0.6,0.8,0}};
    WarpAffine1(t1);
    float t2[2][3] = {{1,0,cx},{0,1,cy}};
    WarpAffine1(t2);

    imshow("out",in_image);
    waitKey(0);
    imwrite("/Users/apple/Desktop/a31.png",in_image);

}
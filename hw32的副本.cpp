//
// Created by apple on 2018/9/26.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include <cmath>

using namespace std;
using namespace cv;

Mat in_image1;
Mat out_image1;

void WarpAffine1(){
    out_image1 = Mat::zeros(in_image1.size(),in_image1.type());
    //双线性插值
    for(int y=0;y<out_image1.rows;y++){
        for(int x=0;x<out_image1.cols;x++){
            for(int k=0;k<3;k++){
                float y0 = (float)(y - out_image1.rows/2)/(float)(out_image1.rows/2);
                float x0 = (float)(x - out_image1.cols/2)/(float)(out_image1.cols/2);
                float r = sqrt(pow(y0,2)+pow(x0,2));
                if (r>=1.00){
                    //cout<<1<<endl;
                    float yp = y0;
                    float xp = x0;
                    float real_y = (yp * in_image1.rows/2) + in_image1.rows/2;
                    float real_x = (xp * in_image1.cols/2) + in_image1.cols/2;

                    int sy = (int)(real_y);
                    int sx = (int)(real_x);
                    if ((sx>=0)&&(sy>=0)&&(sx<in_image1.cols-1)&&(sy<in_image1.rows-1)){
                        float h1 = (real_x-sx)*in_image1.at<Vec3b>(sy,sx+1)[k]+(sx+1-real_x)*in_image1.at<Vec3b>(sy,sx)[k];
                        float h2 = (real_x-sx)*in_image1.at<Vec3b>(sy+1,sx+1)[k]+(sx+1-real_x)*in_image1.at<Vec3b>(sy+1,sx)[k];
                        float h = (real_y-sy)*h2+(sy+1-real_y)*h1;
                        out_image1.at<Vec3b>(y,x)[k] = (int)(h+0.5);
                        //cout<<h<<endl;
                    }else{
                        out_image1.at<Vec3b>(y,x)[k] = 0;
                        //cout<<0.0<<endl;
                    }
                }else{
                    //cout<<0<<endl;
                    float theta = pow(1-r,2);
                    float yp = sin(theta)*x0+cos(theta)*y0;
                    float xp = cos(theta)*x0-sin(theta)*y0;
                    float real_y = (yp * in_image1.rows/2) + in_image1.rows/2;
                    float real_x = (xp * in_image1.cols/2) + in_image1.cols/2;

                    int sy = (int)(real_y);
                    int sx = (int)(real_x);
                    if ((sx>=0)&&(sy>=0)&&(sx<in_image1.cols-1)&&(sy<in_image1.rows-1)){
                        float h1 = (real_x-sx)*in_image1.at<Vec3b>(sy,sx+1)[k]+(sx+1-real_x)*in_image1.at<Vec3b>(sy,sx)[k];
                        float h2 = (real_x-sx)*in_image1.at<Vec3b>(sy+1,sx+1)[k]+(sx+1-real_x)*in_image1.at<Vec3b>(sy+1,sx)[k];
                        float h = (real_y-sy)*h2+(sy+1-real_y)*h1;
                        out_image1.at<Vec3b>(y,x)[k] = (int)(h+0.5);
                        //cout<<h<<endl;
                    }else{
                        out_image1.at<Vec3b>(y,x)[k] = 0;
                        //cout<<0<<endl;
                    }
                }
            }
        }
    }
}

int main(){
    in_image1 = imread("/Users/apple/Desktop/a.png");
    WarpAffine1();
    imshow("out",out_image1);
    waitKey(0);
    imwrite("/Users/apple/Desktop/a32.png",out_image1);
}

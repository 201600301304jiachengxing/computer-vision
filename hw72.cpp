//
// Created by apple on 2018/10/30.
//

#include <cmath>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
    Mat input = cv::imread("/Users/apple/Desktop/d.jpg");
    resize(input,input,Size(input.cols/5,input.rows/5),0,0,INTER_LINEAR);
    Mat output(input.size(),CV_8U);
    Mat input0;

    /*/ cir one mul 1150
    int pos=100;
    int maxr=20;
    int slide=20;
    int range=160;
    /*/

    /*/ cd one mul 1175
    int pos=100;
    int maxr=30;
    int slide=10;
    int range=155;
    /*/

    /*/ c0 one mul 1150
    int pos=100;
    int maxr=20;
    int slide=40;
    int range=200;
    /*/

    // d one mul 1075
    int pos=70;
    int maxr=40;
    int slide=40;
    int range=200;
    //
    float pi=3.1415926;
    if (input.empty())
        return -1;
    cvtColor(input, input0, CV_BGR2GRAY);
    Canny(input0,output,pos,pos*2,3);
    //imshow("out",output);
    //cvWaitKey(0);

    cout<<input.rows<<endl;
    int c[output.rows][output.cols][maxr];
    cout<<input.cols<<endl;
    for(int i=0;i<output.rows;i++){
        for(int j=0;j<output.cols;j++){
            for(int k=0;k<maxr;k++){
                c[i][j][k]=0;
            }
        }
    }

    cout<<0<<endl;
    for(int i=0;i<output.rows;i++){
        for(int j=0;j<output.cols;j++){
            if((int)output.at<uchar>(i,j)==255){
                for(int r=0;r<maxr;r++){
                    for(int k=0;k<360;k++){
                        int y0=i+(int)((r+slide)*cos(k*pi/(180))+0.5);
                        int x0=j+(int)((r+slide)*sin(k*pi/(180))+0.5);
                        if(y0>=1&&x0>=1&&y0<output.rows-1&&x0<output.cols-1){
                            c[y0][x0][r]++;
                            /*/
                            c[y0-1][x0-1][r-1]++;
                            c[y0-1][x0-1][r]++;
                            c[y0-1][x0-1][r-1]++;
                            c[y0-1][x0][r-1]++;
                            c[y0-1][x0][r]++;
                            c[y0-1][x0][r-1]++;
                            c[y0-1][x0+1][r-1]++;
                            c[y0-1][x0+1][r]++;
                            c[y0-1][x0+1][r-1]++;
                            c[y0][x0-1][r-1]++;
                            c[y0][x0-1][r]++;
                            c[y0][x0-1][r-1]++;
                            c[y0][x0][r-1]++;
                            c[y0][x0][r]++;
                            c[y0][x0][r-1]++;
                            c[y0][x0+1][r-1]++;
                            c[y0][x0+1][r]++;
                            c[y0][x0+1][r-1]++;
                            c[y0+1][x0-1][r-1]++;
                            c[y0+1][x0-1][r]++;
                            c[y0+1][x0-1][r-1]++;
                            c[y0+1][x0][r-1]++;
                            c[y0+1][x0][r]++;
                            c[y0+1][x0][r-1]++;
                            c[y0+1][x0+1][r-1]++;
                            c[y0+1][x0+1][r]++;
                            c[y0+1][x0+1][r-1]++;
                             /*/
                        }
                    }
                }
            }
        }
    }

    cout<<1<<endl;
    for(int i=0;i<output.rows;i++){
        for(int j=0;j<output.cols;j++){
            for(int k=0;k<maxr;k++){
                if(c[i][j][k]>=range){
                    Point p(j,i);
                    circle(input,p,k+slide,Scalar(0, 255, 0));
                }
            }
        }
    }

    imwrite("/Users/apple/Desktop/h1.jpg",input);
    imshow("out",input);
    waitKey(0); //等待按键
    return 0;
}
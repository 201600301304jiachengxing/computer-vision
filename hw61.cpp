//
// Created by apple on 2018/10/24.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include <cmath>
#include <string>

using namespace std;
using namespace cv;

int main61(){
    Mat input=imread("/Users/apple/Desktop/a.png");
    cvtColor(input,input,CV_BGR2GRAY);
    threshold(input,input,128,255,THRESH_BINARY);
    Mat output=Mat::zeros(input.size(),CV_8UC3);
    Mat out1=Mat::zeros(input.size(),input.type());

    int h=input.rows;
    int w=input.cols;
    int t[h][w];
    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){
            t[i][j]=0;
            //cout<<(int)input.at<uchar>(i,j)<<endl;
        }
    }

    //6.1.1 分区域
    int num=0;
    struct color{
        int n;
        int b;
        int g;
        int r;
    }c[1000];

    for(int i=0;i<1000;i++){
        c[i].b=0;
        c[i].g=0;
        c[i].r=0;
    }

    c[0].n=0;
    c[0].b=random()%255;
    c[0].g=random()%255;
    c[0].r=random()%255;


    for(int i=1;i<h;i++){
        for(int j=1;j<w;j++){
            if((int)input.at<uchar>(i,j)==(int)input.at<uchar>(i-1,j)||(int)input.at<uchar>(i,j)==(int)input.at<uchar>(i,j-1)){
                if((int)input.at<uchar>(i-1,j)==(int)input.at<uchar>(i,j-1)){
                    if(c[t[i-1][j]].n==c[t[i][j-1]].n){
                        t[i][j]=t[i][j-1];
                    }else{
                        t[i][j]=t[i][j-1];
                        if(c[t[i-1][j]].n>c[t[i][j-1]].n){
                            c[t[i-1][j]].n=c[t[i][j-1]].n;
                            c[t[i-1][j]].b=c[t[i][j-1]].b;
                            c[t[i-1][j]].g=c[t[i][j-1]].g;
                            c[t[i-1][j]].r=c[t[i][j-1]].r;
                        }else if(c[t[i-1][j]].n<=c[t[i][j-1]].n){
                            c[t[i][j-1]].n=c[t[i-1][j]].n;
                            c[t[i][j-1]].b=c[t[i-1][j]].b;
                            c[t[i][j-1]].g=c[t[i-1][j]].g;
                            c[t[i][j-1]].r=c[t[i-1][j]].r;
                        }

                    }
                }else if((int)input.at<uchar>(i,j)==(int)input.at<uchar>(i-1,j)){
                    t[i][j]=t[i-1][j];
                }else if((int)input.at<uchar>(i,j)==(int)input.at<uchar>(i,j-1)){
                    t[i][j]=t[i][j-1];
                }
            }else{
                num++;
                c[num].n=num;
                c[num].b=(random()*2)%255;
                c[num].g=(random()*3)%255;
                c[num].r=(random()*4)%255;
                t[i][j]=num;
            }
        }
    }

    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){
            output.at<Vec3b>(i,j)[0]=c[t[i][j]].b;
            output.at<Vec3b>(i,j)[1]=c[t[i][j]].g;
            output.at<Vec3b>(i,j)[2]=c[t[i][j]].r;
        }
    }

    imshow("out",output);
    imwrite("/Users/apple/Desktop/a0.png",output);
    cvWaitKey(0);

    //6.1.2 最大区域
    num++;
    int q[num];
    for(int i=0;i<num;i++){
        q[i]=0;
    }

    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){
            q[c[t[i][j]].n]++;
        }
    }
    int max=0;
    int index=0;
    for(int i=1;i<num;i++){
        //cout<<q[i]<<endl;
        if(q[i]>max){
            max=q[i];
            index=i;
        }
    }

    cout<<num<<endl;
    //cout<<index<<endl;
    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){
            if(c[t[i][j]].n==index){
                out1.at<uchar>(i,j)=255;
            }else{
                out1.at<uchar>(i,j)=0;
            }
        }
    }
    imshow("out1",out1);
    imwrite("/Users/apple/Desktop/a1.png",out1);
    waitKey(0);

}
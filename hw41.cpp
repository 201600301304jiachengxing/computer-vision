//
// Created by apple on 2018/10/9.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include <cmath>

using namespace std;
using namespace cv;

void Gaussian(const Mat &input,Mat &output,double sigma){
    int m=(int)(6*sigma-1);
    if(m%2==0){
        m++;
    }
    int k=m/2;
    //cout<<k<<m<<endl;
    int sum=0;
    int ro[m];
    int co[m];
    double b=exp(-pow(k,2)/(2*pow(sigma,2)));
    for(int i=0;i<m;i++){
        ro[i]=(int)(exp(-pow(i-k,2)/(2*pow(sigma,2)))/b);
        co[i]=(int)(exp(-pow(i-k,2)/(2*pow(sigma,2)))/b);
    }
    for(int i=0;i<m;i++){
        for(int j=0;j<m;j++){
            sum+=ro[i]*co[j];
        }
    }

    for(int i=0;i<m;i++){
        cout<<ro[i]<<' '<<co[i]<<endl;
    }

    // 行列可分离性加速
    for(int y=0;y<input.rows;y++){
        for(int x=0;x<input.cols;x++){
            for(int c=0;c<3;c++){
                //cout<<(int)input.at<Vec3b>(y,x)[c]<<endl;
                int p[m];
                int e=0;
                for(int i=0;i<m;i++){
                    p[i]=0;
                    for(int j=0;j<m;j++){
                        if(y+i-k>=0&&x+j-k>=0&&x+i-k<input.cols&&y+j-k<input.rows){
                            p[i]+=input.at<Vec3b>(y+i-k,x+j-k)[c]*co[j];
                        }
                    }
                }
                for(int i=0;i<m;i++){
                    if(y+i-k>=0&&y+i-k<input.rows){
                        e+=p[i]*ro[i];
                    }
                }
                //cout<<(int)output.at<Vec3b>(y,x)[c]<<endl;
                output.at<Vec3b>(y,x)[c]=e/sum;
                //cout<<(int)output.at<Vec3b>(y,x)[c]<<endl;
            }
        }
    }

    /*/ 普通滤波器
    for(int y=0;y<input.rows;y++){
        for(int x=0;x<input.cols;x++){
            for(int c=0;c<3;c++){
                int e=0;
                output.at<Vec3b>(y,x)[c]=0;
                for(int i=0;i<m;i++){
                    for(int j=0;j<m;j++){
                        if(y+i-k>=0&&x+j-k>=0&&x+i-k<input.cols&&y+j-k<input.rows){
                            e+=input.at<Vec3b>(y+i-k,x+j-k)[c]*ro[i]*co[j];
                        }
                    }
                }
                output.at<Vec3b>(y,x)[c]=output.at<Vec3b>(y,x)[c]/sum;
            }
        }
    }

    for(int y=0;y<input.rows;y++){
        for(int x=0;x<input.cols;x++){
            for(int c=0;c<3;c++){
                cout<<(int)output.at<Vec3b>(y,x)[c]<<endl;
            }
        }
    }

    /*/
}


int main(){
    Mat input=imread("/Users/apple/Desktop/c.jpg");
    Mat output=Mat::zeros(input.size(),input.type());
    Gaussian(input,output,2);
    imshow("out",output);
    imwrite("/Users/apple/Desktop/g.jpg",output);
    waitKey(0);
}


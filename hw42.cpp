//
// Created by apple on 2018/10/9.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include <cmath>

using namespace std;
using namespace cv;

void MeanFilter(const Mat &input,Mat &output,int z){
    if(z%2==0){
        z++;
    }
    int w=z/2;
    int sum=z*z;

    //cout<<sum<<endl;
    int s[input.rows][input.cols][3];
    //cout<<0<<endl;
    s[0][0][0]=(int)(input.at<Vec3b>(0,0)[0]);
    s[0][0][1]=(int)(input.at<Vec3b>(0,0)[1]);
    s[0][0][2]=(int)(input.at<Vec3b>(0,0)[2]);
    //cout<<1<<endl;
    for(int i=1;i<input.cols;i++){
        for(int c=0;c<3;c++){
            s[0][i][c]=0;
            s[0][i][c]=(int)(input.at<Vec3b>(0,i)[c])+s[0][i-1][c];
            //cout<<s[0][i-1][c]<<'-'<<endl;
            //cout<<(int)(input.at<Vec3b>(0,i)[c])<<'/'<<endl;
            //cout<<(int)(input.at<Vec3b>(0,i)[c])+s[0][i-1][c]<<endl;
        }
    }
    for(int i=1;i<input.rows;i++){
        for(int c=0;c<3;c++){
            s[i][0][c]=0;
            s[i][0][c]=(int)(input.at<Vec3b>(i,0)[c])+s[i-1][0][c];
            //cout<<s[i][0][c]<<'-'<<endl;
            //cout<<(int)input.at<Vec3b>(i,0)[c]+s[i-1][0][c]<<endl;
        }
    }
    for(int y=1;y<input.rows;y++){
        for(int x=1;x<input.cols;x++){
            for(int c=0;c<3;c++){
                s[y][x][c]=0;
                s[y][x][c]=(int)(input.at<Vec3b>(y,x)[c])+s[y-1][x][c]+s[y][x-1][c]-s[y-1][x-1][c];
                //cout<<s[y][x][c]<<'-'<<endl;
                //cout<<(int)(input.at<Vec3b>(y,x)[c])<<'/'<<endl;
                //cout<<(int)(input.at<Vec3b>(y,x)[c])+s[y][x][c]<<endl;
            }
        }
    }




    //cout<<z<<w<<endl;

    /*/
    for(int y=0;y<input.rows;y++){
        for(int x=0;x<input.cols;x++){
            for(int c=0;c<3;c++){
                if(s[y][x][c]<0){
                    s[y][x][c]=__inf();
                }
                //cout<<s[y][x][c]<<endl;
            }
        }
    }
    /*/

    //cout<<input.rows<<' '<<input.cols<<endl;


    // 普通滤波器
    for(int y=0;y<input.rows;y++){
        for(int x=0;x<input.cols;x++){
            for(int c=0;c<3;c++){
                //cout<<x<<' '<<y<<endl;
                int k=0;
                if(y-w-1<0&&x-w-1<0&&y+w<input.rows&&x+w<input.cols){
                    k=s[y+w][x+w][c];
                }else if(y-w-1<0&&x-w-1>=0&&y+w<input.rows&&x+w>=input.cols){
                    k=s[y+w][input.cols-1][c]-s[y+w][x-w-1][c];
                }else if(y-w-1>=0&&x-w-1<0&&y+w>=input.rows&&x+w<input.cols){
                    k=s[input.rows-1][x+w][c]-s[y-w-1][x+w][c];
                }else if(y-w-1>=0&&x-w-1>=0&&y+w>=input.rows&&x+w>=input.cols){
                    k=s[input.rows-1][input.cols-1][c]+s[y-w-1][x-w-1][c]-s[input.rows-1][x-w-1][c]-s[y-w-1][input.cols-1][c];
                }else if(y-w-1>=0&&x-w-1<0&&y+w<input.rows&&x+w<input.cols){
                    k=s[y+w][x+w][c]-s[y-w-1][x+w][c];
                }else if(y-w-1>=0&&x-w-1>=0&&y+w<input.rows&&x+w>=input.cols){
                    k=s[y+w][input.cols-1][c]+s[y-w-1][x-w-1][c]-s[y+w][x-w-1][c]-s[y-w-1][input.cols-1][c];
                }else if(y-w-1<0&&x-w-1>=0&&y+w<input.rows&&x+w<input.cols){
                    k=s[y+w][x+w][c]-s[y+w][x-w-1][c];
                }else if(y-w-1>=0&&x-w-1>=0&&y+w>=input.rows&&x+w<input.cols){
                    k=s[input.rows-1][x+w][c]+s[y-w-1][x-w-1][c]-s[input.rows-1][x-w-1][c]-s[y-w-1][x+w][c];
                }else if(y-w-1>=0&&x-w-1>=0&&y+w<input.rows&&x+w<input.cols){
                    k=s[y+w][x+w][c]+s[y-w-1][x-w-1][c]-s[y+w][x-w-1][c]-s[y-w-1][x+w][c];
                    //cout<<1<<endl;
                }
                //cout<<x<<'-'<<y<<endl;
                //cout<<(int)output.at<Vec3b>(y,x)[c]<<endl;
                output.at<Vec3b>(y,x)[c]=k/sum;
            }
        }
    }

    /*/
    for(int y=0;y<input.rows;y++){
        for(int x=0;x<input.cols;x++){
            for(int c=0;c<3;c++){
                cout<<(int)output.at<Vec3b>(y,x)[c]<<endl;
            }
        }
    }
    /*/

}


int main42(){
    Mat input=imread("/Users/apple/Desktop/a.png");
    Mat output=Mat::zeros(input.size(),input.type());
    MeanFilter(input,output,11);
    imshow("out",output);
    imwrite("/Users/apple/Desktop/h2.png",output);
    waitKey(0);
}
//
// Created by apple on 2018/10/16.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include <cmath>
#include <string>

using namespace std;
using namespace cv;
int main(){
    VideoCapture cap("/Users/apple/Desktop/1.avi");
    if(!cap.isOpened()){
        return -1;
    }
    int x,y,x0,y0,dx,dy;
    int num=1;
    Mat frame0;
    cap >> frame0;
    x=frame0.cols;
    y=frame0.rows;
    int t[256][3];
    float d[256][3];
    for(int j=0;j<256;j++){
        for(int c=0;c<3;c++){
            t[j][c] = 0;
            d[j][c] = 0;
        }
    }
    float alpha=0.001;
    int sum=0;
    //(0,160)-->(0+470,160+320)
    for(;;){
        Mat frame;
        cap >> frame;
        num++;
        if(num==20){
            x0=350;
            y0=20;
            dx=110;
            dy=120;
            sum=dx*dy;
            // h
            for(int j=y0;j<y0+dy;j++){
                for(int i=x0;i<x0+dx;i++){
                    for(int c=0;c<3;c++){
                        t[(int)frame.at<Vec3b>(j,i)[c]][c]++;
                    }
                }
            }
            for(int j=0;j<256;j++){
                for(int c=0;c<3;c++){
                    d[j][c]=(float)(t[j][c])/sum;
                }
            }
            for(int j=1;j<256;j++){
                for(int c=0;c<3;c++){
                    d[j][c]+=d[j-1][c];
                }
            }
            rectangle(frame,cvPoint(x0,y0),cvPoint(x0+dx,y0+dy),cvScalar(0,255,0),2);
            imshow("out",frame);
            imwrite("/Users/apple/Desktop/20.png",frame);
        }else if(num>20&&num<=45){
            int t1[256][3];
            float d1[256][3];
            for(int j=0;j<256;j++){
                for(int c=0;c<3;c++){
                    t1[j][c] = 0;
                    d1[j][c] = 0;
                }
            }
            float cos=0;
            float cos0=0;
            int pnum=0;
            int ddx=0;
            int ddy=0;
            int x1=160;
            int y1=0;
            int xm=x0;
            int ym=y0;
            float tm[256][3];
            float dm[256][3];
            while(1-cos>alpha&&pnum<500){
                ddx=rand()%(dx/2)-dx/4;
                ddy=rand()%(dy/2)-dy/4;
                x1=x0+ddx;
                y1=y0+ddy;
                // new h
                if(x1>=160&&y1>=0&&x1<480-dx&&y1<480-dy){
                    pnum++;
                    for(int j=0;j<256;j++){
                        for(int c=0;c<3;c++){
                            t1[j][c]=0;
                        }
                    }
                    for(int j=y1;j<y1+dy;j++){
                        for(int i=x1;i<x1+dx;i++){
                            for(int c=0;c<3;c++){
                                t1[(int)frame.at<Vec3b>(j,i)[c]][c]++;
                            }
                        }
                    }
                    for(int j=0;j<256;j++){
                        for(int c=0;c<3;c++){
                            d1[j][c]=(float)(t1[j][c])/sum;
                        }
                    }
                    for(int j=1;j<256;j++){
                        for(int c=0;c<3;c++){
                            d1[j][c]+=d1[j-1][c];
                        }
                    }
                    // compute cos
                    float sumx=0;
                    float sum1=0;
                    float sum2=0;
                    for(int j=1;j<256;j++){
                        for(int c=0;c<3;c++){
                            sumx+=d[j][c]*d1[j][c];
                            sum1+=d[j][c]*d[j][c];
                            sum2+=d1[j][c]*d1[j][c];
                        }
                    }
                    //cout<<sumx<<" "<<sum1<<" "<<sum2<<endl;
                    if(sum2!=0){
                        cos0=abs(sumx/sqrt(sum1*sum2));
                    }else{
                        cos0=0;
                    }
                    //cout<<cos0<<endl;
                    if(cos0>cos){
                        cos=cos0;
                        xm=x1;
                        ym=y1;
                        // update
                        for(int j=0;j<256;j++){
                            for(int c=0;c<3;c++){
                                dm[j][c]=d1[j][c];
                                tm[j][c]=t1[j][c];
                            }
                        }
                    }
                }
            }
            cout<<pnum<<endl;
            cout<<ddx<<" "<<ddy<<endl;
            //cout<<xm<<' '<<ym<<endl;

            x0=xm;
            y0=ym;
            // update
            for(int j=0;j<256;j++){
                for(int c=0;c<3;c++){
                    d[j][c]=dm[j][c];
                    t[j][c]=tm[j][c];
                }
            }
            rectangle(frame,cvPoint(x0,y0),cvPoint(x0+dx,y0+dy),cvScalar(0,255,0),2);
            imshow("out",frame);
            if(num%5==0){

                stringstream sname;
                string name1="/Users/apple/Desktop/";
                string name2=".png";
                sname<<name1<<num<<name2<<endl;
                imwrite(sname.str(),frame);
            }
        }
        if(waitKey(30)>=0){
            break;
        }
    }
}
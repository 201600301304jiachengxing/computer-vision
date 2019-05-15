//
// Created by apple on 2018/11/21.
//

#include<iostream>
#include<vector>

#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;


int main()
{
    //读取图片
    Mat rgbd1 = imread("/Users/apple/Desktop/13.jpg");
    Mat rgbd2 = imread("/Users/apple/Desktop/14.png");
    Ptr<ORB> orb = ORB::create(50);
    vector<KeyPoint> Keypoints1,Keypoints2;
    Mat descriptors1,descriptors2;
    orb->detectAndCompute(rgbd1, Mat(), Keypoints1, descriptors1);
    orb->detectAndCompute(rgbd1, Mat(), Keypoints2, descriptors2);

    //可视化，显示关键点
    Mat ShowKeypoints1, ShowKeypoints2;
    drawKeypoints(rgbd1,Keypoints1,ShowKeypoints1);
    drawKeypoints(rgbd2, Keypoints2, ShowKeypoints2);
    //imshow("Keypoints1", ShowKeypoints1);
    //imshow("Keypoints2", ShowKeypoints2);
    //waitKey(0);

    //Matching
    vector<DMatch> matches;
    Ptr<DescriptorMatcher> matcher =DescriptorMatcher::create("BruteForce");
    matcher->match(descriptors1, descriptors2, matches);
    cout << "find out total " << matches.size() << " matches" << endl;

    //可视化
    Mat ShowMatches;
    drawMatches(rgbd1,Keypoints1,rgbd2,Keypoints2,matches,ShowMatches);
    imshow("matches", ShowMatches);
    imwrite("/Users/apple/Desktop/ORB.jpg",ShowMatches);
    waitKey(0);
    return 0;
}

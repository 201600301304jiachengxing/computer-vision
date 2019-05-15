//
// Created by apple on 2018/11/14.
//

#include <iostream>
#include <vector>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

int main91()
{
    Mat img1 = imread("/Users/apple/Desktop/13.jpg", IMREAD_GRAYSCALE);
    Mat img2 = imread("/Users/apple/Desktop/14.png", IMREAD_GRAYSCALE);
    if ((img1.data == NULL)||(img2.data ==NULL))
    {
        cout << "No exist" << endl;
        return -1;
    }
    Ptr<Feature2D> feature = xfeatures2d::SIFT::create(1000);

    vector<KeyPoint> keypoints_1, keypoints_2;
    Mat descriptors_1, descriptors_2;

    feature->detectAndCompute(img1, Mat(), keypoints_1, descriptors_1 );
    feature->detectAndCompute(img2, Mat(), keypoints_2, descriptors_2 );
    drawKeypoints(img1, keypoints_1, img1);
    drawKeypoints(img2, keypoints_2, img2);

    FlannBasedMatcher matcher;
    std::vector< DMatch > matches;
    matcher.match( descriptors_1, descriptors_2, matches );
    double max_dist = 0; double min_dist = 100;

    for( int i = 0; i < descriptors_1.rows; i++ )
    {
        double dist = matches[i].distance;
        if( dist < min_dist ) min_dist = dist;
        if( dist > max_dist ) max_dist = dist;
    }
    printf("-- Max dist : %f \n", max_dist );
    printf("-- Min dist : %f \n", min_dist );

    std::vector< DMatch > good_matches;
    for( int i = 0; i < descriptors_1.rows; i++ )
    {
        if( matches[i].distance <= max(2*min_dist, 0.02) )
        {
            good_matches.push_back( matches[i]);
        }
    }

    Mat img_matches;
    drawMatches( img1, keypoints_1, img2, keypoints_2,
    good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),
    vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );

    namedWindow("Good Matches",0);
    resizeWindow("Good Matches",800,800);
    imshow( "Good Matches", img_matches );
    imwrite("/Users/apple/Desktop/SI.jpg",img_matches);

    for( int i = 0; i < (int)good_matches.size(); i++ )
    {
        printf( "-- Good Match [%d] Keypoint 1: %d  -- Keypoint 2: %d  \n", i, good_matches[i].queryIdx, good_matches[i].trainIdx );
    }
    waitKey(0);
    return 0;
}


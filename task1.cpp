#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
int main() {
    Mat srcImage = imread("/Users/apple/Desktop/ppp.png");
    imshow("[img]", srcImage);
    waitKey(0);
    imwrite("/Users/apple/Desktop/ppp2.png",srcImage);
    return 0;
}

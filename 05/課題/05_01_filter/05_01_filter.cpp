#include <iostream>
#include <opencv2/opencv.hpp>
#define FILE_NAME "./apple_grayscale.jpg"
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"

int main(int argc, const char *argv[])
{
    cv::Mat src_img = cv::imread(FILE_NAME, 0);
    if (src_img.empty())
    {
        fprintf(stderr, "File is not opened.\n");
        return (-1);
    }

    cv::Mat dst_img;
    int n;
    printf("n:");scanf("%d",&n);
    if (n==0) return -1;
    for (int i=0;i<n;i++){
        cv::blur(src_img, dst_img,cv::Size(3, 3));
        src_img = dst_img;
    }

    // cv::imshow(WINDOW_NAME_INPUT, src_img);
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
    cv::waitKey();

    return 0;
}
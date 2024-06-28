#include <iostream>
#include <opencv2/opencv.hpp>
// #define FILE_NAME "./sakura.jpg"
#define FILE_NAME "./fruit_image.jpg"
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"
#define COLOR_NUM (256)

int main(int argc, const char *argv[])
{
    cv::Mat src_img = cv::imread(FILE_NAME, cv::IMREAD_GRAYSCALE);
    cv::Mat dst_img = cv::Mat(src_img.size(), CV_8UC1);

    if (src_img.empty())
    {
        fprintf(stderr, "読み込み失敗\n");
        return (-1);
    }

    uchar lut[COLOR_NUM];
    int n,gray;

    fprintf(stderr, "階調数:");
    scanf("%d", &n);

    for (int i = 0; i < COLOR_NUM; i++){
        gray = i/(COLOR_NUM / n) * ((COLOR_NUM - 1) / (n - 1));
        if (gray >255){
            lut[i]=255;
        }
        else{
            lut[i] = gray;
        }
        // printf("%d,%d\n",i,lut[i]);
    }

    for (int y = 0; y < src_img.rows; y++)
        for (int x = 0; x < src_img.cols; x++)
            dst_img.at<uchar>(y, x) = lut[src_img.at<uchar>(y, x)];

    cv::imshow(WINDOW_NAME_INPUT, src_img);
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
    cv::waitKey();

    return 0;
}
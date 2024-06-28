#include <iostream>
#include <opencv2/opencv.hpp>
#define sample "./drug0.png"
#define file "./drug11.png"
#define TH (127)
#define HIGHVAL (255)

int main(int argc, const char *argv[]){
    double count = 0, all = 0, per = 0;
    int r = 0, g = 0, b = 0;
    cv::Mat src_img = cv::imread(file);
    cv::Mat sample_img = cv::imread(sample);
    cv::Mat dst_img;

    if (src_img.empty() || sample_img.empty()){
        fprintf(stderr, "File is not opened.\n");
        return (-1);
    }

    cv::threshold(sample_img, dst_img, TH, HIGHVAL, cv::THRESH_BINARY);
    for (int y=0;y<dst_img.rows;y++){
        for (int x=0;x<dst_img.cols;x++){
            cv::Vec3b bgr = dst_img.at<cv::Vec3b>(y, x);
            int gray = 0.229*bgr[2] + 0.587*bgr[1] + 0.114*bgr[0];

            if (gray > TH){
                r = bgr[2];
                g = bgr[1];
                b = bgr[0];
            }
        }
    }

    cv::threshold(src_img, dst_img, TH, HIGHVAL, cv::THRESH_BINARY);
    for (int y=0;y<dst_img.rows;y++){
        for (int x=0; x<dst_img.cols;x++){
            cv::Vec3b bgr = dst_img.at<cv::Vec3b>(y, x);

            all ++;
            if (r == bgr[2] && g == bgr[1] && b == bgr[0]) count ++;
        }
    }

    per = (count / all) * 100;
    if (per > 23) printf("%.1lf%% 膨張\n", per);
    else if (per < 17) printf("%.1lf%% 欠損\n", per);
    else printf("%.1lf%% 正常\n", per);

    cv::imshow("WINDOW_NAME_INPUT", src_img);
    cv::imshow("WINDOW_NAME_OUTPUT", dst_img);
    cv::waitKey();
    return 0;
}
#include <iostream>
#include <opencv2/opencv.hpp>
#define TARGET_IMG_FILE "./gazoDora.jpg"
#define GREEN_IMG_FILE "./green.jpg"
#define RED_IMG_FILE "./red.jpg"
#define PURPLE_IMG_FILE "./star.jpg"
#define YELLOW_IMG_FILE "./yellow.jpg"

int main(int argc, const char *argv[]) {
    char template_file[4][15] = {GREEN_IMG_FILE, RED_IMG_FILE, PURPLE_IMG_FILE, YELLOW_IMG_FILE};
    int color[4][3]{{0, 255, 0}, {255, 0, 0}, {255, 0, 255}, {255, 255, 0}};
    cv::Mat src_img, template_img, compare_img, result_img;
    double min_val, max_val;
    cv::Point min_loc, max_loc;
    float s;

    src_img = cv::imread(TARGET_IMG_FILE, cv::IMREAD_COLOR);
    if (src_img.empty()) return (-1);
    result_img = cv::Mat(src_img.size(), CV_8UC1);
    result_img = src_img.clone();
    template_img = cv::imread(GREEN_IMG_FILE, cv::IMREAD_COLOR);
    compare_img = cv::Mat(cv::Size(src_img.rows - template_img.rows + 1, src_img.cols - template_img.cols + 1), CV_32F, 1);

    for (int i = 0; i < 4; i++) {
        template_img = cv::imread(template_file[i], cv::IMREAD_COLOR);
        cv::matchTemplate(src_img, template_img, compare_img, cv::TM_SQDIFF_NORMED);
        cv::minMaxLoc(compare_img, &min_val, &max_val, &min_loc, &max_loc);
        for (int y = 0; y < compare_img.rows; y++){
            for (int x = 0; x < compare_img.cols; x++) {
                s = compare_img.at<float>(y, x);
                if (s < 0.1) cv::rectangle(result_img, cv::Point(x, y), cv::Point(x + template_img.cols, y + template_img.rows), CV_RGB (color[i][0], color[i][1], color[i][2]), 5);
            }
        }
    }

    cv::imshow("input", src_img);
    cv::imshow("template", template_img);
    cv::imshow("result", result_img);
    cv::waitKey(0);

    return 0;
}

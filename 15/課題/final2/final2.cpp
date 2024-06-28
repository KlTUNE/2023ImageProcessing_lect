#include <iostream>
#include <opencv2/opencv.hpp>
#define TARGET_IMG_FILE "./input_img1.png"
#define KING "./king1.png"
#define KING_R "./king2.png"
#define PAWN "./pawn1.png"
#define PAWN_R "./pawn2.png"
#define PROM "./prom_pawn1.png"
#define PROM_R "./prom_pawn2.png"

int main(int argc, const char *argv[]) {
    char template_file[3][20] = {KING, PAWN, PROM};
    char template_r[3][20] = {KING_R, PAWN_R, PROM_R};
    char koma[3][20] = {"king: ", "pawn: ", "prom_pawn: "};
    cv::Mat src_img = cv::imread(TARGET_IMG_FILE);
    cv::Mat template_img, compare_img, result_img;
    cv::Point min_loc, max_loc;
    double min_val, max_val;
    float s;
    int count = 0, flag = 0;

    if (src_img.empty()) return (-1);

    //upperの表示
    printf("upper\n");
    for (int i = 0; i < 3; i++) {
        //テンプレートマッチング
        template_img = cv::imread(template_r[i], cv::IMREAD_COLOR);
        compare_img = cv::Mat(cv::Size(src_img.rows - template_img.rows + 1, src_img.cols - template_img.cols + 1), CV_32F, 1);
        cv::matchTemplate(src_img, template_img, compare_img, cv::TM_SQDIFF_NORMED);
        cv::minMaxLoc(compare_img, &min_val, &max_val, &min_loc, &max_loc);

        for (int y = 0; y < compare_img.rows; y++){
            for (int x = 0; x < compare_img.cols; x++) {
                s = compare_img.at<float>(y, x);
                //マッチ度が0.2未満だとカウントアップ、x軸とy軸を5px飛ばす
                if (s < 0.2) {
                    count ++;
                    x += 5;
                    flag = 1;
                }
            }
            if (flag == 1){
                y += 5;
                flag = 0;
            }
        }
        //カウントが0以外だったら出力
        if (count != 0){
            printf("%s%d\n", koma[i], count);
            count = 0;
        }
    }

    printf("\n\nlower\n");
    for (int i = 0; i < 3; i++) {
        //テンプレートマッチング
        template_img = cv::imread(template_file[i], cv::IMREAD_COLOR);
        compare_img = cv::Mat(cv::Size(src_img.rows - template_img.rows + 1, src_img.cols - template_img.cols + 1), CV_32F, 1);
        cv::matchTemplate(src_img, template_img, compare_img, cv::TM_SQDIFF_NORMED);
        cv::minMaxLoc(compare_img, &min_val, &max_val, &min_loc, &max_loc);

        for (int y = 0; y < compare_img.rows; y++){
            for (int x = 0; x < compare_img.cols; x++) {
                s = compare_img.at<float>(y, x);
                //マッチ度が0.2未満だとカウントアップ、x軸とy軸を5px飛ばす
                if (s < 0.2) {
                    count ++;
                    x += 5;
                    flag = 1;
                }
            }
            if (flag == 1){
                y += 5;
                flag = 0;
            }
        }
        //カウントが0以外だったら出力
        if (count != 0){
            printf("%s%d\n", koma[i], count);
            count = 0;
        }
    }

    cv::imshow("input", src_img);
    cv::waitKey(0);

    return 0;
}

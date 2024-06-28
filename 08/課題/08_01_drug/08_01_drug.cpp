// K22105 幅優太

#include <iostream>
#include <opencv2/opencv.hpp>
#define file "./drug7.png"
#define TH (127)

int main(int argc, const char *argv[]){
    char file_name[12];

    for (int i=0; i<8; i++) {
        double count = 0, all = 0, per = 0;;

        snprintf(file_name, sizeof(file_name), "./drug%d.png", i);
        printf("file:%s  ", file_name);

        cv::Mat src_img = cv::imread(file_name, 0);
        if (src_img.empty()){
            fprintf(stderr, "File is not opened.\n");
            return (-1);
        }

        for (int y=0; y<src_img.rows; y++) {
            for (int x=0; x<src_img.cols; x++) {
                uchar s = src_img.at<uchar>(y, x);

                all ++;
                if (s > TH) {
                    count ++;
                }
            }
        }

        per = (count / all) * 100;
        if (per >23){
            printf("%.1lf%% 膨張\n", per);
        }
        else if (per < 17){
            printf("%.1lf%% 欠損\n", per);
        }
        else{
            printf("%.1lf%% 正常\n", per);
        }
    }

    return 0;
}
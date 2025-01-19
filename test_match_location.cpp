#include <boost/filesystem.hpp>
#include <map>
#include <numeric>
#include <future>
#include <thread>
#include "nkr.h"

int main(int argc, char* argv[])
{
    // linemode 模板匹配 
    cv::Mat to_recognize = cv::imread(argv[1]);
    if (to_recognize.channels() == 3)
        cv::cvtColor(to_recognize, to_recognize, cv::COLOR_BGR2GRAY);     
    std::string model_path = std::string(argv[2]);
    
    // 多尺度模板，匹配定位加速
    nkr::Linemode_Match linemode_match_loc(128, {2}, {0, 1}, 2, {0.5, 1.0}, 0.5, model_path, {"test_loc"}, "test_loc", 10, 10);
    
    cv::Mat template_image = cv::imread(argv[3]);
    cv::Rect match_roi;
    // linemode匹配定位 
    if (!linemode_match_loc.is_loaded("test_loc"))
        linemode_match_loc.train_model(template_image, model_path, {"test_loc"}, "test_loc");
    linemode_match_loc.recognize(to_recognize, {"test_loc"}, 80, match_roi, true);
        
    cv::Mat write_mat = to_recognize.clone();
    if (write_mat.channels() == 1)
        cv::cvtColor(write_mat, write_mat, cv::COLOR_GRAY2BGR); 
    cv::rectangle(write_mat, match_roi, cv::Scalar(0, 255, 0), 2, 8, 0);
    cv::imwrite("./datas/locate_text_area.png", write_mat);

    
    // 设置匹配区域
    
    cv::Rect process_roi = cv::Rect(0, 0, template_image.cols, template_image.rows);
    // 多尺度快速灰度模板匹配定位
    nkr::fast_match_template(to_recognize, template_image, process_roi, match_roi);
    cv::rectangle(write_mat, match_roi, cv::Scalar(0, 255, 0), 2, 8, 0);
    cv::imwrite("./datas/locate_text_area.png", write_mat);
    
   
    return 0;

}

#ifndef NKR_H
#define NKR_H

#include <opencv2/opencv.hpp>
#include <boost/filesystem.hpp> 
#include <numeric>

class Linemode_Template_Match;
class Edge_Template_Match;


namespace nkr {


// linemode模板匹配定位和识别

class Linemode_Match
{

public:

Linemode_Match(const std::vector<int>& pyr_stride, const std::vector<float>& angle_range, float angle_step, 
                const std::vector<float>& scale_range, float scale_step, const std::string& model_path, 
                const std::vector<std::string>& class_ids, const std::string& template_model_name);

Linemode_Match(int feature_number, const std::vector<int>& pyr_stride, const std::vector<float>& angle_range, float angle_step, 
                const std::vector<float>& scale_range, float scale_step, const std::string& model_path, 
                const std::vector<std::string>& class_ids, const std::string& template_model_name, 
                int weak_thresh = 0, int strong_thresh = 80);

// 加载模型
void load_model(const std::string& model_path, const std::vector<std::string>& class_ids, 
                const std::string& template_model_name);


// 给定多个模板图对应的标签
void set_labels(const std::map<int, std::string> labels);

// 给定模板图路径读取对应的标签，模板需按 "字符" + "当前字符数量标志".png 例如 10.png 11.png A1.png A2.png
void read_labels(const std::string& template_image_path);

// 判断模型是否加载
bool is_loaded(const std::string& class_id);

// 加载文件路径下的所有图像训练模型
bool train_model(const std::string& template_image_path, const std::string& model_path, 
                 const std::string& class_id, const std::string& template_model_name);

// 给定图像训练模型
bool train_model(const cv::Mat& template_image, const std::string& model_path, const std::string& class_id, 
                 const std::string& template_model_name);

// 删除class_id的模型
bool delete_model(const std::vector<std::string>& class_ids);

// 形状匹配定位和识别
bool recognize(const cv::Mat& to_match, const std::vector<std::string>& class_ids, int match_similarity_thresh, 
               cv::Rect& match_roi, bool pyramid_acc = true);


// 单字符形状匹配识别
std::string recognize(const cv::Mat& to_match, const std::vector<std::string>& class_ids, 
                      int match_similarity_thresh, bool pyramid_acc = false);


// 字符行形状匹配识别
std::string recognize(const cv::Mat& to_match, const std::vector<std::string>& class_ids, int match_similarity_thresh,
                      int nms_similarity_thresh, float num_iou_thresh, std::vector<cv::Rect>& match_rois, 
                      bool pyramid_acc = false, unsigned int refine_match = 0,
                      const std::vector<cv::Rect>& mask_roi = std::vector<cv::Rect>());


private:

    std::shared_ptr<Linemode_Template_Match> linemode_template_match;

};


// 边缘形状匹配定位
class Edge_Match
{

public:
    Edge_Match();

    Edge_Match(const std::vector<std::string>& model_names, int contrast, int min_contrast, int min_contour, 
                int layer_number = 3,  float scale_start = 1.0, float scale_stop = 1.0, float scale_step = 1,
                float angle_start = -45, float angle_stop = 45, int angle_step =  1);

    // 匹配每一个模板，得到每个模板的匹配结果
    void match_models(const cv::Mat& to_match, float min_score, std::map<std::string, cv::Rect>& pattern_rois, 
                      std::map<std::string, std::pair<float, cv::Rect>>& match_results);


    // 输入原图和模板roi及模板文件名称，训练模板并保存
    bool train_shape_model(const cv::Mat& template_image, const cv::Rect& pattern_roi, const std::string& model_name);


    // 根据模板文件名加载匹配模板
    bool load_shape_models(const std::vector<std::string>& model_names);

    // 判断某个模板名是否加载
    bool is_loaded(const std::string& model_name);


    // 设置模板训练参数
    void set_model_thresh(int min_contrast, int contrast, int layer_number = 3, int min_contour = 60);


private:

    std::shared_ptr<Edge_Template_Match> shape_template_match;

};


// 模板灰度相关匹配初定位
double match_template(const cv::Mat& src, const cv::Mat& template_img, cv::Rect process_roi, cv::Rect& match_location);

// 多尺度模板灰度相关匹配定位
double fast_match_template(const cv::Mat& src, const cv::Mat& template_img, cv::Rect process_roi, cv::Rect& match_location);



class Match_Location
{
public:
    Match_Location() { };

    bool apply_location() { };

private:

};

class Segmentation
{
public:
    Segmentation() { };

    bool apply_segmentation() { };

private:

};

class Recognition
{
public:
    Recognition() { };

    bool apply_recognition() { };

private:

};

class Saliency_Detection
{
public:
    Saliency_Detection() { };

    bool apply_detection(const cv::Mat& to_detect, int saliency_thresh) { };

private:

};


}
#endif // NKR_H



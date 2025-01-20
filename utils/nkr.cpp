#include "utils.h"
#include "nkr.h"

namespace nkr
{
    Linemode_Match::Linemode_Match(const std::vector<int>& pyr_stride, const std::vector<float>& angle_range, float angle_step, 
                    const std::vector<float>& scale_range, float scale_step, const std::string& model_path, 
                    const std::vector<std::string>& class_ids, const std::string& template_model_name):
                    linemode_template_match(std::make_shared<Linemode_Template_Match>(pyr_stride, angle_range, angle_step, 
                    scale_range, scale_step, model_path, class_ids, template_model_name)) { }
                        

    Linemode_Match::Linemode_Match(int feature_number, const std::vector<int>& pyr_stride, const std::vector<float>& angle_range, float angle_step, 
                    const std::vector<float>& scale_range, float scale_step, const std::string& model_path, const std::vector<std::string>& class_ids, 
                    const std::string& template_model_name, int weak_thresh, int strong_thresh):
                    linemode_template_match(std::make_shared<Linemode_Template_Match>(feature_number, pyr_stride, angle_range, angle_step, 
                    scale_range, scale_step, model_path, class_ids, template_model_name, weak_thresh, strong_thresh)) { }


    void Linemode_Match::load_model(const std::string& model_path, const std::vector<std::string>& class_ids, 
                                    const std::string& template_model_name)
    {
        linemode_template_match->load_model(model_path, class_ids, template_model_name);
    }

    void Linemode_Match::set_labels(const std::map<int, std::string> labels) 
    {   linemode_template_match->set_labels(labels); }

    // 给定模板图路径读取对应的标签，模板需按 "字符" + "当前字符数量标志".png 例如 10.png 11.png A1.png A2.png
    void Linemode_Match::read_labels(const std::string& template_image_path) 
    {   linemode_template_match->read_labels(template_image_path); }

    // 判断模型是否加载
    bool Linemode_Match::is_loaded(const std::string& class_id) 
    {   return linemode_template_match->is_loaded(class_id); }

    // 加载文件路径下的所有图像训练模型
    bool Linemode_Match::train_model(const std::string& template_image_path, const std::string& model_path, 
                                     const std::string& class_id, const std::string& template_model_name)
    {
        return linemode_template_match->train_model(template_image_path, model_path,
                                                    class_id, template_model_name);
    }

    // 给定图像训练模型
    bool Linemode_Match::train_model(const cv::Mat& template_image, const std::string& model_path, const std::string& class_id, 
                                     const std::string& template_model_name)
    {
        return linemode_template_match->train_model(template_image, model_path,
                                                    class_id, template_model_name);
    }

    // 删除class_id的模型
    bool Linemode_Match::delete_model(const std::vector<std::string>& class_ids) 
    {   return linemode_template_match->delete_model(class_ids); }

    // 形状匹配定位和识别
    bool Linemode_Match::recognize(const cv::Mat& to_match, const std::vector<std::string>& class_ids, int match_similarity_thresh, 
                                   cv::Rect& match_roi, bool pyramid_acc)
    {
        return linemode_template_match->recognize(to_match, class_ids, match_similarity_thresh,
                                                  match_roi, pyramid_acc);
    }

    // 单字符形状匹配识别
    std::string Linemode_Match::recognize(const cv::Mat& to_match, const std::vector<std::string>& class_ids, 
                                          int match_similarity_thresh, bool pyramid_acc)
    {
                
        return linemode_template_match->recognize(to_match, class_ids, match_similarity_thresh,
                                                  pyramid_acc);
    }

    // 字符行形状匹配识别
    std::string Linemode_Match::recognize(const cv::Mat& to_match, const std::vector<std::string>& class_ids, int match_similarity_thresh,
                        int nms_similarity_thresh, float num_iou_thresh, std::vector<cv::Rect>& match_rois, 
                        bool pyramid_acc, unsigned int refine_match, const std::vector<cv::Rect>& mask_roi)
    {
                
        return linemode_template_match->recognize(to_match, class_ids, match_similarity_thresh, 
                                                  nms_similarity_thresh, num_iou_thresh, match_rois,
                                                  pyramid_acc, refine_match, mask_roi);    
    }



    Edge_Match::Edge_Match(): shape_template_match(std::make_shared<Edge_Template_Match>()) { };

    Edge_Match::Edge_Match(const std::vector<std::string>& model_names, int contrast, int min_contrast, int min_contour, 
                           int layer_number,  float scale_start, float scale_stop, float scale_step,
                           float angle_start, float angle_stop, int angle_step):
                           shape_template_match(std::make_shared<Edge_Template_Match>(model_names, contrast, min_contrast,
                           min_contour, layer_number, scale_start, scale_stop, scale_step, angle_start, 
                           angle_stop, angle_step)) { };

    // 匹配每一个模板，得到每个模板的匹配结果
    void Edge_Match::match_models(const cv::Mat& to_match, float min_score, std::map<std::string, cv::Rect>& pattern_rois, 
                      std::map<std::string, std::pair<float, cv::Rect>>& match_results)
    {
        shape_template_match->match_models(to_match, min_score, pattern_rois, match_results);
    }

    // 输入原图和模板roi及模板文件名称，训练模板并保存
    bool Edge_Match::train_shape_model(const cv::Mat& template_image, const cv::Rect& pattern_roi, const std::string& model_name)
    {
        shape_template_match->train_shape_model(template_image, pattern_roi, model_name);
    }

    // 根据模板文件名加载匹配模板
    bool Edge_Match::load_shape_models(const std::vector<std::string>& model_names)
    {
        shape_template_match->load_shape_models(model_names);
    }
    // 判断某个模板名是否加载
    bool Edge_Match::is_loaded(const std::string& model_name)
    {
        shape_template_match->is_loaded(model_name);
    }

    // 设置模板训练参数
    void Edge_Match::set_model_thresh(int min_contrast, int contrast, int layer_number, int min_contour) 
    { 
        shape_template_match->set_model_thresh(min_contrast, contrast, layer_number, min_contour);
    }



}
#include <algorithm>
#include <functional>
#include <utility>
#include <vector>
#include <numeric>

#include "caffe/layer.hpp"
#include "caffe/util/io.hpp"
#include "caffe/util/math_functions.hpp"
#include "caffe/layers/create_mask_vector_layer.hpp"

namespace caffe {

template <typename Dtype>
void CreateMaskVectorLayer<Dtype>::LayerSetUp(
  const vector<Blob<Dtype>*>& bottom, const vector<Blob<Dtype>*>& top) {
    num_label_ = this->layer_param_.create_mask_vector_param().num_label();
}

template <typename Dtype>
void CreateMaskVectorLayer<Dtype>::Reshape(
  const vector<Blob<Dtype>*>& bottom, const vector<Blob<Dtype>*>& top) {
  CHECK_EQ(bottom[0]->channels(), 1)
    << "The bottom channels should be 1.";
  //top[0]->Reshape(bottom[0]->num(), 1, 1, num_joint_ * 2);  
  top[0]->Reshape(bottom[0]->num(), num_label_, 1, 1); 
}
  

template <typename Dtype>
void CreateMaskVectorLayer<Dtype>::Forward_cpu(const vector<Blob<Dtype>*>& bottom,
    const vector<Blob<Dtype>*>& top) {
  const Dtype* bottom_data = bottom[0]->cpu_data();
  Dtype* top_data = top[0]->mutable_cpu_data();
  int num = bottom[0]->num();
  int height = bottom[0]->height();
  int width = bottom[0]->width();

 // std::vector<Dtype> label_vector[num_label_];
  std::vector<int > sum_vector[num_label_];
  int cls_;
  switch (this->layer_param_.create_mask_vector_param().pool()) 
  {
  case CreateMaskVectorParameter_PoolMethod_AVE:
     for (int i = 0; i < num; ++i) 
     {
       for (int h = 0; h < height; ++h) 
       {
         for (int w = 0; w < width; ++w)
         {
           cls_ =  bottom_data[h * width + w];  // bian li MAT all point ,cls_ is the GT of each pixel
           if (cls_ >= 0 && cls_ < num_label_) 
           {
              sum_vector[cls_].push_back(1);
              //  label_vector[cls_]= Dtype(0);
           }
         }
       }
    
       for (int w = 0; w < num_label_; ++w) {
       // top_data[w] = label_vector[cls_];
	  top_data[w] = 0;
       }
       for (int n = 0; n < num_label_; n++) {
	  if (sum_vector[n].size() > 0) {
          double ave = std::accumulate(sum_vector[n].begin(), sum_vector[n].end(), 0.0)
                                      / (width * height);
          // LOG(INFO) << "ave: " << ave;
          top_data[n] = Dtype(ave);
          } 
       }
       bottom_data += bottom[0]->offset(1);
       top_data += top[0]->offset(1);
    }
    break;
  case CreateMaskVectorParameter_PoolMethod_MAX:
     for (int i = 0; i < num; ++i) 
     {
       for (int h = 0; h < height; ++h) 
       {
         for (int w = 0; w < width; ++w)
         {
           cls_ =  bottom_data[h * width + w];  // bian li MAT all point ,cls_ is the GT of each pixel
           if (cls_ >= 0 && cls_ < num_label_) 
           {
              sum_vector[cls_].push_back(1);
              //  label_vector[cls_]= Dtype(0);
           }
         }
       }
       for (int w = 0; w < num_label_; ++w) {
       // top_data[w] = label_vector[cls_];
	  top_data[w] = 0;
       }
       for (int n = 0; n < num_label_; n++) {
	  if (sum_vector[n].size() > 0) {
          top_data[n] = Dtype(1);
          } 
       }
       bottom_data += bottom[0]->offset(1);
       top_data += top[0]->offset(1);
     }
    break;
  default:
    LOG(FATAL) << "Unknown pooling method.";   
  }
}
INSTANTIATE_CLASS(CreateMaskVectorLayer);
REGISTER_LAYER_CLASS(CreateMaskVector);

}  // namespace caffe

## Trusted Guidance Pyramid Network for Human Parsing
Xianghui Luo, Zhuo Su, Jiaming Guo, Gengwei Zhang, Xiangjian He, "Trusted Guidance Pyramid Network for Human Parsing", ACM Multimedia 2018.

### Introduction


Human parsing, which segments a human-centric image into pixel-wise categorization, has a wide range of applications. However, none of the existing methods can productively solve the issue of label parsing fragmentation due to confused and complicated annotations. In this paper, we propose a novel Trusted Guidance Pyramid Network (TGPNet) to address this limitation. Based on a pyramid architecture, we design a Pyramid Residual Pooling (PRP) module setting at the end of a bottom-up approach to capture both global and local level context. In the top-down approach, we propose a Trusted Guidance Multi-scale Supervision (TGMS) that efficiently integrates and supervises multi-scale contextual information. Furthermore, we present a simple yet powerful Trusted Guidance Framework (TGF) which imposes global-level semantics into parsing results directly without extra ground truth labels in model training. Extensive experiments on two public human parsing benchmarks well demonstrate that our TGPNet has a strong ability in solving label parsing fragmentation problem and has an obtained improvement than other methods.Our TGPNet are trained and tested based on the[Caffe](http://caffe.berkeleyvision.org).
Please consult and consider citing the following papers:
@InProceedings{Luo_2018_TGPnet,
      author = {Luo, Xianghui and Su, Zhuo and Guo, Jiaming and Zhang, Gengwei and He, Xiangjian},
      title = {Trusted Guidance Pyramid Network for Human Parsing},
      booktitle = {The 2018 ACM on Multimedia Conference},
      year = {2018}
    }
### Dataset
The valuation of our network performance is conducted on the ATR dataset and the Fashion clothing dataset. The ATR dataset is available at [here](https://github.com/lemondan/HumanParsing-Dataset).
### Pre-trained models
We have released our trained models with best performance at [baidu drive](https://pan.baidu.com/s/13nrS1NE3zA0qsUkJYYRWcA) passwd: uaqg.

### Train and test
1. Download the dataset or prepare your own data.
2. Put the images(*,jpg) and segmentations(*.png) into TGPnet/human/data/train_images. You can run the provided MATLAB script, resize_image_and_label.m to change the image and label resolution according to your needs.
3. Put the train, val, test lists into TGPnet/human/list. Each type contains a list for path and a list for id (e.g., train.txt and train_id.txt) 
4. Download the pre-trained model and put it into TGPnet/human/model/TGPnet/. You can also refer [DeepLab](https://bitbucket.org/aquariusjay/deeplab-public-ver2) for more models. 
5. Set up your init.caffemodel before training and test.caffemodel before testing. You can simply use a soft link.
6. The prototxt files for network config are saved in TGPnet/human/config
7. In run_parsing.sh, you can set the value of RUN_TRAIN and RUN_TEST to train or test the model.In addition, you have to change the link according to your own path.
8. After you run TEST, the computed features will be saved in TGPnet/human/features. You can run the provided MATLAB script, show.m to generate visualizable results. 

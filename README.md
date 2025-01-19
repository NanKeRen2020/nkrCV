About
=====

This project provide some nice and fast computer vision methods in C++ for industrial vision.

More good methods and their documents is coming soon ...

Note: nkrcv just abbr. for NanKeRen Computer Vision.


Environments
=============

Ubuntu1604  OpenCV3.4.x 

sudo apt install libeigen3-dev


Build & Usage
==============

cd nkrcv

mkdir build
cmake ..
make -j8

./test_match_location path_to/datas/row_text_originals0 path_to/datas/ path_to/datas/edges

./test_geo_match -t Template.jpg -h 100 -l 10 -s Search1.jpg -m 0.7 -g 0.5

recognize the location of chars of image

![image](https://github.com/NanKeRen2020/linemode_template_match/blob/main/datas/to_match0.png)

recognize the location of chars of image

![image](https://github.com/NanKeRen2020/linemode_template_match/blob/main/datas/to_match1.png)

match the location of the template of image

![image](https://github.com/NanKeRen2020/linemode_template_match/blob/main/datas/locate_text_area.png)




References
==========

[1] https://github.com/meiqua/shape_based_matching.

[2] S. Hinterstoisser et al. Gradient Response Maps for Real-Time Detection of Textureless Objects. 

IEEE Transactions on Pattern Analysis and Machine Intelligence, vol. 34, no. 5, pp. 876-888, May 2012.

[3]. https://www.codeproject.com/Articles/99457/Edge-Based-Template-Matching.



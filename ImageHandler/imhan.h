/*!
 * @file    imhan.h
 * @brief   �摜�����N���X
 * @details �摜�f�[�^���i�[���A�����摜��G�b�W�摜��@par
 *           �̉摜�������s���B�f�[�^�͉摜��O���t�Ƃ���@par
 *           �\�����邱�Ƃ��o����B
 * @date    201?/0?/??
 */
#pragma once
#include <iostream>
#include <string>
#include <deque>
#include <memory>
#include <map>
#include <opencv2\opencv.hpp>
#include "singleImageHandler.h"
//#include "multiImageHandler.h"
#include "imageHandler.h"
#include "imhan_operators.h"



std::shared_ptr<imageHandler>  imhan(cv::Mat &m);
std::shared_ptr<imageHandler>  imhan(std::map<std::string, cv::Mat> &map);
std::shared_ptr<imageHandler>  imhan(std::pair<std::string, cv::Mat> &pair);
std::shared_ptr<imageHandler>  imhan(std::string path, bool isDir=false);


//class imhan{
//public:
//    imhan(cv::Mat &m){
//        this = imageHandler(m);
//    }

//    imageHandler img;

//};

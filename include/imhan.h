/*!
 * @file    imhan.h
 * @brief   画像処理クラス
 * @details 画像データを格納し、差分画像やエッジ画像等@par
 *           の画像処理を行う。データは画像やグラフとして@par
 *           表示することが出来る。
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
std::shared_ptr<imageHandler>  imhan(std::string name);


//class imhan{
//public:
//    imhan(cv::Mat &m){
//        this = imageHandler(m);
//    }

//    imageHandler img;

//};

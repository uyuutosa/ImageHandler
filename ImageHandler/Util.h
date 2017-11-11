#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <opencv2\opencv.hpp>
#include <fstream>
#include <Windows.h>
#include <experimental/filesystem>

std::vector<cv::Mat> loadImagesForColorCorrector(int imageNum, int interval);

std::vector<cv::Mat> loadImagesForAngleCorrector();

std::vector<std::string> fileList(std::string dirName, std::string extension, bool isRec);

bool isExpansion(std::string path, std::string expansion);

std::vector<std::string> walk(std::string dirName, std::string extension);

std::vector<std::string> split(const std::string &str, char sep);

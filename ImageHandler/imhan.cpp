//#include "stdafx.h"
#include "imhan.h"


std::shared_ptr<imageHandler> imhan(cv::Mat &m){
    std::shared_ptr<imageHandler> ptr(new singleImageHandler(m));
    return ptr;
}

std::shared_ptr<imageHandler> imhan(std::map<std::string, cv::Mat> &map){
    std::shared_ptr<imageHandler> ptr(new multiImageHandler(map));
    return ptr;
}

std::shared_ptr<imageHandler> imhan(std::pair<std::string, cv::Mat> &pair){
    std::shared_ptr<imageHandler> ptr(new singleImageHandler(pair));
    return ptr;
}

std::shared_ptr<imageHandler> imhan(std::string name){
    try{
    	std::shared_ptr<imageHandler> ptr;
    	//if(util::flst(name)[0].find("DIR") == std::string::npos)
    	//    ptr = std::make_shared<singleImageHandler>(name);
    	//else{
        //    std::deque<std::string> fileList(util::flst(name+"\\*"));
    	//    ptr = std::make_shared<multiImageHandler>(name);
        //}
    	return ptr;
    } catch(std::string error){
        return std::shared_ptr<imageHandler>();
    } 
}
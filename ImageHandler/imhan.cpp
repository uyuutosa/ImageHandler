//#include "stdafx.h"
#include "imhan.h"
#include "Util.h"


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

std::shared_ptr<imageHandler> imhan(std::string path, bool isDir){
    try{
    	std::shared_ptr<imageHandler> ptr;
		std::string tmp = std::string(path);
    	if(!isDir)
    	//if(util::flst(path)[0].find("DIR") == std::string::npos)
    	    ptr = std::make_shared<singleImageHandler>(path);
    	else{
//            std::deque<std::string> fileList(util::flst(path+"\\*"));
//			auto fileList = walk(path, "");
    	    multiImageHandler a(path);
    	    ptr = std::make_shared<multiImageHandler>(a);
        }
    	return ptr;
    } catch(std::string error){
        return std::shared_ptr<imageHandler>();
    } 
}
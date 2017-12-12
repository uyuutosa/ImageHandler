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

std::shared_ptr<imageHandler> imhan(std::string path, bool isDir, int movieSize){
    try{
    	std::shared_ptr<imageHandler> ptr;
		std::string tmp = std::string(path);
		std::string ext(getExtension(path));
		if (ext == "mp4" || ext == "MP4") {
			cv::VideoCapture cap(path);
			std::vector<cv::Mat> mlst;
			int cnt(0);
			for (bool isContinue = true; isContinue;) {
				cv::Mat m;
				if (!cap.read(m) || cnt == movieSize)
					break;

				mlst.push_back(m);
				cnt++;
		
			}
    		ptr = std::make_shared<multiImageHandler>(mlst);
		} else if(!isDir)
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
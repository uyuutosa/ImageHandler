#include "Util.h"


std::vector<cv::Mat> loadImagesForColorCorrector(int imageNum, int interval) {
	cv::VideoCapture cap("data/C0033.MP4");
	std::vector<cv::Mat> ret(imageNum);

	//cv::namedWindow("hoge", CV_WINDOW_NORMAL);
	int imageCnt(0);
	while (1) {
		cap.set(CV_CAP_PROP_POS_FRAMES, imageCnt * interval);
		cv::Mat frame;
		cap >> frame;
		if (frame.empty() || cv::waitKey(30) >= 0 ||
			cap.get(CV_CAP_PROP_POS_AVI_RATIO) == 1) {
			break;
		}
		std::stringstream ss;
		ss << "img_fr_" << imageCnt * interval << "_No_" << imageCnt << ".jpg";
		cv::imwrite(ss.str(), frame);
		ret[imageCnt] = frame;
		imageCnt++;

		if (imageCnt == imageNum)
			break;
	}
	return ret;
}

std::vector<cv::Mat> loadImagesForAngleCorrector() {

	return std::vector<cv::Mat>();
}

std::vector<std::string> fileList(std::string dirName, std::string extension, bool isRec) {
	HANDLE hFind;
	WIN32_FIND_DATA win32fd;
	std::vector<std::string> fileNames;

	// set extention
	std::string searchName = dirName + "\\*." + extension;

	hFind = FindFirstFile(searchName.c_str(), &win32fd);

	if (hFind == INVALID_HANDLE_VALUE) {
		throw std::runtime_error("file not found");
	}

	do {
		if (win32fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			if (isRec) {

			}
			win32fd.cFileName;
		}
		else {
			fileNames.push_back(win32fd.cFileName);
			printf("%s\n", fileNames.back().c_str());
		}
	} while (FindNextFile(hFind, &win32fd));

	FindClose(hFind);

	return fileNames;
}

bool isExpansion(std::string path, std::string expansion) {
	return path.rfind(expansion) != std::string::npos;
}

std::vector<std::string> walk(std::string dirName, std::string expansion) {
	std::vector<std::string> ret;
	for(auto a: std::experimental::filesystem::recursive_directory_iterator(dirName)) {
		std::stringstream ss;
		ss << a;
		if(!std::experimental::filesystem::is_directory(a))
			if (isExpansion(ss.str(), expansion)) {
				ret.push_back(ss.str());
			}
	}
	return ret;
}

std::vector<std::string> split(const std::string &str, char sep)
{
    std::vector<std::string> v;
    std::stringstream ss(str);
    std::string buffer;
    while( std::getline(ss, buffer, sep) ) {
        v.push_back(buffer);
    }
    return v;
}

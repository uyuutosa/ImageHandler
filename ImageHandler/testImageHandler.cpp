#include<opencv2\opencv.hpp>
#include<imhan.h>


int main() {
	cv::Mat m = cv::imread("Corvette.jpg");
	auto obj = imhan(m);
	obj->canny()->dump("", "Corvette_canny.jpg");
}
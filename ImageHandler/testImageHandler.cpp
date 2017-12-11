#include<opencv2\opencv.hpp>
#include<imhan.h>
#include <iostream>


int main() {
	
	//for (auto a : walk("C:/Users/sleep/ownCloud/share/tmp/North", ""))
	//	std::cout << a << std::endl;

	//auto obj = imhan(".", true);
	//auto obj = imhan("C:/Users/sleep/ownCloud/share/tmp/North", true);
	auto obj = imhan("testMov.mp4", false);
	//obj->dump("", "Corvette_canny.jpg"); //canny
	obj->view("hello", 1, true);
}
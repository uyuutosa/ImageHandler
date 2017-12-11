#include<opencv2\opencv.hpp>
#include<imhan.h>
#include <iostream>


int main() {
	
	//for (auto a : walk("C:/Users/sleep/ownCloud/share/tmp/North", ""))
	//	std::cout << a << std::endl;

	//auto obj = imhan(".", true);
	auto obj = imhan("C:/Users/sleep/ownCloud/share/tmp/North", true);
	//obj->dump("", "Corvette_canny.jpg"); //canny
	obj->canny()->view();
}
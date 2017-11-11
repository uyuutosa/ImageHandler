//#include "stdafx.h"
#include "imageHandler.h"
// #pragma optimize("",off)

imageHandler::imageHandler(){}

imageHandler::imageHandler(cv::Mat input_m, double input_param, cv::Rect input_rect):
    m(input_m), m_width(input_m.cols), m_height(input_m.rows), param(input_param), rect(input_rect)
{
    initializePointers();
}

imageHandler::imageHandler(cv::Mat input_m, parameters input_params, cv::Rect input_rect):
    m(input_m), m_width(input_m.cols), m_height(input_m.rows), param(input_params), rect(input_rect)
{
    initializePointers();
}
imageHandler::imageHandler(std::pair<std::string, cv::Mat> &input_pair):
    name(input_pair.first), 
    m(input_pair.second) 
{
    initializePointers();
}

imageHandler::imageHandler(std::map<std::string, cv::Mat> &input_map)
{
    initializePointers();
        
    
}

// 初期化関数

void imageHandler::initializePointers(){
    param.setOr();
}


std::shared_ptr<imageHandler> imageHandler::convertTo(int type){
    return std::shared_ptr<imageHandler>();
}

std::shared_ptr<imageHandler> imageHandler::cvtColor(int type){
    return std::shared_ptr<imageHandler>();
}

std::shared_ptr<imageHandler> imageHandler::erode(cv::InputArray  &kernel,
                                    			        cv::Point &anchor,
                                    			        int iteration,
                                    			        int borderType,
                                    			        const cv::Scalar
                                    			          &borderValue
                                    			        ){
    return std::shared_ptr<imageHandler>(new imageHandler());
}

std::shared_ptr<imageHandler> imageHandler::RGB2Gray(){
    return std::shared_ptr<imageHandler>();
}

std::shared_ptr<imageHandler> imageHandler::abs(){
    return std::shared_ptr<imageHandler>();
}

std::shared_ptr<imageHandler> imageHandler::inv(){
    return std::shared_ptr<imageHandler>();
}

std::shared_ptr<imageHandler> imageHandler::mult(std::shared_ptr<imageHandler> &obj){
    return std::shared_ptr<imageHandler>();
}
std::shared_ptr<imageHandler> imageHandler::aveImg(){
    return std::shared_ptr<imageHandler>();
}

std::shared_ptr<imageHandler> imageHandler::minImg(){
    return std::shared_ptr<imageHandler>();
}

std::shared_ptr<imageHandler> imageHandler::maxImg(){
    return std::shared_ptr<imageHandler>();
}

std::shared_ptr<imageHandler> imageHandler::isValueAmountForMoreThan(double thresh, double area){
    return std::shared_ptr<imageHandler>();
}

std::shared_ptr<imageHandler> imageHandler::genComatrix(int divNum, int kaityouNum){
    return std::shared_ptr<imageHandler>();
}

std::shared_ptr<imageHandler> imageHandler::calcEnergy(int divNum, int kaityouNum){
    return std::shared_ptr<imageHandler>();
}

std::shared_ptr<imageHandler> imageHandler::calcContrast(int divNum, int kaityouNum){
    return std::shared_ptr<imageHandler>();
}

std::shared_ptr<imageHandler> imageHandler::calcCorrelation(int divNum, int kaityouNum){
    return std::shared_ptr<imageHandler>();
}

std::shared_ptr<imageHandler> imageHandler::calcVariance(int divNum, int kaityouNum){
    return std::shared_ptr<imageHandler>();
}
    
std::shared_ptr<imageHandler> imageHandler::calcEntropy(int divNum, int kaityouNum){
    return std::shared_ptr<imageHandler>();
}

std::shared_ptr<imageHandler> imageHandler::calcSumEntropy(int divNum, int kaityouNum){
    return std::shared_ptr<imageHandler>();
}

std::shared_ptr<imageHandler> imageHandler::calcIDM(int divNum, int kaityouNum){
    return std::shared_ptr<imageHandler>();
}


std::shared_ptr<imageHandler> imageHandler::nearSimilar(int n_row, int n_col){
    return std::shared_ptr<imageHandler>();
}

void imageHandler::push_back(cv::Mat &input_m){
}

void imageHandler::pop_front(){
}

void imageHandler::push(cv::Mat &input_m, int th_num){
}

void imageHandler::mgrid(int iMin, int iMax, int iStep,
           int jMin, int jMax, int jStep){
}

std::shared_ptr<imageHandler> imageHandler::gridImage(int n_row, int n_col){
    return std::shared_ptr<imageHandler>();
}

void imageHandler::readImage(std::string &input_name){
}

std::shared_ptr<imageHandler> imageHandler::gridMean(int n_row, int n_col){
    return std::shared_ptr<imageHandler>();
}

void imageHandler::drawGridRect(int n_row, int n_col){
}

void imageHandler::getRect(int n_row, int n_col){
}

std::shared_ptr<imageHandler> imageHandler::canny(int threshold1, 
                                                  int threshold2){
    return std::shared_ptr<imageHandler>();
}

std::shared_ptr<imageHandler> imageHandler::distanceOfCircleEdge(
                            int threshold1, 
                            int threshold2,
                            int radius,
                            int n_div,
                            bool isDraw){
    return std::shared_ptr<imageHandler>();
}


std::shared_ptr<imageHandler> imageHandler::resize(int height, 
                                                   int width){
    return std::shared_ptr<imageHandler>();
}

std::shared_ptr<imageHandler> imageHandler::expand(int height, 
                                                   int width, 
                                                   bool drawValue){
    return std::shared_ptr<imageHandler>();
}

std::shared_ptr<imageHandler> imageHandler::pildown(int height, 
                                                    int width, 
                                                    int n_div, 
                                                    bool drawValue){
    return std::shared_ptr<imageHandler>();
}

std::shared_ptr<imageHandler> imageHandler::genParamMap(int n_row, int n_col){
    return std::shared_ptr<imageHandler>();
}

std::shared_ptr<imageHandler> imageHandler::normalize(int minVal, 
                                        int maxVal,
                                        int bitDepth){

    return std::shared_ptr<imageHandler>();
}                         

std::shared_ptr<imageHandler> imageHandler::normParam(
        double minVal1, 
        double maxVal1,
        double minVal2, 
        double maxVal2){
    return std::shared_ptr<imageHandler>();
}

std::shared_ptr<imageHandler> imageHandler::threshold(
                                        double thresh, 
                                        double maxVal, 
                                        int    threshType){
    return std::shared_ptr<imageHandler>();
}

                         
std::shared_ptr<imageHandler> imageHandler::paintMask(
    std::shared_ptr<imageHandler> &obj,
	int thresh){
    return std::shared_ptr<imageHandler>();
}                         

std::shared_ptr<imageHandler> imageHandler::paintMask(
    std::shared_ptr<imageHandler> &obj){
    return std::shared_ptr<imageHandler>();
}


std::shared_ptr<imageHandler> imageHandler::cpyParam(std::shared_ptr<imageHandler> &obj){
    return std::shared_ptr<imageHandler>();
}

std::shared_ptr<imageHandler> imageHandler::interp(std::shared_ptr<imageHandler> &obj){
    return std::shared_ptr<imageHandler>();
}


std::shared_ptr<imageHandler> imageHandler::setParam(double input_param){
    return std::shared_ptr<imageHandler>();
}

std::shared_ptr<imageHandler> imageHandler::setParam(parameters input_param){
    return std::shared_ptr<imageHandler>();
}

std::shared_ptr<imageHandler> imageHandler::extractValidArea(std::shared_ptr<imageHandler> &obj){
    return std::shared_ptr<imageHandler>();
}
                          
void imageHandler::dump(std::string dirPath,
                        std::string fileName,
                        std::string expand){
    
}

std::shared_ptr<imageHandler> imageHandler::sortForQue(){
    return std::shared_ptr<imageHandler>();
}

std::shared_ptr<imageHandler> imageHandler::sortForQueIdx(){
    return std::shared_ptr<imageHandler>();
}

std::shared_ptr<imageHandler> imageHandler::sortForQueWithObj(
    std::shared_ptr<imageHandler> obj){
    return std::shared_ptr<imageHandler>();
}

std::shared_ptr<imageHandler> imageHandler::getBoundingBoxInfo(){
    return std::shared_ptr<imageHandler>();
}

std::shared_ptr<imageHandler> imageHandler::rectangle(
        cv::Scalar& color, 
        int thickness, 
        int lineType, 
        cv::Rect input_rect, 
        int shift
        ){
    return std::shared_ptr<imageHandler>();
}

std::shared_ptr<imageHandler> imageHandler::checkValidArea(std::shared_ptr<imageHandler> &obj){
    return std::shared_ptr<imageHandler>();
}

std::shared_ptr<imageHandler> imageHandler::clip(std::shared_ptr<imageHandler> &obj){
    return std::shared_ptr<imageHandler>();
}

std::shared_ptr<imageHandler> imageHandler::clip(cv::Rect &input_rect, bool inv){
    return std::shared_ptr<imageHandler>();
}

std::shared_ptr<imageHandler> imageHandler::superImpose(int thresh){
    return std::shared_ptr<imageHandler>();
}
//std::shared_ptr<imageHandler> imageHandler::clip(cv::Rect &input_rect){
//    return std::shared_ptr<imageHandler>();
//}

// 比較用関数。
parameters& imageHandler::getRefofParam(){
    return param;
}

bool imageHandler::any(){
    return false;
}

bool imageHandler::all(){
    return false;
}

// 画用関数

void imageHandler::view(std::string input_name, int wTime){
}

void imageHandler::histView(
     std::string input_name, 
     int binNum, 
     int xMin, 
     int xMax,
     int yMin,
     int yMax){
}

std::shared_ptr<imageHandler> imageHandler::drawOuterFrame(
   cv::Scalar &color,
   int thickness, 
   int lineType, 
   int shift){
    return std::shared_ptr<imageHandler>();
}

std::shared_ptr<imageHandler> imageHandler::labeling(bool isMulti, int threshBreakNum,int times){
    return std::shared_ptr<imageHandler>();
}

std::shared_ptr<imageHandler> imageHandler::putCenterParam(
    int fontFace, 
	cv::Scalar color, 
	int thickness){
    return std::shared_ptr<imageHandler>();
}


std::shared_ptr<imageHandler> imageHandler::drawOuterFrameAroundObjects(){
    return std::shared_ptr<imageHandler>();
}

std::shared_ptr<imageHandler> imageHandler::fillObjects(cv::Mat mask, cv::Scalar &color){
    return std::shared_ptr<imageHandler>();
}


// 画像処理後をした後に表示する高級関数群。
   
void imageHandler::viewGridedImg(std::string input_name, int wTime){
}

void imageHandler::viewGridedParam(std::string input_name){
}

void imageHandler::resizeView(int width, int height){
}

void imageHandler::expandView(int width, int height){
}

void imageHandler::pildownView(int width, int height, int n_div, bool drawValue){
}

int imageHandler::size(){
    return 0;
}


std::shared_ptr<imageHandler> imageHandler::stichImg(int n_row, int n_col){
    return std::shared_ptr<imageHandler>();    
}

// 演算子オーバロード

std::shared_ptr<imageHandler> imageHandler::operator+(
        const std::shared_ptr<imageHandler> &obj){
    return std::shared_ptr<imageHandler>();
}

std::shared_ptr<imageHandler>  imageHandler::operator-(
        std::shared_ptr<imageHandler> obj){
    return std::shared_ptr<imageHandler>();
}

std::shared_ptr<imageHandler>  imageHandler::operator*(
        std::shared_ptr<imageHandler> obj){
    return std::shared_ptr<imageHandler>();
}

std::shared_ptr<imageHandler>  imageHandler::operator/(
        std::shared_ptr<imageHandler> obj){
    return std::shared_ptr<imageHandler>();
}

std::shared_ptr<imageHandler>  imageHandler::operator^(
        std::shared_ptr<imageHandler> obj){
    return std::shared_ptr<imageHandler>();
}

std::shared_ptr<imageHandler> imageHandler::operator>(
    const std::shared_ptr<imageHandler> &obj
    ){
    return std::shared_ptr<imageHandler>();
}

std::shared_ptr<imageHandler> imageHandler::operator<(
    const std::shared_ptr<imageHandler> &obj
    ){
    return std::shared_ptr<imageHandler>();
}

std::shared_ptr<imageHandler> imageHandler::operator>=(
    const std::shared_ptr<imageHandler> &obj
    ){
    return std::shared_ptr<imageHandler>();
}

std::shared_ptr<imageHandler> imageHandler::operator<=(
    const std::shared_ptr<imageHandler> &obj){
    return std::shared_ptr<imageHandler>();
}

std::shared_ptr<imageHandler> imageHandler::operator==(
    const std::shared_ptr<imageHandler> &obj){
    return std::shared_ptr<imageHandler>();
}

std::shared_ptr<imageHandler> imageHandler::operator&&(
    const std::shared_ptr<imageHandler> &obj){
    return std::shared_ptr<imageHandler>();
}

std::shared_ptr<imageHandler> imageHandler::operator>(
    const double &val
    ){
    return std::shared_ptr<imageHandler>();
}

std::shared_ptr<imageHandler> imageHandler::operator<(
    const double &val
    ){
    return std::shared_ptr<imageHandler>();
}

std::shared_ptr<imageHandler> imageHandler::operator>=(
    const double &val
    ){
    return std::shared_ptr<imageHandler>();
}

std::shared_ptr<imageHandler> imageHandler::operator<=(
    const double &val
    ){
    return std::shared_ptr<imageHandler>();
}

std::shared_ptr<imageHandler> imageHandler::operator==(
    const double &val
    ){
    return std::shared_ptr<imageHandler>();
}

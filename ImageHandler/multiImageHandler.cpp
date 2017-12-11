//#include "stdafx.h"
#include "multiImageHandler.h"

// #pragma optimize("", off)
multiImageHandler::multiImageHandler(std::vector<std::vector<double> > &v){}

multiImageHandler::multiImageHandler(std::map<std::string, cv::Mat> &input_map){
    for(auto a: input_map){
        std::pair<std::string, cv::Mat> b; // aのstd::stringはconstがついていたため直接代入できなかった。
        b.first  = a.first;                // ←要検討。
        b.second = a.second;
        m_lst.push_back(std::shared_ptr<imageHandler>(new singleImageHandler(b)));  
    }
}

    /*!
     * @brief     コンストラクタ(std::deque<cv::Mat>用)
     * @details   入力画像が格納されたコンテナを受け取る。
     * @param[in] input_obj 入力画像が格納されたコンテナ。
     */
multiImageHandler::multiImageHandler(std::deque<std::shared_ptr<imageHandler> > input_obj)
     {
        m_lst    = input_obj;
        if(m_lst.size()){
        	m_height = m_lst[0]->m.rows;
        	m_width  = m_lst[0]->m.cols;
        }
    }

    /*!
     * @brief     コンストラクタ(フォルダ名)
     * @details   指定フォルダに格納されている画像を
     *            cv::imread()で取得する。
     * @param[in] input_name フォルダ名。
     */
multiImageHandler::multiImageHandler(std::string input_name){

    
    try{
		for (auto a : walk(input_name, "")){
        //for (auto a: util::flst(input_name+"\\*")){
            
            //std::cout << a.find("DIR")<< std::endl;
            //if(a.find("DIR") != std::string::npos) 
            //    continue;
    	    m_lst.push_back(std::shared_ptr<singleImageHandler>
                           (new singleImageHandler(a)));
    	}
    } catch(std::string error){
        std::cerr << error << std::endl;
        
    }
}


void multiImageHandler::initializePointers(){
}

std::shared_ptr<imageHandler> multiImageHandler::convertTo(int type){
    std::deque<std::shared_ptr<imageHandler> > ret; 
    for (int i=0; i<m_lst.size(); i++){
        ret.push_back(m_lst[i]->convertTo(type));
    }
    return std::shared_ptr<imageHandler>(new multiImageHandler(ret));
}

std::shared_ptr<imageHandler> multiImageHandler::cvtColor(int type){
    std::deque<std::shared_ptr<imageHandler> > ret; 
    for (int i=0; i<m_lst.size(); i++){
        ret.push_back(m_lst[i]->cvtColor(type));
    }
    return std::shared_ptr<imageHandler>(new multiImageHandler(ret));
}

std::shared_ptr<imageHandler> multiImageHandler::erode(cv::InputArray &kernel,
                                                       cv::Point &anchor,
                                                       int iteration,
                                                       int borderType,
                                                       const cv::Scalar
                                                      &borderValue
                                                       ){
    std::deque<std::shared_ptr<imageHandler> > ret; 
    for (int i=0; i<m_lst.size(); i++){
        ret.push_back(m_lst[i]->erode(kernel, anchor, iteration, borderType, borderValue));
    }
    return std::shared_ptr<imageHandler>(new multiImageHandler(ret));
}

std::shared_ptr<imageHandler> multiImageHandler::RGB2Gray(){
    std::deque<std::shared_ptr<imageHandler> > ret; 
    for (int i=0; i<m_lst.size(); i++){
        ret.push_back(m_lst[i]->RGB2Gray());
    }
    return std::shared_ptr<imageHandler>(new multiImageHandler(ret));
}

std::shared_ptr<imageHandler> multiImageHandler::abs(){
    std::deque<std::shared_ptr<imageHandler> > ret; 
    for (int i=0; i<m_lst.size(); i++){
        ret.push_back(m_lst[i]->abs());
    }
    return std::shared_ptr<imageHandler>(new multiImageHandler(ret));
}

std::shared_ptr<imageHandler> multiImageHandler::inv(){
    std::deque<std::shared_ptr<imageHandler> > ret; 
    for (int i=0; i<m_lst.size(); i++){
        ret.push_back(m_lst[i]->inv());
    }
    return std::shared_ptr<imageHandler>(new multiImageHandler(ret));
}

std::shared_ptr<imageHandler> multiImageHandler::mult(std::shared_ptr<imageHandler> &obj){
    std::deque<std::shared_ptr<imageHandler> > ret; 
    for (int i=0; i<m_lst.size(); i++){
        ret.push_back(m_lst[i]->mult(obj));
    }
    return std::shared_ptr<imageHandler>(new multiImageHandler(ret));
}

std::shared_ptr<imageHandler> multiImageHandler::aveImg(){
    std::deque<std::shared_ptr<imageHandler> > ret; 
    for (int i=0; i<m_lst.size(); i++){
        ret.push_back(m_lst[i]->aveImg());
    }
    return std::shared_ptr<imageHandler>(new multiImageHandler(ret));
}

std::shared_ptr<imageHandler> multiImageHandler::minImg(){
    std::deque<std::shared_ptr<imageHandler> > ret; 
    for (int i=0; i<m_lst.size(); i++){
        ret.push_back(m_lst[i]->minImg());
    }
    return std::shared_ptr<imageHandler>(new multiImageHandler(ret));
}

std::shared_ptr<imageHandler> multiImageHandler::maxImg(){
    std::deque<std::shared_ptr<imageHandler> > ret; 
    for (int i=0; i<m_lst.size(); i++){
        ret.push_back(m_lst[i]->maxImg());
    }
    return std::shared_ptr<imageHandler>(new multiImageHandler(ret));
}

std::shared_ptr<imageHandler> multiImageHandler::isValueAmountForMoreThan(double th_val, double th_area){
    std::deque<std::shared_ptr<imageHandler> > ret; 
    for (int i=0; i<m_lst.size(); i++){
        ret.push_back(m_lst[i]->isValueAmountForMoreThan(th_val, th_area));
    }
    return std::shared_ptr<imageHandler>(new multiImageHandler(ret));
}

std::shared_ptr<imageHandler> multiImageHandler::genComatrix(int divNum, int kaityouNum){
    std::deque<std::shared_ptr<imageHandler> > ret; 
    for (int i=0; i<m_lst.size(); i++){
        ret.push_back(m_lst[i]->genComatrix(divNum, kaityouNum));
    }
    return std::shared_ptr<imageHandler>(new multiImageHandler(ret));
}

std::shared_ptr<imageHandler> multiImageHandler::calcEnergy(int divNum, int kaityouNum){
    std::deque<std::shared_ptr<imageHandler> > ret; 
    for (int i=0; i<m_lst.size(); i++){
        ret.push_back(m_lst[i]->calcEnergy(divNum, kaityouNum));
    }
    return std::shared_ptr<imageHandler>(new multiImageHandler(ret));
}

std::shared_ptr<imageHandler> multiImageHandler::calcContrast(int divNum, int kaityouNum){
    std::deque<std::shared_ptr<imageHandler> > ret; 
    for (int i=0; i<m_lst.size(); i++){
        ret.push_back(m_lst[i]->calcContrast(divNum, kaityouNum));
    }
    return std::shared_ptr<imageHandler>(new multiImageHandler(ret));
}

std::shared_ptr<imageHandler> multiImageHandler::calcCorrelation(int divNum, int kaityouNum){
    std::deque<std::shared_ptr<imageHandler> > ret; 
    for (int i=0; i<m_lst.size(); i++){
        ret.push_back(m_lst[i]->calcCorrelation(divNum, kaityouNum));
    }
    return std::shared_ptr<imageHandler>(new multiImageHandler(ret));
}

std::shared_ptr<imageHandler> multiImageHandler::calcVariance(int divNum, int kaityouNum){
    std::deque<std::shared_ptr<imageHandler> > ret; 
    for (int i=0; i<m_lst.size(); i++){
        ret.push_back(m_lst[i]->calcVariance(divNum, kaityouNum));
    }
    return std::shared_ptr<imageHandler>(new multiImageHandler(ret));
}

std::shared_ptr<imageHandler> multiImageHandler::calcEntropy(int divNum, int kaityouNum){
    std::deque<std::shared_ptr<imageHandler> > ret; 
    for (int i=0; i<m_lst.size(); i++){
        ret.push_back(m_lst[i]->calcEntropy(divNum, kaityouNum));
    }
    return std::shared_ptr<imageHandler>(new multiImageHandler(ret));
}

std::shared_ptr<imageHandler> multiImageHandler::calcSumEntropy(int divNum, int kaityouNum){
    std::deque<std::shared_ptr<imageHandler> > ret; 
    for (int i=0; i<m_lst.size(); i++){
        ret.push_back(m_lst[i]->calcSumEntropy(divNum, kaityouNum));
    }
    return std::shared_ptr<imageHandler>(new multiImageHandler(ret));
}

std::shared_ptr<imageHandler> multiImageHandler::calcIDM(int divNum, int kaityouNum){
    std::deque<std::shared_ptr<imageHandler> > ret; 
    for (int i=0; i<m_lst.size(); i++){
        ret.push_back(m_lst[i]->calcIDM(divNum, kaityouNum));
    }
    return std::shared_ptr<imageHandler>(new multiImageHandler(ret));
}

std::shared_ptr<imageHandler> multiImageHandler::nearSimilar(int n_row, int n_col){
    std::deque<std::shared_ptr<imageHandler> > ret; 
    for (int i=0; i<m_lst.size(); i++){
        int up(i-m_width), down(i+m_width), left(i-1), right(i+1);
        cv::Mat p1 = m_lst[i]->m;
        cv::Mat p2 = m_lst[up    < 0 || up    >= n_row * n_col ? i : up]->m;
        cv::Mat p3 = m_lst[down  < 0 || down  >= n_row * n_col ? i : down]->m;
        cv::Mat p4 = m_lst[left  < 0 || left  >= n_row * n_col ? i : left]->m;
        cv::Mat p5 = m_lst[right < 0 || right >= n_row * n_col ? i : right]->m;
        double N = up    < 0 || up    >= n_row * n_col ? 0 : 1 +
                   down  < 0 || down  >= n_row * n_col ? 0 : 1 +
                   left  < 0 || left  >= n_row * n_col ? 0 : 1 +
        		   right < 0 || right >= n_row * n_col ? 0 : 1;
        m_lst[i]->nearSim = (cv::norm(p1-p2)+
                             cv::norm(p1-p3)+
                             cv::norm(p1-p3)+
                             cv::norm(p1-p5));
        ret.push_back(m_lst[i]);
    }
    return std::shared_ptr<imageHandler>(new multiImageHandler(ret));

}


void multiImageHandler::push_back(cv::Mat &input_m){
    m_lst.push_back(std::shared_ptr<imageHandler>(new singleImageHandler(input_m))); 
}

void multiImageHandler::pop_front(){
    m_lst.pop_front();
}

void multiImageHandler::push(cv::Mat &input_m, int th_num){
    m_lst.push_back(std::shared_ptr<imageHandler>(new singleImageHandler(input_m))); 
    while(m_lst.size() > th_num)
        m_lst.pop_front();
}

void multiImageHandler::mgrid(int iMin, 
                              int iMax, 
                              int iStep,
                              int jMin, 
                              int jMax, 
                              int jStep
                             )
{
}

std::shared_ptr<imageHandler> multiImageHandler::gridImage(
    int n_row, 
    int n_col)
{
    return std::shared_ptr<imageHandler>();
}

void multiImageHandler::readImage
   (
    std::string &input_name
   )
{
}

std::shared_ptr<imageHandler> multiImageHandler::gridMean
    (
    int n_row, 
    int n_col
    )
{
    return std::shared_ptr<imageHandler>();
}

void multiImageHandler::drawGridRect(int n_row, int n_col){
}

void multiImageHandler::getRect(int n_row, int n_col){
}

std::shared_ptr<imageHandler> multiImageHandler::canny
   (
    int threshold1, 
    int threshold2
   )
{
    //!< こんなとこにも
    std::deque<std::shared_ptr<imageHandler> > ret; 
    for(auto a:m_lst) 
        ret.push_back(a->canny(threshold1, threshold2));
    return std::shared_ptr<imageHandler>(new multiImageHandler(ret));
}

std::shared_ptr<imageHandler> multiImageHandler::distanceOfCircleEdge(
                            int threshold1, 
                            int threshold2,
                            int radius,
                            int n_div,
                            bool isDraw){
    std::deque<std::shared_ptr<imageHandler> > ret;
    for(auto a: m_lst) 
        ret.push_back(a->distanceOfCircleEdge(threshold1, 
                                              threshold2, 
                                              radius, 
                                              n_div, 
                                              isDraw));
    
    return std::shared_ptr<imageHandler>(new multiImageHandler(ret)); 
}


std::shared_ptr<imageHandler> multiImageHandler::resize(int height, 
                                                   int width){
    std::deque<std::shared_ptr<imageHandler> > ret; 
    for (int i=0; i<m_lst.size(); i++){
        ret.push_back(m_lst[i]->resize(height, width));
    }
    return std::shared_ptr<imageHandler>(new multiImageHandler(ret));
}

std::shared_ptr<imageHandler> multiImageHandler::expand(int height, 
                                                   int width, 
                                                   bool drawValue){
    std::deque<std::shared_ptr<imageHandler> > ret; 
    for (int i=0; i<m_lst.size(); i++){
        ret.push_back(m_lst[i]->expand(height, width, drawValue));
    }
    return std::shared_ptr<imageHandler>(new multiImageHandler(ret));
}

std::shared_ptr<imageHandler> multiImageHandler::pildown(int height, 
                                                    int width, 
                                                    int n_div, 
                                                    bool drawValue){
    return std::shared_ptr<imageHandler>();
}

std::shared_ptr<imageHandler> multiImageHandler::genParamMap(int n_row, int n_col){
    cv::Mat ret(n_row, n_col, CV_64F);
    uchar* p;
    for(int i=0; i<n_row; i++){
        //p = ret.ptr(i);
        for(int j=0; j<n_col; j++){
        //    p[j] = m_lst[i * n_col + j]->param;
            ret.at<double>(i,j) = m_lst[i * n_col + j]->param();
        }
    }
    return std::shared_ptr<imageHandler>(new singleImageHandler(ret));
}


std::shared_ptr<imageHandler> multiImageHandler::normalize(int minVal,
                                                           int maxVal, 
                                                           int bitDepth){

    std::deque<std::shared_ptr<imageHandler> > ret(m_lst.size());

    int i(0);
    for( auto a: m_lst){
        ret[i] = a->normalize(minVal, maxVal, bitDepth);
        i++;
    }

    return std::shared_ptr<imageHandler>(new multiImageHandler(ret)); 
}

std::shared_ptr<imageHandler> multiImageHandler::normParam(
        double minVal1,
        double maxVal1,
        double minVal2,
        double maxVal2){
    std::deque<std::shared_ptr<imageHandler> > ret; 
    for (int i=0; i<m_lst.size(); i++){
        ret.push_back(m_lst[i]->normParam(minVal1, maxVal1, minVal2, maxVal2));
    }
    return std::shared_ptr<imageHandler>(new multiImageHandler(ret));
}

std::shared_ptr<imageHandler> multiImageHandler::threshold(
                                        double thresh, 
                                        double maxVal, 
                                        int    threshType){
    std::deque<std::shared_ptr<imageHandler> > ret; 
    for (int i=0; i<m_lst.size(); i++){
        ret.push_back(m_lst[i]->threshold(thresh, maxVal, threshType));
    }
    return std::shared_ptr<imageHandler>(new multiImageHandler(ret));
}

std::shared_ptr<imageHandler> multiImageHandler::paintMask(
    std::shared_ptr<imageHandler> &obj,
	int thresh){
    std::deque<std::shared_ptr<imageHandler> > ret; 
    for (int i=0; i<m_lst.size(); i++){
        ret.push_back(m_lst[i]->paintMask(obj, thresh));
    }
    return std::shared_ptr<imageHandler>(new multiImageHandler(ret));
}

std::shared_ptr<imageHandler> multiImageHandler::paintMask(
    std::shared_ptr<imageHandler> &obj){
    std::deque<std::shared_ptr<imageHandler> > ret; 
    for (int i=0; i<m_lst.size(); i++){
        ret.push_back(m_lst[i]->paintMask(obj));
    }
    return std::shared_ptr<imageHandler>(new multiImageHandler(ret));
}

std::shared_ptr<imageHandler> multiImageHandler::cpyParam(std::shared_ptr<imageHandler> &obj){
    std::deque<std::shared_ptr<imageHandler> > ret; 
    for(int i=0; i < m_lst.size(); i++){
        ret.push_back(m_lst[i]->cpyParam(obj->m_lst[i]));
    }
    return std::shared_ptr<imageHandler>(new multiImageHandler(ret));
}

std::shared_ptr<imageHandler> multiImageHandler::interp(std::shared_ptr<imageHandler> &obj){
    std::deque<std::shared_ptr<imageHandler> > ret; 
    for(int i=0; i < m_lst.size(); i++){
        ret.push_back(m_lst[i]->interp(obj->m_lst[i]));
    }
    return std::shared_ptr<imageHandler>(new multiImageHandler(ret));
}

std::shared_ptr<imageHandler> multiImageHandler::setParam(double input_param){
    std::deque<std::shared_ptr<imageHandler> > ret; 
    for(int i=0; i < m_lst.size(); i++){
        ret.push_back(m_lst[i]->setParam(input_param));
    }
    return std::shared_ptr<imageHandler>(new multiImageHandler(ret));
}

std::shared_ptr<imageHandler> multiImageHandler::setParam(parameters input_param){
    std::deque<std::shared_ptr<imageHandler> > ret; 
    for(int i=0; i < m_lst.size(); i++){
        ret.push_back(m_lst[i]->setParam(input_param));
    }
    return std::shared_ptr<imageHandler>(new multiImageHandler(ret));
}

void multiImageHandler::dump(std::string dirPath, 
                             std::string fileName,
                             std::string expand){
    for(auto a: m_lst){
        a->dump(dirPath, fileName, expand);
    }                              
}


std::shared_ptr<imageHandler> multiImageHandler::sortForQue(){

    std::shared_ptr<multiImageHandler> ret(new multiImageHandler(m_lst));

    for(int j=0; j<m_height; j++)
        for(int k=0; k<m_width; k++){
            std::vector<uchar> v_lst(m_lst.size());
            for(int i=0; i<m_lst.size(); i++)
                v_lst[i] = m_lst[i]->m.at<uchar>(j,k); 
            cv::Mat sorted(v_lst);
            cv::sort(sorted.t(), sorted, CV_SORT_EVERY_ROW);
            uchar *p = sorted.ptr();
            for(int i=0; i<m_lst.size(); i++)
                ret->m_lst[i]->m.at<uchar>(j,k) = p[i]; 

        }
    return std::shared_ptr<imageHandler>(ret);
}

std::shared_ptr<imageHandler> multiImageHandler::putCenterParam(
    int fontFace, 
	cv::Scalar color, 
	int thickness){
    std::deque<std::shared_ptr<imageHandler> > ret; 
    for(int i=0; i < m_lst.size(); i++){
        ret.push_back(m_lst[i]->putCenterParam(fontFace, color, thickness));
    }
    return std::shared_ptr<imageHandler>(new multiImageHandler(ret));
}

std::shared_ptr<imageHandler> multiImageHandler::sortForQueIdx(){

    for(int i=0; i<m_lst.size(); i++) m_lst[i]->m.convertTo(m_lst[i]->m, CV_32S);
    std::shared_ptr<multiImageHandler> ret(new multiImageHandler(m_lst));

    for(int j=0; j<m_height; j++)
        for(int k=0; k<m_width; k++){
            std::vector<uchar> v_lst(m_lst.size());
            for(int i=0; i<m_lst.size(); i++)
                v_lst[i] = m_lst[i]->m.at<int>(j,k); 
            cv::Mat sorted(v_lst);
            cv::sortIdx(sorted.t(), sorted, CV_SORT_EVERY_ROW);
            sorted.convertTo(sorted, CV_32S);
//            std::cout << sorted << std::endl;

 //           uchar *p = sorted.ptr(0);
            for(int i=0; i<m_lst.size(); i++){
                ret->m_lst[i]->m.at<int>(j,k) = sorted.at<int>(0, i); 
            }

        }
    //return ret;
    return std::shared_ptr<imageHandler>(ret);
}

std::shared_ptr<imageHandler> multiImageHandler::sortForQueWithObj(
    std::shared_ptr<imageHandler> obj){

    std::shared_ptr<multiImageHandler> ret(new multiImageHandler(m_lst));
    
    for(int j=0; j<m_height; j++)
        for(int k=0; k<m_width; k++){
            for(int i=0; i<m_lst.size(); i++)
                ret->m_lst[i]->m.at<uchar>(j,k) = 
                    ret->m_lst[obj->m_lst[i]->m.at<int>(j,k)]
                       ->m.at<uchar>(j,k); 

        }
    return std::shared_ptr<imageHandler>(ret);

}

std::shared_ptr<imageHandler> multiImageHandler::getBoundingBoxInfo(){
    std::deque<std::shared_ptr<imageHandler> > ret; 
    for(int i=0; i < m_lst.size(); i++){
        ret.push_back(m_lst[i]->getBoundingBoxInfo());
    }
    return std::shared_ptr<imageHandler>(new multiImageHandler(ret));
}

std::shared_ptr<imageHandler> multiImageHandler::rectangle(
        cv::Scalar& color, 
        int thickness, 
        int lineType, 
        cv::Rect input_rect, 
        int shift
        ){
    std::deque<std::shared_ptr<imageHandler> > ret; 
    for(int i=0; i < m_lst.size(); i++){
        ret.push_back(m_lst[i]->rectangle(color,
                                          thickness,
                                          lineType,
                                          input_rect,
                                          shift));
    }

    return std::shared_ptr<imageHandler>(new multiImageHandler(ret));
}

std::shared_ptr<imageHandler> multiImageHandler::checkValidArea(std::shared_ptr<imageHandler> &obj){
    std::deque<std::shared_ptr<imageHandler> > ret; 
    for(int i=0; i < m_lst.size(); i++){
        auto tmp = m_lst[i]->checkValidArea(obj);
        if(tmp->param())
            ret.push_back(tmp);
    }
    return std::shared_ptr<imageHandler>(new multiImageHandler(ret));
    
}

std::shared_ptr<imageHandler> multiImageHandler::clip(std::shared_ptr<imageHandler> &obj){
    std::deque<std::shared_ptr<imageHandler> > ret; 
    for(int i=0; i < m_lst.size(); i++){
        ret.push_back(m_lst[i]->clip(obj));
    }
    return std::shared_ptr<imageHandler>(new multiImageHandler(ret));
}

std::shared_ptr<imageHandler> multiImageHandler::superImpose(int thresh){
    std::shared_ptr<imageHandler>  ret(new singleImageHandler(cv::Mat(m_height, m_width, m_lst[0]->m.type()))); 
    ret->m = cv::Scalar(0);
    for(int i=0; i < m_lst.size(); i++){
        ret = *ret + m_lst[i];
    }
    return std::shared_ptr<imageHandler>(ret);
}

//std::shared_ptr<imageHandler> singleImageHandler::clip(cv::Rect &input_rect){
//    std::deque<std::shared_ptr<imageHandler> > ret; 
//    for(int i=0; i < m_lst.size(); i++){
//        ret.push_back(m_lst[i]->clip(input_rect));
//    }
//    return std::shared_ptr<imageHandler>(new multiImageHandler(ret));
//}

// 比較用関数。

bool multiImageHandler::any(){
    for (int i=0; i<m_lst.size(); i++){
        if(m_lst[i]->param() > 0){
            return true;
        }
    }
    return false;
}

bool multiImageHandler::all(){
    for (int i=0; i<m_lst.size(); i++){
        if(m_lst[i]->param() == 0)
            return false;
    }
    return false;
}


// 描画用関数

void multiImageHandler::view(std::string input_name, int wTime){
    int cnt(0);
    for(int i=0; i<m_lst.size(); i++){
        std::stringstream ss;
        ss << "No. " << i; 
        m_lst[i]->view(ss.str(), wTime);
    }
}

void multiImageHandler::histView(
     std::string input_name, 
     int binNum, 
     int xMin, 
     int xMax,
     int yMin,
     int yMax){
}

std::shared_ptr<imageHandler> multiImageHandler::drawOuterFrame(
    cv::Scalar &color,
	int thickness, 
	int lineType, 
	int shift){
    std::deque<std::shared_ptr<imageHandler> > ret; 
    for (int i=0; i<m_lst.size(); i++){
        ret.push_back(m_lst[i]->drawOuterFrame(color, thickness, lineType, shift));
    }
    return std::shared_ptr<imageHandler>(new multiImageHandler(ret));
}

void multiImageHandler::viewGridedImg(std::string input_name, int wTime){
}

void multiImageHandler::viewGridedParam(std::string input_name){
}

void multiImageHandler::resizeView(int width, int height){
}

void multiImageHandler::expandView(int width, int height){
    for(auto a: m_lst)
        a->expandView(width, height);
}

void multiImageHandler::pildownView(int width, int height, int n_div, bool drawValue){
}

int multiImageHandler::size(){
    return m_lst.size();
}

std::shared_ptr<imageHandler> multiImageHandler::stichImg(int n_row, 
                                                          int n_col){
                                                            
    cv::Mat ret(n_row * m_height, n_col * m_width, m_lst[0]->m.type());
    ret = cv::Scalar(0);
    int divX(m_width/n_col), divY(m_height/n_row);
    for(int i=0; i<n_row; i++){
        for(int j=0; j<n_col; j++){
            cv::Rect rect(j * m_width, i * m_height, m_width, m_height);
            m_lst[i * n_col + j]->m.copyTo(ret(rect));
        }
    }

    return std::shared_ptr<imageHandler>(new singleImageHandler(ret));
}

// 演算子オーバーロード
std::shared_ptr<imageHandler> multiImageHandler::operator+(const std::shared_ptr<imageHandler> &obj){
    
    std::deque<std::shared_ptr<imageHandler> > ret;
    for(int i=0; i<m_lst.size(); i++)
        ret.push_back(*m_lst[i] + obj->m_lst[i]);
    
    return std::shared_ptr<imageHandler>(new multiImageHandler(ret));
}

std::shared_ptr<imageHandler> multiImageHandler::operator-(
        std::shared_ptr<imageHandler> obj){
    
    std::deque<std::shared_ptr<imageHandler> > ret;
    for(int i=0; i<m_lst.size(); i++)
        ret.push_back(*m_lst[i] - obj->m_lst[i]);
    
    return std::shared_ptr<imageHandler>(new multiImageHandler(ret));
}

std::shared_ptr<imageHandler> multiImageHandler::operator*(
        std::shared_ptr<imageHandler> obj){
    std::deque<std::shared_ptr<imageHandler> > ret;
    for(int i=0; i<m_lst.size(); i++)
        ret.push_back(*m_lst[i] * obj->m_lst[i]);
    
    return std::shared_ptr<imageHandler>(new multiImageHandler(ret));
}


std::shared_ptr<imageHandler> multiImageHandler::operator/(
        std::shared_ptr<imageHandler> obj){
    std::deque<std::shared_ptr<imageHandler> > ret;
    for(int i=0; i<m_lst.size(); i++)
        ret.push_back(*m_lst[i] / obj->m_lst[i]);
    
    return std::shared_ptr<imageHandler>(new multiImageHandler(ret));
}

std::shared_ptr<imageHandler> multiImageHandler::operator^(
        std::shared_ptr<imageHandler> obj){
    std::deque<std::shared_ptr<imageHandler> > ret;
    for(int i=0; i<m_lst.size(); i++)
        ret.push_back(*m_lst[i] ^ obj->m_lst[i]);
    
    return std::shared_ptr<imageHandler>(new multiImageHandler(ret));
}

std::shared_ptr<imageHandler> multiImageHandler::operator>(const std::shared_ptr<imageHandler> &obj){
    std::deque<std::shared_ptr<imageHandler> > ret;
    for(int i=0; i<m_lst.size(); i++)
        ret.push_back(*m_lst[i] > obj->m_lst[i]);
    return std::shared_ptr<imageHandler>(new multiImageHandler(ret));
}

std::shared_ptr<imageHandler> multiImageHandler::operator<(const std::shared_ptr<imageHandler> &obj){
    std::deque<std::shared_ptr<imageHandler> > ret;
    for(int i=0; i<m_lst.size(); i++)
        ret.push_back(*m_lst[i] < obj->m_lst[i]);
    return std::shared_ptr<imageHandler>(new multiImageHandler(ret));
}

std::shared_ptr<imageHandler> multiImageHandler::operator>=(const std::shared_ptr<imageHandler> &obj){
    std::deque<std::shared_ptr<imageHandler> > ret;
    for(int i=0; i<m_lst.size(); i++)
        ret.push_back(*m_lst[i] >= obj->m_lst[i]);
    return std::shared_ptr<imageHandler>(new multiImageHandler(ret));
}

std::shared_ptr<imageHandler> multiImageHandler::operator<=(const std::shared_ptr<imageHandler> &obj){
    std::deque<std::shared_ptr<imageHandler> > ret;
    for(int i=0; i<m_lst.size(); i++)
        ret.push_back(*m_lst[i] <= obj->m_lst[i]);
    return std::shared_ptr<imageHandler>(new multiImageHandler(ret));
}

std::shared_ptr<imageHandler> multiImageHandler::operator==(const std::shared_ptr<imageHandler> &obj){
    std::deque<std::shared_ptr<imageHandler> > ret;
    for(int i=0; i<m_lst.size(); i++)
        ret.push_back(*m_lst[i] == obj->m_lst[i]);
    return std::shared_ptr<imageHandler>(new multiImageHandler(ret));
}

std::shared_ptr<imageHandler> multiImageHandler::operator&&(const std::shared_ptr<imageHandler> &obj){
    std::deque<std::shared_ptr<imageHandler> > ret;
    for(int i=0; i<m_lst.size(); i++)
        ret.push_back(*m_lst[i] && obj->m_lst[i]);
    return std::shared_ptr<imageHandler>(new multiImageHandler(ret));
}



std::shared_ptr<imageHandler> multiImageHandler::operator>(const double &val){
    std::deque<std::shared_ptr<imageHandler> > ret;
    for(int i=0; i<m_lst.size(); i++)
        ret.push_back(*m_lst[i] > val);
    return std::shared_ptr<imageHandler>(new multiImageHandler(ret));
}

std::shared_ptr<imageHandler> multiImageHandler::operator<(const double &val){
    std::deque<std::shared_ptr<imageHandler> > ret;
    for(int i=0; i<m_lst.size(); i++)
        ret.push_back(*m_lst[i] < val);
    return std::shared_ptr<imageHandler>(new multiImageHandler(ret));
}

std::shared_ptr<imageHandler> multiImageHandler::operator>=(const double &val){
    std::deque<std::shared_ptr<imageHandler> > ret;
    for(int i=0; i<m_lst.size(); i++)
        ret.push_back(*m_lst[i] >= val);
    return std::shared_ptr<imageHandler>(new multiImageHandler(ret));
}

std::shared_ptr<imageHandler> multiImageHandler::operator<=(const double &val){
    std::deque<std::shared_ptr<imageHandler> > ret;
    for(int i=0; i<m_lst.size(); i++)
        ret.push_back(*m_lst[i] <= val);
    return std::shared_ptr<imageHandler>(new multiImageHandler(ret));
}

std::shared_ptr<imageHandler> multiImageHandler::operator==(const double &val){
    std::deque<std::shared_ptr<imageHandler> > ret;
    for(int i=0; i<m_lst.size(); i++)
        ret.push_back(*m_lst[i] == val);
    return std::shared_ptr<imageHandler>(new multiImageHandler(ret));
}

//#include "stdafx.h"
#include "singleImageHandler.h"
//#pragma optimize("", off)

//singleImageHandler::singleImageHandler(unsigned char* input_raw, 
//                           int input_width, 
//                           int input_height):
//    m_width(input_height), m_height(input_height)
//    {
//    //initializePointers();
//    m_raw = new unsigned char(*input_raw);
//    //uchar2Mat();
//}

//singleImageHandler::singleImageHandler(std::vector<std::vector<double> > &v):
//    m_width(v[0].size()), m_height(v.size())
//{
//    //initializePointers();
//    //vec2Mat();
//    
//}

//singleImageHandler::singleImageHandler(std::vector<singleImageHandler> &input_obj):
//    m_lst(input_obj), 
//    m_width(input_obj[0].m_height), 
//    m_height(input_obj[0].m_width)
//{
//    initializePointers();
//    img_que.push_back(m);
//}

singleImageHandler::singleImageHandler(cv::Mat input_m, double input_param, cv::Rect input_rect):
    imageHandler(input_m, input_param, input_rect)
{
}

singleImageHandler::singleImageHandler(cv::Mat input_m, parameters input_params, cv::Rect input_rect):
    imageHandler(input_m, input_params, input_rect)
{
}

singleImageHandler::singleImageHandler(std::pair<std::string, cv::Mat> &input_pair):
    imageHandler(input_pair)
{
}

std::shared_ptr<imageHandler> singleImageHandler::getBoundingBoxInfo(){
    // インデックス行列を作成。
    cv::Mat idx_x(m_height, m_width, CV_32S);
    cv::Mat idx_y(m_height, m_width, CV_32S);

    cv::Mat tofMat=m.clone();
    if(m.channels()>1)
        cv::cvtColor(m, tofMat, CV_BGR2GRAY);

    int minIdx_x(m_width), minIdx_y(m_height), maxIdx_x(0), maxIdx_y(0);
    for(int i=0; i<m_height; i++){  
        unsigned char* p_x = idx_x.ptr(i);
        unsigned char* p_y = idx_y.ptr(i);
        unsigned char* p = m.ptr(i);
        for(int j=0; j<m_width; j++){
            if(p[j]){ // 要素が0以上ならば
                minIdx_x = minIdx_x > j ? j : minIdx_x; 
                minIdx_y = minIdx_y > i ? i : minIdx_y;
                maxIdx_x = maxIdx_x < j ? j : maxIdx_x; 
                maxIdx_y = maxIdx_y < i ? i : maxIdx_y;
            }
        }
    }
    

    return std::shared_ptr<imageHandler>(new singleImageHandler(m.clone(), param, cv::Rect(minIdx_x, minIdx_y , maxIdx_x - minIdx_x,  maxIdx_y - minIdx_y)));
}

std::shared_ptr<imageHandler> singleImageHandler::rectangle(
        cv::Scalar& color, 
        int thickness, 
        int lineType, 
        cv::Rect input_rect, 
        int shift
        ){

    cv::Rect retRect(cv::Rect() == input_rect ? rect : input_rect);
    cv::Mat ret = m.clone();

    cv::rectangle(ret, retRect, color, thickness, lineType, shift);
    

    return std::shared_ptr<imageHandler>(new singleImageHandler(ret.clone(),param, rect));
}

std::shared_ptr<imageHandler> singleImageHandler::checkValidArea(std::shared_ptr<imageHandler> &obj){
    cv::Mat this_m = RGB2Gray()->threshold(1, 255, CV_THRESH_BINARY)->m; //  
    cv::Mat obj_m  = obj->RGB2Gray()->threshold(1, 255, CV_THRESH_BINARY)->m;
    //if (this_m.channels() > 1)
    //    cv::cvtColor(this_m, this_m, CV_RGB2GRAY);
    //if (obj_m.channels() > 1)
    //    cv::cvtColor(obj_m, obj_m, CV_RGB2GRAY);
    cv::Mat comp_m = this_m.mul(obj_m);

    auto comp = std::shared_ptr<imageHandler>(new singleImageHandler(comp_m, param));
    
    if(((*comp->maxImg()) > 0)->param != 0)
        return std::shared_ptr<imageHandler>(new singleImageHandler(m.clone(), 1, rect));
    else
        return std::shared_ptr<imageHandler>(new singleImageHandler(m.clone(), 0, rect));
}

std::shared_ptr<imageHandler> singleImageHandler::clip(std::shared_ptr<imageHandler> &obj){
    cv::Mat ret = m.clone();
    for(auto a: obj->m_lst){ 
        
        cv::rectangle(ret, cv::Rect(a->rect.x, a->rect.y, a->rect.width+1, a->rect.height+1), cv::Scalar(0,0,0), -1);
    }

    return std::shared_ptr<imageHandler>(new singleImageHandler(ret, param, rect));
}

std::shared_ptr<imageHandler> singleImageHandler::clip(cv::Rect &input_rect, bool inv){
    cv::Mat ret;
    if (inv)
        ret = m(input_rect).clone();
    else{
        ret = m.clone();
        ret(input_rect) = cv::Scalar(0,0,0);
    }

    return std::shared_ptr<imageHandler>(new singleImageHandler(ret, param, rect));
}
//std::shared_ptr<imageHandler> singleImageHandler::clip(cv::Rect &input_rect){
//}

void singleImageHandler::view(std::string input_name, int wTime, bool isMovie){
    if (!(m.cols || m.rows))
        return;

	cv::namedWindow(input_name, CV_WINDOW_NORMAL);
    cv::imshow(name.size() ? name : input_name, m);
    cv::waitKey(wTime);
}

singleImageHandler::singleImageHandler(std::string input_name){
    readImage(input_name);
}

void singleImageHandler::histView(
                                  std::string input_name, 
                                  int binNum, 
                                  int xMin, 
                                  int xMax,
                                  int yMin,
                                  int yMax){

    //c = new TCanvas("c1", "c1");
    //h = new TH1F(name.c_str(), 
    //             name.c_str(),
    //             binNum, 
    //             xMin, 
    //             xMax);

    //for(int i=0; i<m_height; i++)
    //    for(int j=0; j<m_width; j++)
    //        h->Fill((int)m.at<unsigned char>(i,j),1); 

    //h->SetMinimum(yMin);
   	//h->SetMaximum(yMax);

    //h->Draw();
   	////TF1 *f1 = new TF1("f1", "gaus", 0, 255);
   	////source->Fit("f1", "R");
   	////source->Draw();
   	////f1->Draw("same");
   	//////f1->Draw("same");
   	////c1->Draw("AXIS");
   	////TLine* a = new TLine(0.1, 0.1, 1, 1);
   	//////viewWithConsole(f1->);
   	////a->Draw();
   	//c->Update();
}

std::shared_ptr<imageHandler> singleImageHandler::drawOuterFrame(
    cv::Scalar &color,
	int thickness, 
	int lineType, 
	int shift){

    cv::Mat ret = m.clone();
    cv::rectangle(ret, cv::Rect(0, 0, m.cols, m.rows), color, thickness, lineType, shift);
    return std::shared_ptr<imageHandler>(new singleImageHandler(ret));
}



//std::shared_ptr<imageHandler> singleImageHandler::labeling(bool isMulti){
//    cv::Mat ret(m_height, m_width, CV_8U, cv::Scalar(0));

//    
//    int labelNum(1); // ラベル番号(一番から。0はラベリングされていない領域を指す)。

//    


//    //static int left;
// 	//static int right;
// 	//static int up ;  
// 	//static int down;         
//    typedef struct{ // 再帰的にラベリングをするファンクタを定義。
//       static void func(int i, int j, int labelNum, cv::Mat &m, cv::Mat &ret){
//            ret.ptr(i)[j] = labelNum;
//            int left  = (j-1 < 0)       ? j : j-1;
//    		int right = (j+1 >= m.cols) ? j : j+1;
//    		int up    = (i-1 < 0)       ? i : i-1;
//    		int down  = (i+1 >= m.rows) ? i : i+1;

//            if(m.ptr(i)[left] != 0 && left != j && ret.ptr(i)[left] == 0){
//                func(i, left, labelNum, m, ret);
//            }
//            if(m.ptr(i)[right] != 0 && right != j && ret.ptr(i)[right] == 0){
//                func(i, right, labelNum, m, ret);
//            }
//            if(m.ptr(up)[j] != 0 && up != i && ret.ptr(up)[j] == 0){
//                func(up, j, labelNum, m, ret);
//            }
//            //if(m.ptr(up)[left] != 0 && up != i && left != j && ret.ptr(up)[left] == 0){
//            //    ret.ptr(up)[left] = labelNum; 
//            //    func(up, left, labelNum, m, ret);
//            //}
//            //if(m.ptr(up)[right] != 0 && up != i && right != j && ret.ptr(up)[right] == 0){
//            //    ret.ptr(up)[right] = labelNum; 
//            //    func(up, right, labelNum, m, ret);
//            //}
//            if(m.ptr(down)[j] != 0 && down != i && ret.ptr(down)[j] == 0){
//                ret.ptr(down)[j] = labelNum; 
//                func(down, j, labelNum, m, ret);
//            }
//            //if(m.ptr(down)[left] != 0 && down != i && left != j && ret.ptr(down)[left] == 0){
//            //    ret.ptr(down)[left] = labelNum; 
//            //    func(down, left, labelNum, m, ret);
//            //}
//            //if(m.ptr(down)[right] != 0 && down != i && right != j && ret.ptr(down)[right] == 0){
//            //    ret.ptr(down)[right] = labelNum; 
//            //    func(down, right, labelNum, m, ret);
//            //}
//        }
//    } labelingAround;

//    for(int i = 0; i < m_height; i++){
//        unsigned char* p     = m.ptr(i);
//        unsigned char* p_ret = ret.ptr(i);
//        for (int j = 0; j < m_width; j++){
//            if(p[j] != 0 && p_ret[j] == 0){ // 要素がマスク領域であり、まだラベリングされていない場合、
//                labelingAround::func(i, j, labelNum, m, ret);
//                //labelingAround::func(m, ret, i, j, labelNum);
//                labelNum++;
//            }
//            
//        }
//    }

//    if(isMulti){
//        std::deque<std::shared_ptr<imageHandler> > retQue;
//        for(int i=0; i<labelNum-1; i++){
//            cv::Mat retMat = ret == (i+1);
//            retQue.push_back(std::shared_ptr<imageHandler>(new singleImageHandler(retMat.clone())));///255);//*(i+1))))));
//        }
//        if(retQue.size())
//            return std::shared_ptr<imageHandler>(new multiImageHandler(retQue));
//        else
//            return std::shared_ptr<imageHandler>();
//    } else
//        return std::shared_ptr<imageHandler>(new singleImageHandler(ret));
//}
//std::shared_ptr<imageHandler> singleImageHandler::labeling(bool isMulti, int threshBreakNum){
//    cv::Mat ret(m_height, m_width, CV_8U, cv::Scalar(0));

//    
//    int labelNum(1); // ラベル番号(一番から。0はラベリングされていない領域を指す)。

//    int p(3); // 探索点数。
//    int d; // ステップ数(次元ベクトルDの要素)。

//    cv::Mat labelMat = cv::Mat(m_height, m_width, CV_8U, cv::Scalar(0));


//    std::vector<int> I;
//    I.push_back(-m_width); //up
//    I.push_back(1);        //right
//    I.push_back(m_width);  //down
//    I.push_back(-1);       //left
//    
//    std::deque<int> D;
//    std::deque<int> o;  // 向き(otientation);
//    int breakNum(0); // 無限ループを終了する条件の閾値。
//    for(int i=m_height/2; i<m_height; i++){
//        unsigned char* ptr     = m.ptr(i);
//        unsigned char* ptr_label = labelMat.ptr(i);
//        for(int j=m_width/2; j<m_width;  j++){
//            if(ptr_label[j] == 0 &&
//               ptr[j]       != 0){

//                breakNum = 0;
//                int k=0;
//    	    	while(true){ // 無限ループ
//    			    int k_sub = k;

//    			    D.push_back(0); // 下行の比較用に0をつめる(後でとる)。

//    			    while(D[D.size()-1] != 1 && k_sub >= 0){ // 現在のdが1(約分可能なpがない)ではなく、
//    			        d = 1;

//    			    	while(true) { // 約分可能な最大公約数を求める。
//                            if(k_sub/d)
//    			    	        d *= p;
//                            else{
//                                d =  d/p ? d/p : d;
//                                break;
//                            }
//    			    	}

//    			    	D.push_back(d);
//    			        o.push_back(k_sub/d);

//    			        k_sub -= (k_sub/d) * d;     // 下位ランクの計算のために減算する。
//    			    }

//    			    D.pop_front(); //先頭の0をとる。

//    			    // 現在のインデックスを求める。
//            	    int idx(i * m_width + j); // インデックス(一次元配列として見たとき)
//            	    int o_sum(0); // 向きの総和。    
//    			    for(int l=0; l<D.size(); l++){
//            	        o_sum += o[l];
//    			        idx += I[o_sum%p];
//    			    }

//            	    
//            	    int a(idx/m_width), b(idx%m_width);     // 現在のインデックスの定義。

//            	    if(!(a < 0 || a >= m_height ||          // インデックスが画像範囲外ではなく、
//            	         b < 0 || b >= m_width) && 
//            	         labelMat.ptr(a)[b] == 0 &&         // 現在の画素がラベル付けされておらず、
//            	       m.ptr(a)[b] != 0 // かつ現在の画素が有効であれば、
//            	       ){
//            	    	    labelMat.ptr(a)[b] = 255;
//                            cv::imshow("hello", labelMat);
//                            cv::waitKey(1);
//            	    	   // labelMat.ptr(a)[b] = labelNum;
//            	    }else
//            	        breakNum++; // 終了

//                    o.clear(); o.shrink_to_fit();
//                    D.clear(); D.shrink_to_fit();

//            	    if(breakNum > threshBreakNum)
//            	        break;
//                    k ++;
//            	}   

//                labelNum++; //　ラベルをインクリメント。
//            }

//        }
//    }    



//    if(isMulti){
//        std::deque<std::shared_ptr<imageHandler> > retQue;
//        for(int i=0; i<labelNum-1; i++){
//            cv::Mat retMat = ret == (i+1);
//            retQue.push_back(std::shared_ptr<imageHandler>(new singleImageHandler(retMat.clone())));///255);//*(i+1))))));
//        }
//        if(retQue.size())
//            return std::shared_ptr<imageHandler>(new multiImageHandler(retQue));
//        else
//            return std::shared_ptr<imageHandler>();
//    } else
//        return std::shared_ptr<imageHandler>(new singleImageHandler(ret));
//}
std::shared_ptr<imageHandler> singleImageHandler::labeling(bool isMulti, int threshBreakNum, int times){
    cv::Mat ret(m_height, m_width, CV_8U, cv::Scalar(0));

    
    int labelNum(1); // ラベル番号(一番から。0はラベリングされていない領域を指す)。

    int p(3); // 探索点数。
    int d; // ステップ数(次元ベクトルDの要素)。

    cv::Mat labelMat = cv::Mat(m_height, m_width, CV_8U, cv::Scalar(0));

    std::vector<int> lut(10000,0), changeLst(10000,0);
    for(int t=0; t<times; t++){
    	lut = std::vector<int>(100,0);
        for(int i=0; i<m_height; i++){
    	    unsigned char* ptr = m.ptr(i);
    	    unsigned char* ptr_label = labelMat.ptr(i);
    	    for(int j=0; j<m_width;  j++){
    	        if(ptr[j] != 0){
    	            int left  = (j-1 < 0)       ? j : j-1;
		    		int right = (j+1 >= m.cols) ? j : j+1;
		    		int up    = (i-1 < 0)       ? i : i-1;
		    		int down  = (i+1 >= m.rows) ? i : i+1;
    	            unsigned char curr = ptr_label[j];

    	            // 周囲8画素のいずれかが0出ないとき、かつ現在のラベルより小さい場合。
    	            // そのラベルを現在のラベルに代入する。

    	            // 左
    	            if (curr == 0 || labelMat.ptr(i)[left] && labelMat.ptr(i)[left] < curr){ 
    	                curr = labelMat.ptr(i)[left];
    	                changeLst.push_back(curr);
    	            }

    	            // 右 
    	            if (curr == 0 || labelMat.ptr(i)[right] && labelMat.ptr(i)[right] < curr){
    	                curr = labelMat.ptr(i)[right];
    	                changeLst.push_back(curr);
    	            }

    	            // 上
    	            if (curr == 0 || labelMat.ptr(up)[j] && labelMat.ptr(up)[j] < curr) {
    	                curr = labelMat.ptr(down)[j];
    	                changeLst.push_back(curr);
    	            }

    	            // 下 
    	            if (curr == 0 || labelMat.ptr(down)[j] && labelMat.ptr(down)[j] < curr) {
    	                curr = labelMat.ptr(down)[j];
    	                changeLst.push_back(curr);
    	            }

    	            // 左上
    	            if (curr == 0 || labelMat.ptr(up)[left] && labelMat.ptr(up)[left] < curr){
    	                curr = labelMat.ptr(up)[left];
    	                changeLst.push_back(curr);
    	            }

    	            // 左下
    	            if (curr == 0 || labelMat.ptr(down)[left] && labelMat.ptr(down)[left] < curr){
    	                curr = labelMat.ptr(down)[left];
    	                changeLst.push_back(curr);
    	            }

    	            // 右上
    	            if (curr == 0 || labelMat.ptr(up)[right] && labelMat.ptr(up)[right] < curr){
    	                curr = labelMat.ptr(up)[right];
    	                changeLst.push_back(curr);
    	            }

    	            // 右下
    	            if (curr == 0 || labelMat.ptr(down)[right] && labelMat.ptr(down)[right] < curr){
    	                curr = labelMat.ptr(down)[right];
    	                changeLst.push_back(curr);
    	            }


    	            // 周囲8画素がゼロの場合。
    	            if (!(labelMat.ptr(i)   [left]  ||
    	                  labelMat.ptr(i)   [right] ||
    	                  labelMat.ptr(down)[j]     ||
    	                  labelMat.ptr(down)[left]  ||
    	                  labelMat.ptr(down)[right] ||
    	                  labelMat.ptr(up)  [j]     ||
    	                  labelMat.ptr(up)  [left]  ||
    	                  labelMat.ptr(up)  [right])){  // 周囲8要素すべてが0ならば、
    	                ptr_label[j] = labelNum++;                // カウントアップする。
    	            } else {
    	                ptr_label[j] = curr;  
    	            }

    	            for(auto change: changeLst)
    	                lut[change] = curr;
    	            lut[curr] = curr;

    	            changeLst.clear();changeLst.shrink_to_fit();
    	        }
    	        
    	    }
    	}    
    }


    for(int i=0; i<m_height; i++){
        unsigned char* ptr = m.ptr(i);
        unsigned char* ptr_label = labelMat.ptr(i);
        for(int j=0; j<m_width;  j++){
            if(ptr[j] != 0){
                ptr_label[j] = lut[ptr_label[j]];
            }
        }
    }

    std::vector<int> hist(10000,0);
    for(auto l:lut)
        hist[l]++;

    int size(0);
    for(int i=1; i<lut.size(); i++) //0は必ず入っているので飛ばす。
        if(hist[i] > 0){
            size++;
            hist[i] = size; // ヒストグラムを変換テーブルとしても用いる。
        }


    for(int i=0; i<m_height; i++){
        unsigned char* ptr = m.ptr(i);
        unsigned char* ptr_label = labelMat.ptr(i);
        for(int j=0; j<m_width;  j++){
            if(ptr[j] != 0){
                ptr_label[j] = hist[ptr_label[j]];
            }
        }
    }
        


    if(isMulti){
        std::deque<std::shared_ptr<imageHandler> > retQue;
        for(int i=0; i<size; i++){ // 必ず0が入るのでsize-1
            cv::Mat retMat = labelMat == (i+1);
            retQue.push_back(std::shared_ptr<imageHandler>(new singleImageHandler(
                retMat.clone())));///255);//*(i+1))))));
        }
        if(retQue.size())
            return std::shared_ptr<imageHandler>(new multiImageHandler(retQue));
        else
            return std::shared_ptr<imageHandler>(new singleImageHandler(ret));
    } else
        return std::shared_ptr<imageHandler>(new singleImageHandler(ret));
}

std::shared_ptr<imageHandler> singleImageHandler::putCenterParam(
    int fontFace, 
    cv::Scalar color, 
    int thickness){
    cv::Mat ret = m.clone();
    std::stringstream ss;
    ss << std::setw(4) << std::fixed << std::setprecision(2) << param();
    cv::putText( ret, ss.str(), cv::Point(m_width/5, m_height/1.6), fontFace, (double)(m_width + m_height) / 190., color, thickness);
    return std::shared_ptr<imageHandler>(new singleImageHandler(ret, param));
}


std::shared_ptr<imageHandler> singleImageHandler::drawOuterFrameAroundObjects(int thresh){
    cv::Mat ret;
    return std::shared_ptr<imageHandler>(new singleImageHandler(ret));
    
}

std::shared_ptr<imageHandler> singleImageHandler::fillObjects(cv::Mat mask, cv::Scalar &color){
    cv::Mat bg(m_height, m_width, m.type(), color);
    cv::Mat ret = m.clone();
    bg.copyTo(ret, mask);
    return std::shared_ptr<imageHandler>(new singleImageHandler(ret));
    
}

std::shared_ptr<imageHandler> imageHandler::putText(std::string text,
                                      cv::Point org,
                                      int fontFace,
                                      double fontScale,
                                      cv::Scalar color,
                                      int thickness,
                                      int lineType,
                                      bool bottomLeftOrigin){
    cv::Mat ret = m.clone();
    cv::putText(
        ret, 
        text, 
        org, 
        fontFace, 
        fontScale, 
        color, 
        thickness, 
        lineType, 
        bottomLeftOrigin
        );
    return std::shared_ptr<imageHandler>(new singleImageHandler(ret));
}


void singleImageHandler::initializePointers(){
    //m_raw  = (unsigned char *)calloc((m_width * m_height), sizeof(unsigned char));
    ////m_gray = (unsigned char *)calloc((m_width * m_height), sizeof(unsigned char));
    //m_ave  = (unsigned char *)calloc((m_width * m_height), sizeof(unsigned char));
    //m_diff = (unsigned char *)calloc((m_width * m_height), sizeof(unsigned char));

   // theApp = std::unique_ptr<TApplication>(new TApplication("AP", NULL, NULL));
    
}

//// private functions
//void singleImageHandler::vec2Mat(){
//    for (int i=0; i<m_height; i++){
//        unsigned char *p = m.ptr<unsigned char>(i);
//        for (int j=0; j<m_width; j++)
//            v;
//    }
//}


//void singleImageHandler::uchar2Mat(){
//    for (int i=0; i<m_height; i++){
//        unsigned char *p = m.ptr<unsigned char>(i);
//        for (int j=0; j < m_width; j++)
//            p[j] = m_raw[i * m_height + j];
//    }
//}

////void singleImageHandler::make_diff_image ()
////{
////	int range = 1;
////	BYTE *pL_t_last_list[300]; //TMP

////	for (int i = 0; i < m_height; i++) { // 行ループ

////		// 前回行（上の行）
////		if (i >= range) { // i が、range 以降ならば、
////			for (int i2 = 0; i2 <= range; i2++) { // 行の範囲： i-range - i（range+1行）
////				int ads_last = (i-range+i2) * m_width * IMG_CHANNEL;
////				pL_t_last_list[i2] = (BYTE*)(raw + ads_last); // 出力用
////			} // for i2
////			
////		}

////		// 現在行
////		int ads = i * m_width * IMG_CHANNEL;
////		BYTE *pL_s = (BYTE*)(raw + ads); // 入力用
////		BYTE *pL_t = (BYTE*)(diff + ads); // 出力用

////		for (int j = 0; j < m_width; j++) { // 列ループ

////			// 実明度の取得
////			double b = (double)(*(pL_s + 0)); // 青
////			double g = (double)(*(pL_s + 1)); // 緑
////			double r = (double)(*(pL_s + 2)); // 赤
////			double kd = (b + g + r) / 3.0; // 実明度

////			double skd = 0.0; // 基準明度

////			// 色差分（補正あり）の計算
////			if (kd > 127.0) {
////				if (kd < 240.0) { //TMP
////				//if (kd < 255.0) { //TMP
////					b = skd + fabs(b - kd) * F_DIFF_MOD_O127(kd); // 青 TMP fabs
////					g = skd + fabs(g - kd) * F_DIFF_MOD_O127(kd); // 緑
////					r = skd + fabs(r - kd) * F_DIFF_MOD_O127(kd); // 赤
////				} else {
////#if 0 //TMP
////					b = 0; // 青
////					g = 0; // 緑
////					r = 0; // 赤

////#else // 周囲のピクセル（左上）で、最も高いRGB相対輝度値を採用

////					double b_max = -DBL_MAX;
////					double g_max = -DBL_MAX;
////					double r_max = -DBL_MAX;

////					double b_sum = 0.0;
////					double g_sum = 0.0;
////					double r_sum = 0.0;
////					int num = 0;

////					// 前回行
////					if (i >= range) { // i が、range 以降ならば、

////						//for (int i2 = i-range; i2 < i; i2++) { // 行ループ
////						for (int i2 = 0; i2 < range; i2++) { // 行ループ
////							for (int j2 = j-range; j2 < j; j2++) { // 列ループ

////								if (j2 < 0) continue; // 範囲外ならば、パス

////								if (i2 == i && j2 == j) continue; // 現在ピクセルならば、パス

////								double b2 = (double)(*(pL_t_last_list[i2] + j2 * IMG_CHANNEL + 0)); // 青
////								double g2 = (double)(*(pL_t_last_list[i2] + j2 * IMG_CHANNEL + 1)); // 緑
////								double r2 = (double)(*(pL_t_last_list[i2] + j2 * IMG_CHANNEL + 2)); // 赤

////								b_max = (b2 > b_max) ? b2 : b_max; // 青
////								g_max = (g2 > g_max) ? g2 : g_max; // 緑
////								r_max = (r2 > r_max) ? r2 : r_max; // 赤

////								b_sum += b2;
////								b_sum += g2;
////								b_sum += r2;

////								num += 1;

////							} //for j2
////						} // for i2

////#if 1
////						b = b_max; // 青
////						g = g_max; // 緑
////						r = r_max; // 赤
////#else
////						b = b_sum / (double)num;
////						g = g_sum / (double)num;
////						r = r_sum / (double)num;
////#endif
////					}
////#endif
////				}

////			} else { // if kd <= 127.0

////				if (kd > 40.0) {
////					b = skd + fabs(b - kd) * F_DIFF_MOD_U127(kd); // 青 TMP fabs
////					g = skd + fabs(g - kd) * F_DIFF_MOD_U127(kd); // 緑
////					r = skd + fabs(r - kd) * F_DIFF_MOD_U127(kd); // 赤
////				} else {
////					b = 0; // 青
////					g = 0; // 緑
////					r = 0; // 赤
////				}
////			}

////			// 設定

////			// 青
////			if (b > 255.0) {
////				*(pL_t + 0) = 255;
////			} else if (b < 0.0) {
////				*(pL_t + 0) = 0;
////			} else {
////				*(pL_t + 0) = (unsigned char)b;
////			}

////			// 緑
////			if (g > 255.0) {
////				*(pL_t + 1) = 255;
////			} else if (g < 0.0) {
////				*(pL_t + 1) = 0;
////			} else {
////				*(pL_t + 1) = (unsigned char)g;
////			}

////			// 赤
////			if (r > 255.0) {
////				*(pL_t + 2) = 255;
////			} else if (r < 0.0) {
////				*(pL_t + 2) = 0;
////			} else {
////				*(pL_t + 2) = (unsigned char)r;
////			}

////			// ポインターの移動
////			pL_s += IMG_CHANNEL; // 入力用
////			pL_t += IMG_CHANNEL; // 出力用




////		} // for j
////	} // for i

////}



std::shared_ptr<imageHandler> singleImageHandler::convertTo(int type){
    cv::Mat ret;
    m.convertTo(ret, type);
    return std::shared_ptr<imageHandler>(new singleImageHandler(ret));
}

std::shared_ptr<imageHandler> singleImageHandler::cvtColor(int type){
    cv::Mat ret;
    cv::cvtColor(m, ret, type);
    return std::shared_ptr<imageHandler>(new singleImageHandler(ret.clone(), param));
}

std::shared_ptr<imageHandler> singleImageHandler::erode(cv::InputArray &kernel,
                                    			        cv::Point &anchor,
                                    			        int iteration,
                                    			        int borderType,
                                    			        const cv::Scalar
                                    			          &borderValue
                                    			        ){
    cv::Mat ret;
    cv::erode(m, ret, kernel, anchor, iteration, borderType, borderValue); 
    return std::shared_ptr<imageHandler>(new singleImageHandler(ret.clone(), param));
}

std::shared_ptr<imageHandler> singleImageHandler::RGB2Gray()
//std::shared_ptr<singleImageHandler> singleImageHandler::RGB2Gray()
{
    cv::Mat gray;
    if (m.channels()>1)
        cv::cvtColor(m, gray, CV_BGR2GRAY);
    else
        gray = m.clone();

    return std::shared_ptr<imageHandler>(new singleImageHandler(gray.clone()));
    //return std::shared_ptr<singleImageHandler>(new singleImageHandler(gray));
    //cv::Mat m_gray(m_height, m_width, CV_8U);
    //#pragma omp parallel
    //{
    //    #pragma omp for schedule(dynamic, m_height)
    //    for(int i=0; i<m_height; i++){
    //        unsigned char *ptr = m.ptr(i);
    //        unsigned char *ptr_gray = m_gray.ptr(i);
    //        //#pragma omp for schedule(dynamic, m_width)
    //        for(int j=0; j<m_width; j+=3){
    //             ptr_gray[j] = (int)cv::norm(cv::Point3i(ptr[j], ptr[j+1], ptr[j+2]));
    //        }
    //    }
    //}
    //cv::imshow("gray", m_gray);
    //cv::waitKey();
}

std::shared_ptr<imageHandler> singleImageHandler::abs(){
    cv::Mat ret(cv::abs(m.clone()));
    return std::shared_ptr<imageHandler>(new singleImageHandler(ret, param));
}

std::shared_ptr<imageHandler> singleImageHandler::inv(){
    cv::Mat ret((1./m.clone()));
    return std::shared_ptr<imageHandler>(new singleImageHandler(ret, param));
}

std::shared_ptr<imageHandler> singleImageHandler::mult(std::shared_ptr<imageHandler> &obj){
    cv::Mat ret = cv::Mat(m.rows, m.cols, m.type());
    cv::multiply(m, obj->m, ret);

    return std::shared_ptr<imageHandler>(new singleImageHandler(ret, param));
}
//void singleImageHandler::ConvertRGB2Gray()
//{
//    if(!m_LUT4GrayisCreated) set_RGB2Gray_table();
//	int res = OK;
//	BYTE *pGray = (BYTE*)(gray);
//	int n = 0;
//	for (int i = 0; i < m_height; i++) {
//		int ads = i * m_width * IMG_CHANNEL;
//		BYTE *pL = (BYTE*)(raw + ads);
//		for (int j = 0; j < m_width; j++) {
//			*pGray++ = m_RGB2Gray[*(pL+2)][*(pL+1)][*(pL+0)];
//			pL += 3;
//		} // for j
//	} // for i

//}

//void singleImageHandler::set_RGB2Gray_table()
//{
//	for( int r=0; r<256; r++ ) {
//		for( int g=0; g<256; g++ ) {
//			for( int b=0; b<256; b++ ) m_RGB2Gray[r][g][b] = (BYTE)(0.299*r + 0.587*g + 0.114*b + 0.5);
//		} // for g
//	} // for r
//}

////void make_feature_sw (const unsigned char *p, 
////                      const unsigned char *p_diff, 
////                      C_AROD_BlockFeatureManager *bfs)
////{
////	if (m_cParam.imagePreprocess_Type == IMAGE_PREPROCESS_RGB_DIFF) { // RGB相対輝度画像ならば、

////		ret = make_feature();

////	} else { // エッジ画像 or 通常画像ならば、

////		ret = make_feature();
////	}

////	return ret;
////}

std::shared_ptr<imageHandler> singleImageHandler::aveImg(){
    cv::Mat avg;
    auto obj = convertTo(CV_64F);
    cv::reduce(obj->m, avg, 0, CV_REDUCE_AVG);
    cv::reduce(avg, avg, 1, CV_REDUCE_AVG);
    obj->param = param;
    obj->param = avg.at<double>(0,0);
    return std::shared_ptr<imageHandler>(new singleImageHandler(m.clone(), obj->param));
}

std::shared_ptr<imageHandler> singleImageHandler::minImg(){
    cv::Mat avg;
    auto obj = convertTo(CV_64F);
    cv::reduce(obj->m, avg, 0, CV_REDUCE_MIN);
    cv::reduce(avg, avg, 1, CV_REDUCE_MIN);
    obj->param = param;
    obj->param = avg.at<double>(0,0);
    return std::shared_ptr<imageHandler>(new singleImageHandler(m.clone(), obj->param));
}

std::shared_ptr<imageHandler> singleImageHandler::maxImg(){
    cv::Mat avg;
    auto obj = convertTo(CV_64F);
    cv::reduce(obj->m, avg, 0, CV_REDUCE_MAX);
    cv::reduce(avg, avg, 1, CV_REDUCE_MAX);
    obj->param = param;
    obj->param = avg.at<double>(0,0);
    return std::shared_ptr<imageHandler>(new singleImageHandler(m.clone(), obj->param));
}

std::shared_ptr<imageHandler> singleImageHandler::isValueAmountForMoreThan(double th_val, double th_area){
    auto obj = RGB2Gray()->convertTo(CV_64F);
    int cntArea(0);
    for(int i=0; i<m_height; i++){
        //double* p = obj->m.ptr<double>(i);
        for(int j=0; j<m_width; j++){
            if(obj->m.at<double>(i,j) > th_val)  
            //if(p[j] > th_val)  
                cntArea++;
        }
    }
//    (*obj * 255)->convertTo(CV_8U)->resize()->view("amount", 1);

    double area(((double)cntArea) / (double)(m_width * m_height) * 100);
    obj->param["amount"].setValue(area > th_area ? 1 : 0);
    //obj=obj->aveImg();
    obj=obj->maxImg();
    //obj->param["no name"] = obj->param["amount"];

    return std::shared_ptr<imageHandler>(new singleImageHandler(m.clone(), obj->param));
}

std::shared_ptr<imageHandler> singleImageHandler::genComatrix(int divNum, int kaityouNum){
    cv::Mat avg;
    cv::Mat ret_m(m_height, m_width, m.type());
    std::deque<std::shared_ptr<imageHandler> > ret;
    std::vector<int> i_plus, j_plus;

    i_plus.push_back( 0);
    i_plus.push_back(-1);
    i_plus.push_back(-1);
    i_plus.push_back(-1);
    i_plus.push_back( 0);
    i_plus.push_back( 1);
    i_plus.push_back( 1);
    i_plus.push_back( 1);

    j_plus.push_back( 1);
    j_plus.push_back( 1);
    j_plus.push_back( 0);
    j_plus.push_back(-1);
    j_plus.push_back(-1);
    j_plus.push_back(-1);
    j_plus.push_back( 0);
    j_plus.push_back( 1);
     
    for (int k = 0; k < 8; k=8/divNum){
        for (int i = 0; i < m_height; i++) {
    	    unsigned char* p     = m.ptr(i);
			for (int j = 0; j < m_width - 1; j++) {
    	        if (m.channels() > 1){
                    int chNum(m.channels());
				    int k1_0 = p[j*chNum + 0];
				    int k1_1 = p[j*chNum + 1];
				    int k1_2 = p[j*chNum + 2];
					int k2_0 = p[(j+j_plus[k])*chNum+0];
					int k2_1 = p[(j+j_plus[k])*chNum+1];
					int k2_2 = p[(j+j_plus[k])*chNum+2];
					ret_m.ptr(k1_0)[k2_0*chNum + 0] ++;
					ret_m.ptr(k1_0)[k2_1*chNum + 1] ++;
					ret_m.ptr(k1_0)[k2_2*chNum + 2] ++;
					ret_m.ptr(k1_1)[k2_0*chNum + 0] ++;
					ret_m.ptr(k1_1)[k2_1*chNum + 1] ++;
					ret_m.ptr(k1_1)[k2_2*chNum + 2] ++;
					ret_m.ptr(k1_2)[k2_0*chNum + 0] ++;
					ret_m.ptr(k1_2)[k2_1*chNum + 1] ++;
					ret_m.ptr(k1_2)[k2_2*chNum + 2] ++;
					ret_m.ptr(k2_0)[k1_0*chNum + 0] ++;
					ret_m.ptr(k2_0)[k1_1*chNum + 1] ++;
					ret_m.ptr(k2_0)[k1_2*chNum + 2] ++;
					ret_m.ptr(k2_1)[k1_0*chNum + 0] ++;
					ret_m.ptr(k2_1)[k1_1*chNum + 1] ++;
					ret_m.ptr(k2_1)[k1_2*chNum + 2] ++;
					ret_m.ptr(k2_2)[k1_0*chNum + 0] ++;
					ret_m.ptr(k2_2)[k1_1*chNum + 1] ++;
					ret_m.ptr(k2_2)[k1_2*chNum + 2] ++;
    	        } else {
				    int k1 = p[j];
					int k2 = p[j+j_plus[k]];
					ret_m.ptr(k1)[k2] ++;
					ret_m.ptr(k2)[k1] ++;
    	        }
			} 
		} 
        ret.push_back(std::shared_ptr<imageHandler>(new singleImageHandler(ret_m)));
    }

    return std::shared_ptr<imageHandler>
            (new multiImageHandler(ret));
}

std::shared_ptr<imageHandler> singleImageHandler::calcEnergy(int divNum, int kaityouNum){
    return ((*genComatrix(divNum, kaityouNum)->convertTo(CV_64F))^2)->aveImg();
}

std::shared_ptr<imageHandler> singleImageHandler::calcContrast(int divNum, int kaityouNum){
    auto comats = genComatrix(divNum, kaityouNum);
    std::deque<std::shared_ptr<imageHandler> > ret;
    for (auto comat: comats->m_lst){
        double val = 0.0;
        for (int k=0; k<256; k++){
            for (int i=0; i<m_height; i++){
                unsigned char* p = comat->m.ptr(i);
        	    for (int j=0; j<m_width; j++)
                    if((i-j) == k || (j-i) == k) 
                        val += p[j];
            }
        }
        ret.push_back(std::shared_ptr<imageHandler>(new singleImageHandler(comat->m.clone(), val)));
    }

    return std::shared_ptr<imageHandler>(new multiImageHandler(ret));
}

std::shared_ptr<imageHandler> singleImageHandler::calcCorrelation(int divNum, int kaityouNum){
    return std::shared_ptr<imageHandler>();
}

std::shared_ptr<imageHandler> singleImageHandler::calcVariance(int divNum, int kaityouNum){

    auto comats = genComatrix(divNum, kaityouNum);
    std::deque<std::shared_ptr<imageHandler> > ret;
    for (auto comat: comats->m_lst){
        double nyu_x = 0.0;
   		for (int i = 0; i < 256; i++) {
    	    double p_x(0);
    	    unsigned char *p = comat->m.ptr(i);
    	    for(int j =0; j < 256; j++){
				p_x += p[j];
    	    }
    	    nyu_x += (double)i * p_x ;
		} 

    	double var = 0.0;
    	for (int i = 0; i < 256; i++) {
    	    unsigned char *p = comat->m.ptr(i);
			for (int j = 0; j < 256; j++) {
				var += (((double)i-nyu_x) * ((double)i-nyu_x) * p[j]);
			} 
		} 
        ret.push_back(std::shared_ptr<imageHandler>(new singleImageHandler(comat->m.clone(), var)));
    }
    return std::shared_ptr<imageHandler>(new multiImageHandler(ret));
}
    
std::shared_ptr<imageHandler> singleImageHandler::calcEntropy(int divNum, int kaityouNum){
    return std::shared_ptr<imageHandler>();
}

std::shared_ptr<imageHandler> singleImageHandler::calcSumEntropy(int divNum, int kaityouNum){
    return std::shared_ptr<imageHandler>();
}

std::shared_ptr<imageHandler> singleImageHandler::calcIDM(int divNum, int kaityouNum){

    auto comats = genComatrix(divNum, kaityouNum);
    std::deque<std::shared_ptr<imageHandler> > ret;
    for (auto comat: comats->m_lst){
	    double val = 0.0;

		for (int i = 0; i < 256; i++) {
            unsigned char* p=comat->m.ptr(i);
			for (int j = 0; j < 256; j++) {
				val += (1.0 / (1.0 + (i-j)*(i-j)) * p[j]);
			} 
		} 

        ret.push_back(std::shared_ptr<imageHandler>(new singleImageHandler(comat->m.clone(), val)));
    }
    return std::shared_ptr<imageHandler>(new multiImageHandler(ret));
}

void singleImageHandler::drawGridRect(int n_row, int n_col){

    getRect(n_row, n_col);

    for(int i=0; i<n_row; i++){
        for(int j=0; j<n_col; j++){
            cv::rectangle(m, rect_v2[i][j], cv::Scalar(0,255,0),
                          2);   
        }
    }
}

void singleImageHandler::viewGridedParam(std::string input_name){
//    int n_row(dived_img.size());    // 分割行列の行数
//    int n_col(dived_img[0].size()); // 分割行列の列数

//    for(int i=0; i<n_row; i++){
//        for(int j=0; j<n_col; j++){
//            
//            xIdx[i][j] = j*jStep;
//            yIdx[i][j] = i*iStep;
//        }
//    }
}

void singleImageHandler::getRect(int n_row, int n_col){
    mgrid(0, m_height, m_height/n_row, 
          0, m_width,  m_width/n_col);
    int dived_height(m_height/n_row), dived_width(m_width/n_col);

    rect_v2 = std::vector<std::vector<cv::Rect> >(n_row, 
                       std::vector<cv::Rect>  (n_col));

    for(int i=0; i<n_row; i++){
        for(int j=0; j<n_col; j++){
            rect_v2[i][j] = cv::Rect(xIdx[i][j], 
                         yIdx[i][j], 
                         dived_width, 
                         dived_height);
        }
    }
}

void singleImageHandler::mgrid(int iMin, int iMax, int iStep,
                         int jMin, int jMax, int jStep){
    int n_row((iMax-iMin)/iStep), n_col((jMax-jMin)/jStep);
    xIdx = yIdx = std::vector<std::vector<int> >(n_row,
                                std::vector<int>(n_col, 0));
    for(int i=0; i<n_row; i++){
        for(int j=0; j<n_col; j++){
            xIdx[i][j] = j*jStep;
            yIdx[i][j] = i*iStep;
        }
    }
}

std::shared_ptr<imageHandler> singleImageHandler::gridImage(int n_row, int n_col){
    mgrid(0, m_height, m_height/n_row, 
          0, m_width,  m_width/n_col);
    int dived_height(m_height/n_row), dived_width(m_width/n_col);

    std::deque<std::shared_ptr<imageHandler> > ret(n_row * n_col);

    getRect(n_row, n_col); // Get rectangle infomation as cv::Rect.

    for(int i=0; i<n_row; i++){
        for(int j=0; j<n_col; j++){
             ret[i*n_col + j] = std::shared_ptr<imageHandler>
                                (new singleImageHandler(m(rect_v2[i][j])));       
//            dived_img[i][j] = m(cv::Rect(xIdx[i][j], 
//                                         yIdx[i][j], 
//                                         dived_width, 
//                                         dived_height));
        }
    }

    return std::shared_ptr<imageHandler>(new multiImageHandler(ret));
}

void singleImageHandler::readImage(std::string &input_name){
    m = cv::imread(input_name);
    m_height = m.rows;
    m_width = m.cols;
}

void singleImageHandler::viewGridedImg(std::string input_name, int wTime){
    int n_row(dived_img.size());    // 分割行列の行数
    int n_col(dived_img[0].size()); // 分割行列の列数


    for(int i=0; i<n_row; i++){
        for(int j=0; j<n_col; j++){
            std::stringstream ss;
            ss << input_name << " Row No. = " << i << ", "
                       << " Col No. = " << j << std::endl;

            cv::imshow(ss.str(), dived_img[i][j]);
        }
    }
    cv::waitKey(wTime);
}

std::shared_ptr<imageHandler> singleImageHandler::gridMean(int n_row, int n_col){
    gridImage(n_row, n_col);
    cv::Mat ret(n_row, n_col, CV_8U);
    unsigned char *p;
    for (int i=0; i<n_row; i++){
        p = ret.ptr(i);
        for (int j=0; j<n_col; j++){
            p[j] = (unsigned char)*(cv::mean(dived_img[i][j]).val);
        }
    }
    return std::shared_ptr<singleImageHandler>(new singleImageHandler(ret));
}

std::shared_ptr<imageHandler> singleImageHandler::resize(int height, int width){
    cv::Mat ret;
    cv::Size size(width, height);
   // cv::resize(img_que[0], ret, size, CV_INTER_NEAREST);
    cv::resize(m, ret, size, CV_INTER_CUBIC);
    return std::shared_ptr<singleImageHandler>(new singleImageHandler(ret));
}

std::shared_ptr<imageHandler> singleImageHandler::expand(int height, int width, bool drawValue){
    //int h_ratio(height / m_height);
    //int w_ratio(width / m_width);
    int h_ratio(height / (m_height - height%m_height));
    int w_ratio(width / (m_width - width%m_width));



    cv::Mat ret(height, width, CV_8U);

    for(int i=0; i<height; i++){
        unsigned char *ret_ptr = ret.ptr(i);
        unsigned char *m_ptr = m.ptr(i / h_ratio);

        for(int j=0; j<width; j++){
            ret_ptr[j] = m_ptr[j / w_ratio];
        }
    }

    if(drawValue){
        for(int i=0; i<m_height; i++){
            unsigned char * m_ptr = m.ptr(i);
            for(int j=0; j<m_width; j++){
                std::stringstream ss;
            	ss << (int)m_ptr[j];
            	cv::putText(ret, 
                            ss.str(),
            	            cv::Point2i(j*h_ratio+h_ratio/2, 
                                        i*w_ratio+w_ratio/2), 
            	            CV_FONT_HERSHEY_SCRIPT_COMPLEX,
            	            //cv::FONT_HERSHEY_SIMPLEX, 
            	            0.006 * sqrt(h_ratio * h_ratio + w_ratio * w_ratio),
            	            cv::Scalar(0,0,m.at<unsigned char>(i,j)));
           }
        }
    }
    return std::shared_ptr<singleImageHandler>(new singleImageHandler(ret));
}

std::shared_ptr<imageHandler> singleImageHandler::pildown(int height, 
                                   int width, 
                                   int n_div, 
                                   bool drawValue){
    int n_row, n_col;

    std::deque<std::shared_ptr<imageHandler>> ret;
    int pre_check_row(0), pre_check_col(0);
    for(int i=2; i<n_div; i++){
        if(width   % i ||
           height  % i || 
           width  == i ||
           height == i )
            continue;
        ret.push_back(gridMean(i, i)->expand(height, width, drawValue));
    }

    return std::shared_ptr<imageHandler>(new multiImageHandler(ret));
}

std::shared_ptr<imageHandler> singleImageHandler::normalize(int minVal, 
                                                            int maxVal, 
                                                            int bitDepth){
    cv::Mat ret;
    //if (bitDepth != NULL)
    ret = m.clone();


    double minValOfMat, maxValOfMat;
    double delta(maxVal - minVal);
    cv::minMaxLoc(m, &minValOfMat, &maxValOfMat, int(), int());
    double deltaOfMat(maxValOfMat - minValOfMat);

    for(int i=0; i<m_height; i++){
        uchar* m_ptr(m.ptr(i));
        uchar* ret_ptr(ret.ptr(i));
        for(int j=0; j<m_width; j++)
            ret_ptr[j] = (m_ptr[j] - minValOfMat) * delta / deltaOfMat;
    }

    return std::shared_ptr<imageHandler>(new singleImageHandler(ret.clone(),param));

}

std::shared_ptr<imageHandler> singleImageHandler::normParam(
                                        double minVal1,
                                        double maxVal1,
                                        double minVal2,
                                        double maxVal2){

    double ret((param() - minVal1) * (maxVal2 - minVal2) / (maxVal1 - minVal1));

    return std::shared_ptr<imageHandler>(new singleImageHandler(m.clone(), ret));
}

std::shared_ptr<imageHandler> singleImageHandler::threshold(
    double thresh, 
    double maxVal, 
    int    threshType){

    cv::Mat ret;
    cv::threshold(m, ret, thresh, maxVal, threshType); 

    return std::shared_ptr<imageHandler>(new singleImageHandler(ret));
}


std::shared_ptr<imageHandler> singleImageHandler::paintMask(
    std::shared_ptr<imageHandler> &obj,
	int thresh){

    cv::Mat ret(m_height, m_width, m.type());

    for (int i=0; i<m.rows; i++){
        unsigned char* p     =     m.ptr(i);
        unsigned char* p_obj = obj->m.ptr(i);
        unsigned char* p_ret = ret.ptr(i);
        for (int j=0; j<m.cols; j++){
            if(p_obj[j] > thresh){ // 閾値を超えていたら。
                if(m.channels() > 1){ 
                    p_ret[j * 3 + 0] = 255; // 青く塗る。
                    p_ret[j * 3 + 1] = 0;
                    p_ret[j * 3 + 2] = 0;
                } else 
                    p_ret[j] = 255; // 白く塗る。
            } else {
                if(m.channels() > 1){ 
                    p_ret[j * 3 + 0] = p[j * 3 + 0];
                    p_ret[j * 3 + 1] = p[j * 3 + 1];
                    p_ret[j * 3 + 2] = p[j * 3 + 2];
                } else 
                    p_ret[j] = p[j]; // 白く塗る。
            }
        }
    }

    return std::shared_ptr<imageHandler>(new singleImageHandler(ret.clone(),param));
}                         

std::shared_ptr<imageHandler> singleImageHandler::paintMask(
    std::shared_ptr<imageHandler> &obj){

    cv::Mat ret(m_height, m_width, m.type());

    for (int i=0; i<m.rows; i++){
        unsigned char* p     =     m.ptr(i);
        unsigned char* p_obj = obj->m.ptr(i);
        unsigned char* p_ret = ret.ptr(i);
        for (int j=0; j<m.cols; j++){
            if(p_obj[j] > 255*0.5){ // 50%以上
                if(m.channels() > 1){ 
                    //p_ret[j * 3 + 0] = p[j * 3 + 0];
                    //p_ret[j * 3 + 1] = p[j * 3 + 1];
                    //p_ret[j * 3 + 2] = p[j * 3 + 2];
                    if(p_obj[j] > 255*0.9){         // 90%以上
                        p_ret[j * 3 + 0] = 0;
                        p_ret[j * 3 + 1] = 0;
                    	p_ret[j * 3 + 2] = 255;
                    } else if (p_obj[j] > 255*0.7){ // 70%以上
                        p_ret[j * 3 + 0] = 0;
                        p_ret[j * 3 + 1] = 255;
                    	p_ret[j * 3 + 2] = 0;
                    } else {
                        p_ret[j * 3 + 0] = p_obj[j];
                    	p_ret[j * 3 + 1] = p_obj[j];
                    	p_ret[j * 3 + 2] = p_obj[j];
                    }
                } else 
                    p_ret[j] = p_obj[j]; // 白く塗る。
            } else {
                if(m.channels() > 1){ 
                    p_ret[j * 3 + 0] = p[j * 3 + 0];
                    p_ret[j * 3 + 1] = p[j * 3 + 1];
                    p_ret[j * 3 + 2] = p[j * 3 + 2];
                } else 
                    p_ret[j] = p[j]; // 白く塗る。
            }
        }
    }

    return std::shared_ptr<imageHandler>(new singleImageHandler(ret));
}                         


std::shared_ptr<imageHandler> singleImageHandler::cpyParam(std::shared_ptr<imageHandler> &obj){
    param = obj->param;
    nearSim = obj->nearSim;
    return std::shared_ptr<imageHandler>(new singleImageHandler(m.clone(), param));
}

std::shared_ptr<imageHandler> singleImageHandler::interp(std::shared_ptr<imageHandler> &obj){
    cv::Mat ret = m.clone();
    cv::Mat o = cv::Mat::zeros(m_height, m_width, CV_8UC3);
    cv::Mat mask;
    cv::Mat mask_neg = obj->m > 0;

    cv::cvtColor(obj->m, mask, CV_RGB2GRAY);
    mask = (mask == 0)/255;
    cv::cvtColor(mask, mask, CV_GRAY2BGR);
    cv::multiply(ret, mask, ret);
    obj->m.copyTo(ret, mask_neg);

    return std::shared_ptr<imageHandler>(new singleImageHandler(ret, param));
}

std::shared_ptr<imageHandler> singleImageHandler::setParam(double input_param){
    return std::shared_ptr<imageHandler>(new singleImageHandler(m.clone(), input_param));
}

std::shared_ptr<imageHandler> singleImageHandler::setParam(parameters input_param){
    return std::shared_ptr<imageHandler>(new singleImageHandler(m.clone(), input_param));
}

std::shared_ptr<imageHandler> singleImageHandler::extractValidArea(std::shared_ptr<imageHandler> &obj){
    cv::Mat ret(m.clone());
    for(int i=0; i<m_height; i++){
        unsigned char* p = ret.ptr(i);
        unsigned char* op = obj->m.ptr(i);
        for(int j=0; j<m_width; j++){
            if(op[j] == 0){
                if(m.channels() > 1){
            	    p[j * 3 + 0] = 0;
            	    p[j * 3 + 1] = 0;
            	    p[j * 3 + 2] = 0;
            	} else {
            	    p[j] = 0;
            	}
            }
        }
    }
    return std::shared_ptr<imageHandler>(new singleImageHandler(ret, param));
}

void singleImageHandler::dump(std::string dirPath, 
          std::string fileName,
          std::string expand){
    
    std::stringstream ss;
    if (!dirPath.size())
        ss << fileName << "." << expand;
    else
        ss << dirPath << "\\" << fileName << "." << expand;
    cv::imwrite(ss.str().c_str(), m);
    //cv::imwrite(util::fcnt(fileName, dirPath, -1, expand), m);
}

// 描画用関数
void singleImageHandler::resizeView(int width, int height){
    resize(width, height)->view();       
}


void singleImageHandler::expandView(int width, int height){
    expand(width, height, true)->view();       
}

void singleImageHandler::pildownView(int width, int height, int n_div, bool drawValue){
    pildown(width, height, n_div, drawValue)->view();       
}

////void singleImageHandler::averaging_image(){
////    	ptr2vector(ps, m_v2_raw); // 画像データのベクトル化

////	if (v3_raw.size() < m_cParam.frameNumForAverage) { // 画像がたまっていない
////        int tmp = v3_raw.size();
////        
////		// 3次元RAWベクトルに追加
////		try {
////			v3_raw.push_back(m_v2_raw);
////		} catch (std::bad_alloc) {
////			return MEMORY_SET_ERROR;
////		}

////		// 2次元積算ベクトルに加算
////		for (int i = 0; i < v2_sum.size(); i++) {
////			for (int j = 0; j < v2_sum[i].size(); j++) v2_sum[i][j] += (double)m_v2_raw[i][j];
////		} 

////		if (m_cParam.outputAll_ImageLog == 1) {

////			// 画像の出力（前フレーム）
////			if (p_out != NULL) {
////				ARODErrorCode ret = output_image_happou_pre(p_out, detect_mask_pos_v);
////				if (ret != OK) return ret;
////			}
////		}

////		pass = true; // 画像ためこみ中
////		return OK;

////	} else { // 画像がたまった

////		// ①平均化
////		// ②2次元加算ベクトルから3次元RAWベクトルの先頭を減算
////		// ③2次元加算ベクトルに2次元RAWベクトルを加算
////		int num_i(v2_sum.size());
////		int num_j(v2_sum[0].size());
////		for (int i = 0; i < num_i; i++) {
////			for (int j = 0; j < num_j; j++) {
////				if (m_cParam.frameNumForAverage != 0)
////				    m_v2_ave[i][j] = (unsigned char)(v2_sum[i][j] / (double)m_cParam.frameNumForAverage);
////				v2_sum[i][j] -= (double)v3_raw[0][i][j];
////				v2_sum[i][j] += (double)m_v2_raw[i][j];
////			}
////		} // for i

////		// ２次元ベクトルのポインター化
////		if (pt != NULL) vector2ptr(m_v2_ave, pt);

////		try {
////			// 3次元RAWベクトルに追加
////			v3_raw.push_back(m_v2_raw);
////			// 3次元RAWベクトルの先頭の削除
////			v3_raw.pop_front();

////		} catch (std::bad_alloc) {
////			return MEMORY_SET_ERROR;
////		}

////	} // else 画像がたまった
////#if DEBUG2
//////    view4Debug(v2_sum, "v2_sum");
////    for(int i=0; i<v3_raw.size(); i++)
////        view4Debug(v3_raw[i], "m_v2.raw");
////#endif
////	pass = false; // 画像がたまっている。
////	return OK;
////}

void singleImageHandler::push_back(cv::Mat &input_m){
}

void singleImageHandler::pop_front(){
}

void singleImageHandler::push(cv::Mat &input_m, int th_num){
}

std::shared_ptr<imageHandler> singleImageHandler::canny(int threshold1, int threshold2){
    cv::Mat ret,input_m;
    if(m.channels() > 1)
        m.convertTo(input_m, CV_8UC3);
    else
        m.convertTo(input_m, CV_8U);
    cv::Canny(input_m, ret, threshold1, threshold2); 
    return std::shared_ptr<imageHandler>(new singleImageHandler(ret));
}

std::shared_ptr<imageHandler> singleImageHandler::distanceOfCircleEdge( 
    int threshold1, 
    int threshold2,
    int radius,
    int n_div,
    bool isDraw){

    //switch(tag){
    //case NORMAL:
        if (radius == NULL) radius = sqrt(m_width * m_width + m_height * m_height);
    
        // 後々修正
    	std::shared_ptr<imageHandler> cannied = 
            canny(threshold1, threshold2);
    	cv::Mat drawImg(cannied->m.clone()); // If isDraw is true, then drawImg is drawn
    	                            // a circle and a lines.
    	int cx(m_width/2), cy(m_height/2);


    	std::vector<double> r_lst;
    	for(double theta=0; 
    	    theta<2*3.14159265358979; 
    	    theta+=(2*3.14159265358979)/n_div){
            bool tof(false);
    	    for(int r=radius; r>=0; r--){
    		    int x = r * cos(theta) + cx;
    		    int y = r * sin(theta) + cy;
    	        if( x < m_width && y < m_height &&
    	            x >= 0 && y >= 0){
    	            if(cannied->m.at<unsigned char>(y,x)){
    	                r_lst.push_back(r);
    	                break;
                        tof = true;
    	            }
    	            if (isDraw)
    	                cv::line(drawImg, 
    	            	         cv::Point(x,y), 
    	            	         cv::Point(x,y), 
    	            	         255, 2);
    	        }
    	    }
            if(!tof)
                r_lst.push_back(radius);
    	}

    	cv::circle(drawImg, cv::Point(cx, cy), radius,  255, 2);

    	double r_sum(0);
    	for(auto r: r_lst) r_sum += r;

        param =  r_sum / r_lst.size();
    	std::shared_ptr<imageHandler> ret(
            new singleImageHandler(isDraw ? drawImg : cannied->m
            )); // Return Mean radius value.
        ret->param = param;
        return ret;
}


//singleImageHandler::~singleImageHandler(){
   // theApp->Run();
//}
// 演算子オーバーロード

std::shared_ptr<imageHandler> singleImageHandler::operator+(
        const std::shared_ptr<imageHandler> &obj){
    return std::shared_ptr<imageHandler>(new singleImageHandler(m + obj->m, param + obj->param));
}

std::shared_ptr<imageHandler> singleImageHandler::operator-(
        std::shared_ptr<imageHandler> obj){
    return std::shared_ptr<imageHandler>(new singleImageHandler(m - obj->m, param - obj->param));
}

std::shared_ptr<imageHandler> singleImageHandler::operator*(
        std::shared_ptr<imageHandler> obj){
    return std::shared_ptr<imageHandler>(new singleImageHandler(m * obj->m, param * obj->param));
}

std::shared_ptr<imageHandler> singleImageHandler::operator/(
        std::shared_ptr<imageHandler> obj){
    return std::shared_ptr<imageHandler>(new singleImageHandler(m / obj->m, param / obj->param));
}

std::shared_ptr<imageHandler> singleImageHandler::operator^(
        std::shared_ptr<imageHandler> obj){
    cv::Mat mm, obj_mm, ret;
    cv::multiply(m, m, mm);
    cv::multiply(obj->m, obj->m, obj_mm);
    cv::multiply(mm, obj_mm, ret);
    parameters ret_param(param);
    for(int i=0; i<obj->param(); i++)
        ret_param*=ret_param();
    return std::shared_ptr<imageHandler>(new singleImageHandler(ret, ret_param));
}


std::shared_ptr<imageHandler> singleImageHandler::operator>(const std::shared_ptr<imageHandler> &obj){
    //return this->param > obj->param ? std::shared_ptr<imageHandler>(new singleImageHandler(*this)) : obj;
    if (this->param > obj->param)// && this->nearSim > obj->nearSim)
        return std::shared_ptr<imageHandler>(new singleImageHandler(*this));
    else 
        return obj;
    //return this->param > obj->param && this->nearSim > this->nearSim ? std::shared_ptr<imageHandler>(new singleImageHandler(*this)) : obj;
}

std::shared_ptr<imageHandler> singleImageHandler::operator<(const std::shared_ptr<imageHandler> &obj){
    //return this->param < obj->param  ? std::shared_ptr<imageHandler>(new singleImageHandler(*this)) : obj;
    if (this->param < obj->param)// && this->nearSim > obj->nearSim)
        return std::shared_ptr<imageHandler>(new singleImageHandler(*this));
    else 
        return obj;
    //return this->param < obj->param  ? std::shared_ptr<imageHandler>(new singleImageHandler(*this)) : obj;
    //return this->param < obj->param  && this->nearSim < this->nearSim ? std::shared_ptr<imageHandler>(new singleImageHandler(*this)) : obj;
}

std::shared_ptr<imageHandler> singleImageHandler::operator>=(const std::shared_ptr<imageHandler> &obj){
    return this->param >= obj->param ? std::shared_ptr<imageHandler>(new singleImageHandler(*this)) : obj;
}

std::shared_ptr<imageHandler> singleImageHandler::operator<=(const std::shared_ptr<imageHandler> &obj){
    return this->param <= obj->param ? std::shared_ptr<imageHandler>(new singleImageHandler(*this)) : obj;
}

std::shared_ptr<imageHandler> singleImageHandler::operator==(const std::shared_ptr<imageHandler> &obj){
    return this->param == obj->param ? std::shared_ptr<imageHandler>(new singleImageHandler(*this)) : obj;
}

std::shared_ptr<imageHandler> singleImageHandler::operator&&(const std::shared_ptr<imageHandler> &obj){
    return this->param && obj->param ? std::shared_ptr<imageHandler>(new singleImageHandler(*this)) : obj;
}

std::shared_ptr<imageHandler> singleImageHandler::operator>(const double &val){
    double retVal(param > val ? 1 : 0);
    return std::shared_ptr<imageHandler>(new singleImageHandler(m.clone(), retVal));
}

std::shared_ptr<imageHandler> singleImageHandler::operator<(const double &val){
    double retVal(param < val ? 1 : 0);
    return std::shared_ptr<imageHandler>(new singleImageHandler(m.clone(), retVal));
}

std::shared_ptr<imageHandler> singleImageHandler::operator>=(const double &val){
    double retVal(param >= val ? 1 : 0);
    return std::shared_ptr<imageHandler>(new singleImageHandler(m.clone(), retVal));
}

std::shared_ptr<imageHandler> singleImageHandler::operator<=(const double &val){
    double retVal(param <= val ? 1 : 0);

    return std::shared_ptr<imageHandler>(new singleImageHandler(m.clone(), retVal));
}

std::shared_ptr<imageHandler> singleImageHandler::operator==(const double &val){
    double retVal(param == val ? 1 : 0);
    std::cout << retVal<<std::endl;

    return std::shared_ptr<imageHandler>(new singleImageHandler(m.clone(), retVal));
}

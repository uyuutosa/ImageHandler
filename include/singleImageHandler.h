/*!
    \file singleImageHandler.h
    \brief 画像処理・描画クラス。単一の画像を対象。
*/

#pragma once
#include <iostream>
#include <string.h>
#include <string>
#include <memory>
#include "imageHandler.h"
#include "multiImageHandler.h"
//#include "ocv_include.h"
//#include "ROOT_include.h"


/*!
    \brief 画像処理クラス
    \details 画像データを格納し、差分画像やエッジ画像等
            の画像処理を行う。データは画像やグラフとして
            表示することが出来る。
            単一の2次元データを対象。
 */
class singleImageHandler : 
    public imageHandler {
public:

// コンストラクタ

    /*!
     * @brief     コンストラクタ(unsigned char用)
     * @details   unsignedcharのデータをポインタで受け取る。
     *            画像の横と縦のサイズを指定する必要がある。
     * @param[in] input_raw   入力画像が格納された配列のポインタ。
     * @param[in] input_width 画像の行数。
     * @param[in] input_heigh 画像の列数。
     */
    singleImageHandler(unsigned char* input_raw, 
                       int input_width, 
                       int input_height);

    /*!
     *  @brief     コンストラクタ(cv::Mat用)
     *  @details   cv::Matのデータを受け取る。
     *  @param[in] input_m 入力画像。
     */
    singleImageHandler(cv::Mat input_m, double input_param=0, cv::Rect input_rect=cv::Rect());

    /*!
     *  @brief     コンストラクタ(cv::Mat用)
     *  @details   cv::Matのデータを受け取る。
     *  @param[in] input_m 入力画像。
     */
    singleImageHandler(cv::Mat input_m, parameters input_param, cv::Rect input_rect=cv::Rect());

    /*!
     *  @brief     コンストラクタ(std::pair<std::string, cv::Mat>用)
     *  @details   std::pair<std::string, cv::Mat>型のデータを受け取る。
     *  @param[in] input_map 入力画像。
     */
    singleImageHandler(std::pair<std::string, cv::Mat> &input_pair);


    /*!
     *  @brief   コンストラクタ(std::vector<std::vector<T> >用)
     *  @details 入力画像が格納されたコンテナを受け取る。
     *  @param   v 入力画像が格納されたコンテナ。
     */
    singleImageHandler(std::vector<std::vector<double> > &v);

    /*!
     * @brief     コンストラクタ(ファイル名)
     * @details   内部でcv::imread()を呼ぶ。
     * @param[in] input_name 画像ファイル名。
     */
    singleImageHandler(std::string input_name);

// 初期化関数
    
    /*!
     * @brief   ポインタのイニシャライズ
	 * @details 各画像のイニシャライズを行う。
     */
    void initializePointers();

    //std::shared_ptr<singleImageHandler> RGB2Gray();

    /*!
     * @brief カラー画像からグレー画像への変換
     * @param[in] type CV_8Uなどのcv::Matのビット深度。
     */
    virtual std::shared_ptr<imageHandler> convertTo(int type);

    /*!
     * @brief     カラー画像からグレー画像等への変換
     * @param[in] type 変換タイプ。
     */
    virtual std::shared_ptr<imageHandler> cvtColor(int type);

    /*!
     * @brief      画像を膨張させる。
     * @param[in]  kernel      カーネル。
     * @param[in]  anchor      アンカー。
     * @param[in]  iteration   膨張処理を行う回数。
     * @param[in]  borderType  ピクセル補完方法(cv::borderInterpolate()を参照。)
     * @param[in]  borderValue 一定の境界における境界値(cv::createMorphologyFilter()を参照。
     */
    virtual std::shared_ptr<imageHandler> erode(cv::InputArray  &kernel,
                                                cv::Point &anchor=cv::Point(-1, -1),
                                                int iteration=1,
                                                int borderType=cv::BORDER_CONSTANT, 
                                                const cv::Scalar
                                                    &borderValue=cv::morphologyDefaultBorderValue()
                                                );

    /*!
     * @brief カラー画像からグレー画像への変換
     */
    std::shared_ptr<imageHandler> RGB2Gray();


    /*!
     * @brief 絶対値への変換
     */
    virtual std::shared_ptr<imageHandler> abs();

    /*!
     * @brief 逆数。
     */
    virtual std::shared_ptr<imageHandler> inv();

    /*!
     * @brief 要素積。
     */
    virtual std::shared_ptr<imageHandler> mult(std::shared_ptr<imageHandler> &obj);

    
	//! @brief 複数画像から平均画像の生成
    virtual std::shared_ptr<imageHandler> aveImg();

	//!@brief 最小値を計算。
    virtual std::shared_ptr<imageHandler> minImg();

	//! @brief 最大値を計算。
    virtual std::shared_ptr<imageHandler> maxImg();

	//! @brief 領域に値が何割を占めるか計算。
    virtual std::shared_ptr<imageHandler> isValueAmountForMoreThan(double th_val, double th_area);

	//!@brief 同時生起行列の生成。
    //!
    virtual std::shared_ptr<imageHandler> genComatrix(int divNum, int kaityouNum);

	//!@brief エネルギーの計算。
    //!
    virtual std::shared_ptr<imageHandler> calcEnergy(int divNum, int kaityouNum);

	//!@brief コントラストの計算。
    //!
    virtual std::shared_ptr<imageHandler> calcContrast(int divNum, int kaityouNum);

	//!@brief 相関の計算。
    //!
    virtual std::shared_ptr<imageHandler> calcCorrelation(int divNum, int kaityouNum);

	//!@brief 分散の計算。
    //!
    virtual std::shared_ptr<imageHandler> calcVariance(int divNum, int kaityouNum);
    
	//!@brief エントロピーの計算計算。
    //!
    virtual std::shared_ptr<imageHandler> calcEntropy(int divNum, int kaityouNum);

	//!@brief サムエントロピーの計算。
    //!
    virtual std::shared_ptr<imageHandler> calcSumEntropy(int divNum, int kaityouNum);

	//!@brief 局所一様性の計算。
    //!
    virtual std::shared_ptr<imageHandler> calcIDM(int divNum, int kaityouNum);


    /*! 
     * @brief     画像の蓄積
     * @param[in] input_m パラメータの入力。
     */
    void push_back(cv::Mat &input_m);

    /*!
     * @brief 画像の抜き出し(前から)
     */
    void pop_front();

    /*! 
     * @brief     push_back()とpop_front()する。
     * @param[in] input_m パラメータの入力。
     */
    void push(cv::Mat &input_m, int th_num);

    /*!
     * @brief インデックス行列の作成。
     * @param iMin  i方向のグリッドの最小値。
     * @param iMax  i方向のグリッドの最大値。
     * @param iStep i方向のステップ数。
     * @param jMin  j方向のグリッドの最小値。
     * @param jMax  j方向のグリッドの最大値。
     * @param jStep j方向のステップ数。
     */
    void mgrid(int iMin, int iMax, int iStep,
               int jMin, int jMax, int jStep);

    /*!
     * @brief 画像の分割。
     * @param n_row 行数。
     * @param n_col 列数。
     */
    virtual std::shared_ptr<imageHandler> gridImage(int n_row, int n_col);

    /*!
     * @brief 画像ファイルの読み込み
     * @param input_name ファイル名。
     */
    void readImage(std::string &input_name);

    /*!
     * @brief 画像を領域分割し、各領域で平均値を求める。
     * @param n_row 行数。
     * @param n_col 列数。
     */
    virtual std::shared_ptr<imageHandler> gridMean(int n_row, int n_col);

    /*!
     * @brief 画像を縦n_row x 横n_colで区切り、線を引く。
     * @param n_row 行数。
     * @param n_col 列数。
     */
    virtual void drawGridRect(int n_row, int n_col);

    /*!
     * @brief 画像に格子状の線を入れる。
     * @param n_row 行数。
     * @param n_col 列数。
     */ 
    virtual void getRect(int n_row, int n_col);

    /*!
     * @brief cv::Cannyをつかって、エッジ抽出+細線化+2値化を行う。
     * @param threshold1 cv::Canny()の引数に対応。詳細はOpenCVのdocumantを参照。
     * @param threshold2 cv::Canny()の引数に対応。詳細はOpenCVのdocumantを参照。
     */ 
    virtual std::shared_ptr<imageHandler> canny(int threshold1=100, int threshold2=200);

    /*!
     * @brief     円エッジ間距離を求める。
     * @details   cv::Canny()によりエッジ抽出の後、円から\
     *            原点間での直線を引き、途中でエッジにあたる間での距離
     *            を求める。直線は円の角度0から2piまで2pi/n_divごとに
     *            行う。処理結果を画像で確認するときはisDrawをtrueにする。
     * @param[in] threshold1 cv::Canny()の引数に対応。詳細はOpenCVのdocumantを参照。
     * @param[in] threshold2 cv::Canny()の引数に対応。詳細はOpenCVのdocumantを参照。
     * @param[in] radius     円の半径。
     * @param[in] n_div      走査する直線の数。
     * @param[in] isDraw     処理結果の画像を描画するかを指定。
     */ 
    virtual std::shared_ptr<imageHandler> distanceOfCircleEdge(
                                int threshold1=100, 
                                int threshold2=200,
                                int radius=NULL,
                                int n_div=10,
                                bool isDraw=false);


    /*!
     * @brief     cv::Resizeを使って画像をリサイズする。
     * @param[in] height 画像の高さ [pix]。
     * @param[in] width  画像の幅 [pix]。
     */ 
    virtual std::shared_ptr<imageHandler> resize(
                                            int height=640, 
                                            int width=880
                                            );

    /*!
     * @brief     画像を拡大する。
     * @param[in] height 画像の高さ [pix]。
     * @param[in] width  画像の幅   [pix]。
     */ 
    virtual std::shared_ptr<imageHandler> expand(int height, int width, bool drawValue);

    /*!
     * @rief 画像ピラミッドをexpand()を使って作成する。
     * @param[in] height 画像の高さ [pix]。
     * @param[in] width  画像の幅   [pix]。
     * @param[in] n_div  画像の分割数。ただし、出力される画像のピクセル数は原画像のそれの
     *                   定数倍物のみを選択するため、必ずしも設定した分割数の
     *                   画像を得られるわけではない。
     * @param[in] isDraw     処理結果の画像を描画するかを指定。
     */ 
    virtual std::shared_ptr<imageHandler> pildown(
        int height, 
        int width, 
        int n_div, 
        bool drawValue
        );

    /*!
     * @brief     ノーマライズ
     * @param[in] minVal
     * @param[in] maxVal
     * @param[in] bitDepth
     */ 
    virtual std::shared_ptr<imageHandler> normalize(int minVal, 
                                                    int maxVal, 
                                                    int bitDepth );

    //! @brief     パラメータをノーマライズする。
    //! @param[in] minVal パラメータの最小値　
    //! @param[in] maxVal パラメータの最大値　
    virtual std::shared_ptr<imageHandler> normParam(
        double minVal1=0,
        double maxVal1=1,
        double minVal2=0,
        double maxVal2=1);

    //! @brief 閾値を計算する。
    //! @param[in] thresh      閾値。
    //! @param[in] maxVal      最大値。
    //! @param[in] threashType 閾値のタイプ。
    virtual std::shared_ptr<imageHandler> threshold(
                                        double thresh, 
                                        double maxVal, 
                                        int    threshType);

    //! @brief マスク用行列で指定した箇所に色を付ける。
    //! @param[in] obj    マスク用行列。
    //! @param[in] thresh マスクの閾値。
    virtual std::shared_ptr<imageHandler> paintMask(
                                        std::shared_ptr<imageHandler> &obj,
                                        int thresh);

    //! @brief     マスク用行列で指定した箇所に色を付ける。
    //! @details   マスク用行列の色情報を用いてマスクする。
    //! @param[in] obj    マスク用行列。
    virtual std::shared_ptr<imageHandler> paintMask(
                                        std::shared_ptr<imageHandler> &obj);

    ///! @brief     objのparamをthisにコピーする。
    ///! @param[in] obj オブジェクト。
    virtual std::shared_ptr<imageHandler> cpyParam(std::shared_ptr<imageHandler> &obj);

    //! @brief     画像の0以外の領域を上書きする。
    //! @param[in] obj オブジェクト。
    virtual std::shared_ptr<imageHandler> interp(std::shared_ptr<imageHandler> &obj);

    //! @brief     パラメータを代入する。
    //! @param[in] obj オブジェクト。
    virtual std::shared_ptr<imageHandler> setParam(double input_param);

    //! @brief     パラメータを代入する。
    //! @param[in] input_param オブジェクト。
    virtual std::shared_ptr<imageHandler> setParam(parameters input_param);

    virtual std::shared_ptr<imageHandler> extractValidArea(std::shared_ptr<imageHandler> &obj);

    /*! 
     * @brief     画像を出力する。
     * @param[in] dirPath  ディレクトリパス。
     * @param[in] fileName ファイル名。
     * @param[in] expand   拡張子。
     */
    virtual void dump(std::string dirPath, 
                      std::string fileName,
                      std::string expand="jpg");


    //! @brief     外接矩形の情報を得る。
    virtual std::shared_ptr<imageHandler> getBoundingBoxInfo();

    //! @brief     矩形を描画する。
    //! @param[in] color      色情報。
    //! @param[in] thickness  線の厚さ。
    //! @param[in] lineType   線種。
    //! @param[in] input_rect 矩形情報(指定しない場合はメンバ変数rectが使用される)。
    //! @param[in] shift       
    virtual std::shared_ptr<imageHandler> rectangle(
        cv::Scalar& color=cv::Scalar(150), 
        int thickness=1, 
        int lineType=8, 
        cv::Rect input_rect = cv::Rect(), 
        int shift=0
        );

    //! @brief     保持している矩形領域情報内の画素に輝度があるかをチェックする。
    //! @details   矩形領域情報のcv::Rect()を保持しているのはthisであることに注意。
    //! @param[in] obj 画像を保持する画像処理クラスのインスタンス。
    virtual std::shared_ptr<imageHandler> checkValidArea(std::shared_ptr<imageHandler> &obj);

    //! @brief     与えられた矩形領域情報を用いて画像をクリップする。
    //! @param[in] obj 矩形領域情報cv::Rect()を保持する画像処理クラスのインスタンス。
    virtual std::shared_ptr<imageHandler> clip(std::shared_ptr<imageHandler> &obj);

    ////! @brief     与えられた矩形領域情報を用いて画像をクリップする。
    //! @param input_rect 矩形領域情報。
    //! @param inv        false: 矩形領域をゼロクリアする。true: 矩形領域の画像を取得する。
    virtual std::shared_ptr<imageHandler> clip(cv::Rect &input_rect, bool inv=false);

// 描画用関数

    /*! 
     * @brief     画像を表示する。
     * @param[in] input_name 画像タイトル。
     * @param[in] wTime      画像表示の待機時間。
	 * @param[in] isMovie    動画で表示するか。
     */
	virtual void view(std::string input_name = "obj", int wTime = 0, bool isMovie = false);

    /*! 
     * @brief     画像の輝度ヒストグラムを表示する。
     * @param[in] binNum  ヒストグラムのビンの数。
     * @param[in] xMin    x軸の最小値
     * @param[in] xMax    x軸の最大値
     * @param[in] yMin    y軸の最小値
     * @param[in] yMax    y軸の最大値
     */
    virtual void histView(
         std::string name="obj1", 
         int binNum = 100, 
         int xMin = 0, 
         int xMax = 256,
         int yMin = 0,
         int yMax = 2e4);

    // 画像マスク、線、円、矩形の描画等。

    //! @brief     外枠線を描画する。 
    //! @param[in] color     色情報。
    //! @param[in] thickness 線の太さ。
    //! @param[in] lineType  線の種類。
    //! @param[in] shift     Number of fractional bits in the point coordinates.
    virtual std::shared_ptr<imageHandler> drawOuterFrame(
        cv::Scalar &color,
        int thickness=1, 
        int lineType=8, 
        int shift=0);

    //! @brief     2値化画像をラベリングする。
    //! @details   0はラベリングされていない領域。番号は1から始まる。
    virtual std::shared_ptr<imageHandler> labeling(bool isMulti=false, int threshBreakNum=9999, int times=100);

    //! @brief     画像サイズにあわせてパラメータを画像中心に描画する。
    //! @param[in] val       パラメータ。
    //! @param[in] fontFace  フォント名。
    //! @param[in] color     色。
    //! @param[in] thickness 文字の厚さ。
    virtual std::shared_ptr<imageHandler> putCenterParam(
        int fontFace = cv::FONT_HERSHEY_SIMPLEX,
        cv::Scalar color=cv::Scalar(255,255,255), 
        int thickness=1
    );
    
    //! @brief 閾値以上の点群を外接する矩形を描画する。
    virtual std::shared_ptr<imageHandler> drawOuterFrameAroundObjects(int thresh);

    //! @brief 閾値以上の点群を塗りつぶす。
    //! @brief color 色情報。
    virtual std::shared_ptr<imageHandler> fillObjects(cv::Mat mask, cv::Scalar &color);


    // 画像処理後をした後に表示する高級関数群。

    /*! 
     * @brief     領域分割された画像を表示する。
     * @param[in] name  画像タイトル。
     * @param[in] wTime 画像表示の待機時間。
     */
    virtual void viewGridedImg(std::string name="obj", int wTime=0);

    /*! 
     * @brief     領域分割されたパラメータを表示する。
     * @param[in] name  画像タイトル。
     */
    virtual void viewGridedParam(std::string name="obj");

    /*! 
     * @brief     リサイズした画像を表示する。
     * @param[in] width  画像の幅   [pix]。
     * @param[in] height 画像の高さ [pix]。
     */
    virtual void resizeView(int width, int height);

    /*! 
     * @brief     expandした画像を表示する。
     * @param[in] width  画像の幅   [pix]。
     * @param[in] height 画像の高さ [pix]。
     */
    virtual void expandView(int width, int height);

    /*! 
     * @brief     expandで画像ピラミッドをつくり、それを表示する。
     * @param[in] width  画像の幅   [pix]。
     * @param[in] height 画像の高さ [pix]。
     * @param[in] n_div  画像の分割数。ただし、出力される画像のピクセル数は原画像のそれの
     *                   定数倍物のみを選択するため、必ずしも設定した分割数の
     *                   画像を得られるわけではない。
     */
    virtual void pildownView(int width, int height, int n_div, bool drawValue);



    //int m_width, m_height;   //! @brief 画像の幅、高さ [pix]
    //cv::Mat m;                                    //! @brief 画像格納用変数(cv::Mat)。 
//protected:

    std::vector<std::vector<int> > xIdx, yIdx;    //! @brief インデックス番号
    std::vector<std::vector<cv::Mat> > dived_img; //! @brief 分割された画像を格納するコンテナ。
    cv::Mat m_float;                              //! @brief 画像格納用変数(cv::Mat, float)。 
	unsigned char *m_raw;	                      //! @brief 画像格納用変数(unsigned char*)

    std::deque<cv::Mat> img_que;                  //! @brief 画像の格納キュー

    std::vector<std::vector<cv::Rect> > rect_v2;     //! @brief 画像切り抜き用矩形情報格納キュー


    std::shared_ptr<imageHandler> operator+(
        const std::shared_ptr<imageHandler> &obj);

    std::shared_ptr<imageHandler> operator-(
        std::shared_ptr<imageHandler> obj);

    std::shared_ptr<imageHandler> operator*(
        std::shared_ptr<imageHandler> obj);

    std::shared_ptr<imageHandler> operator/(
        std::shared_ptr<imageHandler> obj);

    std::shared_ptr<imageHandler> operator^(
        std::shared_ptr<imageHandler> obj);


    std::shared_ptr<imageHandler> singleImageHandler::operator+(
	        const double &val){
        cv::Mat retM = m.clone();
        if (m.channels() > 1){
            retM += cv::Scalar(val, val, val);
        } else 
            retM += val;
	    return std::shared_ptr<imageHandler>(new singleImageHandler(retM));
	}

    std::shared_ptr<imageHandler> singleImageHandler::operator-(
	        const double &val){
        cv::Mat retM = m.clone();
        if (m.channels() > 1){
            retM -= cv::Scalar(val, val, val);
        } else 
            retM -= val;
	    return std::shared_ptr<imageHandler>(new singleImageHandler(retM));
	}

    std::shared_ptr<imageHandler> singleImageHandler::operator*(
	        const double &val){
        cv::Mat retM = m.clone();
        if (m.channels() > 1){
            retM = cv::Mat(m.rows, m.cols, m.type(), cv::Scalar(val, val, val));
            retM = retM.mul(m);
        } else 
            retM *= val;
	    return std::shared_ptr<imageHandler>(new singleImageHandler(retM));
	}

    std::shared_ptr<imageHandler> singleImageHandler::operator/(
	        const double &val){
        cv::Mat retM = m.clone();
        if (m.channels() > 1){
            retM = cv::Mat(m.rows, m.cols, m.type(), cv::Scalar(1./val, 1./val, 1./val));
            retM = retM.mul(m);
        } else 
            retM /= val;
	    return std::shared_ptr<imageHandler>(new singleImageHandler(retM));
	}

    std::shared_ptr<imageHandler> singleImageHandler::operator^(
	        const double &val){
        cv::Mat retM = m.clone();
        if (m.channels() > 1){
        	for(int i=0; i<val; i++)
                retM = retM.mul(m);
        } else 
            for(int i=0; i<val; i++) retM *= retM;
	    return std::shared_ptr<imageHandler>(new singleImageHandler(retM));
	}

    std::shared_ptr<imageHandler> operator>(
        const std::shared_ptr<imageHandler> &obj);

    std::shared_ptr<imageHandler> operator<(
        const std::shared_ptr<imageHandler> &obj);

    std::shared_ptr<imageHandler> operator>=(
        const std::shared_ptr<imageHandler> &obj);

    std::shared_ptr<imageHandler> operator<=(
        const std::shared_ptr<imageHandler> &obj);

    std::shared_ptr<imageHandler> operator==(
        const std::shared_ptr<imageHandler> &obj);

    std::shared_ptr<imageHandler> operator&&(
        const std::shared_ptr<imageHandler> &obj);


    std::shared_ptr<imageHandler> operator>(
        const double &val);

    std::shared_ptr<imageHandler> operator<(
        const double &val);

    std::shared_ptr<imageHandler> operator>=(
        const double &val);

    std::shared_ptr<imageHandler> operator<=(
        const double &val);

    std::shared_ptr<imageHandler> operator==(
        const double &val);
   // ~singleImageHandler();


};


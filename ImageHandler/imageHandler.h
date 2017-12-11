/*!
 * @file    imageHandler.h
 * @brief   画像処理クラス
 * @details 画像データを格納し、差分画像やエッジ画像等
 *          の画像処理を行う。データは画像やグラフとして
 *          表示することが出来る。
 * @date    201?/0?/??
 */

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <cmath>
#include <memory>
#include <opencv2\opencv.hpp>
#include "parameter.h"
#include "Util.h"
//#include "ROOT_include.h"



/*!
    \brief 画像処理クラス
    \details 画像データを格納し、差分画像やエッジ画像等
            の画像処理を行う。データは画像やグラフとして
            表示することが出来る。
 */
class imageHandler {
public:

// コンストラクタ

    /*!
        \brief コンストラクタ(空)
        \details 何もしない。
     */
    imageHandler();

    /*!
        \brief コンストラクタ(cv::Mat型)
     */
    imageHandler(cv::Mat m, double input_param=0, cv::Rect input_rect=cv::Rect());

    /*!
        \brief コンストラクタ(cv::Mat型)
     */
    imageHandler(cv::Mat m, parameters input_params, cv::Rect input_rect=cv::Rect());

    /*!
     *  \brief コンストラクタ(std::pair<std::string, cv::Mat>型)
     *  @param input_pair 画像名と画像の対応の連想配列。
     */
    imageHandler(std::pair<std::string, cv::Mat> &input_pair);

    /*!
     *  \brief コンストラクタ(std::map<std::string, cv::Mat>型)
     *  @param input_map 画像名と画像の対応の連想配列。
     */
    imageHandler(std::map<std::string, cv::Mat> &input_map);

// 初期化関数

    /*!
     * @brief   ポインタのイニシャライズ
	 * @details 各画像のイニシャライズを行う。
     */
    virtual void initializePointers();

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
    virtual std::shared_ptr<imageHandler> RGB2Gray();

    /*!
     * @brief 絶対値への変換
     */
    virtual std::shared_ptr<imageHandler> abs();

    /*!
     * @brief 逆数。
     */
    virtual std::shared_ptr<imageHandler> inv();

    //! @brief 要素積。
    virtual std::shared_ptr<imageHandler> mult(std::shared_ptr<imageHandler> &obj);

    
	//! @brief 複数画像から平均画像の生成
    //!
    virtual std::shared_ptr<imageHandler> aveImg();

    
	//!@brief 最小値を計算。
    //!
    virtual std::shared_ptr<imageHandler> minImg();

	//! @brief 最大値を計算。
    //! 
    virtual std::shared_ptr<imageHandler> maxImg();

	//! @brief 領域に値が何割を占めるか計算。
    //! @param[in] thresh 閾値
    //! @param[in] area   面積(パーセント)
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


    virtual std::shared_ptr<imageHandler> nearSimilar(int n_row, int n_col);

    /*! 
     * @brief     画像の蓄積
     * @param[in] input_m パラメータの入力。
     */
    virtual void push_back(cv::Mat &input_m);

    /*! 
     * @brief     画像の抜き出し
     * @param[in] input_m パラメータの入力。
     */
    virtual void pop_front();

    /*! 
     * @brief     push_backとpop_frontを行う。
     * @param[in] input_m パラメータの入力。
     * @param[in] th_num  キューのサイズの閾値。
     */
    virtual void push(cv::Mat &input_m, int th_num);


    /*!
     * @brief インデックス行列の作成。
     * @param iMin  i方向のグリッドの最小値。
     * @param iMax  i方向のグリッドの最大値。
     * @param iStep i方向のステップ数。
     * @param jMin  j方向のグリッドの最小値。
     * @param jMax  j方向のグリッドの最大値。
     * @param jStep j方向のステップ数。
     */
    virtual void mgrid(int iMin, int iMax, int iStep,
               int jMin, int jMax, int jStep);

    /*!
     * @brief 画像の分割。
     * @param n_row 行数。
     * @param n_col 列数。
     */
    virtual std::shared_ptr<imageHandler> gridImage(int n_row, int n_col);

    /*!
     * @brief 画像ファイルの読み込み
     * @param name ファイル名。
     */
    virtual void readImage(std::string &name);

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
    virtual std::shared_ptr<imageHandler> canny(int threshold1=100, 
                                                int threshold2=200);

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
    virtual std::shared_ptr<imageHandler> resize(int height=640, int width=880);

    /*!
     * @brief     画像を拡大する。
     * @param[in] height 画像の高さ [pix]。
     * @param[in] width  画像の幅   [pix]。
     */ 
    virtual std::shared_ptr<imageHandler> expand(int height, int width, bool drawValue);

    /*!
     * @brief     画像ピラミッドをexpand()を使って作成する。
     * @param[in] height 画像の高さ [pix]。
     * @param[in] width  画像の幅   [pix]。
     * @param[in] n_div  画像の分割数。ただし、出力される画像のピクセル数は原画像のそれの
     *                   定数倍物のみを選択するため、必ずしも設定した分割数の
     *                   画像を得られるわけではない。
     * @param[in] isDraw     処理結果の画像を描画するかを指定。
     */ 
    virtual std::shared_ptr<imageHandler> pildown(int height, int width, int n_div, bool drawValue);

    /*!
     * @brief            パラメータのマップを作成する。
     */ 
    virtual std::shared_ptr<imageHandler> genParamMap(int n_row, int n_col);

    
    //!@brief            ノーマライズ
    //! 
    virtual std::shared_ptr<imageHandler> normalize(int minVal,
                                                    int maxVal,
                                                    int bitDepth);


    //! @brief     パラメータをノーマライズする。
    //! @param[in] minVal パラメータの最小値　
    //! @param[in] maxVal パラメータの最大値　
    virtual std::shared_ptr<imageHandler> normParam(
        double minVal1=0,
        double maxVal1=1,
        double minVal2=0,
        double maxVal2=1
        );

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

    //! @brief     二つのobjのparamをthisにコピーする。
    //! @param[in] obj オブジェクト。
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

    /*! 
     * @brief     キューの軸に配列をソートする。
     * @param[in] dirPath  ディレクトリパス。
     * @param[in] fileName ファイル名。
     * @param[in] expand   拡張子。
     */
    virtual std::shared_ptr<imageHandler> sortForQue();

    /*! 
     * @brief     キューの軸に配列のインデックスをソートする。
     */
    virtual std::shared_ptr<imageHandler> sortForQueIdx();

    /*! 
     * @brief     与えられたインデックス情報を元に、
     *            キューの軸に配列のインデックスをソートする。
     */
    virtual std::shared_ptr<imageHandler> sortForQueWithObj(
        std::shared_ptr<imageHandler> input_obj);

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

    //! @brief     複数画像を足し合わせ、閾値より大きい値を有効とする2値画像を返す。
    //! @param[in] thresh 閾値
    virtual std::shared_ptr<imageHandler> superImpose(int thresh=0);

// 描画用関数

    /*! 
     * @brief     画像を表示する。
     * @param[in] name  画像タイトル。
     * @param[in] wTime 画像表示の待機時間。
     */
    virtual void view(std::string name="obj", int wTime=0);

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
    //! @param[in] color       色情報。
    //! @param[in] thickness   線の太さ。
    //! @param[in] lineType    線の種類。
    //! @param[in] shift       Number of fractional bits in the point coordinates.
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
		int thickness=1);
    
    //! @brief 閾値以上の点群を外接する矩形を描画する。
    virtual std::shared_ptr<imageHandler> drawOuterFrameAroundObjects();

    //! @brief 閾値以上の点群を塗りつぶす。
    //! @brief color 色情報。
    virtual std::shared_ptr<imageHandler> fillObjects(cv::Mat mask, cv::Scalar &color);

    //! @brief 文字列を描画する。
    //! @param[in] text             文字列。
    //! @param[in] org              文字列の左下座標。
    //! @param[in] fontFace         フォントタイプ。以下から選択。
    //!                             FONT_HERSHEY_PLAIN, 
    //!                             FONT_HERSHEY_DUPLEX, 
    //!                             FONT_HERSHEY_COMPLEX,
    //!                             FONT_HERSHEY_TRIPLEX, 
    //!                             FONT_HERSHEY_COMPLEX_SMALL,
    //!                             FONT_HERSHEY_SCRIPT_SIMPLEX,
    //!                             FONT_HERSHEY_SCRIPT_COMPLEX
    //! @param[in] fontScale        フォントの大きさ。
    //! @param[in] color            色情報
    //! @param[in] thickness        線の太さ。
    //! @param[in] lineType         線種。
    //! @param[in] bottomLeftOrigin trueの時、画像の原点は左下になる。falseの時は右上。
    virtual std::shared_ptr<imageHandler> putText(std::string text,
                                                  cv::Point org,
                                                  int fontFace,
                                                  double fontScale,
                                                  cv::Scalar color,
                                                  int thickness=1,
                                                  int lineType=8,
                                                  bool bottomLeftOrigin=false);

    // 画像処理後をした後に表示する高級関数群。

    /*! 
     * @brief     領域分割された画像を表示する。
     * @param[in] name  画像タイトル。
     * @param[in] wTime 画像表示の待機時間。
     */
    virtual void viewGridedImg(std::string name="obj", int wTime=0);

     
    //! @brief     領域分割されたパラメータを表示する。
    //! @param[in] name  画像タイトル。
    virtual void viewGridedParam(std::string name="obj");

    //!@brief     リサイズした画像を表示する。
    //!@param[in] width  画像の幅   [pix]。
    //!@param[in] height 画像の高さ [pix]。
    virtual void resizeView(int width, int height);

    //!@brief     expandした画像を表示する。
    //!@param[in] width  画像の幅   [pix]。
    //!@param[in] height 画像の高さ [pix]。
    virtual void expandView(int width, int height);

    //! @brief     expandで画像ピラミッドをつくり、それを表示する。
    //! @param[in] width  画像の幅   [pix]。
    //! @param[in] height 画像の高さ [pix]。
    //! @param[in] n_div  画像の分割数。ただし、出力される画像のピクセル数は原画像のそれの
    //!               定数倍物のみを選択するため、必ずしも設定した分割数の
    //!               画像を得られるわけではない。
    virtual void pildownView(int width, int height, int n_div, bool drawValue);

    /*! 
     * @brief     複数画像を並べる。
     * @param[in] n_row 行数。
     * @param[in] n_col 列数。
     */
    virtual std::shared_ptr<imageHandler> stichImg(int n_row, int n_col);

    //! @brief 格納している画像の数を返す。
    virtual int size();

// 比較用関数。
    //!@brief parameterのリファレンスを得る。
    virtual parameters& getRefofParam();

    //!@brief すべてのパラメータが0より大きいか判定する。 
    virtual bool any();

    //!@brief 少なくともひとつのパラメータが0より大きいか判定する。 
    virtual bool all();


// 演算子オーバロード
    virtual std::shared_ptr<imageHandler> operator+(
        const std::shared_ptr<imageHandler> &obj);

    virtual std::shared_ptr<imageHandler> operator-(
        std::shared_ptr<imageHandler> obj);

    virtual std::shared_ptr<imageHandler> operator*(
        std::shared_ptr<imageHandler> obj);

    virtual std::shared_ptr<imageHandler> operator/(
        std::shared_ptr<imageHandler> obj);

    virtual std::shared_ptr<imageHandler> operator^(
        std::shared_ptr<imageHandler> obj);

    virtual std::shared_ptr<imageHandler> imageHandler::operator+(
	        const double &val){
        return std::shared_ptr<imageHandler>();
	}

    virtual std::shared_ptr<imageHandler> imageHandler::operator-(
	        const double &val){
        return std::shared_ptr<imageHandler>();
	}

    virtual std::shared_ptr<imageHandler> imageHandler::operator*(
	        const double &val){
        return std::shared_ptr<imageHandler>();
	}

    virtual std::shared_ptr<imageHandler> imageHandler::operator/(
	        const double &val){
        return std::shared_ptr<imageHandler>();
	}

    virtual std::shared_ptr<imageHandler> imageHandler::operator^(
	        const double &val){
        return std::shared_ptr<imageHandler>();
	}

    virtual std::shared_ptr<imageHandler> operator>(
        const std::shared_ptr<imageHandler> &obj);

    virtual std::shared_ptr<imageHandler> operator<(
        const std::shared_ptr<imageHandler> &obj);

    virtual std::shared_ptr<imageHandler> operator>=(
        const std::shared_ptr<imageHandler> &obj);

    virtual std::shared_ptr<imageHandler> operator<=(
        const std::shared_ptr<imageHandler> &obj);

    virtual std::shared_ptr<imageHandler> operator==(
        const std::shared_ptr<imageHandler> &obj);

    virtual std::shared_ptr<imageHandler> operator&&(
        const std::shared_ptr<imageHandler> &obj);

    virtual std::shared_ptr<imageHandler> operator>(
        const double &val);

    virtual std::shared_ptr<imageHandler> operator<(
        const double &val);

    virtual std::shared_ptr<imageHandler> operator>=(
        const double &val);

    virtual std::shared_ptr<imageHandler> operator<=(
        const double &val);

    virtual std::shared_ptr<imageHandler> operator==(
        const double &val);


    /*! ROOT用変数。
     */
    //TCanvas* c;
    //TH1* h;
    //TF1* f;
//    std::unique_ptr<TApplication> theApp;

   // ~imageHandler();

   cv::Mat m;               //!< 画像格納用変数(cv::Mat)。 
//protected:
   int m_width, m_height;   //!< 画像の幅、高さ [pix]
   int m_div_width, m_div_height;

   parameters param;            //!< パラメータ;
   double nearSim;            //!< パラメータ;

   std::string name;        //!< 画像名。 

   std::vector<std::string> namelst;//!< 画像名リスト。

   cv::Rect rect; //! 領域情報

   
   
   std::deque<std::shared_ptr<imageHandler>> m_lst;        //! @brief　singleImageHandlerのリスト。

};



/*!
 * @file    multiImageHandler.h
 * @brief   �摜�����N���X
 * @details �摜�f�[�^���i�[���A�����摜��G�b�W�摜��@par
 *           �̉摜�������s���B�f�[�^�͉摜��O���t�Ƃ���@par
 *           �\�����邱�Ƃ��o����B
 * @date    201?/??/??
 */
#pragma once
#include "imageHandler.h"
#include "singleImageHandler.h"
//#include "util.h"



/*!
 * @class   multiImageHandler multiImageHandler.h "multiImageHandler.h"
 * @brief   �摜�����N���X
 * @details �摜�f�[�^���i�[���A�����摜��G�b�W�摜��
 *          �̉摜�������s���B�f�[�^�͉摜��O���t�Ƃ���
 *          �\�����邱�Ƃ��o����B
 */
class multiImageHandler : 
    public imageHandler{
public:

// �R���X�g���N�^

    multiImageHandler(){}

    /*!
     * @brief   �R���X�g���N�^(std::vector<std::vector<T> >�p)
     * @details ���͉摜���i�[���ꂽ�R���e�i���󂯎��B
     * @param   v ���͉摜���i�[���ꂽ�R���e�i�B
     */
    multiImageHandler(std::vector<std::vector<double> > &v);

    multiImageHandler(std::map<std::string, cv::Mat> &input_map);

    /*!
     * @brief     �R���X�g���N�^(std::vector<cv::Mat>�p)
     * @details   ���͉摜���i�[���ꂽ�R���e�i���󂯎��B
     * @param[in] input_obj ���͉摜���i�[���ꂽ�R���e�i�B
     */
    multiImageHandler(std::deque<std::shared_ptr<imageHandler> > input_obj);

    /*!
     * @brief     �R���X�g���N�^(�t�H���_��)
     * @details   �w��t�H���_�Ɋi�[����Ă���摜��
     *            cv::imread()�Ŏ擾����B
     * @param[in] input_name �t�H���_���B
     */
    multiImageHandler(std::string &input_name);


    /*!
     * @brief   �|�C���^�̃C�j�V�����C�Y
	 * @details �e�摜�̃C�j�V�����C�Y���s���B
     */
    void initializePointers();

    //std::shared_ptr<singleImageHandler> RGB2Gray();
    /*!
     * @brief �J���[�摜����O���[�摜�ւ̕ϊ�
     * @param[in] type CV_8U�Ȃǂ�cv::Mat�̃r�b�g�[�x�B
     */
    virtual std::shared_ptr<imageHandler> convertTo(int type);

    /*!
     * @brief     �J���[�摜����O���[�摜���ւ̕ϊ�
     * @param[in] type �ϊ��^�C�v�B
     */
    virtual std::shared_ptr<imageHandler> cvtColor(int type);

    
    //!@brief      �摜��c��������B
    //!@param[in]  kernel      �J�[�l���B
    //!@param[in]  anchor      �A���J�[�B
    //!@param[in]  iteration   �c���������s���񐔁B
    //!@param[in]  borderType  �s�N�Z���⊮���@(cv::borderInterpolate()���Q�ƁB)
    //!@param[in]  borderValue ���̋��E�ɂ����鋫�E�l(cv::createMorphologyFilter()���Q�ƁB
    virtual std::shared_ptr<imageHandler> erode(cv::InputArray  &kernel,
                                                cv::Point &anchor,
                                                int iteration=1,
                                                int borderType=cv::BORDER_CONSTANT, 
                                                const cv::Scalar
                                                    &borderValue=cv::morphologyDefaultBorderValue()
                                                );

    /*!
     * @brief �J���[�摜����O���[�摜�ւ̕ϊ�
     */
    std::shared_ptr<imageHandler> RGB2Gray();

    /*!
     * @brief ��Βl�ւ̕ϊ�
     */
    virtual std::shared_ptr<imageHandler> abs();

    //! @brief �t���B
    virtual std::shared_ptr<imageHandler> inv();

    //! @brief �v�f�ρB
    virtual std::shared_ptr<imageHandler> mult(std::shared_ptr<imageHandler> &obj);

	//! @brief �����摜���畽�ω摜�̐���
    virtual std::shared_ptr<imageHandler> aveImg();

	//! @brief �ŏ��l���v�Z�B
    virtual std::shared_ptr<imageHandler> minImg();

	//! @brief �ő�l���v�Z�B
    virtual std::shared_ptr<imageHandler> maxImg();

	//! @brief �̈�ɒl���������߂邩�v�Z�B
    //! @param[in] thresh 臒l
    //! @param[in] area   �ʐ�(�p�[�Z���g)
    virtual std::shared_ptr<imageHandler> isValueAmountForMoreThan(double th_val, double th_area);

	//! @brief �������N�s��̐����B
    virtual std::shared_ptr<imageHandler> genComatrix(int divNum, int kaityouNum);

	//! @brief �G�l���M�[�̌v�Z�B
    virtual std::shared_ptr<imageHandler> calcEnergy(int divNum, int kaityouNum);

	//! @brief �R���g���X�g�̌v�Z�B
    virtual std::shared_ptr<imageHandler> calcContrast(int divNum, int kaityouNum);

	//! @brief ���ւ̌v�Z�B
    virtual std::shared_ptr<imageHandler> calcCorrelation(int divNum, int kaityouNum);

	//! @brief ���U�̌v�Z�B
    virtual std::shared_ptr<imageHandler> calcVariance(int divNum, int kaityouNum);
    
	//! @brief �G���g���s�[�̌v�Z�v�Z�B
    virtual std::shared_ptr<imageHandler> calcEntropy(int divNum, int kaityouNum);

	//! @brief �T���G���g���s�[�̌v�Z�B
    virtual std::shared_ptr<imageHandler> calcSumEntropy(int divNum, int kaityouNum);

	//! @brief �Ǐ���l���̌v�Z�B
    virtual std::shared_ptr<imageHandler> calcIDM(int divNum, int kaityouNum);

    std::shared_ptr<imageHandler> nearSimilar(int n_row, int n_col);

    /*! 
     * @brief     �摜�̒~��
     * @param[in] input_m ���͍s��B
     */
    virtual void push_back(cv::Mat &input_m);

    /*! 
     * @brief     �摜�̔����o��
     */
    virtual void pop_front();

    /*! 
     * @brief     �摜�̔����o��
     */
    virtual void push(cv::Mat &input_m, int th_num);

    /*!
     * @brief     �C���f�b�N�X�s��̍쐬�B
     * @param[in] iMin  i�����̃O���b�h�̍ŏ��l�B
     * @param[in] iMax  i�����̃O���b�h�̍ő�l�B
     * @param[in] iStep i�����̃X�e�b�v���B
     * @param[in] jMin  j�����̃O���b�h�̍ŏ��l�B
     * @param[in] jMax  j�����̃O���b�h�̍ő�l�B
     * @param[in] jStep j�����̃X�e�b�v���B
     */
    void mgrid(
            int iMin, 
            int iMax, 
            int iStep,
            int jMin, 
            int jMax, 
            int jStep
            );

    /*!
     * @brief     �摜�̕����B
     * @param[in] n_row �s���B
     * @param[in] n_col �񐔁B
     */
    virtual std::shared_ptr<imageHandler> gridImage(int n_row, int n_col);

    /*!
     * @brief     �摜�t�@�C���̓ǂݍ���
     * @param[in] input_name �t�@�C�����B
     */
    void readImage(std::string &input_name);

    /*!
     * @brief     �摜��̈敪�����A�e�̈�ŕ��ϒl�����߂�B
     * @param[in] n_row �s���B
     * @param[in] n_col �񐔁B
     */
    virtual std::shared_ptr<imageHandler> gridMean(int n_row, int n_col);

    /*!
     * @brief     �摜���cn_row x ��n_col�ŋ�؂�A���������B
     * @param[in] n_row �s���B
     * @param[in] n_col �񐔁B
     */
    virtual void drawGridRect(int n_row, int n_col);

    /*!
     * @brief     �摜�Ɋi�q��̐�������B
     * @param[in] n_row �s���B
     * @param[in] n_col �񐔁B
     */ 
    virtual void getRect(int n_row, int n_col);

    /*!
     * @brief     cv::Canny�������āA�G�b�W���o+�א���+2�l�����s���B
     * @param[in] threshold1 cv::Canny()�̈����ɑΉ��B�ڍׂ�OpenCV��documant���Q�ƁB
     * @param[in] threshold2 cv::Canny()�̈����ɑΉ��B�ڍׂ�OpenCV��documant���Q�ƁB
     */ 
    virtual std::shared_ptr<imageHandler> canny(
        int threshold1=100, 
        int threshold2=200
        );

    /*!
     * @brief     �~�G�b�W�ԋ��������߂�B
     * @details   cv::Canny()�ɂ��G�b�W���o�̌�A�~����\
     *            ���_�Ԃł̒����������A�r���ŃG�b�W�ɂ�����Ԃł̋���
     *            �����߂�B�����͉~�̊p�x0����2pi�܂�2pi/n_div���Ƃ�
     *            �s���B�������ʂ��摜�Ŋm�F����Ƃ���isDraw��true�ɂ���B
     * @param[in] threshold1 cv::Canny()�̈����ɑΉ��B�ڍׂ�OpenCV��documant���Q�ƁB
     * @param[in] threshold2 cv::Canny()�̈����ɑΉ��B�ڍׂ�OpenCV��documant���Q�ƁB
     * @param[in] radius     �~�̔��a�B
     * @param[in] n_div      �������钼���̐��B
     * @param[in] isDraw     �������ʂ̉摜��`�悷�邩���w��B
     */ 
    virtual std::shared_ptr<imageHandler> distanceOfCircleEdge(
                                int threshold1=100, 
                                int threshold2=200,
                                int radius=NULL,
                                int n_div=10,
                                bool isDraw=false);


    /*!
     * @brief     cv::Resize���g���ĉ摜�����T�C�Y����B
     * @param[in] height �摜�̍��� [pix]�B
     * @param[in] width  �摜�̕� [pix]�B
     */ 
    virtual std::shared_ptr<imageHandler> resize(int height=640, int width=880);

    /*!
     * @brief     �摜���g�傷��B
     * @param[in] height �摜�̍��� [pix]�B
     * @param[in] width  �摜�̕�   [pix]�B
     */ 
    virtual std::shared_ptr<imageHandler> expand(int height, int width, bool drawValue);

    /*!
     * @brief �摜�s���~�b�h��expand()���g���č쐬����B
     * @param[in] height �摜�̍��� [pix]�B
     * @param[in] width  �摜�̕�   [pix]�B
     * @param[in] n_div  �摜�̕������B�������A�o�͂����摜�̃s�N�Z�����͌��摜�̂����
     *                   �萔�{���݂̂�I�����邽�߁A�K�������ݒ肵����������
     *                   �摜�𓾂���킯�ł͂Ȃ��B
     * @param[in] isDraw     �������ʂ̉摜��`�悷�邩���w��B
     */ 
    virtual std::shared_ptr<imageHandler> pildown(int height, int width, int n_div, bool drawValue);

    /*!
     * @brief            �p�����[�^�̃}�b�v���쐬����B
     */ 
    virtual std::shared_ptr<imageHandler> genParamMap(int n_row, int n_col);

    /*!
     * @brief            �m�[�}���C�Y
     */ 
    virtual std::shared_ptr<imageHandler> normalize(int minVal, 
                                                    int maxVal,
                                                    int bitDepth);

    //! @brief     �p�����[�^���m�[�}���C�Y����B
    //! @param[in] minVal �p�����[�^�̍ŏ��l�@
    //! @param[in] maxVal �p�����[�^�̍ő�l�@
    virtual std::shared_ptr<imageHandler> normParam(
        double minVal1=0,
        double maxVal1=1,
        double minVal2=0,
        double maxVal2=1
        );

    //! @brief 臒l���v�Z����B
    //! @param[in] thresh      臒l�B
    //! @param[in] maxVal      �ő�l�B
    //! @param[in] threashType 臒l�̃^�C�v�B
    virtual std::shared_ptr<imageHandler> threshold(
                                        double thresh, 
                                        double maxVal, 
                                        int    threshType);

    //! @brief �}�X�N�p�s��Ŏw�肵���ӏ��ɐF��t����B
    //! @param[in] obj    �}�X�N�p�s��B
    //! @param[in] thresh �}�X�N��臒l�B
    virtual std::shared_ptr<imageHandler> paintMask(
                                        std::shared_ptr<imageHandler> &obj,
                                        int thresh);

    //! @brief     �}�X�N�p�s��Ŏw�肵���ӏ��ɐF��t����B
    //! @details   �}�X�N�p�s��̐F����p���ă}�X�N����B
    //! @param[in] obj    �}�X�N�p�s��B
    virtual std::shared_ptr<imageHandler> paintMask(
                                        std::shared_ptr<imageHandler> &obj);

    ///! @brief     obj��param��this�ɃR�s�[����B
    ///! @param[in] obj �I�u�W�F�N�g�B
    virtual std::shared_ptr<imageHandler> cpyParam(std::shared_ptr<imageHandler> &obj);

    //! @brief     �摜��0�ȊO�̗̈���㏑������B
    //! @param[in] obj �I�u�W�F�N�g�B
    virtual std::shared_ptr<imageHandler> interp(std::shared_ptr<imageHandler> &obj);

    //! @brief     �p�����[�^��������B
    //! @param[in] input_param ���̓p�����[�^�B
    virtual std::shared_ptr<imageHandler> setParam(double input_param);

    //! @brief     �p�����[�^��������B
    //! @param[in] input_param �I�u�W�F�N�g�B
    virtual std::shared_ptr<imageHandler> setParam(parameters input_param);

    /*! 
     * @brief     �L���[�̎��ɔz����\�[�g����B
     */
    virtual std::shared_ptr<imageHandler> sortForQue();

    /*! 
     * @brief     �L���[�̎��ɔz��̃C���f�b�N�X���\�[�g����B
     */
    virtual std::shared_ptr<imageHandler> sortForQueIdx();

    /*! 
     * @brief     �^����ꂽ�C���f�b�N�X�������ɁA
     *            �L���[�̎��ɔz��̃C���f�b�N�X���\�[�g����B
     */
    virtual std::shared_ptr<imageHandler> sortForQueWithObj(
        std::shared_ptr<imageHandler> input_obj);

    std::shared_ptr<imageHandler> getBoundingBoxInfo();

    //! @brief     ��`��`�悷��B
    //! @param[in] color      �F���B
    //! @param[in] thickness  ���̌����B
    //! @param[in] lineType   ����B
    //! @param[in] input_rect ��`���(�w�肵�Ȃ��ꍇ�̓����o�ϐ�rect���g�p�����)�B
    //! @param[in] shift       
    virtual std::shared_ptr<imageHandler> rectangle(
        cv::Scalar& color=cv::Scalar(150), 
        int thickness=1, 
        int lineType=8, 
        cv::Rect input_rect = cv::Rect(), 
        int shift=0
        );

    //! @brief     �ێ����Ă����`�̈�����̉�f�ɋP�x�����邩���`�F�b�N����B
    //! @details   ��`�̈����cv::Rect()��ێ����Ă���̂�this�ł��邱�Ƃɒ��ӁB
    //! @param[in] obj �摜��ێ�����摜�����N���X�̃C���X�^���X�B
    virtual std::shared_ptr<imageHandler> checkValidArea(std::shared_ptr<imageHandler> &obj);

    //! @brief     �^����ꂽ��`�̈����p���ĉ摜���N���b�v����B
    //! @param[in] obj ��`�̈���cv::Rect()��ێ�����摜�����N���X�̃C���X�^���X�B
    virtual std::shared_ptr<imageHandler> clip(std::shared_ptr<imageHandler> &obj);

    ////! @brief     �^����ꂽ��`�̈����p���ĉ摜���N���b�v����B
    //virtual std::shared_ptr<imageHandler> clip(cv::Rect &input_rect);
    //! @brief     �����摜�𑫂����킹�A臒l���傫���l��L���Ƃ���2�l�摜��Ԃ��B
    //! @param[in] thresh 臒l
    virtual std::shared_ptr<imageHandler> superImpose(int thresh=0);

    //! @brief     �摜�T�C�Y�ɂ��킹�ăp�����[�^���摜���S�ɕ`�悷��B
    //! @param[in] val       �p�����[�^�B
    //! @param[in] fontFace  �t�H���g���B
    //! @param[in] color     �F�B
    //! @param[in] thickness �����̌����B
    virtual std::shared_ptr<imageHandler> putCenterParam(
        int fontFace = cv::FONT_HERSHEY_SIMPLEX,
		cv::Scalar color=cv::Scalar(255,255,255), 
		int thickness=1
        );

// ��r�p�֐��B
    //!@brief ���ׂẴp�����[�^��0���傫�������肷��B 
    virtual bool any();

    //!@brief ���Ȃ��Ƃ��ЂƂ̃p�����[�^��0���傫�������肷��B 
    virtual bool all();


// �`��p�֐�

    /*! 
     * @brief     �摜��\������B
     * @param[in] input_name  �摜�^�C�g���B
     * @param[in] wTime �摜�\���̑ҋ@���ԁB
     */
    virtual void view(std::string input_name="obj", int wTime=0);

    /*! 
     * @brief     �摜�̋P�x�q�X�g�O������\������B
     * @param[in] binNum  �q�X�g�O�����̃r���̐��B
     * @param[in] xMin    x���̍ŏ��l
     * @param[in] xMax    x���̍ő�l
     * @param[in] yMin    y���̍ŏ��l
     * @param[in] yMax    y���̍ő�l
     */
    virtual void histView(
         std::string input_name="obj1", 
         int binNum = 100, 
         int xMin = 0, 
         int xMax = 256,
         int yMin = 0,
         int yMax = 2e4);

    //! @brief     �O�g����`�悷��B 
    //! @param[in] color     �F���B
    //! @param[in] thickness ���̑����B
    //! @param[in] lineType  ���̎�ށB
    //! @param[in] shift     Number of fractional bits in the point coordinates.
    virtual std::shared_ptr<imageHandler> drawOuterFrame(
        cv::Scalar &color,
        int thickness=1, 
        int lineType=8, 
        int shift=0);

    // �摜�������������ɕ\�����鍂���֐��Q�B

    /*! 
     * @brief     �̈敪�����ꂽ�摜��\������B
     * @param[in] input_name  �摜�^�C�g���B
     * @param[in] wTime �摜�\���̑ҋ@���ԁB
     */
    virtual void viewGridedImg(std::string input_name="obj", int wTime=0);

    /*! 
     * @brief     �̈敪�����ꂽ�p�����[�^��\������B
     * @param[in] input_name  �摜�^�C�g���B
     */
    virtual void viewGridedParam(std::string input_name="obj");

    /*! 
     * @brief     ���T�C�Y�����摜��\������B
     * @param[in] width  �摜�̕�   [pix]�B
     * @param[in] height �摜�̍��� [pix]�B
     */
    virtual void resizeView(int width, int height);

    /*! 
     * @brief     expand�����摜��\������B
     * @param[in] width  �摜�̕�   [pix]�B
     * @param[in] height �摜�̍��� [pix]�B
     */
    virtual void expandView(int width, int height);

    /*! 
     * @brief     expand�ŉ摜�s���~�b�h������A�����\������B
     * @param[in] width  �摜�̕�   [pix]�B
     * @param[in] height �摜�̍��� [pix]�B
     * @param[in] n_div  �摜�̕������B�������A�o�͂����摜�̃s�N�Z�����͌��摜�̂����
     *                   �萔�{���݂̂�I�����邽�߁A�K�������ݒ肵����������
     *                   �摜�𓾂���킯�ł͂Ȃ��B
     */
    virtual void pildownView(int width, int height, int n_div, bool drawValue);

    //! @brief �i�[���Ă���摜�̐���Ԃ��B
    virtual int size();

    /*! 
     * @brief     �����摜����ׂ�B
     * @param[in] n_row �s���B
     * @param[in] n_col �񐔁B
     */
    virtual std::shared_ptr<imageHandler> stichImg(int n_row, int n_col);

    /*! 
     * @brief     �摜���o�͂���B
     * @param[in] dirPath  �f�B���N�g���p�X�B
     * @param[in] fileName �t�@�C�����B
     * @param[in] expand   �g���q�B
     */
    virtual void dump(std::string dirPath, 
                      std::string fileName,
                  	  std::string expand="jpg"); 
// �����o�ϐ�
    cv::Mat m; //!< �摜�i�[�p�ϐ�(cv::Mat)�B 
//protected:

    /// �C���f�b�N�X�ԍ�
    std::vector<std::vector<int> > xIdx, yIdx;    ///< @brief �C���f�b�N�X�ԍ�
    std::vector<std::vector<cv::Mat> > dived_img; ///< @brief �������ꂽ�摜���i�[����R���e�i�B
    cv::Mat m_float;                              ///< @brief �摜�i�[�p�ϐ�(cv::Mat, float)�B 
	unsigned char *m_raw;	                      ///< @brief �摜�i�[�p�ϐ�(unsigned char*)

    std::deque<cv::Mat> img_que;                  ///< @brief �摜�̊i�[�L���[

    std::vector<std::vector<cv::Rect> > rect;     ///< �摜�؂蔲���p��`���i�[�L���[

    //std::deque<std::shared_ptr<imageHandler>> m_lst;        //! @brief�@singleImageHandler�̃��X�g�B
// ���Z�q�I�[�o���[�h
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

    std::shared_ptr<imageHandler> operator+(
        const double &val){
        std::deque<std::shared_ptr<imageHandler> > ret;
    	for(int i=0; i<m_lst.size(); i++)
    	    ret.push_back(m_lst[i] = (*m_lst[i] + val));
    	return std::shared_ptr<imageHandler>(new multiImageHandler(ret));
    }

    std::shared_ptr<imageHandler> operator-(
        const double &val){
        std::deque<std::shared_ptr<imageHandler> > ret;
    	for(int i=0; i<m_lst.size(); i++)
    	    ret.push_back(m_lst[i] = (*m_lst[i] - val));
    	return std::shared_ptr<imageHandler>(new multiImageHandler(ret));
    }

    std::shared_ptr<imageHandler> operator*(
        const double &val){
        std::deque<std::shared_ptr<imageHandler> > ret;
    	for(int i=0; i<m_lst.size(); i++)
    	    ret.push_back(m_lst[i] = (*m_lst[i] * val));
    	return std::shared_ptr<imageHandler>(new multiImageHandler(ret));
    }

    std::shared_ptr<imageHandler> operator/(
        const double &val){
        std::deque<std::shared_ptr<imageHandler> > ret;
    	for(int i=0; i<m_lst.size(); i++)
    	    ret.push_back(m_lst[i] = (*m_lst[i] / val));
    	return std::shared_ptr<imageHandler>(new multiImageHandler(ret));
    }

    std::shared_ptr<imageHandler> operator^(
        const double &val){
        std::deque<std::shared_ptr<imageHandler> > ret;
    	for(int i=0; i<m_lst.size(); i++)
    	    ret.push_back(m_lst[i] = (*m_lst[i] ^ val));
    	return std::shared_ptr<imageHandler>(new multiImageHandler(ret));
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

//    ~multiImageHandler();
};

#pragma once 
#include <iostream>
#include <opencv2\opencv.hpp>



class parameter{
public:
    parameter();
    parameter(double input_val, double input_w=1);


    void setValue(double inpue_val);
    double getWeight();
    double getValue();

private:
    double w  ; //!< 重み係数。
    double val; //!< パラメータ。
    
};

enum enum_op{ LT, // <
              LE, // <=
              EQ, // ==
              NE, // !=
              GT, // >
              GE, // >=
              AA};

class parameters {
public:
    parameters();
    parameters(double input_val);
    parameters(std::map<std::string, parameter> input_plst);


    bool and    (parameters &obj, enum_op op);
    bool or     (parameters &obj, enum_op op);
    bool amount (parameters &obj, enum_op op);
    bool and    (double val, enum_op op);
    bool or     (double val, enum_op op);
    bool amount (double val, enum_op op);

//    void setCompFunc(bool (*f)(parameters, enum_op)); 
    void setAnd();
    void setOr();
    void setAmount();


// オペレータ。

    void operator =(const double     val);
    void operator =(const parameters &obj);
    void operator +=(const double     val);
    void operator -=(const double     val);
    void operator *=(const double     val);
    void operator /=(const double     val);
    void operator %=(const double     val);
    void operator +=(const parameters &obj);
    void operator -=(const parameters &obj);
    void operator *=(const parameters &obj);
    void operator /=(const parameters &obj);
    void operator %=(const parameters &obj);
    parameters operator +(const double     val);
    parameters operator -(const double     val);
    parameters operator *(const double     val);
    parameters operator /(const double     val);
    parameters operator %(const double     val);
    parameters operator +(const parameters &obj);
    parameters operator -(const parameters &obj);
    parameters operator *(const parameters &obj);
    parameters operator /(const parameters &obj);
    parameters operator %(const parameters &obj);
    
    bool operator <(const double &val);

    //! @brief パラメータを比較する。
    bool operator >(const double &val);

    //! @brief パラメータを比較する。
    bool operator ==(const double &val);

    //! @brief パラメータを比較する。
    bool operator !=(const double &val);

    //! @brief パラメータを比較する。
    bool operator <=(const double &val);

    //! @brief パラメータを比較する。
    bool operator >=(const double &val);

    //! @brief パラメータを比較する。
    bool operator <(const parameters &obj);

    //! @brief パラメータを比較する。
    bool operator >(const parameters &obj);

    //! @brief パラメータを比較する。
    bool operator ==(const parameters &obj);

    //! @brief パラメータを比較する。
    bool operator !=(const parameters &obj);

    //! @brief パラメータを比較する。
    bool operator <=(const parameters &obj);

    //! @brief パラメータを比較する。
    bool operator >=(const parameters &obj);

    //! @brief パラメータを比較する。
    bool operator &&(const parameters &obj);


    //! @brief パラメータの値を取り出す。
    parameter& operator [](std::string name);

    //! @brief パラメータの値を取り出す(no name用)。
    double operator ()();


    std::map<std::string, parameter> plst; 
    
    bool tof;

    bool (parameters::*func) (parameters& , enum_op );
    bool (parameters::*func2)(double , enum_op );
    
};
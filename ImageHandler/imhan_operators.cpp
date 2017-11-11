//#include "stdafx.h"
#include "imhan_operators.h"

std::shared_ptr<imageHandler> operator+(
    const std::shared_ptr<imageHandler> &obj1,
    const std::shared_ptr<imageHandler> &obj2){
    return *obj1 + obj2;                                        
}

std::shared_ptr<imageHandler> operator-(
    const std::shared_ptr<imageHandler> &obj1,
    const std::shared_ptr<imageHandler> &obj2){
    return *obj1 - obj2;                                        
}

std::shared_ptr<imageHandler> operator*(
    const std::shared_ptr<imageHandler> &obj1,
    const std::shared_ptr<imageHandler> &obj2){
    return *obj1 * obj2;                                        
}

std::shared_ptr<imageHandler> operator/(
    const std::shared_ptr<imageHandler> &obj1,
    const std::shared_ptr<imageHandler> &obj2){
    return *obj1 / obj2;                                        
}

std::shared_ptr<imageHandler> operator^(
    const std::shared_ptr<imageHandler> &obj1,
    const std::shared_ptr<imageHandler> &obj2){
    return *obj1 ^ obj2;                                        
}

std::shared_ptr<imageHandler> operator+(
    const double &val,
    const std::shared_ptr<imageHandler> &obj){
    return *obj + val;
}

std::shared_ptr<imageHandler> operator-(
    const double &val,
    const std::shared_ptr<imageHandler> &obj){
    return *obj - val;
}

std::shared_ptr<imageHandler> operator*(
    const double &val,
    const std::shared_ptr<imageHandler> &obj){
    return *obj * val;
}

std::shared_ptr<imageHandler> operator/(
    const double &val,
    const std::shared_ptr<imageHandler> &obj){
    return *obj->inv() * (1./val);
}

//‰ü’è—\’è
std::shared_ptr<imageHandler> operator^(
    const double &val,
    const std::shared_ptr<imageHandler> &obj){
    return obj;
}

std::shared_ptr<imageHandler> operator+(
    const std::shared_ptr<imageHandler> &obj,
    const double &val){
    return *obj + val;
}

std::shared_ptr<imageHandler> operator-(
    const std::shared_ptr<imageHandler> &obj,
    const double &val){
    return *obj - val;
}

std::shared_ptr<imageHandler> operator*(
    const std::shared_ptr<imageHandler> &obj,
    const double &val){
    return *obj * val;
}

std::shared_ptr<imageHandler> operator/(
    const std::shared_ptr<imageHandler> &obj,
    const double &val){
    return *obj / val;
}

std::shared_ptr<imageHandler> operator^(
    const std::shared_ptr<imageHandler> &obj,
    const double &val){
    return *obj ^ val ;
}
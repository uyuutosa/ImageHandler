#pragma once
#include <iostream>
#include <string>
#include "imageHandler.h"

std::shared_ptr<imageHandler> operator+(
    const std::shared_ptr<imageHandler> &obj1,
    const std::shared_ptr<imageHandler> &obj2);

std::shared_ptr<imageHandler> operator-(
    const std::shared_ptr<imageHandler> &obj1,
    const std::shared_ptr<imageHandler> &obj2);
                                        
std::shared_ptr<imageHandler> operator*(
    const std::shared_ptr<imageHandler> &obj1,
    const std::shared_ptr<imageHandler> &obj2);

std::shared_ptr<imageHandler> operator/(
    const std::shared_ptr<imageHandler> &obj1,
    const std::shared_ptr<imageHandler> &obj2);

std::shared_ptr<imageHandler> operator^(
    const std::shared_ptr<imageHandler> &obj1,
    const std::shared_ptr<imageHandler> &obj2);

std::shared_ptr<imageHandler> operator+(
    const double &val,
    const std::shared_ptr<imageHandler> &obj);

std::shared_ptr<imageHandler> operator-(
    const double &val,
    const std::shared_ptr<imageHandler> &obj);

std::shared_ptr<imageHandler> operator*(
    const double &val,
    const std::shared_ptr<imageHandler> &obj);

std::shared_ptr<imageHandler> operator/(
    const double &val,
    const std::shared_ptr<imageHandler> &obj);

std::shared_ptr<imageHandler> operator^(
    const double &val,
    const std::shared_ptr<imageHandler> &obj);

std::shared_ptr<imageHandler> operator+(
    const std::shared_ptr<imageHandler> &obj,
    const double &val);

std::shared_ptr<imageHandler> operator-(
    const std::shared_ptr<imageHandler> &obj,
    const double &val);

std::shared_ptr<imageHandler> operator*(
    const std::shared_ptr<imageHandler> &obj,
    const double &val);

std::shared_ptr<imageHandler> operator/(
    const std::shared_ptr<imageHandler> &obj,
    const double &val);

std::shared_ptr<imageHandler> operator^(
    const std::shared_ptr<imageHandler> &obj,
    const double &val);

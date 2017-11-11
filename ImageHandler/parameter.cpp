#include "parameter.h"

//#pragma optimize("", off)



parameter::parameter():
    val(0), w(1)
{
}

parameter::parameter(double input_val, double input_w):
    val(input_val), w(input_w)
{
}

void parameter::setValue(double input_val){
    val += input_val;
    
}

double parameter::getValue(){
    return val;
}

double parameter::getWeight(){
    return w;
}

// parameters

parameters::parameters(){}

parameters::parameters(double input_val)
{
    plst["no name"] = parameter(input_val);
}

parameters::parameters(std::map<std::string, parameter> input_plst):
    plst(input_plst)
{
}


parameter& parameters::operator[](std::string name){
    return plst[name];
}

double parameters::operator()(){
    return plst["no name"].getValue();
}

bool parameters::and(double val, enum_op op){
    tof = true;
    switch(op){
    case LT:
        for(auto pair: plst)
            tof &= pair.second.getValue() * pair.second.getWeight() < val;
        break;
    case LE:
        for(auto pair: plst)
            tof &= pair.second.getValue() * pair.second.getWeight() <= val;
        break;
    case EQ:
        for(auto pair: plst)
            tof &= pair.second.getValue() * pair.second.getWeight() == val;
        break;
    case NE:
        for(auto pair: plst)
            tof &= pair.second.getValue() * pair.second.getWeight() != val;
        break;
    case GT:
        for(auto pair: plst){
            tof &= ((pair.second.getValue() * pair.second.getWeight()) > val);
        }
        break;

    case GE:
        for(auto pair: plst)
            tof &= pair.second.getValue() * pair.second.getWeight() >= val;
        break;

    case AA:
        for(auto pair: plst)
            tof &= pair.second.getValue() * pair.second.getWeight() && val;
        break;
    }

    return tof;
}

bool parameters::or(double val, enum_op op){
    tof = false;
    switch(op){
    case LT:
        for(auto pair: plst)
            tof |= pair.second.getValue() * pair.second.getWeight() < val;
        break;
    case LE:
        for(auto pair: plst)
            tof |= pair.second.getValue() * pair.second.getWeight() <= val;
        break;
    case EQ:
        for(auto pair: plst)
            tof |= pair.second.getValue() * pair.second.getWeight() == val;
        break;
    case NE:
        for(auto pair: plst)
            tof |= pair.second.getValue() * pair.second.getWeight() != val;
        break;
    case GT:
        for(auto pair: plst){
            double p(pair.second.getValue());
            double w(pair.second.getWeight());
            tof |= p * w > val;
        }
        break;
    case GE:
        for(auto pair: plst)
            tof |= pair.second.getValue() * pair.second.getWeight() >= val;
        break;
    case AA:
        for(auto pair: plst)
            tof |= pair.second.getValue() * pair.second.getWeight() && val;
        break;
    }
    return tof;
}

bool parameters::amount(double val, enum_op op){
    tof = false;
    switch(op){
    case LT:
        tof = plst["amount"].getValue() < val;
        break;
    case LE:
        tof = plst["amount"].getValue() <= val;
        break;
    case EQ:
        tof = plst["amount"].getValue() == val;
        break;
    case NE:
        tof = plst["amount"].getValue() != val;
    case GT:
        tof = plst["amount"].getValue() > val;
        break;
    case GE:
        tof = plst["amount"].getValue() >= val;
        break;
    }

    return tof;
    
}

bool parameters::and(parameters &obj, enum_op op){
    tof = true;
    switch(op){
    case LT:
        for(auto pair: plst)
            tof &= pair.second.getValue() * pair.second.getWeight() <
            obj.plst[pair.first].getValue() * obj.plst[pair.first].getWeight();
        break;
    case LE:
        for(auto pair: plst)
            tof &= pair.second.getValue() * pair.second.getWeight() <=
            obj.plst[pair.first].getValue() * obj.plst[pair.first].getWeight();
        break;
    case EQ:
        for(auto pair: plst)
            tof &= pair.second.getValue() * pair.second.getWeight() ==
            obj.plst[pair.first].getValue() * obj.plst[pair.first].getWeight();
        break;
    case NE:
        for(auto pair: plst)
            tof &= pair.second.getValue() * pair.second.getWeight() !=
            obj.plst[pair.first].getValue() * obj.plst[pair.first].getWeight();
        break;
    case GT:
        for(auto pair: plst)
            tof &= pair.second.getValue() * pair.second.getWeight() >
            obj.plst[pair.first].getValue() * obj.plst[pair.first].getWeight();
        break;
    case GE:
        for(auto pair: plst)
            tof &= pair.second.getValue() * pair.second.getWeight() >=
            obj.plst[pair.first].getValue() * obj.plst[pair.first].getWeight();
        break;
    }

    return tof;
}

bool parameters::or(parameters &obj, enum_op op){
    tof = false;
    switch(op){
    case LT:
        for(auto pair: plst)
            tof |= pair.second.getValue() * pair.second.getWeight() <
            obj.plst[pair.first].getValue() * obj.plst[pair.first].getWeight();
        break;
    case LE:
        for(auto pair: plst)
            tof |= pair.second.getValue() * pair.second.getWeight() <=
            obj.plst[pair.first].getValue() * obj.plst[pair.first].getWeight();
        break;
    case EQ:
        for(auto pair: plst)
            tof |= pair.second.getValue() * pair.second.getWeight() ==
            obj.plst[pair.first].getValue() * obj.plst[pair.first].getWeight();
        break;
    case NE:
        for(auto pair: plst)
            tof |= pair.second.getValue() * pair.second.getWeight() !=
            obj.plst[pair.first].getValue() * obj.plst[pair.first].getWeight();
        break;
    case GT:
        for(auto pair: plst)
            tof |= pair.second.getValue() * pair.second.getWeight() >
            obj.plst[pair.first].getValue() * obj.plst[pair.first].getWeight();
        break;
    case GE:
        for(auto pair: plst)
            tof |= pair.second.getValue() * pair.second.getWeight() >=
            obj.plst[pair.first].getValue() * obj.plst[pair.first].getWeight();
        break;
    }
    return tof;
}

bool parameters::amount(parameters &obj, enum_op op){
    tof = false;
    switch(op){
    case LT:
        tof = plst["amount"].getValue() <  obj.plst["amount"].getValue();
        break;
    case LE:
        tof = plst["amount"].getValue() <= obj.plst["amount"].getValue();
        break;
    case EQ:
        tof = plst["amount"].getValue() == obj.plst["amount"].getValue();
        break;
    case NE:
        tof = plst["amount"].getValue() != obj.plst["amount"].getValue();
    case GT:
        tof = plst["amount"].getValue() >  obj.plst["amount"].getValue();
        break;
    case GE:
        tof = plst["amount"].getValue() >= obj.plst["amount"].getValue();
        break;
    }

    return tof;
    
}

void parameters::setAnd(){
    func  = &parameters::and;
    func2 = &parameters::and;
}

void parameters::setOr(){
    func  = &parameters::or;
    func2 = &parameters::or;
}

void parameters::setAmount(){
    func  = &parameters::amount;
    func2 = &parameters::amount;
}


parameters parameters::operator + (const double val){
    std::map<std::string, parameter> ret_plst(plst);  
    for(auto pair: ret_plst)
        pair.second.setValue(pair.second.getValue()+val);
    return parameters(ret_plst);
}

parameters parameters::operator - (const double val){
    std::map<std::string, parameter> ret_plst(plst);  
    for(auto pair: ret_plst)
        pair.second.setValue(pair.second.getValue()-val);
    return parameters(ret_plst);
}

parameters parameters::operator * (const double val){
    std::map<std::string, parameter> ret_plst(plst);  
    for(auto pair: ret_plst)
        pair.second.setValue(pair.second.getValue()*val);
    return parameters(ret_plst);
}

parameters parameters::operator / (const double val){
    std::map<std::string, parameter> ret_plst(plst);  
    for(auto pair: ret_plst)
        pair.second.setValue(pair.second.getValue()/val);
    return parameters(ret_plst);
}

parameters parameters::operator % (const double val){
    std::map<std::string, parameter> ret_plst(plst);  
    for(auto pair: ret_plst)
        pair.second.setValue(((int)pair.second.getValue())%(int)val);
    return parameters(ret_plst);
}

parameters parameters::operator + (const parameters &obj){
    std::map<std::string, parameter> ret_plst(plst);  
    std::map<std::string, parameter> ret_plst_obj(obj.plst);  

    for(auto pair: ret_plst){
        pair.second.setValue((pair.second.getValue())+ ret_plst_obj[pair.first].getValue());
    }
    return parameters(ret_plst);
}

parameters parameters::operator - (const parameters &obj){
    std::map<std::string, parameter> ret_plst(plst);  
    std::map<std::string, parameter> ret_plst_obj(obj.plst);  
    for(auto pair: ret_plst)
        pair.second.setValue((pair.second.getValue())- ret_plst_obj[pair.first].getValue());
    return parameters(ret_plst);
}

parameters parameters::operator * (const parameters &obj){
    std::map<std::string, parameter> ret_plst(plst);  
    std::map<std::string, parameter> ret_plst_obj(obj.plst);  
    for(auto pair: ret_plst)
        pair.second.setValue(pair.second.getValue()*ret_plst_obj[pair.first].getValue());
    return parameters(ret_plst);
}

parameters parameters::operator / (const parameters &obj){
    std::map<std::string, parameter> ret_plst(plst);  
    std::map<std::string, parameter> ret_plst_obj(obj.plst);  
    for(auto pair: ret_plst)
        pair.second.setValue(pair.second.getValue()/ret_plst_obj[pair.first].getValue());
    return parameters(ret_plst);
}

parameters parameters::operator % (const parameters &obj){
    std::map<std::string, parameter> ret_plst(plst);  
    std::map<std::string, parameter> ret_plst_obj(obj.plst);  
    for(auto pair: ret_plst)
    for(auto pair: ret_plst)
        pair.second.setValue((int)pair.second.getValue()%(int)ret_plst_obj[pair.first].getValue());
    return parameters(ret_plst);
}

void parameters::operator = (const double val){
    plst["no name"] = val;
}

void parameters::operator = (const parameters &obj){
    plst = obj.plst;
}

void  parameters::operator += (const double val){
    *this = *this + val;
}

void parameters::operator -= (const double val){
    *this = *this - val;
}

void parameters::operator *= (const double val){
    *this = *this * val;
}

void parameters::operator /= (const double val){
    *this = *this / val;
}

void parameters::operator %= (const double val){
    *this = *this % val;
}

void  parameters::operator += (const parameters &obj){
    *this = *this + obj;
}

void parameters::operator -= (const parameters &obj){
    *this = *this - obj;
}

void parameters::operator *= (const parameters &obj){
    *this = *this * obj;
}

void parameters::operator /= (const parameters &obj){
    *this = *this / obj;
}

void parameters::operator %= (const parameters &obj){
    *this = *this % obj;
}

bool parameters::operator < (const parameters &obj){
    return (this->*func)(const_cast<parameters&>(obj), LT);
}

bool parameters::operator <= (const parameters &obj){
    return (this->*func)(const_cast<parameters&>(obj), LE);
}

bool parameters::operator == (const parameters &obj){
    return (this->*func)(const_cast<parameters&>(obj), EQ);
}

bool parameters::operator && (const parameters &obj){
    return (this->*func)(const_cast<parameters&>(obj), AA);
}

bool parameters::operator != (const parameters &obj){
    return (this->*func)(const_cast<parameters&>(obj), NE);
}

bool parameters::operator > (const parameters &obj){
    return (this->*func)(const_cast<parameters&>(obj), GT);
}

bool parameters::operator >= (const parameters &obj){
    return (this->*func)(const_cast<parameters&>(obj), GE);
}

bool parameters::operator < (const double &obj){
    return (this->*func2)(const_cast<double&>(obj), LT);
}

bool parameters::operator <= (const double &val){
    return (this->*func2)(const_cast<double&>(val), LE);
}

bool parameters::operator == (const double &val){
    return (this->*func2)(const_cast<double&>(val), EQ);
}

bool parameters::operator != (const double &val){
    return (this->*func2)(const_cast<double&>(val), NE);
}

bool parameters::operator > (const double &val){
    return (this->*func2)(const_cast<double&>(val), GT);
}

bool parameters::operator >= (const double &val){
    return (this->*func2)(const_cast<double&>(val), GE);
}

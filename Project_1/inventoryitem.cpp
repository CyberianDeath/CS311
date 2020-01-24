#include "inventoryitem.h"
#include <iostream>

ostream& operator<<(ostream & out, const InventoryItem & other){
    out << other._prodName << "(" << other._invNum << ")\n";
    return out;
}
bool operator==(InventoryItem const & lhs, InventoryItem const & rhs){
    if(lhs._invNum == rhs._invNum && lhs._prodName == rhs._prodName){
        return true;
    } else{
        return false;
    }
}
bool operator!=(InventoryItem const & lhs, InventoryItem const & rhs){
    if(lhs._invNum == rhs._invNum && lhs._prodName == rhs._prodName){
        return false;
    } else{
        return true;
    }
}
InventoryItem::InventoryItem(){
    setName("UNNAMED");
    setNumber(0);
}
InventoryItem::InventoryItem(string PN, int IN){//unfinished
    if(IN < 0){
        //throw "no negative numbers";
    } else {
        setName(PN);
        setNumber(IN);
    }
}
std::string InventoryItem::getName() const{
    return this->_prodName;
}
int InventoryItem::getNumber() const{
    return this->_invNum;
}
void InventoryItem::setName(string PN){
    this->_prodName = PN;
}
void InventoryItem::setNumber(int IN){
    this->_invNum = IN;
}
bool InventoryItem::empty() const{
    if(this->_invNum == 0){
        return true;
    }else{
        return false;
    }
}
string InventoryItem::toString() const{
    string newStr = "";
    return newStr;
}
InventoryItem& InventoryItem::operator++(){
    setNumber(getNumber()+1);
    return *this;
}
InventoryItem InventoryItem::operator++([[maybe_unused]]int dummy){
    auto save = *this;
    ++(*this);
    return save;
}
InventoryItem& InventoryItem::operator--(){
    setNumber(getNumber()-1);
    return *this;
}
InventoryItem InventoryItem::operator--([[maybe_unused]]int dummy){
        auto save = *this;
        --(*this);
        return save;
}

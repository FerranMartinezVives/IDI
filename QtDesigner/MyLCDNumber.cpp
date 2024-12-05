#include "MyLCDNumber.h"

MyLCDNumber::MyLCDNumber(QWidget *parent=0):QLCDNumber(parent)
{
}

void MyLCDNumber::suma1() {
    display(value() + 1);
}

void MyLCDNumber::suma4() {
    display(value() + 4);
}
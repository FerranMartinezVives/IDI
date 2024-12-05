#include "MyLCDNumber.h"

MyLCDNumber::MyLCDNumber(QWidget *parent=0):QLCDNumber(parent)
{
    connect(&timer, SIGNAL(timeout()), this, SLOT(comptaMilisegons()));
    record = QTime(0, 0, 0, 0);
    running = false;
    currentTime = QTime(0, 0, 0, 0);
}

void MyLCDNumber::startCronometre() {
    if (not running) {
        timer.start(1);
        running = true;
        emit emitRunningState(running);
    }
}

void MyLCDNumber::stopCronometre() {
    if (running) {
        timer.stop();
        running = false;
        emitRunningState(running);
    }
}

void MyLCDNumber::restartCronometre() {
    if (record == QTime(0, 0, 0, 0) or record > currentTime) {
        record = currentTime;
        emit emitValue(record.toString("hh:mm:ss:zzz"));
    }
    currentTime = QTime(0, 0, 0, 0);
    display(currentTime.toString("hh:mm:ss:zzz"));
}

void MyLCDNumber::comptaMilisegons() {
    currentTime = currentTime.addMSecs(1);
    //He considerat que quan no hi ha cap rècord en memòria el temps que marca el cronòmetre és alhora el rècord
    if (record == QTime(0, 0, 0, 0) or currentTime == record) setStyleSheet("color: rgb(0, 0, 0)");
    else if (currentTime > record) setStyleSheet("color: rgb(255, 0, 0)");
    else setStyleSheet("color: rgb(0, 255, 0)");
    display(currentTime.toString("hh:mm:ss:zzz"));
}
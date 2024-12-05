/********************************************************************************
** Form generated from reading UI file 'Cronometre.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CRONOMETRE_H
#define UI_CRONOMETRE_H

#include <MyLCDNumber.h>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Cronometre
{
public:
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    MyLCDNumber *lcdNumber;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_3;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButton_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButton;

    void setupUi(QWidget *Cronometre)
    {
        if (Cronometre->objectName().isEmpty())
            Cronometre->setObjectName(QString::fromUtf8("Cronometre"));
        Cronometre->resize(687, 537);
        verticalLayout_3 = new QVBoxLayout(Cronometre);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        lcdNumber = new MyLCDNumber(Cronometre);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lcdNumber->sizePolicy().hasHeightForWidth());
        lcdNumber->setSizePolicy(sizePolicy);
        lcdNumber->setMinimumSize(QSize(50, 20));
        lcdNumber->setMaximumSize(QSize(1000000, 400000));
        QFont font;
        font.setPointSize(5);
        font.setStrikeOut(false);
        font.setKerning(true);
        font.setStyleStrategy(QFont::PreferAntialias);
        lcdNumber->setFont(font);
        lcdNumber->setDigitCount(12);
        lcdNumber->setSegmentStyle(QLCDNumber::Filled);
        lcdNumber->setProperty("value", QVariant(0.000000000000000));

        verticalLayout_2->addWidget(lcdNumber);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        pushButton_4 = new QPushButton(Cronometre);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton_4->sizePolicy().hasHeightForWidth());
        pushButton_4->setSizePolicy(sizePolicy1);
        pushButton_4->setMinimumSize(QSize(100, 40));
        pushButton_4->setMaximumSize(QSize(100, 40));

        horizontalLayout_3->addWidget(pushButton_4);

        pushButton_3 = new QPushButton(Cronometre);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        sizePolicy1.setHeightForWidth(pushButton_3->sizePolicy().hasHeightForWidth());
        pushButton_3->setSizePolicy(sizePolicy1);
        pushButton_3->setMinimumSize(QSize(100, 40));
        pushButton_3->setMaximumSize(QSize(100, 40));

        horizontalLayout_3->addWidget(pushButton_3);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        pushButton_2 = new QPushButton(Cronometre);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        sizePolicy1.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy1);
        pushButton_2->setMinimumSize(QSize(100, 40));
        pushButton_2->setMaximumSize(QSize(100, 40));

        horizontalLayout_3->addWidget(pushButton_2);


        verticalLayout_2->addLayout(horizontalLayout_3);


        verticalLayout_3->addLayout(verticalLayout_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        label = new QLabel(Cronometre);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setMinimumSize(QSize(80, 20));
        label->setMaximumSize(QSize(80, 20));
        QFont font1;
        font1.setPointSize(16);
        label->setFont(font1);

        horizontalLayout_2->addWidget(label);

        label_2 = new QLabel(Cronometre);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);
        label_2->setMinimumSize(QSize(160, 20));
        label_2->setMaximumSize(QSize(160, 20));
        label_2->setFont(font1);

        horizontalLayout_2->addWidget(label_2);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);


        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        pushButton = new QPushButton(Cronometre);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout->addWidget(pushButton);


        horizontalLayout->addLayout(verticalLayout);


        verticalLayout_3->addLayout(horizontalLayout);


        retranslateUi(Cronometre);
        QObject::connect(pushButton_3, SIGNAL(clicked()), lcdNumber, SLOT(stopCronometre()));
        QObject::connect(pushButton_2, SIGNAL(clicked()), lcdNumber, SLOT(restartCronometre()));
        QObject::connect(pushButton, SIGNAL(clicked()), Cronometre, SLOT(close()));
        QObject::connect(lcdNumber, SIGNAL(emitValue(QString)), label_2, SLOT(setText(QString)));
        QObject::connect(lcdNumber, SIGNAL(emitRunningState(bool)), Cronometre, SLOT(changeRunningState(bool)));
        QObject::connect(Cronometre, SIGNAL(emitStart()), lcdNumber, SLOT(startCronometre()));
        QObject::connect(Cronometre, SIGNAL(emitStop()), lcdNumber, SLOT(stopCronometre()));
        QObject::connect(Cronometre, SIGNAL(emitRestart()), lcdNumber, SLOT(restartCronometre()));
        QObject::connect(Cronometre, SIGNAL(emitQuit()), Cronometre, SLOT(close()));
        QObject::connect(pushButton_4, SIGNAL(clicked()), lcdNumber, SLOT(startCronometre()));

        QMetaObject::connectSlotsByName(Cronometre);
    } // setupUi

    void retranslateUi(QWidget *Cronometre)
    {
        Cronometre->setWindowTitle(QCoreApplication::translate("Cronometre", "Form", nullptr));
        pushButton_4->setText(QCoreApplication::translate("Cronometre", "Start", nullptr));
        pushButton_3->setText(QCoreApplication::translate("Cronometre", "Stop", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Cronometre", "Restart", nullptr));
        label->setText(QCoreApplication::translate("Cronometre", "R\303\250cord:", nullptr));
        label_2->setText(QString());
        pushButton->setText(QCoreApplication::translate("Cronometre", "Quit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Cronometre: public Ui_Cronometre {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CRONOMETRE_H

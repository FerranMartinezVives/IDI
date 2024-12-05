#include<QLCDNumber>
class MyLCDNumber:public QLCDNumber
{
    Q_OBJECT
    public: 
        MyLCDNumber(QWidget *parent);
    
    public slots:
        void suma1();
        
        void suma4();
};
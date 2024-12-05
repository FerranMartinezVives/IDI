#include<QLCDNumber>
#include<QTime>
#include<QTimer>
class MyLCDNumber:public QLCDNumber
{
    Q_OBJECT
    public:
        MyLCDNumber(QWidget *parent);

    private:
        QTimer timer;
        QTime record;
        bool running;
        QTime currentTime;
    
    public slots:
        void startCronometre();

        void stopCronometre();

        void restartCronometre();

        void comptaMilisegons();
    
    signals:
        void emitValue(const QString &);

        void emitRunningState(const bool);
};
#ifndef DATAHANDLETOOLS_H
#define DATAHANDLETOOLS_H

#include <QObject>
//����һЩ�������ݵķ�������
//��̬�����ݰ�
class  VehicleParaMeterPack:public QObject
{
    Q_OBJECT
public:




private:
    static QByteArray packHead;  // 4
    static QByteArray Counter;   //4
    static QByteArray FlightTime;
    static QByteArray  VehicleID;

signals:
    void valueChanged();


};

class DataHandleTools : public QObject
{
    Q_OBJECT
public:
    explicit DataHandleTools(QObject *parent = nullptr);







signals:

};

#endif // DATAHANDLETOOLS_H

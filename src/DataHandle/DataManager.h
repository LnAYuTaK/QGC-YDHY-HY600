#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>
//����һЩ�������ݵķ�������
//��̬�����ݰ�
class  VehicleParaMeterPack:public QObject
{
    Q_OBJECT
public:



private:
    static QByteArray packHead;  // 4֡ͷ
    static qint64 Counter;   // ������
    static QByteArray FlightTime;// ���ʱ��
    static QByteArray  VehicleID;

};

//
class DataManager : public QObject
{
    Q_OBJECT
public:
    explicit DataManager(QObject *parent = nullptr);







signals:

};

#endif // DATAMANAGER_H

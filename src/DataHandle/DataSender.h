#ifndef DATASENDER_H
#define DATASENDER_H
//QT Head
#include <QObject>
#include <QTcpSocket>

//QGC Head
#include <QGCApplication.h>
#include <MultiVehicleManager.h>

class DataSender : public QObject
{
    Q_OBJECT
public:
    explicit DataSender(QObject *parent = nullptr);


private:
    //��ȡ��ǰ�ɻ�������
    MultiVehicleManager *VehicleManager;



signals:

};

#endif // DATASENDER_H

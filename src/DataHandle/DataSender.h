#ifndef DATASENDER_H
#define DATASENDER_H
//QT Head
#include <QObject>
#include <QTcpSocket>
#include  "Settings/HySettings.h"
//QGC Head
#include <QGCApplication.h>
#include <MultiVehicleManager.h>

class DataSender : public QObject
{
    Q_OBJECT
public:
    explicit DataSender(QObject *parent = nullptr);
//    QTcpSocket  * datasock(){return data_sender;};

private:
    //获取当前飞机管理类
    MultiVehicleManager *VehicleManager;

signals:

};

#endif // DATASENDER_H

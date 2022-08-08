#ifndef DATAMANAGER_H
#define DATAMANAGER_H

//QT Head
#include <QObject>
#include <QDateTime>
#include <QMap>
#include <QVector>
#include <QByteArray>
#include <QString>
#include <QTcpSocket>
//QGC Head
#include "QGCMAVLink.h"
#include "QGCApplication.h"
#include "Vehicle.h"
#include  "Settings/HySettings.h"


#define   PACKHEAD  "EB90"
//ֲ����DataFact
class  VehicleDataFactPack:public QObject
{
    Q_OBJECT
public:
      explicit VehicleDataFactPack(QObject *parent = nullptr);
      //����ӿڻ�ȡ���ݵĽӿ�
      //pack �ڲ����˿ռ�ע������
      QString   pack                      () ;
      Q_INVOKABLE bool     flightState    () {return _flightState;}
      Q_INVOKABLE QString  flightTime     () {return _flightTime;}
      Q_INVOKABLE uint8_t  sprayState     () {return _sprayStat;}
      Q_INVOKABLE int      id             () {return _id;}
      Q_INVOKABLE uint8_t  flowRate       () {return _flowRate;}
      Q_INVOKABLE double   workArea       () {return _workArea;}
      Q_INVOKABLE double   lot            () {return _lot;}
      Q_INVOKABLE double   lat            () {return _lat;}
      Q_INVOKABLE double   flightTailTude () {return _flightTailTude;}
      Q_INVOKABLE double   groundSpeed    () {return _groundSpeed;}
      Q_INVOKABLE QString  flightMode     () {return _flightMode;}

      //����ģʽ����// ���б�����ͺ������
      const QStringList FlightModeType {
              "PreFlight",
              "Stabilize",
              "Guided",
              "Auto",
              "Test",
              "Altitude Hold",
              "RTL",
              "Loiter"
      };
//�����Vehcile���յ�����
public slots:
      void _vehicleTakeOff();

      void _vehicleLand();

      void _vehicleFlightTime(QString time);

      void _vehicleSprayState(bool isOpen);

      void _vehicleid(int id);

      void _vehicleFlowRate(uint8_t flowRate);

      void _vehicleWorkArea(double workArea);

      void _vehicleLongitude(double lot);

      void _vehicleLatitude(double lat);

      void _vehicleFlighTaltiTude(double flightTaltiTude);

      void _vehicleGroundFlightSpeed(double groundSpeed);

      void _vehicleDataSendTime();

      void _vehicleLevelGaugeStatus(uint8_t gaugetype);

      void _vehicleFlightMode(QString flightmodetype);

      void _vehicleMsgText(QString messageText);

      void _vehicleDataSendNumChanged();



private:
      static bool      _flightState;
      static QString   _flightTime;
      static uint8_t   _sprayStat;
      static int       _id ;
      static uint8_t   _flowRate;
      static double    _workArea;
      static double    _lot;
      static double    _lat;
      static double    _flightTailTude;
      static double    _groundSpeed;
      static uint8_t    _gaugetype;
      static QString   _flightMode;
      //�Ƿ���·��мܴ�flag
      static bool      _upDataFlightFlag;
      //֡ͷ
      const  QString  packHead =PACKHEAD;
      //�汾�͹̼���ͨ����ʱ��ȡͨ��HySetting��ȡ
      const QString    _softWareVersion;
      const QString    _fireWareVersion;

      QVector <qint64> splitDouble(double data,qint16 digit);
      QVector <QString>vehiclePack;
};
//��ʼ����̬����

//���ݹ�����
class DataController: public QObject
{

    Q_OBJECT
public:
     DataController();
     //send netdata
     void  sendData();
     void  saveDataLocal();
private:
    VehicleDataFactPack* createDataFact(Vehicle* vehicle);
    //
    void dataFactAdd(Vehicle* vehicle);
    //
    void dataFactRemove(Vehicle* vehicle);
    //Key&Value
    //Vehicle ID  ---  VehicleDataFactPack pointer
    QMap<int,VehicleDataFactPack *> *dataFactMap=nullptr;
    //Test ��ʱ�����ӻ�Ծ��Vehicle
    QTimer  *dataSendTimer;
    QTcpSocket mSocket;

protected:
    QGCApplication* _app;
    QGCToolbox*     _toolbox;

signals:
    void sendDataNumAdd();//���ʹ�������

};

#endif // DATAMANAGER_H

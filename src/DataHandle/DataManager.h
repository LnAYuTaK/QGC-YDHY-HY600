#ifndef DATAMANAGER_H
#define DATAMANAGER_H

//QT Head
#include <QObject>
#include <QDateTime>
#include <QMap>
#include <QVector>
#include <QByteArray>
#include <QString>
//QGC Head
#include "QGCMAVLink.h"
#include "QGCApplication.h"
#include "Vehicle.h"
#define   PACKHEAD  "EB90"

//ֲ����DataFact
class  VehicleDataFactPack:public QObject
{
    Q_OBJECT
public:
      explicit VehicleDataFactPack(QObject *parent = nullptr);
      //����ӿڻ�ȡ���ݵĽӿ�
      QVector <QByteArray> * Pack         () {return &vehiclePack;}

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

  void _vehicleLevelGaugeStatus(bool gaugetype);

  void _vehicleFlightMode(QString flightmodetype);

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
      static bool      _gaugetype;
      static QString   _flightMode;
      //�Ƿ���·��мܴ�flag
      static bool      _upDataFlightFlag;
      //֡ͷ
      const  QByteArray  packHead = QString(PACKHEAD).toLatin1();
      //�汾�͹̼���ͨ����ʱ��ȡͨ��HySetting��ȡ
      const QString    _softWareVersion;
      const QString    _fireWareVersion;

//Tools
   QVector <qint64> splitDouble(double data,qint16 digit);

//���͵���̨�����ݰ� ÿ����Ϣλ���̶������ж�λ��ֱ�����������ֶ�����Ϣ��λ�ù̶���ʮ�������ַ���
   QVector <QByteArray> vehiclePack;
};
//��ʼ����̬����

//���ݹ�����
class DataManager : public QGCTool
{
    Q_OBJECT

//
public:
     DataManager(QGCApplication* app, QGCToolbox* toolbox);
     // Override from QGCTool
     virtual void setToolbox(QGCToolbox* toolbox)final;
private:
    VehicleDataFactPack* createDataFact(Vehicle* vehicle);
    //
    void dataFactAdd(Vehicle* vehicle);
    //
    void dataFactRemove(Vehicle* vehicle);
    //Key&Value
    //Vehicle ID  ---  VehicleDataFactPack pointer
    QMap<int,VehicleDataFactPack *> *dataFactMap=nullptr;

protected:
    QGCApplication* _app;
    QGCToolbox*     _toolbox;
signals:

};

#endif // DATAMANAGER_H

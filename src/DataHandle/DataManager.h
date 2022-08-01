#ifndef DATAMANAGER_H
#define DATAMANAGER_H

//QT Head
#include <QObject>
#include <QDateTime>
#include <QMap>
//QGC Head
#include "QGCMAVLink.h"
#include "QGCApplication.h"
#include "Vehicle.h"
//ֲ����DataFact
class  VehicleDataFactPack:public QObject
{
    Q_OBJECT
public:
      explicit VehicleDataFactPack(QObject *parent = nullptr);
      //����ӿ�
      Q_INVOKABLE bool     flightState    () {return _flightState;}
      Q_INVOKABLE QString  flightTime     () {return _flightTime;}
      Q_INVOKABLE uint8_t  sprayState     () {return _sprayStat;}
      Q_INVOKABLE QString  uid            () {return _uid;}
      Q_INVOKABLE uint8_t  flowRate       () {return _flowRate;}
      Q_INVOKABLE double   workArea       () {return _workArea;}
      Q_INVOKABLE double   lot            () {return _lot;}
      Q_INVOKABLE double   lat            () {return _lat;}
      Q_INVOKABLE double   flightTailTude () {return _flightTailTude;}
      Q_INVOKABLE double   groundSpeed    () {return _groundSpeed;}
      Q_INVOKABLE QString  flightMode     () {return _flightMode;}

      //����ģʽ����// ���б�����ͺ������
      QStringList FlightModeType {
      "PreFlight",
      "Stabilize",
      "Guided",
      "Auto",
      "Test",
      "Altitude Hold",
      "RTL",
      "Loiter"
      };
private:
      static bool      _flightState;
      static QString   _flightTime;
      static uint8_t   _sprayStat;
      static QString   _uid ;
      static uint8_t   _flowRate;
      static double    _workArea;
      static double    _lot;
      static double    _lat;
      static double    _flightTailTude;
      static double    _groundSpeed;
      static bool      _gaugetype;
      //
      static bool      _upDataFlightFlag;
      static QString   _flightMode;
//�����Vehcile���յ�����
public slots:
//���˻����
  void _vehicleTakeOff();
//���˻�����
  void _vehicleLand();
//���˻����ʱ��
  void _vehicleFlightTime(QString time);
//���˻���ͷ��ͷ״̬�Ƿ��
  void _vehicleSprayState(bool isOpen);
//���˻�UID ��
  void _vehicleUid(QString uid);
//���˻����ٻ�ȡ֮���Ϊ С������ ��ʱδʹ��
  void _vehicleFlowRate(uint8_t flowRate);
//���˻���ҵ���(ע��Ҫ�ۼ�)
  void _vehicleWorkArea(double workArea);
//���˻�����
  void _vehicleLongitude(double lot);
//���˻�ά��
  void _vehicleLatitude(double lat);
//���˻��߶ȷ��и߶�
  void _vehicleFlighTaltiTude(double flightTaltiTude);
//���˻������ٶ�(����)
  void _vehicleGroundFlightSpeed(double groundSpeed);
//202281
//���˻����ݷ���ʱ��()//
  void _vehicleDataSendTime();
//���˻�Һλ��״̬
  void _vehicleLevelGaugeStatus(bool gaugetype);
//���˻�����״̬
  void _vehicleFlightMode(QString flightmodetype);
//���л�ת��QByteArray//

//ʱ���ת��//

//У�麯��//
   QByteArray *checkPack();
};
//��ʼ����̬����

//���ݹ�����
class DataManager : public QObject
{
    Q_OBJECT
public:
    explicit DataManager(QObject *parent = nullptr);
private:
    VehicleDataFactPack* createDataFact(Vehicle* vehicle);
    //
    void dataFactAdd(Vehicle* vehicle);
    //
    void dataFactRemove(Vehicle* vehicle);
    //Key&Value
    //Vehicle ID  ---  VehicleDataFactPack pointer
    QMap<int,VehicleDataFactPack *> *dataFactMap=nullptr;

signals:

};

#endif // DATAMANAGER_H

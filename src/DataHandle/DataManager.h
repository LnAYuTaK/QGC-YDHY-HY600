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
//植保机DataFact
class  VehicleDataFactPack:public QObject
{
    Q_OBJECT
public:
      explicit VehicleDataFactPack(QObject *parent = nullptr);
      //对外接口
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

      //飞行模式类型// 还有别的类型后续添加
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
//处理从Vehcile接收的数据
public slots:
//无人机起飞
  void _vehicleTakeOff();
//无人机降落
  void _vehicleLand();
//无人机起飞时间
  void _vehicleFlightTime(QString time);
//无人机喷头喷头状态是否打开
  void _vehicleSprayState(bool isOpen);
//无人机UID √
  void _vehicleUid(QString uid);
//无人机流速获取之后分为 小数整数 暂时未使用
  void _vehicleFlowRate(uint8_t flowRate);
//无人机作业面积(注意要累加)
  void _vehicleWorkArea(double workArea);
//无人机经度
  void _vehicleLongitude(double lot);
//无人机维度
  void _vehicleLatitude(double lat);
//无人机高度飞行高度
  void _vehicleFlighTaltiTude(double flightTaltiTude);
//无人机飞行速度(地速)
  void _vehicleGroundFlightSpeed(double groundSpeed);
//202281
//无人机数据发送时刻()//
  void _vehicleDataSendTime();
//无人机液位计状态
  void _vehicleLevelGaugeStatus(bool gaugetype);
//无人机飞行状态
  void _vehicleFlightMode(QString flightmodetype);
//序列化转换QByteArray//

//时间戳转换//

//校验函数//
   QByteArray *checkPack();
};
//初始化静态变量

//数据管理类
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

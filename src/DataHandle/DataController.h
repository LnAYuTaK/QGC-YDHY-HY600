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
#include "NetWorkLayer/NetWorkManager.h"
#include "FactGroup.h"

#define   PACKHEAD  "EB90"

//所有类型飞机数据包基类// Fact  重构
class  VehicleDataFactPack:public QObject
{
    Q_OBJECT
public:
      explicit VehicleDataFactPack(QObject *parent = nullptr);
      //获取校验完成的数据
      Q_INVOKABLE QString     pack          () ;

      //获取架次信息
      //Q_INVOKABLE QStringList get           (int index);
      //列表总长度
      Q_INVOKABLE int         listSize      () {return  flightMsgPack.size();}

      //飞行模式类型// 还有别的类型后续添加
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
//处理从Vehcile接收的数据
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
//private slots:
//      //更新飞行架次
//       void _updataFlightSorties();
//signals:
//       void updata();
private:
      //初始化PackList
      void  _initPackList();
      //整数小数分离
      QVector <qint64> splitDouble(double data,qint16 digit);
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
      static uint8_t   _gaugetype;
      static QString   _flightMode;
      //是否更新飞行架次flag
      static bool      _upDataFlightFlag;
      //帧头
      const  QString  packHead =PACKHEAD;
      //版本和固件号通过暂时获取通过HySetting获取
      const QString    _softWareVersion;
      const QString    _fireWareVersion;
      //存放所有信息
      QVector <QString>vehiclePack;
      //存放每一架次的飞行记录信息   QStringList << |用户账号|起飞时间|飞行用时|喷洒区域|喷洒亩数|喷洒农药用量|飞行控制号码|飞行距离|作物种类
      QVector <QStringList> flightMsgPack;
};
//数据管理类
class DataController: public QObject
{
    Q_OBJECT
public:
     DataController(void);
     //发送日志数据到后台
     void  sendData();
     //存储后台所需数据到本地文本TXT
     void  saveDataLocal();
    //Test

private:
    VehicleDataFactPack* createDataFact(Vehicle* vehicle);
    //自动绑定Vehicle 和dataFact
    void dataFactAdd(Vehicle* vehicle);
    //飞机移除自动删除dataFact
    void dataFactRemove(Vehicle* vehicle);
    //加载配置
    //void LoadSetting();
    //Vehicle ID  ---  VehicleDataFactPack pointer
    //Test 定时器连接活跃的Vehicle
    VehicleDataFactPack * _dataPack    = nullptr;
    QTimer              * dataSendTimer =nullptr;
    QThread   mThread;
    QTcpSocket mSocket;
protected:

signals:
    //发送次数增加
    void sendDataNumAdd();
    //
private:
     NetWorkManager  *   _networkMgr =nullptr;
};

#endif // DATAMANAGER_H

#include "DataController.h"
//初始化 VehicleDataFactPack
//调试宏
#define DEBUGINFO

//飞机类型定义 不要动
#define HY600
//对外显示的数据初始化
bool      VehicleDataFactPack::_flightState      = false;
QString   VehicleDataFactPack::_flightTime       = "2020-02-20 20:20:20";
uint8_t   VehicleDataFactPack::_sprayStat        = 0;
int       VehicleDataFactPack::_id               = 0;
uint8_t   VehicleDataFactPack::_flowRate         = 0;
double    VehicleDataFactPack::_workArea         = 0;
double    VehicleDataFactPack::_lot              = 0.0;
double    VehicleDataFactPack::_lat              = 0;
double    VehicleDataFactPack::_flightTailTude   = 0;
double    VehicleDataFactPack::_groundSpeed      = 0;
bool      VehicleDataFactPack::_upDataFlightFlag = false;
uint8_t   VehicleDataFactPack::_gaugetype        = 1;
QString   VehicleDataFactPack::_flightMode       = "";

VehicleDataFactPack::VehicleDataFactPack(QObject *parent)
    : QObject{parent}
{
   //初始化vehiclePack方便赋值
    this->_initPackList();
}

void VehicleDataFactPack::_initPackList()
{
    this->vehiclePack.clear();
    vehiclePack.append(packHead);      //帧头   0
    vehiclePack.append(QString(4,'0')); //发送次数 1
    vehiclePack.append(QString(8,'0'));//起飞时间 2
    vehiclePack.append(QString(3,'0'));//无人机ID 3
    vehiclePack.append(QString(3,'0'));//用户ID  4
    vehiclePack.append(QString(1,'0'));//流速整数部分5
    vehiclePack.append(QString(2,'0'));//流速小数部分6
    vehiclePack.append(QString(2,'0'));//作业面积整数部分7
    vehiclePack.append(QString(2,'0'));//作业面积小数部分8
    vehiclePack.append(QString(1,'0'));//喷洒状态9
    vehiclePack.append(QString(2,'0'));//经度整数10
    vehiclePack.append(QString(6,'0'));//经度小数部分11
    vehiclePack.append(QString(2,'0'));//维度整数部分12
    vehiclePack.append(QString(6,'0'));//维度小数部分13
    vehiclePack.append(QString(1,'0'));//高度正负14
    vehiclePack.append(QString(3,'0'));//高度整数15
    vehiclePack.append(QString(2,'0'));//高度小数16
    vehiclePack.append(QString(2,'0'));//飞行地速整数17
    vehiclePack.append(QString(2,'0'));//飞行地速小数18
    vehiclePack.append(QString(4,'0'));//数据发送时间19
    vehiclePack.append(QString(1,'0'));//液位计状态20
    vehiclePack.append(QString(1,'0'));//飞行模式21
}
//202282
//数据处理
void VehicleDataFactPack::_vehicleDataSendNumChanged()
{
    static int dataSendTimes=0;
    dataSendTimes++;
}
void VehicleDataFactPack::_vehicleMsgText(QString messageText)
{
    if(messageText== "No Load RTL") {
        _gaugetype  = 0;
        vehiclePack[20] = QString("%1").arg(_gaugetype,1,16,QLatin1Char('0'));
    }
}

void VehicleDataFactPack::_vehicleFlightTime(QString time)
{
    if(!_upDataFlightFlag) {
       _flightTime       = time;
       _upDataFlightFlag = true;  
    }     
}
//无人机起飞
void VehicleDataFactPack::_vehicleTakeOff()
{
    _flightState = true;

}
//无人机降落
void VehicleDataFactPack::_vehicleLand()
{
    _flightState= false;
    _upDataFlightFlag= false;
}
//无人机喷头喷头状态是否打开
void VehicleDataFactPack::_vehicleSprayState(bool isOpen)
{
    if(isOpen!=true) {
       _sprayStat = 8;
    }
    else{
       _sprayStat = 0;
    }
}
//无人机ID
void VehicleDataFactPack::_vehicleid(int id)
{
    _id= id;
    vehiclePack[4] = QString("%1").arg(_id,3,16,QLatin1Char('0'));

}
//无人机流速获取之后分为 小数整数 暂时未使用
void VehicleDataFactPack::_vehicleFlowRate(uint8_t flowRate)
{
    _flowRate = flowRate;
    QVector <qint64> temp = splitDouble(_flowRate,2);
    qDebug () <<temp[1] <<temp [0] <<"TEMP";
    vehiclePack[5] = QString("%1").arg(temp[0],1,16,QLatin1Char('0'));
    vehiclePack[6] = QString("%1").arg(temp[1],2,16,QLatin1Char('0'));
}
//无人机作业面积(注意要累加
void VehicleDataFactPack::_vehicleWorkArea(double workArea)
{
    //累计面积
    if(_sprayStat>0){
       _workArea += workArea;
    }
   QVector <qint64> temp = splitDouble(_workArea,2);
   vehiclePack[7] = QString("%1").arg(temp[0],2,16,QLatin1Char('0'));
   vehiclePack[8] = QString("%1").arg(temp[1],2,16,QLatin1Char('0'));
}
//无人机经度
void VehicleDataFactPack::_vehicleLongitude(double lot)
{
    _lot =lot;
    QVector <qint64> temp = splitDouble(_lot,7);
    vehiclePack[10] = QString("%1").arg(temp[0],2,16,QLatin1Char('0'));
    vehiclePack[11] = QString("%1").arg(temp[1],6,16,QLatin1Char('0'));
}
//无人机维度
void VehicleDataFactPack::_vehicleLatitude(double lat)
{
    _lat =lat;
    QVector <qint64> temp = splitDouble(_lat,7);
    vehiclePack[12] = QString("%1").arg(temp[0],2,16,QLatin1Char('0'));
    vehiclePack[13] = QString("%1").arg(temp[1],6,16,QLatin1Char('0'));
}
//无人机高度飞行高度
void VehicleDataFactPack::_vehicleFlighTaltiTude(double flightTaltiTude)
{
    _flightTailTude = flightTaltiTude;
    if(_flightTailTude<0)
    {
       vehiclePack[14] =  QString("%1").arg(1,1,16,QLatin1Char('0'));
    }
    else{
     vehiclePack[14] =  QString("%1").arg(0,1,16,QLatin1Char('0'));
    }
    QVector <qint64> temp = splitDouble(qAbs(_flightTailTude),2);
    vehiclePack[15] = QString("%1").arg(temp[0],3,16,QLatin1Char('0'));
    vehiclePack[16] = QString("%1").arg(temp[1],2,16,QLatin1Char('0'));
}
//无人机飞行速度(地速)
void VehicleDataFactPack::_vehicleGroundFlightSpeed(double groundSpeed)
{
    _groundSpeed = groundSpeed;
    QVector <qint64> temp =splitDouble(groundSpeed,2);
    vehiclePack[17] = QString("%1").arg(temp[0],2,16,QLatin1Char('0'));
    vehiclePack[18] = QString("%1").arg(temp[1],2,16,QLatin1Char('0'));
}
//无人机数据发送时刻()//暂时弃用
void VehicleDataFactPack::_vehicleDataSendTime()
{

}
//无人机液位计状态//暂时弃用
void VehicleDataFactPack::_vehicleLevelGaugeStatus(uint8_t gaugetype)
{

}
//无人机飞行模式
void VehicleDataFactPack::_vehicleFlightMode(QString flightmodetype)
{
    _flightMode =flightmodetype;
    qint16 value  = FlightModeType.indexOf(_flightMode);
    if(value < 0 || value > 7){
      vehiclePack[21] = QString("%1").arg(0,1,16,QLatin1Char('0'));
    }
    else{
      vehiclePack[21] = QString("%1").arg(1,1,16,QLatin1Char('0'));
    }
}
//整数小数分离
QVector <qint64> VehicleDataFactPack::splitDouble(double data,qint16 digit)
{
  QVector <qint64> temp ;
  QString data_str = QString::number(data,'f',digit).toUtf8();
  QStringList list = data_str.split(".");
  for(int i =0; i<2 ;i++)
    temp.append(list[i].toInt());
  return temp;
}
//打包数据并加上校验
QString VehicleDataFactPack::pack()
{
    QString  pack;
    for(int i = 0;i<vehiclePack.size();++i){
         pack +=vehiclePack[i];
    }
    QByteArray pack_array = pack.toLatin1();
    long checksumtemp = 0;
    for(int i = 0; i < pack_array.size(); i++){
        checksumtemp +=pack_array[i];
    }
    QString checkSum   = QString("%1").arg(checksumtemp,4,16,QLatin1Char('0'));
    return pack+checkSum;
}
//更新架次信息
//void VehicleDataFactPack::_updataFlightSorties()
//{
//    QStringList list;
//    QString userName = "010";

//}

DataController::DataController(void)
 : _networkMgr()
{
   dataSendTimer =new  QTimer();
   MultiVehicleManager *manager = qgcApp()->toolbox()->multiVehicleManager();
   connect(manager,&MultiVehicleManager::vehicleAdded, this,&DataController::dataFactAdd);
   connect(manager,&MultiVehicleManager::vehicleRemoved, this,&DataController::dataFactRemove);
   //定时1秒发送一次飞行信息到后台
   connect(dataSendTimer,&QTimer::timeout,this,&DataController::sendData);
   //本地日志记录
   connect(dataSendTimer,&QTimer::timeout,this,&DataController::saveDataLocal);
   dataSendTimer->setInterval(1000);
   //本地数据库记录TUDO



}

VehicleDataFactPack* DataController::createDataFact(Vehicle* vehicle)
{
  if(vehicle!=nullptr){
   //为不同类型飞机实例化不同的需求
   #ifdef HY600
      if(this->_dataPack==nullptr){
          _dataPack =new VehicleDataFactPack();
      }
   #endif
     return _dataPack;
  }
   return nullptr;
}

//这里比较繁琐后面改成函数模板//
void DataController::dataFactAdd(Vehicle* vehicle)
{
   VehicleDataFactPack * data  =this->createDataFact(vehicle);
   if((data!=nullptr)){
       connect(vehicle,&Vehicle::vehicleTakeOff,data,&VehicleDataFactPack::_vehicleTakeOff);
       connect(vehicle,&Vehicle::vehicleLand,data,&VehicleDataFactPack::_vehicleLand);
       connect(vehicle,&Vehicle::vehicleFlightTime,data,&VehicleDataFactPack::_vehicleFlightTime);
       connect(vehicle,&Vehicle::vehicleSprayState,data,&VehicleDataFactPack::_vehicleSprayState);
       connect(vehicle,&Vehicle::vehicleid,data,&VehicleDataFactPack::_vehicleid);
       connect(vehicle,&Vehicle::vehicleFlowRate,data,&VehicleDataFactPack::_vehicleFlowRate);
       connect(vehicle,&Vehicle::vehicleWorkArea,data,&VehicleDataFactPack::_vehicleWorkArea);
       connect(vehicle,&Vehicle::vehicleLongitude,data,&VehicleDataFactPack::_vehicleLongitude);
       connect(vehicle,&Vehicle::vehicleLatitude,data,&VehicleDataFactPack::_vehicleLatitude);
       connect(vehicle,&Vehicle::vehicleFlighTaltiTude,data,&VehicleDataFactPack::_vehicleFlighTaltiTude);
       connect(vehicle,&Vehicle::vehicleGroundFlightSpeed,data,&VehicleDataFactPack::_vehicleGroundFlightSpeed);
       connect(vehicle,&Vehicle::vehicleDataSendTime,data,&VehicleDataFactPack::_vehicleDataSendTime);
       connect(vehicle,&Vehicle::vehicleMsgText,data,&VehicleDataFactPack::_vehicleMsgText);
       connect(vehicle,&Vehicle::vehicleFlightMode,data,&VehicleDataFactPack::_vehicleFlightMode);     
       connect(this,&DataController::sendDataNumAdd,data,&VehicleDataFactPack::_vehicleDataSendNumChanged);
       dataSendTimer->start();
   }
}

void DataController::dataFactRemove(Vehicle* vehicle)
{
    if(vehicle!=nullptr&&_dataPack!=nullptr){
           _dataPack->deleteLater();
           dataSendTimer->stop();
    }
}

//发送到后台
void DataController::sendData()
{
      mSocket.connectToHost("192.168.3.113",8901);
      if (mSocket.waitForConnected(100)) {
          if(_dataPack!=nullptr){
             if(mSocket.write(_dataPack->pack().toLocal8Bit())){
                emit sendDataNumAdd();
             }
             mSocket.flush();
             mSocket.close();
          }
      }
}

//TODU 需要重构
//这里是存储到本地 根据AppSetting 的文件夹存放
void DataController::saveDataLocal()
{
   if(_dataPack!=nullptr){
   QString min = QDateTime::currentDateTime().toString("yyyyMMdd");
   QString timestr = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
#if !defined(__android__)
   QString dir_path =  "../DATA_SAVE";
#else
   QString dir_path =  "/storage/emulated/0/DATA_SAVE";
#endif
   QDir dir;
   if(!dir.exists(dir_path)){
       dir.mkdir(dir_path);
       qDebug() << "Create Dir";
   }
   QString save_filename = dir_path + "/" + min + ".txt";
   QFile f(save_filename);
   QTextStream in(&f);
   if(!f.open( QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)){
       qDebug()<<"Write Error";
       return;
   }
   in <<_dataPack->pack().toLocal8Bit();
   f.flush();
   f.close();
   }
}






















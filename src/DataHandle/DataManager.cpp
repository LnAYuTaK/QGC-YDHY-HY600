#include "DataManager.h"
//初始化 VehicleDataFactPack


//调试宏
#define DEBUGINFO
//对外显示的数据
bool      VehicleDataFactPack::_flightState      = false;
QString   VehicleDataFactPack::_flightTime       = "2020-02-20 20:20:20";
uint8_t   VehicleDataFactPack::_sprayStat        = 0;
int       VehicleDataFactPack::_id               = 0;
uint8_t   VehicleDataFactPack::_flowRate         = 0;
double    VehicleDataFactPack::_workArea         = 0;
double    VehicleDataFactPack::_lot              = 0;
double    VehicleDataFactPack::_lat              = 0;
double    VehicleDataFactPack::_flightTailTude   = 0;
double    VehicleDataFactPack::_groundSpeed      = 0;
bool      VehicleDataFactPack::_upDataFlightFlag = false;
bool      VehicleDataFactPack::_gaugetype        = false;
QString   VehicleDataFactPack::_flightMode       = "";

VehicleDataFactPack::VehicleDataFactPack(QObject *parent)
    : QObject{parent}
{
   //初始化vehiclePack方便赋值
    vehiclePack[0]  = packHead;       //帧头
    vehiclePack.append(QByteArray(4,0));//计数器
    vehiclePack[2]  = QByteArray(8,0);//起飞时间
    vehiclePack[3]  = QByteArray(3,0);//无人机ID
    vehiclePack[4]  = QByteArray(3,0);//用户ID
    vehiclePack[5]  = QByteArray(1,0);//流速整数部分
    vehiclePack[6]  = QByteArray(2,0);//流速小数部分
    vehiclePack[7]  = QByteArray(2,0);//作业面积整数部分
    vehiclePack[8]  = QByteArray(2,0);//作业面积小数部分
    vehiclePack[9]  = QByteArray(1,0);//喷洒状态
    vehiclePack[10] = QByteArray(2,0);//经度整数
    vehiclePack[11] = QByteArray(6,0);//经度小数部分
    vehiclePack[12] = QByteArray(2,0);//维度整数部分
    vehiclePack[13] = QByteArray(6,0);//维度小数部分
    vehiclePack[14] = QByteArray(1,0);//高度正负
    vehiclePack[15] = QByteArray(3,0);//高度整数
    vehiclePack[16] = QByteArray(2,0);//高度小数
    vehiclePack[17] = QByteArray(2,0);//飞行地速整数
    vehiclePack[18] = QByteArray(2,0);//飞行地速小数
    vehiclePack[19] = QByteArray(4,0);//数据发送时间
    vehiclePack[20] = QByteArray(1,0);//液位计状态
    vehiclePack[21] = QByteArray(1,0);//飞行模式
    vehiclePack[22] = QByteArray(4,0);//校验
    qDebug() << "InitOK";
}
//202282
//数据处理
void VehicleDataFactPack::_vehicleFlightTime(QString time)
{
    if(!_upDataFlightFlag){
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
    vehiclePack[4] = QString("%1").arg(_id,3,16,QLatin1Char('0')).toLatin1();
    qDebug()<<"!!!!!!!!!!!!!!!!!!!!"<< _id;
}
//无人机流速获取之后分为 小数整数 暂时未使用
void VehicleDataFactPack::_vehicleFlowRate(uint8_t flowRate)
{
    _flowRate = flowRate;
    QVector <qint64> temp = splitDouble(_flowRate,2);
    vehiclePack[5] = QString("%1").arg(temp[0],1,16,QLatin1Char('0')).toLatin1();
    vehiclePack[6] = QString("%1").arg(temp[1],2,16,QLatin1Char('0')).toLatin1();
}
//无人机作业面积(注意要累加
void VehicleDataFactPack::_vehicleWorkArea(double workArea)
{
    //累计面积
    if(_sprayStat>0){
       _workArea += workArea;
    }
    QVector <qint64> temp = splitDouble(_workArea,2);
    vehiclePack[7] = QString("%1").arg(temp[0],2,16,QLatin1Char('0')).toLatin1();
    vehiclePack[8] = QString("%1").arg(temp[1],2,16,QLatin1Char('0')).toLatin1();
}
//无人机经度
void VehicleDataFactPack::_vehicleLongitude(double lot)
{
    _lot =lot;
    QVector <qint64> temp = splitDouble(_lot,2);
    vehiclePack[10] = QString("%1").arg(temp[0],2,16,QLatin1Char('0')).toLatin1();
    vehiclePack[11] = QString("%1").arg(temp[1],6,16,QLatin1Char('0')).toLatin1();
}
//无人机维度
void VehicleDataFactPack::_vehicleLatitude(double lat)
{
    _lat =lat;
    QVector <qint64> temp = splitDouble(_lot,2);
    vehiclePack[12] = QString("%1").arg(temp[0],2,16,QLatin1Char('0')).toLatin1();
    vehiclePack[13] = QString("%1").arg(temp[1],6,16,QLatin1Char('0')).toLatin1();
}
//无人机高度飞行高度
void VehicleDataFactPack::_vehicleFlighTaltiTude(double flightTaltiTude)
{
    _flightTailTude = flightTaltiTude;
    if(_flightTailTude<0)
    {
       vehiclePack[14] =  QString("%1").arg(1,1,16,QLatin1Char('0')).toLatin1();
    }
    else{
       vehiclePack[14] =  QString("%1").arg(0,1,16,QLatin1Char('0')).toLatin1();
    }
    QVector <qint64> temp = splitDouble(qAbs(_flightTailTude),2);
    vehiclePack[15] = QString("%1").arg(temp[0],3,16,QLatin1Char('0')).toLatin1();
    vehiclePack[16] = QString("%1").arg(temp[1],2,16,QLatin1Char('0')).toLatin1();
}
//无人机飞行速度(地速)
void VehicleDataFactPack::_vehicleGroundFlightSpeed(double groundSpeed)
{
    _groundSpeed = groundSpeed;
    QVector <qint64> temp =splitDouble(groundSpeed,2);
    vehiclePack[17] = QString("%1").arg(temp[0],2,16,QLatin1Char('0')).toLatin1();
    vehiclePack[18] = QString("%1").arg(temp[1],2,16,QLatin1Char('0')).toLatin1();
}
//无人机数据发送时刻()//暂时不用
void VehicleDataFactPack::_vehicleDataSendTime()
{

}
//无人机液位计状态
void VehicleDataFactPack::_vehicleLevelGaugeStatus(bool gaugetype)
{
    _gaugetype = gaugetype;
}
//无人机飞行模式
void VehicleDataFactPack::_vehicleFlightMode(QString flightmodetype)
{
    _flightMode =flightmodetype;
    qint16 value  = FlightModeType.indexOf(_flightMode);
    if(value < 0 || value > 7){
       vehiclePack[21] = QString("%1").arg(0,1,16,QLatin1Char('0')).toLatin1();
    }
}
//返回临时QVector
QVector <qint64> VehicleDataFactPack::splitDouble(double data,qint16 digit)
{
  QString data_str = QString::number(data,'f',digit).toUtf8();
  QStringList list = data_str.split(".");
  QVector <qint64> temp ;
  for(int i =0; i<2 ;i++)
      temp[i] = list[i].toInt();
  return temp;
}

//DataManager Class
DataManager::DataManager(QGCApplication* app, QGCToolbox* toolbox)
    : QGCTool(app, toolbox)
{
   dataFactMap = new QMap<int,VehicleDataFactPack *>;
//   connect(qgcApp()->toolbox()->multiVehicleManager(),&MultiVehicleManager::vehicleAdded, this,&DataManager::dataFactAdd);
//   connect(qgcApp()->toolbox()->multiVehicleManager(),&MultiVehicleManager::vehicleRemoved, this,&DataManager::dataFactRemove);
   //创建当有新的Vehcile实例化后 创建相应的Data实例
}

void DataManager::setToolbox(QGCToolbox *toolbox)
{
    QGCTool::setToolbox(toolbox);
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
    connect(qgcApp()->toolbox()->multiVehicleManager(),&MultiVehicleManager::vehicleAdded, this,&DataManager::dataFactAdd);
    connect(qgcApp()->toolbox()->multiVehicleManager(),&MultiVehicleManager::vehicleRemoved, this,&DataManager::dataFactRemove);
}

VehicleDataFactPack* DataManager::createDataFact(Vehicle* vehicle)
{
  if(vehicle!=nullptr){
    VehicleDataFactPack * data = new VehicleDataFactPack();
    return data;
  }
   return nullptr;
}
//这里比较繁琐后面改成函数模板//
void DataManager::dataFactAdd(Vehicle* vehicle)
{
   VehicleDataFactPack * data  =this->createDataFact(vehicle);
   if(data!=nullptr){
       dataFactMap->insert(vehicle->id(),data);
       //这里绑定一下信号槽
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
       connect(vehicle,&Vehicle::vehicleLevelGaugeStatus,data,&VehicleDataFactPack::_vehicleLevelGaugeStatus);
       connect(vehicle,&Vehicle::vehicleFlightMode,data,&VehicleDataFactPack::_vehicleFlightMode);
   }
}

void DataManager::dataFactRemove(Vehicle* vehicle)
{
    if(vehicle!=nullptr||(!dataFactMap->isEmpty()))
    {
        if(dataFactMap->contains(vehicle->id()))
        {
           dataFactMap->value(vehicle->id())->deleteLater();
           dataFactMap->remove(vehicle->id());
        }
    }
}














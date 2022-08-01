#include "DataManager.h"
//初始化 VehicleDataFactPack
bool      VehicleDataFactPack::_flightState      = false;
QString   VehicleDataFactPack::_flightTime       = "2020-02-20 20:20:20";
uint8_t   VehicleDataFactPack::_sprayStat        = 0;
QString   VehicleDataFactPack::_uid              = "";
uint8_t   VehicleDataFactPack::_flowRate         = 0;
double    VehicleDataFactPack::_workArea         = 0;
double    VehicleDataFactPack::_lot              = 0;
double    VehicleDataFactPack::_lat              = 0;
double    VehicleDataFactPack::_flightTailTude   = 0;
double    VehicleDataFactPack::_groundSpeed      = 0;
bool      VehicleDataFactPack::_upDataFlightFlag = false;

VehicleDataFactPack::VehicleDataFactPack(QObject *parent)
    : QObject{parent}
{

}

void VehicleDataFactPack::_vehicleFlightTime(QString time)
{
    if(!_upDataFlightFlag){
       _flightTime       = time;
       _upDataFlightFlag = true;
    }
}

void VehicleDataFactPack::_vehicleTakeOff()
{
    _flightState = true;
}

void VehicleDataFactPack::_vehicleLand()
{
    _flightState= false;
    _upDataFlightFlag= false;
}
//fool function
void VehicleDataFactPack::_vehicleSprayState(bool isOpen)
{
    if(isOpen!=true) {
       _sprayStat = 8;
    }
    else{
       _sprayStat = 0;
    }
}

void VehicleDataFactPack::_vehicleUid(QString uid)
{
    _uid= uid;
}

void VehicleDataFactPack::_vehicleFlowRate(uint8_t flowRate)
{
    _flowRate = flowRate;
}

void VehicleDataFactPack::_vehicleWorkArea(double workArea)
{
    //累计面积
    if(_sprayStat>0){
     _workArea += workArea;
    }
}

void VehicleDataFactPack::_vehicleLongitude(double lot)
{
    _lot =lot;
}

void VehicleDataFactPack::_vehicleLatitude(double lat)
{
    _lat =lat;
}

void VehicleDataFactPack::_vehicleFlighTaltiTude(double flightTaltiTude)
{
    _flightTailTude = flightTaltiTude;
}

void VehicleDataFactPack::_vehicleGroundFlightSpeed(double groundSpeed)
{
    _groundSpeed = groundSpeed;
}

void VehicleDataFactPack::_vehicleLevelGaugeStatus(bool gaugetype)
{
    _gaugetype = gaugetype;
}

void VehicleDataFactPack::_vehicleFlightMode(QString flightmodetype)
{
    _flightMode =flightmodetype;
}

//DataManager Class
DataManager::DataManager(QObject *parent)
    : QObject{parent}
{
   dataFactMap = new QMap<int,VehicleDataFactPack *>;
   //创建当有新的Vehcile实例化后 创建相应的Data实例
   connect(qgcApp()->toolbox()->multiVehicleManager(),&MultiVehicleManager::vehicleAdded, this,&DataManager::dataFactAdd);
   connect(qgcApp()->toolbox()->multiVehicleManager(),&MultiVehicleManager::vehicleRemoved, this,&DataManager::dataFactRemove);
}

VehicleDataFactPack* DataManager::createDataFact(Vehicle* vehicle)
{
  if(vehicle!=nullptr){
    VehicleDataFactPack * data  =new VehicleDataFactPack();
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
       connect(vehicle,&Vehicle::vehicleUid,data,&VehicleDataFactPack::_vehicleUid);
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














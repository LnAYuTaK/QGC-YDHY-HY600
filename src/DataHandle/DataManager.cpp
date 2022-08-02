#include "DataManager.h"
//��ʼ�� VehicleDataFactPack


//���Ժ�
#define DEBUGINFO
//������ʾ������
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
   //��ʼ��vehiclePack���㸳ֵ
    vehiclePack[0]  = packHead;       //֡ͷ
    vehiclePack.append(QByteArray(4,0));//������
    vehiclePack[2]  = QByteArray(8,0);//���ʱ��
    vehiclePack[3]  = QByteArray(3,0);//���˻�ID
    vehiclePack[4]  = QByteArray(3,0);//�û�ID
    vehiclePack[5]  = QByteArray(1,0);//������������
    vehiclePack[6]  = QByteArray(2,0);//����С������
    vehiclePack[7]  = QByteArray(2,0);//��ҵ�����������
    vehiclePack[8]  = QByteArray(2,0);//��ҵ���С������
    vehiclePack[9]  = QByteArray(1,0);//����״̬
    vehiclePack[10] = QByteArray(2,0);//��������
    vehiclePack[11] = QByteArray(6,0);//����С������
    vehiclePack[12] = QByteArray(2,0);//ά����������
    vehiclePack[13] = QByteArray(6,0);//ά��С������
    vehiclePack[14] = QByteArray(1,0);//�߶�����
    vehiclePack[15] = QByteArray(3,0);//�߶�����
    vehiclePack[16] = QByteArray(2,0);//�߶�С��
    vehiclePack[17] = QByteArray(2,0);//���е�������
    vehiclePack[18] = QByteArray(2,0);//���е���С��
    vehiclePack[19] = QByteArray(4,0);//���ݷ���ʱ��
    vehiclePack[20] = QByteArray(1,0);//Һλ��״̬
    vehiclePack[21] = QByteArray(1,0);//����ģʽ
    vehiclePack[22] = QByteArray(4,0);//У��
    qDebug() << "InitOK";
}
//202282
//���ݴ���
void VehicleDataFactPack::_vehicleFlightTime(QString time)
{
    if(!_upDataFlightFlag){
       _flightTime       = time;
       _upDataFlightFlag = true;  
    }     
}
//���˻����
void VehicleDataFactPack::_vehicleTakeOff()
{
    _flightState = true;

}
//���˻�����
void VehicleDataFactPack::_vehicleLand()
{
    _flightState= false;
    _upDataFlightFlag= false;
}
//���˻���ͷ��ͷ״̬�Ƿ��
void VehicleDataFactPack::_vehicleSprayState(bool isOpen)
{
    if(isOpen!=true) {
       _sprayStat = 8;
    }
    else{
       _sprayStat = 0;
    }
}
//���˻�ID
void VehicleDataFactPack::_vehicleid(int id)
{
    _id= id;
    vehiclePack[4] = QString("%1").arg(_id,3,16,QLatin1Char('0')).toLatin1();
    qDebug()<<"!!!!!!!!!!!!!!!!!!!!"<< _id;
}
//���˻����ٻ�ȡ֮���Ϊ С������ ��ʱδʹ��
void VehicleDataFactPack::_vehicleFlowRate(uint8_t flowRate)
{
    _flowRate = flowRate;
    QVector <qint64> temp = splitDouble(_flowRate,2);
    vehiclePack[5] = QString("%1").arg(temp[0],1,16,QLatin1Char('0')).toLatin1();
    vehiclePack[6] = QString("%1").arg(temp[1],2,16,QLatin1Char('0')).toLatin1();
}
//���˻���ҵ���(ע��Ҫ�ۼ�
void VehicleDataFactPack::_vehicleWorkArea(double workArea)
{
    //�ۼ����
    if(_sprayStat>0){
       _workArea += workArea;
    }
    QVector <qint64> temp = splitDouble(_workArea,2);
    vehiclePack[7] = QString("%1").arg(temp[0],2,16,QLatin1Char('0')).toLatin1();
    vehiclePack[8] = QString("%1").arg(temp[1],2,16,QLatin1Char('0')).toLatin1();
}
//���˻�����
void VehicleDataFactPack::_vehicleLongitude(double lot)
{
    _lot =lot;
    QVector <qint64> temp = splitDouble(_lot,2);
    vehiclePack[10] = QString("%1").arg(temp[0],2,16,QLatin1Char('0')).toLatin1();
    vehiclePack[11] = QString("%1").arg(temp[1],6,16,QLatin1Char('0')).toLatin1();
}
//���˻�ά��
void VehicleDataFactPack::_vehicleLatitude(double lat)
{
    _lat =lat;
    QVector <qint64> temp = splitDouble(_lot,2);
    vehiclePack[12] = QString("%1").arg(temp[0],2,16,QLatin1Char('0')).toLatin1();
    vehiclePack[13] = QString("%1").arg(temp[1],6,16,QLatin1Char('0')).toLatin1();
}
//���˻��߶ȷ��и߶�
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
//���˻������ٶ�(����)
void VehicleDataFactPack::_vehicleGroundFlightSpeed(double groundSpeed)
{
    _groundSpeed = groundSpeed;
    QVector <qint64> temp =splitDouble(groundSpeed,2);
    vehiclePack[17] = QString("%1").arg(temp[0],2,16,QLatin1Char('0')).toLatin1();
    vehiclePack[18] = QString("%1").arg(temp[1],2,16,QLatin1Char('0')).toLatin1();
}
//���˻����ݷ���ʱ��()//��ʱ����
void VehicleDataFactPack::_vehicleDataSendTime()
{

}
//���˻�Һλ��״̬
void VehicleDataFactPack::_vehicleLevelGaugeStatus(bool gaugetype)
{
    _gaugetype = gaugetype;
}
//���˻�����ģʽ
void VehicleDataFactPack::_vehicleFlightMode(QString flightmodetype)
{
    _flightMode =flightmodetype;
    qint16 value  = FlightModeType.indexOf(_flightMode);
    if(value < 0 || value > 7){
       vehiclePack[21] = QString("%1").arg(0,1,16,QLatin1Char('0')).toLatin1();
    }
}
//������ʱQVector
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
   //���������µ�Vehcileʵ������ ������Ӧ��Dataʵ��
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
//����ȽϷ�������ĳɺ���ģ��//
void DataManager::dataFactAdd(Vehicle* vehicle)
{
   VehicleDataFactPack * data  =this->createDataFact(vehicle);
   if(data!=nullptr){
       dataFactMap->insert(vehicle->id(),data);
       //�����һ���źŲ�
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














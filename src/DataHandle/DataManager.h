#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>
//ï¿½ï¿½ï¿½ï¿½Ò»Ð©ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ÝµÄ·ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
//ï¿½ï¿½Ì¬ï¿½ï¿½ï¿½ï¿½ï¿½Ý°ï¿½
class  VehicleParaMeterPack:public QObject
{
    Q_OBJECT
public:



private:
    static QByteArray packHead;  // 4Ö¡Í·
    static qint64 Counter;   // ¼ÆÊýÆ÷
    static QByteArray FlightTime;// Æð·ÉÊ±¼ä
    static QByteArray  VehicleID;

};

//
class DataManager : public QObject
{
    Q_OBJECT
public:
    explicit DataManager(QObject *parent = nullptr);







signals:

};

#endif // DATAMANAGER_H

#ifndef HYSETTINGS_H
#define HYSETTINGS_H


//QT Head
#include <QObject>
#include <QSettings>
#include <QFile>
#include <QDebug>
#include <QDir>
//QGC Head
#include "QGCApplication.h"


//Singleton
class HySettings : public QObject
{
    Q_OBJECT
public:
   static HySettings* getSettings();

   //Config filename
   static const char *NetWorkConfigFile;
   static const char *UserConfigFile;

public slots:
   QVariant getNetValue(QString configtype,const QString &section,const QString &key);
private:
    HySettings();
    HySettings(const  HySettings&){}
    static HySettings * instance;
    //Õ¯¬Á…Ë÷√ini
    static QSettings * NetSetting;
    //”√ªß≈‰÷√ini
    static QSettings * UserSetting;


signals:

};

#endif // HYSETTINGS_H

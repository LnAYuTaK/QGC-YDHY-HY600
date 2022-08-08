#ifndef NETLAYER_H
#define NETLAYER_H

//QT Head
#include <QObject>
#include <QTcpSocket>
#include <QFile>
#include <QThread>
#include <QDataStream>
#include <QCryptographicHash>
#include <QTimer>
#include <QTime>
#include <QFileInfo>
//QGC Head
#include "QGCApplication.h"
#include "HySettings.h"
//这里准备重构一下作为网络任务基类
class NetLayer : public QObject
{
    Q_OBJECT
public:
    explicit NetLayer(QObject *parent = nullptr);
    //任务定时器
    QTimer*  TaskTimeOut ;
    //回复给QML显示的错误类型枚举
private:

public slots:

    //Task
    void SendBinLogFile(QString);
    //Task
    //void SendData();
private slots:


signals:
    void LogSendSuccess();
    void LogSendFail();
};

#endif // NETLAYER_H

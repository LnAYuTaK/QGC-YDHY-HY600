#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H
#include <QTcpSocket>
#include <QObject>
#include <QMap>
#include <QQueue>
#include <QMutex>
#include "GeoTagController.h"
#include "QGCToolbox.h"
#include "DataHandle/DataController.h"
#include "LogDownloadController.h"

//网络管理类用于管理所有后台任务包括datacontroller 后台实时数据
class LogSendTask  :public QObject
{
    Q_OBJECT
public:
    LogSendTask (QString);
    //获取文件名字
    QString logFile         () const { return _logFile;}

    void send               ();
protected:
    //耗时任务
    void work                ();
signals:
    void error              (QString errorMsg);

private slots:
    bool ready ();
private:
    QMutex                  _mutex;
    QString                 _logFile;
    QFile                   _file;
    QByteArray              _md5;
    QString                 _reqPack;
    QByteArray              _filedata;
};

class NetWorkManager  :public QGCTool {

   Q_OBJECT
public:
   NetWorkManager                     (QGCApplication* app, QGCToolbox* toolbox);
   // QGCTool overrides
   void setToolbox                    (QGCToolbox* toolbox) final;
   //重构一下
   //Q_INVOKABLE void sendBinLogFile    (QString);
   //管理后台数据的控制器
   DataController*  datacontroller()  {return _datacontroller;}


   //队列里边添加任务
   bool             addTask(/*LogSendTask **/QString filename);
   //执行所有任务
   Q_INVOKABLE void             runTask();

   Q_INVOKABLE void             show();
private:
   QMutex                             _mutex;
   DataController*                    _datacontroller;
   //发送日志任务
   //LogSendTask                      _worker;
   //错误信息
   QString                            _errorMessage;
   //日志的任务队列
   QQueue<LogSendTask*>               _taskQueue;
   //线程
   QThread                            _workThread;

private slots:
   //void _managerError                 (QString errorMsg);
   void _workerError                  (QString errorMsg);

};
#endif // NETWORKMANAGER_H

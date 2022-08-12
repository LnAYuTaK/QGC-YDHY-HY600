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
class QGCLogEntry;
struct LogDownloadData;
//Task 基类用于任务类的继承
class Task    :public QThread
{
     Q_OBJECT
public :
    Task();
    //需要自己实现work和析构
    virtual void work() = 0;
    virtual ~Task() =0 ;
};
//日志任务
class LogSendTask  :public Task
{
    Q_OBJECT
public:
    LogSendTask (QString filename , QGCLogEntry*  logEntry);
    ~LogSendTask();
    //Task Overrride
    void work               ();
protected:
    // Qthread Overrride
    void run                ();
signals:
    void error              (QString errorMsg);
    //发送成功后主界面显示发送成功
    void stateChanged       (QString stat);
private slots:
    //任务准备工作
    bool _ready              (void);
private:
    QMutex                  _mutex;
    QString                 _logFile;
    QFile                   _file;
    QByteArray              _md5;
    QString                 _reqPack;
    QByteArray              _filedata;
    QGCLogEntry *           _logEntry;
};

class NetWorkManager  :public QGCTool {

   Q_OBJECT
public:
   NetWorkManager                      (QGCApplication* app, QGCToolbox* toolbox);
   //QGCTool overrides
   void setToolbox                     (QGCToolbox* toolbox) final;
   //实例化不同的任务
   bool                  addTask       (Task * task);
   //执行所有任务
   Q_INVOKABLE void      runTask       ();
   //实例化日志任务
   Q_INVOKABLE void      createLogTask (QString filename , QGCLogEntry*  logEntry);
private:
   QMutex                              _mutex;
   //错误信息
   QString                             _errorMessage;
   //日志的任务队列
   QQueue<Task*>                       _taskQueue;

private slots:
   void _workerError                  (QString errorMsg);

};
#endif // NETWORKMANAGER_H

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
//��Ҫ�ع���
//������������ڹ������к�̨�������datacontroller ��̨ʵʱ����

class LogSendTask  :public QObject
{
    Q_OBJECT
public:
    LogSendTask (QString filename , QGCLogEntry*  logEntry);
    //��ȡ�ļ�����
    QString logFile         () const { return _logFile;}
    //������־
    void send               ();

protected:
    //��ʱ����
    void work                ();

signals:
    void error              (QString errorMsg);
    //���ͳɹ�����������ʾ���ͳɹ�
    void stateChanged       (QString stat);

private slots:
    bool ready ();

private:
    QMutex                  _mutex;
    QString                 _logFile;
    QFile                   _file;
    QByteArray              _md5;
    QString                 _reqPack;
    QByteArray              _filedata;
    QGCLogEntry*            _logEntry;
   /* LogDownloadData *       _logDownlogdata*/;
};

class NetWorkManager  :public QGCTool {

   Q_OBJECT
public:
   NetWorkManager                      (QGCApplication* app, QGCToolbox* toolbox);
   // QGCTool overrides
   void setToolbox                     (QGCToolbox* toolbox) final;
   //�ع�һ��
   //Q_INVOKABLE void sendBinLogFile   (QString);
   //�����̨���ݵĿ�����
   //DataController*  datacontroller()   {return _datacontroller;}
   //��������������
   bool                  addTask       (QString filename , QGCLogEntry*  logEntry);
   //ִ����������
   Q_INVOKABLE void      runTask       ();

private:
   QMutex                             _mutex;
//   DataController*                    _datacontroller;
   //������־����
   //LogSendTask                      _worker;
   //������Ϣ
   QString                            _errorMessage;
   //��־���������
   QQueue<LogSendTask*>               _taskQueue;
   //�߳�
   QThread                            _workThread;

private slots:
   //void _managerError                 (QString errorMsg);
   void _workerError                  (QString errorMsg);

};
#endif // NETWORKMANAGER_H

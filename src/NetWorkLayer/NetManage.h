#ifndef NETMANAGE_H
#define NETMANAGE_H
#include <QTcpSocket>
#include <QObject>
#include <QMap>
#include <QQueue>
#include <QMutex>
#include "NetWorkLayer/NetLayer.h"
//重构一下NetManager
//内部维护一个工作队列
class NetManage :public QObject
{
     Q_OBJECT
public:
    static NetManage * getManage();

    Q_INVOKABLE void SendLogFileEmit(QString);

private:
    NetManage();
    NetManage(const NetManage&){}
    NetManage& operator=(const NetManage&other);
    static NetManage *s_instance;
    static NetLayer *m_layer;
    static QThread WorkThread;
    //执行网络任务
    void runNetTask(QString taskName);
     QMutex locker;
    //工作队列
    static QQueue <NetLayer*> *AsynWorkTaskQueue;
    bool startflag = true;
signals:
    void SendLogFile(QString path);
    void QSendLogSuccess();
    void QSendLogFail();
private slots:
    void pushTask(NetLayer *task);

    NetLayer *popTask();

};




















#endif // NETMANAGE_H

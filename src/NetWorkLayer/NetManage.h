#ifndef NETMANAGE_H
#define NETMANAGE_H
#include <QTcpSocket>
#include <QObject>
#include <QMap>
#include "NetWorkLayer/NetLayer.h"
//重构一下NetManager
//网络管理类将任务指针放到layerList中集中管理和销毁
//后续准备计时器模块用于任务计时
//用于处理各种文件校验算法 字符串处理等
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
    //创建网络任务
    bool createNetTask(QString taskName ,NetLayer *task);
    //执行网络任务
    void runNetTask(QString taskName);
    //线程qlist表存放线程句柄记住要结束销毁
    QMap<QString ,NetLayer *> layerMap;

signals:
    void SendLogFile(QString path);
    void QSendLogSuccess();
    void QSendLogFail();
private slots:
    void taskFinised(QString taskName);


};

#endif // NETMANAGE_H

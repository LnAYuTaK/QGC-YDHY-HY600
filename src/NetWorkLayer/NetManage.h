#ifndef NETMANAGE_H
#define NETMANAGE_H
#include <QTcpSocket>
#include <QObject>
#include <QMap>
#include "NetWorkLayer/NetLayer.h"
//�ع�һ��NetManager
//��������ཫ����ָ��ŵ�layerList�м��й��������
//����׼����ʱ��ģ�����������ʱ
//���ڴ�������ļ�У���㷨 �ַ��������
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
    //������������
    bool createNetTask(QString taskName ,NetLayer *task);
    //ִ����������
    void runNetTask(QString taskName);
    //�߳�qlist�����߳̾����סҪ��������
    QMap<QString ,NetLayer *> layerMap;

signals:
    void SendLogFile(QString path);
    void QSendLogSuccess();
    void QSendLogFail();
private slots:
    void taskFinised(QString taskName);


};

#endif // NETMANAGE_H

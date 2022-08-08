#include "NetWorkLayer/NetLayer.h"


NetLayer::NetLayer(QObject *parent)
    : QObject{parent}
{

}

//日志任务执行一次发送一个文件 //发送后等待服务器回复(五秒)
void NetLayer::SendBinLogFile(QString filename)
{
    QTcpSocket *NetSocket = new QTcpSocket;
    QString IP =  "192.168.3.113";
    qint64 Port = 8900;
    NetSocket->connectToHost(IP,Port);
    NetSocket->waitForConnected(2000);
    QFile m_file;
    m_file.setFileName(filename);
    if ((NetSocket->state() != QAbstractSocket::ConnectedState) || (!m_file.open(QIODevice::ReadOnly)) ) {
         NetSocket->deleteLater();
         return;
    }
    QFileInfo fileInfo(filename);
    QString FileName = fileInfo.baseName();
    QByteArray filedata = m_file.readAll();
    QByteArray md5 = QCryptographicHash::hash(filedata, QCryptographicHash::Md5);
    QString ReqPack = "FFFF:"+md5.toHex()+':'+"Data"+':'+FileName+"\n";
    qint64 ReqPackSize = NetSocket->write(ReqPack.toLatin1());
    Q_UNUSED(ReqPackSize)
    qint64 sendsize = NetSocket->write(filedata);
    qDebug()<< sendsize;
    TaskTimeOut =new QTimer(this);
    TaskTimeOut->setTimerType(Qt::PreciseTimer);
    TaskTimeOut->start(5000);
    while (TaskTimeOut->remainingTime()>0)
    {
          if (NetSocket->waitForReadyRead(10)){
              QByteArray replymsg =NetSocket->readAll();
              qDebug() << replymsg;
              if(replymsg == "OK"){
                  qDebug()<<"SUCCESSFULE SENDLOG";
                  return;
              }
              else{
                   qDebug()<<"FAIL SENDLOG_";
                  return;
              }
           }
     }
    NetSocket->deleteLater();

}

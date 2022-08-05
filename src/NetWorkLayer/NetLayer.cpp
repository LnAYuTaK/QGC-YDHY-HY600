#include "NetWorkLayer/NetLayer.h"


NetLayer::NetLayer(QObject *parent)
    : QObject{parent}
{

}

void NetLayer::SendBinLogFile(QString filename)
{
//    QTcpSocket *NetSocket = new QTcpSocket;
//    QString IP =  "192.168.3.113";
//    qint64 Port = 8900;
//   // qDebug()<< "Send" << filename << IP << Port;
//    NetSocket->connectToHost(IP,Port);
//    NetSocket->waitForConnected(2000);
//    QFile m_file;
//    m_file.setFileName(filename);
//    if ((NetSocket->state() != QAbstractSocket::ConnectedState) || (!m_file.open(QIODevice::ReadOnly)) ) {
//         NetSocket->deleteLater();
//         return;
//    }
//    QFileInfo fileInfo(filename);
//    QString FileName = fileInfo.baseName();
//    QByteArray filedata = m_file.readAll();

//    QByteArray md5 = QCryptographicHash::hash(filedata, QCryptographicHash::Md5);
//    //?FFFF +Md5?????+ UserID + ???????   //Hex

//    QString ReqPack = "FFFF:"+md5.toHex()+':'+"Data"+':'+FileName+"\n";
//    qDebug() << ReqPack;
//    qDebug() << md5.toHex();
//    //??????????
//    qint64 ReqPackSize = NetSocket->write(ReqPack.toLatin1());
//    Q_UNUSED(ReqPackSize)
//    qint64 sendsize = NetSocket->write(filedata);
//    qDebug()<< sendsize;
//    TaskTimeOut =new QTimer(this);
//    TaskTimeOut->setTimerType(Qt::PreciseTimer);
//    TaskTimeOut->start(5000);
//      while (TaskTimeOut->remainingTime()>0)
//      {
//          if (NetSocket->waitForReadyRead(10)){
//              QByteArray replymsg =NetSocket->readAll();
//               qDebug() << replymsg;
//              if(replymsg == "OK"){
//                emit LogSendSuccess();
//                  return;
//              }
//              else{
//                 emit LogSendFail();
//                  return;
//              }
//           }
//       }
//     emit LogSendFail();
}

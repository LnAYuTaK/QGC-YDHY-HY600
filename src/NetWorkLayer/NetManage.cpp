#include "NetManage.h"

NetManage *NetManage::s_instance = nullptr;
NetLayer *NetManage::m_layer =nullptr;

QThread NetManage::WorkThread;

QQueue<NetLayer *> *NetManage::AsynWorkTaskQueue =nullptr;

NetManage::NetManage()
{

}

NetManage* NetManage::getManage()
{
  if(s_instance== nullptr)
  {
      s_instance = new NetManage();
      AsynWorkTaskQueue = new QQueue<NetLayer *>();
      AsynWorkTaskQueue->clear();
      //太繁琐后续重构
//      m_layer = new NetLayer();
//      m_layer->moveToThread(&WorkThread);
//      connect(&WorkThread,&QThread::finished,m_layer,&QObject::deleteLater);
//      connect(s_instance,SIGNAL(SendLogFile(QString)),m_layer,SLOT(SendBinLogFile(QString)));
//      connect(m_layer,SIGNAL(LogSendSuccess()),s_instance,SIGNAL(QSendLogSuccess()));
//      connect(m_layer,SIGNAL(LogSendFail()),s_instance,SIGNAL(QSendLogFail()));
//      WorkThread.start();
  }
  return s_instance;
}
//TODU
void NetManage::pushTask(NetLayer *task)
{
    if(AsynWorkTaskQueue!=nullptr)
    {
        locker.lock();
        AsynWorkTaskQueue->push_front(task);
        locker.unlock();
    }
}

NetLayer *NetManage::popTask()
{
    locker.lock();
    NetLayer *task=nullptr;
    if(AsynWorkTaskQueue->size() == 0){
        task =  nullptr;
    }
    else{
        task =AsynWorkTaskQueue->takeFirst();
    }
    locker.unlock();
    return task;
}

void NetManage::SendLogFileEmit(QString filepath)
{
    qDebug() << filepath<<"SENDBINLOG";
   // emit SendLogFile(filepath);
}















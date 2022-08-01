#include "NetManage.h"

NetManage *NetManage::s_instance = nullptr;
NetLayer *NetManage::m_layer =nullptr;

QThread NetManage::WorkThread;
NetManage::NetManage()
{

}

NetManage* NetManage::getManage()
{
  if(s_instance== nullptr){
      s_instance = new NetManage();
      //太繁琐后续重构
      m_layer = new NetLayer();
      m_layer->moveToThread(&WorkThread);
      connect(&WorkThread,&QThread::finished,m_layer,&QObject::deleteLater);
      connect(s_instance,SIGNAL(SendLogFile(QString)),m_layer,SLOT(SendBinLogFile(QString)));
      connect(m_layer,SIGNAL(LogSendSuccess()),s_instance,SIGNAL(QSendLogSuccess()));
      connect(m_layer,SIGNAL(LogSendFail()),s_instance,SIGNAL(QSendLogFail()));
      WorkThread.start();
  }
  return s_instance;
}
//TODU
bool NetManage::createNetTask(QString taskName,NetLayer *task)
{
    if(task!=nullptr||!(layerMap.contains(taskName))){
        layerMap.insert(taskName,task);
        return true;
    }
    return false;
}
//TODU
void NetManage::runNetTask(QString taskName)
{

}

void NetManage::SendLogFileEmit(QString filepath)
{
    qDebug() << filepath;
    emit SendLogFile(filepath);
}

void NetManage::taskFinised(QString taskName)
{
    if(layerMap.contains(taskName)){
        //先清理指针 再从map移除
        layerMap.value(taskName)->deleteLater();
        layerMap.remove(taskName);
    }
}














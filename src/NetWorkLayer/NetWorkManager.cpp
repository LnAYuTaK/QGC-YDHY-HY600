#include "NetWorkManager.h"
LogSendTask ::LogSendTask (QString filename)
{
       this->_logFile=filename;
}

bool LogSendTask::ready()
{
    _file.setFileName(_logFile);
    qDebug()<<_file.fileName();
    if(_file.exists())
    {
       QFileInfo fileInfo(_logFile);
       QString FileName = fileInfo.baseName();
       _mutex.lock();
       if(_file.open(QIODevice::ReadOnly))
       {
         _filedata = _file.readAll();
         _mutex.unlock();
         _reqPack = "FFFF:"+_md5.toHex()+':'+"Data"+':'+FileName+"\n";
         _md5 = QCryptographicHash::hash(_filedata, QCryptographicHash::Md5);
         return true;
       }
       return false;
    }
   emit  error("File Not Exists");
   return false;
}

void LogSendTask::work()
{
 QTcpSocket mSock;
 QString IP =  "192.168.3.113";
 qint64 Port = 8720;
 mSock.connectToHost(IP,Port);
 mSock.waitForConnected(2000);
 if ((mSock.state() != QAbstractSocket::ConnectedState)) {
      return;
 }
 //发送 请求包  和文件数据 没分包
 mSock.write(_reqPack.toLatin1());
 mSock.write(_filedata);
 if (mSock.waitForReadyRead(10)){
           QByteArray replymsg =mSock.readAll();
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

void LogSendTask ::send()
{
    if(ready())
    {
       this->work();
    }
}

NetWorkManager :: NetWorkManager(QGCApplication* app, QGCToolbox* toolbox)
 : QGCTool(app, toolbox)
{
       //connect(&_worker, &LogSendTask::error, this, &NetWorkManager::_workerError);
}

void NetWorkManager::setToolbox(QGCToolbox *toolbox)
{
    QGCTool::setToolbox(toolbox);
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
    qmlRegisterSingletonInstance<NetWorkManager>("QGroundControl.NetWorkManager", 1, 0, "NetWorkManager", qgcApp()->toolbox()->netWorkManager());
    _datacontroller =new DataController();
}

bool NetWorkManager::addTask(QString filename)
{
    LogSendTask* task = new LogSendTask(filename);
    if(task!=nullptr){
       _mutex.lock();
       _taskQueue.enqueue(task);
       _mutex.unlock();
       return true;
    }
    task->deleteLater();
    return false;
}

void NetWorkManager::_workerError(QString errorMessage)
{
    _errorMessage = errorMessage;
}

//队列执行同步任务
void NetWorkManager::runTask()
{
    qDebug() << " RUNTASK " << " Task Num "<<this->_taskQueue.size();
    LogSendTask* task = nullptr;
    forever{
        if (_taskQueue.isEmpty()) {
            // 任务队列为空，等待有任务时唤醒
           break;
        }
        // 获取一个任务
       task= _taskQueue.dequeue();
       if (task){
         task->moveToThread(&_workThread);
         task->send();
         if(task!=nullptr)
         {
             task->deleteLater();
         }
      }
   }
}

void NetWorkManager::show()
{

    qDebug()<< _taskQueue.size();

}





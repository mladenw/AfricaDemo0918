#ifndef TCMSCONTROLLER_H
#define TCMSCONTROLLER_H

#include <QWidget>

class TcmsPort;
class TcmsAfricaBuffer;
class TcmsHMIAfricaBuffer;
class TcmsAfricaTimeBuffer;

class TcmsController : public QObject
{
    Q_OBJECT
public:
    TcmsController(QObject *parent = 0);
    ~TcmsController();

    void putAfricaTimeData(quint16 portAddress, const quint16 *buf);
    void putAfricaData(quint16 portAddress, quint16 *buf );//  add AGE info  void putafricadata(add,*buf,age)
    void setAfricaBuffer(TcmsAfricaBuffer *AfricaBuffer){m_pMvbAfricaBuffer = AfricaBuffer;}
    void setHMIAfricaBuffer(TcmsHMIAfricaBuffer *HMIAfricaBuffer){m_pHMIAfricaBUffer = HMIAfricaBuffer;}
    void setAfricaTimeBuffer(TcmsAfricaTimeBuffer *AfricaTimeBuffer){m_pMvbAfricaTimeBuffer = AfricaTimeBuffer;}
    void getSrceData(quint16 portAddress, quint16 *buf);
    void setHMIAddress();

    void start();
    void stop();

private:
    bool               m_running;
    TcmsPort          *m_pPort518;
    TcmsPort          *m_pPort1F;
    TcmsPort          *m_pPort136;
    TcmsPort          *m_pPort308;
    TcmsPort          *m_pPort720;
    TcmsPort          *m_pPort710;
    TcmsPort          *m_pPort726;
    TcmsPort          *m_pPort716;
    TcmsPort          *m_pPortFD0;
    TcmsPort          *m_pPort717;
    TcmsPort          *m_pPort727;
    TcmsPort          *m_pPortFD5;
    TcmsPort          *m_pPort30A;

    TcmsAfricaBuffer      *m_pMvbAfricaBuffer;
    TcmsHMIAfricaBuffer   *m_pHMIAfricaBUffer;
    TcmsAfricaTimeBuffer  *m_pMvbAfricaTimeBuffer;
};

#endif // TCMSCONTROLLER_H

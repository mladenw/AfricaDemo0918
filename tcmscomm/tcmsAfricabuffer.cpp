#include "tcmsAfricabuffer.h"
#include <QDebug>

TcmsAfricaBuffer::TcmsAfricaBuffer(QObject *parent) :
    QObject(parent)
{
    m_updataAfricaPort717_Status_Life_TimerPtr = new QTimer(this) ;
    m_updataAfricaPort727_Status_Life_TimerPtr = new QTimer(this) ;
    m_VCUonline_TimerPtr = new QTimer(this);
    m_BCUonline_TimerPtr = new QTimer(this);

    connect(m_updataAfricaPort717_Status_Life_TimerPtr, SIGNAL(timeout()), this, SLOT(Port717_Status_Life_Timeout()));
    m_updataAfricaPort717_Status_Life_TimerPtr->setInterval(3000);

    connect(m_updataAfricaPort727_Status_Life_TimerPtr, SIGNAL(timeout()), this, SLOT(Port727_Status_Life_Timeout()));
    m_updataAfricaPort727_Status_Life_TimerPtr->setInterval(3000);

    connect(m_VCUonline_TimerPtr, SIGNAL(timeout()), this, SLOT(PortVCU_Status_Life_Timeout()));
    m_VCUonline_TimerPtr->setInterval(3000);

    connect(m_BCUonline_TimerPtr, SIGNAL(timeout()), this, SLOT(PortBCU_Status_Life_Timeout()));
    m_BCUonline_TimerPtr->setInterval(3000);

    reset();
}

void TcmsAfricaBuffer::reset()
{
    m_iLocoNumber = 0;
    m_iBP_Pressure = 0;
    m_iLocoSpeed = 0;
    m_iLocoAcc = 0;
    m_iTracEffort = 0;
    m_iNotch = 0;
    m_iMR_Pressure = 0;
    m_iER_Pressure = 0;
    m_iBC_Pressure = 0;
    m_iVoltage = 0;
    m_iCurrent = 0;
    m_iMileageFlag = 0;
    m_iMileageValue = 0;
    m_iEngineSpeed1 = 0;
    m_iEngineSpeed2 = 0;
    m_iEnginePower1 = 0;
    m_iEnginePower2 = 0;
    m_iAfricaLife = 255;
    m_iGWmaster2 = 0 ;
    m_iGWmaster1 = 0 ;
    m_iAfricaPort717_Status_Life = 255 ;
    m_iAfricaPort727_Status_Life = 255 ;
    m_bAfricaPort727_Status_Life_CommNormal = false ;
    m_bAfricaPort717_Status_Life_CommNormal = false ;
    m_bVCUOnline = false;
    m_bBCUOnline = false;
}

void TcmsAfricaBuffer::putPort518Data(const quint16 *buf)
{
    m_iPort518_buf = buf ;
    m_iNotch = m_iPort518_buf[3] & 0xff ;
}

void TcmsAfricaBuffer::putPort136Data(const quint16 *buf)
{
    m_iPort136_buf = buf ;
    m_iBP_Pressure = ((m_iPort136_buf[0] >> 8) & 0x00ff) | ((m_iPort136_buf[0] << 8) & 0xff00) ;
    m_iMR_Pressure = ((m_iPort136_buf[1] >> 8) & 0x00ff) | ((m_iPort136_buf[1] << 8) & 0xff00) ;
    m_iER_Pressure = ((m_iPort136_buf[2] >> 8) & 0x00ff) | ((m_iPort136_buf[2] << 8) & 0xff00) ;
    m_iBC_Pressure = ((m_iPort136_buf[3] >> 8) & 0x00ff) | ((m_iPort136_buf[3] << 8) & 0xff00) ;

    quint8 m_Life =( buf[11] >> 8) & 0xff;
    if(m_Life != m_iBCUtoVCU_Life)
    {
        m_iBCUtoVCU_Life = m_Life ;
        if(m_BCUonline_TimerPtr->isActive())
        {
            m_BCUonline_TimerPtr->stop();
        }
        m_bBCUOnline = true ;
    }
    else
    {
        if(!m_BCUonline_TimerPtr->isActive())
        {
            m_BCUonline_TimerPtr->start();
        }
    }
}

void TcmsAfricaBuffer::putPort308Data(const quint16 *buf)
{
    m_iPort308_buf = buf ;
    m_iLocoSpeed = ((m_iPort308_buf[8] >> 8) & 0x00ff) | ((m_iPort308_buf[8] << 8) & 0xff00) ;
    m_iVoltage   = ((m_iPort308_buf[9] >> 8) & 0x00ff) | ((m_iPort308_buf[9] << 8) & 0xff00) ;
    m_iCurrent   = ((m_iPort308_buf[10] >> 8) & 0x00ff) | ((m_iPort308_buf[10] << 8) & 0xff00) ;
    m_iTracEffort = ((m_iPort308_buf[11] >> 8) & 0x00ff) | ((m_iPort308_buf[11] << 8) & 0xff00) ;
    m_iLocoAcc = ((m_iPort308_buf[12] >> 8) & 0x00ff) | ((m_iPort308_buf[12] << 8) & 0xff00) ;
    m_iLocoMode = buf[6]&0xff;
    quint8 m_Life =buf[7] & 0xff;
    if(m_Life != m_iVCUtoALL_Life)
    {
        m_iVCUtoALL_Life = m_Life ;
        if(m_VCUonline_TimerPtr->isActive())
        {
            m_VCUonline_TimerPtr->stop();
        }
        m_bVCUOnline = true ;
    }
    else
    {
        if(!m_VCUonline_TimerPtr->isActive())
        {
            m_VCUonline_TimerPtr->start();
        }
    }
}

void TcmsAfricaBuffer::putPort720Data(const quint16 *buf)
{
    m_iPort720_buf = buf ;
    m_iEngineSpeed1 = ((static_cast<qint32>(((m_iPort720_buf[8] >> 8) & 0x00ff) | ((m_iPort720_buf[8] << 8) & 0xff00))) << 16)
            | (static_cast<qint32>(((m_iPort720_buf[9] >> 8) & 0x00ff) | ((m_iPort720_buf[9] << 8) & 0xff00)));
}

void TcmsAfricaBuffer::putPort710Data(const quint16 *buf)
{
    m_iPort710_buf = buf ;
    m_iEngineSpeed2 = ((static_cast<qint32>(((m_iPort710_buf[8] >> 8) & 0x00ff) | ((m_iPort710_buf[8] << 8) & 0xff00))) << 16)
            | (static_cast<qint32>(((m_iPort710_buf[9] >> 8) & 0x00ff) | ((m_iPort710_buf[9] << 8) & 0xff00)));
}

void TcmsAfricaBuffer::putPort726Data(const quint16 *buf)
{
    m_iPort726_buf = buf ;
    m_iEnginePower1 = ((static_cast<qint32>(((m_iPort726_buf[2] >> 8) & 0x00ff) | ((m_iPort726_buf[2] << 8) & 0xff00))) << 16)
            | (static_cast<qint32>(((m_iPort726_buf[3] >> 8) & 0x00ff) | ((m_iPort726_buf[3] << 8) & 0xff00)));
}

void TcmsAfricaBuffer::putPort716Data(const quint16 *buf)
{
    m_iPort716_buf = buf ;
    m_iEnginePower2 = ((static_cast<qint32>(((m_iPort716_buf[2] >> 8) & 0x00ff) | ((m_iPort716_buf[2] << 8) & 0xff00))) << 16)
            | (static_cast<qint32>(((m_iPort716_buf[3] >> 8) & 0x00ff) | ((m_iPort716_buf[3] << 8) & 0xff00)));
}

void TcmsAfricaBuffer::putPortFD0Data(const quint16 *buf)
{
    m_iPortFD0_buf = buf ;
    m_iAfricaLife = m_iPortFD0_buf[0] & 0xff;
}

void TcmsAfricaBuffer::putPort717Data(const quint16 *buf)
{
    quint8 m_Life = buf[0] & 0xff;
    if(m_Life != m_iAfricaPort717_Status_Life)
    {
        m_iGWmaster2 = buf[1] & 0xff ;
        m_iAfricaPort717_Status_Life = m_Life ;
        if(m_updataAfricaPort717_Status_Life_TimerPtr->isActive())
        {
            m_updataAfricaPort717_Status_Life_TimerPtr->stop();
        }
        m_bAfricaPort717_Status_Life_CommNormal = true ;
    }
    else
    {
        if(!m_updataAfricaPort717_Status_Life_TimerPtr->isActive())
        {
            m_updataAfricaPort717_Status_Life_TimerPtr->start();
        }
    }
}

void TcmsAfricaBuffer::putPort727Data(const quint16 *buf)
{
    quint8 m_Life = buf[0] & 0xff ;
    if(m_Life != m_iAfricaPort727_Status_Life)
    {
        m_iGWmaster1 = buf[1] & 0xff ;
        m_iAfricaPort727_Status_Life = m_Life ;
        if(m_updataAfricaPort727_Status_Life_TimerPtr->isActive())
        {
            m_updataAfricaPort727_Status_Life_TimerPtr->stop();
        }
        m_bAfricaPort727_Status_Life_CommNormal = true ;
    }
    else
    {
        if(!m_updataAfricaPort727_Status_Life_TimerPtr->isActive())
        {
            m_updataAfricaPort727_Status_Life_TimerPtr->start();
        }
    }

}

void TcmsAfricaBuffer::putPortFD5Data(const quint16 *buf)
{
    m_iPortFD5_buf = buf ;

    m_iMileageFlag = ((m_iPortFD5_buf[0] >> 8) & 0x00ff) | ((m_iPortFD5_buf[0] << 8) & 0xff00) ;
    m_iMileageValue = ((static_cast<quint32>(((m_iPortFD5_buf[1] >> 8) & 0x00ff) | ((m_iPortFD5_buf[1] << 8) & 0xff00))) << 16)
            | (static_cast<quint32>(((m_iPortFD5_buf[2] >> 8) & 0x00ff) | ((m_iPortFD5_buf[2] << 8) & 0xff00)));
}
void TcmsAfricaBuffer::putPort30AData(const quint16 *buf)
{
    m_iPort30A_buf = buf ;
    m_iLocoNumber = ((m_iPort30A_buf[11] >> 8) & 0x00ff) | ((m_iPort30A_buf[11] << 8) & 0xff00) ;
}
quint16 TcmsAfricaBuffer::getLocoNumber()
{
    return m_iLocoNumber ;
}

qint16 TcmsAfricaBuffer::getBP_Pressure()
{
    return m_iBP_Pressure ;
}

quint16 TcmsAfricaBuffer::getLocoSpeed()
{
    return m_iLocoSpeed ;
}

qint16 TcmsAfricaBuffer::getLocoAcc()
{
    return m_iLocoAcc ;
}

qint16 TcmsAfricaBuffer::getTracEffort()
{
    return m_iTracEffort ;
}

quint8 TcmsAfricaBuffer::getNotch()
{
    return m_iNotch ;
}

qint16 TcmsAfricaBuffer::getMR_Pressure()
{
    return m_iMR_Pressure ;
}

qint16 TcmsAfricaBuffer::getER_Pressure()
{
    return m_iER_Pressure ;
}

qint16 TcmsAfricaBuffer::getBC_Pressure()
{
    return m_iBC_Pressure ;
}

quint16 TcmsAfricaBuffer::getVoltage()
{
    return m_iVoltage ;
}

quint16 TcmsAfricaBuffer::getCurrent()
{
    return m_iCurrent ;
}

qint32 TcmsAfricaBuffer::getEngineSpeed1()
{
    return m_iEngineSpeed1 ;
}

qint32 TcmsAfricaBuffer::getEngineSpeed2()
{
    return m_iEngineSpeed2 ;
}

qint32 TcmsAfricaBuffer::getEnginePower1()
{
    return m_iEnginePower1 ;
}

qint32 TcmsAfricaBuffer::getEnginePower2()
{
    return m_iEnginePower2 ;
}

quint16 TcmsAfricaBuffer::getMileageFlag()
{
    return m_iMileageFlag ;
}

quint32 TcmsAfricaBuffer::getMileageValue()
{
    return m_iMileageValue ;
}

quint8  TcmsAfricaBuffer::getAfricaLife()
{
    return m_iAfricaLife ;
}

quint8 TcmsAfricaBuffer::getm_iGWmaster2()
{
    return m_iGWmaster2 ;
}

quint8 TcmsAfricaBuffer::getm_iGWmaster1()
{
    return m_iGWmaster1 ;
}

bool TcmsAfricaBuffer::getAfricaPort717_Status_Life()
{
    return m_bAfricaPort717_Status_Life_CommNormal ;
}

bool TcmsAfricaBuffer::getAfricaPort727_Status_Life()
{
    return m_bAfricaPort727_Status_Life_CommNormal ;
}
bool TcmsAfricaBuffer::getBCU_Status_Life()
{
    return m_bBCUOnline ;
}
bool TcmsAfricaBuffer::getVCU_Status_Life()
{
    return m_bVCUOnline ;
}
quint8 TcmsAfricaBuffer::getLocoMode()
{
    return m_iLocoMode;
}

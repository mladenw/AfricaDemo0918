#include "tcmsport.h"
#include <tcmscomm/mvb.h>
#include <tcmscomm/tcmscontroller.h>

TcmsPort::TcmsPort(TcmsController *controller, quint16 address, bool isSrce, quint8 size, quint16 period, PortSort iPort) :
    QObject(controller),
    m_controller(controller),
    m_timer(new QTimer(this)),
    m_address(address),
    m_isSrce(isSrce),
    m_size(size),
    m_period(period),
    m_iPort(iPort)
{
    connect(m_timer, SIGNAL(timeout()), this, SLOT(run()));
}

TcmsPort::~TcmsPort()
{
    delete m_timer;
}

quint16 TcmsPort::address() const
{
    return m_address;
}

void TcmsPort::setAddress(quint16 address)
{
    m_address = address;
}

bool TcmsPort::isSrce() const
{
    return m_isSrce;
}

void TcmsPort::setSrce(bool isSrce)
{
    m_isSrce = isSrce;
}

quint8 TcmsPort::size() const
{
    return m_size;
}

void TcmsPort::setSize(quint8 size)
{
    m_size = size;
}

quint16 TcmsPort::period() const
{
    return m_period;
}

void TcmsPort::setPeriod(quint16 period)
{
    m_period = period;
}

void TcmsPort::open()
{
    m_timer->start(m_period);
}

void TcmsPort::close()
{
    m_timer->stop();
}

void TcmsPort::run()
{
    if(m_isSrce)
    {
        m_controller->getSrceData(m_address, &m_ibuf[1]);
        ::MVBCPutPort(m_address, m_ibuf, 0);
    }else{
        quint16 age;
        if (::MVBCGetPort(m_address, m_ibuf, 0, &age, 0) != MVB_NO_ERROR)
            return;
        m_age = age;
        switch(m_iPort){
        case AfricaTimePort:
            m_controller->putAfricaTimeData(m_address, &m_ibuf[1]);break;
        case AfricaPort:
            m_controller->putAfricaData(m_address, &m_ibuf[1]);break;
        default:
            break;
        }
    }
}

#include "tcmsAfricaTimebuffer.h"
#include <iostream>
#include <QDebug>

TcmsAfricaTimeBuffer::TcmsAfricaTimeBuffer(QObject *parent):
    QObject(parent)
{
    reset();
    init();
}

void TcmsAfricaTimeBuffer::reset()
{
    m_africaDate.setYMD(0, 0, 0);
    m_africaTime.setHMS(0, 0, 0);
}

void TcmsAfricaTimeBuffer::init()
{

}

QDate TcmsAfricaTimeBuffer::getDate()
{
    return m_africaDate;
}

QTime TcmsAfricaTimeBuffer::getTime()
{
    return m_africaTime;
}

void TcmsAfricaTimeBuffer::putAfricaTime(const quint16 *buf)
{
//    quint16 year   = static_cast<unsigned int>(((buf[2]&0x000f)) + (((buf[2] >> 4) &0x000f)*10)&0xff) + static_cast<unsigned int>(2000);
//    quint8 month   = static_cast<unsigned int>(((buf[2] >> 8)&0x000f) + (((buf[2] >> 12)&0x000f)*10)&0xff);
//    quint8 day     = static_cast<unsigned int>(((buf[3])&0x000f) + (((buf[3] >> 4)&0x000f)*10)&0xff);
//    quint8 hour    = static_cast<unsigned int>(((buf[3] >> 8)&0x000f) + (((buf[3] >> 12)&0x000f)*10)&0xff);
//    quint8 minute  = static_cast<unsigned int>(((buf[4])&0x000f) + (((buf[4] >> 4)&0x000f)*10)&0xff);
//    quint8 second  = static_cast<unsigned int>(((buf[4] >> 8)&0x000f) + (((buf[4] >> 12)&0x000f)*10)&0xff);

//    m_africaDate.setYMD(year, month, day);
//    m_africaTime.setHMS(hour, minute, second);
    //printf("日期： %d-%d-%d\n", year, month, day);
    //printf("时间： %d-%d-%d\n", hour, minute, second);

   m_tAfricaTimeContent = ((static_cast<quint32>(((buf[2] >> 8) & 0x00ff) | ((buf[2] << 8) & 0xff00))) << 16)
            | (static_cast<quint32>(((buf[3] >> 8) & 0x00ff) | ((buf[3] << 8) & 0xff00)));

    return;
}

quint32 TcmsAfricaTimeBuffer::getAfricaTimeContent()
{
    return m_tAfricaTimeContent ;
}

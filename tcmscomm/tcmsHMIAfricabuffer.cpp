#include "tcmsHMIAfricabuffer.h"

TcmsHMIAfricaBuffer::TcmsHMIAfricaBuffer(QObject *parent) : QObject(parent)
{
    m_iHMI_Content_Life = 255 ;
}

void TcmsHMIAfricaBuffer::getHMI_Content(quint16 *buf)
{
    m_iHMI_Content_Life += 1 ;
    buf[0] = (static_cast<quint16>(m_iHMI_Content_Life) & 0x00ff) |
            ((static_cast<quint16>(12) << 8) & 0xff00);
}


#ifndef TCMSHMIAFRICABUFFER_H
#define TCMSHMIAFRICABUFFER_H

#include <QObject>

class TcmsHMIAfricaBuffer : public QObject
{
    Q_OBJECT
public:
    explicit TcmsHMIAfricaBuffer(QObject *parent = 0);

    void getHMI_Content(quint16 *buf); //Port FD0H

private:
    quint8 m_iHMI_Content_Life ;
};

#endif // TCMSHMIAFRICABUFFER_H

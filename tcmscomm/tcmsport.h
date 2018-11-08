#ifndef TCMSPORT_H
#define TCMSPORT_H

#include <QObject>
#include <QTimer>
class TcmsController;

enum PortSort{
    AfricaTimePort = 0,
    AfricaPort,
    AfricaHMIPort
};

class TcmsPort : public QObject
{
    Q_OBJECT
public:
    TcmsPort(TcmsController *controller, quint16 address, bool isSrce, quint8 size, quint16 period, PortSort iPort);
    ~TcmsPort();

    bool isSrce() const;
    void setSrce(bool isSrce);

    quint16 address() const;
    void setAddress(quint16 address);

    quint8 size() const;
    void setSize(quint8 size);

    quint16 period() const;
    void setPeriod(quint16 period);

    void open();
    void close();

    int m_age;

public slots:
    void run();

private:

    quint16         m_ibuf[32];
    TcmsController *m_controller;
    QTimer         *m_timer;
    quint16         m_address;
    bool            m_isSrce;
    quint8          m_size;
    quint16         m_period;
    int             m_iPort;

};

#endif // TCMSPORT_H

#ifndef TCMSAFRICATIMEBUFFER_H
#define TCMSAFRICATIMEBUFFER_H

#include <QObject>
#include <QTime>
#include <QDate>

class TcmsAfricaTimeBuffer : public QObject
{
    Q_OBJECT
public:
    TcmsAfricaTimeBuffer(QObject *parent = 0);

    void putAfricaTime(const quint16 *buf);
    QTime getTime(void);
    QDate getDate(void);

    void reset();
    void init();
    quint32 getAfricaTimeContent();

signals:

private:
    QTime     m_africaTime;
    QDate     m_africaDate;

    quint32   m_tAfricaTimeContent;

};

#endif // TCMSAFRICATIMEBUFFER_H

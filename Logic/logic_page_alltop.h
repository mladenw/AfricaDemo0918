#ifndef LOGIC_PAGE_ALLTOP_H
#define LOGIC_PAGE_ALLTOP_H

#include "tcmscomm/tcmsAfricabuffer.h"
#include "tcmscomm/tcmsAfricaTimebuffer.h"

#include <QObject>
#include <QTime>

struct PAGE_AllTop
{
    //日期信息
    QString   CurrentTime;
    QString   CurrentDate;
    QString   AfricaLocoSpeed;
    QString   AfricaLocoNumber;
};

class Logic_Page_AllTop : public QObject
{
    Q_OBJECT
public:
    explicit Logic_Page_AllTop(QObject *parent = 0);

    PAGE_AllTop   get_PAGE_AllTop_Data();

    void setAfricaBuffer(TcmsAfricaBuffer *AfricaBuffer){m_pMvbAfricaBuffer = AfricaBuffer;}
    void setAfricaTimeBuffer(TcmsAfricaTimeBuffer *AfricaTimeBuffer){m_pMvbAfricaTimeBuffer = AfricaTimeBuffer;}
    void init();

protected:
        //获取日期
        QString       setPAGE_AllTop_Date();
        //获取时间
        QString       setPAGE_AllTop_Time();
        QString       setPAGE_AllTop_Speed();
        //设置LocoNumber
        QString       setPAGE_AllTop_LocoNumber();
        //Set Data
        void          fill_PAGE_AllTop_Data();

private:
        PAGE_AllTop   m_PAGE_AllTop_Data;

        TcmsAfricaBuffer  *m_pMvbAfricaBuffer;
        TcmsAfricaTimeBuffer *m_pMvbAfricaTimeBuffer;
};

#endif // LOGIC_PAGE_ALLTOP_H

#include "logic_page_alltop.h"
#include <QDebug>

Logic_Page_AllTop::Logic_Page_AllTop(QObject *parent) :
    QObject(parent)
{
    init();
}

void Logic_Page_AllTop::init()
{
    m_PAGE_AllTop_Data.CurrentTime = "";
    m_PAGE_AllTop_Data.CurrentDate = "";
    m_PAGE_AllTop_Data.AfricaLocoSpeed = "";
    m_PAGE_AllTop_Data.AfricaLocoNumber = "" ;
}

QString Logic_Page_AllTop::setPAGE_AllTop_Date()
{
    QString strResult = "";
    QDate m_Temp = m_pMvbAfricaTimeBuffer->getDate();
    bool m_bAllCuuTimeDataValid = false;
    if(m_Temp.year() > 0 && m_Temp.year() < 2100 && m_Temp.month() > 0 && m_Temp.month() < 13 && m_Temp.day() > 0 && m_Temp.day() < 32)
    {
        m_bAllCuuTimeDataValid = true;
    }else{
        m_bAllCuuTimeDataValid = false;
    }
    if(m_bAllCuuTimeDataValid){
        strResult = QString("%1-%2-%3").arg(m_Temp.year()).arg(m_Temp.month()).arg(m_Temp.day());
    }
    return strResult;
}

QString Logic_Page_AllTop::setPAGE_AllTop_Time()
{
    QString strResult   =   "";
    QTime m_Temp = m_pMvbAfricaTimeBuffer->getTime();
    bool m_bAllCuuTimeDataValid = false;
    if((0 <= m_Temp.hour() < 24) & (0 <= m_Temp.minute() < 60) & (0 <= m_Temp.second() < 60))
    {
        m_bAllCuuTimeDataValid = true;
    }else{
        m_bAllCuuTimeDataValid = false;
    }
    if(m_Temp.hour() ==0 && m_Temp.minute() == 0 && m_Temp.second() == 0)
        m_bAllCuuTimeDataValid = false;
    if(m_bAllCuuTimeDataValid){
        strResult = QString("%1:%2:%3").arg(m_Temp.hour()).arg(m_Temp.minute()).arg(m_Temp.second());
    }

    return strResult;
}

QString Logic_Page_AllTop::setPAGE_AllTop_Speed()
{
    QString strResult = "";
    if(m_pMvbAfricaBuffer->getAfricaLife())
    {
        strResult = QString("%1").arg(static_cast<float>(m_pMvbAfricaBuffer->getLocoSpeed())/100,0,'f',2);
    }
    return strResult;
}

QString Logic_Page_AllTop::setPAGE_AllTop_LocoNumber()
{
    QString strResult = "";

    if((m_pMvbAfricaBuffer->getLocoNumber() > 0) && (m_pMvbAfricaBuffer->getLocoNumber() < 10))
    {
        strResult = QString("%1%2%3").arg(0).arg(0).arg(m_pMvbAfricaBuffer->getLocoNumber());
        return strResult;
    }
    else if((m_pMvbAfricaBuffer->getLocoNumber() >= 10) && (m_pMvbAfricaBuffer->getLocoNumber() < 100))
    {
        strResult = QString("%1%2").arg(0).arg(m_pMvbAfricaBuffer->getLocoNumber());
        return strResult;
    }
    else if((m_pMvbAfricaBuffer->getLocoNumber() >= 100) && (m_pMvbAfricaBuffer->getLocoNumber() < 999))
    {
        strResult = QString("%1").arg(m_pMvbAfricaBuffer->getLocoNumber());
        return strResult;
    }
    else if(m_pMvbAfricaBuffer->getLocoNumber() >= 1000){
        strResult = QString("%1").arg("000");
        return strResult;
    }else if(m_pMvbAfricaBuffer->getLocoNumber() == 0){
        strResult = QString("%1").arg("000");
        return strResult;
    }
    return strResult ;
    //return QString::number(m_pMvbAfricaBuffer->getPort518age());
}

void Logic_Page_AllTop::fill_PAGE_AllTop_Data()
{
    m_PAGE_AllTop_Data.AfricaLocoSpeed = setPAGE_AllTop_Speed();
    m_PAGE_AllTop_Data.AfricaLocoNumber = setPAGE_AllTop_LocoNumber();
}

PAGE_AllTop Logic_Page_AllTop::get_PAGE_AllTop_Data()
{
    fill_PAGE_AllTop_Data();
    return m_PAGE_AllTop_Data;
}

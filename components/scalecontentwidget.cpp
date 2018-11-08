#include "scalecontentwidget.h"
#include <QDebug>

ScaleContentWidget::ScaleContentWidget(QWidget *parent, const char *pszNamePtr, int iWidth, int iHeight, int iPosX, int iPosY):
    CXAbstractWidget(parent, pszNamePtr, iWidth, iHeight, iPosX, iPosY)
{
    m_pPainter = new QPainter();
    init();
}

ScaleContentWidget::~ScaleContentWidget(){
    delete m_pFont1;
    delete m_pPainter;
    delete m_theBGPixmapPtr;
}

void ScaleContentWidget::init()
{
    QPalette aQPalette = this->palette();
    aQPalette.setColorGroup(QPalette::Active,
                                QColor(255,255,255),           //const QBush & windowText
                                aQPalette.button(),
                                QColor(255,255,255),           //const QBush & light
                                aQPalette.dark(),
                                aQPalette.mid(),
                                aQPalette.text(),
                                aQPalette.brightText(),
                                aQPalette.base(),
                                QColor(0,0,0));                //const QBush & window
    aQPalette.setColorGroup(QPalette::Inactive,
                                QColor(255,255,255),           //const QBush & windowText
                                aQPalette.button(),
                                QColor(255,255,255),           //const QBush & light
                                aQPalette.dark(),
                                aQPalette.mid(),
                                aQPalette.text(),
                                aQPalette.brightText(),
                                aQPalette.base(),
                                QColor(0,0,0));                //const QBush & window
    this->setPalette(aQPalette);
    m_isBackgroundSet = false;
    m_bShallUpdate = true;

    setAutoFillBackground(false);
    setAttribute(Qt::WA_OpaquePaintEvent, true);         //Widget paints all its pixels when it receives a paint event

    m_iValue = 0;
    m_iMileageValueFlag = 0 ;
    m_ScalerFrame = QRect(0,0,0,0);
    m_IndicatorFrame = QRect(0,0,0,0);
    m_ScalerDraw = QRect(12,140,27,0);
    m_Pen.setStyle(Qt::SolidLine);
    m_Pen.setColor(QColor(255,255,255));
    m_Pen.setWidth(2);

    m_pFont1 = new QFont("Arial", 14, QFont::Normal, false);
    m_pFont2 = new QFont("Arial", 18, QFont::Normal, false);

    renderBackground();

}

void ScaleContentWidget::renderBackground()
{
    m_theBGPixmapPtr = new QPixmap(this->width(), this->height());

    m_pPainter->begin(m_theBGPixmapPtr);
    m_pPainter->fillRect(m_theBGPixmapPtr->rect(),this->palette().color(QPalette::Window));
    m_pPainter->setPen(m_Pen);
    m_pPainter->setFont(*m_pFont1);
    m_FillBrush.setColor(Qt::black);
    m_FillBrush.setStyle(Qt::SolidPattern);
    m_pPainter->fillRect(15,3,70,40,m_FillBrush);
    m_pPainter->fillRect(88,3,60,40,m_FillBrush);

    m_pPainter->fillRect(15,46,70,40,m_FillBrush);
    m_pPainter->fillRect(88,46,60,40,m_FillBrush);

    m_pPainter->fillRect(15,89,70,40,m_FillBrush);
    m_pPainter->fillRect(88,89,60,40,m_FillBrush);

    m_pPainter->fillRect(15,132,70,40,m_FillBrush);
    m_pPainter->fillRect(88,132,60,40,m_FillBrush);

    m_pPainter->fillRect(15,175,70,40,m_FillBrush);
    m_pPainter->fillRect(88,175,60,40,m_FillBrush);

    m_pPainter->fillRect(15,218,70,40,m_FillBrush);
    m_pPainter->fillRect(88,218,60,40,m_FillBrush);

    m_pPainter->fillRect(15,261,70,40,m_FillBrush);
    m_pPainter->fillRect(88,261,60,40,m_FillBrush);

    m_pPainter->fillRect(15,304,70,40,m_FillBrush);
    m_pPainter->fillRect(88,304,60,40,m_FillBrush);

    m_pPainter->drawText(8,5,75,30,Qt::AlignHCenter|Qt::AlignTop,"Engine");
    m_pPainter->drawText(6,16,75,30,Qt::AlignCenter,"Power(kW)");
    m_pPainter->drawText(8,48,75,30,Qt::AlignHCenter|Qt::AlignTop,"Acc");
    m_pPainter->drawText(5,59,85,30,Qt::AlignCenter,"(km/h/min)");

    m_pPainter->drawText(6,89,75,40,Qt::AlignCenter,"BP(kPa)");
    m_pPainter->drawText(6,132,75,40,Qt::AlignCenter,"BC(kPa)");
    m_pPainter->drawText(6,175,75,40,Qt::AlignCenter,"ER(kPa)");
    m_pPainter->drawText(6,218,75,40,Qt::AlignCenter,"MR(kPa)");
    m_pPainter->drawText(6,248,75,40,Qt::AlignCenter,"Engine");
    m_pPainter->drawText(1,268,90,30,Qt::AlignCenter,"Speed(rpm)");
   // m_pPainter->drawText(6,295,75,40,Qt::AlignCenter,"Mileage");
   // m_pPainter->drawText(6,310,75,40,Qt::AlignCenter,"(km)");

    m_pPainter->end();
}

void ScaleContentWidget::paintEvent(QPaintEvent *event)
{
    if(event->rect() == this->rect())
    {
        m_isBackgroundSet = false;
    }

    m_pPainter->begin(this);
    m_pPainter->setFont(*m_pFont2);
    if(!m_isBackgroundSet){
        m_pPainter->drawPixmap(0,0,*m_theBGPixmapPtr);
        m_isBackgroundSet = true;
    }

    if(m_bShallUpdate)
    {
        if(m_pMvbAfricaBuffer->getAfricaPort727_Status_Life() && m_pMvbAfricaBuffer->getm_iGWmaster1()){
            m_pPainter->drawText(94,10,60,30,Qt::AlignCenter,QString("%1").arg(m_pMvbAfricaBuffer->getEnginePower1()*0.001,0,'f',1));
            m_pPainter->drawText(82+10,260,60,40,Qt::AlignCenter,QString("%1").arg(m_pMvbAfricaBuffer->getEngineSpeed1()*0.1,0,'f',1));
        }else if(m_pMvbAfricaBuffer->getAfricaPort717_Status_Life() && m_pMvbAfricaBuffer->getm_iGWmaster2()){
            m_pPainter->drawText(84+10,10,60,30,Qt::AlignCenter,QString("%1").arg(m_pMvbAfricaBuffer->getEnginePower2()*0.001,0,'f',1));
            m_pPainter->drawText(82+10,260,60,40,Qt::AlignCenter,QString("%1").arg(m_pMvbAfricaBuffer->getEngineSpeed2()*0.1,0,'f',1));
        }else{
            m_pPainter->drawText(84+10,10,60,30,Qt::AlignCenter,QString("%1").arg("***"));
            m_pPainter->drawText(82+10,260,60,40,Qt::AlignCenter,QString("%1").arg("***"));
        }

        // VCU port
        if(m_pMvbAfricaBuffer->getVCU_Status_Life())
        {
            m_pPainter->drawText(84+10,52,60,30,Qt::AlignCenter,QString("%1").arg(static_cast<float>(m_pMvbAfricaBuffer->getLocoAcc()),0,'f',1));// x10
            /*if(m_pMvbAfricaBuffer->getMileageFlag() == 4){
                m_pPainter->drawText(84,310,60,30,Qt::AlignCenter,QString("%1").arg(m_pMvbAfricaBuffer->getMileageValue()*0.01,0,'f',2));
                 m_iMileageValueFlag = m_pMvbAfricaBuffer->getMileageValue();
            }else{
                m_pPainter->drawText(84,310,60,30,Qt::AlignCenter,QString("%1").arg(m_iMileageValueFlag*0.01,0,'f',2));
            }*/
            if(m_pMvbAfricaBuffer->getMileageFlag() == 4)
            {
                m_iMileageValueFlag = m_pMvbAfricaBuffer->getMileageValue();
            }
            //m_pPainter->drawText(84,310,60,30,Qt::AlignCenter,QString("%1").arg(m_iMileageValueFlag*0.01));

        }else
        {
            m_pPainter->drawText(84+10,52,60,30,Qt::AlignCenter,QString("%1").arg("***"));// x10
            //m_pPainter->drawText(84,310,60,30,Qt::AlignCenter,QString("%1").arg("***"));
        }

        //BCU port
        if(m_pMvbAfricaBuffer->getBCU_Status_Life())
        {
            m_pPainter->drawText(84+10,93,60,30,Qt::AlignCenter,QString("%1").arg(static_cast<float>(m_pMvbAfricaBuffer->getBP_Pressure())*0.0625,0,'f',1));
            m_pPainter->drawText(84+10,136,60,30,Qt::AlignCenter,QString("%1").arg(static_cast<float>(m_pMvbAfricaBuffer->getBC_Pressure())*0.0625,0,'f',1));
            m_pPainter->drawText(84+10,179,60,30,Qt::AlignCenter,QString("%1").arg(static_cast<float>(m_pMvbAfricaBuffer->getER_Pressure())*0.0625,0,'f',1));
            m_pPainter->drawText(84+10,222,60,30,Qt::AlignCenter,QString("%1").arg(static_cast<float>(m_pMvbAfricaBuffer->getMR_Pressure())*0.0625,0,'f',1));
        }else
        {
            m_pPainter->drawText(84+10,93,60,30,Qt::AlignCenter,QString("%1").arg("***"));
            m_pPainter->drawText(84+10,136,60,30,Qt::AlignCenter,QString("%1").arg("***"));
            m_pPainter->drawText(84+10,179,60,30,Qt::AlignCenter,QString("%1").arg("***"));
            m_pPainter->drawText(84+10,222,60,30,Qt::AlignCenter,QString("%1").arg("***"));
        }

    }
    m_bShallUpdate = false;
    m_pPainter->end();
}

void ScaleContentWidget::setShallUpdate()
{
    m_bShallUpdate = true;
    this->update();
}

void ScaleContentWidget::setAfricaBuffer(TcmsAfricaBuffer *AfricaBuffer)
{
    m_pMvbAfricaBuffer = AfricaBuffer ;
}

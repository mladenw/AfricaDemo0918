#include "notchbarwidget.h"
#include <QDebug>

NotchBarWidget::NotchBarWidget(QWidget *parent, const char *pszNamePtr, int iWidth, int iHeight, int iPosX, int iPosY, const QString strLabel):
    CXAbstractWidget(parent, pszNamePtr, iWidth, iHeight, iPosX, iPosY)
{
    m_pPainter = new QPainter();

    m_iStartX = iPosX;
    m_iStartY = iPosY;
    m_iWidth = iWidth;
    m_iHeight = iHeight;
    m_strLabel = strLabel;

    init();
}

NotchBarWidget::~NotchBarWidget(){
    delete m_pFont1;
    delete m_pFont2;
    delete m_pFont3;
    delete m_pPainter;
    delete m_theBGPixmapPtr;
}

void NotchBarWidget::init()
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

    m_iValue = 100;
    m_ScalerFrame = QRect(0,0,0,0);
    m_IndicatorFrame = QRect(0,0,0,0);
    m_ScalerDraw = QRect(12,140,27,0);
    m_Pen.setStyle(Qt::SolidLine);
    m_Pen.setColor(QColor(255,255,255));
    m_Pen.setWidth(1);
    m_pFont1 = new QFont("Arial", 8, QFont::Normal, false);
    m_pFont2 = new QFont("Arial", 10, QFont::Normal, false);
    m_pFont3 = new QFont("Arial", 16, QFont::Normal, false);
    m_FillBrush.setColor(QColor(46,117,181));
    m_FillBrush.setStyle(Qt::SolidPattern);

    m_GreenBrush.setColor(QColor(5,194,34));
    m_GreenBrush.setStyle(Qt::SolidPattern);

    renderBackground();

}

void NotchBarWidget::renderBackground()
{
    m_theBGPixmapPtr = new QPixmap(this->width(), this->height());

    m_pPainter->begin(m_theBGPixmapPtr);
    m_pPainter->fillRect(m_theBGPixmapPtr->rect(),this->palette().color(QPalette::Window));
    m_pPainter->setPen(m_Pen);
    m_pPainter->setFont(*m_pFont2);
    m_pPainter->drawText(9,0,80,20, (Qt::AlignVCenter|Qt::AlignLeft),m_strLabel);
    m_pPainter->drawLine(40,20,48,20);

    m_ScalerFrame = QRect(10,20,30,360);
    m_pPainter->drawRect(m_ScalerFrame); //主体竖着的矩形

    float fInterval = 22.5;
    for(int i = 1;i<17;i++)
    {
        QPointF p1(40,20+i*fInterval);
        QPointF p2(48,20+i*fInterval);
        m_pPainter->drawLine(p1,p2);
    }
    m_pPainter->drawLine(40,200,58,200);

    m_pPainter->end();
}

void NotchBarWidget::paintEvent(QPaintEvent *event)
{
    if(event->rect() == this->rect())
    {
        m_isBackgroundSet = false;
    }

    m_pPainter->begin(this);
    if(!m_isBackgroundSet){
        m_pPainter->drawPixmap(0,0,*m_theBGPixmapPtr);
        m_isBackgroundSet = true;
    }
    if(m_bShallUpdate){
        if(m_iValue == 101){
            m_ScalerDraw = QRectF(11,177.5,29,22.5); // N1
            m_pPainter->fillRect(m_ScalerDraw,m_GreenBrush);
            m_pPainter->drawText(11,384,30,20,Qt::AlignCenter,QString("N%1").arg("1"));
        }else if(m_iValue == 102){
            m_ScalerDraw = QRectF(11,155,29,45);     // N2
            m_pPainter->fillRect(m_ScalerDraw,m_GreenBrush);
            m_pPainter->drawText(11,384,30,20,Qt::AlignCenter,QString("N%1").arg("2"));
        }else if(m_iValue == 103){
            m_ScalerDraw = QRectF(11,132.5,29,67.5); // N3
            m_pPainter->fillRect(m_ScalerDraw,m_GreenBrush);
            m_pPainter->drawText(11,384,30,20,Qt::AlignCenter,QString("N%1").arg("3"));
        }else if(m_iValue == 104){
            m_ScalerDraw = QRectF(11,110,29,90);     // N4
            m_pPainter->fillRect(m_ScalerDraw,m_GreenBrush);
            m_pPainter->drawText(11,384,30,20,Qt::AlignCenter,QString("N%1").arg("4"));
        }else if(m_iValue == 105){
            m_ScalerDraw = QRectF(11,87.5,29,112.5); // N5
            m_pPainter->fillRect(m_ScalerDraw,m_GreenBrush);
            m_pPainter->drawText(11,384,30,20,Qt::AlignCenter,QString("N%1").arg("5"));
        }else if(m_iValue == 106){
            m_ScalerDraw = QRectF(11,65,29,135);    // N6
            m_pPainter->fillRect(m_ScalerDraw,m_GreenBrush);
            m_pPainter->drawText(11,384,30,20,Qt::AlignCenter,QString("N%1").arg("6"));
        }else if(m_iValue == 107){
            m_ScalerDraw = QRectF(11,42.5,29,157.5); // N7
            m_pPainter->fillRect(m_ScalerDraw,m_GreenBrush);
            m_pPainter->drawText(11,384,30,20,Qt::AlignCenter,QString("N%1").arg("7"));
        }else if(m_iValue == 108){
            m_ScalerDraw = QRectF(11,21,29,180);     // N8
            m_pPainter->fillRect(m_ScalerDraw,m_GreenBrush);
            m_pPainter->drawText(11,384,30,20,Qt::AlignCenter,QString("N%1").arg("8"));
        }else if(m_iValue == 92){
            m_ScalerDraw = QRectF(11,200,29,180);   // B8
            m_pPainter->fillRect(m_ScalerDraw,m_FillBrush);
            m_pPainter->drawText(11,384,30,20,Qt::AlignCenter,QString("B%1").arg("8"));
        }else if(m_iValue == 93){
            m_ScalerDraw = QRectF(11,200,29,157.5);  // B7
            m_pPainter->fillRect(m_ScalerDraw,m_FillBrush);
            m_pPainter->drawText(11,384,30,20,Qt::AlignCenter,QString("B%1").arg("7"));
        }else if(m_iValue == 94){
            m_ScalerDraw = QRectF(11,200,29,135);   // B6
            m_pPainter->fillRect(m_ScalerDraw,m_FillBrush);
            m_pPainter->drawText(11,384,30,20,Qt::AlignCenter,QString("B%1").arg("6"));
        }else if(m_iValue == 95){
            m_ScalerDraw = QRectF(11,200,29,112.5);     // B5
            m_pPainter->fillRect(m_ScalerDraw,m_FillBrush);
            m_pPainter->drawText(11,384,30,20,Qt::AlignCenter,QString("B%1").arg("5"));
        }else if(m_iValue == 96){
            m_ScalerDraw = QRectF(11,200,29,90);  // B4
            m_pPainter->fillRect(m_ScalerDraw,m_FillBrush);
            m_pPainter->drawText(11,384,30,20,Qt::AlignCenter,QString("B%1").arg("4"));
        }else if(m_iValue == 97){
            m_ScalerDraw = QRectF(11,200,29,67.5);    // B3
            m_pPainter->fillRect(m_ScalerDraw,m_FillBrush);
            m_pPainter->drawText(11,384,30,20,Qt::AlignCenter,QString("B%1").arg("3"));
        }else if(m_iValue == 98){
            m_ScalerDraw = QRectF(11,200,29,45);  // B2
            m_pPainter->fillRect(m_ScalerDraw,m_FillBrush);
            m_pPainter->drawText(11,384,30,20,Qt::AlignCenter,QString("B%1").arg("2"));
        }else if(m_iValue == 99){
             m_ScalerDraw = QRectF(11,200,29,22.5);  // B1
             m_pPainter->fillRect(m_ScalerDraw,m_FillBrush);
             m_pPainter->drawText(11,384,30,20,Qt::AlignCenter,QString("B%1").arg("1"));
        }else if(m_iValue == 100){
             m_pPainter->drawText(11,384,30,20,Qt::AlignCenter,QString("%1").arg("idle"));
        }


    }
    m_bShallUpdate = false;
    m_pPainter->end();
}

bool NotchBarWidget::votedUpdate()
{
    m_bShallUpdate = true;
    this->update();

    return m_bShallUpdate;
}

void NotchBarWidget::setValue(int value)
{
    if((value >= 80) && (value <= 120)){
        m_iValue = value;
    }
    this->update();
}

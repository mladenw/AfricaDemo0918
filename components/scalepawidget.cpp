#include "scalepawidget.h"
#include <QDebug>

ScalePAWidget::ScalePAWidget(QWidget *parent, const char *pszNamePtr, int iWidth, int iHeight, int iPosX, int iPosY, const QString strLabel):
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

ScalePAWidget::~ScalePAWidget(){
    delete m_pFont1;
    delete m_pFont2;
    delete m_pPainter;
    delete m_theBGPixmapPtr;
}

void ScalePAWidget::init()
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
    m_ScalerFrame = QRect(0,0,0,0);
    m_IndicatorFrame = QRect(0,0,0,0);
    m_ScalerDraw = QRect(12,140,27,0);
    m_Pen.setStyle(Qt::SolidLine);
    m_Pen.setColor(QColor(255,255,255));
    m_Pen.setWidth(1);
    m_pFont1 = new QFont("Arial", 10, QFont::Normal, false);
    m_pFont2 = new QFont("Arial", 10, QFont::Normal, false);
    m_FillBrush.setColor(QColor(3,14,207));
    m_FillBrush.setStyle(Qt::SolidPattern);

    renderBackground();

}

void ScalePAWidget::renderBackground()
{
    m_theBGPixmapPtr = new QPixmap(this->width(), this->height());

    m_pPainter->begin(m_theBGPixmapPtr);
    m_pPainter->fillRect(m_theBGPixmapPtr->rect(),this->palette().color(QPalette::Window));
    m_pPainter->setPen(m_Pen);
    m_pPainter->setFont(*m_pFont2);
    m_pPainter->drawText(14,6,30,20,Qt::AlignCenter,m_strLabel);
    m_pPainter->setFont(*m_pFont1);
    m_pPainter->drawLine(40,25,50,25);

    int jInterval = 40;
    for(int j = 0 ;j<10;j++)
    {
        m_pPainter->drawLine(40,25+j*jInterval,50,25+j*jInterval);
    }

    m_pPainter->drawText(50,23,24,10,Qt::AlignCenter,"900");
    m_pPainter->drawText(50,63,24,10,Qt::AlignCenter,"800");
    m_pPainter->drawText(50,103,24,10,Qt::AlignCenter,"700");
    m_pPainter->drawText(50,143,24,10,Qt::AlignCenter,"600");
    m_pPainter->drawText(50,183,24,10,Qt::AlignCenter,"500");
    m_pPainter->drawText(50,223,24,10,Qt::AlignCenter,"400");
    m_pPainter->drawText(50,263,24,10,Qt::AlignCenter,"300");
    m_pPainter->drawText(50,303,24,10,Qt::AlignCenter,"200");
    m_pPainter->drawText(50,343,24,10,Qt::AlignCenter,"100");
    m_pPainter->drawText(50,383,24,10,Qt::AlignCenter,"0");

    m_ScalerFrame = QRect(10,25,30,360);
    m_pPainter->drawRect(m_ScalerFrame); //主体竖着的矩形

    m_pPainter->end();
}

void ScalePAWidget::paintEvent(QPaintEvent *event)
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
        m_pPainter->fillRect(m_ScalerDraw,m_FillBrush);
    }

    m_pPainter->drawText(2,390,50,20,Qt::AlignCenter,QString("%1").arg(m_iValue)+" kPa");

    m_bShallUpdate = false;
    m_pPainter->end();
}

bool ScalePAWidget::votedUpdate()
{
    m_bShallUpdate = true;
    if(m_iValue != 0)
    {
        int iScaleHeight = int(m_iValue * 0.4) ;//x0.24
        int iScaleStartY = 385 - iScaleHeight ;
        m_ScalerDraw = QRect(12,iScaleStartY,28,iScaleHeight);//change width
    }
    else
    {
        m_ScalerDraw = QRect(0,0,0,0);
    }

    this->update();
    return true ;
}

void ScalePAWidget::setValue(int value)
{
    m_iValue = value ;
    this->update();
}

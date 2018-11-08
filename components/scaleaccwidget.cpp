#include "scaleaccwidget.h"
#include <QDebug>

ScaleAccWidget::ScaleAccWidget(QWidget *parent, const char *pszNamePtr, int iWidth, int iHeight, int iPosX, int iPosY):
    CXAbstractWidget(parent, pszNamePtr, iWidth, iHeight, iPosX, iPosY)
{
    m_pPainter = new QPainter();
    m_iStartX = iPosX;
    m_iStartY = iPosY;
    m_iWidth = iWidth;
    m_iHeight = iHeight;

    init();
}

ScaleAccWidget::~ScaleAccWidget(){
    delete m_pFont1;
    delete m_pFont2;
    delete m_pFont3;
    delete m_pPainter;
    delete m_theBGPixmapPtr;
}

void ScaleAccWidget::init()
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
    m_Pen.setWidth(2);

    m_pFont1 = new QFont("Arial", 8, QFont::Normal, false);
    m_pFont2 = new QFont("Arial", 12, QFont::Normal, false);
    m_pFont3 = new QFont("Arial", 16, QFont::Normal, false);

    renderBackground();

}

void ScaleAccWidget::renderBackground()
{
    m_theBGPixmapPtr = new QPixmap(this->width(), this->height());

    m_pPainter->begin(m_theBGPixmapPtr);
    m_pPainter->fillRect(m_theBGPixmapPtr->rect(),this->palette().color(QPalette::Window));
    m_pPainter->setPen(m_Pen);
    m_pPainter->setFont(*m_pFont3);
    //m_pPainter->setFont(*m_pFont2);
    m_FillBrush.setColor(QColor(221,27,237));
    m_FillBrush.setStyle(Qt::SolidPattern);
    m_FillLeftBrush.setColor(QColor(255,255,0));
    m_FillLeftBrush.setStyle(Qt::SolidPattern);
    m_pPainter->drawRect(15,2,230,20);//Acc Rectangle
    m_pPainter->drawText(5,2,10,20,Qt::AlignCenter,"-");
    m_pPainter->drawText(245,2,10,20,Qt::AlignCenter,"+");
    //
    m_pPainter->drawLine(QPoint(125,0),QPoint(125,24));
    //
    m_pPainter->end();
}

void ScaleAccWidget::paintEvent(QPaintEvent *event)
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
        if((m_iValue >= 0) && (m_iValue <= 200))
        {
            m_pPainter->fillRect(m_ScalerDraw,m_FillLeftBrush);
            m_pPainter->drawText(15,30,230,20,Qt::AlignCenter,QString("+%1 km/h/min").arg(m_iValue));
        }else if((m_iValue >= -200) && (m_iValue < 0)){
            m_pPainter->fillRect(m_ScalerDraw,m_FillLeftBrush);
            m_pPainter->drawText(15,30,230,20,Qt::AlignCenter,QString("%1 km/h/min").arg(m_iValue));
        }
    }

    m_bShallUpdate = false;
    m_pPainter->end();
}

bool ScaleAccWidget::votedUpdate()
{
    m_bShallUpdate = true;

    if((m_iValue >= 0) && (m_iValue <= 200))
    {
        int iScaleWidth = int(m_iValue * 0.6);
        m_ScalerDraw = QRect(125,3,iScaleWidth,18);
    }else if((m_iValue >= -200) && (m_iValue < 0)){
        int iScaleWidth = int((-m_iValue) * 0.55);
        m_ScalerDraw = QRect(128-iScaleWidth,3,iScaleWidth,18);
    }

    this->update();
    return m_bShallUpdate;
}

void ScaleAccWidget::setValue(int value)
{
    m_iValue = value ;
    this->update();
}

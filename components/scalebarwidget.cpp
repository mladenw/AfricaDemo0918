#include "scalebarwidget.h"
#include <QDebug>

ScaleBarWidget::ScaleBarWidget(QWidget *parent, const char *pszNamePtr, int iWidth, int iHeight, int iPosX, int iPosY, const QString strLabel):
    CXAbstractWidget(parent, pszNamePtr, iWidth, iHeight, iPosX, iPosY)
{
    m_iStartX = iPosX;
    m_iStartY = iPosY;
    m_iWidth = iWidth;
    m_iHeight = iHeight;
    m_strLabel = strLabel;

    m_pPainter = new QPainter();

    init();
}

ScaleBarWidget::~ScaleBarWidget(){
    delete m_pFont1;
    delete m_pFont2;
    delete m_pFont3;
    delete m_pPainter;
    delete m_theBGPixmapPtr;
}

void ScaleBarWidget::init()
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
    m_pFont1 = new QFont("Arial", 8, QFont::Normal, false);
    m_pFont2 = new QFont("Arial", 10, QFont::Normal, false);
    m_pFont3 = new QFont("Arial", 16, QFont::Normal, false);
    m_FillBrush.setColor(QColor(46,117,181));
    m_FillBrush.setStyle(Qt::SolidPattern);

    m_GreenBrush.setColor(QColor(5,194,34));
    m_GreenBrush.setStyle(Qt::SolidPattern);

    renderBackground();

}

void ScaleBarWidget::renderBackground()
{
    m_theBGPixmapPtr = new QPixmap(this->width(), this->height());

    m_pPainter->begin(m_theBGPixmapPtr);
    m_pPainter->fillRect(m_theBGPixmapPtr->rect(),this->palette().color(QPalette::Window));
    m_pPainter->setPen(m_Pen);
    m_pPainter->setFont(*m_pFont2);
    m_pPainter->drawText(6,0,80,20, (Qt::AlignVCenter|Qt::AlignLeft),m_strLabel);
    m_pPainter->setFont(*m_pFont2);
    m_pPainter->setFont(*m_pFont1);

    m_ScalerFrame = QRect(10,20,30,360);
    m_pPainter->drawRect(m_ScalerFrame); //主体竖着的矩形

    m_pPainter->end();
}

void ScaleBarWidget::paintEvent(QPaintEvent *event)
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
        if((m_iValue >= -500) && (m_iValue <0)){
            m_pPainter->fillRect(m_ScalerDraw,m_FillBrush);
            m_pPainter->drawText(2,384,46,20,Qt::AlignCenter,QString("%1").arg(-m_iValue)+" kN");
        }else if((m_iValue >= 0) && (m_iValue <= 700)){
            m_pPainter->fillRect(m_ScalerDraw,m_GreenBrush);
            m_pPainter->drawText(2,384,46,20,Qt::AlignCenter,QString("%1").arg(m_iValue)+" kN");
        }
    }

    m_bShallUpdate = false;
    m_pPainter->end();
}

bool ScaleBarWidget::votedUpdate()
{
    m_bShallUpdate = true;
    if((m_iValue >= -500) && (m_iValue <0)){
        int iScaleHeight = int((-m_iValue) * 0.72);
        int iScaleStartY = 380 - iScaleHeight;
        m_ScalerDraw = QRect(11,iScaleStartY,29,iScaleHeight);
    }else if((m_iValue >= 0) && (m_iValue <= 700)){
        int iScaleHeight = int(m_iValue * 0.514);
        int iScalerStartY = 380 - iScaleHeight;
        m_ScalerDraw = QRect(11,iScalerStartY,29,iScaleHeight);
    }else{
        m_ScalerDraw = QRect(0,0,0,0);
    }

    this->update();
    return m_bShallUpdate ;
}

void ScaleBarWidget::setValue(int value)
{
    m_iValue = int(value);
    this->update();
}

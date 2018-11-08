#include "scaleunitwidget.h"
#include <QDebug>

ScaleUnitWidget::ScaleUnitWidget(QWidget *parent, const char *pszNamePtr, int iWidth, int iHeight, int iPosX, int iPosY):
    CXAbstractWidget(parent, pszNamePtr, iWidth, iHeight, iPosX, iPosY)
{
    m_pPainter = new QPainter();
    m_iStartX = iPosX;
    m_iStartY = iPosY;
    m_iWidth = iWidth;
    m_iHeight = iHeight;

    init();
}

ScaleUnitWidget::~ScaleUnitWidget(){
    delete m_pFont1;
    delete m_pFont2;
    delete m_pFont3;
    delete m_pPainter;
    delete m_theBGPixmapPtr;
}

void ScaleUnitWidget::init()
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
    m_Pen.setColor(Qt::white);
    m_Pen.setWidth(2);

    m_pFont1 = new QFont("Arial", 8, QFont::Normal, false);
    m_pFont2 = new QFont("Arial", 12, QFont::Normal, false);
    m_pFont3 = new QFont("Arial", 16, QFont::Normal, false);

    renderBackground();

}

void ScaleUnitWidget::renderBackground()
{
    m_theBGPixmapPtr = new QPixmap(this->width(), this->height());

    m_pPainter->begin(m_theBGPixmapPtr);
    m_pPainter->fillRect(m_theBGPixmapPtr->rect(),this->palette().color(QPalette::Window));
    m_pPainter->setPen(m_Pen);
    m_pPainter->setFont(*m_pFont3);
    m_pPainter->setFont(*m_pFont2);
    m_FillBrush.setColor(Qt::black);
    m_FillBrush.setStyle(Qt::SolidPattern);
    m_pPainter->fillRect(15,20,70,20,m_FillBrush);
    m_pPainter->fillRect(88,20,60,20,m_FillBrush);
    m_pPainter->drawText(5,20,80,20,Qt::AlignCenter,"Parameter");
    m_pPainter->drawText(88+10,20,60,20,Qt::AlignCenter,"Value");

    m_pPainter->drawText(15,53,90,40,Qt::AlignCenter|Qt::AlignHCenter,"Engine");

    m_pPainter->end();
}

void ScaleUnitWidget::paintEvent(QPaintEvent *event)
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

    }

    m_bShallUpdate = false;
    m_pPainter->end();
}

#include "pagegeneral.h"
#include "components/scalebarwidget.h"
#include "components/scalepawidget.h"
#include "components/notchbarwidget.h"
#include "components/scaleaccwidget.h"
#include "tcmscomm/tcmsAfricabuffer.h"
#include "components/scaleunitwidget.h"
#include "components/analogclockwidget.h"
#include "components/scalecontentwidget.h"

PageGeneral::PageGeneral(QWidget *parent, const char *pszNamePtr, int iWidth, int iHeight, int iPosX, int iPosY)
    : CXAbstractWidget(parent, pszNamePtr, iWidth, iHeight, iPosX, iPosY)
{
    m_pAnalogClock = new AnalogClockWidget(this, "Anlogclock", 330, 330, 50, 25);
    m_pScaleBrakePipeBar = new ScalePAWidget(this, "BrakePipe", 80, 410, 5, 10, "BP");
    m_pScaleAccBar = new ScaleAccWidget(this, "Acc", 260, 80, 85, 350);
    m_pScaleNotchBar = new NotchBarWidget(this, "Notch", 60, 400, 345, 20, "Notch");
    m_pScaleTractionBreakBar = new ScaleBarWidget(this, "TractionBrake", 60, 400, 410, 20, "TE/BE");
    m_pScaleTitle = new ScaleUnitWidget(this, "Title", 150, 55, 470, 20);
    m_pScaleContent = new ScaleContentWidget(this, "Content",160, 350, 470, 60);

    m_pPainter = new QPainter();
    init();
}

PageGeneral::~PageGeneral()
{
    delete m_theFont1Ptr;
    delete m_theFont2Ptr;
    delete m_pPainter;
    delete m_theBGPixmapPtr;
    delete m_pScaleBrakePipeBar;
    delete m_pAnalogClock;
    delete m_pScaleAccBar;
    delete m_pScaleNotchBar;
    delete m_pScaleTractionBreakBar;
    delete m_pScaleTitle;
    delete m_pScaleContent;
}

void PageGeneral::init()
{
    // Set attributes
    setAutoFillBackground(false);
    setAttribute(Qt::WA_OpaquePaintEvent, true);

    // Set palette
    QPalette aQPalette = this->palette();
    aQPalette.setColorGroup (QPalette::Active,
                             QColor(255,255,255),
                             aQPalette.button(),
                             QColor(255,255,255),
                             aQPalette.dark(),
                             aQPalette.mid(),
                             QColor(255,255,255),
                             aQPalette.brightText(),
                             aQPalette.base(),
                             QColor(0,0,0));	   // const QBrush & window
    aQPalette.setColorGroup (QPalette::Inactive,
                             QColor(255,255,255),
                             aQPalette.button(),
                             QColor(255,255,255),
                             aQPalette.dark(),
                             aQPalette.mid(),
                             QColor(255,255,255),
                             aQPalette.brightText(),
                             aQPalette.base(),
                             QColor(0,0,0));	   // const QBrush & window
    this->setPalette(aQPalette);

    m_theFont1Ptr = new QFont("Arial", 12, QFont::Normal, false);
    m_theFont2Ptr = new QFont("Arial", 16, QFont::Normal, false);
    m_theTextPen = QPen(Qt::white);
    this->setFont(*m_theFont1Ptr);

    m_whitePen = QPen(Qt::white);

    m_isBackgroundSet = false;
    m_bShallUpdate    = true;

    renderBackGround();

    return;
}

void PageGeneral::renderBackGround()
{
    m_theBGPixmapPtr = new QPixmap(this->width(), this->height());

    m_pPainter->begin(m_theBGPixmapPtr);

    m_pPainter->setFont(*m_theFont1Ptr);
    m_pPainter->setPen(m_theTextPen);
    m_pPainter->fillRect(m_theBGPixmapPtr->rect(),this->palette().color(QPalette::Window));
    m_whitePen.setWidth(1);
    m_pPainter->setPen(m_whitePen);
    m_pPainter->drawLine(0,0,0,450);    //左边竖线
    m_pPainter->drawLine(639,0,639,450);//右侧竖线
    m_pPainter->drawLine(0,449,640,449);//底端竖线

    m_pPainter->end();
}

void PageGeneral::paintEvent(QPaintEvent *event)
{
    if(event->rect() == this->rect())
    {
        m_isBackgroundSet = false;
    }

    m_pPainter->begin(this);

    if(!m_isBackgroundSet)
    {
        m_pPainter->drawPixmap(0, 0, *m_theBGPixmapPtr);
        m_isBackgroundSet = true;
    }
    m_pPainter->drawText(QRect(550,420,90,30),"Version 1.2");
    m_pPainter->end();
}

bool PageGeneral::votedUpdata()
{
    m_pScaleContent->setShallUpdate();
    m_pScaleBrakePipeBar->votedUpdate();
    m_pAnalogClock->votedUpdate();
    m_pScaleAccBar->votedUpdate();
    m_pScaleTractionBreakBar->votedUpdate();
    m_pScaleNotchBar->votedUpdate();

    return false ;
}

void PageGeneral::UpdatePage()
{
    int m_itmp_BP_Pressure;
    float m_itmp_LocoSpeed;
    int m_itmp_LocoAcc;
    int m_itmp_INotch;
    int m_itmp_TracEffort;
    int m_itmp_LocoMode;
    if(m_pMvbAfricaBuffer->getBCU_Status_Life())
    {
        m_itmp_BP_Pressure = static_cast<int>(m_pMvbAfricaBuffer->getBP_Pressure() * 0.0625) ;
    }else
    {
        m_itmp_BP_Pressure = 0 ;

    }

    if(m_pMvbAfricaBuffer->getVCU_Status_Life())
    {

        m_itmp_LocoSpeed = static_cast<float>(m_pMvbAfricaBuffer->getLocoSpeed() * 0.01) ;
        m_itmp_LocoAcc = static_cast<int>(m_pMvbAfricaBuffer->getLocoAcc()) ;//  x10
        m_itmp_INotch = m_pMvbAfricaBuffer->getNotch();
        m_itmp_TracEffort = static_cast<int>(m_pMvbAfricaBuffer->getTracEffort() * 0.1) ;
        m_itmp_LocoMode = static_cast<int>(m_pMvbAfricaBuffer->getLocoMode());
    }else
    {
        m_itmp_LocoSpeed = 0.00;
        m_itmp_LocoAcc = 0;
        m_itmp_INotch = 0;
        m_itmp_TracEffort = 0;
        m_itmp_LocoMode = 0;
    }

    if((m_itmp_BP_Pressure >= 0) && (m_itmp_BP_Pressure <= 900)){
        m_pScaleBrakePipeBar->setValue(m_itmp_BP_Pressure);
    }

    if((m_itmp_LocoSpeed >= 0) && (m_itmp_LocoSpeed <= 120)){
        m_pAnalogClock->setValue(m_itmp_LocoSpeed,m_itmp_LocoMode);
    }

    m_pScaleAccBar->setValue(m_itmp_LocoAcc);
    m_pScaleTractionBreakBar->setValue(m_itmp_TracEffort);
    m_pScaleNotchBar->setValue(m_itmp_INotch);
}

void PageGeneral::setContentBuffer(TcmsAfricaBuffer *AfricaContentBuffer)
{
    AfricaContentBuffer = m_pMvbAfricaBuffer ;
    m_pScaleContent->setAfricaBuffer(AfricaContentBuffer);
}

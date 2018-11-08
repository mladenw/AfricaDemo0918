#include "pagealltop.h"

PageAlltop::PageAlltop(QWidget *parent, const char *pszNamePtr, int iWidth, int iHeight, int iPosX, int iPosY) :
    CXAbstractWidget(parent, pszNamePtr, iWidth, iHeight, iPosX, iPosY)
{
    m_pPainter = new QPainter();
    init();
}

PageAlltop::~PageAlltop()
{
    delete m_pPainter;
    delete m_theBGPixmapPtr;
    delete m_theFontPtr;
}

void PageAlltop::init()
{
    QPalette aQPalette;
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

    setAutoFillBackground(false);
    setAttribute(Qt::WA_OpaquePaintEvent, true);         //Widget paints all its pixels when it receives a paint event

    m_theFontPtr = new QFont("Arial", 14, QFont::Normal, false);

    this->setFont(*m_theFontPtr);
    m_isBackgroundSet = false;
    m_bShallUpdate    = false;
    m_whitePen = QPen(Qt::white);
    m_blackPen = QPen(Qt::black);
    m_greenPen = QPen(Qt::green);
    m_redPen   = QPen(Qt::red);

    m_strCurrentTime = QString("");
    m_strCurrentDate = QString("");
    m_strSpeed = QString("");
    m_strLocoNumber = QString("");

    renderBackgroundPixmap();
}

void PageAlltop::renderBackgroundPixmap()
{
    QPainter aPainter;

    m_theBGPixmapPtr = new QPixmap(this->width(),this->height());

    aPainter.begin(m_theBGPixmapPtr);
    aPainter.setPen(m_whitePen);
    aPainter.setFont(*m_theFontPtr);
    aPainter.fillRect(m_theBGPixmapPtr->rect(), this->palette().color(QPalette::Window));

    // Draw Rect 画上端界面
    m_whitePen.setWidth(1);
    aPainter.drawLine(QPoint(0, 0), QPoint(640,0));
    aPainter.drawLine(QPoint(0,0),QPoint(0,29));
    aPainter.drawLine(QPoint(0, 29), QPoint(640, 29));
    aPainter.drawLine(QPoint(256,0),QPoint(256,29));
    aPainter.drawLine(QPoint(384,0),QPoint(384,29));
    aPainter.drawLine(QPoint(512,0),QPoint(512,29));
    aPainter.drawLine(QPoint(639,0),QPoint(639,29));
    aPainter.drawText(QRect(0, 6, 130, 29), Qt::AlignLeft, "Loco No: D45");

    m_greenPen.setWidth(4);
    aPainter.setPen(m_greenPen);

    aPainter.end();
}

void PageAlltop::paintEvent(QPaintEvent *event)
{
    if(event->rect() == this->rect())
     {
         m_isBackgroundSet = false;
     }

     m_pPainter->begin(this);
     m_pPainter->setRenderHint(QPainter::Antialiasing, false);
     m_pPainter->setRenderHint(QPainter::SmoothPixmapTransform, false);
     m_pPainter->setPen(m_whitePen);
     m_pPainter->setFont(*m_theFontPtr);
     if(!m_isBackgroundSet)
     {
         m_pPainter->drawPixmap(0, 0, *m_theBGPixmapPtr);
         m_isBackgroundSet = true;
     }
     if(m_bShallUpdate){
         if(m_pMvbAfricaBuffer->getVCU_Status_Life())
         {
             //LocoNumber
             m_pPainter->drawText(62,0,90,29,Qt::AlignCenter,m_strLocoNumber);

             //Speed
             if((m_fPageAllTopSpeed >= 0) && (m_fPageAllTopSpeed <=90)){
                 m_pPainter->setPen(m_greenPen);
                 m_pPainter->drawText(256, 0, 60, 29, Qt::AlignCenter, m_strSpeed);
                 m_pPainter->drawText(QRect(230, 6 ,128, 29), Qt::AlignRight,"km/h");
             }else if((m_fPageAllTopSpeed >90) && (m_fPageAllTopSpeed <=120)){
                 m_pPainter->setPen(m_redPen);
                 m_pPainter->drawText(256, 0, 60, 29, Qt::AlignCenter, m_strSpeed);
                 m_pPainter->drawText(QRect(230, 6 ,128, 29), Qt::AlignRight,"km/h");
             }
             //时间
             m_pPainter->setPen(m_whitePen);
             m_pPainter->drawText(QRect(512, 0, 128, 29), Qt::AlignCenter, m_strCurrentTime);
             m_pPainter->drawText(QRect(384, 0, 128, 29), Qt::AlignCenter, m_strCurrentDate);
         }else
         {
             m_pPainter->drawText(62,0,90,29,Qt::AlignCenter,"***");

             m_pPainter->drawText(QRect(230, 6 ,128, 29), Qt::AlignRight,"km/h");
             m_pPainter->drawText(256, 0, 60, 29, Qt::AlignCenter, "***");
             //m_pPainter->drawText(QRect(230, 6 ,128, 29), Qt::AlignRight,"km/h");
             //时间
             m_pPainter->setPen(m_whitePen);
             m_pPainter->drawText(QRect(512, 0, 128, 29), Qt::AlignCenter, "**/**/**");
             m_pPainter->drawText(QRect(384, 0, 128, 29), Qt::AlignCenter, "****-**-**");
         }

     }
     m_bShallUpdate = false;

     m_pPainter->end();
}

bool PageAlltop::votedUpdate()
{
    m_bShallUpdate = true;
    PAGE_AllTop PageAllTop;
    QDateTime dateTime = QDateTime::fromTime_t(m_pMvbAfricaTimeBuffer->getAfricaTimeContent());
    PageAllTop = m_pLogic_PageAllTop->get_PAGE_AllTop_Data();
    m_strLocoNumber = PageAllTop.AfricaLocoNumber ;
    m_strSpeed = PageAllTop.AfricaLocoSpeed ;
    m_strCurrentDate = dateTime.toString("yyyy-MM-dd");
    m_strCurrentTime = dateTime.toString("hh:mm:ss");

    m_fPageAllTopSpeed = m_pMvbAfricaBuffer->getLocoSpeed() * 0.01;

    this->update();

    return m_bShallUpdate ;
}

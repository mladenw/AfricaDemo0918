#include "analogclockwidget.h"
#include <QDebug>

AnalogClockWidget::AnalogClockWidget(QWidget *parent, const char *pszNamePtr, int iWidth, int iHeight, int iPosX, int iPosY):
    CXAbstractWidget(parent, pszNamePtr, iWidth, iHeight, iPosX, iPosY)
{
    m_pPainter = new QPainter();

    init();
    initData();
}

AnalogClockWidget::~AnalogClockWidget(){
    delete m_theFont1Ptr;
    delete m_theFont2Ptr;
    delete m_pPainter;
    delete m_theBGPixmapPtr;
}

void AnalogClockWidget::init()
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
    m_bShallUpdate = false;

    setAutoFillBackground(false);
    setAttribute(Qt::WA_OpaquePaintEvent, true);         //Widget paints all its pixels when it receives a paint event

    m_theFont1Ptr = new QFont("Arial", 16, QFont::Normal, false);
    m_theFont2Ptr = new QFont("Arial", 20, QFont::Normal, false);
    m_theTextPen = QPen(Qt::white);
    this->setFont(*m_theFont1Ptr);

    renderBackground();

}

void AnalogClockWidget::renderBackground()
{
    m_theBGPixmapPtr = new QPixmap(this->width(), this->height());

    m_pPainter->begin(m_theBGPixmapPtr);
    m_pPainter->setFont(*m_theFont1Ptr);
    m_pPainter->setPen(m_theTextPen);
    m_pPainter->fillRect(m_theBGPixmapPtr->rect(),this->palette().color(QPalette::Window));

    m_pPainter->end();
}

void AnalogClockWidget::paintEvent(QPaintEvent *event)
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
    //设置指针的关键点
    static const QPoint hourHand[8] =
    {
        QPoint(4,-20),
        QPoint(4,-60),
        QPoint(1,-70),
        QPoint(1,-80),
        QPoint(-1,-80),
        QPoint(-1,-70),
        QPoint(-4,-60),
        QPoint(-4,-20)
    };
    //设置颜色
    QColor pointer(200,0,0);
    QColor hourColor(255,255,255);
    QColor minuteColor(255,122,29);
    QColor textColor(255,255,255);

    int side = qMin(width(), height());

    QPainter painter(this);
    painter.fillRect(rect(), QBrush(Qt::black));
    painter.translate(width()/2,height()/2);
    painter.scale(side/300.0,side/300.0);

    painter.setPen(Qt::NoPen);
    painter.setBrush(pointer);

    painter.save();
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setPen(hourColor);
    for(int i=0;i<9;i++){
        painter.drawLine(-53,73,-62,85);
        painter.rotate(36.0);
    }
    painter.restore();
    painter.save();
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setPen(minuteColor);
    for(int j=0;j<8;j++){
        painter.drawLine(-73,53,-85,62);
        painter.rotate(36.0);
    }
    painter.restore();

    //内圆
    painter.save();
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setPen(QPen(Qt::white,2,Qt::SolidLine));
    painter.setBrush(QBrush(Qt::white));
    painter.drawEllipse(-20,-20,40,40);
    painter.restore();


    painter.save();
    painter.setPen(QPen(Qt::white,2,Qt::SolidLine));
    QFont font;
    font.setPointSize(36);
    painter.setFont(font);
    if(m_bShallUpdate)
    {
        painter.drawText(-118,85,240,60,Qt::AlignCenter,QString("%1 km/h").arg(m_iValue));
    }

    painter.restore();

    //内圆内数字
    font.setPointSize(12);
    setFont(font);
    //painter.drawText(-13,-11,30,30,Qt::AlignHCenter | Qt::AlignTop,QString::number(m_iValue));
    painter.drawText(-16,-7,30,30,Qt::AlignHCenter | Qt::AlignTop,"");
    painter.setBrush(Qt::white);
    if(m_iLocomMode == 35)
    {

        //最外面圆弧
        painter.save();
        painter.setPen(QPen(Qt::white,3,Qt::SolidLine));
        painter.setRenderHint(QPainter::Antialiasing,true);
        painter.drawArc(-105,-105,210,210,-54*16,288*16);
        painter.restore();

        //设置刻度值
        painter.setPen(textColor);
        painter.drawText(-61, 57,30, 30, Qt::AlignHCenter | Qt::AlignTop,QString::number(0));//从（x,y）开始,高为30,宽为30
        painter.drawText(-90, 15,35,30, Qt::AlignHCenter | Qt::AlignTop,QString::number(0.375));
        painter.drawText(-90, -35,30, 30,Qt::AlignHCenter | Qt::AlignTop,QString::number(0.75));
        painter.drawText(-62, -71,35, 30,Qt::AlignHCenter | Qt::AlignTop,QString::number(1.125));
        painter.drawText(-15, -90,30, 30,Qt::AlignHCenter | Qt::AlignTop,QString::number(1.5));
        painter.drawText(27, -71,35, 30,Qt::AlignHCenter | Qt::AlignTop,QString::number(1.875));
        painter.drawText(62, -31,30, 30,Qt::AlignHCenter | Qt::AlignTop,QString::number(2.25));
        painter.drawText(55, 20,33, 30,Qt::AlignHCenter | Qt::AlignTop,QString::number(2.625));
        painter.drawText(35, 55,30, 30,Qt::AlignHCenter | Qt::AlignTop,QString::number(3));

        //画指针
        painter.save();
        painter.setPen(textColor);
        painter.setRenderHint(QPainter::Antialiasing,true);
        if(m_iValue > 3)//speed > 3km/h  clock just show 3km/h
            m_iValue = 3;
        painter.rotate(180+36+m_iValue*40*288/120);
        painter.drawConvexPolygon(hourHand, 8);
        painter.restore();
    }else
    {

        //最外面圆弧
        painter.save();
        painter.setPen(QPen(Qt::red,3,Qt::SolidLine));
        painter.setRenderHint(QPainter::Antialiasing,true);
        painter.drawArc(-105,-105,210,210,-54*16,48*16);
        painter.restore();
        painter.save();
        painter.setPen(QPen(Qt::yellow,3,Qt::SolidLine));
        painter.setRenderHint(QPainter::Antialiasing,true);
        painter.drawArc(-105,-105,210,210,-6*16,24*16);
        painter.restore();
        painter.save();
        painter.setPen(QPen(Qt::white,3,Qt::SolidLine));
        painter.setRenderHint(QPainter::Antialiasing,true);
        painter.drawArc(-105,-105,210,210,18*16,216*16);
        painter.restore();
        //设置刻度值
        painter.setPen(textColor);
        painter.drawText(-61, 57,30, 30, Qt::AlignHCenter | Qt::AlignTop,QString::number(0));//从（x,y）开始,高为30,宽为30
        painter.drawText(-90, 15,30, 30, Qt::AlignHCenter | Qt::AlignTop,QString::number(15));
        painter.drawText(-90, -35,30, 30,Qt::AlignHCenter | Qt::AlignTop,QString::number(30));
        painter.drawText(-62, -71,30, 30,Qt::AlignHCenter | Qt::AlignTop,QString::number(45));
        painter.drawText(-15, -90,30, 30,Qt::AlignHCenter | Qt::AlignTop,QString::number(60));
        painter.drawText(32, -71,30, 30,Qt::AlignHCenter | Qt::AlignTop,QString::number(75));
        painter.drawText(62, -31,30, 30,Qt::AlignHCenter | Qt::AlignTop,QString::number(90));
        painter.drawText(60, 20,28, 30,Qt::AlignHCenter | Qt::AlignTop,QString::number(105));
        painter.drawText(35, 55,30, 30,Qt::AlignHCenter | Qt::AlignTop,QString::number(120));

        //画指针
        painter.save();
        painter.setPen(textColor);
        painter.setRenderHint(QPainter::Antialiasing,true);
        painter.rotate(180+36+m_iValue*288/120);
        //painter.rotate(180+36+mValue*288/160);
        painter.drawConvexPolygon(hourHand, 8);
        painter.restore();

    }



    m_bShallUpdate = false;
    m_pPainter->end();
}

bool AnalogClockWidget::votedUpdate()
{
    m_bShallUpdate = true;

    if (m_bShallUpdate) {
        this->update();
    }

    return m_bShallUpdate;
}

void AnalogClockWidget::setValue(float value,int LocoMode)
{
    m_iValue = value;
    m_iLocomMode = LocoMode;
    this->update();
}

void AnalogClockWidget::initData()
{
    this->setValue(0,0);
}

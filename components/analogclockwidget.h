#ifndef ANALOGCLOCKWIDGET_H
#define ANALOGCLOCKWIDGET_H

#include "Core/CXAbstractWidget.h"
#include <QtGui>
#include <QPushButton>
#include <QPainter>
#include <QPen>
#include <QPixmap>

class AnalogClockWidget : public CXAbstractWidget
{
    Q_OBJECT
public:
    AnalogClockWidget(QWidget *parent, const char *pszNamePtr, int iWidth, int iHeight, int iPosX, int iPosY);
    ~AnalogClockWidget();

    void initData();
    bool votedUpdate();
    void setValue(float value, int LocoMode);

protected:
    void paintEvent(QPaintEvent *event);

private:
    void init();
    void renderBackground();

    bool m_isBackgroundSet;
    bool m_bShallUpdate;
    int m_iLocomMode;
    QFont           *m_theFont1Ptr;
    QFont           *m_theFont2Ptr;
    QPen             m_theTextPen;
    QPainter        *m_pPainter;
    QPixmap	        *m_theBGPixmapPtr;
    float            m_iValue;
};

#endif // ANALOGCLOCKWIDGET_H

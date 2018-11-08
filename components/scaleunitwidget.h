#ifndef SCALEUNITWIDGET_H
#define SCALEUNITWIDGET_H

#include <QPen>
#include <QtGui>
#include <QBrush>
#include <QColor>
#include <QPixmap>
#include <QPainter>
#include <QPushButton>
#include "Core/CXAbstractWidget.h"

class ScaleUnitWidget : public CXAbstractWidget
{
    Q_OBJECT
public:
    ScaleUnitWidget(QWidget *parent, const char *pszNamePtr, int iWidth, int iHeight, int iPosX, int iPosY);

    ~ScaleUnitWidget();

protected:
    void paintEvent(QPaintEvent *event);

private:
    void init();
    void renderBackground();

    bool m_isBackgroundSet;
    bool m_bShallUpdate;
    int  m_iWidth;
    int  m_iHeight;
    int  m_iStartX;
    int  m_iStartY;
    int  m_iValue;

    QRect m_ScalerFrame;
    QRect m_IndicatorFrame;
    QRect m_ScalerDraw;

    QPen m_Pen;
    QFont *m_pFont1;
    QFont *m_pFont2;
    QFont *m_pFont3;
    QBrush m_FillBrush;

    QPainter *m_pPainter;
    QPixmap	 *m_theBGPixmapPtr;
};

#endif // SCALEUNITWIDGET_H

#ifndef SCALEACCWIDGET_H
#define SCALEACCWIDGET_H

#include "Core/CXAbstractWidget.h"
#include <QtGui>
#include <QPushButton>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QColor>
#include <QPixmap>

class ScaleAccWidget : public CXAbstractWidget
{
    Q_OBJECT
public:
    ScaleAccWidget(QWidget *parent, const char *pszNamePtr, int iWidth, int iHeight, int iPosX, int iPosY);
    ~ScaleAccWidget();

    bool votedUpdate();
    void setValue(int value);

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
    QBrush m_FillLeftBrush;

    QPainter *m_pPainter;
    QPixmap	 *m_theBGPixmapPtr;
};

#endif // SCALEACCWIDGET_H

#ifndef SCALEBARWIDGET_H
#define SCALEBARWIDGET_H

#include "Core/CXAbstractWidget.h"
#include <QPen>
#include <QtGui>
#include <QBrush>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <QPushButton>

class ScaleBarWidget : public CXAbstractWidget
{
    Q_OBJECT
public:
    ScaleBarWidget(QWidget *parent, const char *pszNamePtr, int iWidth, int iHeight, int iPosX, int iPosY, const QString strLabel);
    ~ScaleBarWidget();

    void setValue(int value);

    bool votedUpdate();

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
    QString m_strLabel;

    QRect m_ScalerFrame;
    QRect m_IndicatorFrame;
    QRect m_ScalerDraw;
    QRect m_ScalerBrakeDraw;

    QPen m_Pen;
    QFont *m_pFont1;
    QFont *m_pFont2;
    QFont *m_pFont3;
    QBrush m_FillBrush;
    QBrush m_GreenBrush;

    QPainter *m_pPainter;
    QPixmap	 *m_theBGPixmapPtr;
};

#endif // SCALEBARWIDGET_H

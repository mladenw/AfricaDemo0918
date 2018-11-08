#ifndef NOTCHBARWIDGET_H
#define NOTCHBARWIDGET_H

#include "Core/CXAbstractWidget.h"
#include <QtGui>
#include <QPen>
#include <QBrush>
#include <QPixmap>
#include <QRectF>
#include <QSizeF>
#include <QPainter>
#include <QPushButton>

class NotchBarWidget : public CXAbstractWidget
{
    Q_OBJECT
public:
    NotchBarWidget(QWidget *parent, const char *pszNamePtr, int iWidth, int iHeight, int iPosX, int iPosY, const QString strLabel);
    ~NotchBarWidget();

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
    QString m_strLabel;

    QRect m_ScalerFrame;
    QRect m_IndicatorFrame;
    QRectF m_ScalerDraw;

    QPen m_Pen;
    QFont *m_pFont1;
    QFont *m_pFont2;
    QFont *m_pFont3;
    QBrush m_FillBrush;
    QBrush m_GreenBrush;

    QPainter *m_pPainter;
    QPixmap	 *m_theBGPixmapPtr;

    int refreshData ;
};

#endif // NOTCHBARWIDGET_H

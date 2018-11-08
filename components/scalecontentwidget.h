#ifndef SCALECONTENTWIDGET_H
#define SCALECONTENTWIDGET_H

#include <QPen>
#include <QtGui>
#include <QBrush>
#include <QColor>
#include <QPixmap>
#include <QPainter>
#include <QPushButton>
#include "Core/CXAbstractWidget.h"
#include "tcmscomm/tcmsAfricabuffer.h"

class ScaleContentWidget : public CXAbstractWidget
{
    Q_OBJECT
public:
    ScaleContentWidget(QWidget *parent, const char *pszNamePtr, int iWidth, int iHeight, int iPosX, int iPosY);

    ~ScaleContentWidget();

    void setShallUpdate();
    void setAfricaBuffer(TcmsAfricaBuffer *AfricaBuffer);

signals:

public slots:

protected:
    void paintEvent(QPaintEvent *event);

private slots:

private:
    void init();
    void renderBackground();

    bool m_isBackgroundSet;
    bool m_bShallUpdate;
    bool m_bInitStatus;
    bool m_bInitValue;
    int  m_iValue;
    quint32 m_iMileageValueFlag;

    QRect m_ScalerFrame;
    QRect m_IndicatorFrame;
    QRect m_ScalerDraw;

    QPen m_Pen;
    QFont *m_pFont1;
    QFont *m_pFont2;
    QBrush m_FillBrush;

    QPainter *m_pPainter;
    QPixmap	 *m_theBGPixmapPtr;
    TcmsAfricaBuffer *m_pMvbAfricaBuffer;
};

#endif // SCALECONTENTWIDGET_H

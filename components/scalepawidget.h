#ifndef SCALEPAWIDGET_H
#define SCALEPAWIDGET_H

#include <QPen>
#include <QtGui>
#include <QBrush>
#include <QPixmap>
#include <QPainter>
#include <QPushButton>
#include "Core/CXAbstractWidget.h"

class ScalePAWidget : public CXAbstractWidget
{
    Q_OBJECT
public:
    ScalePAWidget(QWidget *parent, const char *pszNamePtr, int iWidth, int iHeight, int iPosX, int iPosY, const QString strLabel);
    ~ScalePAWidget();

    bool votedUpdate();
    void setValue(int value);

protected:
    void paintEvent(QPaintEvent *event);

private slots:

private:
    void init();
    void renderBackground();

    int         m_iWidth;
    int         m_iHeight;
    int         m_iStartX;
    int         m_iStartY;
    bool        m_bInitValue;
    bool        m_bInitStatus;
    bool        m_bShallUpdate;
    bool        m_isBackgroundSet;
    int         m_iValue;
    QString     m_strLabel;

    QPen        m_Pen;
    QFont       *m_pFont1;
    QFont       *m_pFont2;
    QBrush      m_FillBrush;
    QRect       m_ScalerFrame;
    QRect       m_ScalerDraw;
    QRect       m_IndicatorFrame;

    QPainter    *m_pPainter;
    QPixmap     *m_theBGPixmapPtr;

};

#endif // SCALEPAWIDGET_H

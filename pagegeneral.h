#ifndef PAGEGENERAL_H
#define PAGEGENERAL_H

#include <QObject>
#include <QPen>
#include <QPainter>
#include <QPaintEvent>
#include "Core/CXAbstractWidget.h"

class ScalePAWidget;
class NotchBarWidget;
class ScaleAccWidget;
class ScaleBarWidget;
class ScaleUnitWidget;
class AnalogClockWidget;
class ScaleContentWidget;
class TcmsAfricaBuffer;

class PageGeneral : public CXAbstractWidget
{
    Q_OBJECT
public:
    PageGeneral(QWidget *parent, const char *pszNamePtr, int iWidth, int iHeight, int iPosX, int iPosY);
    ~PageGeneral();
    void setAfricaBuffer(TcmsAfricaBuffer *AfricaBuffer){m_pMvbAfricaBuffer = AfricaBuffer;}
    void setContentBuffer(TcmsAfricaBuffer *AfricaContentBuffer);

    bool votedUpdata();
    void UpdatePage();

protected:
    void paintEvent(QPaintEvent *event);

private:
    void init();
    void renderBackGround();

    bool             m_bShallUpdate;
    bool             m_isBackgroundSet;
    QFont           *m_theFont1Ptr;
    QFont           *m_theFont2Ptr;
    QPixmap         *m_theBGPixmapPtr;
    QPainter        *m_pPainter;
    QPen             m_whitePen;
    QPen             m_theTextPen;

    ScalePAWidget      *m_pScaleBrakePipeBar;
    AnalogClockWidget  *m_pAnalogClock;
    ScaleAccWidget     *m_pScaleAccBar;
    NotchBarWidget     *m_pScaleNotchBar;
    ScaleBarWidget     *m_pScaleTractionBreakBar;
    ScaleUnitWidget    *m_pScaleTitle;
    ScaleContentWidget *m_pScaleContent;
    TcmsAfricaBuffer   *m_pMvbAfricaBuffer;

};

#endif // PAGEGENERAL_H

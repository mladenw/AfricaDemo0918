#ifndef PAGEALLTOP_H
#define PAGEALLTOP_H

#include <QPen>
#include <QRect>
#include <QtGui>
#include <QPixmap>
#include <QPainter>
#include <QWidget>
#include <QPainter>
#include <QPalette>
#include <QPaintEvent>
#include <QPushButton>
#include <QButtonGroup>
#include <QAbstractButton>
#include "Core/CXAbstractWidget.h"
#include "Logic/logic_page_alltop.h"
#include "tcmscomm/tcmsAfricabuffer.h"
#include "tcmscomm/tcmsAfricaTimebuffer.h"

class PageAlltop : public CXAbstractWidget
{
    Q_OBJECT
public:
    PageAlltop(QWidget *parent, const char *pszNamePtr, int iWidth, int iHeight, int iPosX, int iPosY);
    ~PageAlltop();
    void setPageLogic(Logic_Page_AllTop *TopData){m_pLogic_PageAllTop = TopData;}
    void setAfricaBuffer(TcmsAfricaBuffer *AfricaBuffer){m_pMvbAfricaBuffer = AfricaBuffer;}
    void setAfricaTimeBuffer(TcmsAfricaTimeBuffer *AfricaTimeBuffer){m_pMvbAfricaTimeBuffer = AfricaTimeBuffer;}

    bool votedUpdate();

protected:
    void paintEvent(QPaintEvent *event);

private:
    void init();
    void renderBackgroundPixmap();

    QPainter       *m_pPainter;

    QPixmap        *m_theBGPixmapPtr;
    QFont          *m_theFontPtr;
    QPen            m_whitePen;
    QPen            m_blackPen;
    QPen            m_greenPen;
    QPen            m_redPen;

    bool            m_isBackgroundSet;
    bool            m_bShallUpdate;
    QString         m_strCurrentTime;
    QString         m_strCurrentDate;
    QString         m_strSpeed;
    QString         m_strLocoNumber;

    float           m_fPageAllTopSpeed;

    Logic_Page_AllTop *m_pLogic_PageAllTop;
    TcmsAfricaBuffer  *m_pMvbAfricaBuffer;
    TcmsAfricaTimeBuffer *m_pMvbAfricaTimeBuffer;
};

#endif // PAGEALLTOP_H

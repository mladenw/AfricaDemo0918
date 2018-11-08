#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QTimer>

class PageAlltop;
class PageGeneral;
class TcmsController;
class CXAbstractWidget;
class Logic_Page_AllTop;
class TcmsAfricaBuffer;
class TcmsHMIAfricaBuffer;
class TcmsAfricaTimeBuffer;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
     MainWindow(const char *pszNamePtr, int iWidth, int iHeight, int iPosX, int iPosY);
    ~MainWindow();

     void initForm(void);

private slots:
     void updateSlot();

private:
     bool                 m_bRefreshAlltop;
     bool                 m_bRefreshGeneral;

     QTimer              *m_pUpdateTimer;
     PageAlltop          *m_pPageAlltop;
     PageGeneral         *m_pPageGeneral;
     CXAbstractWidget    *m_pWidget;

     TcmsController       *m_pMvbController;
     TcmsAfricaBuffer     *m_pMvbAfricaBuffer;
     TcmsHMIAfricaBuffer  *m_pMvbHMIAfricaBuffer;
     TcmsAfricaTimeBuffer *m_pMvbAfricaTimeBuffer;

     Logic_Page_AllTop   *m_pLogic_PageAllTop;
};

#endif // MAINWINDOW_H

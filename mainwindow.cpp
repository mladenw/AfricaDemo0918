#include "mainwindow.h"
#include "pagealltop.h"
#include "pagegeneral.h"
#include "src/disphw32.h"
#include "src/windefs.h"
#include "tcmscomm/tcmscontroller.h"
#include "tcmscomm/tcmsAfricabuffer.h"
#include "tcmscomm/tcmsHMIAfricabuffer.h"
#include "tcmscomm/tcmsAfricaTimebuffer.h"
#include "Core/CXAbstractWidget.h"

MainWindow::MainWindow(const char *pszNamePtr, int iWidth, int iHeight, int iPosX, int iPosY) :
    m_pUpdateTimer(new QTimer(this))
{
    setFixedSize(iWidth, iHeight);
    move(iPosX, iPosY);
    setObjectName(QString::fromAscii(pszNamePtr));

    m_pWidget = new CXAbstractWidget(this, "PageMain", 640, 480, 0, 0);
    m_pPageAlltop  = new PageAlltop(m_pWidget, "PageAlltop", 640, 30, 0, 0);// 上端界面使用该类
    m_pPageGeneral = new PageGeneral(m_pWidget, "PageGeneral", 640, 450, 0, 0);// 中间界面使用该类
    m_pPageGeneral->setGeometry(0, 30, 640, 450);

    connect(m_pUpdateTimer, SIGNAL(timeout()), this, SLOT(updateSlot()));

    initForm();
}

MainWindow::~MainWindow()
{
    delete this;
    delete m_pPageAlltop;
    delete m_pPageGeneral;
    delete m_pMvbController;
    delete m_pLogic_PageAllTop;
    delete m_pMvbAfricaTimeBuffer;
}

void MainWindow::initForm()
{
    m_bRefreshAlltop   =  true;
    m_bRefreshGeneral  =  true;

    ENV_init();                                    //初始化底层驱动
    ENV_activateAutomaticBrightness(FALSE,0);      //关闭自动调节背光

    m_pMvbController = new TcmsController(this);
    m_pLogic_PageAllTop = new Logic_Page_AllTop(this);
    m_pMvbAfricaBuffer = new TcmsAfricaBuffer(this);
    m_pMvbHMIAfricaBuffer = new TcmsHMIAfricaBuffer(this);
    m_pMvbAfricaTimeBuffer = new TcmsAfricaTimeBuffer(this);

    m_pMvbController->setHMIAddress();
    m_pMvbController->setAfricaTimeBuffer(m_pMvbAfricaTimeBuffer);
    m_pMvbController->setAfricaBuffer(m_pMvbAfricaBuffer);
    m_pMvbController->setHMIAfricaBuffer(m_pMvbHMIAfricaBuffer);
    m_pLogic_PageAllTop->setAfricaBuffer(m_pMvbAfricaBuffer);
    m_pLogic_PageAllTop->setAfricaTimeBuffer(m_pMvbAfricaTimeBuffer);
    m_pPageAlltop->setPageLogic(m_pLogic_PageAllTop);
    m_pPageAlltop->setAfricaBuffer(m_pMvbAfricaBuffer);
    m_pPageAlltop->setAfricaTimeBuffer(m_pMvbAfricaTimeBuffer);
    m_pPageGeneral->setAfricaBuffer(m_pMvbAfricaBuffer);
    m_pPageGeneral->setContentBuffer(m_pMvbAfricaBuffer);

    m_pUpdateTimer->setInterval(500);
    m_pUpdateTimer->start();

    m_pMvbController->start();   // Start MVB communication
}

void MainWindow::updateSlot()
{
    if(m_bRefreshAlltop)
    {
        m_pPageAlltop->votedUpdate() ;
    }
    if(m_bRefreshGeneral)
    {
        m_pPageGeneral->votedUpdata() ;
        m_pPageGeneral->UpdatePage();
    }
}

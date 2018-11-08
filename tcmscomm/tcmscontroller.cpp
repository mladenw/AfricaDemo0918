#include "tcmscomm/mvb.h"
#include "tcmscontroller.h"
#include "tcmscomm/tcmsport.h"
#include "tcmscomm/tcmsAfricabuffer.h"
#include "tcmscomm/tcmsHMIAfricabuffer.h"
#include "tcmscomm/tcmsAfricaTimebuffer.h"

unsigned char gOptionOpto = 0; //ESD:1,EMD:0;

TcmsController::TcmsController(QObject *parent) :
    QObject(parent),
    m_running(false),
    m_pPort518(new TcmsPort(this, 0x518, false, 32, 256, AfricaPort)),
    m_pPort1F(new TcmsPort(this, 0x1F, false, 32, 256, AfricaTimePort)),
    m_pPort136(new TcmsPort(this, 0x136, false, 32, 256, AfricaPort)),
    m_pPort308(new TcmsPort(this, 0x308, false, 32, 256, AfricaPort)),
    m_pPort720(new TcmsPort(this, 0x720, false, 32, 256, AfricaPort)),
    m_pPort710(new TcmsPort(this, 0x710, false, 32, 256, AfricaPort)),
    m_pPort726(new TcmsPort(this, 0x726, false, 32, 256, AfricaPort)),
    m_pPort716(new TcmsPort(this, 0x716, false, 32, 256, AfricaPort)),
    m_pPort717(new TcmsPort(this, 0x717, false, 32, 256, AfricaPort)),
    m_pPort727(new TcmsPort(this, 0x727, false, 32, 256, AfricaPort)),
    m_pPortFD5(new TcmsPort(this, 0xFD5, false, 32, 256, AfricaPort)),
    m_pPort30A(new TcmsPort(this, 0x30A, false, 32, 256, AfricaPort))

{

}

TcmsController::~TcmsController()
{
    stop();
}

void TcmsController::setHMIAddress()
{
    m_pPortFD0 = new TcmsPort(this, 0xFD0, true, 32, 256, AfricaHMIPort);
}

void TcmsController::start()
{
    if(m_running)
        return;

    quint16 m_iNumberPort = 13;

    TYPE_LP_TS_CFG mvbCfg;
    TYPE_LP_PRT_CFG mvb_ts_cfg[m_iNumberPort];       //[i]i为几个通讯端口

    mvbCfg.pb_pit = 0xD0000000L;
    mvbCfg.pb_pcs = 0xD000C000L;
    mvbCfg.pb_prt = 0xD0004000L;
    mvbCfg.pb_frc = 0xD0008000L;
    mvbCfg.pb_def = 0;
    mvbCfg.ownership = 1;
    mvbCfg.ts_type = 1;
    mvbCfg.prt_addr_max = 4095;
    mvbCfg.prt_indx_max = 1023;           //4的倍数-1,最少是i x 4
    mvbCfg.prt_count = m_iNumberPort;
    mvbCfg.tm_start = 0xD0000000L;
    mvbCfg.mcm = 2;
    mvbCfg.msq_offset = 0;
    mvbCfg.mft_offset = 0;
    mvbCfg.line_cfg = 2;
    mvbCfg.reply_to = 1;
    mvbCfg.dev_addr = 0x0A;
    mvbCfg.p_prt_cfg = (UNSIGNED32) mvb_ts_cfg;

    mvb_ts_cfg[0].prt_addr = m_pPort518->address();
    mvb_ts_cfg[0].prt_indx = 4;                              //4的倍数
    mvb_ts_cfg[0].size     = m_pPort518->size();
    mvb_ts_cfg[0].type     = m_pPort518->isSrce() ? LP_CFG_SRCE : LP_CFG_SINK;

    mvb_ts_cfg[1].prt_addr = m_pPort1F->address();
    mvb_ts_cfg[1].prt_indx = 8;                              //4的倍数
    mvb_ts_cfg[1].size     = m_pPort1F->size();
    mvb_ts_cfg[1].type     = m_pPort1F->isSrce() ? LP_CFG_SRCE : LP_CFG_SINK;

    mvb_ts_cfg[2].prt_addr = m_pPort136->address();
    mvb_ts_cfg[2].prt_indx = 12;                              //4的倍数
    mvb_ts_cfg[2].size     = m_pPort136->size();
    mvb_ts_cfg[2].type     = m_pPort136->isSrce() ? LP_CFG_SRCE : LP_CFG_SINK;

    mvb_ts_cfg[3].prt_addr = m_pPort308->address();
    mvb_ts_cfg[3].prt_indx = 16;                              //4的倍数
    mvb_ts_cfg[3].size     = m_pPort308->size();
    mvb_ts_cfg[3].type     = m_pPort308->isSrce() ? LP_CFG_SRCE : LP_CFG_SINK;

    mvb_ts_cfg[4].prt_addr = m_pPort720->address();
    mvb_ts_cfg[4].prt_indx = 20;                              //4的倍数
    mvb_ts_cfg[4].size     = m_pPort720->size();
    mvb_ts_cfg[4].type     = m_pPort720->isSrce() ? LP_CFG_SRCE : LP_CFG_SINK;

    mvb_ts_cfg[5].prt_addr = m_pPort710->address();
    mvb_ts_cfg[5].prt_indx = 24;                              //4的倍数
    mvb_ts_cfg[5].size     = m_pPort710->size();
    mvb_ts_cfg[5].type     = m_pPort710->isSrce() ? LP_CFG_SRCE : LP_CFG_SINK;

    mvb_ts_cfg[6].prt_addr = m_pPort726->address();
    mvb_ts_cfg[6].prt_indx = 28;                              //4的倍数
    mvb_ts_cfg[6].size     = m_pPort726->size();
    mvb_ts_cfg[6].type     = m_pPort726->isSrce() ? LP_CFG_SRCE : LP_CFG_SINK;

    mvb_ts_cfg[7].prt_addr = m_pPort716->address();
    mvb_ts_cfg[7].prt_indx = 32;                              //4的倍数
    mvb_ts_cfg[7].size     = m_pPort716->size();
    mvb_ts_cfg[7].type     = m_pPort716->isSrce() ? LP_CFG_SRCE : LP_CFG_SINK;

    mvb_ts_cfg[8].prt_addr = m_pPortFD0->address();
    mvb_ts_cfg[8].prt_indx = 36;                              //4的倍数
    mvb_ts_cfg[8].size     = m_pPortFD0->size();
    mvb_ts_cfg[8].type     = m_pPortFD0->isSrce() ? LP_CFG_SRCE : LP_CFG_SINK;

    mvb_ts_cfg[9].prt_addr = m_pPort717->address();
    mvb_ts_cfg[9].prt_indx = 40;                              //4的倍数
    mvb_ts_cfg[9].size     = m_pPort717->size();
    mvb_ts_cfg[9].type     = m_pPort717->isSrce() ? LP_CFG_SRCE : LP_CFG_SINK;

    mvb_ts_cfg[10].prt_addr = m_pPort727->address();
    mvb_ts_cfg[10].prt_indx = 44;                              //4的倍数
    mvb_ts_cfg[10].size     = m_pPort727->size();
    mvb_ts_cfg[10].type     = m_pPort727->isSrce() ? LP_CFG_SRCE : LP_CFG_SINK;

    mvb_ts_cfg[11].prt_addr = m_pPortFD5->address();
    mvb_ts_cfg[11].prt_indx = 48;                              //4的倍数
    mvb_ts_cfg[11].size     = m_pPortFD5->size();
    mvb_ts_cfg[11].type     = m_pPortFD5->isSrce() ? LP_CFG_SRCE : LP_CFG_SINK;


    mvb_ts_cfg[12].prt_addr = m_pPort30A->address();
    mvb_ts_cfg[12].prt_indx = 52;                              //4的倍数
    mvb_ts_cfg[12].size     = m_pPort30A->size();
    mvb_ts_cfg[12].type     = m_pPort30A->isSrce() ? LP_CFG_SRCE : LP_CFG_SINK;

    if (::MVBCInit(&mvbCfg, 0) != MVB_NO_ERROR)
        return;

    m_pPortFD0->run();

    if (::MVBCStart(0) != MVB_NO_ERROR)
        return;

    m_pPort518->open();
    m_pPort1F->open();
    m_pPort136->open();
    m_pPort308->open();
    m_pPort720->open();
    m_pPort710->open();
    m_pPort726->open();
    m_pPort716->open();
    m_pPortFD0->open();
    m_pPort717->open();
    m_pPort727->open();
    m_pPortFD5->open();
    m_pPort30A->open();

    m_running = true;
    return;
}

void TcmsController::stop()
{
    if(!m_running)
        return;
    ::MVBCStop(0);

    m_pPort518->close();
    m_pPort1F->close();
    m_pPort136->close();
    m_pPort308->close();
    m_pPort720->close();
    m_pPort710->close();
    m_pPort726->close();
    m_pPort716->close();
    m_pPortFD0->close();
    m_pPort717->close();
    m_pPort727->close();
    m_pPortFD5->close();
    m_pPort30A->close();
    m_running = false;
}

void TcmsController::putAfricaTimeData(quint16 portAddress, const quint16 *buf)
{
    if(portAddress == m_pPort1F->address())
    {
        m_pMvbAfricaTimeBuffer->putAfricaTime(buf);
    }
}

void TcmsController::putAfricaData(quint16 portAddress, quint16 *buf)
{
    if(portAddress == m_pPort518->address()){
        m_pMvbAfricaBuffer->putPort518Data(buf);
    }else if(portAddress == m_pPort136->address()){
        m_pMvbAfricaBuffer->putPort136Data(buf);
    }else if(portAddress == m_pPort308->address()){
        m_pMvbAfricaBuffer->putPort308Data(buf);
    }else if(portAddress == m_pPort720->address()){
        m_pMvbAfricaBuffer->putPort720Data(buf);
    }else if(portAddress == m_pPort710->address()){
        m_pMvbAfricaBuffer->putPort710Data(buf);
    }else if(portAddress == m_pPort726->address()){
        m_pMvbAfricaBuffer->putPort726Data(buf);
    }else if(portAddress == m_pPort716->address()){
        m_pMvbAfricaBuffer->putPort716Data(buf);
    }else if(portAddress == m_pPort717->address()){
        m_pMvbAfricaBuffer->putPort717Data(buf);
    }else if(portAddress == m_pPort727->address()){
        m_pMvbAfricaBuffer->putPort727Data(buf);
    }else if(portAddress == m_pPortFD5->address()){
        m_pMvbAfricaBuffer->putPortFD5Data(buf);
    }else if(portAddress == m_pPort30A->address()){
        m_pMvbAfricaBuffer->putPort30AData(buf);
    }
}

void TcmsController::getSrceData(quint16 portAddress, quint16 *buf)
{
    if(portAddress == m_pPortFD0->address())
    {
        m_pHMIAfricaBUffer->getHMI_Content(buf);
    }

    return ;
}

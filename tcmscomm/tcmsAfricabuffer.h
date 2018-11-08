#ifndef TCMSAFRICABUFFER_H
#define TCMSAFRICABUFFER_H

#include <QObject>
#include <QTimer>

class TcmsAfricaBuffer : public QObject
{
    Q_OBJECT
public:
    explicit TcmsAfricaBuffer(QObject *parent = 0);

    void reset();

    void putPort518Data(const quint16 *buf);
    void putPort136Data(const quint16 *buf);
    void putPort308Data(const quint16 *buf);
    void putPort720Data(const quint16 *buf);
    void putPort710Data(const quint16 *buf);
    void putPort726Data(const quint16 *buf);
    void putPort716Data(const quint16 *buf);
    void putPortFD0Data(const quint16 *buf);
    void putPort717Data(const quint16 *buf);
    void putPort727Data(const quint16 *buf);
    void putPortFD5Data(const quint16 *buf);
    void putPort30AData(const quint16 *buf);

    quint16 getLocoNumber();
    qint16  getBP_Pressure();
    quint16 getLocoSpeed();
    qint16  getLocoAcc();
    qint16  getTracEffort();
    quint8  getNotch();
    qint16  getMR_Pressure();
    qint16  getER_Pressure();
    qint16  getBC_Pressure();
    quint16 getVoltage();
    quint16 getCurrent();
    qint32  getEngineSpeed1();
    qint32  getEngineSpeed2();
    qint32  getEnginePower1();
    qint32  getEnginePower2();
    quint16 getMileageFlag();
    quint32 getMileageValue();
    quint8  getAfricaLife();
    quint8  getGWLifesignal2(); // 717Port
    quint8  getGWLifesignal1(); // 727Port
    quint8  getm_iGWmaster2();  // 717Port 主从标识
    quint8  getm_iGWmaster1();  // 727Port 主从标识
    quint8  getLocoMode();
    //返回CUU-HMI的各种生命信号
    bool getAfricaPort717_Status_Life();
    bool getAfricaPort727_Status_Life();
    bool getVCU_Status_Life();
    bool getBCU_Status_Life();
private slots:
    void Port717_Status_Life_Timeout(){m_bAfricaPort717_Status_Life_CommNormal = false;}
    void Port727_Status_Life_Timeout(){m_bAfricaPort727_Status_Life_CommNormal = false;}
    void PortVCU_Status_Life_Timeout(){m_bVCUOnline = false;}
    void PortBCU_Status_Life_Timeout(){m_bBCUOnline = false;}

private:
    //生命信号定时器
    QTimer *m_updataAfricaPort727_Status_Life_TimerPtr;
    QTimer *m_updataAfricaPort717_Status_Life_TimerPtr;
    QTimer *m_VCUonline_TimerPtr;
    QTimer *m_BCUonline_TimerPtr;

    quint16 m_iLocoNumber;
    qint16  m_iBP_Pressure;
    quint16 m_iLocoSpeed;
    qint16  m_iLocoAcc;
    qint16  m_iTracEffort;
    quint8  m_iNotch;
    qint16  m_iMR_Pressure;
    qint16  m_iER_Pressure;
    qint16  m_iBC_Pressure;
    quint16 m_iVoltage;
    quint16 m_iCurrent;
    quint16 m_iMileageFlag;
    quint32 m_iMileageValue;
    qint32  m_iEngineSpeed1;
    qint32  m_iEngineSpeed2;
    qint32  m_iEnginePower1;
    qint32  m_iEnginePower2;
    quint8  m_iAfricaLife;
    quint8  m_iGWmaster2;     //717Port 主从标识
    quint8  m_iGWmaster1;     //727Port 主从标识
    quint8  m_iLocoMode;
    //端口生命信号
    quint8 m_iAfricaPort717_Status_Life;
    quint8 m_iAfricaPort727_Status_Life;
    quint8 m_iVCUtoALL_Life;
    quint8 m_iBCUtoVCU_Life;
    //生命信号超时状态
    bool m_bAfricaPort727_Status_Life_CommNormal;
    bool m_bAfricaPort717_Status_Life_CommNormal;
    bool m_bVCUOnline;
    bool m_bBCUOnline;
    //端口数据指针
    const quint16 *m_iPort518_buf;
    const quint16 *m_iPort136_buf;
    const quint16 *m_iPort308_buf;
    const quint16 *m_iPort720_buf;
    const quint16 *m_iPort710_buf;
    const quint16 *m_iPort726_buf;
    const quint16 *m_iPort716_buf;
    const quint16 *m_iPortFD0_buf;
    const quint16 *m_iPortFD5_buf;
    const quint16 *m_iPort30A_buf;

    quint16 m_Port518_age;
};

#endif // TCMSAFRICABUFFER_H

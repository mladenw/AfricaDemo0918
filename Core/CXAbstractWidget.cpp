#include "CXAbstractWidget.h"

CXAbstractWidget::CXAbstractWidget(QWidget *parent, const char *pszNamePtr, int iWidth, int iHeight, int iPosX, int iPosY):
    QWidget(parent)
{
    setFixedSize(iWidth, iHeight);
    move(iPosX, iPosY);
    setObjectName(QString::fromAscii(pszNamePtr));
}

CXAbstractWidget::~CXAbstractWidget()
{

}

void CXAbstractWidget::setInv()
{
    if(!this->isVisible())
        return;
    this->setVisible(false);
}

void CXAbstractWidget::setVis()
{
    if(this->isVisible())
        return;
    this->setVisible(true);
}

void CXAbstractWidget::setVisibility(bool isOn)
{
    if((this->isVisible()) && (isOn))
        return;
    this->setVisible(isOn);
}

bool CXAbstractWidget::getVisibility()
{
    return this->isVisible();
}

void CXAbstractWidget::setPos(int x, int y)
{
    this->move(x, y);
}

QString CXAbstractWidget::widgetName() const
{
    return this->objectName();
}

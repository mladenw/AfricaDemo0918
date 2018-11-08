#ifndef CXABSTRACTWIDGET_H
#define CXABSTRACTWIDGET_H

#include <QWidget>
#include <QtGui>
#include <QString>

class CXAbstractWidget : public QWidget
{
    Q_OBJECT
public:
    CXAbstractWidget(QWidget *parent, const char *pszNamePtr, int iWidth, int iHeight, int iPosX, int iPosY);
    ~CXAbstractWidget();

public slots:

    void setInv();
    void setVis();
    void setVisibility(bool isOn);

    bool getVisibility();

    void setPos(int x, int y);
    QString widgetName () const;

protected:


private:

};

#endif // CXABSTRACTWIDGET_H

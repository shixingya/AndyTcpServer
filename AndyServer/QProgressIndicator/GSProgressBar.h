#pragma once
#include "preheader.h"

#include "QProgressBar"
class GSProgressBar : public QProgressBar
{
  Q_OBJECT
public:
    GSProgressBar(QWidget * parent = 0, int minRange = 0, int maxRange = 30, int nWidth = 450, int nHeight = 30);
    virtual ~GSProgressBar();

    //注意，需要跨线程调用
    Q_INVOKABLE void UpdateProgress(int APos);
    Q_INVOKABLE void GotoNextStep();   //前进一步
    Q_INVOKABLE void UpdatePrompt(QString qsText);
    Q_INVOKABLE void SetMaxRange(int maxRange);
    Q_INVOKABLE void ShowImmediately();        //显示进度条(调用刷新操作，防止进度条不出现)

protected:
    virtual void showEvent(QShowEvent *e) override;
    virtual void hideEvent(QHideEvent *e) override;

private:
    int m_nOneStepValue;
    int m_nCurrentStep;
    int m_nCurrentPos;
    int m_nCount;
};

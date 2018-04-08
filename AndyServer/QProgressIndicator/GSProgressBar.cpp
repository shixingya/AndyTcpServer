#include "GSProgressBar.h"
const int CTotalSteps = 50;  //进度条更新的步数

GSProgressBar::GSProgressBar( QWidget * parent /*= 0*/, int minRange /*= 0*/, int maxRange /*= 30*/,
                               int nWidth /*= 450*/, int nHeight /*= 30*/ )
    : QProgressBar(parent)
    , m_nCount(0)
{


    setRange(minRange, maxRange);
    setFixedSize(nWidth, nHeight);


    if(parent ==0)
    {
        setAlignment(Qt::AlignVCenter);
        setWindowFlags(Qt::ToolTip);
        window()->setWindowModality(Qt::ApplicationModal);
        //把进度条放在屏幕中心
        QDesktopWidget* desktopWidget = QApplication::desktop();
        QRect applicationRect = desktopWidget->availableGeometry(desktopWidget->screenNumber(QCursor::pos()));
        int x = applicationRect.x() + applicationRect.width() / 2 - nWidth / 2;
        int y = applicationRect.y() + applicationRect.height() / 2 - nHeight / 2 + 50;
        setGeometry(x, y, nWidth, nHeight);
    }


    m_nOneStepValue = maxRange / CTotalSteps + 1;
    m_nCurrentStep = 0;
    m_nCurrentPos = 0;
    this->setStyleSheet("QProgressBar{ \
                        background:#B8BCBF;\
                        color: #FFFFFF;  \
                        text-align:center;\
                        border: 0px solid grey;\
                        border-radius: 5px;\
                        }\
                        QProgressBar::chunk {\
                        background:#37A4F5;\
                        color: #FFFFFF;  \
                        border: 0px solid grey;\
                        border-radius: 5px;\
                        }\
                        ");
}


GSProgressBar::~GSProgressBar()
{

}

void GSProgressBar::showEvent(QShowEvent *e)
{
    window()->setWindowModality(Qt::ApplicationModal);
    QProgressBar::showEvent(e);
}

void GSProgressBar::hideEvent(QHideEvent *e)
{
    window()->setWindowModality(Qt::NonModal);
    QProgressBar::hideEvent(e);
}

void GSProgressBar::UpdateProgress(int APos )
{
    if (APos == -1)
    {
        ++m_nCurrentPos;
        ++m_nCount;
    }
    else
    {
        m_nCount += APos - m_nCurrentPos;
        m_nCurrentPos = APos;
    }

    if ((m_nCurrentPos >= minimum()) && (m_nCurrentPos <= maximum()))
    {
        if((m_nCount >= m_nOneStepValue) || (m_nCurrentPos == minimum()))
        {
            setValue(m_nCurrentPos);
            m_nCount = 0;
            m_nCurrentStep++;
        }
    }
}

void GSProgressBar::GotoNextStep()
{
    m_nCurrentStep++;
    if(m_nCurrentStep <= CTotalSteps)
    {
        int nPos = m_nCurrentStep * m_nOneStepValue;
        setValue(nPos);
    }
}

void GSProgressBar::SetMaxRange( int maxRange)
{
    reset();
    if (maxRange == 0)
    {
        setRange(0,0);
        reset();
        QApplication::processEvents();
    }
    else
        setMaximum(maxRange);
    m_nCurrentStep = 0;
    m_nCount = 0;
    m_nOneStepValue = maxRange / CTotalSteps + 1;
}

void GSProgressBar::UpdatePrompt( QString qsText )
{
    setFormat(qsText);
}

void GSProgressBar::ShowImmediately()
{
    show();
    QApplication::processEvents();
}



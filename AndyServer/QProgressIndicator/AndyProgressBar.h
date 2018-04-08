#include "preheader.h"
#include "./GSProgressBar.h"
namespace Ui {
class AndyProgressBar;
}

class AndyProgressBar : public QWidget
{
    Q_OBJECT

public:
    explicit AndyProgressBar(QWidget *parent = 0);
    ~AndyProgressBar();

    void SetFileName(QString);
    void SetMaxRange(int) ;
    void UpdateProgress(int) ;
    void UpdatePrompt(QString) ;
private:
    Ui::AndyProgressBar *ui;
    GSProgressBar progressBar;

public slots:
    void on_UpdatePercent(int);
    void on_UpdateMaximum(int);
    void on_UpdateText(QString);
};

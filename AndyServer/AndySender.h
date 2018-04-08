#pragma once
#include "preheader.h"

namespace Ui {
class AndySender;
}

class AndySender : public QWidget
{
    Q_OBJECT

public:
    explicit AndySender(QWidget *parent = 0);
    ~AndySender();

private slots:
    void on_pbt_selectFile_clicked();
    void on_UpdatePercent();
private:
    Ui::AndySender *ui;
};

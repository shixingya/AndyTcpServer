#include "AndyProgressBar.h"
#include "ui_AndyProgressBar.h"


AndyProgressBar::AndyProgressBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AndyProgressBar)
{
    ui->setupUi(this);
    ui->hl_content->addWidget(&progressBar);

    progressBar.SetMaxRange(100);
    progressBar.UpdateProgress(20);
    progressBar.ShowImmediately();
}

AndyProgressBar::~AndyProgressBar()
{
    delete ui;
}
void AndyProgressBar::SetMaxRange(int val)
{
    progressBar.SetMaxRange(val);
}
void AndyProgressBar::UpdateProgress(int val)
{
    progressBar.UpdateProgress(val);
}
void AndyProgressBar::UpdatePrompt(QString str)
{
    progressBar.UpdatePrompt(str);
}
void AndyProgressBar::SetFileName(QString str)
{
    ui->label->setText(str);
}

void AndyProgressBar::on_UpdatePercent(int val)
{
    UpdateProgress(val);
}
void AndyProgressBar::on_UpdateMaximum(int val)
{
    SetMaxRange(val);
}
void AndyProgressBar::on_UpdateText(QString str)
{
    UpdatePrompt(str);
}

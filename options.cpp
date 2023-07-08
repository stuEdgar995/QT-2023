#include "options.h"
#include "ui_options.h"

Options::Options(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Options)
{
    ui->setupUi(this);
}

Options::~Options()
{
    delete ui;
}


void Options::on_BackButton_clicked()
{
    Config* config = new Config();
    config->visible = ui->VisiblecheckBox->isChecked();
    config->prop_time = ui->ProTimespinBox->value();
    config->end_score = ui->EndScorespinBox->value();
    emit signalConfig(config);
    accept();
}


void Options::on_VisiblecheckBox_clicked()
{

}


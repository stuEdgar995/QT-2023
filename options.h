#ifndef OPTIONS_H
#define OPTIONS_H

#include <QDialog>
#include "utils.h"

namespace Ui {
class Options;
}

class Options : public QDialog
{
    Q_OBJECT

public:
    explicit Options(QWidget *parent = nullptr);
    ~Options();

signals:
    void signalConfig(Config* config);

private slots:

    void on_BackButton_clicked();

    void on_VisiblecheckBox_clicked();

private:
    Ui::Options *ui;
};

#endif // OPTIONS_H

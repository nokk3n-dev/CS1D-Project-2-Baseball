#ifndef STARTPAGE_H
#define STARTPAGE_H

#include <QDialog>

namespace Ui {
class StartPage;
}

class StartPage : public QDialog
{
    Q_OBJECT

public:
    explicit StartPage(QWidget *parent = nullptr);
    ~StartPage();

private:
    Ui::StartPage *ui;
};

#endif // STARTPAGE_H

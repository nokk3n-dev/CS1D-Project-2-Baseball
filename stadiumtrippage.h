#ifndef STADIUMTRIPPAGE_H
#define STADIUMTRIPPAGE_H

#include <QDialog>

namespace Ui {
class StadiumTripPage;
}

class StadiumTripPage : public QDialog
{
    Q_OBJECT

public:
    explicit StadiumTripPage(QWidget *parent = nullptr);
    ~StadiumTripPage();
    void setTrip(const QString tripType);
private:
    Ui::StadiumTripPage *ui;
};

#endif // STADIUMTRIPPAGE_H

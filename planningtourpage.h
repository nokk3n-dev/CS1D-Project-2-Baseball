#ifndef PLANNINGTOURPAGE_H
#define PLANNINGTOURPAGE_H

#include <QDialog>

namespace Ui {
class planningTourPage;
}

class planningTourPage : public QDialog
{
    Q_OBJECT

public:
    explicit planningTourPage(QWidget *parent = nullptr);
    ~planningTourPage();

private slots:
    void on_kruskal_clicked();

    void on_prims_clicked();

    void on_shortest_path_clicked();

private:
    Ui::planningTourPage *ui;
};

#endif // PLANNINGTOURPAGE_H

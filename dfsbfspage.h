#ifndef DFSBFSPAGE_H
#define DFSBFSPAGE_H

#include <QDialog>

namespace Ui {
class DfsBfsPage;
}

class DfsBfsPage : public QDialog
{
    Q_OBJECT

public:
    explicit DfsBfsPage(QWidget *parent = nullptr);
    ~DfsBfsPage();

    void DFS();
    void BFS();

private:
    Ui::DfsBfsPage *ui;
};

#endif // DFSBFSPAGE_H

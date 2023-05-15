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

private slots:
    void on_dfs_button_clicked();

    void on_bfs_button_clicked();

private:
    Ui::DfsBfsPage *ui;
};

#endif // DFSBFSPAGE_H

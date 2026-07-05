#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "filescontroller.h"
#include "searchcontroller.h"

#include <QMainWindow>

#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class QActionGroup;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow* ui;

    void setupActions();
    void setupConnections();

    void selectRootDirectory();

    // slots

    void searchClicked();
    void resetClicked();
    void queryEntered();
    void queryChanged(const QString& query);
    void rootDirectoryChanged(const QString& rootDirectory);
    void setQueryState();
    void setRootDirectoryState();

    QActionGroup* actionGroup_{nullptr};

    SearchController searchController_;

    FilesController filesController_;
};
#endif // MAINWINDOW_H

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QActionGroup>
#include <QDebug>
#include <QFileDialog>

#include <filesystem>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setupActions();
    setupConnections();

    filesController_.setList(ui->files);
    searchController_.setFilesController(&filesController_);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupConnections()
{
    // actions

    connect(ui->actionBlockingSearch, &QAction::triggered,
            []() -> void { qDebug() << "Blocking Search triggered"; });
    connect(ui->actionNonBlockingSearch, &QAction::triggered,
            []() -> void { qDebug() << "Non-Blocking Search triggered"; });
    connect(ui->actionParallelSearch, &QAction::triggered,
            []() -> void { qDebug() << "Parallel Search triggered"; });
    connect(ui->actionAbout, &QAction::triggered,
            []() -> void { qDebug() << "About action triggered"; });

    connect(ui->actionRootDirectory, &QAction::triggered,
            [this]() -> void { this->selectRootDirectory(); });


    auto children = ui->query->findChildren<QAction*>();

    if (!children.isEmpty()) {
        connect(children.first(), &QAction::triggered, this, [this]() {
            qDebug() << "Query clear button clicked: " << ui->query->text();
        });
    }

    // buttons


    // connect(ui->resetButton, &QPushButton::clicked, this,
    //         &MainWindow::resetClicked);

    connect(ui->searchButton, &QPushButton::clicked, this,
            &MainWindow::searchClicked);

    // query

    connect(ui->query, &QLineEdit::returnPressed, this,
            &MainWindow::queryEntered);

    connect(ui->query, &QLineEdit::textChanged, this,
            &MainWindow::queryChanged);
    connect(ui->rootDirectory, &QLineEdit::textChanged, this,
            &MainWindow::rootDirectoryChanged);
}

void MainWindow::selectRootDirectory()
{
    namespace fs = std::filesystem;
    const auto root{fs::current_path().root_path()};
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setDirectory(QString::fromStdString(root));
    if (dialog.exec())
    {
        const QDir directory = dialog.directory();
        ui->rootDirectory->setText(directory.absolutePath());
        ui->rootDirectory->home(false);
    }
}

void MainWindow::searchClicked()
{
    searchController_.search();
}

void MainWindow::resetClicked()
{
    qDebug() << "Reset clicked";
}

void MainWindow::queryEntered()
{
    const QString query = ui->query->text();
    searchController_.setQuery(query);
}

void MainWindow::queryChanged(const QString& query)
{
    qDebug() << "Query changed: " << query;

    // ui->resetButton->setEnabled(!query.isEmpty());
    ui->searchButton->setEnabled(!query.isEmpty());
}

void MainWindow::rootDirectoryChanged(const QString& rootDirectory)
{
    ui->query->setEnabled(!rootDirectory.isEmpty());
    searchController_.setRootDirectory(rootDirectory);
}

void MainWindow::setupActions()
{
    actionGroup_ = new QActionGroup(this);
    actionGroup_->addAction(ui->actionBlockingSearch);
    actionGroup_->addAction(ui->actionNonBlockingSearch);
    actionGroup_->addAction(ui->actionParallelSearch);
    ui->actionBlockingSearch->setChecked(true);
}

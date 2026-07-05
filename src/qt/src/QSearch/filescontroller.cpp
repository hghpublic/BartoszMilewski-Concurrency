#include "filescontroller.h"


#include <QListWidget>

FilesController::FilesController() {}

void FilesController::clear()
{
    if (!list_)
    {
        return;
    }

    std::scoped_lock lock(mtx_);
    list_->clear();
}

void FilesController::addFiles(const QStringList& files)
{
    if (!list_)
    {
        return;
    }

    std::scoped_lock lock(mtx_);
    list_->addItems(files);
}

void FilesController::setList(QListWidget* list)
{
    list_ = list;
    clear();
}

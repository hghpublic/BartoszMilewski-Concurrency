#include "searchcontroller.h"

#include <QDebug>

SearchController::SearchController() {}

void SearchController::setRootDirectory(QString rootDirectory)
{
    qDebug() << "setRootDirectory: " << rootDirectory;

    rootDirectory_ = rootDirectory;
}

auto SearchController::getRootDirectory() const -> QString
{
    return rootDirectory_;
}

void SearchController::setQuery(QString query)
{
    qDebug() << "setQuery: " << query;

    query_ = query;
}

auto SearchController::getQuery() const -> QString
{
    return query_;
}

void SearchController::setSearchType(SearchType searchType) {}

auto SearchController::getSearchType() const -> SearchType
{
    return searchType_;
}

void SearchController::setFilesController(FilesController* filesController)
{
    filesController_ = filesController;
}

void SearchController::search()
{
    qDebug() << "search";

    QStringList files;
    for (int i = 0; i < 10; ++i)
    {
        files << QString("file %1").arg(i);
    }

    filesController_->addFiles(files);
}

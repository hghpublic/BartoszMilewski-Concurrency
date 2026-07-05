#ifndef SEARCHCONTROLLER_H
#define SEARCHCONTROLLER_H

#include "filescontroller.h"
#include <QString>

#include <vector>

enum class SearchType : int
{
    Blocking,
    NonBlocking,
    Parallel
};

class SearchController
{
public:
    SearchController();

    void setRootDirectory(QString rootDirectory);
    [[nodiscard]] auto getRootDirectory() const -> QString;

    void setQuery(QString query);
    [[nodiscard]] auto getQuery() const -> QString;

    void setSearchType(SearchType searchType);
    [[nodiscard]] auto getSearchType() const -> SearchType;

    void setFilesController(FilesController* filesController);

    void search();

private:
    QString rootDirectory_;
    QString query_;
    std::vector<QString> results_;
    SearchType searchType_{SearchType::Blocking};
    FilesController* filesController_{nullptr};
};

#endif // SEARCHCONTROLLER_H

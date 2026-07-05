#ifndef FILESCONTROLLER_H
#define FILESCONTROLLER_H

#include <QtCore/qcontainerfwd.h>
#include <mutex>

class QListWidget;
class FilesController
{
public:
    explicit FilesController();
    void clear();
    void addFiles(const QStringList& files);
    void setList(QListWidget* list);

private:
    QListWidget* list_{nullptr};
    std::mutex mtx_;
};

#endif // FILESCONTROLLER_H
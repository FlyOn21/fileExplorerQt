#include "custom_filesystem_model.h"
#include <QFileInfo>
#include <QFileIconProvider>


CustomFileSystemModel::CustomFileSystemModel(QObject *parent)
    : QFileSystemModel(parent) {

}


void CustomFileSystemModel::setFolderOpen(const QString &path, bool open) {
    if (open) {
        openFolders.insert(path);
    } else {
        openFolders.remove(path);
    }
}

QVariant CustomFileSystemModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) {
        return QVariant();
    }

    QFileInfo fileInfo = this->fileInfo(index);
    if (role == Qt::DecorationRole && index.column() == 0) {
        if (fileInfo.isDir()) {
            if (openFolders.contains(fileInfo.filePath())) {
                return QIcon(":/icons/opened_folder.png");
            }
            return QIcon(":/icons/folder.png");
        } else {
            return QIcon(":/icons/file.png");
        }
    }

    return QFileSystemModel::data(index, role);
}

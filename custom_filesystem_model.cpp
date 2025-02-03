
#include "custom_filesystem_model.h"
#include <QFileInfo>

CustomFileSystemModel::CustomFileSystemModel(QObject *parent)
    : QFileSystemModel(parent) {}

QVariant CustomFileSystemModel::data(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole && index.column() == 0) {

        QFileInfo fileInfo = this->fileInfo(index);
        if (fileInfo.isDir()) {
            return QString("[DIR] %1").arg(fileInfo.fileName());
        } else {
            return QString("%1 (%2 KB)").arg(fileInfo.fileName()).arg(fileInfo.size() / 1024);
        }
    }
    return QFileSystemModel::data(index, role);
}

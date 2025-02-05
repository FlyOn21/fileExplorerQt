#ifndef CUSTOM_FILESYSTEM_MODEL_H
#define CUSTOM_FILESYSTEM_MODEL_H

#include <QFileSystemModel>
#include <QSet>


class CustomFileSystemModel : public QFileSystemModel
{
    Q_OBJECT

public:
    explicit CustomFileSystemModel(QObject *parent = nullptr);
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    void setFolderOpen(const QString &path, bool open);


private:
    QSet<QString> openFolders;

};

#endif // CUSTOM_FILESYSTEM_MODEL_H

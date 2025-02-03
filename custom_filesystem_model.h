#ifndef CUSTOM_FILESYSTEM_MODEL_H
#define CUSTOM_FILESYSTEM_MODEL_H

#include <QFileSystemModel>

class CustomFileSystemModel : public QFileSystemModel
{
    Q_OBJECT

public:
    explicit CustomFileSystemModel(QObject *parent = nullptr);
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

signals:

};

#endif // CUSTOM_FILESYSTEM_MODEL_H

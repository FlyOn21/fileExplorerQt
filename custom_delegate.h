#ifndef CUSTOM_DELEGATE_H
#define CUSTOM_DELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>

class CustomDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit CustomDelegate(QObject *parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // CUSTOM_DELEGATE_H

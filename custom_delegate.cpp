#include "custom_delegate.h"
#include <QPainter>
#include <QFileSystemModel>

CustomDelegate::CustomDelegate(QObject *parent)
    : QStyledItemDelegate(parent) {}

void CustomDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    if (!index.isValid()) return;

    painter->save();
    QRect rect = option.rect;

    const QFileSystemModel *model = static_cast<const QFileSystemModel *>(index.model());
    QFileInfo fileInfo = model->fileInfo(index);
    QString displayText = index.data(Qt::DisplayRole).toString();

    if (option.state & QStyle::State_Selected) {
        painter->fillRect(option.rect, option.palette.highlight());
        painter->setPen(option.palette.highlightedText().color());
    } else {
        if (fileInfo.isDir()) {
            painter->setPen(Qt::blue);
        } else {
            painter->setPen(Qt::darkGreen);
        }
    }

    painter->drawText(rect.adjusted(5, 0, -5, 0), Qt::AlignVCenter | Qt::AlignLeft, displayText);
    painter->restore();
}

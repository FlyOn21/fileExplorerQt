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
    QIcon icon = index.data(Qt::DecorationRole).value<QIcon>();

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
    QSize iconSize = QSize(16, 16);
    QRect iconRect = QRect(rect.left()+5, rect.center().y() - iconSize.height() / 2, iconSize.width(), iconSize.height());
    icon.paint(painter, iconRect);

    QRect textRect = rect.adjusted(iconSize.width() + 10, 0, -5, 0);
    painter->drawText(textRect, Qt::AlignVCenter | Qt::AlignLeft, displayText);
    painter->restore();
}

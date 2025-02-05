#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeView>
#include <QTableView>
#include <QFile>
#include <QTextStream>
#include <QStandardItemModel>
#include <QTextEdit>
#include "custom_filesystem_model.h"
#include "custom_delegate.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onFileSelected(const QModelIndex &index);
    void onFolderExpanded(const QModelIndex &index);
    void onFolderCollapsed(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    CustomFileSystemModel *model;
    CustomDelegate *delegate;
    QStandardItemModel *fileModel;
};

#endif // MAINWINDOW_H




#include <QApplication>
#include <QTreeView>
#include <QFileSystemModel>
#include <QSysInfo>
#include <QTableView>
#include "custom_filesystem_model.cpp"
#include "custom_delegate.cpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QString osName = QSysInfo::prettyProductName();
    qDebug() << "Запуск на ОС:" << osName;

    CustomFileSystemModel *model = new CustomFileSystemModel;
    model->setRootPath(QDir::homePath());
    qDebug()<< QDir::homePath();
    // model->setFilter(QDir::NoDotAndDotDot | QDir::Files | QDir::Dirs);
    // model->setNameFilters(QStringList() << "*.txt" << "*.cpp");
    model->setNameFilterDisables(false);

    QTreeView *treeView = new QTreeView;
    treeView->setModel(model);
    treeView->setColumnWidth(0, 400);
    treeView->setRootIndex(model->index(QDir::homePath()));
    treeView->resize(800, 600);

    QTableView *tableView = new QTableView();


    CustomDelegate *delegate = new CustomDelegate(treeView);
    treeView->setItemDelegate(delegate);

    treeView->show();

    return app.exec();
}

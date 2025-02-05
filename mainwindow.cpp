#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QMimeDatabase>
#include <QMimeType>
#include <QSplitter>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    model = new CustomFileSystemModel(this);
    model->setRootPath(QDir::homePath());
    model->setFilter(QDir::NoDotAndDotDot | QDir::Files | QDir::Dirs);
    model->setNameFilterDisables(false);

    ui->treeView->setModel(model);
    ui->treeView->setColumnWidth(0, 250);
    ui->treeView->setRootIndex(model->index(QDir::homePath()));


    delegate = new CustomDelegate(this);
    ui->treeView->setItemDelegate(delegate);

    fileModel = new QStandardItemModel(this);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setStyleSheet(R"(
    QTableView {
        background-color: #f8f9fa;
        border: 1px solid #d1d5db;
        border-radius: 8px;
        gridline-color: transparent;
        selection-background-color: #4a90e2;
        selection-color: white;
    }

    QTableView::item {
        padding: 8px;
        border: none;
    }

    QHeaderView::section {
        background-color: #4a90e2;
        color: white;
        font-weight: bold;
        padding: 8px;
        border: none;
        border-bottom: 2px solid #2c6cb3;
    }

    QTableView::item:selected {
        background-color: #4a90e2;
        color: white;
    }

    QTableView::item:hover {
        background-color: #e3f2fd;
    }

    QTableView::corner {
        background-color: #4a90e2;
    }
)");
    ui->tableView->setModel(fileModel);

    QSplitter *splitter = new QSplitter(Qt::Horizontal, this);
    splitter->addWidget(ui->treeView);
    splitter->addWidget(ui->tableView);
    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 2);
    setCentralWidget(splitter);


    connect(ui->treeView, &QTreeView::clicked, this, &MainWindow::onFileSelected);
    connect(ui->treeView, &QTreeView::expanded, this, &MainWindow::onFolderExpanded);
    connect(ui->treeView, &QTreeView::collapsed, this, &MainWindow::onFolderCollapsed);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onFolderExpanded(const QModelIndex &index) {
    model->setFolderOpen(model->filePath(index), true);
}

void MainWindow::onFolderCollapsed(const QModelIndex &index) {
    model->setFolderOpen(model->filePath(index), false);
}

void MainWindow::onFileSelected(const QModelIndex &index) {
    if (!fileModel) {
        qDebug() << "File model is not initialized!";
        return;
    }

    QFileInfo fileInfo = model->fileInfo(index);
    if (fileInfo.isFile()) {

        qDebug() << "Selected file: " << fileInfo.filePath();

        QFile file(fileInfo.filePath());
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::warning(this, "Error", "Cannot open file: " + file.errorString());
            return;
        }
        QMimeDatabase mimeDb;
        QMimeType mimeType = mimeDb.mimeTypeForFile(fileInfo);
        qDebug() << mimeType;
        QList<QString> allowMime = {"xml", "x-shellscript"};
        QString mimeName = mimeType.name();
        QStringList parts = mimeName.split('/');

        if (mimeName.startsWith("application/") && (parts.size() < 2 || !allowMime.contains(parts[1]))) {
            QMessageBox::warning(this, "Unsupported File",
                                 "Cannot open binary files. Maybe in a future version.");
            return;
        }

        QTextStream in(&file);
        QStringList lines;
        while (!in.atEnd()) {
            lines.append(in.readLine());
        }

        file.close();

        fileModel->clear();
        fileModel->setColumnCount(1);
        fileModel->setHorizontalHeaderLabels({fileInfo.fileName()});

        for (const QString &line : lines) {
            QList<QStandardItem *> rowItems;
            rowItems.append(new QStandardItem(line));
            fileModel->appendRow(rowItems);
        }


    } else {
        qDebug() << "Selected dir: " << fileInfo.filePath();
    }
}

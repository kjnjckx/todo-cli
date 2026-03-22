#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "task.h"
#include <QListWidgetItem>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 启动时加载任务
    loadTasks();
    refreshTaskList();

    // 连接信号和槽
    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::onAddTask);
    connect(ui->taskListWidget, &QListWidget::itemChanged, this, &MainWindow::onTaskItemChanged);
}

MainWindow::~MainWindow()
{
    // 退出时保存任务
    saveTasks();
    delete ui;
}

void MainWindow::refreshTaskList()
{
    ui->taskListWidget->clear();

    for (const auto& t : tasks) {
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(t.title));
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(t.done ? Qt::Checked : Qt::Unchecked);
        item->setData(Qt::UserRole, t.id);  // 把 id 存在 item 里
        ui->taskListWidget->addItem(item);
    }
}

void MainWindow::onAddTask()
{
    QString title = ui->inputEdit->text().trimmed();
    if (title.isEmpty()) {
        QMessageBox::warning(this, "提示", "任务内容不能为空");
        return;
    }

    int newId = tasks.empty() ? 1 : tasks.back().id + 1;
    Task t{newId, title.toStdString(), false};
    tasks.push_back(t);

    ui->inputEdit->clear();
    refreshTaskList();
    saveTasks();
}

void MainWindow::onTaskItemChanged(QListWidgetItem* item)
{
    if (item->checkState() == Qt::Checked) {
        int id = item->data(Qt::UserRole).toInt();

        // 从 tasks 里删除这个任务
        for (auto it = tasks.begin(); it != tasks.end(); ++it) {
            if (it->id == id) {
                tasks.erase(it);
                break;
            }
        }

        refreshTaskList();
        saveTasks();
    }
}
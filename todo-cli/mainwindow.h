#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onAddTask();           // 点击"添加任务"按钮
    void onTaskItemChanged(QListWidgetItem* item);  // 勾选任务时触发

private:
    Ui::MainWindow *ui;
    void refreshTaskList();     // 刷新列表显示
};

#endif // MAINWINDOW_H
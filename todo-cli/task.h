#ifndef TASK_H
#define TASK_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>

struct Task {
    int id;
    std::string title;
    bool done;
};

// 全局任务列表
extern std::vector<Task> tasks;

// 文件操作
void loadTasks();
void saveTasks();

#endif // TASK_H
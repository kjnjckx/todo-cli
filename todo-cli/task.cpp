#include "task.h"
#include <iostream>

const std::string DATA_FILE = "tasks.txt";
std::vector<Task> tasks;

void loadTasks() {
    tasks.clear();
    std::ifstream in(DATA_FILE);
    if (!in.is_open()) {
        return;
    }

    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string idStr, title, doneStr;

        if (!std::getline(ss, idStr, '|')) continue;
        if (!std::getline(ss, title, '|')) continue;
        if (!std::getline(ss, doneStr, '|')) continue;

        Task t;
        try {
            t.id = std::stoi(idStr);
        } catch (...) {
            continue;
        }
        t.title = title;
        t.done = (doneStr == "1");
        tasks.push_back(t);
    }
}

void saveTasks() {
    std::ofstream out(DATA_FILE, std::ios::trunc);
    if (!out.is_open()) {
        std::cerr << "Error: cannot open " << DATA_FILE << " for writing.\n";
        return;
    }

    for (const auto& t : tasks) {
        out << t.id << "|" << t.title << "|" << (t.done ? 1 : 0) << "\n";
    }
}
#ifndef TASKFUNC_H
#define TASKFUNC_H

#define TASK_STR_LENGTH 100
#define TASK_MAX_LENGTH 50

typedef struct {
	char task[TASK_STR_LENGTH];
	int done;
} Task;

void printFunction(int* toggle);

void addTask(Task* t, int* rear);

void showTask(Task* t, int rear);

void completeTask(Task* t, int rear);

void notCompleteTask(Task* t, int rear);

void removeTask(Task* t, int* rear);

void swapTask(Task* t, int rear);

void saveTask(Task* t, int size);

void importTask(Task* t, int* rear);

void addTaskByNumber(Task* t, int* rear);

#endif
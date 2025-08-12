#include <stdio.h>
#include "taskfunc.h"

int main() {
	Task task[TASK_MAX_LENGTH];

	int toggle = 0;
	int rear = -1;

	while (1) {
		printFunction(&toggle);

		int function;
		printf("\n사용할 기능의 번호를 입력해주세요 : ");
		
		scanf_s("%d", &function);

		switch (function) {
		case 1:
			addTask(task, &rear);
			break;
		case 2:
			showTask(task, rear);
			break;
		case 3:
			completeTask(task, rear);
			break;
		case 4:
			notCompleteTask(task, rear);
			break;
		case 5:
			removeTask(task, &rear);
			break;
		case 6:
			swapTask(task, rear);
			break;
		case 7:
			saveTask(task, rear+1);
			break;
		case 8:
			importTask(task, &rear);
			break;
		case 9:
			addTaskByNumber(task, &rear);
			break;
		case 10:
			return 0;
		default:
			printf("지원하지 않는 번호입니다.");
		}
	}
	return 0;
}
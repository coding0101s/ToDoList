#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "taskfunc.h"

void printFunction(int* toggle) {
	if (*toggle == 0) {
		printf("=====ToDoList 기능=====\n");
		printf("1. 할 일 추가\n");
		printf("2. 할 일 보기\n");
		printf("3. 할 일 완료 처리\n");
		printf("4. 할 일 미완료 처리\n");
		printf("5. 할 일 삭제\n");
		printf("6. 일 우선순위 바꾸기\n");
		printf("7. 할 일 저장\n");
		//printf("8. 종료\n");

		printf("8. 할 일 불러오기\n");
		printf("9. 할 일 끼워넣기\n");
		printf("10. 종료\n");
		*toggle = 1;
	}
	else {
		printf("\n\n=====ToDoList 기능=====\n");
		printf("1. 할 일 추가\n");
		printf("2. 할 일 보기\n");
		printf("3. 할 일 완료 처리\n");
		printf("4. 할 일 미완료 처리\n");
		printf("5. 할 일 삭제\n");
		printf("6. 일 우선순위 바꾸기\n");
		printf("7. 할 일 저장\n");
		//printf("8. 종료\n");

		printf("8. 할 일 불러오기\n");
		printf("9. 할 일 끼워넣기\n");
		printf("10. 종료\n");
	}
}

void addTask(Task* t, int* rear) {
	if (*rear == TASK_MAX_LENGTH - 1) {
		printf("ToDoList가 꽉 찼습니다.\n");
		return;
	}

	char task[TASK_STR_LENGTH];
	unsigned int buffer = sizeof(task);

	printf("추가할 일을 입력해주세요 : ");
	scanf_s(" %[^\n]", task, buffer);

	(*rear)++;
	strncpy_s(t[*rear].task, TASK_STR_LENGTH, task, _TRUNCATE);

	t[*rear].done = 0;
	printf("\n=> '%s' 추가 완료\n", task);
}

void showTask(Task* t, int rear) {
	system("cls");
	printf("===== ToDoList =====\n");
	if (rear == -1) {
		printf("ToDoList가 비어있습니다.\n");
		return;
	}

	if (rear == 0) {
		printf("[%d] %s (%s)", 1, t[rear].task, (t[rear].done > 0) ? "완료" : "미완료");
		return;
	}

	int count = 1;
	char* done;

	for (int i = 0; i <= rear; i++) {
		done = (t[i].done > 0) ? "완료" : "미완료";
		printf("[%d] %s (%s)\n", i + 1, t[i].task, done);
	}
	printf("\n\n");
}

void completeTask(Task* t, int rear) {
	if (rear == -1) {
		printf("ToDoList가 비어있습니다.\n");
		return;
	}

	int taskNum;
	printf("완료할 일의 번호를 입력하세요 : ");
	scanf_s("%d", &taskNum);

	if (taskNum > rear + 1) {
		printf("존재하지 않는 번호입니다.\n");
		return;
	}

	if (t[taskNum - 1].done == 1) {
		printf("해당 일은 이미 완료처리 되어있습니다.\n");
		return;
	}

	t[taskNum - 1].done = 1;
}

void notCompleteTask(Task* t, int rear) {
	if (rear == -1) {
		printf("ToDoList가 비어있습니다.\n");
		return;
	}

	int taskNum;
	printf("미완료할 일의 번호를 입력하세요 : ");
	scanf_s("%d", &taskNum);

	if (taskNum < 1 || taskNum > rear + 1) {
		printf("존재하지 않는 번호입니다.\n");
		return;
	}

	if (t[taskNum - 1].done == 0) {
		printf("해당 일은 이미 미완료처리 되어있습니다.\n");
		return;
	}

	t[taskNum - 1].done = 0;
}

void removeTask(Task* t, int* rear) {
	if (*rear == -1) {
		printf("ToDoList가 비어있습니다.\n");
		return;
	}

	/*(*rear)--;*/

	int removeTaskNum;
	printf("지울 일의 번호를 입력하세요 : ");
	scanf_s("%d", &removeTaskNum);

	if (removeTaskNum - 1 > *rear) {
		printf("존재하지 않는 번호입니다.\n");
		return;
	}

	for (int i = removeTaskNum - 1; i < *rear; i++) {
		t[i] = t[i + 1];
	}
	(*rear)--;
}

void swapTask(Task* t, int rear) {
	if (rear == -1) {
		printf("ToDoList가 비어있습니다.\n");
		return;
	}

	int idx1;
	int idx2;

	printf("바꿀 일의 번호를 입력하세요 : ");
	scanf_s("%d", &idx1);

	if (idx1 > rear + 1) {
		printf("존재하지 않는 번호입니다.\n");
		return;
	}

	printf("'%d'번과 바꿀 번호를 입력하세요 : ", idx1);
	scanf_s("%d", &idx2);

	if (idx2 > rear + 1) {
		printf("존재하지 않는 번호입니다.\n");
		return;
	}

	idx1--;
	idx2--;

	Task tempTask = t[idx1];
	t[idx1] = t[idx2];
	t[idx2] = tempTask;
}

void saveTask(Task* t, int size) {
	FILE* fp = fopen("task.txt", "w");

	if (fp == NULL) {
		printf("저장에 실패했습니다.\n");
		return;
	}

	for (int i = 0; i < size; i++) {
		fprintf(fp, "%d|%s\n", t[i].done, t[i].task);
	}

	fclose(fp);
}

void importTask(Task* t, int* rear) {
	*rear = 0;

	char line[TASK_STR_LENGTH + 2];
	unsigned int line_buffer = sizeof(line);

	char* lines[TASK_MAX_LENGTH];
	int lines_size = sizeof(lines) / sizeof(lines[0]);

	int i = 0;

	FILE* fp = fopen("task.txt", "r");

	if (fp == NULL) {
		printf("불러오기 실패했습니다.\n");
		return;
	}

	while (fgets(line, line_buffer, fp) != NULL) {
		if (strcmp(line, "\n") == 0 || strcmp(line, "") == 0) {
			continue;
		}

		if (strlen(line) < 2) continue;

		line[strcspn(line, "\n")] = '\0';

		if (line == NULL) {
			continue;
		}

		lines[i++] = _strdup(line);
	}

	for (int j = 0; j < i; j++) {
		char* context = NULL;

		char* token = strtok_s(lines[j], "|", &context);

		if (token == NULL) {
			free(lines[j]);
			continue;
		}
		
		t[*rear].done = atoi(token);

		token = strtok_s(NULL, "|", &context);

		strncpy_s(t[*rear].task, TASK_STR_LENGTH, token, _TRUNCATE);

		(*rear)++;
		free(lines[j]);
	}

	fclose(fp);

	*rear -= 1;
}

void addTaskByNumber(Task* t, int* rear) {
	if (*rear == TASK_MAX_LENGTH - 1) {
		printf("ToDoList가 꽉 찼습니다.\n");
		return;
	}

	char task[TASK_STR_LENGTH];
	unsigned int buffer = sizeof(task);

	printf("추가할 일을 입력해주세요 : ");
	scanf_s(" %[^\n]", task, buffer);

	int taskNumber;

	printf("'%s'을(를)추가할 번호를 선택해주세요 : ", task);
	scanf_s("%d", &taskNumber);

	(*rear)++;
	for (int i = *rear - 1; i >= taskNumber - 1; i--) {
		if (taskNumber - 1 == *rear) {
			strncpy_s(t[*rear - 1].task, TASK_STR_LENGTH, t[*rear].task, _TRUNCATE);
			t[*rear - 1].done = t[*rear].done;
			break;
		}
		strncpy_s(t[i + 1].task, TASK_STR_LENGTH, t[i].task, _TRUNCATE);
		t[i + 1].done = t[i].done;
	}

	strncpy_s(t[taskNumber-1].task, TASK_STR_LENGTH, task, _TRUNCATE);

	t[*rear].done = 0;
	printf("\n=> '%s' 추가 완료\n", task);
}
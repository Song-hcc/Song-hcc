#include<stdio.h>
#include "StudentManager.h"
#include<stdlib.h>
#include <stdbool.h>
#include<string.h>

static Node* CreateNode() {

	// 创建节点
	Node* node = malloc(sizeof(Node));
	if (!node) {
		printf("malloc failed\n");
		return NULL;
	}
	node->next = NULL;
	return node;

}

int menu() {
	printf("****************************************************\n");
	printf("*         欢迎使用高校学生成绩管理系统V1.0         *\n");
	printf("****************************************************\n");
	printf("*                    请选择功能                    *\n");
	printf("****************************************************\n");
	printf("*                  1.录入学生信息                  *\n");
	printf("*                  2.打印学生信息                  *\n");
	printf("*                  3.保存学生信息                  *\n");
	printf("*                  4.读取学生信息                  *\n");
	printf("*                  5.统计学生信息                  *\n");
	printf("*                  6.查找学生信息                  *\n");
	printf("*                  7.修改学生信息                  *\n");
	printf("*                  8.删除学生信息                  *\n");
	printf("*                  9.学生成绩排名                  *\n");
	printf("*                  0.  退出系统                    *\n");
	printf("****************************************************\n");
	printf("select>");
	int select = -1;
	scanf_s("%d", &select);
	return select;

}

void entryStudent(List* list) {

	Node* node = CreateNode();

	// 输入学生信息
	printf("请输入学生学号>");
	scanf_s("%llu", &node->stu.number);

	printf("请输入学生姓名>");
	scanf_s("%s", node->stu.name, (unsigned int)sizeof(node->stu.name));

	printf("请输入学生语文成绩>");
	scanf_s("%f", &node->stu.chinese);

	printf("请输入学生数学成绩>");
	scanf_s("%f", &node->stu.math);

	printf("请输入学生英语成绩>");
	scanf_s("%f", &node->stu.english);

	// 插入到链表中
	node->next = list->front;
	list->front = node;
	list->size++;

}

void printStudent(List* list) {

	printf("****************************************************\n");
	printf("*         欢迎使用高校学生成绩管理系统V1.0         *\n");
	printf("****************************************************\n");
	printf("*学 号    *  姓 名  *  语 文  *  数 学  *  英 语   *\n");
	printf("****************************************************\n");


	Node* curNode = list->front;
	//遍历链表
	while (curNode != NULL) {

		printf(" %-10llu  %-10s%-10.1f%-10.1f%-10.1f\n", curNode->stu.number, curNode->stu.name,
			curNode->stu.chinese, curNode->stu.math, curNode->stu.english);
		curNode = curNode->next;

	}
}

void saveStudent(List* list) {
	// 打开文件
	FILE* fp;
	errno_t err = fopen_s(&fp, "students.data", "wb");// FILE* fp = fopen("students.data", "wb");
	if (err) { // !fp
		// perror作用：将上一个函数发生的错误原因，输出到标准设备。
		perror("file open failed");
		return;
	}
	// 写入学生信息
	Node* curNode = list->front;
	while (curNode != NULL) {

		fwrite(&curNode->stu, sizeof(Student), 1, fp);
		curNode = curNode->next;
	}

	perror("file write succeed");
	// 关闭文件
	fclose(fp);

}

void saveStudentHuman(List* list) {
	// 打开文件
	FILE* fp;
	errno_t err = fopen_s(&fp, "students.txt", "w");// FILE* fp = fopen("students.data", "w");
	if (err) { // !fp
		// perror作用：将上一个函数发生的错误原因，输出到标准设备.
		perror("file open failed");
		return;
	}
	// 写入学生信息
	Node* curNode = list->front;
	while (curNode != NULL) {

		fprintf(fp, "%-25llu%-25s%-25.1f%-25.1f%-25.1f\n", curNode->stu.number, curNode->stu.name,
			curNode->stu.chinese, curNode->stu.math, curNode->stu.english);
		curNode = curNode->next;
	}

	perror("file write succeed");
	// 关闭文件
	fclose(fp);

}

void readStudent(List* list) {

	// 打开文件
	FILE* fp;
	errno_t err = fopen_s(&fp, "students.data", "rb");
	if (err) {
		perror("file open failed");
		return;
	}

	//读取学生信息
	while (!feof(fp)) {

		Node* node = CreateNode();
		if (!node)
			break;

		//fread(&node->stu, sizeof(Student), 1, fp);
		size_t len = fread_s(&node->stu, sizeof(node->stu), sizeof(Student), 1, fp);
		if (len == 0) {
			free(node);
			break;
		}

		//插入到链表中
		node->next = list->front;
		list->front = node;
		list->size++;
	}

	perror("file read succeed");
	fclose(fp);
}

void readStudentHuamn(List* list) {
	// 打开文件
	FILE* fp;
	errno_t err = fopen_s(&fp, "students.txt", "r");
	if (err) {
		perror("file open failed");
		return;
	}

	//读取学生信息
	while (!feof(fp)) {

		Node* node = CreateNode();
		if (!node)
			break;

		if (fscanf_s(fp, "%llu%s%f%f%f", &node->stu.number, node->stu.name, (unsigned int)sizeof(node->stu.name),
			&node->stu.chinese, &node->stu.math, &node->stu.english) != 5) {
			// 读取失败
			free(node);
			break;
		}

		//插入到链表中
		node->next = list->front;
		list->front = node;
		list->size++;
	}
	perror("file read succeed");
	fclose(fp);
}

void statisticsStudentCount(List* list) {

	if (list->size == 0) {
		printf("暂未录入任何学生信息。\n");
		return;
	}
	//printf("学生总人数为：%d\n", list->size);

	int count = 0;
	float chineseTotalScore = 0, mathTotalScore = 0, englishTotalScore = 0;
	Node* curNode = list->front;

	float maxChinese, maxMath, maxEnglish;
	float minChinese, minMath, minEnglish;
	maxChinese = minChinese = curNode->stu.chinese;
	maxMath = minMath = curNode->stu.math;
	maxEnglish = minEnglish = curNode->stu.english;

	while (curNode != NULL) {
		//统计人数和总分
		chineseTotalScore += curNode->stu.chinese;
		mathTotalScore += curNode->stu.math;
		englishTotalScore += curNode->stu.english;
		count++;

		//统计语文最高分最低分
		if (curNode->stu.chinese > maxChinese) {
			maxChinese = curNode->stu.chinese;
		}
		if (curNode->stu.chinese < minChinese) {
			minChinese = curNode->stu.chinese;
		}

		//统计数学最高分最低分
		if (curNode->stu.math > maxMath) {
			maxMath = curNode->stu.math;
		}
		if (curNode->stu.math < minMath) {
			minMath = curNode->stu.math;
		}

		//统计英语最高分最低分
		if (curNode->stu.english > maxEnglish) {
			maxEnglish = curNode->stu.english;
		}
		if (curNode->stu.english < minEnglish) {
			minEnglish = curNode->stu.english;
		}

		curNode = curNode->next;
	}


	printf("学生总人数为：%d\n语文平均成绩：%.1f 最高分：%.1f 最低分：%.1f\n数学平均成绩：%.1f 最高分：%.1f 最低分：%.1f\n英语平均成绩：%.1f 最高分：%.1f 最低分：%.1f\n", count,
		chineseTotalScore / count, maxChinese, minChinese,
		mathTotalScore / count, maxMath, minMath,
		englishTotalScore / count, maxEnglish, minEnglish);

}

Node* findStudent(List* list) {

	if (list->size == 0) {
		printf("暂未录入任何学生信息。\n");
		return NULL;
	}

	char buffer[32];
	printf("请输入要查找的学生学号或姓名>");
	scanf_s("%s", buffer, (unsigned int)sizeof(buffer));

	// 尝试把buffer转成整形
	size_t number = -1;
	sscanf_s(buffer, "%llu", &number);

	Node* curNode = list->front;
	while (curNode != NULL) {

		if (strcmp(curNode->stu.name, buffer) == 0 || // 按照姓名查找
			curNode->stu.number == number) {
			return curNode;
		}

		curNode = curNode->next;

	}

	return NULL;

}

void alterStudent(List* list) {

	if (list->size == 0) {
		printf("暂未录入任何学生信息。\n");
		return;
	}

	char buffer[32];
	printf("请输入要修改的学生学号或姓名>");
	scanf_s("%s", buffer, (unsigned int)sizeof(buffer));

	// 尝试把buffer转成整形
	size_t number = -1;
	sscanf_s(buffer, "%llu", &number);

	Node* curNode = list->front;
	while (curNode != NULL) {

		if (strcmp(curNode->stu.name, buffer) == 0 || // 按照姓名查找
			curNode->stu.number == number) {

			printf("请输入要修改的学生的语文、数学、英语成绩>");
			scanf_s("%f%f%f", &curNode->stu.chinese, &curNode->stu.math, &curNode->stu.english);
			printf("修改成功！\n");
			break;
		}

		curNode = curNode->next;

	}

	if (curNode == NULL) {
		printf("没有找到该学生，修改失败。\n");
	}
}

void removeStudent(List* list) {

	if (list->size == 0) {
		printf("暂未录入任何学生信息。\n");
		return;
	}

	char buffer[32];
	printf("请输入要删除的学生学号或姓名>");
	scanf_s("%s", buffer, (unsigned int)sizeof(buffer));

	// 尝试把buffer转成整形
	size_t number = -1;
	sscanf_s(buffer, "%llu", &number);

	Node* curNode = list->front;
	Node* preNode = NULL;
	while (curNode != NULL) {

		if (strcmp(curNode->stu.name, buffer) == 0 || // 按照姓名查找
			curNode->stu.number == number) { // 按照学号查找
			break; // 跳出while循环
		}

		preNode = curNode;
		curNode = curNode->next;

	}

	// 是否找到
	if (curNode) {
		// 要删除的就是第一个节点
		if (preNode == NULL) {
			list->front = curNode->next;
		}
		else {
			preNode->next = curNode->next;
		}

		printf("删除成功！\n");
		free(curNode);
		list->size--;
	}
	else
		printf("未找到该学生信息。\n");

}

void rankStudent(List* list) {
	// 如果链表为空或只有一个元素，则无需排序
	if (list->size <= 1) return;

	//选择按哪一科排序
	char rank_num = 0;
	printf("请输入1~3，对应按语文、数学、英语成绩排名\n");
	scanf_s("%hhd", &rank_num);

	//定义三个节点
	Node* currNode = list->front;
	Node* preNode = NULL;
	Node* nextNode = currNode->next;

	for (int j = 0; j < list->size - 1; j++) {

		for (int i = 0; i < list->size - j - 1; i++) {
			//由大到小排序，大的放左边，小的放右边
			if ((nextNode != NULL) &&
				(rank_num == 1 ? (nextNode->stu.chinese > currNode->stu.chinese) :
					(rank_num == 2 ? (nextNode->stu.math > currNode->stu.math) :
						(nextNode->stu.english > currNode->stu.english)))) {//通过三元运算符选择语数外成绩

				currNode->next = nextNode->next;
				nextNode->next = currNode;

				if (preNode == NULL) {
					list->front = nextNode;
				}
				else {
					preNode->next = nextNode;
				}

				//更新preNode和nextNode
				preNode = nextNode;
				nextNode = currNode->next;
			}
			else {
				//右移一位
				preNode = currNode;
				currNode = nextNode;
				nextNode = currNode->next;
			}
		}
		preNode = NULL; // 在每轮外层循环开始时重置preNode  
		currNode = list->front; // 从链表的头部开始每轮比较 
		nextNode = currNode->next;
	}
	printf("排序成功\n");
}




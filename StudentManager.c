#include<stdio.h>
#include "StudentManager.h"
#include<stdlib.h>
#include <stdbool.h>
#include<string.h>

static Node* CreateNode() {

	// �����ڵ�
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
	printf("*         ��ӭʹ�ø�Уѧ���ɼ�����ϵͳV1.0         *\n");
	printf("****************************************************\n");
	printf("*                    ��ѡ����                    *\n");
	printf("****************************************************\n");
	printf("*                  1.¼��ѧ����Ϣ                  *\n");
	printf("*                  2.��ӡѧ����Ϣ                  *\n");
	printf("*                  3.����ѧ����Ϣ                  *\n");
	printf("*                  4.��ȡѧ����Ϣ                  *\n");
	printf("*                  5.ͳ��ѧ����Ϣ                  *\n");
	printf("*                  6.����ѧ����Ϣ                  *\n");
	printf("*                  7.�޸�ѧ����Ϣ                  *\n");
	printf("*                  8.ɾ��ѧ����Ϣ                  *\n");
	printf("*                  9.ѧ���ɼ�����                  *\n");
	printf("*                  0.  �˳�ϵͳ                    *\n");
	printf("****************************************************\n");
	printf("select>");
	int select = -1;
	scanf_s("%d", &select);
	return select;

}

void entryStudent(List* list) {

	Node* node = CreateNode();

	// ����ѧ����Ϣ
	printf("������ѧ��ѧ��>");
	scanf_s("%llu", &node->stu.number);

	printf("������ѧ������>");
	scanf_s("%s", node->stu.name, (unsigned int)sizeof(node->stu.name));

	printf("������ѧ�����ĳɼ�>");
	scanf_s("%f", &node->stu.chinese);

	printf("������ѧ����ѧ�ɼ�>");
	scanf_s("%f", &node->stu.math);

	printf("������ѧ��Ӣ��ɼ�>");
	scanf_s("%f", &node->stu.english);

	// ���뵽������
	node->next = list->front;
	list->front = node;
	list->size++;

}

void printStudent(List* list) {

	printf("****************************************************\n");
	printf("*         ��ӭʹ�ø�Уѧ���ɼ�����ϵͳV1.0         *\n");
	printf("****************************************************\n");
	printf("*ѧ ��    *  �� ��  *  �� ��  *  �� ѧ  *  Ӣ ��   *\n");
	printf("****************************************************\n");


	Node* curNode = list->front;
	//��������
	while (curNode != NULL) {

		printf(" %-10llu  %-10s%-10.1f%-10.1f%-10.1f\n", curNode->stu.number, curNode->stu.name,
			curNode->stu.chinese, curNode->stu.math, curNode->stu.english);
		curNode = curNode->next;

	}
}

void saveStudent(List* list) {
	// ���ļ�
	FILE* fp;
	errno_t err = fopen_s(&fp, "students.data", "wb");// FILE* fp = fopen("students.data", "wb");
	if (err) { // !fp
		// perror���ã�����һ�����������Ĵ���ԭ���������׼�豸��
		perror("file open failed");
		return;
	}
	// д��ѧ����Ϣ
	Node* curNode = list->front;
	while (curNode != NULL) {

		fwrite(&curNode->stu, sizeof(Student), 1, fp);
		curNode = curNode->next;
	}

	perror("file write succeed");
	// �ر��ļ�
	fclose(fp);

}

void saveStudentHuman(List* list) {
	// ���ļ�
	FILE* fp;
	errno_t err = fopen_s(&fp, "students.txt", "w");// FILE* fp = fopen("students.data", "w");
	if (err) { // !fp
		// perror���ã�����һ�����������Ĵ���ԭ���������׼�豸.
		perror("file open failed");
		return;
	}
	// д��ѧ����Ϣ
	Node* curNode = list->front;
	while (curNode != NULL) {

		fprintf(fp, "%-25llu%-25s%-25.1f%-25.1f%-25.1f\n", curNode->stu.number, curNode->stu.name,
			curNode->stu.chinese, curNode->stu.math, curNode->stu.english);
		curNode = curNode->next;
	}

	perror("file write succeed");
	// �ر��ļ�
	fclose(fp);

}

void readStudent(List* list) {

	// ���ļ�
	FILE* fp;
	errno_t err = fopen_s(&fp, "students.data", "rb");
	if (err) {
		perror("file open failed");
		return;
	}

	//��ȡѧ����Ϣ
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

		//���뵽������
		node->next = list->front;
		list->front = node;
		list->size++;
	}

	perror("file read succeed");
	fclose(fp);
}

void readStudentHuamn(List* list) {
	// ���ļ�
	FILE* fp;
	errno_t err = fopen_s(&fp, "students.txt", "r");
	if (err) {
		perror("file open failed");
		return;
	}

	//��ȡѧ����Ϣ
	while (!feof(fp)) {

		Node* node = CreateNode();
		if (!node)
			break;

		if (fscanf_s(fp, "%llu%s%f%f%f", &node->stu.number, node->stu.name, (unsigned int)sizeof(node->stu.name),
			&node->stu.chinese, &node->stu.math, &node->stu.english) != 5) {
			// ��ȡʧ��
			free(node);
			break;
		}

		//���뵽������
		node->next = list->front;
		list->front = node;
		list->size++;
	}
	perror("file read succeed");
	fclose(fp);
}

void statisticsStudentCount(List* list) {

	if (list->size == 0) {
		printf("��δ¼���κ�ѧ����Ϣ��\n");
		return;
	}
	//printf("ѧ��������Ϊ��%d\n", list->size);

	int count = 0;
	float chineseTotalScore = 0, mathTotalScore = 0, englishTotalScore = 0;
	Node* curNode = list->front;

	float maxChinese, maxMath, maxEnglish;
	float minChinese, minMath, minEnglish;
	maxChinese = minChinese = curNode->stu.chinese;
	maxMath = minMath = curNode->stu.math;
	maxEnglish = minEnglish = curNode->stu.english;

	while (curNode != NULL) {
		//ͳ���������ܷ�
		chineseTotalScore += curNode->stu.chinese;
		mathTotalScore += curNode->stu.math;
		englishTotalScore += curNode->stu.english;
		count++;

		//ͳ��������߷���ͷ�
		if (curNode->stu.chinese > maxChinese) {
			maxChinese = curNode->stu.chinese;
		}
		if (curNode->stu.chinese < minChinese) {
			minChinese = curNode->stu.chinese;
		}

		//ͳ����ѧ��߷���ͷ�
		if (curNode->stu.math > maxMath) {
			maxMath = curNode->stu.math;
		}
		if (curNode->stu.math < minMath) {
			minMath = curNode->stu.math;
		}

		//ͳ��Ӣ����߷���ͷ�
		if (curNode->stu.english > maxEnglish) {
			maxEnglish = curNode->stu.english;
		}
		if (curNode->stu.english < minEnglish) {
			minEnglish = curNode->stu.english;
		}

		curNode = curNode->next;
	}


	printf("ѧ��������Ϊ��%d\n����ƽ���ɼ���%.1f ��߷֣�%.1f ��ͷ֣�%.1f\n��ѧƽ���ɼ���%.1f ��߷֣�%.1f ��ͷ֣�%.1f\nӢ��ƽ���ɼ���%.1f ��߷֣�%.1f ��ͷ֣�%.1f\n", count,
		chineseTotalScore / count, maxChinese, minChinese,
		mathTotalScore / count, maxMath, minMath,
		englishTotalScore / count, maxEnglish, minEnglish);

}

Node* findStudent(List* list) {

	if (list->size == 0) {
		printf("��δ¼���κ�ѧ����Ϣ��\n");
		return NULL;
	}

	char buffer[32];
	printf("������Ҫ���ҵ�ѧ��ѧ�Ż�����>");
	scanf_s("%s", buffer, (unsigned int)sizeof(buffer));

	// ���԰�bufferת������
	size_t number = -1;
	sscanf_s(buffer, "%llu", &number);

	Node* curNode = list->front;
	while (curNode != NULL) {

		if (strcmp(curNode->stu.name, buffer) == 0 || // ������������
			curNode->stu.number == number) {
			return curNode;
		}

		curNode = curNode->next;

	}

	return NULL;

}

void alterStudent(List* list) {

	if (list->size == 0) {
		printf("��δ¼���κ�ѧ����Ϣ��\n");
		return;
	}

	char buffer[32];
	printf("������Ҫ�޸ĵ�ѧ��ѧ�Ż�����>");
	scanf_s("%s", buffer, (unsigned int)sizeof(buffer));

	// ���԰�bufferת������
	size_t number = -1;
	sscanf_s(buffer, "%llu", &number);

	Node* curNode = list->front;
	while (curNode != NULL) {

		if (strcmp(curNode->stu.name, buffer) == 0 || // ������������
			curNode->stu.number == number) {

			printf("������Ҫ�޸ĵ�ѧ�������ġ���ѧ��Ӣ��ɼ�>");
			scanf_s("%f%f%f", &curNode->stu.chinese, &curNode->stu.math, &curNode->stu.english);
			printf("�޸ĳɹ���\n");
			break;
		}

		curNode = curNode->next;

	}

	if (curNode == NULL) {
		printf("û���ҵ���ѧ�����޸�ʧ�ܡ�\n");
	}
}

void removeStudent(List* list) {

	if (list->size == 0) {
		printf("��δ¼���κ�ѧ����Ϣ��\n");
		return;
	}

	char buffer[32];
	printf("������Ҫɾ����ѧ��ѧ�Ż�����>");
	scanf_s("%s", buffer, (unsigned int)sizeof(buffer));

	// ���԰�bufferת������
	size_t number = -1;
	sscanf_s(buffer, "%llu", &number);

	Node* curNode = list->front;
	Node* preNode = NULL;
	while (curNode != NULL) {

		if (strcmp(curNode->stu.name, buffer) == 0 || // ������������
			curNode->stu.number == number) { // ����ѧ�Ų���
			break; // ����whileѭ��
		}

		preNode = curNode;
		curNode = curNode->next;

	}

	// �Ƿ��ҵ�
	if (curNode) {
		// Ҫɾ���ľ��ǵ�һ���ڵ�
		if (preNode == NULL) {
			list->front = curNode->next;
		}
		else {
			preNode->next = curNode->next;
		}

		printf("ɾ���ɹ���\n");
		free(curNode);
		list->size--;
	}
	else
		printf("δ�ҵ���ѧ����Ϣ��\n");

}

void rankStudent(List* list) {
	// �������Ϊ�ջ�ֻ��һ��Ԫ�أ�����������
	if (list->size <= 1) return;

	//ѡ����һ������
	char rank_num = 0;
	printf("������1~3����Ӧ�����ġ���ѧ��Ӣ��ɼ�����\n");
	scanf_s("%hhd", &rank_num);

	//���������ڵ�
	Node* currNode = list->front;
	Node* preNode = NULL;
	Node* nextNode = currNode->next;

	for (int j = 0; j < list->size - 1; j++) {

		for (int i = 0; i < list->size - j - 1; i++) {
			//�ɴ�С���򣬴�ķ���ߣ�С�ķ��ұ�
			if ((nextNode != NULL) &&
				(rank_num == 1 ? (nextNode->stu.chinese > currNode->stu.chinese) :
					(rank_num == 2 ? (nextNode->stu.math > currNode->stu.math) :
						(nextNode->stu.english > currNode->stu.english)))) {//ͨ����Ԫ�����ѡ��������ɼ�

				currNode->next = nextNode->next;
				nextNode->next = currNode;

				if (preNode == NULL) {
					list->front = nextNode;
				}
				else {
					preNode->next = nextNode;
				}

				//����preNode��nextNode
				preNode = nextNode;
				nextNode = currNode->next;
			}
			else {
				//����һλ
				preNode = currNode;
				currNode = nextNode;
				nextNode = currNode->next;
			}
		}
		preNode = NULL; // ��ÿ�����ѭ����ʼʱ����preNode  
		currNode = list->front; // �������ͷ����ʼÿ�ֱȽ� 
		nextNode = currNode->next;
	}
	printf("����ɹ�\n");
}




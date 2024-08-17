#pragma once

/*
*ѧ���ṹ
*/
typedef struct Student
{
	unsigned long long number;	//ѧ��
	char name[32];				//����
	float chinese;				//����
	float math;					//��ѧ
	float english;				//Ӣ��
}Student;

/*
*�ڵ� Node
*/
typedef struct Node
{
	Student stu;		//ѧ��		
	struct Node* next;	//ָ����һ���ڵ��ָ��
}Node;

/*
*����
*/
typedef struct List
{
	Node* front;		//ָ���һ���ڵ�
	int size;			//��ǰ�ڵ�����
}List;

/*
*�˵�����
*/
typedef enum MenuOptions
{
	Quit,				//�˳�ϵͳ
	Entry,				//¼��ѧ����Ϣ
	Print,				//��ӡѧ����Ϣ
	Save,				//����ѧ����Ϣ
	Read,				//��ȡѧ����Ϣ
	Statistics,			//ͳ��ѧ����Ϣ
	Find,				//����ѧ����Ϣ
	Alter,				//�޸�ѧ����Ϣ
	Remove,				//ɾ��ѧ����Ϣ
	Rank				//����ѧ����Ϣ

}MenuOptions;
/*
*��ӡ�˵�������ʾ�û�ѡ���ܡ�
*/
int menu();

/*
*ѧ��¼�� Alt + Enter��ݶ���
*/
void entryStudent(List* list);

/*
*��ӡѧ��
*/
void printStudent(List* list);

/*
* ����ѧ���������Ʊ���
*/
void saveStudent(List* list);

/*
* ����ѧ�������ܿ����ķ�ʽ����
*/
void saveStudentHuman(List* list);

/*
* ��ȡѧ����������
*/
void readStudent(List* list);

/*
* ��ȡѧ�����ܶ�����
*/
void readStudentHuamn(List* list);

/*
* ͳ��ѧ������
*/
void statisticsStudentCount(List* list);

/*
* ����ѧ��
*/
Node* findStudent(List* list);

/*
* ����ѧ��
*/
void alterStudent(List* list);

/*
* ɾ��ѧ��
*/
void removeStudent(List* list);

/*
* ����ѧ��
*/
void rankStudent(List* list);




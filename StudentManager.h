#pragma once

/*
*学生结构
*/
typedef struct Student
{
	unsigned long long number;	//学号
	char name[32];				//姓名
	float chinese;				//语文
	float math;					//数学
	float english;				//英语
}Student;

/*
*节点 Node
*/
typedef struct Node
{
	Student stu;		//学生		
	struct Node* next;	//指向下一个节点的指针
}Node;

/*
*链表
*/
typedef struct List
{
	Node* front;		//指向第一个节点
	int size;			//当前节点数量
}List;

/*
*菜单功能
*/
typedef enum MenuOptions
{
	Quit,				//退出系统
	Entry,				//录入学生信息
	Print,				//打印学生信息
	Save,				//保存学生信息
	Read,				//读取学生信息
	Statistics,			//统计学生信息
	Find,				//查找学生信息
	Alter,				//修改学生信息
	Remove,				//删除学生信息
	Rank				//排序学生信息

}MenuOptions;
/*
*打印菜单，并提示用户选择功能。
*/
int menu();

/*
*学生录入 Alt + Enter快捷定义
*/
void entryStudent(List* list);

/*
*打印学生
*/
void printStudent(List* list);

/*
* 保存学生，二进制保存
*/
void saveStudent(List* list);

/*
* 保存学生，用能看懂的方式保存
*/
void saveStudentHuman(List* list);

/*
* 读取学生，二进制
*/
void readStudent(List* list);

/*
* 读取学生，能读懂的
*/
void readStudentHuamn(List* list);

/*
* 统计学生人数
*/
void statisticsStudentCount(List* list);

/*
* 查找学生
*/
Node* findStudent(List* list);

/*
* 查找学生
*/
void alterStudent(List* list);

/*
* 删除学生
*/
void removeStudent(List* list);

/*
* 排序学生
*/
void rankStudent(List* list);




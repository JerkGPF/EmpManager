#pragma once
#include<iostream>
#include "Worker.h"
#include "Manager.h"
#include "Boss.h"
#include "Employee.h"
#include <fstream>
#define FILENAME "empFile.txt"
using namespace std;
class WorkManager
{
public:
	WorkManager();
	//չʾ�˵�
	void showMenu();
	//�˳�ϵͳ
	void exitSystem();

	//��¼ְ������
	int mEmpNum;
	//ְ������ָ��
	Worker** mEmpArray;
	//��Ӻ���
	void addEmp();

	//�����ļ�
	void save();

	//�ж��ļ��Ƿ�Ϊ��
	bool isEmptyFile;

	//ͳ���ļ�������
	int getEmpNum();
	//��ʼ��Ա��
	void initEmp();
	//��ʾְ��
	void showEmp();
	//ɾ��Ա��
	void delEmp();
	//�ж�ְ���Ƿ���ڣ����ڷ��������е�λ�ã������ڷ���-1��
	int isExistEmp(int id);
	//�޸�ְ��
	void ModEmp();
	//����ְ��
	void findEmp();
	//���ձ������
	void sortEmp();
	//����ļ�
	void cleanFile();

	~WorkManager();

};


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
	//展示菜单
	void showMenu();
	//退出系统
	void exitSystem();

	//记录职工人数
	int mEmpNum;
	//职工数组指针
	Worker** mEmpArray;
	//添加函数
	void addEmp();

	//保存文件
	void save();

	//判断文件是否为空
	bool isEmptyFile;

	//统计文件中人数
	int getEmpNum();
	//初始化员工
	void initEmp();
	//显示职工
	void showEmp();
	//删除员工
	void delEmp();
	//判断职工是否存在，存在返回数组中的位置，不存在返回-1；
	int isExistEmp(int id);
	//修改职工
	void ModEmp();
	//查找职工
	void findEmp();
	//按照编号排序
	void sortEmp();
	//清空文件
	void cleanFile();

	~WorkManager();

};


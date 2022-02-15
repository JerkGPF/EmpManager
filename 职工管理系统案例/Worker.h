#pragma once
#include<iostream>
#include <string>
using namespace std;
class Worker
{
public:
	//显示个人信息
	virtual void showInfo() = 0;
	//获取岗位名称
	virtual string getDeptName() = 0;
	int mId;//职工编号 
	string mName;//员工姓名
	int mDeptId;//部门编号
};


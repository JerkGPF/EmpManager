#pragma once
#include "Worker.h"
#include <iostream>
#include <string>
using namespace std;

class Employee :
    public Worker
{
public:
	Employee();
	Employee(int id, string name, int dId);
	//��ʾ������Ϣ
	void showInfo();
	//��ȡ��λ����
	string getDeptName();
};


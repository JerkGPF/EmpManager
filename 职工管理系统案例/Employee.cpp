#include "Employee.h"

Employee::Employee()
{
}

Employee::Employee(int id,string name,int dId)
{
	this->mId = id;
	this->mName = name;
	this->mDeptId = dId;
}
void Employee::showInfo()
{
	cout << "ְ�����:" << this->mId
		<< "\tְ������:" << this->mName
		<< "\t��λ:" << this->getDeptName()
		<< "\t��λְ����ɾ�����������" << endl;
}

string Employee::getDeptName()
{
	return string("Ա��");
}

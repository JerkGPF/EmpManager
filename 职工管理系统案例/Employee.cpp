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
	cout << "职工编号:" << this->mId
		<< "\t职工姓名:" << this->mName
		<< "\t岗位:" << this->getDeptName()
		<< "\t岗位职责：完成经理交代的任务" << endl;
}

string Employee::getDeptName()
{
	return string("员工");
}

#include "Manager.h"

Manager::Manager()
{
}

Manager::Manager(int id, string name, int dId)
{
	this->mId = id;
	this->mName = name;
	this->mDeptId = dId;
}

void Manager::showInfo()
{
	cout << "ְ�����:" << this->mId
		<< "\tְ������:" << this->mName
		<< "\t��λ:" << this->getDeptName()
		<< "\t��λְ������ϰ彻�������񣬲����·�����" << endl;
}

string Manager::getDeptName()
{
	return string("����");
}

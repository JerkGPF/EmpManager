#include "Boss.h"

Boss::Boss()
{
}

Boss::Boss(int id, string name, int dId)
{
	this->mId = id;
	this->mName = name;
	this->mDeptId = dId;
}

void Boss::showInfo()
{
	cout << "ְ�����:" << this->mId
		<< "\tְ������:" << this->mName
		<< "\t��λ:" << this->getDeptName()
		<< "\t��λְ�𣺹���˾����" << endl;

}

string Boss::getDeptName()
{
	return string("�ϰ�");
}

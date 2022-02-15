#include "WorkManager.h"

WorkManager::WorkManager()
{
	//1.文件不存在
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//读文件
	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;
		//初始化属性
		this->mEmpNum = 0;
		this->mEmpArray = NULL;
		this->isEmptyFile = true;
		ifs.close();
		return;
	}
	//2.文件存在但为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "文件为空" << endl;
		//初始化属性
		this->mEmpNum = 0;
		this->mEmpArray = NULL;
		this->isEmptyFile = true;
		ifs.close();
		return;
	}
	//3.文件存在，且不为空
	int num = this->getEmpNum();
	cout << "职工有" << num << "人" << endl;
	this->mEmpNum = num;

	//开辟空间
	this->mEmpArray = new Worker * [this->mEmpNum];
	//将文件中的数据存到数组中
	this->initEmp();
	
}

void WorkManager::showMenu()
{
	cout << "**********************************" << endl;
	cout << "*******欢迎使用职工管理系统!******" << endl;
	cout << "********* 0.退出管理程序 *********" << endl;
	cout << "********* 1.增加职工信息 *********" << endl;
	cout << "********* 2.显示职工信息 *********" << endl;
	cout << "********* 3.删除离职职工 *********" << endl;
	cout << "********* 4.修改职工信息 *********" << endl;
	cout << "********* 5.查找职工信息 *********" << endl;
	cout << "********* 6.按照编号排序 *********" << endl;
	cout << "********* 7.清空所有文档 *********" << endl;
	cout << "**********************************" << endl;
	cout << endl;
}

void WorkManager::exitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}

void WorkManager::addEmp()
{
	cout << "请输入添加职工的数量" << endl;
	int addNum = 0;//保存用户输入的数量
	cin >> addNum;
	if (addNum > 0)
	{
		//添加
		//计算添加新空间大小
		int newSize = this->mEmpNum + addNum;//新人数 = 原来记录人数+新增人数
		//开辟新空间
		Worker** newSpace = new Worker * [newSize];
		//将原来的空间数据拷贝到新空间下
		if (this->mEmpArray != NULL)
			for (int i = 0; i < this->mEmpNum; i++)
				newSpace[i] = this->mEmpArray[i];
		//添加新数据
		for (int i = 0; i < addNum; i++)
		{
			int id;//编号
			string name;//姓名
			int dSelect;//部门选择
			cout << "请输入第" << i + 1 << "个新职工编号:" << endl;
			cin >> id;

			cout << "请输入第" << i + 1 << "个新职工姓名:" << endl;
			cin >> name;

			cout << "请选择该职工岗位" << endl;
			cout << "1.普通员工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;
			cin >> dSelect;
			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				break;
			}
			//将创建的员工保存到数组中
			newSpace[this->mEmpNum + i] = worker;
		}
		//释放原有的空间
		delete[] this->mEmpArray;
		//更改新空间的指向
		this->mEmpArray = newSpace;
		//更新员工人数
		this->mEmpNum = newSize;
		this->save();		//保存信息
		cout << "成功添加" << addNum << "名员工" << endl;
		this->isEmptyFile = false;//更新文件状态
		
	}
	else
		cout << "输入有误" << endl;
	system("cls");//清屏
}

void WorkManager::save()
{
	ofstream ofs;//创建流
	ofs.open(FILENAME, ios::out);//打开文件
	for (int i = 0; i < this->mEmpNum; i++)//写入
	{
		ofs << this->mEmpArray[i]->mId << " "
			<< this->mEmpArray[i]->mName << " "
			<< this->mEmpArray[i]->mDeptId << endl;
	}
	ofs.close();//关闭文件
}

int WorkManager::getEmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//读取文件
	int id;
	string name;
	int dId;
	int num = 0;//记录人数
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		num++;
	}

	return num;
}

void WorkManager::initEmp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int dId;
	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		Worker* worker = NULL;
		if (dId == 1)
			worker = new Employee(id, name, dId);
		else if (dId == 2)
			worker = new Manager(id, name, dId);
		else 
			worker = new Boss(id, name, dId);
		this->mEmpArray[index] = worker;
		index++;
	}
	ifs.close();
}

void WorkManager::showEmp()
{
	//判断文件是否为空
	if (isEmptyFile)
		cout << "文件不存在或记录为空" << endl;
	else
		cout <<"mEmpNum:"<< mEmpNum << endl;
		for (int i = 0; i < mEmpNum; i++)
			this->mEmpArray[i]->showInfo();//多态调用程序接口

	system("pause");
	system("cls");


}

void WorkManager::delEmp()
{
	if (this->isEmptyFile)
		cout << "文件不存在或者记录为空" << endl;
	else
	{
		//按照职工编号删除
		cout << "请输入想要删除的职工编号" << endl;
		int id = 0;
		cin >> id;
		int index = isExistEmp(id);
		if (index != -1)
		{
			for (int i = index; i < this->mEmpNum-1; i++)	
				this->mEmpArray[i] = this->mEmpArray[i + 1];//数据前移
			this->mEmpNum--;//更新记录人数
			//保存数据
			save();
			cout << "删除成功" << endl;
	
		}
		else
			cout << "删除失败，未找到该员工" << endl;
	}
	system("pause");
	system("cls");
}
//判断职工是否存在，存在返回数组中的位置，不存在返回-1；
int WorkManager::isExistEmp(int id)
{
	int index = -1;
	for (int i = 0; i < mEmpNum; i++)
	{
		if (this->mEmpArray[i]->mId == id)
		{
			index = i;
			break;
		}
	}
	return index;
}

void WorkManager::ModEmp()
{
	if (this->isEmptyFile)
	{
		cout << "文件不存在或者记录为空！" << endl;
	}
	else
	{
		cout << "请输入修改职工的编号:" << endl;
		int id;
		cin >> id;
		int ret = this->isExistEmp(id);
		if (ret != -1)
		{
			//查找到编号职工
			delete this->mEmpArray[ret];
			int newId = 0;
			string newName = "";
			int dSelect = 0;

			cout << "查到:" << id << "号职工，请输入新职工号:" << endl;
			cin >> newId;

			cout << "请输入新姓名:" << endl;
			cin >> newName;

			cout << "请输入职工岗位:" << endl;
			cout << "1.普通员工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;
			cin >> dSelect;

			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(newId, newName, dSelect);
				break;
			case 2:
				worker = new Manager(newId, newName, dSelect);
				break;
			case 3:
				worker = new Boss(newId, newName, dSelect);
				break;
			default:
				break;
			}
			//更新数组
			this->mEmpArray[ret] = worker;
			cout << "修改成功" << endl;
			//保存文件
			save();
		}
		else
		{
			cout << "修改失败,查无此人" << endl;
		}
	}
	system("pause");
	system("cls");
}

void WorkManager::findEmp()
{
	if (this->isEmptyFile)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{
		cout << "请输入查找的方式" << endl;
		cout << "1.按职工编号查找" << endl;
		cout << "2.按职工姓名查找" << endl;
		int select = 0;
		cin >> select;
		if (select == 1)
		{
			//按照编号查
			int id;
			cout << "请输入查找的职工编号:" << endl;
			cin >> id;
			int ret = isExistEmp(id);
			if (ret != -1)
			{
				//查找成功
				cout << "查找成功，该职工信息如下" << endl;
				this->mEmpArray[ret]->showInfo();
			}
			else
			{
				cout << "查找失败，查无此人" << endl;
			}

		}
		else if (select == 2)
		{
			//按照姓名查
			string name;
			cout << "请输入姓名" << endl;
			cin >> name;
			bool flag = false;//默认未找到职工
			for (int i = 0; i < mEmpNum; i++)
			{
				if (this->mEmpArray[i]->mName == name)
				{
					cout << "查找成功，职工编号为:"
						<< mEmpArray[i]->mId 
						<< "号职工信息如下" << endl;
					flag = true;
					this->mEmpArray[i]->showInfo();//打印信息

				}
			}
			if (flag == false)
				cout << "查找识别，查无此人!" << endl;
		}
		else
		{
			cout << "输入有误" << endl;
		}
	}
	system("pause");
	system("cls");
}

void WorkManager::sortEmp()
{
	if (this->isEmptyFile)
	{
		cout << "文件不存在或记录为空" << endl;
		return;
	}
	cout << "请选择排序规则" << endl;
	cout << "1.升序" << endl;
	cout << "2.降序" << endl;
	int sel = 0;
	cin >> sel;

	for (int i = 0; i < mEmpNum; i++)
	{
		int minOrMax = i;//声明最小值或者最大值下标
		for (int j = i + 1; j < mEmpNum; j++)
		{
			if (sel == 1)//升序
			{
				if (this->mEmpArray[minOrMax]->mId > this->mEmpArray[j]->mId)
				{
					minOrMax = j;
				}
			}
			else
			{
				if (this->mEmpArray[minOrMax]->mId < this->mEmpArray[j]->mId)
				{
					minOrMax = j;
				}
			}
		}
		//判断当前的i是否为计算的最大或者最小
		if (i != minOrMax)
		{
			Worker* temp = this->mEmpArray[i];
			this->mEmpArray[i] = this->mEmpArray[minOrMax];
			this->mEmpArray[minOrMax] = temp;
		}
	}
	cout << "排序成功" << endl;
	this->save();
	this->showEmp();
	
}

void WorkManager::cleanFile()
{
	cout << "确定清空吗?" << endl;
	cout << "1.确定" << endl;
	cout << "2.返回" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		//清空文件
		ofstream ofs(FILENAME, ios::trunc);//删除文件后新建
		ofs.close();
		if (this->mEmpArray != NULL)
		{
			for (int i = 0; i < mEmpNum; i++)
			{
				delete this->mEmpArray[i];
				this->mEmpArray[i] = NULL;
			}
			delete[] this->mEmpArray;
			this->mEmpArray = NULL;
			this->mEmpNum = 0;
			this->isEmptyFile = true;
		}
		cout << "清空成功" << endl;
	}
	system("pause");
	system("cls");
}

WorkManager::~WorkManager()
{
	if (this->mEmpArray != NULL)
	{
		for (int i = 0; i < mEmpNum; i++)
		{
			if (this->mEmpArray[i] != NULL)
			{
				delete this->mEmpArray[i];
			}
		}
		delete[] this->mEmpArray;
		this->mEmpArray = NULL;
	}
}

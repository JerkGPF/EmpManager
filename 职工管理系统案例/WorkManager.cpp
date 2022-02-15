#include "WorkManager.h"

WorkManager::WorkManager()
{
	//1.�ļ�������
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//���ļ�
	if (!ifs.is_open())
	{
		cout << "�ļ�������" << endl;
		//��ʼ������
		this->mEmpNum = 0;
		this->mEmpArray = NULL;
		this->isEmptyFile = true;
		ifs.close();
		return;
	}
	//2.�ļ����ڵ�Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "�ļ�Ϊ��" << endl;
		//��ʼ������
		this->mEmpNum = 0;
		this->mEmpArray = NULL;
		this->isEmptyFile = true;
		ifs.close();
		return;
	}
	//3.�ļ����ڣ��Ҳ�Ϊ��
	int num = this->getEmpNum();
	cout << "ְ����" << num << "��" << endl;
	this->mEmpNum = num;

	//���ٿռ�
	this->mEmpArray = new Worker * [this->mEmpNum];
	//���ļ��е����ݴ浽������
	this->initEmp();
	
}

void WorkManager::showMenu()
{
	cout << "**********************************" << endl;
	cout << "*******��ӭʹ��ְ������ϵͳ!******" << endl;
	cout << "********* 0.�˳�������� *********" << endl;
	cout << "********* 1.����ְ����Ϣ *********" << endl;
	cout << "********* 2.��ʾְ����Ϣ *********" << endl;
	cout << "********* 3.ɾ����ְְ�� *********" << endl;
	cout << "********* 4.�޸�ְ����Ϣ *********" << endl;
	cout << "********* 5.����ְ����Ϣ *********" << endl;
	cout << "********* 6.���ձ������ *********" << endl;
	cout << "********* 7.��������ĵ� *********" << endl;
	cout << "**********************************" << endl;
	cout << endl;
}

void WorkManager::exitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}

void WorkManager::addEmp()
{
	cout << "���������ְ��������" << endl;
	int addNum = 0;//�����û����������
	cin >> addNum;
	if (addNum > 0)
	{
		//���
		//��������¿ռ��С
		int newSize = this->mEmpNum + addNum;//������ = ԭ����¼����+��������
		//�����¿ռ�
		Worker** newSpace = new Worker * [newSize];
		//��ԭ���Ŀռ����ݿ������¿ռ���
		if (this->mEmpArray != NULL)
			for (int i = 0; i < this->mEmpNum; i++)
				newSpace[i] = this->mEmpArray[i];
		//���������
		for (int i = 0; i < addNum; i++)
		{
			int id;//���
			string name;//����
			int dSelect;//����ѡ��
			cout << "�������" << i + 1 << "����ְ�����:" << endl;
			cin >> id;

			cout << "�������" << i + 1 << "����ְ������:" << endl;
			cin >> name;

			cout << "��ѡ���ְ����λ" << endl;
			cout << "1.��ͨԱ��" << endl;
			cout << "2.����" << endl;
			cout << "3.�ϰ�" << endl;
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
			//��������Ա�����浽������
			newSpace[this->mEmpNum + i] = worker;
		}
		//�ͷ�ԭ�еĿռ�
		delete[] this->mEmpArray;
		//�����¿ռ��ָ��
		this->mEmpArray = newSpace;
		//����Ա������
		this->mEmpNum = newSize;
		this->save();		//������Ϣ
		cout << "�ɹ����" << addNum << "��Ա��" << endl;
		this->isEmptyFile = false;//�����ļ�״̬
		
	}
	else
		cout << "��������" << endl;
	system("cls");//����
}

void WorkManager::save()
{
	ofstream ofs;//������
	ofs.open(FILENAME, ios::out);//���ļ�
	for (int i = 0; i < this->mEmpNum; i++)//д��
	{
		ofs << this->mEmpArray[i]->mId << " "
			<< this->mEmpArray[i]->mName << " "
			<< this->mEmpArray[i]->mDeptId << endl;
	}
	ofs.close();//�ر��ļ�
}

int WorkManager::getEmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//��ȡ�ļ�
	int id;
	string name;
	int dId;
	int num = 0;//��¼����
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
	//�ж��ļ��Ƿ�Ϊ��
	if (isEmptyFile)
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	else
		cout <<"mEmpNum:"<< mEmpNum << endl;
		for (int i = 0; i < mEmpNum; i++)
			this->mEmpArray[i]->showInfo();//��̬���ó���ӿ�

	system("pause");
	system("cls");


}

void WorkManager::delEmp()
{
	if (this->isEmptyFile)
		cout << "�ļ������ڻ��߼�¼Ϊ��" << endl;
	else
	{
		//����ְ�����ɾ��
		cout << "��������Ҫɾ����ְ�����" << endl;
		int id = 0;
		cin >> id;
		int index = isExistEmp(id);
		if (index != -1)
		{
			for (int i = index; i < this->mEmpNum-1; i++)	
				this->mEmpArray[i] = this->mEmpArray[i + 1];//����ǰ��
			this->mEmpNum--;//���¼�¼����
			//��������
			save();
			cout << "ɾ���ɹ�" << endl;
	
		}
		else
			cout << "ɾ��ʧ�ܣ�δ�ҵ���Ա��" << endl;
	}
	system("pause");
	system("cls");
}
//�ж�ְ���Ƿ���ڣ����ڷ��������е�λ�ã������ڷ���-1��
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
		cout << "�ļ������ڻ��߼�¼Ϊ�գ�" << endl;
	}
	else
	{
		cout << "�������޸�ְ���ı��:" << endl;
		int id;
		cin >> id;
		int ret = this->isExistEmp(id);
		if (ret != -1)
		{
			//���ҵ����ְ��
			delete this->mEmpArray[ret];
			int newId = 0;
			string newName = "";
			int dSelect = 0;

			cout << "�鵽:" << id << "��ְ������������ְ����:" << endl;
			cin >> newId;

			cout << "������������:" << endl;
			cin >> newName;

			cout << "������ְ����λ:" << endl;
			cout << "1.��ͨԱ��" << endl;
			cout << "2.����" << endl;
			cout << "3.�ϰ�" << endl;
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
			//��������
			this->mEmpArray[ret] = worker;
			cout << "�޸ĳɹ�" << endl;
			//�����ļ�
			save();
		}
		else
		{
			cout << "�޸�ʧ��,���޴���" << endl;
		}
	}
	system("pause");
	system("cls");
}

void WorkManager::findEmp()
{
	if (this->isEmptyFile)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else
	{
		cout << "��������ҵķ�ʽ" << endl;
		cout << "1.��ְ����Ų���" << endl;
		cout << "2.��ְ����������" << endl;
		int select = 0;
		cin >> select;
		if (select == 1)
		{
			//���ձ�Ų�
			int id;
			cout << "��������ҵ�ְ�����:" << endl;
			cin >> id;
			int ret = isExistEmp(id);
			if (ret != -1)
			{
				//���ҳɹ�
				cout << "���ҳɹ�����ְ����Ϣ����" << endl;
				this->mEmpArray[ret]->showInfo();
			}
			else
			{
				cout << "����ʧ�ܣ����޴���" << endl;
			}

		}
		else if (select == 2)
		{
			//����������
			string name;
			cout << "����������" << endl;
			cin >> name;
			bool flag = false;//Ĭ��δ�ҵ�ְ��
			for (int i = 0; i < mEmpNum; i++)
			{
				if (this->mEmpArray[i]->mName == name)
				{
					cout << "���ҳɹ���ְ�����Ϊ:"
						<< mEmpArray[i]->mId 
						<< "��ְ����Ϣ����" << endl;
					flag = true;
					this->mEmpArray[i]->showInfo();//��ӡ��Ϣ

				}
			}
			if (flag == false)
				cout << "����ʶ�𣬲��޴���!" << endl;
		}
		else
		{
			cout << "��������" << endl;
		}
	}
	system("pause");
	system("cls");
}

void WorkManager::sortEmp()
{
	if (this->isEmptyFile)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
		return;
	}
	cout << "��ѡ���������" << endl;
	cout << "1.����" << endl;
	cout << "2.����" << endl;
	int sel = 0;
	cin >> sel;

	for (int i = 0; i < mEmpNum; i++)
	{
		int minOrMax = i;//������Сֵ�������ֵ�±�
		for (int j = i + 1; j < mEmpNum; j++)
		{
			if (sel == 1)//����
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
		//�жϵ�ǰ��i�Ƿ�Ϊ�������������С
		if (i != minOrMax)
		{
			Worker* temp = this->mEmpArray[i];
			this->mEmpArray[i] = this->mEmpArray[minOrMax];
			this->mEmpArray[minOrMax] = temp;
		}
	}
	cout << "����ɹ�" << endl;
	this->save();
	this->showEmp();
	
}

void WorkManager::cleanFile()
{
	cout << "ȷ�������?" << endl;
	cout << "1.ȷ��" << endl;
	cout << "2.����" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		//����ļ�
		ofstream ofs(FILENAME, ios::trunc);//ɾ���ļ����½�
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
		cout << "��ճɹ�" << endl;
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

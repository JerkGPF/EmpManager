#pragma once
#include "Worker.h"
#include <iostream>
#include <string>
using namespace std;
class Boss :
    public Worker
{
public:
    Boss();
    Boss(int id, string name, int dId);
    //��ʾ������Ϣ
    virtual void showInfo();
    //��ȡ��λ����
    virtual string getDeptName();
};


#pragma once
#include "Worker.h"
#include <iostream>
#include <string>
using namespace std;

class Manager :
    public Worker
{
public:
    Manager();
    Manager(int id,string name,int dId);
    //显示个人信息
    virtual void showInfo();
    //获取岗位名称
    virtual string getDeptName();
    
};


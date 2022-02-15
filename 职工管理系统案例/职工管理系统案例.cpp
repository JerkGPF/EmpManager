#include <iostream>
#include <string>
#include "WorkManager.h"
#include "Worker.h"
#include "Employee.h"
#include "Manager.h"
#include "Boss.h"
using namespace std;
int main()
{
    //创建实例化对象
    WorkManager wm;
    int choice = 0;//用来存储用户的选项
    while (true)
    {
        wm.showMenu();
        cout << "请输入您的选择:" << endl;
        cin >> choice;
        switch (choice)
        {
        case 0://退出
            wm.exitSystem();
            break;
        case 1://增加职工
            wm.addEmp();
            break;
        case 2://显示职工
            wm.showEmp();
            break;
        case 3://删除职工
            wm.delEmp();
            break;
        case 4://修改职工
            wm.ModEmp();
            break;
        case 5://查找职工
            wm.findEmp();
            break;
        case 6://排序
            wm.sortEmp();
            break;
        case 7://清空文档
            wm.cleanFile();
            break;
        default:
            system("cls");//清屏
            break;
        }
    }
}

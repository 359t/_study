#include <iostream>
#include "speechManager.h"
using namespace std;
#include <ctime>

int main()
{

    //随机数种子
    srand((unsigned int)time(NULL));
    speechManager sm;

    int choice = 0;

    // for(map<int , Speaker>:: iterator it = sm.m_Speaker.begin(); it != sm.m_Speaker.end(); it++){
    //     cout << it->first<<it->second.m_Name<<it->second.m_Score[0]<<endl;
    // }

    while (true)
    {
        sm.show_Menu();

        cout <<" 请输入您的选择"<<endl ;
        cin >> choice;

        switch(choice)
        {
            case 1 ://开始演讲比赛
            sm.startSpeech();
            break;

            case 2 ://查看往届记录
            sm.showRecord();
            break;

            case 3 ://清空比赛记录
            sm.clearRecord();
            break;

            case 0 ://退出比赛程序
            sm.exitSystem();
            break;

            default:
            system("cls");
            break;
        }

    }

    

    return 0;
}
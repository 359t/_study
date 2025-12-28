#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "speaker.h"
#include<algorithm>
#include <deque>
#include <functional>
#include <numeric>
#include <fstream>

using namespace std;


class speechManager
{
    public:

    speechManager();

    ~speechManager();

    void show_Menu();

    void exitSystem();

    //初始化属性
    void initSpeech();

    //创建选手
    void creatSpeaker();

    //开始比赛
    void startSpeech();

    //抽签
    void speechDraw();

    //比赛
    void speechContest();

    //显示得分
    void showScore();

    //保存记录
    void saveRecord();

    //读取记录
    void loadRecord();

    //显示往届记录
    void showRecord();

    //清空记录
    void clearRecord();

    //判断文件是否为空
    bool fileIsEmpty;

    //存放往届记录的容器
    map<int, vector<string>> m_Record;

    //成员属性
    vector<int> v1; //参赛选手
    vector<int> v2; //第一轮胜者
    vector<int> v3; //前三名

    map<int, Speaker> m_Speaker;

    //比赛轮数
    int m_index;

};

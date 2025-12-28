#include "speechManager.h"


speechManager::speechManager()
{
     this->initSpeech();

     this->creatSpeaker();
     //加载往届记录
     this->loadRecord();
}

speechManager::~speechManager(){
}

void speechManager::show_Menu(){

cout << "*****************************************************" <<endl;
cout <<"****************欢迎参加英语演讲比赛****************" <<endl;
cout << "******************1. 开始演讲比赛********************" <<endl;
cout << "******************2. 查看往届记录********************" <<endl;
cout << "******************3. 清空比赛记录********************" <<endl;
cout << "******************0. 退出比赛程序********************" <<endl;
cout << "*****************************************************" <<endl;
}

void speechManager::exitSystem(){

     cout<<"欢迎下次使用"<<endl;

     exit(0);
}

void speechManager::initSpeech(){
     this->v1.clear();
     this->v2.clear();
     this->v3.clear();
     this->m_Speaker.clear();

     this->m_index = 1;
     //初始化记录容器
     this->m_Record.clear();
}

 void speechManager:: creatSpeaker(){
     string name_seed = "ABCDEFGHIJKL";

     for(int i= 0 ; i < name_seed.size() ; ++i){
          string name ="选手";
          name += name_seed[i];

          Speaker sp;
          sp.m_Name = name;
          for(int i = 0; i<2;i++)
          {
               sp.m_Score[i] = 0;
          }

          this->v1.push_back(i+10001);


          this->m_Speaker.insert(make_pair(i+10001,sp));

     }
 }

    void speechManager:: startSpeech(){

     //第一轮比赛开始

     //抽签
     this->speechDraw();

     //比赛
     this ->speechContest();

     //显示结果
     this ->showScore();

     //第二轮比赛开始
     this->m_index++;

     //抽签
     this->speechDraw();

     //比赛
     this ->speechContest();

     //显示结果
     this ->showScore();

     //保存分数到文件
     this->saveRecord();
     cout<<"本届比赛圆满结束!"<<endl;

     //重置比赛获取记录
      this->initSpeech();

     this->creatSpeaker();
     //加载往届记录
     this->loadRecord();
    }

 void speechManager::speechDraw(){
     cout <<"第"<<this->m_index<<"轮的选手正在比赛"<<endl;
     cout <<"----------------------------------------------------"<<endl;
     cout << "抽签后演讲顺序如下："<<endl;


     if(m_index == 1){
          //第一轮比赛；
     random_shuffle(v1.begin(),v1.end());
     for(vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
     {
          cout<<*it<<" ";
     }
     cout<<endl;
     
     }
     else{
          //第二轮比赛
     random_shuffle(v2.begin(),v2.end());
     for(vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
     {
          cout<<*it<<" ";
     }
     cout<<endl;
     }
     cout<<"-----------------------------------------------------------"<<endl;

     cout<<"按Enter键盘继续"<<endl;
     
     while(true){
          cin.ignore();
          cin.get();
          break;
     }
     
     
 }

 void speechManager::speechContest(){

     cout<<"第"<<this->m_index<<"轮正式比赛"<<endl;
     multimap <double, int ,greater<double>> groupScore;
     int num = 0; //统计人员个数；

     vector<int> v_Src;
     if(this->m_index ==1){
          v_Src = this->v1;
     }
     else{
          v_Src = this->v2;
     }

     //遍历所有选手进行比赛
     for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it ++)
     {
          num++;
          deque<double> d;
          for( int i = 0; i< 10; i++){
               double score = (rand()%401+600)/10.f;
               // cout <<score<<" ";
               d.push_back(score);

          }
          // cout <<endl;
          sort(d.begin(),d.end(),greater<double>());
          d.pop_back();
          d.pop_front();

          double sum = accumulate(d.begin(),d.end(), 0.0f);
          double avg = sum/ (double)d.size();

          // cout<<"编号："<<*it<<" 姓名："<<this->m_Speaker[*it].m_Name<<" 平均分： "<<m_Speaker[*it].m_Score<<" ";
          // cout<<endl;

          this->m_Speaker[*it].m_Score[this->m_index-1] = avg;
          groupScore.insert(make_pair(avg, *it));
          if(num%6 == 0)
          {
               cout<<"第"<<num/6 <<"小组的名次如下："<<endl;
               for(multimap<double, int ,greater<double>>::iterator it = groupScore.begin(); it!= groupScore.end(); it++)
               {
                    cout<<"编号："<<it->second<<"姓名："<<this->m_Speaker[it->second].m_Name<<"成绩："
                                                  <<this->m_Speaker[it->second].m_Score[this->m_index-1]<<endl;
               }

          
               int count = 0;
               for(multimap<double, int ,greater<double>>::iterator it = groupScore.begin(); it!= groupScore.end()&&count!=3; it++,count++){

                    if(this->m_index  ==1){
                         v2.push_back((*it).second);
                         
                    }
                    else{
                         v3.push_back((*it).second);
                         
                    }
               }
               groupScore.clear();
          }
          
     }
     cout <<"第"<<this->m_index<<"轮比赛完成"<<endl;
     cout<<"----------------------------------------------------"<<endl;

     cout<<"按Enter键盘继续"<<endl;
     
     while(true){
          cin.ignore();
          cin.get();
          break;
     }
 }

 void speechManager:: showScore(){
     cout<<"--------------------------------------------第" <<this->m_index<<"轮晋级选手信息--------------------"<<endl;

     vector<int> v;
     if(this->m_index ==1){
          v=v2;
     }
     else{
          v=v3;
     }
     for(vector<int>::iterator it = v.begin(); it != v.end(); it ++)
     {
          cout <<" 编号： " << *it << " 姓名："<<this->m_Speaker[*it].m_Name<< " 得分： "<< 
          this->m_Speaker[*it].m_Score[this->m_index-1] <<endl;
     }
     cout <<endl;
    
 }

 void  speechManager:: saveRecord(){
     ofstream ofs;
     ofs.open("speech.csv",ios::out| ios::app);

     for (vector<int>:: iterator it = v3 .begin(); it != v3.end(); it++)
     {
          ofs << *it << ","
                  << m_Speaker[*it].m_Score[1]<<",";
     }

     ofs<<endl;

     ofs.close();
     cout<<"记录已经保存"<<endl;

     this->fileIsEmpty = false;

 }



 void speechManager::loadRecord(){
     ifstream ifs("speech.csv",ios::in);

     if(!ifs.is_open())
     {
          this->fileIsEmpty = true;
          //cout<<"文件不存在"<<endl;
          ifs.close();
          return;
     }
     char ch;
     ifs >> ch;
     if(ifs.eof())
     {
          //cout <<"文件为空"<<endl;
          this->fileIsEmpty =true;
          ifs.close();
          return;
     }
     this->fileIsEmpty = false;

     ifs.putback(ch);

     string data;
     int index = 0;
     
     while (ifs >>data)
     {

          vector<string> v;
          int pos = -1; //“，”位置；
          int start = 0; //起始位置

          while(true)
          {
               pos =data.find(",",start);
               if(pos ==-1){

                    break;
               }
               string temp =data.substr(start, pos -start);
               //cout<<temp <<endl;
               v.push_back(temp);
               start =pos+1;
          }
     this->m_Record.insert(make_pair(index,v));
     index ++;
          
     }


     ifs.close();
 }

  void speechManager::showRecord(){

     if(this->fileIsEmpty)
     {
          cout<< "文件为空或文件不存在!"<<endl;
     }
     else{
     for(int i = 0 ;i<this-> m_Record.size() ; i++)
          {
               cout<<"第"<< i+1<<"届"
               <<"冠军编号：" << this->m_Record[i][0]<<" 得分：" << this->m_Record[i][1] << " "
               <<"亚军编号：" << this->m_Record[i][2]<<" 得分：" << this->m_Record[i][3] << " "
               <<"季军编号：" << this->m_Record[i][4]<<" 得分：" << this->m_Record[i][5] << " "<<endl;

               

          }
     cout<<"按Enter键盘继续"<<endl;
     
     while(true){
          cin.ignore();
          cin.get();
          break;
     }


     return;
}
}

void speechManager:: clearRecord(){

     cout<<"确定清空?" <<endl;
     cout<< "1、确定"<<endl;
     cout <<"2、返回" <<endl;

     int select =0;
     cin >>select;

     if(select == 1)
     {
          ofstream ofs("speech.csv" ,ios::trunc);
          ofs.close();

          this->initSpeech();

          this->creatSpeaker();

          this->loadRecord();

          cout<<"清空成功！"<<endl;
     }

     cout<<"按Enter键盘继续"<<endl;
     
     while(true){
          cin.ignore();
          cin.get();
          break;
     }
}
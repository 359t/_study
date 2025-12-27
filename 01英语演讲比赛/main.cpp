#include <iostream>
#include<vector>
using namespace std;

int main()
{
    vector<int> v;
    vector<int>::iterator it=v.begin();
    (*it)=1;
    cout <<*it<<endl;
    
    return 0;
}
#include "SkipList.h"
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

void debug()
{
        //srand(time(NULL));
    
    //for(size_t j = 0; j < 100; j++)
    //{
        SkipList<int> list1;
        //cout<<"list1"<<endl;
        for(int i=0; i<10000;i++)
            list1.insert(rand()%51);

        for(int i=0; i<10000;i++)
            list1.insertRec( (rand()%51) + 50);
        list1.insertRec(2);
        list1.insertRec(3);
        list1.insertRec(4);
        list1.insertRec(4);
        list1.insertRec(625);
        list1.print();

        //list1.sup_ele(2);
        //for(int i=0; i<1000;i++)
        //    list1.sup_ele(rand()%1001);
        //list1.empty();

        //list1.print();
        //if(list1.exists(2))
           // cout<<"exists"<<endl;
        //list1.empty();
        //list1.sup_ele(2);
        //list1.print();
        //if(list1.exists(625))
        //{
           // cout<<"not ok"<<endl;
        //list1.print();

        //}
        
    //}
}


void complexity()
{
    int n = 500;
    int step = 2;
    time_point <system_clock> start , end;
    vector<uint> times_skip_list;
    //cout<<"nb , t"<<endl;
    for(int i=step; i<n;i+=step)
    {
        SkipList<short unsigned int> list;
        start = system_clock::now();
        for(int j=0; j<i; j++)
        {
            //std::cout << "hello";
            list.insertRec( rand()%n );
        }
        end = system_clock::now();
        uint diff = duration_cast<microseconds>(end-start).count();
        times_skip_list.push_back(diff);

    }
    for(int i=0; i<times_skip_list.size(); i++)
    {
        cout<<step*(i+1)<< " ; "<<times_skip_list[i]<<endl;
    }
    
}

int main()
{
    complexity();
    //debug();
    return 0;
}
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <list>
using namespace std;

struct Student
{
    int index;
    int leavingTime;
    int comingTime;
    int ans;
    Student()
    {
        ans = 0;
    };
    Student(int i, int l, int r, int a)
    {
        index = i;
        leavingTime = r;
        comingTime = l;
        ans = a;
        Student();
    };
    int operator < (const Student & rhs) const
    {
        return comingTime < rhs.comingTime;
    };
};

list <Student> Queue;
queue <Student> waitingStu;
vector <Student> stu;

int main()
{
    int t, n, l, r;
    cin >> t;
    while(t--)
    {
        while(!waitingStu.empty())
            waitingStu.pop();
        Queue.clear();
        stu.clear();
        cin >> n;
        for(int i = 1; i <= n; i++)
        {
            cin >> l >> r;
            stu.push_back(Student(i, l, r, 0));
        }

        for(int i = 0; i < n; i++)
            waitingStu.push(stu[i]);

        int sec = 0;
        while((!waitingStu.empty()) || (!Queue.empty()))
        {
            sec++;
            Student curstu;

            while(!waitingStu.empty())
            {
                curstu = waitingStu.front();
                if(curstu.comingTime > sec)
                    break;
                waitingStu.pop();
                Queue.push_back(curstu);
            }

            if(!Queue.empty())
            {
                while(Queue.begin()->ans < 0)
                    Queue.pop_front();

                curstu = Queue.front();
                Queue.pop_front();

                while(Queue.begin()->ans < 0)
                    Queue.pop_front();

                stu[curstu.index-1].ans = sec;
            }

            list<Student>::iterator itr;
            for(itr = Queue.begin(); itr != Queue.end(); itr++)
            {
                if(itr->leavingTime <= sec)
                {
                    int index = (*itr).index;
                    //cerr << index << endl;
                    stu[index-1].ans = -1;
                    itr->ans = -1;
                    //Queue.erase(itr);
                }

            }
        }

        for(int i = 0; i < n; i++)
        {
            if(i != 0)
                cout << " " ;
            cout << (stu[i].ans <= 0 ? 0 : stu[i].ans) ;
        }
        cout << endl ;
    }
}

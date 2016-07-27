#include<iostream>
#include<thread>
#include<vector>
using namespace std;

int a(int x)
{
    int s = 0;
    for(int i = 0; i < 100; i++)
        s += i;
    return s;
}

int main()
{
    unsigned int thread_no = 10000;
    vector<thread> t(thread_no);

    for(int i = 0; i < 10; i++)
        t[i] = std::thread(a, 10);

    for(thread& t_now : t)
        t_now.join();

    cout << "OK" << endl;
    cin.get();
}

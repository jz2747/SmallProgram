#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

bool comp(int a, int b)
{
	return a > b;
}
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    vector<int> v;
    for(int i = 1; i < 10; i ++)
    	v.push_back(i*5);
    make_heap(v.begin(), v.end(), comp);
    vector<int>::iterator it;
    for (it = v.begin(); it != v.end(); it++)
    	cout << *it << " ";
    cout << endl;
    pop_heap(v.begin(), v.end(), comp);
    for (it = v.begin(); it != v.end(); it++)
    	cout << *it << " ";
    cout << endl;
    v.pop_back();
    for (it = v.begin(); it != v.end(); it++)
    	cout << *it << " ";
    cout << endl;
    v.push_back(49);
    push_heap(v.begin(), v.end(), comp);
    for (it = v.begin(); it != v.end(); it++)
    	cout << *it << " ";
    cout << endl;
    return 0;
}




#include<set>
#include<iostream>

using namespace std;

int main(){
	set<int> s;
	s.insert(1);
	set<int>::iterator it;
	for(it = s.begin(); it != s.end(); it++)
		cout << *it << endl;
	return 0;
	
}

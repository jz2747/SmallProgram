#include<iostream>
#include<string>
#include<deque>
#include<sstream>
using namespace std;
int main(){
	deque<char> deq;
	string s;
	stringstream ss;
	getline(cin, s);
	for (int i = 0; i < s.length(); i++){
		if (s[i] >= 'A' && s[i] <= 'Z'){
			deq.push_back(s[i]);
		}
		else if (s[i] >= 'a' && s[i] <= 'z'){
			if(!deq.empty() && deq.back() == (s[i] - 'a' + 'A')){
				deq.pop_back();
			}
			else{
				deq.push_back(s[i]);
			}
		}
	}
	while(!deq.empty()){
		ss << deq.front();
		deq.pop_front();
	}
	cout << ss.str() << endl;
	return 0;
}


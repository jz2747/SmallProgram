#include<iostream>
#include<string>
using namespace std;
int main(){
	string s;
	for(int i = 1; i < 5; i++){
		getline(cin,s);
		cout << s << endl;
	}
	return 0;
}

#include<iostream>
#include<unordered_map>
using namespace std;

int main(){
	unordered_map<char,int> hasht;
	char inputs;
	while(cin >> inputs){
		if(hasht.find(inputs) == hasht.end()){
			hasht.insert(make_pair(inputs,1));
		}
		else{
			cout << inputs << endl;
			break;
		}
	}
	return 0;
}

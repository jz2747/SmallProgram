#include<iostream>
#include<stack>
using namespace std;

int main(){
	stack<char> stk;
	int max = 0;
	int arrive[] = {900,940,950,1100,1500,1800};
	int depart[] = {910,1200,1120,1130,1900,2000};
	int arvIndex = 0;
	int depIndex = 0;
	while(arvIndex < sizeof(arrive)/sizeof(int)){
		if(arrive[arvIndex] <= depart[depIndex]){
			stk.push('a');
			max = (stk.size() > max) ? stk.size() : max;
			arvIndex++;
		}
		else if (arrive[arvIndex] > depart[depIndex]){
			stk.pop();
			depIndex++;
		}
	}
	cout << max << endl;
	while(1){
		stk.push(arrive[0]);
		stk.pop();
	}
	return 0;
}

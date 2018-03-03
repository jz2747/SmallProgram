#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include<string>
using namespace std;


using namespace std;

bool comp(vector<int>* a, vector<int>* b){
    return a->size() > b->size();
}

bool merge(vector<int>* a, vector<int>* b){
    bool finished = true;
    vector<int>* first;
    vector<int>* second;
    if(a->front() < b->front()){
        first = a;
        second = b;
    }
    else{
        first = b;
        second = a;
    }
    if(first->size() == second->size())
        first->push_back(1001);
    vector<int>::iterator fit, sit;
    fit = first->begin();
    sit = second->begin();
    while(fit != first->end() && sit != second->end()){
        if(*sit > *fit && *sit < *(fit+1)){
            sit++;
            fit++;
        }
        else{
            finished = false;
            break;
        }
    }
    if(first->back() == 1001)
        first->pop_back();
    return finished;
}

int twoCharaters(string s) {
    // Complete this function
    vector<int>* v[26];
    for(int i = 0; i < 26; i++)
        v[i] = new vector<int>;
    for(int i = 0; i < s.size(); i++)
        v[s[i]-'a']->push_back(i);
    sort(v, v+26, comp);
    for(int i = 0; i < 26; i++){
        for(vector<int>::iterator it = v[i]->begin(); it != v[i]->end(); it++)
        	cout << *it << " " ;
        cout << i << endl;
    }
    for(int i = 1; i < 26; i++){
    	if(v[i]->size() > 0 && v[i-1]->size() > 0 )
        if(v[i]->size() == v[i-1]->size() || v[i]->size() == v[i-1]->size() - 1)
            if(merge(v[i], v[i-1])){
                return v[i]->size() + v[i-1]->size();        
            }           
    }
    return 0;
}

int main() {
    int l;
    cin >> l;
    string s;
    cin >> s;
    int result = twoCharaters(s);
    cout << result << endl;
    return 0;
}


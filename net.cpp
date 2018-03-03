#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int N, Q;
    int x, y;
    char c;
    cin >> N >> Q;
    set<int> sets[N];
    int index[N];
    for(int j = 0; j < N; j++){
        index[j] = j;
        sets[j].insert(j);
    }
    for(int j = 0; j < Q; j++){
        cin >> c;
        if(c == 'M'){
            cin >> x >> y;
            x--;
            y--;
            if(index[x] != index[y]){
            	int tempy = index[y];
            	set<int>::iterator it;
                for(it = sets[tempy].begin(); it != sets[tempy].end(); ++it){
                  sets[index[x]].insert(*it);
                  index[*it] = index[x];
                  sets[tempy].erase(it);
                }
            }
        }
        else if(c == 'Q'){
            cin >> x;
            x--;
            cout << sets[index[x]].size() << endl;
        }
    }
    return 0;
}

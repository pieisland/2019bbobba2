// Online C++ compiler to run C++ program online
#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

/*
다른것보다도 문제가 됐던 건..
to_string을 안 써본거랑.
매개변수 넘길 때 뭐 넘겨야할지 어어 하고 있었음.
dfs도 사실 너무 오랜만이라섴 ㅋㅋㅋ 노답이기도 했고.
잘.. 못함. ㅋ
*/

int numbers[5][5];
int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
vector<string> mystring;

void dfs(int y, int x, int cnt, string mystr) {
    if(cnt == 6) {
        int possible =1;
        for(int i=0;i<mystring.size();i++) {
            if(mystring[i] == mystr)//이렇게 대놓고 비교가 되나?
            {   possible =0;
                break;
                
            }
        }
        if(possible) mystring.push_back(mystr);
        
        return;
    }
    
    for(int i=0;i<4;i++) {
        int ny = dir[i][0] + y;
        int nx = dir[i][1] + x;
        
        if(ny>=0 && ny<5 && nx>=0 && nx <5) {
            dfs(ny, nx, cnt+1, mystr + to_string(numbers[ny][nx]));
        }
    }
    
}

int main() {
    for(int i=0;i<5;i++) {
        for(int j=0;j<5;j++){
            cin>>numbers[i][j];
        }
    }
    
    for(int i=0;i<5;i++) {
        for(int j=0;j<5;j++){
            dfs(i, j, 1, to_string(numbers[i][j]));
        }
    }
    
    cout<<mystring.size();

    return 0;
}

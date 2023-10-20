// Online C++ compiler to run C++ program online
#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

int n;
int arr[15][2];

int maxMoney;

void dfs(int day, int days, int pay) {
    
    if(day + days -1 < n) {
        if(pay > maxMoney) maxMoney = pay;
    }
    else {//그때까지 일을 못 행.
        return;
    }
    
    //cout<<day + days -1<<endl;

    //그 다음날부터 봐야하는거였는데 그 날부터로 하니까 계속 막혔음.
    for(int i=day+days; i<n;i++) {
        dfs(i, arr[i][0], pay + arr[i][1]);
    }
}

int main() {
    cin>> n;
    for(int i=0;i<n;i++) {
        int t, p; // 요소일이 t이고 그때 얻는 돈이 p다.
        cin>>t>>p;
        
        arr[i][0] = t;
        arr[i][1] = p;
    }

    //n+1일째에 퇴사를 한다는 사실..
    for(int i=0;i<n;i++) {
        dfs(i, arr[i][0], arr[i][1]);
    }
    
    cout<<maxMoney;
    
    return 0;
}

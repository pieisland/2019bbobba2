// Online C++ compiler to run C++ program online
#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

int n, m;
int arr[50][50];

vector<pair<int, int>> home;
vector<pair<int, int>> chicken;
int minDist = 987654321;

void dfs(int idx, int cnt, vector<int> selected) {
    if(idx==chicken.size()) return;
    
    if(cnt <= m) {//m개 이하의 치킨집을 구했다.
        //치킨거리 구하기

        int sumdist =0;
        for(int h=0;h<home.size();h++) {
            int hy = home[h].first;
            int hx = home[h].second;
            int chickenDist = 987654321;
            
            for(int i=0;i<selected.size();i++) {
                int dist =0;
                
                int cy = chicken[selected[i]].first;
                int cx= chicken[selected[i]].second;
                //<<cy<<cx<<endl;
                
                if(hy - cy <0) dist += cy-hy;
                else dist += hy-cy;
                
                if(hx - cx<0) dist += cx - hx;
                else dist += hx - cx;
                
                if(dist <chickenDist) chickenDist = dist;
            }
            
            sumdist += chickenDist;
            
            //cout<<cnt<<"   "<<sumdist<<endl;
        }
        
        if(sumdist < minDist) minDist = sumdist;
    }
    
    for(int i=idx+1; i<chicken.size(); i++) {
        selected.push_back(i);
        dfs(i, cnt+1, selected);
        selected.pop_back();
    }
}

int main() {
    cin>>n>>m;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++) {
            cin>>arr[i][j];
        
            if(arr[i][j] ==1) {
                home.push_back({i, j});
            }
            else if(arr[i][j] ==2) {
                chicken.push_back({i, j});
            }
        }
    }
    
    //cout<<chicken.size()<<endl;
    for(int i=0;i<chicken.size();i++){
        vector<int> selected;
        selected.push_back(i);
       // cout<<"아니 머하냐고~~"<<endl;
        dfs(i, 1, selected);//뭘 더 적어야할지를 모르겠네..
        selected.pop_back();
    }
    
    cout<<minDist;
    
    return 0;
}

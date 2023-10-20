// Online C++ compiler to run C++ program online
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;
/*
vector 그냥 쓰려면.. using namespace 안 쓰면 에러나는 건 처음 알았다.

그리고 이런 방향 움직이는거는.. dir 배열 만들어서 하는 게 제일 좋고, 
기존걸 덮어쓰는 것 때문에 고민이 되는거는 기존 배열을 복사한 형태를 사용하면 되는거였다.
그러면 되는거구나..
이것때문에 너무 시간 잡아먹다가.. 화가 났고.
추가로 더 신경을 써야 되는 부분은, 
배열 초기화를 잘 하자는 것.
그리고 왜 안 되나 싶으면 출력을 해보자는거다..

에휴.... 예전에 잘 풀었던 문제를 다시 풀었을 때 못 해 처먹겠을 땐 너무 슬픈 것 같다...

*/


int bang[51][51];
int tmp[51][51];
int r, c, t;
int dir[4][2] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};

//공기청정기 위치 저장.
vector<pair<int, int>> air;

bool isinside(int y, int x) {
    if(y>=0 && y<r && x>=0 && x<c) return true;
    else return false;
}

void spread() {
      
    for(int i=0;i<r;i++) {
        for(int j=0;j<c;j++){
            tmp[i][j] =0;
        }
    }
    
    
    
    vector<pair<int, int>> dust;
    for(int i=0;i<r;i++) {
        for(int j=0;j<c;j++) {
            if(bang[i][j]>0){
                dust.push_back({i, j});
            }
        }
    }
    
    int len = dust.size();
    for(int i=0;i<len;i++) {
        int y= dust[i].first;
        int x = dust[i].second;
        
        int cnt=0;
        int okidx[4] = {0, 0, 0, 0};
        for(int j=0;j<4;j++) {
            int ny = y + dir[j][0];
            int nx = x + dir[j][1];
            
            //몇 군데로 미세먼지가 뻗어나갈 수 있을까.
            if(isinside(ny, nx) && bang[ny][nx]!=-1) {
                cnt++;
                okidx[j] = 1;//뻗어나갈 수 있는 인덱스를 미리 저장해둠.
            }
        }
        //저 for문에서 나와서 해야하는거 아님...? 근데 위치를 알아야지.
        int val = bang[y][x];
        int spreadVal = val/5;
        int myval = val - spreadVal*cnt;
        bang[y][x] = myval;
        
        for(int j=0;j<4;j++){
            int ny = y + dir[j][0];
            int nx = x + dir[j][1];
            
            if(okidx[j]==1) {
                tmp[ny][nx] += spreadVal;
            }
        }
    }
    
    //다 구했으면 반영을 해주면 됨.
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++) {
            bang[i][j] += tmp[i][j];
        }
    }
  
    
    
    //모든 걸 다 하고나면 tmp 배열을 0으로 해줘야한다.
}

void showBang(){
    cout<<"show bang"<<endl;
    for(int i=0;i<r;i++) {
        for(int j=0;j<c;j++) {
            cout<<bang[i][j]<<' ';
        }
        cout<<endl;
    }
}


void air_on() {
    /*
    공기청정기 가동,.. 회전을 신경써야 함.
    dust의 이동...을 어떻게 구현할 것인가...
    넣을 때 맨 처음에 들어간 게 위쪽으로 바람 보내는거고
    아래쪽에 들어간 게 아래쪽으로 바람 보내는거.
    방향도 신경 써야 함. 어떻게??
    */
    
    int uy, ux;
    int dy, dx;
    uy = air[0].first;
    ux = air[0].second;
    dy = air[1].first;
    dx = air[1].second;
    
    //r,c는 배열의 크기고...
    //공기청정기 위치로 해야될텐데....그지같이 함..
    //존나 헷갈림.......
    
    int wind1[4][2] = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};
    int wind2[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    
    
    //좋은거 하나 알아간다. 복사하면 된다. 이전거 덮어쓰는 게 신경이 쓰인다면.
    for(int i=0;i<r;i++) {
        for(int j=0;j<c;j++) {
            tmp[i][j] = bang[i][j];
        }
    }
    
    bang[uy][ux+1] =0;
    bang[dy][dx+1] =0;
    
    int cy = uy;
    int cx = ux+1;
    
    int d =0;
    while(1) {
        int ny = cy + wind1[d][0];
        int nx = cx + wind1[d][1];
        
        //이것때문에 어차피 멈춰서 문제가 안 됐던 거구나..
        if(bang[ny][nx]==-1) break;
        
        if(isinside(ny, nx)) {
            bang[ny][nx] = tmp[cy][cx];
            cy = ny;
            cx = nx;
        }
        else {
            d++;
        }
        
        if(d==4) break;
    }

    d=0;
    
    cy = dy;
    cx = dx+1;
    while(1) {
        int ny = cy+wind2[d][0];
        int nx = cx+wind2[d][1];
        
        if(bang[ny][nx]==-1) break;
        
        if(isinside(ny, nx)) {
            bang[ny][nx] = tmp[cy][cx];
            cy = ny;
            cx = nx;
        }
        else {
            d++;
        }
        
        if(d==4) break;
    }
    
    /*
    //위쪽 공기청정기 가동으로 반시계방향 회전 구현..
    for(int k=0;k<=ny-2;k++){
        bang[k+1][0] = bang[k][0];
    }
    
    for(int k=1;k<c;k++) {
        bang[0][k-1] = bang[0][k];
    }
    
    for(int k=ny;k>=1;k--) {
        bang[k-1][c-1] = bang[k][c-1];
    }
    
    for(int k=c-1; k>=1;k--) {
        bang[ny][k+1] = bang[ny][k]; 
    }
    
    //헷갈려서 작성을 못 하겠음..;;;
    bang[ny][1] =0;
    
    
    //아래쪽 공기청정긱 가동. 시계방향 회전.
    for(int k=r-1;k>=dy+2;k--) {
        bang[k-1][0] = bang[k][0];
    }
    for(int k=1;k<=c-1;k++){
        bang[r-1][k-1] = bang[r-1][k];
    }
    for(int k=r-2;k>=dy;k--){
        bang[k+1][c] = vang[k][c-1];
    }
    for(int k=c-2;k>=dx+1;k--) {
        bang[dy][k+1] = bang[dy][k];
    }
    bang[dy][dx+1] = 0;*/
}

int main() {
    int answer =0;
    
    cin >>r >>c >>t;
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++) {
            cin>>bang[i][j];
            if(bang[i][j] == -1) {
                air.push_back({i, j});
            }
        }
    }

    for(int i=0; i<t; i++) {
        //cout<<"spread.."<<endl;
        spread();
        
        
        //showBang();
        
        //cout<<"air on..."<<endl;
        air_on();
        
        //showBang();
    }

    for(int i=0;i<r; i++) {
        for(int j=0;j<c;j++) {
            if(bang[i][j]!=-1) {
                answer+= bang[i][j];
            }
        }
    }
    
    cout<<answer;

    return 0;
}

// Online C++ compiler to run C++ program online
#include <iostream>
#include <vector>
#include <math.h>

int mymap[20][20];
int diceRow[4];//1 위
int diceCol[4];//1, 3 위 바닥
int dir[4][2] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};//동서북남
int n, m;

using namespace std;

/*
하하.... 그림에서 전개도 저렇게 나와있다고
4개 3개 잡고 만들었던 게 바보임.
변경이 되는 부분은 남북 움직일 때 동서 움직일 때 각각 4개씩 바뀌는데
저 전개도 그대로 만들면 동서로 움직일 때 세 개만 바뀐다는 의미가 됨..
그래서 무시하고 4개씩 해야하고, 바닥면이랑 윗면은 동유하고 있어야 함.
고정되는 건 서로에서 두 개 밖에 없다는 걸 기억... ㅠㅠㅠ 시간 너무 걸려서 화났다.
*/

bool isinside(int y, int x) {
    if(y>=0 && y<n && x>=0 && x<m) return true;
    else return false;
}

void moveDice(int rot){
    if(rot==1) {
        //dong
        int tmp = diceRow[3];
        diceRow[3] = diceRow[2];
        diceRow[2] = diceRow[1];
        diceRow[1] = diceRow[0];
        diceRow[0] = tmp;
        diceCol[1] = diceRow[1];
        diceCol[3] = diceRow[3];
    }
    else if(rot==2){
        //seo
        int tmp = diceRow[0];
        diceRow[0] = diceRow[1];
        diceRow[1] = diceRow[2];
        diceRow[2] = diceRow[3];
        diceRow[3] = tmp;
        diceCol[1] = diceRow[1];
        diceCol[3] = diceRow[3];
    }
    else if(rot==3){
        //buk
        int tmp = diceCol[0];
        diceCol[0] = diceCol[1];
        diceCol[1] = diceCol[2];
        diceCol[2] = diceCol[3];
        diceCol[3] = tmp;
        diceRow[1] = diceCol[1];
        diceRow[3] = diceCol[3];
    }
    else if(rot==4) {
        //nam
        int tmp = diceCol[3];
        diceCol[3] = diceCol[2];
        diceCol[2] = diceCol[1];
        diceCol[1] = diceCol[0];
        diceCol[0] = tmp;
        diceRow[1] = diceCol[1];
        diceRow[3] = diceCol[3];
    }
}

void setDice(int y, int x) {
    if(mymap[y][x] ==0) {
        mymap[y][x] = diceCol[3];
    }
    else {
        diceCol[3] = mymap[y][x];
        diceRow[3] = mymap[y][x];
        mymap[y][x] =0; 
    }
}

void showDice() {
    cout<<"show dice!!!"<<endl;
    
    for(int i=0;i<4;i++) {
        cout<<diceCol[i]<<' ';
    }
    cout<<endl;
    for(int i=0;i<3;i++) {
        cout<<diceRow[i]<<' ';
    }
    cout<<endl;
}

int main() {
    int y, x;//주사위가 처음에 높여있는 좌표.
    int k;
    
    //int answer =0;
    
    cin>>n>>m>>y>>x>>k;
    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++) {
            cin>>mymap[i][j];
        }
    }
    
    //cout<<"answer is ..."<<endl;
    
    //move
    int cy = y;
    int cx = x;
    for(int i=0;i<k;i++) {
        int move;
        cin>>move;
        
        int ny;
        int nx;
        ny = cy + dir[move-1][0];
        nx = cx + dir[move-1][1];
        //동서북남 순서 1 2 3 4
        if(isinside(ny, nx)) {
         //뭔가 더 해야지 
            cy = ny;
            cx = nx;
            
            //좌표 바꿔줬고....
            moveDice(move);
            setDice(cy, cx);
            //showDice();
            
            //col을 봐도 상관 없긴 하지만...
            //answer += diceRow[1];
            //cout<< "answer is..."<<endl;
            cout<< diceRow[1]<<endl;
        }
    }

    return 0;
}

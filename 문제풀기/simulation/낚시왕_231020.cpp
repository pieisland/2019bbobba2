// Online C++ compiler to run C++ program online
#include <iostream>
#include <vector>

using namespace std;

/*
풀리지만 시간초과다.
그건 해결 못하겠다.. ^^)
있는 상어인지 확인하는 부분때문에 시간초과 나는 것 같다.
상어 수가 많을 수 있어서.. 아오..
시간 너무 오래걸림 ㅋㅋㅋㅋ
*/

typedef struct {
    int posy;
    int posx;
    int speed;
    int dir;
    int size;
    int dead;
} Shark;

vector<Shark> sharks;
int checkSharkCnt[100][100];

int r, c, m;

int getShark(int col) {
    int ret =0;
    
    int cnt = sharks.size();
    
    //땅과 가장 가까운 상어를 잡는거래...
    int ground = 987654321;
    int idx;
    for(int i=0;i<cnt; i++){
        if(sharks[i].posx == col && sharks[i].dead ==0) {
            //ret += sharks[i].size;
            //sharks[i].dead = 1;
            if(sharks[i].posy < ground) {
                ground = sharks[i].posy;
                idx = i;
            } 
        }
    }
    
    if(ground != 987654321) {
        ret = sharks[idx].size;
        sharks[idx].dead =1;
    }
    
    return ret;
}

void showShark(){
    cout<<"shark cnt"<<endl;
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            cout<<checkSharkCnt[i][j]<<' ';
        }
        cout<<endl;
    }
    cout<<endl;
}

void moveShark() {
    /*
    고려할 점...
    1. 속력에 따라서 위치가 어디인지 일단 잘 구해야 함.
    2. 같은 위치의 상어에 대해서 크기를 파악해야함.
    3. 크기 작은 상어는 죽음 처리해야 함.
    
    근데 같은 위치의 상어를 구할 때의 문제가 또 있음. 
    일단은 다 옮기고 나서 확인을 해야하는데,
    상어의 자리를 표시하기 위한 배열을 만들어도 될까...?
    그것때문에 근데 만들기가 애매하긴 한데;
    거기다가 움직인 애를 먼저 저장을..하려고 해도 사실 인덱스도
    같이 저장해야 어떤 애인지 아는건데 애매해짐.. 정말 애매하네;
    이것때문에 어려어했던 것 같기도 함. 
    
    */
    
    int len = sharks.size();
    
    //모든 상어가 움직인다.
    for(int i=0;i<len;i++) {
        if(sharks[i].dead ==1 ) continue;
        
        int speed = sharks[i].speed;

        int dir = sharks[i].dir;
        
        //cout<<"sharkpos before: "<<sharks[i].posy<<" "<<sharks[i].posx<<endl;
        
        if(dir >= 2) {
            //좌우 움직임
            int cx = sharks[i].posx;
            for(int k=0;k<speed;k++) {
                if(dir == 2) {//오른쪽으로
                    int nx = cx +1;
                    if(nx == c) {
                        cx = c-2;
                        dir = 3;
                    } else {
                        cx = nx;
                    }
                }
                else {//왼쪽으로
                    int nx = cx -1;
                    if(nx == -1) {
                        cx = 1;
                        dir = 2;
                    }
                    else {
                        cx = nx;
                    }
                    
                }
            }
            sharks[i].posx = cx;
            sharks[i].dir = dir;
        }
        else {
            //상하 움직임
            int cy = sharks[i].posy;
            for(int k=0;k<speed;k++) {
                if(dir == 1) {//아래로
                    int ny = cy +1;
                    if(ny ==r) {
                        cy = r-2;
                        dir = 0;
                    } else {
                        cy = ny;
                    }
                }
                else {//위로
                    int ny = cy -1;
                    if(ny == -1) {
                        cy = 1;
                        dir = 1;
                    }
                    else {
                        cy = ny;
                    }
                }
            }
            sharks[i].posy = cy;
            sharks[i].dir = dir;
        }
                    
        //cout<<"sharkpos after: "<<sharks[i].posy<<" "<<sharks[i].posx<<endl;
        checkSharkCnt[sharks[i].posy][sharks[i].posx] +=1;
    }
    
    //showShark();
}

void killShark(int y, int x) {
    //이름이 잘 안 맞기는 하지만;; 하는대로 하자고.
    int len = sharks.size();
    
    int maxSharkSize = 0;
    vector<int> sameSizeSharkIdx;
    //int bigSharkIdx;
    for(int i=0;i<len;i++) {
        if(sharks[i].posy == y && sharks[i].posx == x) {
            sameSizeSharkIdx.push_back(i);
            if(maxSharkSize < sharks[i].size) {
                maxSharkSize = sharks[i].size;
            }
        }
    }
    
    for(int i=0;i<sameSizeSharkIdx.size();i++) {
        if(sharks[i].size!=maxSharkSize){
            sharks[i].dead = 1;
        }
    }
    
    //이렇게 작성하면 할 이유가 없음. 
    //return maxSharkSize;
}

void eatShark() {
    //동일한 위치에 있다면 더 몸집이 큰 상어가 잡아먹어야 한다
    //동일한 위치에 있음을 파악하는 방법?
    //쓰다가 또 거져가지고;;; 어이가 없음.. ㅋㅋㅋㅋ
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++) {
            if(checkSharkCnt[i][j]>1) {
                //여러 명의 상어가 있는 곳이라면, 
                //int maxSharkSize = getMaxSharkSize(i, j);
                killShark(i, j);
            }
            
            //볼장다봤으니 그냥 영기서 클리어해버림....
            checkSharkCnt[i][j] = 0;
        }
    }
    
}

int main() {
    int answer =0;
    
    cin>>r>>c>>m;
    
    for(int i=0;i<m;i++) {
        Shark s;
        cin>>s.posy>>s.posx>>s.speed>>s.dir>>s.size;
        s.posy = s.posy-1;
        s.posx = s.posx-1;
        s.dir = s.dir-1;
        s.dead = 0;
        sharks.push_back(s);
    }

    for(int i=0;i<c;i++) {
        //상어를 잡는다.
        answer += getShark(i);
        
        //상어가 이동한다.
        moveShark();
        eatShark();
    }
    
    cout<<answer;

    return 0;
}

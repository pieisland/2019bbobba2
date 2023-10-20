
// Online C++ compiler to run C++ program online
#include <iostream>
#include <vector>

using namespace std;

typedef struct {
    int posy;
    int posx;
    int speed;
    int dir;
    int size;
    int dead;
} Shark;

vector<Shark> sharks;

int r, c, m;

int getShark(int col) {
    int ret =0;
    
    int cnt = sharks.size();
    
    for(int i=0;i<c; i++){
        if(sharks[i].posx == col && sharks[i].dead ==0) {
            ret += sharks[i].size;
            sharks[i].dead = 1;
        }
    }
    
    return ret;
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
        if(dir %2 ==0) {
            //좌우 움직임
            int cx = sharks[i].posx;
            for(int k=0;k<speed;k++) {
                if(dir == 0) {
                    int nx = cx +1;
                    if(nx == c) {
                        cx = c-2;
                        dir = 2;
                    } else {
                        cx = nx;
                    }
                }
                else {
                    int nx = cx -1;
                    if(nx == -1) {
                        cx = 1;
                        dir = 0;
                    }
                    else {
                        cx = nx;
                    }
                    
                }
            }
            sharks[i].cx = cx;
            sharks[i].dir = dir;
        }
        else {
            //상하 움직임
            int cy = sharks[i].posy;
            for(int k=0;k<speed;k++) {
                if(dir == 3) {
                    int ny = cy +1;
                    if(nx ==r) {
                        cy = r-2;
                        dir = 1;
                    } else {
                        cy = ny;
                    }
                }
                else {
                    int ny = cy -1;
                    if(nx == -1) {
                        cy = 1;
                        dir = 3;
                    }
                    else {
                        cy = ny;
                    }
                }
            }
            sharks[i].cy = cy;
            sharks[i].dir = dir;
        }
    }
}

void eatShark() {
    //동일한 위치에 있다면 더 몸집이 큰 상어가 잡아먹어야 한다.
    //동일한 위치에 있음을 파악하는 방법?
}

int main() {
    int answer =0;
    
    cin>>r>>c>>m;
    
    for(int i=0;i<m;i++) {
        Shart s;
        cin>>s.posy>>s.posx>>s.speed>>s.dir>>s.size;
        s.posy = s.posy-1;
        s.posx = s.posx-1;
        s.dead = 0;
        sharks.push_back(s);
    }

    for(int i=0;i<c;i++) {
        //상어를 잡는다.
        answer += getShark();
        
        //상어가 이동한다.
        moveShark();
    }

    return 0;
}

/*
정답 아님. 근데 일단 올려놓음...
*/

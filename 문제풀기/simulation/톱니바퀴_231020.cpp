#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

int arr[4][8];

/*
틀릴 게 없는데 런타임에러낫다고 해서 가 열받았는데
반환형이 int인데 아무것도 반환 안 했다고 런타임에러 남.
개열받음.
*/

void rotate(int idx, int rot) {
    if(rot ==1) {
        //시계방향
        int tmp = arr[idx][7];
        for(int i=6;i>=0;i--) {
            arr[idx][i+1] = arr[idx][i];
        }
        arr[idx][0] = tmp;
    }
    else if(rot ==-1) {
        //반시계방향
        int tmp = arr[idx][0];
        for(int i=1;i<8;i++) {
            arr[idx][i-1] = arr[idx][i];
        }
        arr[idx][7] = tmp;
    }
}

void sol3(int k, int rot) {
    int kidx = k-1;
    
    vector<pair<int,int>> vec;
    vec.push_back({kidx, rot});
    
    //다른 애들도 돌아야 하는지 찾아야 함..
    //오른쪽에서 돌아야 하는 애가 있는지.
    int myrot = rot;
    for(int i = kidx; i<3;i++) {
        int right = arr[i][2];
        
        if(right != arr[i+1][6])//다르면 회전해야 함..
        { 
            myrot = -myrot;
            vec.push_back({i+1, myrot});
            //회전 필요한 리스트에 넣어줌.
            //어느 방향으로 회전하는지도 넣어줘야지...
        }
        else break;
    }
    
    myrot = rot;
    for(int i=kidx; i>0; i--) {
        int left = arr[i][6];
        
        if(left != arr[i-1][2]) {
            myrot = -myrot;
            vec.push_back({i-1, myrot});
        }
        else break;
    }
    
    for(int i=0;i<vec.size();i++) {
        rotate(vec[i].first, vec[i].second);
    }
    
    /*for(int i=0;i<4;i++) {
        if(arr[i][0]==1)
            answer += pow(2, i);    
    }*/
}

int main() {
    for (int i = 0; i < 4; i++)
		for (int j = 0; j < 8; j++)
			scanf("%1d", &arr[i][j]);

	int t, idx, rot;
	cin >> t;
	while (t--)
	{
		cin >> idx >> rot;
		sol3(idx, rot);
	}

    int answer =0; 
    for(int i=0;i<4;i++) {
        if(arr[i][0]==1)
            answer += pow(2, i);    
    }

    /*for(int i=0;i<4;i++) {
        cout<<"arr i : ";
        for(int j=0;j<8;j++) {
            cout<<arr[i][j];
        }
        cout<<endl;
    }*/

    //cout <<"answer is ... "<<answer;
    cout<<answer;
    
    return 0;
}

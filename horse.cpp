#include<iostream>
#include<vector>
#include<algorithm>
#include<memory.h>

#define MAXIMUM_STEP 64

int nextPositionX[] = { 1,2,2,1,-1,-2,-2,-1 };
int nextPositionY[] = { 2,1,-1,-2,-2,-1,1,2 };

bool visited[8][8];
int way[MAXIMUM_STEP];

typedef struct _position{
	int x;
	int y;
	int totalWayToNext;
}Position;

bool cmp(Position a,Position b){
	return a.totalWayToNext < b.totalWayToNext;
}

bool isValid(Position p){
	if(p.x < 0 || p.y < 0 || p.x > 7 || p.y > 7 || visited[p.x][p.y]) return false;
	return true;
}

bool dfs(Position p, int step){
	visited[p.x][p.y] = true;
	way[step] = p.y * 8 + p.x + 1;
	if(step == 63){
		for(int i = 0; i < MAXIMUM_STEP - 1; i++)
			std::cout << way[i] << " ";
		std::cout << way[MAXIMUM_STEP - 1] << std::endl;
        return true;
    } else{
		std::vector<Position> possibleWay;
		for(int i = 0; i < 8; i++){
			Position possibleNext;
			possibleNext.x = p.x + nextPositionX[i];
				possibleNext.y = p.y + nextPositionY[i];
			possibleNext.totalWayToNext = 0;
			if(isValid(possibleNext)){
				for(int j = 0; j < 8; j++){
					Position NextPositionToPossibleNext;
					NextPositionToPossibleNext.x = possibleNext.x + nextPositionX[j];
					NextPositionToPossibleNext.y = possibleNext.y + nextPositionY[j];
					if(isValid(NextPositionToPossibleNext)) possibleNext.totalWayToNext++;
				}
				possibleWay.push_back(possibleNext);
			}
		}
		std::sort(possibleWay.begin(),possibleWay.end(),cmp);
		
		for(int i = 0; i < possibleWay.size(); i++) {
			visited[possibleWay[i].x][possibleWay[i].y] = true;
			if(dfs(possibleWay[i],step + 1)) return true;
			visited[possibleWay[i].x][possibleWay[i].y] = false;
		}
		return false;
	}
}

int main(){
	int n;
	while(std::cin >> n && n != -1) {
		Position p;
		p.y = (n - 1) / 8;
		p.x = ((n - 1) - (p.y * 8)) % 8;
		p.totalWayToNext = 0;
		memset(visited,false,sizeof(visited));
		memset(way,-1,sizeof(way));

		dfs(p,0);
	}
	return 0;
}
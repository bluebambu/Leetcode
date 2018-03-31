class Robot {
public:
	bool move(){ return true; }  //dummy
	bool isExit(){ return true; }// dummy
	void turn90(){};  // dummy

	typedef pair<int, int> PII; 
	map<PII, int> visited;

	// dir: up,right,down,left, 0, 1, 2, 3
	void broomAll(){
		visited[{0, 0}] = 1; 
		for (int dir = 0; dir < 4; ++dir){
			dfs(0, 0, dir, visited); 
		}
	}

	void dfs(int i, int j, int dir, map<PII, int>& visited){
		int x, y; 
		if (dir % 2){
			x = i; 
			y = j + (dir == 1 ? 1 : -1); 
		}
		else{
			x = i + (dir == 2 ? 1 : -1); 
			y = j; 
		}
		if (visited[{x, y}])
			return; 
		if (!move())
			return; 
		if (abs(x) > 3 || abs(y) > 3)
			return; 

		cout << x << " " << y << endl; 
    
		visited[{x,y}] = 1;
		for (int k = 0; k < 2; ++k) // turn 180
			turn90(); 
		dir = (dir + 2) % 4; // turn 180

		for (int k = 0; k < 3; ++k){ // left, straight, right
			turn90(); 
			dir = (dir + 1) % 4; 
			dfs(x, y, dir, visited); 
		}
		turn90();  // backtrack
		visited[{x, y}] = 2;
		move(); 
	}
};



int main(){
	Robot a; 
	a.broomAll(); 
}

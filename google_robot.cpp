////////////////////////////////////////////////////////////////
// 给一个扫地机器人，还有三个function：
// move(), which returns boolean value
// turn_left(k), which make robot turns left k times.
// turn_right(k), which make robot turns right k times.
// Design an algorithm to make robot clean up all room.Timecomplexity, linear in term of room space.


typedef pair<int, int> PII; 

class Matrix{
	int n; 
	int m; 
	vector<vector<int>>& core; 
	int r_init_x, r_init_y; 

public:
	Matrix(vector<vector<int>>& x) :n(x.size()), m(x[0].size()), core(x),r_init_x(0), r_init_y(0) {}

	void setRobotInit(int i, int j){
		r_init_x = i; 
		r_init_y = j;
	}

	bool can(int i, int j){
		int x = i + r_init_x, y = j + r_init_y; 
		return x >= 0 && y >= 0 && x < n && y < m && core[x][y] != 1; 
	}

	void clean(int i, int j){
		int x = i + r_init_x, y = j + r_init_y; 
		core[x][y] = 2; 
		cout << "["<<x << " " << y <<"]"<< endl; 

		prt2Layer(core); 
	}

	void backtrack(int i, int j){
		int x = i + r_init_x, y = j + r_init_y; 
		core[x][y] = 3; 
		prt2Layer(core); 
	}
};

class Robot {
public:
	int i, j; 
	int direction; // dir: up,right,down,left, 0, 1, 2, 3
	Matrix& mtx; 
	map<PII, int> visited;

	explicit Robot(Matrix& y) :i(0), j(0), direction(1), mtx(y) {}

	PII alongDirection1StepPos(){
		int x, y; 
		if (direction % 2){
			x = i; 
			y = j + (direction == 1 ? 1 : -1); 
		}
		else{
			x = i + (direction == 2 ? 1 : -1); 
			y = j; 
		}
		return{ x, y };
	}

	bool move(){ 
		PII nextPos = alongDirection1StepPos(); 
		int x = nextPos.first, y = nextPos.second; 
		if (!mtx.can(x,y))
			return false; 

		i = x; 
		j = y;
		return true; 
	}

	void clean(){
		mtx.clean(i, j); 
	}

	void turn90(){
		direction = (direction + 1) % 4;
	}; 

	// dir: up,right,down,left, 0, 1, 2, 3
	void broomAll(){
		dfs(visited); 
	}

	void dfs(map<PII, int>& visited){
		visited[{i,j}] = 1;
		clean(); 

		for (int k = 0; k < 2; ++k) // turn 180 first, to get the dir order below
			turn90(); 

		for (int k = 0; k < 4; ++k){ // left, straight, right, backward
			turn90(); 
			int x, y;
			x = alongDirection1StepPos().first, y = alongDirection1StepPos().second;

			if (visited[{x, y}]) 
				continue;
			if (!move())
				continue;

			dfs(visited); 
		}
		move(); // backtrack
		turn90(); turn90(); // recover direction
	}
};



int main(){
	vector < vector<int>> a = {
		{ 0, 1, 1, 0, 1, 0 },
		{ 1, 1, 1, 0, 1, 0 },
		{ 0, 0, 0, 0, 1, 0 },
		{ 0, 0, 1, 0, 0, 0 },
		{ 0, 1, 1, 0, 1, 0 },
		{ 0, 0, 1, 0, 1, 0 },
	}; // 6x6

	Matrix b(a); 

	Robot c(b); 

	b.setRobotInit(2, 2); 

	c.broomAll();
}



// OUTPUT: 
//0 1 1 2 1 2
//1 1 1 2 1 2
//2 2 2 2 1 2
//2 2 1 2 2 2
//2 1 1 2 1 2
//2 2 1 2 1 2


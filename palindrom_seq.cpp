
class PalinSeq{
public:
	vector<string> solve(string s){
		vector<string> res;
		if (s.empty())
			return res;

		int n = s.size();
		struct unit{
			int len;
			string str;
			unit(int x, string y) :len(x), str(y) {}
		};
		vector<vector<unit>> dp(n);
		dp[0].push_back(unit(1, string() + s[0]));
		for (auto x : dp[0]){
			res.push_back(x.str);
		}

		for (int i = 1; i < n; ++i){
			if (dp[i - 1].size()){
				vector<unit>& pre = dp[i - 1];
				for (unit& u : pre){
					int len = u.len;
					string ss = u.str;
					string potential = string() + s[i] + ss + s[i];
					if (i - len - 1 >= 0 && s[i - len - 1] == s[i]){
						dp[i].push_back(unit(len + 2, potential));
					}
					if (i - len - 2 >= 0 && s[i - len - 2] == s[i]){
						dp[i].push_back(unit(len + 3, potential));
					}
				}
			}
			if (i - 2 >= 0 && dp[i - 2].size()){
				vector<unit>& ppre = dp[i - 2];
				for (unit& u : ppre){
					int len = u.len;
					string ss = u.str;
					string potential = string() + s[i] + ss + s[i];
					if (i - len - 2 >= 0 && s[i - len - 2] == s[i]){
						dp[i].push_back(unit(len + 3, potential));
					}
					if (i - len - 3 >= 0 && s[i - len - 3] == s[i]){
						dp[i].push_back(unit(len + 4, potential));
					}
				}
			}

			dp[i].push_back(unit(1, string() + s[i]));

			for (auto x : dp[i]){
				res.push_back(x.str);
			}
		}

		return res;
	}
};



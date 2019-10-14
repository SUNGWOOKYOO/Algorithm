class Solution {
public:
    
    // O(n) top down 
    int lookup(vector<int>& profits, vector<int>& dp, int i){
        if i == 1:
            dp[1] = max(profits[1], profits[0])
        elif i == 0:
            dp[0] = profits[]
    }
    
    int deleteAndEarn(vector<int>& nums) {
        const int n = 10001;
        
        vector<int> profits = vector<int>(n,0);
        
        for(auto n : nums)
            profits[n]+=n;

        vector<int> dp = vector<int>(n,0);
        dp[1] = profits[1];
        for(int i= 2 ; i< n ;++i){
            dp[i] = max(dp[i-1],profits[i] + dp[i-2]);
        }
        return dp[n-1];
    }
    
    // O(n) bottom up 
    int deleteAndEarn_BU(vector<int>& nums) {
        const int n = 10001;
        
        vector<int> profits = vector<int>(n,0);
        
        for(auto n : nums)
            profits[n]+=n;
        
        vector<int> dp = vector<int>(n,0);
        dp[1] = profits[1];
        for(int i= 2 ; i< n ;++i){
            dp[i] = max(dp[i-1],profits[i] + dp[i-2]);
        }
        return dp[n-1];   
    }
};
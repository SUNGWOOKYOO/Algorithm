#include<iostream>
#include<queue>
#include<limits>
using namespace std;
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
	vector<int> largestValues(TreeNode* root) {

		vector<int> result;
		if (root == NULL)
			return result;

		queue<TreeNode*> q;
		int max, tmp;
		int MinInf = numeric_limits<int>::min();

		q.push(root);
		//cout << "debug:"<<endl;
		while (!q.empty()) {
			max = MinInf;
			// for each level...
			queue<TreeNode*> localq;
			while (!q.empty()) {
				auto cur = q.front(); q.pop();
				if (cur != NULL) {
					//cout << "debug:"<<cur->val <<endl;
					tmp = cur->val;
					if (cur->left)
						localq.push(cur->left);
					if (cur->right)
						localq.push(cur->right);
					if (max < tmp) {
						max = tmp;
					}
				}
			}
			result.push_back(max);
			q = localq;
		}

		for (auto e : result) {
			cout << e << " ";
		}cout << endl;

		return result;
	}
};

int main() {
	TreeNode* root = new TreeNode(1);
	TreeNode* cur;
	root->left = new TreeNode(3);
	root->right = new TreeNode(2);
	cur = root->left;
	cur->left = new TreeNode(5);
	cur->right = new TreeNode(3);
	cur = root->right;
	cur->right = new TreeNode(9);

	Solution sol;
	sol.largestValues(root);

	return 0;
}
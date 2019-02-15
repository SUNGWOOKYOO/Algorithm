#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <stack>
using namespace std;

class TreeNode {
public:
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
	vector<vector<int>> levelOrder(TreeNode* root) {
		queue<TreeNode*> q;
		q.push(root);
		vector<vector<int>> result;
		int Lv = 0;
		while (!q.empty()) {
			queue<TreeNode*> localq;
			result.push_back(vector<int>()); //level++;

			while (!q.empty()) {
				TreeNode* cur = q.front(); q.pop();
				//cout << cur->val << " ";
				result[Lv].push_back(cur->val);

				if (cur->left != NULL)
					localq.push(cur->left);
				if (cur->right != NULL)
					localq.push(cur->right);
			}
			q = localq; //copy each Level;
			++Lv;
			//cout << "level " << Lv << endl;
		}


		for (auto vec : result) {
			for (auto e : vec) {
				cout << e << " ";
			}cout << endl;
		}
		cout << endl;

		return result;
	}

	// preorder approach
	void buildVector(vector<vector<int>>& ret, TreeNode *root, int depth)
	{
		if (root == NULL) return;
		if (ret.size() == depth)
			ret.push_back(vector<int>());

		ret[depth].push_back(root->val);
		buildVector(ret, root->left, depth + 1);
		buildVector(ret, root->right, depth + 1);
	}

	vector<vector<int> > levelOrder2(TreeNode *root) {
		vector<vector<int>> result;
		buildVector(result, root, 0);

		for (auto vec : result) {
			for (auto e : vec) {
				cout << e << " ";
			}cout << endl;
		}
		cout << endl;

		return result;
	}
};
int main() {
	Solution sol;
	TreeNode* root = new TreeNode(3);
	TreeNode* cur;
	root->left = new TreeNode(9);
	root->right = new TreeNode(20);
	cur = root->right;
	cur->left = new TreeNode(15);
	cur->right = new TreeNode(7);

	// BFS approach
	sol.levelOrder(root);

	// preorder approach
	sol.levelOrder2(root);

	return 0;
}
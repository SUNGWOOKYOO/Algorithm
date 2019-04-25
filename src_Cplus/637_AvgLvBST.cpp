#include<iostream>
#include<vector>
#include<queue>
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

	vector<double> averageOfLevels(TreeNode* root) {
		vector<double> result;
		queue<TreeNode*> Q;
		Q.push(root);

		while (!Q.empty()) {
			queue<TreeNode*> tmp;
			int count = 0;
			double local = 0;
			// each Lv
			while (!Q.empty()) {
				TreeNode* u = Q.front(); Q.pop();
				//cout << u->val << " ";
				local = local + u->val;
				count++;
				if (u->left != NULL) {
					tmp.push(u->left);
				}
				if (u->right != NULL) {
					tmp.push(u->right);
				}
			}
			Q = tmp;
			result.push_back(local / (double)count);
		}
		return result;
	}

	// preorder approach
	void buildVector(TreeNode *root, int depth)
	{
		if (root == NULL) return;
		if (ret.size() == depth)
			ret.push_back(vector<int>());

		ret[depth].push_back(root->val);
		buildVector(root->left, depth + 1);
		buildVector(root->right, depth + 1);
	}

	vector<vector<int> > levelOrder(TreeNode *root) {
		buildVector(root, 0);
		return ret;
	}
};

int main(){

	TreeNode *root = new TreeNode(3);
	root->left = new TreeNode(9);
	root->right = new TreeNode(20);
	root->right->left = new TreeNode(15);
	root->right->right = new TreeNode(7);

	Solution sol;
	vector<double> result = sol.averageOfLevels(root);
	for (auto it = result.begin(); it != result.end(); ++it) {
		cout << *it << " ";
	}cout << endl;

	return 0;
}
#include <iostream>
#include <cstdlib>

#include "BST.h"

using namespace std;

int main()
{
	BST<int> * tree = new BST<int>();

	int randoms[10];

	for (int i = 0; i < 10; i++)
	{
		randoms[i] = int(rand() % 100);
		cout << "Insertion : " << randoms[i] << endl;
		tree->insertion(randoms[i]);
	}
	cout << endl;

	tree->print_inorder();

	tree->deletion(1);
 	tree->print_inorder();

	for (int i = 0; i < 10; i += 3)
	{
		tree->deletion(randoms[i]);
		tree->print_inorder();
	}
  delete tree;
	return 0;

}

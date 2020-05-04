#ifndef _SEGMENTTREE_H_

#define _SEGMENTTREE_H_

#include<iostream>
using namespace std;

class TreeNode
{
public:
	int left;
	int right;
	int covers;
	TreeNode* lChild;
	TreeNode* rChild;
};


class SegmentTree
{
public:
	TreeNode* CreateTree(int left, int right);
private:
	TreeNode* boot;
}





#endif //ssssssssssssssssssssssssssssssssssssss
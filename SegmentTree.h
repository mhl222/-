#pragma once
#include<iostream>
#include<queue>
#include<string>
using namespace std;

class TreeNode
{
public:
	int left;
	int right;
	int covers;
	int unionLenght;
	int height;
	TreeNode* lChild;
	TreeNode* rChild;

};

class SegmentTree
{
public:
	SegmentTree(int left, int right);
	static TreeNode* CreateTree(int left, int right);
	void insertSegment(int left, int right);
	void insertRectangle(int left,int right ,int nodeHeight);
	void deleteSegment(int left, int right);
	int getUnionLength() { return boot->unionLenght; };
	int getRectangleArea() { return boot->height; };
	void print();
	void aprintf();

private:
	TreeNode* boot;
	void insertSegment(int left, int right, TreeNode* tree);
	void insertRectangle(int left, int right, int nodeHeight, TreeNode* tree);
	void deleteSegment(int left, int right, TreeNode* tree);
	void print(TreeNode* tree);
	void aprintf(TreeNode* parent, TreeNode* root, string prefix);
	void updataUnionLength(TreeNode* tree);
	void updataHeight(TreeNode* tree);

};

 SegmentTree::SegmentTree(int left, int right)
{
	 if (right - left < 1)
	 {
		 cout << "参数区间不正确。";
		 this->boot = NULL;
		 return ;
	 }
	 this->boot = CreateTree(left, right);
}
TreeNode* SegmentTree::CreateTree(int left, int right) {
	if (right - left < 1)
	{
		return NULL;
	}
	TreeNode* node = new TreeNode();
	node->left = left;
	node->right = right;
	node->covers = 0;
	node->height=0;
	node->unionLenght = 0;
	node->lChild = NULL;
	node->rChild = NULL;
	if (right - left == 1)
		return node;
	int mid = (left + right) / 2;
	node->lChild=CreateTree(left, mid);
	node->rChild=CreateTree(mid, right);
	return node;
}
void SegmentTree::insertRectangle(int left, int right,int nodeHeight)
{
	insertRectangle(left, right,nodeHeight, boot);
	updataHeight(boot);
}
void SegmentTree::insertSegment(int left, int right)
{
	 insertSegment(left, right,boot);
	 updataUnionLength(boot);

}
void SegmentTree::deleteSegment(int left, int right)
 {
	deleteSegment(left, right, boot);
	updataUnionLength(boot);
 }
void SegmentTree::print()
{
	print(boot);
}
void SegmentTree::aprintf()
{
	string str="";
	aprintf(boot,boot,str);
}

void SegmentTree::insertSegment(int left, int right, TreeNode* tree)
{
	if (left <tree->left || right > tree->right)
	{
		cout << "区间出界！";
		return;
	}
	
	if (left == tree->left && right == tree->right&& tree->right-tree->left==1)
	{
		tree->covers++;
		tree->unionLenght = 1;
		return;
	}
	int mid = tree->lChild->right;
	if (right <= mid)
	{
		insertSegment(left, right, tree->lChild);
	}
	else if (left >= mid) {
		insertSegment(left, right, tree->rChild);

	}
	else
	{
		insertSegment(left, mid, tree->lChild);
		insertSegment(mid, right, tree->rChild);

	}
}
void SegmentTree::insertRectangle(int left, int right, int nodeHeight, TreeNode* tree)
{
	if (left <tree->left || right > tree->right)
	{
		cout << "区间出界！";
		return;
	}

	if (left == tree->left && right == tree->right && tree->right - tree->left == 1)
	{
		if (tree->height < nodeHeight)
			tree->height = nodeHeight;
		return;
	}
	int mid = tree->lChild->right;
	if (right <= mid)
	{
		insertRectangle(left, right, nodeHeight, tree->lChild);
	}
	else if (left >= mid) {
		insertRectangle(left, right, nodeHeight, tree->rChild);

	}
	else
	{
		insertRectangle(left, mid, nodeHeight, tree->lChild);
		insertRectangle(mid, right, nodeHeight, tree->rChild);

	}
}
void SegmentTree::deleteSegment(int left, int right, TreeNode* tree)
{
	if (left <tree->left || right > tree->right)
	{
		cout << "区间出界！";
		return;
	}
	
	if (left == tree->left && right == tree->right && tree->right - tree->left == 1)
	{
		tree->covers--;
		tree->unionLenght = 0;
		return;
	}
	int mid = tree->lChild->right;
	if (right <= mid)
	{
		deleteSegment(left,right, tree->lChild);
	}
	else if (left >= mid) {
		deleteSegment(left, right, tree->rChild);

	}
	else
	{
		deleteSegment(left, mid, tree->lChild);
		deleteSegment(mid, right, tree->rChild);

	}
}
void SegmentTree::print(TreeNode* tree)
{
	queue<TreeNode*>  nodeQueue;
	if (tree != NULL)
		nodeQueue.push(tree);
	TreeNode* node;
	TreeNode* lastNode = tree;
	TreeNode* movingLastNode = NULL;

	while (!nodeQueue.empty())
	{
		node = nodeQueue.front();
		nodeQueue.pop();
		cout << "(" << node->left << "," << node->right<<"U："<<node->unionLenght << "C：" << node->covers << "A：" << node->height << ")";
		if (node->lChild)
		{
			nodeQueue.push(node->lChild);
			movingLastNode = node->lChild;
		}
		if (node->rChild)
		{
			nodeQueue.push(node->rChild);
			movingLastNode = node->rChild;
		}
		if (node == lastNode)
		{
			cout << endl;
			lastNode = movingLastNode;
		}
	}

}
void SegmentTree::aprintf(TreeNode* parent, TreeNode* root, string prefix)
{
	prefix += "|";
	if (root) {
		cout << prefix << endl;
		cout << prefix << "--" <<  "(" << root->left << "," <<root->right << ")"<<endl;
		if (root == parent || root == parent->rChild) {
			prefix.pop_back(); prefix += " ";
		}
		prefix += "  ";
		aprintf(root, root->lChild,prefix);
		aprintf(root, root->rChild, prefix);
	}
	else {
		if (parent->lChild || parent->rChild) //有一个孩子节点不空就打印，以区分左右孩子
			cout << prefix << "--" << "{}" << endl;
	}

}
void SegmentTree::updataUnionLength(TreeNode* tree)
{
	if(tree)
	{
		updataUnionLength(tree->lChild);
		updataUnionLength(tree->rChild);
		if (tree->lChild && tree->rChild)
		{
			tree->unionLenght = tree->lChild->unionLenght + tree->rChild->unionLenght;
		}
	}
}
void SegmentTree::updataHeight(TreeNode* tree)
{
	if (tree)
	{
		updataHeight(tree->lChild);
		updataHeight(tree->rChild);
		if (tree->lChild && tree->rChild)
		{
			tree->height = tree->lChild->height + tree->rChild->height;
		}
	}
}
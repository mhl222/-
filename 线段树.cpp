#include"SegmentTree.h"

int main()
{
	SegmentTree tree(2,12);
	tree.insertRectangle(3, 6, 4);
	tree.insertRectangle(5, 7, 6);
	tree.aprintf();
	return 0;
}


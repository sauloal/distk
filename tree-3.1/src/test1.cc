
#include <iostream>
#include "tree.hh"
#include "tree_util.hh"

int main(int, char **)
	{
	tree<int> tr;

#ifndef __TREE_SIMPLE__
	tr.insert(tr.begin(), 1);
	tree<int>::iterator i2 = tr.insert(tr.end(), 2);
	tree<int>::iterator i3 = tr.insert(tr.end(), 3);
	tr.append_child(i2, 21);
	tr.append_child(i3, 31);
	tree<int>::iterator i4 = tr.insert(tr.end(), 4);

	kptree::print_tree_bracketed(tr, std::cout);
#else //__TREE_SIMPLE__
	tr.append_child(tr.begin(), 1);
	tree<int>::iterator i2 = tr.append_child(tr.end(), 2);
	tree<int>::iterator i3 = tr.append_child(tr.end(), 3);
	tr.append_child(i2, 21);
	tr.append_child(i3, 31);
	tree<int>::iterator i4 = tr.append_child(tr.end(), 4);

	kptree::print_tree_bracketed(tr, std::cout);
#endif //__TREE_SIMPLE__
	std::cout << std::endl;
	}

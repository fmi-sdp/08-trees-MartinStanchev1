#include <iostream>
#include "BinaryTree.hpp"
#include "GeneralTree.hpp"

int main()
{
	BinaryTree<int> bt1(1);
	BinaryTree<int> bt2(3);
	BinaryTree<int> bt3(2, bt1, bt2);
	BinaryTree<int> bt4(6);
	BinaryTree<int> bt5(8);
	BinaryTree<int> bt6(7, bt4, bt5);
	BinaryTree<int> bt7(4, bt3);
	BinaryTree<int> bt8(5, bt7, bt6);

	//1 zad
	bt8.printInOrder();
	bt8.printPreOrder();
	bt8.printPostOrder();
	//2 zad
	BinaryTree<int> bt9 = bt8;
	bt9.trim();
	bt9.printInOrder();
	//3 zad
	BinaryTree<int> bt10 = bt8;
	bt10.bloom();
	bt10.printPostOrder();
	//4 zad
	GeneralTree<int> gt1(1);
	GeneralTree<int> gt2(2);
	GeneralTree<int> gt3(3, gt1, gt2);
	GeneralTree<int> gt4(4);
	GeneralTree<int> gt5(5);
	GeneralTree<int> gt6(6, gt4, gt5);
	GeneralTree<int> gt7(7, gt3);
	GeneralTree<int> gt8(8, gt7, gt6);
	GeneralTree<int> gt9(9, gt8);
	gt9.print();
	using GeneralTree = typename GeneralTree<int>;

	GeneralTree gt(0, GeneralTree(1, GeneralTree(),
		GeneralTree(2, GeneralTree(), GeneralTree(3, GeneralTree(4,
			GeneralTree(), GeneralTree(5, GeneralTree(), GeneralTree(6)))))));

	std::cout << gt9.branchingCoefficient() << std::endl;
	std::cout << gt.branchingCoefficient() << std::endl;
	//5 zad
	gt9.printLevel(0);
	gt9.printLevel(1);
	gt9.printLevel(2);
	gt9.printLevel(3);
	gt9.printLevel(4);
	gt9.printLevel(5);

	//6 zad
	std::cout << gt9.leafCount() << std::endl;
	std::cout << gt.leafCount() << std::endl;
	return 0;
}
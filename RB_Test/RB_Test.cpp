#pragma once

#include "pch.h"
#include "CppUnitTest.h"
#include <string>
#include "..//RB/RB.cpp"
//#include "..//RB/NormalList.h"



using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RBTest
{
	TEST_CLASS(RBTest)
	{
	private:
		Map<int, string> tree;
		List<int>* myList = new List<int>;
		List<string>* myList1 = new List<string>;
		List<NodeOfTree*> list;

	public:

		TEST_METHOD_INITIALIZE(init)
		{
			
			NodeOfTree* a = new NodeOfTree;
			a->c = 'a';
			a->a = 19;
			NodeOfTree* b = new NodeOfTree;
			b->c = 'b';
			b->a = 7;
			NodeOfTree* c = new NodeOfTree;
			c->c = 'c';
			c->a = 24;
			list.push_back(c);
			list.push_back(b);
			list.push_back(a);
			tree.insert(30, "a");
			tree.insert(40, "a");
			tree.insert(15, "daada");
			tree.insert(10, "daada");
			tree.insert(20, "daada");
			tree.insert(5, "daada");
			tree.insert(3, "daada");

		}
		TEST_METHOD(test_insert)
		{
			tree.insert(2, "oleg");
			tree.insert(21, "ne sdast labu");
			Assert::AreEqual(tree.getRoot()->left->left->left->key, 2);
			Assert::AreEqual(tree.getRoot()->right->left->right->key, 21);
		}
		TEST_METHOD(test_remove1)
		{
			tree.remove(15);
			Assert::AreEqual(tree.getRoot()->left->key, 5);
		}
		TEST_METHOD(test_remove2)
		{
			tree.remove(20);
			Assert::AreEqual(tree.getRoot()->left->key, 5);
		}
		TEST_METHOD(find)
		{
			Assert::AreEqual(tree.find(40)->data, (string)"a");

		}
		TEST_METHOD(test_print_to_console)
		{
			tree.print(tree.getRoot(), 0);
		}
		TEST_METHOD(test_getListKey)
		{
			
			myList = tree.getListKey(tree.getRoot(), myList);
			Assert::AreEqual(myList->at(0), 3);
			Assert::AreEqual(myList->at(1), 10);
		}
		TEST_METHOD(test_getListData)
		{
			List<string>* myList1 = new List<string>;
			myList1 = tree.getListData(tree.getRoot(), myList1);
			Assert::AreEqual(myList1->at(0), (string)"daada");
			Assert::AreEqual(myList1->at(1), (string)"daada");
		}
		TEST_METHOD(sort_List)
		{
			
			sortList(list);
			Assert::AreEqual(list.get_pointer(0)->data->c, 'b');
			Assert::AreEqual(list.get_pointer(1)->data->c, 'a');
			Assert::AreEqual(list.get_pointer(2)->data->c, 'c');
		}
		TEST_METHOD(test_BuildTree)
		{
			
			BuildTree(list);
			Assert::AreEqual(list.head->data->left->c, 'c');
			Assert::AreEqual(list.head->data->right->left->c, 'b');
			Assert::AreEqual(list.head->data->right->right->c, 'a');

		}
		TEST_METHOD(test_BuildTable)
		{
			
			BuildTree(list);
			NodeOfTree* root = list.head->data;
			List<bool> listCode;
			Map<char, bool*> table;
			table.insert('a', nullptr);
			table.insert('b', nullptr);
			table.insert('c', nullptr);
			BuildTable(root, table, listCode);
			Assert::AreEqual(table.find('c')->data[0], false);
			Assert::AreEqual(table.find('b')->data[0], true);
			Assert::AreEqual(table.find('b')->data[1], false);
			Assert::AreEqual(table.find('a')->data[0], true);
			Assert::AreEqual(table.find('a')->data[1], true);


		}
	};
}

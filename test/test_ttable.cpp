#include "uttable.h"
#include "utavltree.h"

#include <gtest.h>


TEST(UnorderedTable, new_unordered_table_empty) {
	UnorderedTable<int> ut;
	ASSERT_EQ(ut.getSize(), 0);
}

TEST(UnorderedTable, can_add_elements) {
	UnorderedTable<int> ut;
	ut.insert(1, 12);
	ut.insert(2, 24);
	ASSERT_EQ(ut.getSize(), 2);
}

TEST(UnorderedTable, keys_unique) {
	UnorderedTable<int> ut;
	ut.insert(1, 12);
	ASSERT_ANY_THROW(ut.insert(1, 24));
}

TEST(UnorderedTable, can_find_elements) {
	UnorderedTable<int> ut;
	ut.insert(1, 12);
	ASSERT_EQ(ut.find(1)->second, 12);
}

TEST(UnorderedTable, can_erase_elements) {
	UnorderedTable<int> ut;
	ut.insert(1, 12);
	ut.insert(2, 24);
	ut.erase(1);
	ASSERT_EQ(ut.find(2)->second, 24);
}

TEST(UnorderedTable, can_clear) {
	UnorderedTable<int> ut;
	ut.insert(1, 12);
	ut.insert(2, 24);
	ut.clear();
	ASSERT_EQ(ut.getSize(), 0);
}

TEST(OrderedTable, new_ordered_table_empty) {
	OrderedTable<int> ot;
	ASSERT_EQ(ot.getSize(), 0);
}

TEST(OrderedTable, can_add_elements) {
	OrderedTable<int> ot;
	ot.insert(1, 12);
	ot.insert(2, 24);
	ASSERT_EQ(ot.getSize(), 2);
}

TEST(OrderedTable, keys_unique) {
	OrderedTable<int> ot;
	ot.insert(1, 12);
	ASSERT_ANY_THROW(ot.insert(1, 24));
}

TEST(OrderedTable, can_find_elements) {
	OrderedTable<int> ot;
	ot.insert(1, 12);
	ASSERT_EQ(ot.find(1)->second, 12);
}


TEST(OrderedTable, can_find_elements_near_middle) {
	OrderedTable<int> ot;
	ot.insert(1, 12);
	ot.insert(2, 24);
	ot.insert(4, 35);
	ot.insert(5, 3424);
	ot.insert(3, 40);
	ASSERT_EQ(ot.find(4)->second, 35);
}

TEST(OrderedTable, can_find_first_element) {
	OrderedTable<int> ot;
	ot.insert(1, 12);
	ot.insert(2, 24);
	ot.insert(4, 35);
	ot.insert(5, 3424);
	ot.insert(3, 40);
	ASSERT_EQ(ot.find(1)->second, 12);
}

TEST(OrderedTable, can_find_last_element) {
	OrderedTable<int> ot;
	ot.insert(1, 12);
	ot.insert(2, 24);
	ot.insert(4, 35);
	ot.insert(5, 3424);
	ot.insert(3, 40);
	ASSERT_EQ(ot.find(5)->second, 3424);
}

TEST(OrderedTable, can_erase_elements) {
	OrderedTable<int> ot;
	ot.insert(1, 12);
	ot.insert(2, 24);
	ot.insert(4, 35);
	ot.insert(5, 3424);
	ot.insert(3, 40);
	ot.erase(4);
	ASSERT_EQ(ot.find(5)->second, 3424);
}

TEST(OrderedTable, can_clear) {
	OrderedTable<int> ot;
	ot.insert(1, 12);
	ot.insert(2, 24);
	ot.clear();
	ASSERT_EQ(ot.getSize(), 0);
}

TEST(HashTable, new_hash_table_empty) {
	HashTable ht(5);
	ASSERT_EQ(ht.getSize(), 0);
}

TEST(HashTable, can_add_elements) {
	HashTable ht(5);
	ht.insert(1, 12);
	ht.insert(2, 24);
	ASSERT_EQ(ht.getSize(), 2);
}

TEST(HashTable, can_find_elements) {
	HashTable ht(5);
	ht.insert(1, 12);
	ASSERT_EQ(ht.find(1)->second, 12);
}

TEST(HashTable, can_erase_elements) {
	HashTable ht(5);
	ht.insert(1, 12);
	ht.insert(2, 24);
	ht.erase(1);
	ASSERT_EQ(ht.find(2)->second, 24);
}

TEST(HashTable, open_addressing_works) {
	HashTable ht(5);
	ht.insert(1, 12);
	ht.insert(2, 24);
	ht.insert(3, 36);
	ht.insert(4, 48);
	ht.insert(5, 60);
	ht.erase(5);
	ht.erase(1);
	ht.insert(6, 72);
	ht.erase(3);
	ASSERT_EQ(ht.find(4)->second, 48);
}

TEST(HashTable, can_clear) {
	HashTable ht(5);
	ht.insert(1, 12);
	ht.insert(2, 24);
	ht.clear();
	ASSERT_EQ(ht.getSize(), 0);
}

TEST(DTree, can_create_tree) {
	std::vector<int> v = { 3,4,2,1,5,6 };
	ASSERT_NO_THROW(DTree<int> tree(v, 2));
}

TEST(DTree, can_find_left_child) {
	std::vector<int> v = { 3,4,2,1,5,6 };
	DTree<int> tree(v, 2);
	ASSERT_EQ(tree.storage[tree.leftChild(0)], 4);
}

TEST(DTree, can_find_right_child) {
	std::vector<int> v = { 3,4,2,1,5,6 };
	DTree<int> tree(v, 2);
	ASSERT_EQ(tree.storage[tree.rightChild(0)], 2);
}

TEST(DTree, can_find_right_child_if_less_than_d_children) {
	std::vector<int> v = { 3,4,2,1,5,6 };
	DTree<int> tree(v, 2);
	ASSERT_EQ(tree.storage[tree.rightChild(2)], 6);
}

TEST(DTree, heapsort_works) {
	std::vector<int> v = { 3,4,2,1,5,6 };
	DTree<int> tree(v, 2);
	tree.heapsort();
	std::vector<int> sorted = { 1,2,3,4,5,6 };
	ASSERT_EQ(tree.storage, sorted);
}
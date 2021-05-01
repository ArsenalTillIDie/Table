#include "uttable.h"

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
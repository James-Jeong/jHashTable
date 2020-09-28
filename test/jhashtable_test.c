#include "../include/ttlib.h"
#include "../include/jhashtable.h"

////////////////////////////////////////////////////////////////////////////////
/// Definitions of Test
////////////////////////////////////////////////////////////////////////////////

DECLARE_TEST();

TEST(ControlNode, CreateAndDeleteNode, {
	JNodePtr node = NewJNode();
	EXPECT_NOT_NULL(node);
	EXPECT_NUM_EQUAL(DeleteJNode(&node), DeleteSuccess);

	EXPECT_NUM_EQUAL(DeleteJNode(NULL), DeleteFail);
})

TEST(ControlNode, SetNodeData, {
	JNodePtr node = NewJNode();

	int expected = 5;
	EXPECT_NOT_NULL(JNodeSetData(node, &expected));
	EXPECT_PTR_EQUAL(node->data, &expected);
	EXPECT_NUM_EQUAL(*((int*)(node->data)), expected);

	EXPECT_NULL(JNodeSetData(NULL, &expected));
	EXPECT_NULL(JNodeSetData(node, NULL));

	DeleteJNode(&node);
})

TEST(ControlNode, GetNodeData, {
	JNodePtr node = NewJNode();

	int expected = 5;
	JNodeSetData(node, &expected);
	EXPECT_NOT_NULL(JNodeGetData(node));
	EXPECT_NUM_EQUAL(*((int*)JNodeGetData(node)), expected);

	EXPECT_NULL(JNodeGetData(NULL));

	DeleteJNode(&node);
})

TEST(ControlLinkedList, CreateAndDeleteLinkedList, {
	JLinkedListPtr list = NewJLinkedList(0);
	EXPECT_NOT_NULL(list);
	EXPECT_NUM_EQUAL(DeleteJLinkedList(&list), DeleteSuccess);

	EXPECT_NUM_EQUAL(DeleteJLinkedList(NULL), DeleteFail);
})

TEST(ControlLinkedList, AddNode, {
	JLinkedListPtr list = NewJLinkedList(0);

	int expected = 5;
	EXPECT_NOT_NULL(JLinkedListAddNode(list, &expected));
	EXPECT_NUM_EQUAL(*((int*)(list->tail->prev->data)), expected);

	DeleteJLinkedList(&list);
})

TEST(ControlLinkedList, GetLinkedListFirstNodeData, {
	JLinkedListPtr list = NewJLinkedList(0);

	int expected1 = 5;
	int expected2 = 6;
	int expected3 = 7;

	JLinkedListAddNode(list, &expected1);
	JLinkedListAddNode(list, &expected2);
	JLinkedListAddNode(list, &expected3);

	EXPECT_NUM_EQUAL(*((int*)JLinkedListGetFirstNodeData(list)), expected1);

	EXPECT_NULL(JLinkedListGetFirstNodeData(NULL));

	DeleteJLinkedList(&list);
})

TEST(ControlLinkedList, GetLinkedListLastNodeData, {
	JLinkedListPtr list = NewJLinkedList(0);

	int expected1 = 5;
	int expected2 = 6;
	int expected3 = 7;

	JLinkedListAddNode(list, &expected1);
	JLinkedListAddNode(list, &expected2);
	JLinkedListAddNode(list, &expected3);

	EXPECT_NUM_EQUAL(*((int*)JLinkedListGetLastNodeData(list)), expected3);
	
	EXPECT_NULL(JLinkedListGetFirstNodeData(NULL));

	DeleteJLinkedList(&list);
})

TEST(ControlLinkedList, GetLinkedListSize, {
	JLinkedListPtr list = NewJLinkedList(0);
	int expected1 = 5;
	int expected2 = 6;
	int expected3 = 7;

	JLinkedListAddNode(list, &expected1);
	JLinkedListAddNode(list, &expected2);
	JLinkedListAddNode(list, &expected3);
	EXPECT_NUM_EQUAL(JLinkedListGetSize(list), 3);

	DeleteJLinkedList(&list);
})

TEST(ControlLinkedList, SetLinkedListData, {
	JLinkedListPtr list = NewJLinkedList(0);
	int expected = 5;

	EXPECT_NOT_NULL(JLinkedListSetData(list, &expected));
	EXPECT_NUM_EQUAL(*((int*)JLinkedListGetData(list)), expected);

	DeleteJLinkedList(&list);
})

TEST(ControlLinkedList, GetLinkedListData, {
	JLinkedListPtr list = NewJLinkedList(0);
	int expected = 5;

	JLinkedListSetData(list, &expected);
	EXPECT_NOT_NULL(JLinkedListGetData(list));
	EXPECT_NUM_EQUAL(*((int*)JLinkedListGetData(list)), 5);

	DeleteJLinkedList(&list);
})

TEST(ControlHashTable, CreateAndDeleteHashTable, {
	int size = 10;
	JHashTablePtr table = NewJHashTable(size, IntType);
	EXPECT_NOT_NULL(table);
	EXPECT_NUM_EQUAL(DeleteJHashTable(&table), DeleteSuccess);

	EXPECT_NULL(NewJHashTable(-1, IntType));
	EXPECT_NULL(NewJHashTable(0, IntType));
	EXPECT_NUM_EQUAL(DeleteJHashTable(NULL), DeleteFail);
})

TEST(ControlHashTable, GetHashTableSize, {
	int expected = 10;
	JHashTablePtr table = NewJHashTable(expected, IntType);
	EXPECT_NUM_EQUAL(JHashTableGetSize(table), expected);
	DeleteJHashTable(&table);
})

TEST(ControlHashTable, AddData, {
	int size = 10;
	int expected1 = 5;
	JHashTablePtr table = NewJHashTable(size, IntType);
	EXPECT_NOT_NULL(JHashTableAddData(table, &expected1));
	DeleteJHashTable(&table);
})

TEST(ControlHashTable, GetFirstData, {
	int size = 10;
	int expected1 = 4;
	int expected2 = 5;
	int expected3 = 6;
	int expected4 = 7;
	JHashTablePtr table = NewJHashTable(size, IntType);

	JHashTableAddData(table, &expected1);
	JHashTableAddData(table, &expected2);
	JHashTableAddData(table, &expected3);
	JHashTableAddData(table, &expected4);
	EXPECT_NUM_EQUAL(*((int*)JHashTableGetFirstData(table)), expected1);

	EXPECT_NULL(JHashTableGetFirstData(NULL));

	DeleteJHashTable(&table);
})

TEST(ControlHashTable, GetLastData, {
	int size = 10;
	int expected1 = 4;
	int expected2 = 5;
	int expected3 = 6;
	int expected4 = 7;
	JHashTablePtr table = NewJHashTable(size, IntType);

	JHashTableAddData(table, &expected1);
	JHashTableAddData(table, &expected2);
	JHashTableAddData(table, &expected3);
	JHashTableAddData(table, &expected4);
	EXPECT_NUM_EQUAL(*((int*)JHashTableGetLastData(table)), expected4);

	EXPECT_NULL(JHashTableGetLastData(NULL));

	DeleteJHashTable(&table);
})

////////////////////////////////////////////////////////////////////////////////
/// Main Function
////////////////////////////////////////////////////////////////////////////////

int main()
{
    CREATE_TESTSUIT();

    REGISTER_TESTS(
		Test_ControlNode_CreateAndDeleteNode,
		Test_ControlNode_SetNodeData,
		Test_ControlNode_GetNodeData,
		Test_ControlLinkedList_CreateAndDeleteLinkedList,
		Test_ControlLinkedList_AddNode,
		Test_ControlLinkedList_GetLinkedListFirstNodeData,
		Test_ControlLinkedList_GetLinkedListLastNodeData,
		Test_ControlLinkedList_GetLinkedListSize,
		Test_ControlLinkedList_SetLinkedListData,
		Test_ControlLinkedList_GetLinkedListData,
		Test_ControlHashTable_CreateAndDeleteHashTable,
		Test_ControlHashTable_GetHashTableSize,
		Test_ControlHashTable_AddData,
		Test_ControlHashTable_GetFirstData,
		Test_ControlHashTable_GetLastData
    );

    RUN_ALL_TESTS();

    CLEAN_UP_TESTSUIT();

	return 1;
}


#include "../include/ttlib.h"
#include "../include/jhashtable.h"

////////////////////////////////////////////////////////////////////////////////
/// Definitions of Test
////////////////////////////////////////////////////////////////////////////////

DECLARE_TEST();

////////////////////////////////////////////////////////////////////////////////
/// Node Test
////////////////////////////////////////////////////////////////////////////////

TEST(ControlNode, CreateAndDeleteNode, {
	JNodePtr node = NewJNode();
	EXPECT_NOT_NULL(node);
	EXPECT_NUM_EQUAL(DeleteJNode(&node), DeleteSuccess);

	EXPECT_NUM_EQUAL(DeleteJNode(NULL), DeleteFail);
})

TEST(ControlNode, SetData, {
	JNodePtr node = NewJNode();

	int expected = 5;
	EXPECT_NOT_NULL(JNodeSetData(node, &expected));
	EXPECT_PTR_EQUAL(node->data, &expected);
	EXPECT_NUM_EQUAL(*((int*)(node->data)), expected);

	EXPECT_NULL(JNodeSetData(NULL, &expected));
	EXPECT_NULL(JNodeSetData(node, NULL));
	EXPECT_NULL(JNodeSetData(NULL, NULL));

	DeleteJNode(&node);
})

TEST(ControlNode, GetData, {
	JNodePtr node = NewJNode();

	int expected = 5;
	JNodeSetData(node, &expected);
	EXPECT_NOT_NULL(JNodeGetData(node));
	EXPECT_NUM_EQUAL(*((int*)JNodeGetData(node)), expected);

	EXPECT_NULL(JNodeGetData(NULL));

	DeleteJNode(&node);
})

////////////////////////////////////////////////////////////////////////////////
/// LinkedList Test
////////////////////////////////////////////////////////////////////////////////

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

	EXPECT_NULL(JLinkedListAddNode(NULL, &expected));
	EXPECT_NULL(JLinkedListAddNode(list, NULL));
	EXPECT_NULL(JLinkedListAddNode(NULL, NULL));

	DeleteJLinkedList(&list);
})

TEST(ControlLinkedList, GetLinkedListFirstData, {
	JLinkedListPtr list = NewJLinkedList(0);

	int expected1 = 5;
	int expected2 = 6;
	int expected3 = 7;

	JLinkedListAddNode(list, &expected1);
	JLinkedListAddNode(list, &expected2);
	JLinkedListAddNode(list, &expected3);

	EXPECT_NUM_EQUAL(*((int*)JLinkedListGetFirstData(list)), expected1);

	EXPECT_NULL(JLinkedListGetFirstData(NULL));

	DeleteJLinkedList(&list);
})

TEST(ControlLinkedList, GetLinkedListLastData, {
	JLinkedListPtr list = NewJLinkedList(0);

	int expected1 = 5;
	int expected2 = 6;
	int expected3 = 7;

	JLinkedListAddNode(list, &expected1);
	JLinkedListAddNode(list, &expected2);
	JLinkedListAddNode(list, &expected3);

	EXPECT_NUM_EQUAL(*((int*)JLinkedListGetLastData(list)), expected3);
	
	EXPECT_NULL(JLinkedListGetFirstData(NULL));

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

	EXPECT_NUM_EQUAL(JLinkedListGetSize(NULL), -1);

	DeleteJLinkedList(&list);
})

TEST(ControlLinkedList, SetLinkedListData, {
	JLinkedListPtr list = NewJLinkedList(0);
	int expected = 5;

	EXPECT_NOT_NULL(JLinkedListSetData(list, &expected));
	EXPECT_NUM_EQUAL(*((int*)JLinkedListGetData(list)), expected);

	EXPECT_NULL(JLinkedListSetData(NULL, &expected));
	EXPECT_NULL(JLinkedListSetData(list, NULL));
	EXPECT_NULL(JLinkedListSetData(NULL, NULL));

	DeleteJLinkedList(&list);
})

TEST(ControlLinkedList, GetLinkedListData, {
	JLinkedListPtr list = NewJLinkedList(0);
	int expected = 5;

	JLinkedListSetData(list, &expected);
	EXPECT_NOT_NULL(JLinkedListGetData(list));
	EXPECT_NUM_EQUAL(*((int*)JLinkedListGetData(list)), 5);

	EXPECT_NULL(JLinkedListGetData(NULL));

	DeleteJLinkedList(&list);
})

TEST(ControlLinkedList, DeleteLinkedListData, {
	JLinkedListPtr list = NewJLinkedList(0);
	int expected1 = 5;

	JLinkedListAddNode(list, &expected1);
	EXPECT_NUM_EQUAL(JLinkedListDeleteData(list, &expected1), DeleteSuccess);
	EXPECT_NULL(JLinkedListGetLastData(list));

	EXPECT_NUM_EQUAL(JLinkedListDeleteData(NULL, &expected1), DeleteFail);
	EXPECT_NUM_EQUAL(JLinkedListDeleteData(list, NULL), DeleteFail);
	EXPECT_NUM_EQUAL(JLinkedListDeleteData(NULL, NULL), DeleteFail);

	DeleteJLinkedList(&list);
})

TEST(ControlLinkedList, FindLinkedListData, {
	JLinkedListPtr list = NewJLinkedList(0);
	int expected1 = 5;

	JLinkedListAddNode(list, &expected1);
	EXPECT_NUM_EQUAL(JLinkedListFindData(list, &expected1), FindSuccess);

	EXPECT_NUM_EQUAL(JLinkedListFindData(NULL, &expected1), FindFail);
	EXPECT_NUM_EQUAL(JLinkedListFindData(list, NULL), FindFail);
	EXPECT_NUM_EQUAL(JLinkedListFindData(NULL, NULL), FindFail);

	DeleteJLinkedList(&list);
})

////////////////////////////////////////////////////////////////////////////////
/// HashTable Test
////////////////////////////////////////////////////////////////////////////////

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

TEST(ControlHashTable, ChangeHashType, {
	int expected = 10;
	JHashTablePtr table = NewJHashTable(expected, IntType);
	EXPECT_NOT_NULL(JHashTableChangeType(table, StringType));
	EXPECT_NUM_EQUAL(table->type, StringType);

	EXPECT_NULL(JHashTableChangeType(NULL, StringType));
	EXPECT_NULL(JHashTableChangeType(table, 123));
	EXPECT_NULL(JHashTableChangeType(NULL, 123));

	DeleteJHashTable(&table);
})

TEST(ControlHashTable, AddData, {
	int size = 10;
	int expected1 = 5;
	JHashTablePtr table = NewJHashTable(size, IntType);
	EXPECT_NOT_NULL(JHashTableAddData(table, &expected1));

	EXPECT_NULL(JHashTableAddData(NULL, &expected1));
	EXPECT_NULL(JHashTableAddData(table, NULL));
	EXPECT_NULL(JHashTableAddData(NULL, NULL));
	
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

TEST(ControlHashTable, DeleteData, {
	int size = 10;
	int expected1 = 4;
	JHashTablePtr table = NewJHashTable(size, IntType);

	JHashTableAddData(table, &expected1);
	EXPECT_NUM_EQUAL(JHashTableDeleteData(table, &expected1), DeleteSuccess);

	EXPECT_NUM_EQUAL(JHashTableDeleteData(NULL, &expected1), DeleteFail);
	EXPECT_NUM_EQUAL(JHashTableDeleteData(table, NULL), DeleteFail);
	EXPECT_NUM_EQUAL(JHashTableDeleteData(NULL, NULL), DeleteFail);

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
		Test_ControlNode_SetData,
		Test_ControlNode_GetData,
		Test_ControlLinkedList_CreateAndDeleteLinkedList,
		Test_ControlLinkedList_AddNode,
		Test_ControlLinkedList_GetLinkedListFirstData,
		Test_ControlLinkedList_GetLinkedListLastData,
		Test_ControlLinkedList_GetLinkedListSize,
		Test_ControlLinkedList_SetLinkedListData,
		Test_ControlLinkedList_GetLinkedListData,
		Test_ControlLinkedList_DeleteLinkedListData,
		Test_ControlLinkedList_FindLinkedListData,
		Test_ControlHashTable_CreateAndDeleteHashTable,
		Test_ControlHashTable_GetHashTableSize,
		Test_ControlHashTable_ChangeHashType,
		Test_ControlHashTable_AddData,
		Test_ControlHashTable_GetFirstData,
		Test_ControlHashTable_GetLastData,
		Test_ControlHashTable_DeleteData
    );

    RUN_ALL_TESTS();

    CLEAN_UP_TESTSUIT();

	return 1;
}


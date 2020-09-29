#include "../include/ttlib.h"
#include "../include/jhashtable.h"

////////////////////////////////////////////////////////////////////////////////
/// Predefinition Of Static Function
////////////////////////////////////////////////////////////////////////////////

static void printIntHash(const JHashTablePtr table);

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

TEST(ControlLinkedList, GetFirstNodeData, {
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

TEST(ControlLinkedList, GetLastNodeData, {
	JLinkedListPtr list = NewJLinkedList(0);

	int expected1 = 5;
	int expected2 = 6;
	int expected3 = 7;

	JLinkedListAddNode(list, &expected1);
	JLinkedListAddNode(list, &expected2);
	JLinkedListAddNode(list, &expected3);

	EXPECT_NUM_EQUAL(*((int*)JLinkedListGetLastNodeData(list)), expected3);
	
	EXPECT_NULL(JLinkedListGetLastNodeData(NULL));

	DeleteJLinkedList(&list);
})

TEST(ControlLinkedList, GetSize, {
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

TEST(ControlLinkedList, SetData, {
	JLinkedListPtr list = NewJLinkedList(0);
	int expected = 5;

	EXPECT_NOT_NULL(JLinkedListSetData(list, &expected));
	EXPECT_NUM_EQUAL(*((int*)JLinkedListGetData(list)), expected);

	EXPECT_NULL(JLinkedListSetData(NULL, &expected));
	EXPECT_NULL(JLinkedListSetData(list, NULL));
	EXPECT_NULL(JLinkedListSetData(NULL, NULL));

	DeleteJLinkedList(&list);
})

TEST(ControlLinkedList, GetData, {
	JLinkedListPtr list = NewJLinkedList(0);
	int expected = 5;

	JLinkedListSetData(list, &expected);
	EXPECT_NOT_NULL(JLinkedListGetData(list));
	EXPECT_NUM_EQUAL(*((int*)JLinkedListGetData(list)), 5);

	EXPECT_NULL(JLinkedListGetData(NULL));

	DeleteJLinkedList(&list);
})

TEST(ControlLinkedList, DeleteNodeData, {
	JLinkedListPtr list = NewJLinkedList(0);
	int expected1 = 5;

	JLinkedListAddNode(list, &expected1);
	EXPECT_NUM_EQUAL(JLinkedListDeleteNodeData(list, &expected1), DeleteSuccess);
	EXPECT_NULL(JLinkedListGetLastNodeData(list));

	EXPECT_NUM_EQUAL(JLinkedListDeleteNodeData(NULL, &expected1), DeleteFail);
	EXPECT_NUM_EQUAL(JLinkedListDeleteNodeData(list, NULL), DeleteFail);
	EXPECT_NUM_EQUAL(JLinkedListDeleteNodeData(NULL, NULL), DeleteFail);

	DeleteJLinkedList(&list);
})

TEST(ControlLinkedList, FindNodeData, {
	JLinkedListPtr list = NewJLinkedList(0);
	int expected1 = 5;

	JLinkedListAddNode(list, &expected1);
	EXPECT_NUM_EQUAL(JLinkedListFindNodeData(list, &expected1), FindSuccess);

	EXPECT_NUM_EQUAL(JLinkedListFindNodeData(NULL, &expected1), FindFail);
	EXPECT_NUM_EQUAL(JLinkedListFindNodeData(list, NULL), FindFail);
	EXPECT_NUM_EQUAL(JLinkedListFindNodeData(NULL, NULL), FindFail);

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

TEST(ControlHashTable, GetSize, {
	int expected = 10;
	JHashTablePtr table = NewJHashTable(expected, IntType);
	EXPECT_NUM_EQUAL(JHashTableGetSize(table), expected);
	DeleteJHashTable(&table);
})

TEST(ControlHashTable, GetType, {
	int size = 10;
	HashType expected = IntType;
	JHashTablePtr table = NewJHashTable(size, IntType);
	EXPECT_NUM_EQUAL(JHashTableGetType(table), expected);
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
	int expected2 = 5;
	JHashTablePtr table = NewJHashTable(size, IntType);

	JHashTableAddData(table, &expected1);
	JHashTableAddData(table, &expected2);
	//printIntHash(table);

	EXPECT_NUM_EQUAL(JHashTableDeleteData(table, &expected2), DeleteSuccess);
	EXPECT_NUM_EQUAL(*((int*)JHashTableGetLastData(table)), expected1);
	//printIntHash(table);

	EXPECT_NUM_EQUAL(JHashTableDeleteData(NULL, &expected1), DeleteFail);
	EXPECT_NUM_EQUAL(JHashTableDeleteData(table, NULL), DeleteFail);
	EXPECT_NUM_EQUAL(JHashTableDeleteData(NULL, NULL), DeleteFail);

	DeleteJHashTable(&table);
})

TEST(ControlHashTable, DeleteFirstData, {
	int size = 10;
	int expected1 = 4;
	int expected2 = 5;
	JHashTablePtr table = NewJHashTable(size, IntType);

	JHashTableAddData(table, &expected1);
	JHashTableAddData(table, &expected2);
	//printIntHash(table);

	EXPECT_NUM_EQUAL(JHashTableDeleteFirstData(table), DeleteSuccess);
	EXPECT_NUM_EQUAL(*((int*)JHashTableGetFirstData(table)), expected2);
	//printIntHash(table);

	EXPECT_NUM_EQUAL(JHashTableDeleteFirstData(NULL), DeleteFail);

	DeleteJHashTable(&table);
})

TEST(ControlHashTable, DeleteLastData, {
	int size = 10;
	int expected1 = 4;
	int expected2 = 5;
	int expected3 = 6;
	JHashTablePtr table = NewJHashTable(size, IntType);

	JHashTableAddData(table, &expected1);
	JHashTableAddData(table, &expected2);
	JHashTableAddData(table, &expected3);
	//printIntHash(table);

	EXPECT_NUM_EQUAL(JHashTableDeleteLastData(table), DeleteSuccess);
	EXPECT_NUM_EQUAL(*((int*)JHashTableGetLastData(table)), expected2);
	//printIntHash(table);

	EXPECT_NUM_EQUAL(JHashTableDeleteLastData(NULL), DeleteFail);

	DeleteJHashTable(&table);
})

TEST(ControlHashTable, FindData, {
	int size = 10;
	int expected1 = 4;
	int expected2 = 5;
	int expected3 = 6;
	JHashTablePtr table = NewJHashTable(size, IntType);

	JHashTableAddData(table, &expected1);
	JHashTableAddData(table, &expected2);
	JHashTableAddData(table, &expected3);
	//printIntHash(table);

	EXPECT_NUM_EQUAL(JHashTableFindData(table, &expected1), FindSuccess);
	EXPECT_NUM_EQUAL(JHashTableFindData(table, &expected2), FindSuccess);
	EXPECT_NUM_EQUAL(JHashTableFindData(table, &expected3), FindSuccess);

	EXPECT_NUM_EQUAL(JHashTableFindData(NULL, &expected1), FindFail);
	EXPECT_NUM_EQUAL(JHashTableFindData(table, NULL), FindFail);
	EXPECT_NUM_EQUAL(JHashTableFindData(NULL, NULL), FindFail);

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
		Test_ControlLinkedList_GetFirstNodeData,
		Test_ControlLinkedList_GetLastNodeData,
		Test_ControlLinkedList_GetSize,
		Test_ControlLinkedList_SetData,
		Test_ControlLinkedList_GetData,
		Test_ControlLinkedList_DeleteNodeData,
		Test_ControlLinkedList_FindNodeData,
		Test_ControlHashTable_CreateAndDeleteHashTable,
		Test_ControlHashTable_GetSize,
		Test_ControlHashTable_GetType,
		Test_ControlHashTable_ChangeHashType,
		Test_ControlHashTable_AddData,
		Test_ControlHashTable_GetFirstData,
		Test_ControlHashTable_GetLastData,
		Test_ControlHashTable_DeleteData,
		Test_ControlHashTable_DeleteFirstData,
		Test_ControlHashTable_DeleteLastData,
		Test_ControlHashTable_FindData
    );

    RUN_ALL_TESTS();

    CLEAN_UP_TESTSUIT();

	return 1;
}

////////////////////////////////////////////////////////////////////////////////
/// Static Function
////////////////////////////////////////////////////////////////////////////////

static void printIntHash(const JHashTablePtr table)
{
	if(table == NULL) return;

	int isDataExist = 0;
	int listIndex = 0;
	int tableSize = table->size;
	JNodePtr head = NULL;
	JNodePtr tail = NULL;
	JNodePtr node = NULL;

	printf("------------------\n");
	for( ; listIndex < tableSize; listIndex++)
	{
		head = table->listContainer[listIndex]->head;
		tail = table->listContainer[listIndex]->tail;
		node = head->next;

		if(node == tail) isDataExist = -1;
		else isDataExist = 1;

		if(isDataExist == 1) printf("[ ");
		while(node != tail)
		{
			printf("%d ", *((int*)node->data));
			node = node->next;
		}
		if(isDataExist == 1) printf("]\n");
	}
	printf("------------------\n");
}

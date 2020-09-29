#include "../include/ttlib.h"
#include "../include/jhashtable.h"

////////////////////////////////////////////////////////////////////////////////
/// Definitions of Test
////////////////////////////////////////////////////////////////////////////////

DECLARE_TEST();

// ---------- Common Test ----------

////////////////////////////////////////////////////////////////////////////////
/// Node Test
////////////////////////////////////////////////////////////////////////////////

TEST(ControlNode, CreateAndDeleteNode, {
	JNodePtr node = NewJNode();
	EXPECT_NOT_NULL(node);
	EXPECT_NUM_EQUAL(DeleteJNode(&node), DeleteSuccess);

	EXPECT_NUM_EQUAL(DeleteJNode(NULL), DeleteFail);
})

////////////////////////////////////////////////////////////////////////////////
/// Linked List Test
////////////////////////////////////////////////////////////////////////////////

TEST(ControlLinkedList, CreateAndDeleteLinkedList, {
	JLinkedListPtr list = NewJLinkedList(0);
	EXPECT_NOT_NULL(list);
	EXPECT_NUM_EQUAL(DeleteJLinkedList(&list), DeleteSuccess);

	EXPECT_NUM_EQUAL(DeleteJLinkedList(NULL), DeleteFail);
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

////////////////////////////////////////////////////////////////////////////////
/// Hash Table Test
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

// ---------- Hash int Test ----------

////////////////////////////////////////////////////////////////////////////////
/// Node Test (int)
////////////////////////////////////////////////////////////////////////////////

TEST(ControlNode_INT, SetData, {
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

TEST(ControlNode_INT, GetData, {
	JNodePtr node = NewJNode();

	int expected = 5;
	JNodeSetData(node, &expected);
	EXPECT_NOT_NULL(JNodeGetData(node));
	EXPECT_NUM_EQUAL(*((int*)JNodeGetData(node)), expected);

	EXPECT_NULL(JNodeGetData(NULL));

	DeleteJNode(&node);
})

////////////////////////////////////////////////////////////////////////////////
/// LinkedList Test (int)
////////////////////////////////////////////////////////////////////////////////

TEST(ControlLinkedList_INT, AddNode, {
	JLinkedListPtr list = NewJLinkedList(0);
	int expected = 5;

	// 정상 동작 확인
	EXPECT_NOT_NULL(JLinkedListAddNode(list, &expected));
	EXPECT_NUM_EQUAL(*((int*)(list->tail->prev->data)), expected);

	// 중복 허용 테스트
	EXPECT_NULL(JLinkedListAddNode(list, &expected));

	// NULL 이 입력값이면, NULL 을 반환
	EXPECT_NULL(JLinkedListAddNode(NULL, &expected));
	EXPECT_NULL(JLinkedListAddNode(list, NULL));
	EXPECT_NULL(JLinkedListAddNode(NULL, NULL));

	DeleteJLinkedList(&list);
})

TEST(ControlLinkedList_INT, GetFirstNodeData, {
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

TEST(ControlLinkedList_INT, GetLastNodeData, {
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

TEST(ControlLinkedList_INT, SetData, {
	JLinkedListPtr list = NewJLinkedList(0);
	int expected = 5;

	EXPECT_NOT_NULL(JLinkedListSetData(list, &expected));
	EXPECT_NUM_EQUAL(*((int*)JLinkedListGetData(list)), expected);

	EXPECT_NULL(JLinkedListSetData(NULL, &expected));
	EXPECT_NULL(JLinkedListSetData(list, NULL));
	EXPECT_NULL(JLinkedListSetData(NULL, NULL));

	DeleteJLinkedList(&list);
})

TEST(ControlLinkedList_INT, GetData, {
	JLinkedListPtr list = NewJLinkedList(0);
	int expected = 5;

	JLinkedListSetData(list, &expected);
	EXPECT_NOT_NULL(JLinkedListGetData(list));
	EXPECT_NUM_EQUAL(*((int*)JLinkedListGetData(list)), 5);

	EXPECT_NULL(JLinkedListGetData(NULL));

	DeleteJLinkedList(&list);
})

TEST(ControlLinkedList_INT, DeleteNodeData, {
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

TEST(ControlLinkedList_INT, FindNodeData, {
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
/// HashTable Test (int)
////////////////////////////////////////////////////////////////////////////////

TEST(ControlHashTable_INT, AddData, {
	int size = 10;
	int expectedKey1 = 5;
	int expectedValue1 = 10;
	JHashTablePtr table = NewJHashTable(size, IntType);
	EXPECT_NOT_NULL(JHashTableAddData(table, &expectedKey1, &expectedValue1));

	EXPECT_NULL(JHashTableAddData(NULL, &expectedKey1, &expectedValue1));
	EXPECT_NULL(JHashTableAddData(NULL, &expectedKey1, NULL));
	EXPECT_NULL(JHashTableAddData(NULL, NULL, &expectedValue1));
	EXPECT_NULL(JHashTableAddData(table, NULL, NULL));
	EXPECT_NULL(JHashTableAddData(table, &expectedKey1, NULL));
	EXPECT_NULL(JHashTableAddData(table, NULL, &expectedValue1));
	EXPECT_NULL(JHashTableAddData(NULL, NULL, NULL));
	
	DeleteJHashTable(&table);
})

TEST(ControlHashTable_INT, GetFirstData, {
	int size = 10;
	int expectedKey1 = 4;
	int expectedValue1 = 10;
	int expectedKey2 = 5;
	int expectedValue2 = 11;
	JHashTablePtr table = NewJHashTable(size, IntType);

	JHashTableAddData(table, &expectedKey1, &expectedValue1);
	JHashTableAddData(table, &expectedKey2, &expectedValue2);
	EXPECT_NUM_EQUAL(*((int*)JHashTableGetFirstData(table)), expectedValue1);

	EXPECT_NULL(JHashTableGetFirstData(NULL));

	DeleteJHashTable(&table);
})

TEST(ControlHashTable_INT, GetLastData, {
	int size = 10;
	int expectedKey1 = 4;
	int expectedValue1 = 10;
	int expectedKey2 = 5;
	int expectedValue2 = 11;
	JHashTablePtr table = NewJHashTable(size, IntType);

	JHashTableAddData(table, &expectedKey1, &expectedValue1);
	JHashTableAddData(table, &expectedKey2, &expectedValue2);
	EXPECT_NUM_EQUAL(*((int*)JHashTableGetLastData(table)), expectedValue2);

	EXPECT_NULL(JHashTableGetLastData(NULL));

	DeleteJHashTable(&table);
})

TEST(ControlHashTable_INT, DeleteData, {
	int size = 10;
	int expectedKey1 = 4;
	int expectedValue1 = 10;
	int expectedKey2 = 5;
	int expectedValue2 = 11;
	JHashTablePtr table = NewJHashTable(size, IntType);

	JHashTableAddData(table, &expectedKey1, &expectedValue1);
	JHashTableAddData(table, &expectedKey2, &expectedValue2);
	//JHashTablePrintAll(table);

	EXPECT_NUM_EQUAL(JHashTableDeleteData(table, &expectedKey2, &expectedValue2), DeleteSuccess);
	EXPECT_NUM_EQUAL(*((int*)JHashTableGetLastData(table)), expectedValue1);
	//JHashTablePrintAll(table);

	EXPECT_NUM_EQUAL(JHashTableDeleteData(NULL, &expectedKey1, &expectedValue1), DeleteFail);
	EXPECT_NUM_EQUAL(JHashTableDeleteData(NULL, &expectedKey1, NULL), DeleteFail);
	EXPECT_NUM_EQUAL(JHashTableDeleteData(NULL, NULL, &expectedValue1), DeleteFail);
	EXPECT_NUM_EQUAL(JHashTableDeleteData(table, NULL, NULL), DeleteFail);
	EXPECT_NUM_EQUAL(JHashTableDeleteData(table, &expectedKey1, NULL), DeleteFail);
	EXPECT_NUM_EQUAL(JHashTableDeleteData(table, NULL, &expectedValue1), DeleteFail);
	EXPECT_NUM_EQUAL(JHashTableDeleteData(NULL, NULL, NULL), DeleteFail);

	DeleteJHashTable(&table);
})

TEST(ControlHashTable_INT, DeleteFirstData, {
	int size = 10;
	int expectedKey1 = 4;
	int expectedValue1 = 10;
	int expectedKey2 = 5;
	int expectedValue2 = 11;
	JHashTablePtr table = NewJHashTable(size, IntType);

	JHashTableAddData(table, &expectedKey1, &expectedValue1);
	JHashTableAddData(table, &expectedKey2, &expectedValue2);
	//JHashTablePrintAll(table);

	EXPECT_NUM_EQUAL(JHashTableDeleteFirstData(table), DeleteSuccess);
	EXPECT_NUM_EQUAL(*((int*)JHashTableGetFirstData(table)), expectedValue2);
	//JHashTablePrintAll(table);

	EXPECT_NUM_EQUAL(JHashTableDeleteFirstData(NULL), DeleteFail);

	DeleteJHashTable(&table);
})

TEST(ControlHashTable_INT, DeleteLastData, {
	int size = 10;
	int expectedKey1 = 4;
	int expectedValue1 = 10;
	int expectedKey2 = 5;
	int expectedValue2 = 11;
	JHashTablePtr table = NewJHashTable(size, IntType);

	JHashTableAddData(table, &expectedKey1, &expectedValue1);
	JHashTableAddData(table, &expectedKey2, &expectedValue2);
	//JHashTablePrintAll(table);

	EXPECT_NUM_EQUAL(JHashTableDeleteLastData(table), DeleteSuccess);
	EXPECT_NUM_EQUAL(*((int*)JHashTableGetLastData(table)), expectedValue1);
	//JHashTablePrintAll(table);

	EXPECT_NUM_EQUAL(JHashTableDeleteLastData(NULL), DeleteFail);

	DeleteJHashTable(&table);
})

TEST(ControlHashTable_INT, FindData, {
	int size = 10;
	int expectedKey1 = 4;
	int expectedValue1 = 10;
	int expectedKey2 = 5;
	int expectedValue2 = 11;
	JHashTablePtr table = NewJHashTable(size, IntType);

	JHashTableAddData(table, &expectedKey1, &expectedValue1);
	JHashTableAddData(table, &expectedKey2, &expectedValue2);
	//JHashTablePrintAll(table);

	EXPECT_NUM_EQUAL(JHashTableFindData(table, &expectedKey1, &expectedValue1), FindSuccess);
	EXPECT_NUM_EQUAL(JHashTableFindData(table, &expectedKey2, &expectedValue2), FindSuccess);

	EXPECT_NUM_EQUAL(JHashTableFindData(NULL, &expectedKey1, &expectedValue1), FindFail);
	EXPECT_NUM_EQUAL(JHashTableFindData(NULL, &expectedKey1, NULL), FindFail);
	EXPECT_NUM_EQUAL(JHashTableFindData(NULL, NULL, &expectedValue1), FindFail);
	EXPECT_NUM_EQUAL(JHashTableFindData(table, NULL, NULL), FindFail);
	EXPECT_NUM_EQUAL(JHashTableFindData(table, &expectedKey1, NULL), FindFail);
	EXPECT_NUM_EQUAL(JHashTableFindData(table, NULL, &expectedValue1), FindFail);
	EXPECT_NUM_EQUAL(JHashTableFindData(NULL, NULL, NULL), FindFail);

	DeleteJHashTable(&table);
})

// ---------- Hash char Test ----------

////////////////////////////////////////////////////////////////////////////////
/// Node Test (char)
////////////////////////////////////////////////////////////////////////////////

TEST(ControlNode_CHAR, SetData, {
	JNodePtr node = NewJNode();

	char expected = 'a';
	EXPECT_NOT_NULL(JNodeSetData(node, &expected));
	EXPECT_PTR_EQUAL(node->data, &expected);
	EXPECT_NUM_EQUAL(*((char*)(node->data)), expected);

	EXPECT_NULL(JNodeSetData(NULL, &expected));
	EXPECT_NULL(JNodeSetData(node, NULL));
	EXPECT_NULL(JNodeSetData(NULL, NULL));

	DeleteJNode(&node);
})

TEST(ControlNode_CHAR, GetData, {
	JNodePtr node = NewJNode();

	char expected = 'a';
	JNodeSetData(node, &expected);
	EXPECT_NOT_NULL(JNodeGetData(node));
	EXPECT_NUM_EQUAL(*((char*)JNodeGetData(node)), expected);

	EXPECT_NULL(JNodeGetData(NULL));

	DeleteJNode(&node);
})

////////////////////////////////////////////////////////////////////////////////
/// LinkedList Test (char)
////////////////////////////////////////////////////////////////////////////////

TEST(ControlLinkedList_CHAR, AddNode, {
	JLinkedListPtr list = NewJLinkedList(0);
	char expected = 'a';

	// 정상 동작 확인
	EXPECT_NOT_NULL(JLinkedListAddNode(list, &expected));
	EXPECT_NUM_EQUAL(*((char*)(list->tail->prev->data)), expected);

	// 중복 허용 테스트
	EXPECT_NULL(JLinkedListAddNode(list, &expected));

	// NULL 이 입력값이면, NULL 을 반환
	EXPECT_NULL(JLinkedListAddNode(NULL, &expected));
	EXPECT_NULL(JLinkedListAddNode(list, NULL));
	EXPECT_NULL(JLinkedListAddNode(NULL, NULL));

	DeleteJLinkedList(&list);
})

TEST(ControlLinkedList_CHAR, GetFirstNodeData, {
	JLinkedListPtr list = NewJLinkedList(0);

	char expected1 = 'a';
	char expected2 = 'b';
	char expected3 = 'c';

	JLinkedListAddNode(list, &expected1);
	JLinkedListAddNode(list, &expected2);
	JLinkedListAddNode(list, &expected3);

	EXPECT_NUM_EQUAL(*((char*)JLinkedListGetFirstNodeData(list)), expected1);

	EXPECT_NULL(JLinkedListGetFirstNodeData(NULL));

	DeleteJLinkedList(&list);
})

TEST(ControlLinkedList_CHAR, GetLastNodeData, {
	JLinkedListPtr list = NewJLinkedList(0);

	char expected1 = 'a';
	char expected2 = 'b';
	char expected3 = 'c';

	JLinkedListAddNode(list, &expected1);
	JLinkedListAddNode(list, &expected2);
	JLinkedListAddNode(list, &expected3);

	EXPECT_NUM_EQUAL(*((char*)JLinkedListGetLastNodeData(list)), expected3);
	
	EXPECT_NULL(JLinkedListGetLastNodeData(NULL));

	DeleteJLinkedList(&list);
})

TEST(ControlLinkedList_CHAR, SetData, {
	JLinkedListPtr list = NewJLinkedList(0);
	char expected = 'a';

	EXPECT_NOT_NULL(JLinkedListSetData(list, &expected));
	EXPECT_NUM_EQUAL(*((char*)JLinkedListGetData(list)), expected);

	EXPECT_NULL(JLinkedListSetData(NULL, &expected));
	EXPECT_NULL(JLinkedListSetData(list, NULL));
	EXPECT_NULL(JLinkedListSetData(NULL, NULL));

	DeleteJLinkedList(&list);
})

TEST(ControlLinkedList_CHAR, GetData, {
	JLinkedListPtr list = NewJLinkedList(0);
	char expected = 'a';

	JLinkedListSetData(list, &expected);
	EXPECT_NOT_NULL(JLinkedListGetData(list));
	EXPECT_NUM_EQUAL(*((char*)JLinkedListGetData(list)), expected);

	EXPECT_NULL(JLinkedListGetData(NULL));

	DeleteJLinkedList(&list);
})

TEST(ControlLinkedList_CHAR, DeleteNodeData, {
	JLinkedListPtr list = NewJLinkedList(0);
	char expected1 = 'a';

	JLinkedListAddNode(list, &expected1);
	EXPECT_NUM_EQUAL(JLinkedListDeleteNodeData(list, &expected1), DeleteSuccess);
	EXPECT_NULL(JLinkedListGetLastNodeData(list));

	EXPECT_NUM_EQUAL(JLinkedListDeleteNodeData(NULL, &expected1), DeleteFail);
	EXPECT_NUM_EQUAL(JLinkedListDeleteNodeData(list, NULL), DeleteFail);
	EXPECT_NUM_EQUAL(JLinkedListDeleteNodeData(NULL, NULL), DeleteFail);

	DeleteJLinkedList(&list);
})

TEST(ControlLinkedList_CHAR, FindNodeData, {
	JLinkedListPtr list = NewJLinkedList(0);
	char expected1 = 'a';

	JLinkedListAddNode(list, &expected1);
	EXPECT_NUM_EQUAL(JLinkedListFindNodeData(list, &expected1), FindSuccess);

	EXPECT_NUM_EQUAL(JLinkedListFindNodeData(NULL, &expected1), FindFail);
	EXPECT_NUM_EQUAL(JLinkedListFindNodeData(list, NULL), FindFail);
	EXPECT_NUM_EQUAL(JLinkedListFindNodeData(NULL, NULL), FindFail);

	DeleteJLinkedList(&list);
})

////////////////////////////////////////////////////////////////////////////////
/// HashTable Test (char)
////////////////////////////////////////////////////////////////////////////////

TEST(ControlHashTable_CHAR, AddData, {
	int size = 10;
	char expectedKey1 = 'a';
	char expectedValue1 = 'd';
	JHashTablePtr table = NewJHashTable(size, CharType);
	EXPECT_NOT_NULL(JHashTableAddData(table, &expectedKey1, &expectedValue1));

	EXPECT_NULL(JHashTableAddData(NULL, &expectedKey1, &expectedValue1));
	EXPECT_NULL(JHashTableAddData(NULL, &expectedKey1, NULL));
	EXPECT_NULL(JHashTableAddData(NULL, NULL, &expectedValue1));
	EXPECT_NULL(JHashTableAddData(table, NULL, NULL));
	EXPECT_NULL(JHashTableAddData(table, &expectedKey1, NULL));
	EXPECT_NULL(JHashTableAddData(table, NULL, &expectedValue1));
	EXPECT_NULL(JHashTableAddData(NULL, NULL, NULL));
	
	DeleteJHashTable(&table);
})

TEST(ControlHashTable_CHAR, GetFirstData, {
	int size = 10;
	char expectedKey1 = 'a';
	char expectedValue1 = 'x';
	char expectedKey2 = 'b';
	char expectedValue2 = 'y';
	JHashTablePtr table = NewJHashTable(size, CharType);

	JHashTableAddData(table, &expectedKey1, &expectedValue1);
	JHashTableAddData(table, &expectedKey2, &expectedValue2);
	EXPECT_NUM_EQUAL(*((char*)JHashTableGetFirstData(table)), expectedValue1);

	EXPECT_NULL(JHashTableGetFirstData(NULL));

	DeleteJHashTable(&table);
})

TEST(ControlHashTable_CHAR, GetLastData, {
	int size = 10;
	char expectedKey1 = 'a';
	char expectedValue1 = 'x';
	char expectedKey2 = 'b';
	char expectedValue2 = 'y';
	JHashTablePtr table = NewJHashTable(size, CharType);

	JHashTableAddData(table, &expectedKey1, &expectedValue1);
	JHashTableAddData(table, &expectedKey2, &expectedValue2);
	EXPECT_NUM_EQUAL(*((char*)JHashTableGetLastData(table)), expectedValue2);

	EXPECT_NULL(JHashTableGetLastData(NULL));

	DeleteJHashTable(&table);
})

TEST(ControlHashTable_CHAR, DeleteData, {
	int size = 10;
	char expectedKey1 = 'a';
	char expectedValue1 = 'x';
	char expectedKey2 = 'b';
	char expectedValue2 = 'y';
	JHashTablePtr table = NewJHashTable(size, CharType);

	JHashTableAddData(table, &expectedKey1, &expectedValue1);
	JHashTableAddData(table, &expectedKey2, &expectedValue2);
	//JHashTablePrintAll(table);

	EXPECT_NUM_EQUAL(JHashTableDeleteData(table, &expectedKey2, &expectedValue2), DeleteSuccess);
	EXPECT_NUM_EQUAL(*((char*)JHashTableGetLastData(table)), expectedValue1);
	//JHashTablePrintAll(table);

	EXPECT_NUM_EQUAL(JHashTableDeleteData(NULL, &expectedKey1, &expectedValue1), DeleteFail);
	EXPECT_NUM_EQUAL(JHashTableDeleteData(NULL, &expectedKey1, NULL), DeleteFail);
	EXPECT_NUM_EQUAL(JHashTableDeleteData(NULL, NULL, &expectedValue1), DeleteFail);
	EXPECT_NUM_EQUAL(JHashTableDeleteData(table, NULL, NULL), DeleteFail);
	EXPECT_NUM_EQUAL(JHashTableDeleteData(table, &expectedKey1, NULL), DeleteFail);
	EXPECT_NUM_EQUAL(JHashTableDeleteData(table, NULL, &expectedValue1), DeleteFail);
	EXPECT_NUM_EQUAL(JHashTableDeleteData(NULL, NULL, NULL), DeleteFail);

	DeleteJHashTable(&table);
})

TEST(ControlHashTable_CHAR, DeleteFirstData, {
	int size = 10;
	char expectedKey1 = 'a';
	char expectedValue1 = 'x';
	char expectedKey2 = 'b';
	char expectedValue2 = 'y';
	JHashTablePtr table = NewJHashTable(size, CharType);

	JHashTableAddData(table, &expectedKey1, &expectedValue1);
	JHashTableAddData(table, &expectedKey2, &expectedValue2);
	//JHashTablePrintAll(table);

	EXPECT_NUM_EQUAL(JHashTableDeleteFirstData(table), DeleteSuccess);
	EXPECT_NUM_EQUAL(*((char*)JHashTableGetFirstData(table)), expectedValue2);
	//JHashTablePrintAll(table);

	EXPECT_NUM_EQUAL(JHashTableDeleteFirstData(NULL), DeleteFail);

	DeleteJHashTable(&table);
})

TEST(ControlHashTable_CHAR, DeleteLastData, {
	int size = 10;
	char expectedKey1 = 'a';
	char expectedValue1 = 'x';
	char expectedKey2 = 'b';
	char expectedValue2 = 'y';
	JHashTablePtr table = NewJHashTable(size, CharType);

	JHashTableAddData(table, &expectedKey1, &expectedValue1);
	JHashTableAddData(table, &expectedKey2, &expectedValue2);
	//JHashTablePrintAll(table);

	EXPECT_NUM_EQUAL(JHashTableDeleteLastData(table), DeleteSuccess);
	EXPECT_NUM_EQUAL(*((char*)JHashTableGetLastData(table)), expectedValue1);
	//JHashTablePrintAll(table);

	EXPECT_NUM_EQUAL(JHashTableDeleteLastData(NULL), DeleteFail);

	DeleteJHashTable(&table);
})

TEST(ControlHashTable_CHAR, FindData, {
	int size = 10;
	char expectedKey1 = 'a';
	char expectedValue1 = 'x';
	char expectedKey2 = 'b';
	char expectedValue2 = 'y';
	JHashTablePtr table = NewJHashTable(size, CharType);

	JHashTableAddData(table, &expectedKey1, &expectedValue1);
	JHashTableAddData(table, &expectedKey2, &expectedValue2);
	//JHashTablePrintAll(table);

	EXPECT_NUM_EQUAL(JHashTableFindData(table, &expectedKey1, &expectedValue1), FindSuccess);
	EXPECT_NUM_EQUAL(JHashTableFindData(table, &expectedKey2, &expectedValue2), FindSuccess);

	EXPECT_NUM_EQUAL(JHashTableFindData(NULL, &expectedKey1, &expectedValue1), FindFail);
	EXPECT_NUM_EQUAL(JHashTableFindData(NULL, &expectedKey1, NULL), FindFail);
	EXPECT_NUM_EQUAL(JHashTableFindData(NULL, NULL, &expectedValue1), FindFail);
	EXPECT_NUM_EQUAL(JHashTableFindData(table, NULL, NULL), FindFail);
	EXPECT_NUM_EQUAL(JHashTableFindData(table, &expectedKey1, NULL), FindFail);
	EXPECT_NUM_EQUAL(JHashTableFindData(table, NULL, &expectedValue1), FindFail);
	EXPECT_NUM_EQUAL(JHashTableFindData(NULL, NULL, NULL), FindFail);

	DeleteJHashTable(&table);
})

////////////////////////////////////////////////////////////////////////////////
/// Main Function
////////////////////////////////////////////////////////////////////////////////

int main()
{
    CREATE_TESTSUIT();

    REGISTER_TESTS(
		// (Common) -----------------------------------------
		Test_ControlNode_CreateAndDeleteNode,
		Test_ControlLinkedList_CreateAndDeleteLinkedList,
		Test_ControlLinkedList_GetSize,
		Test_ControlHashTable_CreateAndDeleteHashTable,
		Test_ControlHashTable_GetSize,
		Test_ControlHashTable_GetType,
		Test_ControlHashTable_ChangeHashType,

		// _INT -------------------------------------------
		Test_ControlNode_INT_SetData,
		Test_ControlNode_INT_GetData,
		Test_ControlLinkedList_INT_AddNode,
		Test_ControlLinkedList_INT_GetFirstNodeData,
		Test_ControlLinkedList_INT_GetLastNodeData,
		Test_ControlLinkedList_INT_SetData,
		Test_ControlLinkedList_INT_GetData,
		Test_ControlLinkedList_INT_DeleteNodeData,
		Test_ControlLinkedList_INT_FindNodeData,
		Test_ControlHashTable_INT_AddData,
		Test_ControlHashTable_INT_GetFirstData,
		Test_ControlHashTable_INT_GetLastData,
		Test_ControlHashTable_INT_DeleteData,
		Test_ControlHashTable_INT_DeleteFirstData,
		Test_ControlHashTable_INT_DeleteLastData,
		Test_ControlHashTable_INT_FindData,

		// _CHAR -------------------------------------------
		Test_ControlNode_CHAR_SetData,
		Test_ControlNode_CHAR_GetData,
		Test_ControlLinkedList_CHAR_AddNode,
		Test_ControlLinkedList_CHAR_GetFirstNodeData,
		Test_ControlLinkedList_CHAR_GetLastNodeData,
		Test_ControlLinkedList_CHAR_SetData,
		Test_ControlLinkedList_CHAR_GetData,
		Test_ControlLinkedList_CHAR_DeleteNodeData,
		Test_ControlLinkedList_CHAR_FindNodeData,
		Test_ControlHashTable_CHAR_AddData,
		Test_ControlHashTable_CHAR_GetFirstData,
		Test_ControlHashTable_CHAR_GetLastData,
		Test_ControlHashTable_CHAR_DeleteData,
		Test_ControlHashTable_CHAR_DeleteFirstData,
		Test_ControlHashTable_CHAR_DeleteLastData,
		Test_ControlHashTable_CHAR_FindData

		// (STRING) -------------------------------------------
    );

    RUN_ALL_TESTS();

    CLEAN_UP_TESTSUIT();

	return 1;
}


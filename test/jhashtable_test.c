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

TEST(Node, CreateAndDeleteNode, {
	JNodePtr node = NewJNode();
	EXPECT_NOT_NULL(node);
	EXPECT_NUM_EQUAL(DeleteJNode(&node), DeleteSuccess);

	EXPECT_NUM_EQUAL(DeleteJNode(NULL), DeleteFail);
})

////////////////////////////////////////////////////////////////////////////////
/// Linked List Test
////////////////////////////////////////////////////////////////////////////////

TEST(LinkedList, CreateAndDeleteLinkedList, {
	JLinkedListPtr list = NewJLinkedList(0);
	EXPECT_NOT_NULL(list);
	EXPECT_NUM_EQUAL(DeleteJLinkedList(&list), DeleteSuccess);

	EXPECT_NULL(NewJLinkedList(-1));
	EXPECT_NUM_EQUAL(DeleteJLinkedList(NULL), DeleteFail);
})

TEST(LinkedList, GetSize, {
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

TEST(HashTable, CreateAndDeleteHashTable, {
	int size = 10;
	JHashTablePtr table = NewJHashTable(size, IntType, IntType);
	EXPECT_NOT_NULL(table);
	EXPECT_NUM_EQUAL(DeleteJHashTable(&table), DeleteSuccess);

	EXPECT_NULL(NewJHashTable(-1, IntType, IntType));
	EXPECT_NULL(NewJHashTable(0, IntType, IntType));
	EXPECT_NULL(NewJHashTable(size, 123, IntType));
	EXPECT_NULL(NewJHashTable(size, IntType, 456));
	EXPECT_NULL(NewJHashTable(size, 123, 456));
	EXPECT_NULL(NewJHashTable(0, 123, 456));
	EXPECT_NULL(NewJHashTable(0, 123, IntType));
	EXPECT_NULL(NewJHashTable(0, IntType, 456));

	EXPECT_NUM_EQUAL(DeleteJHashTable(NULL), DeleteFail);
})

TEST(HashTable, GetSize, {
	int expected = 10;
	JHashTablePtr table = NewJHashTable(expected, IntType, IntType);
	EXPECT_NUM_EQUAL(JHashTableGetSize(table), expected);
	DeleteJHashTable(&table);
})

TEST(HashTable, GetType, {
	int size = 10;
	HashType expected = IntType;
	JHashTablePtr table = NewJHashTable(size, IntType, IntType);
	EXPECT_NUM_EQUAL(JHashTableGetType(table), expected);
	DeleteJHashTable(&table);
})

TEST(HashTable, ChangeHashType, {
	int expected = 10;
	JHashTablePtr table = NewJHashTable(expected, IntType, IntType);

	EXPECT_NOT_NULL(JHashTableSetType(table, Key, StringType));
	EXPECT_NUM_EQUAL(table->keyType, StringType);

	EXPECT_NOT_NULL(JHashTableSetType(table, Value, CharType));
	EXPECT_NUM_EQUAL(table->valueType, CharType);

	EXPECT_NULL(JHashTableSetType(NULL, Key, StringType));
	EXPECT_NULL(JHashTableSetType(NULL, Key, 123));
	EXPECT_NULL(JHashTableSetType(NULL, 456, StringType));
	EXPECT_NULL(JHashTableSetType(NULL, 456, 123));
	EXPECT_NULL(JHashTableSetType(table, Value, 123));
	EXPECT_NULL(JHashTableSetType(table, 456, CharType));
	EXPECT_NULL(JHashTableSetType(table, 456, 123));

	DeleteJHashTable(&table);
})

// ---------- Hash int Test ----------

////////////////////////////////////////////////////////////////////////////////
/// Node Test (int)
////////////////////////////////////////////////////////////////////////////////

TEST(Node_INT, SetData, {
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

TEST(Node_INT, GetData, {
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

TEST(LinkedList_INT, AddNode, {
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

TEST(LinkedList_INT, GetFirstNodeData, {
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

TEST(LinkedList_INT, GetLastNodeData, {
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

TEST(LinkedList_INT, SetData, {
	JLinkedListPtr list = NewJLinkedList(0);
	int expected = 5;

	EXPECT_NOT_NULL(JLinkedListSetData(list, &expected));
	EXPECT_NUM_EQUAL(*((int*)JLinkedListGetData(list)), expected);

	EXPECT_NULL(JLinkedListSetData(NULL, &expected));
	EXPECT_NULL(JLinkedListSetData(list, NULL));
	EXPECT_NULL(JLinkedListSetData(NULL, NULL));

	DeleteJLinkedList(&list);
})

TEST(LinkedList_INT, GetData, {
	JLinkedListPtr list = NewJLinkedList(0);
	int expected = 5;

	JLinkedListSetData(list, &expected);
	EXPECT_NOT_NULL(JLinkedListGetData(list));
	EXPECT_NUM_EQUAL(*((int*)JLinkedListGetData(list)), 5);

	EXPECT_NULL(JLinkedListGetData(NULL));

	DeleteJLinkedList(&list);
})

TEST(LinkedList_INT, DeleteNodeData, {
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

TEST(LinkedList_INT, FindNodeData, {
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

TEST(HashTable_INT, AddData, {
	int size = 10;
	int expectedKey1 = 5;
	int expectedValue1 = 10;
	JHashTablePtr table = NewJHashTable(size, IntType, IntType);
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

TEST(HashTable_INT, GetFirstData, {
	int size = 10;
	int expectedKey1 = 4;
	int expectedValue1_1 = 10;
	int expectedValue1_2 = 20;
	int expectedKey2 = 5;
	int expectedValue2 = 11;
	JHashTablePtr table = NewJHashTable(size, IntType, IntType);

	JHashTableAddData(table, &expectedKey1, &expectedValue1_1);
	JHashTableAddData(table, &expectedKey1, &expectedValue1_2);
	JHashTableAddData(table, &expectedKey2, &expectedValue2);
	EXPECT_NUM_EQUAL(*((int*)JHashTableGetFirstData(table)), expectedValue1_1);
	JHashTablePrintAll(table);

	EXPECT_NULL(JHashTableGetFirstData(NULL));

	DeleteJHashTable(&table);
})

TEST(HashTable_INT, GetLastData, {
	int size = 10;
	int expectedKey1 = 4;
	int expectedValue1_1 = 10;
	int expectedKey2 = 5;
	int expectedValue2_1 = 11;
	int expectedValue2_2 = 22;
	JHashTablePtr table = NewJHashTable(size, IntType, IntType);

	JHashTableAddData(table, &expectedKey1, &expectedValue1_1);
	JHashTableAddData(table, &expectedKey2, &expectedValue2_1);
	JHashTableAddData(table, &expectedKey2, &expectedValue2_2);
	EXPECT_NUM_EQUAL(*((int*)JHashTableGetLastData(table)), expectedValue2_2);
	JHashTablePrintAll(table);

	EXPECT_NULL(JHashTableGetLastData(NULL));

	DeleteJHashTable(&table);
})

TEST(HashTable_INT, DeleteData, {
	int size = 10;
	int expectedKey1 = 4;
	int expectedValue1 = 10;
	int expectedKey2 = 5;
	int expectedValue2 = 11;
	JHashTablePtr table = NewJHashTable(size, IntType, IntType);

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

TEST(HashTable_INT, DeleteFirstData, {
	int size = 10;
	int expectedKey1 = 4;
	int expectedValue1 = 10;
	int expectedKey2 = 5;
	int expectedValue2 = 11;
	JHashTablePtr table = NewJHashTable(size, IntType, IntType);

	JHashTableAddData(table, &expectedKey1, &expectedValue1);
	JHashTableAddData(table, &expectedKey2, &expectedValue2);
	//JHashTablePrintAll(table);

	EXPECT_NUM_EQUAL(JHashTableDeleteFirstData(table), DeleteSuccess);
	EXPECT_NUM_EQUAL(*((int*)JHashTableGetFirstData(table)), expectedValue2);
	//JHashTablePrintAll(table);

	EXPECT_NUM_EQUAL(JHashTableDeleteFirstData(NULL), DeleteFail);

	DeleteJHashTable(&table);
})

TEST(HashTable_INT, DeleteLastData, {
	int size = 10;
	int expectedKey1 = 4;
	int expectedValue1 = 10;
	int expectedKey2 = 5;
	int expectedValue2 = 11;
	JHashTablePtr table = NewJHashTable(size, IntType, IntType);

	JHashTableAddData(table, &expectedKey1, &expectedValue1);
	JHashTableAddData(table, &expectedKey2, &expectedValue2);
	//JHashTablePrintAll(table);

	EXPECT_NUM_EQUAL(JHashTableDeleteLastData(table), DeleteSuccess);
	EXPECT_NUM_EQUAL(*((int*)JHashTableGetLastData(table)), expectedValue1);
	//JHashTablePrintAll(table);

	EXPECT_NUM_EQUAL(JHashTableDeleteLastData(NULL), DeleteFail);

	DeleteJHashTable(&table);
})

TEST(HashTable_INT, FindData, {
	int size = 10;
	int expectedKey1 = 4;
	int expectedValue1 = 10;
	int expectedKey2 = 5;
	int expectedValue2 = 11;
	JHashTablePtr table = NewJHashTable(size, IntType, IntType);

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

TEST(Node_CHAR, SetData, {
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

TEST(Node_CHAR, GetData, {
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

TEST(LinkedList_CHAR, AddNode, {
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

TEST(LinkedList_CHAR, GetFirstNodeData, {
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

TEST(LinkedList_CHAR, GetLastNodeData, {
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

TEST(LinkedList_CHAR, SetData, {
	JLinkedListPtr list = NewJLinkedList(0);
	char expected = 'a';

	EXPECT_NOT_NULL(JLinkedListSetData(list, &expected));
	EXPECT_NUM_EQUAL(*((char*)JLinkedListGetData(list)), expected);

	EXPECT_NULL(JLinkedListSetData(NULL, &expected));
	EXPECT_NULL(JLinkedListSetData(list, NULL));
	EXPECT_NULL(JLinkedListSetData(NULL, NULL));

	DeleteJLinkedList(&list);
})

TEST(LinkedList_CHAR, GetData, {
	JLinkedListPtr list = NewJLinkedList(0);
	char expected = 'a';

	JLinkedListSetData(list, &expected);
	EXPECT_NOT_NULL(JLinkedListGetData(list));
	EXPECT_NUM_EQUAL(*((char*)JLinkedListGetData(list)), expected);

	EXPECT_NULL(JLinkedListGetData(NULL));

	DeleteJLinkedList(&list);
})

TEST(LinkedList_CHAR, DeleteNodeData, {
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

TEST(LinkedList_CHAR, FindNodeData, {
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

TEST(HashTable_CHAR, AddData, {
	int size = 10;
	char expectedKey1 = 'a';
	char expectedValue1 = 'd';
	JHashTablePtr table = NewJHashTable(size, CharType, CharType);
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

TEST(HashTable_CHAR, GetFirstData, {
	int size = 10;
	char expectedKey1 = 'a';
	char expectedValue1 = 'x';
	char expectedKey2 = 'b';
	char expectedValue2 = 'y';
	JHashTablePtr table = NewJHashTable(size, CharType, CharType);

	JHashTableAddData(table, &expectedKey1, &expectedValue1);
	JHashTableAddData(table, &expectedKey2, &expectedValue2);
	EXPECT_NUM_EQUAL(*((char*)JHashTableGetFirstData(table)), expectedValue1);

	EXPECT_NULL(JHashTableGetFirstData(NULL));

	DeleteJHashTable(&table);
})

TEST(HashTable_CHAR, GetLastData, {
	int size = 10;
	char expectedKey1 = 'a';
	char expectedValue1 = 'x';
	char expectedKey2 = 'b';
	char expectedValue2 = 'y';
	JHashTablePtr table = NewJHashTable(size, CharType, CharType);

	JHashTableAddData(table, &expectedKey1, &expectedValue1);
	JHashTableAddData(table, &expectedKey2, &expectedValue2);
	EXPECT_NUM_EQUAL(*((char*)JHashTableGetLastData(table)), expectedValue2);

	EXPECT_NULL(JHashTableGetLastData(NULL));

	DeleteJHashTable(&table);
})

TEST(HashTable_CHAR, DeleteData, {
	int size = 10;
	char expectedKey1 = 'a';
	char expectedValue1 = 'x';
	char expectedKey2 = 'b';
	char expectedValue2 = 'y';
	JHashTablePtr table = NewJHashTable(size, CharType, CharType);

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

TEST(HashTable_CHAR, DeleteFirstData, {
	int size = 10;
	char expectedKey1 = 'a';
	char expectedValue1 = 'x';
	char expectedKey2 = 'b';
	char expectedValue2 = 'y';
	JHashTablePtr table = NewJHashTable(size, CharType, CharType);

	JHashTableAddData(table, &expectedKey1, &expectedValue1);
	JHashTableAddData(table, &expectedKey2, &expectedValue2);
	//JHashTablePrintAll(table);

	EXPECT_NUM_EQUAL(JHashTableDeleteFirstData(table), DeleteSuccess);
	EXPECT_NUM_EQUAL(*((char*)JHashTableGetFirstData(table)), expectedValue2);
	//JHashTablePrintAll(table);

	EXPECT_NUM_EQUAL(JHashTableDeleteFirstData(NULL), DeleteFail);

	DeleteJHashTable(&table);
})

TEST(HashTable_CHAR, DeleteLastData, {
	int size = 10;
	char expectedKey1 = 'a';
	char expectedValue1 = 'x';
	char expectedKey2 = 'b';
	char expectedValue2 = 'y';
	JHashTablePtr table = NewJHashTable(size, CharType, CharType);

	JHashTableAddData(table, &expectedKey1, &expectedValue1);
	JHashTableAddData(table, &expectedKey2, &expectedValue2);
	//JHashTablePrintAll(table);

	EXPECT_NUM_EQUAL(JHashTableDeleteLastData(table), DeleteSuccess);
	EXPECT_NUM_EQUAL(*((char*)JHashTableGetLastData(table)), expectedValue1);
	//JHashTablePrintAll(table);

	EXPECT_NUM_EQUAL(JHashTableDeleteLastData(NULL), DeleteFail);

	DeleteJHashTable(&table);
})

TEST(HashTable_CHAR, FindData, {
	int size = 10;
	char expectedKey1 = 'a';
	char expectedValue1 = 'x';
	char expectedKey2 = 'b';
	char expectedValue2 = 'y';
	JHashTablePtr table = NewJHashTable(size, CharType, CharType);

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

// ---------- Hash string Test ----------

////////////////////////////////////////////////////////////////////////////////
/// Node Test (string)
////////////////////////////////////////////////////////////////////////////////

TEST(Node_STRING, SetData, {
	JNodePtr node = NewJNode();

	char *expected = "abc";
	EXPECT_NOT_NULL(JNodeSetData(node, expected));
	EXPECT_PTR_EQUAL(node->data, expected);
	EXPECT_STR_EQUAL((char*)(node->data), expected);

	EXPECT_NULL(JNodeSetData(NULL, expected));
	EXPECT_NULL(JNodeSetData(node, NULL));
	EXPECT_NULL(JNodeSetData(NULL, NULL));

	DeleteJNode(&node);
})

TEST(Node_STRING, GetData, {
	JNodePtr node = NewJNode();

	char *expected = "abc";
	JNodeSetData(node, expected);
	EXPECT_NOT_NULL(JNodeGetData(node));
	EXPECT_STR_EQUAL((char*)JNodeGetData(node), expected);

	EXPECT_NULL(JNodeGetData(NULL));

	DeleteJNode(&node);
})

////////////////////////////////////////////////////////////////////////////////
/// LinkedList Test (string)
////////////////////////////////////////////////////////////////////////////////

TEST(LinkedList_STRING, AddNode, {
	JLinkedListPtr list = NewJLinkedList(0);
	char *expected = "abc";

	// 정상 동작 확인
	EXPECT_NOT_NULL(JLinkedListAddNode(list, expected));
	EXPECT_STR_EQUAL((char*)(list->tail->prev->data), expected);

	// 중복 허용 테스트
	EXPECT_NULL(JLinkedListAddNode(list, expected));

	// NULL 이 입력값이면, NULL 을 반환
	EXPECT_NULL(JLinkedListAddNode(NULL, expected));
	EXPECT_NULL(JLinkedListAddNode(list, NULL));
	EXPECT_NULL(JLinkedListAddNode(NULL, NULL));

	DeleteJLinkedList(&list);
})

TEST(LinkedList_STRING, GetFirstNodeData, {
	JLinkedListPtr list = NewJLinkedList(0);

	char *expected1 = "abc";
	char *expected2 = "123";
	char *expected3 = "*&$";

	JLinkedListAddNode(list, expected1);
	JLinkedListAddNode(list, expected2);
	JLinkedListAddNode(list, expected3);

	EXPECT_STR_EQUAL((char*)JLinkedListGetFirstNodeData(list), expected1);

	EXPECT_NULL(JLinkedListGetFirstNodeData(NULL));

	DeleteJLinkedList(&list);
})

TEST(LinkedList_STRING, GetLastNodeData, {
	JLinkedListPtr list = NewJLinkedList(0);

	char *expected1 = "abc";
	char *expected2 = "123";
	char *expected3 = "*&$";

	JLinkedListAddNode(list, expected1);
	JLinkedListAddNode(list, expected2);
	JLinkedListAddNode(list, expected3);

	EXPECT_STR_EQUAL((char*)JLinkedListGetLastNodeData(list), expected3);
	
	EXPECT_NULL(JLinkedListGetLastNodeData(NULL));

	DeleteJLinkedList(&list);
})

TEST(LinkedList_STRING, SetData, {
	JLinkedListPtr list = NewJLinkedList(0);
	char *expected = "abc";

	EXPECT_NOT_NULL(JLinkedListSetData(list, expected));
	EXPECT_STR_EQUAL((char*)JLinkedListGetData(list), expected);

	EXPECT_NULL(JLinkedListSetData(NULL, expected));
	EXPECT_NULL(JLinkedListSetData(list, NULL));
	EXPECT_NULL(JLinkedListSetData(NULL, NULL));

	DeleteJLinkedList(&list);
})

TEST(LinkedList_STRING, GetData, {
	JLinkedListPtr list = NewJLinkedList(0);
	char *expected = "abc";

	JLinkedListSetData(list, expected);
	EXPECT_NOT_NULL(JLinkedListGetData(list));
	EXPECT_STR_EQUAL((char*)JLinkedListGetData(list), expected);

	EXPECT_NULL(JLinkedListGetData(NULL));

	DeleteJLinkedList(&list);
})

TEST(LinkedList_STRING, DeleteNodeData, {
	JLinkedListPtr list = NewJLinkedList(0);
	char *expected1 = "abc";

	JLinkedListAddNode(list, expected1);
	EXPECT_NUM_EQUAL(JLinkedListDeleteNodeData(list, expected1), DeleteSuccess);
	EXPECT_NULL(JLinkedListGetLastNodeData(list));

	EXPECT_NUM_EQUAL(JLinkedListDeleteNodeData(NULL, expected1), DeleteFail);
	EXPECT_NUM_EQUAL(JLinkedListDeleteNodeData(list, NULL), DeleteFail);
	EXPECT_NUM_EQUAL(JLinkedListDeleteNodeData(NULL, NULL), DeleteFail);

	DeleteJLinkedList(&list);
})

TEST(LinkedList_STRING, FindNodeData, {
	JLinkedListPtr list = NewJLinkedList(0);
	char *expected1 = "abc";

	JLinkedListAddNode(list, expected1);
	EXPECT_NUM_EQUAL(JLinkedListFindNodeData(list, expected1), FindSuccess);

	EXPECT_NUM_EQUAL(JLinkedListFindNodeData(NULL, expected1), FindFail);
	EXPECT_NUM_EQUAL(JLinkedListFindNodeData(list, NULL), FindFail);
	EXPECT_NUM_EQUAL(JLinkedListFindNodeData(NULL, NULL), FindFail);

	DeleteJLinkedList(&list);
})

////////////////////////////////////////////////////////////////////////////////
/// HashTable Test (string)
////////////////////////////////////////////////////////////////////////////////

TEST(HashTable_STRING, AddData, {
	int size = 10;
	char *expectedKey1 = "abc";
	char *expectedValue1 = "123";
	JHashTablePtr table = NewJHashTable(size, StringType, StringType);
	EXPECT_NOT_NULL(JHashTableAddData(table, expectedKey1, expectedValue1));

	EXPECT_NULL(JHashTableAddData(NULL, expectedKey1, expectedValue1));
	EXPECT_NULL(JHashTableAddData(NULL, expectedKey1, NULL));
	EXPECT_NULL(JHashTableAddData(NULL, NULL, &expectedValue1));
	EXPECT_NULL(JHashTableAddData(table, NULL, NULL));
	EXPECT_NULL(JHashTableAddData(table, expectedKey1, NULL));
	EXPECT_NULL(JHashTableAddData(table, NULL, expectedValue1));
	EXPECT_NULL(JHashTableAddData(NULL, NULL, NULL));
	
	DeleteJHashTable(&table);
})

TEST(HashTable_STRING, GetFirstData, {
	int size = 10;
	char *expectedKey1 = "def";
	char *expectedValue1 = "[1$2**3]";
	char *expectedKey2 = "abc";
	char *expectedValue2 = "{4@5u6}";
	JHashTablePtr table = NewJHashTable(size, StringType, StringType);

	JHashTableAddData(table, expectedKey1, expectedValue1);
	JHashTableAddData(table, expectedKey2, expectedValue2);
	EXPECT_STR_EQUAL((char*)JHashTableGetFirstData(table), expectedValue1);

	EXPECT_NULL(JHashTableGetFirstData(NULL));

	DeleteJHashTable(&table);
})

TEST(HashTable_STRING, GetLastData, {
	int size = 10;
	char *expectedKey1 = "def";
	char *expectedValue1 = "[1$2**3]";
	char *expectedKey2 = "abc";
	char *expectedValue2 = "{4@5u6}";
	JHashTablePtr table = NewJHashTable(size, StringType, StringType);

	JHashTableAddData(table, expectedKey1, expectedValue1);
	JHashTableAddData(table, expectedKey2, expectedValue2);
	EXPECT_STR_EQUAL((char*)JHashTableGetLastData(table), expectedValue2);

	EXPECT_NULL(JHashTableGetLastData(NULL));

	DeleteJHashTable(&table);
})

TEST(HashTable_STRING, DeleteData, {
	int size = 10;
	char *expectedKey1 = "def";
	char *expectedValue1 = "[1$2**3]";
	char *expectedKey2 = "abc";
	char *expectedValue2 = "{4@5u6}";
	JHashTablePtr table = NewJHashTable(size, StringType, StringType);

	JHashTableAddData(table, expectedKey1, expectedValue1);
	JHashTableAddData(table, expectedKey2, expectedValue2);
	//JHashTablePrintAll(table);

	EXPECT_NUM_EQUAL(JHashTableDeleteData(table, expectedKey2, expectedValue2), DeleteSuccess);
	EXPECT_STR_EQUAL((char*)JHashTableGetLastData(table), expectedValue1);
	//JHashTablePrintAll(table);

	EXPECT_NUM_EQUAL(JHashTableDeleteData(NULL, expectedKey1, expectedValue1), DeleteFail);
	EXPECT_NUM_EQUAL(JHashTableDeleteData(NULL, expectedKey1, NULL), DeleteFail);
	EXPECT_NUM_EQUAL(JHashTableDeleteData(NULL, NULL, expectedValue1), DeleteFail);
	EXPECT_NUM_EQUAL(JHashTableDeleteData(table, NULL, NULL), DeleteFail);
	EXPECT_NUM_EQUAL(JHashTableDeleteData(table, expectedKey1, NULL), DeleteFail);
	EXPECT_NUM_EQUAL(JHashTableDeleteData(table, NULL, expectedValue1), DeleteFail);
	EXPECT_NUM_EQUAL(JHashTableDeleteData(NULL, NULL, NULL), DeleteFail);

	DeleteJHashTable(&table);
})

TEST(HashTable_STRING, DeleteFirstData, {
	int size = 10;
	char *expectedKey1 = "def";
	char *expectedValue1 = "[1$2**3]";
	char *expectedKey2 = "abc";
	char *expectedValue2 = "{4@5u6}";
	JHashTablePtr table = NewJHashTable(size, StringType, StringType);

	JHashTableAddData(table, expectedKey1, expectedValue1);
	JHashTableAddData(table, expectedKey2, expectedValue2);
	//JHashTablePrintAll(table);

	EXPECT_NUM_EQUAL(JHashTableDeleteFirstData(table), DeleteSuccess);
	EXPECT_STR_EQUAL((char*)JHashTableGetFirstData(table), expectedValue2);
	//JHashTablePrintAll(table);

	EXPECT_NUM_EQUAL(JHashTableDeleteFirstData(NULL), DeleteFail);

	DeleteJHashTable(&table);
})

TEST(HashTable_STRING, DeleteLastData, {
	int size = 10;
	char *expectedKey1 = "def";
	char *expectedValue1 = "[1$2**3]";
	char *expectedKey2 = "abc";
	char *expectedValue2 = "{4@5u6}";
	JHashTablePtr table = NewJHashTable(size, StringType, StringType);

	JHashTableAddData(table, expectedKey1, expectedValue1);
	JHashTableAddData(table, expectedKey2, expectedValue2);
	JHashTablePrintAll(table);

	EXPECT_NUM_EQUAL(JHashTableDeleteLastData(table), DeleteSuccess);
	EXPECT_STR_EQUAL((char*)JHashTableGetLastData(table), expectedValue1);
	JHashTablePrintAll(table);

	EXPECT_NUM_EQUAL(JHashTableDeleteLastData(NULL), DeleteFail);

	DeleteJHashTable(&table);
})

TEST(HashTable_STRING, FindData, {
	int size = 10;
	char *expectedKey1 = "def";
	char *expectedValue1 = "[1$2**3]";
	char *expectedKey2 = "abc";
	char *expectedValue2 = "{4@5u6}";
	JHashTablePtr table = NewJHashTable(size, StringType, StringType);

	JHashTableAddData(table, expectedKey1, expectedValue1);
	JHashTableAddData(table, expectedKey2, expectedValue2);
	//JHashTablePrintAll(table);

	EXPECT_NUM_EQUAL(JHashTableFindData(table, expectedKey1, expectedValue1), FindSuccess);
	EXPECT_NUM_EQUAL(JHashTableFindData(table, expectedKey2, expectedValue2), FindSuccess);

	EXPECT_NUM_EQUAL(JHashTableFindData(NULL, expectedKey1, expectedValue1), FindFail);
	EXPECT_NUM_EQUAL(JHashTableFindData(NULL, expectedKey1, NULL), FindFail);
	EXPECT_NUM_EQUAL(JHashTableFindData(NULL, NULL, expectedValue1), FindFail);
	EXPECT_NUM_EQUAL(JHashTableFindData(table, NULL, NULL), FindFail);
	EXPECT_NUM_EQUAL(JHashTableFindData(table, expectedKey1, NULL), FindFail);
	EXPECT_NUM_EQUAL(JHashTableFindData(table, NULL, expectedValue1), FindFail);
	EXPECT_NUM_EQUAL(JHashTableFindData(NULL, NULL, NULL), FindFail);

	DeleteJHashTable(&table);
})

// ---------- Hash int & char Test ----------

////////////////////////////////////////////////////////////////////////////////
/// HashTable Test (int & char)
////////////////////////////////////////////////////////////////////////////////

TEST(HashTable_INT_CHAR, AddData, {
	int size = 10;
	int expectedKey1 = 5;
	char expectedValue1 = 'd';
	JHashTablePtr table = NewJHashTable(size, IntType, CharType);
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

TEST(HashTable_INT_CHAR, GetFirstData, {
	int size = 10;
	int expectedKey1 = 5;
	char expectedValue1 = 'x';
	int expectedKey2 = 6;
	char expectedValue2 = 'y';
	JHashTablePtr table = NewJHashTable(size, IntType, CharType);

	JHashTableAddData(table, &expectedKey1, &expectedValue1);
	JHashTableAddData(table, &expectedKey2, &expectedValue2);
	EXPECT_NUM_EQUAL(*((char*)JHashTableGetFirstData(table)), expectedValue1);

	EXPECT_NULL(JHashTableGetFirstData(NULL));

	DeleteJHashTable(&table);
})

TEST(HashTable_INT_CHAR, GetLastData, {
	int size = 10;
	int expectedKey1 = 5;
	char expectedValue1 = 'x';
	int expectedKey2 = 6;
	char expectedValue2 = 'y';
	JHashTablePtr table = NewJHashTable(size, IntType, CharType);

	JHashTableAddData(table, &expectedKey1, &expectedValue1);
	JHashTableAddData(table, &expectedKey2, &expectedValue2);
	EXPECT_NUM_EQUAL(*((char*)JHashTableGetLastData(table)), expectedValue2);

	EXPECT_NULL(JHashTableGetLastData(NULL));

	DeleteJHashTable(&table);
})

TEST(HashTable_INT_CHAR, DeleteData, {
	int size = 10;
	int expectedKey1 = 5;
	char expectedValue1 = 'x';
	int expectedKey2 = 6;
	char expectedValue2 = 'y';
	JHashTablePtr table = NewJHashTable(size, IntType, CharType);

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

TEST(HashTable_INT_CHAR, DeleteFirstData, {
	int size = 10;
	int expectedKey1 = 5;
	char expectedValue1 = 'x';
	int expectedKey2 = 6;
	char expectedValue2 = 'y';
	JHashTablePtr table = NewJHashTable(size, IntType, CharType);

	JHashTableAddData(table, &expectedKey1, &expectedValue1);
	JHashTableAddData(table, &expectedKey2, &expectedValue2);
	//JHashTablePrintAll(table);

	EXPECT_NUM_EQUAL(JHashTableDeleteFirstData(table), DeleteSuccess);
	EXPECT_NUM_EQUAL(*((char*)JHashTableGetFirstData(table)), expectedValue2);
	//JHashTablePrintAll(table);

	EXPECT_NUM_EQUAL(JHashTableDeleteFirstData(NULL), DeleteFail);

	DeleteJHashTable(&table);
})

TEST(HashTable_INT_CHAR, DeleteLastData, {
	int size = 10;
	int expectedKey1 = 5;
	char expectedValue1 = 'x';
	int expectedKey2 = 6;
	char expectedValue2 = 'y';
	JHashTablePtr table = NewJHashTable(size, IntType, CharType);

	JHashTableAddData(table, &expectedKey1, &expectedValue1);
	JHashTableAddData(table, &expectedKey2, &expectedValue2);
	//JHashTablePrintAll(table);

	EXPECT_NUM_EQUAL(JHashTableDeleteLastData(table), DeleteSuccess);
	EXPECT_NUM_EQUAL(*((char*)JHashTableGetLastData(table)), expectedValue1);
	//JHashTablePrintAll(table);

	EXPECT_NUM_EQUAL(JHashTableDeleteLastData(NULL), DeleteFail);

	DeleteJHashTable(&table);
})

TEST(HashTable_INT_CHAR, FindData, {
	int size = 10;
	int expectedKey1 = 5;
	char expectedValue1 = 'x';
	int expectedKey2 = 6;
	char expectedValue2 = 'y';
	JHashTablePtr table = NewJHashTable(size, IntType, CharType);

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
/// HashTable Test (char & int)
////////////////////////////////////////////////////////////////////////////////

TEST(HashTable_CHAR_INT, AddData, {
	int size = 10;
	char expectedKey1 = 'a';
	int expectedValue1 = 5;
	JHashTablePtr table = NewJHashTable(size, CharType, IntType);
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

TEST(HashTable_CHAR_INT, GetFirstData, {
	int size = 10;
	char expectedKey1 = 'a';
	int expectedValue1 = 5;
	char expectedKey2 = 'b';
	int expectedValue2 = 6;
	JHashTablePtr table = NewJHashTable(size, CharType, IntType);

	JHashTableAddData(table, &expectedKey1, &expectedValue1);
	JHashTableAddData(table, &expectedKey2, &expectedValue2);
	EXPECT_NUM_EQUAL(*((int*)JHashTableGetFirstData(table)), expectedValue1);

	EXPECT_NULL(JHashTableGetFirstData(NULL));

	DeleteJHashTable(&table);
})

TEST(HashTable_CHAR_INT, GetLastData, {
	int size = 10;
	char expectedKey1 = 'a';
	int expectedValue1 = 5;
	char expectedKey2 = 'b';
	int expectedValue2 = 6;
	JHashTablePtr table = NewJHashTable(size, CharType, IntType);

	JHashTableAddData(table, &expectedKey1, &expectedValue1);
	JHashTableAddData(table, &expectedKey2, &expectedValue2);
	EXPECT_NUM_EQUAL(*((int*)JHashTableGetLastData(table)), expectedValue2);

	EXPECT_NULL(JHashTableGetLastData(NULL));

	DeleteJHashTable(&table);
})

TEST(HashTable_CHAR_INT, DeleteData, {
	int size = 10;
	char expectedKey1 = 'a';
	int expectedValue1 = 5;
	char expectedKey2 = 'b';
	int expectedValue2 = 6;
	JHashTablePtr table = NewJHashTable(size, CharType, IntType);

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

TEST(HashTable_CHAR_INT, DeleteFirstData, {
	int size = 10;
	char expectedKey1 = 'a';
	int expectedValue1 = 5;
	char expectedKey2 = 'b';
	int expectedValue2 = 6;
	JHashTablePtr table = NewJHashTable(size, CharType, IntType);

	JHashTableAddData(table, &expectedKey1, &expectedValue1);
	JHashTableAddData(table, &expectedKey2, &expectedValue2);
	JHashTablePrintAll(table);

	EXPECT_NUM_EQUAL(JHashTableDeleteFirstData(table), DeleteSuccess);
	EXPECT_NUM_EQUAL(*((int*)JHashTableGetFirstData(table)), expectedValue2);
	JHashTablePrintAll(table);

	EXPECT_NUM_EQUAL(JHashTableDeleteFirstData(NULL), DeleteFail);

	DeleteJHashTable(&table);
})

TEST(HashTable_CHAR_INT, DeleteLastData, {
	int size = 10;
	char expectedKey1 = 'a';
	int expectedValue1 = 5;
	char expectedKey2 = 'b';
	int expectedValue2 = 6;
	JHashTablePtr table = NewJHashTable(size, CharType, IntType);

	JHashTableAddData(table, &expectedKey1, &expectedValue1);
	JHashTableAddData(table, &expectedKey2, &expectedValue2);
	//JHashTablePrintAll(table);

	EXPECT_NUM_EQUAL(JHashTableDeleteLastData(table), DeleteSuccess);
	EXPECT_NUM_EQUAL(*((int*)JHashTableGetLastData(table)), expectedValue1);
	//JHashTablePrintAll(table);

	EXPECT_NUM_EQUAL(JHashTableDeleteLastData(NULL), DeleteFail);

	DeleteJHashTable(&table);
})

TEST(HashTable_CHAR_INT, FindData, {
	int size = 10;
	char expectedKey1 = 'a';
	int expectedValue1 = 5;
	char expectedKey2 = 'b';
	int expectedValue2 = 6;
	JHashTablePtr table = NewJHashTable(size, CharType, IntType);

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

// ---------- Hash int & string Test ----------

////////////////////////////////////////////////////////////////////////////////
/// HashTable Test (int & string)
////////////////////////////////////////////////////////////////////////////////

TEST(HashTable_INT_STRING, AddData, {
	int size = 10;
	int expectedKey1 = 5;
	char *expectedValue1 = "abc";
	JHashTablePtr table = NewJHashTable(size, IntType, StringType);
	EXPECT_NOT_NULL(JHashTableAddData(table, &expectedKey1, expectedValue1));

	EXPECT_NULL(JHashTableAddData(NULL, &expectedKey1, expectedValue1));
	EXPECT_NULL(JHashTableAddData(NULL, &expectedKey1, NULL));
	EXPECT_NULL(JHashTableAddData(NULL, NULL, expectedValue1));
	EXPECT_NULL(JHashTableAddData(table, NULL, NULL));
	EXPECT_NULL(JHashTableAddData(table, &expectedKey1, NULL));
	EXPECT_NULL(JHashTableAddData(table, NULL, expectedValue1));
	EXPECT_NULL(JHashTableAddData(NULL, NULL, NULL));
	
	DeleteJHashTable(&table);
})

TEST(HashTable_INT_STRING, GetFirstData, {
	int size = 10;
	int expectedKey1 = 5;
	char *expectedValue1 = "abc";
	int expectedKey2 = 6;
	char *expectedValue2 = "1e4h";
	JHashTablePtr table = NewJHashTable(size, IntType, StringType);

	JHashTableAddData(table, &expectedKey1, expectedValue1);
	JHashTableAddData(table, &expectedKey2, expectedValue2);
	EXPECT_STR_EQUAL((char*)JHashTableGetFirstData(table), expectedValue1);

	EXPECT_NULL(JHashTableGetFirstData(NULL));

	DeleteJHashTable(&table);
})

TEST(HashTable_INT_STRING, GetLastData, {
	int size = 10;
	int expectedKey1 = 5;
	char *expectedValue1 = "abc";
	int expectedKey2 = 6;
	char *expectedValue2 = "1e4h";
	JHashTablePtr table = NewJHashTable(size, IntType, StringType);

	JHashTableAddData(table, &expectedKey1, expectedValue1);
	JHashTableAddData(table, &expectedKey2, expectedValue2);
	EXPECT_STR_EQUAL((char*)JHashTableGetLastData(table), expectedValue2);

	EXPECT_NULL(JHashTableGetLastData(NULL));

	DeleteJHashTable(&table);
})

TEST(HashTable_INT_STRING, DeleteData, {
	int size = 10;
	int expectedKey1 = 5;
	char *expectedValue1 = "abc";
	int expectedKey2 = 6;
	char *expectedValue2 = "1e4h";
	JHashTablePtr table = NewJHashTable(size, IntType, StringType);

	JHashTableAddData(table, &expectedKey1, expectedValue1);
	JHashTableAddData(table, &expectedKey2, expectedValue2);
	//JHashTablePrintAll(table);

	EXPECT_NUM_EQUAL(JHashTableDeleteData(table, &expectedKey2, expectedValue2), DeleteSuccess);
	EXPECT_STR_EQUAL((char*)JHashTableGetLastData(table), expectedValue1);
	//JHashTablePrintAll(table);

	EXPECT_NUM_EQUAL(JHashTableDeleteData(NULL, &expectedKey1, expectedValue1), DeleteFail);
	EXPECT_NUM_EQUAL(JHashTableDeleteData(NULL, &expectedKey1, NULL), DeleteFail);
	EXPECT_NUM_EQUAL(JHashTableDeleteData(NULL, NULL, expectedValue1), DeleteFail);
	EXPECT_NUM_EQUAL(JHashTableDeleteData(table, NULL, NULL), DeleteFail);
	EXPECT_NUM_EQUAL(JHashTableDeleteData(table, &expectedKey1, NULL), DeleteFail);
	EXPECT_NUM_EQUAL(JHashTableDeleteData(table, NULL, expectedValue1), DeleteFail);
	EXPECT_NUM_EQUAL(JHashTableDeleteData(NULL, NULL, NULL), DeleteFail);

	DeleteJHashTable(&table);
})

TEST(HashTable_INT_STRING, DeleteFirstData, {
	int size = 10;
	int expectedKey1 = 5;
	char *expectedValue1 = "abc";
	int expectedKey2 = 6;
	char *expectedValue2 = "1e4h";
	JHashTablePtr table = NewJHashTable(size, IntType, StringType);

	JHashTableAddData(table, &expectedKey1, expectedValue1);
	JHashTableAddData(table, &expectedKey2, expectedValue2);
	//JHashTablePrintAll(table);

	EXPECT_NUM_EQUAL(JHashTableDeleteFirstData(table), DeleteSuccess);
	EXPECT_STR_EQUAL((char*)JHashTableGetFirstData(table), expectedValue2);
	//JHashTablePrintAll(table);

	EXPECT_NUM_EQUAL(JHashTableDeleteFirstData(NULL), DeleteFail);

	DeleteJHashTable(&table);
})

TEST(HashTable_INT_STRING, DeleteLastData, {
	int size = 10;
	int expectedKey1 = 5;
	char *expectedValue1 = "abc";
	int expectedKey2 = 6;
	char *expectedValue2 = "1e4h";
	JHashTablePtr table = NewJHashTable(size, IntType, StringType);

	JHashTableAddData(table, &expectedKey1, expectedValue1);
	JHashTableAddData(table, &expectedKey2, expectedValue2);
	//JHashTablePrintAll(table);

	EXPECT_NUM_EQUAL(JHashTableDeleteLastData(table), DeleteSuccess);
	EXPECT_STR_EQUAL((char*)JHashTableGetLastData(table), expectedValue1);
	//JHashTablePrintAll(table);

	EXPECT_NUM_EQUAL(JHashTableDeleteLastData(NULL), DeleteFail);

	DeleteJHashTable(&table);
})

TEST(HashTable_INT_STRING, FindData, {
	int size = 10;
	int expectedKey1 = 5;
	char *expectedValue1 = "abc";
	int expectedKey2 = 6;
	char *expectedValue2 = "1e4h";
	JHashTablePtr table = NewJHashTable(size, IntType, StringType);

	JHashTableAddData(table, &expectedKey1, expectedValue1);
	JHashTableAddData(table, &expectedKey2, expectedValue2);
	//JHashTablePrintAll(table);

	EXPECT_NUM_EQUAL(JHashTableFindData(table, &expectedKey1, expectedValue1), FindSuccess);
	EXPECT_NUM_EQUAL(JHashTableFindData(table, &expectedKey2, expectedValue2), FindSuccess);

	EXPECT_NUM_EQUAL(JHashTableFindData(NULL, &expectedKey1, expectedValue1), FindFail);
	EXPECT_NUM_EQUAL(JHashTableFindData(NULL, &expectedKey1, NULL), FindFail);
	EXPECT_NUM_EQUAL(JHashTableFindData(NULL, NULL, expectedValue1), FindFail);
	EXPECT_NUM_EQUAL(JHashTableFindData(table, NULL, NULL), FindFail);
	EXPECT_NUM_EQUAL(JHashTableFindData(table, &expectedKey1, NULL), FindFail);
	EXPECT_NUM_EQUAL(JHashTableFindData(table, NULL, expectedValue1), FindFail);
	EXPECT_NUM_EQUAL(JHashTableFindData(NULL, NULL, NULL), FindFail);

	DeleteJHashTable(&table);
})

////////////////////////////////////////////////////////////////////////////////
/// HashTable Test (string & int)
////////////////////////////////////////////////////////////////////////////////

TEST(HashTable_STRING_INT, AddData, {
	int size = 10;
	char *expectedKey1 = "abc";
	int expectedValue1 = 5;
	JHashTablePtr table = NewJHashTable(size, StringType, IntType);
	EXPECT_NOT_NULL(JHashTableAddData(table, expectedKey1, &expectedValue1));

	EXPECT_NULL(JHashTableAddData(NULL, expectedKey1, &expectedValue1));
	EXPECT_NULL(JHashTableAddData(NULL, expectedKey1, NULL));
	EXPECT_NULL(JHashTableAddData(NULL, NULL, &expectedValue1));
	EXPECT_NULL(JHashTableAddData(table, NULL, NULL));
	EXPECT_NULL(JHashTableAddData(table, expectedKey1, NULL));
	EXPECT_NULL(JHashTableAddData(table, NULL, &expectedValue1));
	EXPECT_NULL(JHashTableAddData(NULL, NULL, NULL));
	
	DeleteJHashTable(&table);
})

TEST(HashTable_STRING_INT, GetFirstData, {
	int size = 10;
	char *expectedKey1 = "def";
	int expectedValue1 = 5;
	char *expectedKey2 = "abc";
	int expectedValue2 = 6;
	JHashTablePtr table = NewJHashTable(size, StringType, IntType);

	JHashTableAddData(table, expectedKey1, &expectedValue1);
	JHashTableAddData(table, expectedKey2, &expectedValue2);
	EXPECT_NUM_EQUAL(*((int*)JHashTableGetFirstData(table)), expectedValue1);

	EXPECT_NULL(JHashTableGetFirstData(NULL));

	DeleteJHashTable(&table);
})

TEST(HashTable_STRING_INT, GetLastData, {
	int size = 10;
	char *expectedKey1 = "def";
	int expectedValue1 = 5;
	char *expectedKey2 = "abc";
	int expectedValue2 = 6;
	JHashTablePtr table = NewJHashTable(size, StringType, IntType);

	JHashTableAddData(table, expectedKey1, &expectedValue1);
	JHashTableAddData(table, expectedKey2, &expectedValue2);
	EXPECT_NUM_EQUAL(*((int*)JHashTableGetLastData(table)), expectedValue2);

	EXPECT_NULL(JHashTableGetLastData(NULL));

	DeleteJHashTable(&table);
})

TEST(HashTable_STRING_INT, DeleteData, {
	int size = 10;
	char *expectedKey1 = "def";
	int expectedValue1 = 5;
	char *expectedKey2 = "abc";
	int expectedValue2 = 6;
	JHashTablePtr table = NewJHashTable(size, StringType, IntType);

	JHashTableAddData(table, expectedKey1, &expectedValue1);
	JHashTableAddData(table, expectedKey2, &expectedValue2);
	//JHashTablePrintAll(table);

	EXPECT_NUM_EQUAL(JHashTableDeleteData(table, expectedKey2, &expectedValue2), DeleteSuccess);
	EXPECT_NUM_EQUAL(*((int*)JHashTableGetLastData(table)), expectedValue1);
	//JHashTablePrintAll(table);

	EXPECT_NUM_EQUAL(JHashTableDeleteData(NULL, expectedKey1, &expectedValue1), DeleteFail);
	EXPECT_NUM_EQUAL(JHashTableDeleteData(NULL, expectedKey1, NULL), DeleteFail);
	EXPECT_NUM_EQUAL(JHashTableDeleteData(NULL, NULL, &expectedValue1), DeleteFail);
	EXPECT_NUM_EQUAL(JHashTableDeleteData(table, NULL, NULL), DeleteFail);
	EXPECT_NUM_EQUAL(JHashTableDeleteData(table, expectedKey1, NULL), DeleteFail);
	EXPECT_NUM_EQUAL(JHashTableDeleteData(table, NULL, &expectedValue1), DeleteFail);
	EXPECT_NUM_EQUAL(JHashTableDeleteData(NULL, NULL, NULL), DeleteFail);

	DeleteJHashTable(&table);
})

TEST(HashTable_STRING_INT, DeleteFirstData, {
	int size = 10;
	char *expectedKey1 = "def";
	int expectedValue1 = 5;
	char *expectedKey2 = "abc";
	int expectedValue2 = 6;
	JHashTablePtr table = NewJHashTable(size, StringType, IntType);

	JHashTableAddData(table, expectedKey1, &expectedValue1);
	JHashTableAddData(table, expectedKey2, &expectedValue2);
	JHashTablePrintAll(table);

	EXPECT_NUM_EQUAL(JHashTableDeleteFirstData(table), DeleteSuccess);
	EXPECT_NUM_EQUAL(*((int*)JHashTableGetFirstData(table)), expectedValue2);
	JHashTablePrintAll(table);

	EXPECT_NUM_EQUAL(JHashTableDeleteFirstData(NULL), DeleteFail);

	DeleteJHashTable(&table);
})

TEST(HashTable_STRING_INT, DeleteLastData, {
	int size = 10;
	char *expectedKey1 = "def";
	int expectedValue1 = 5;
	char *expectedKey2 = "abc";
	int expectedValue2 = 6;
	JHashTablePtr table = NewJHashTable(size, StringType, IntType);

	JHashTableAddData(table, expectedKey1, &expectedValue1);
	JHashTableAddData(table, expectedKey2, &expectedValue2);
	//JHashTablePrintAll(table);

	EXPECT_NUM_EQUAL(JHashTableDeleteLastData(table), DeleteSuccess);
	EXPECT_NUM_EQUAL(*((int*)JHashTableGetLastData(table)), expectedValue1);
	//JHashTablePrintAll(table);

	EXPECT_NUM_EQUAL(JHashTableDeleteLastData(NULL), DeleteFail);

	DeleteJHashTable(&table);
})

TEST(HashTable_STRING_INT, FindData, {
	int size = 10;
	char *expectedKey1 = "def";
	int expectedValue1 = 5;
	char *expectedKey2 = "abc";
	int expectedValue2 = 6;
	JHashTablePtr table = NewJHashTable(size, StringType, IntType);

	JHashTableAddData(table, expectedKey1, &expectedValue1);
	JHashTableAddData(table, expectedKey2, &expectedValue2);
	//JHashTablePrintAll(table);

	EXPECT_NUM_EQUAL(JHashTableFindData(table, expectedKey1, &expectedValue1), FindSuccess);
	EXPECT_NUM_EQUAL(JHashTableFindData(table, expectedKey2, &expectedValue2), FindSuccess);

	EXPECT_NUM_EQUAL(JHashTableFindData(NULL, expectedKey1, &expectedValue1), FindFail);
	EXPECT_NUM_EQUAL(JHashTableFindData(NULL, expectedKey1, NULL), FindFail);
	EXPECT_NUM_EQUAL(JHashTableFindData(NULL, NULL, &expectedValue1), FindFail);
	EXPECT_NUM_EQUAL(JHashTableFindData(table, NULL, NULL), FindFail);
	EXPECT_NUM_EQUAL(JHashTableFindData(table, expectedKey1, NULL), FindFail);
	EXPECT_NUM_EQUAL(JHashTableFindData(table, NULL, &expectedValue1), FindFail);
	EXPECT_NUM_EQUAL(JHashTableFindData(NULL, NULL, NULL), FindFail);

	DeleteJHashTable(&table);
})

// ---------- Hash char & string Test ----------

////////////////////////////////////////////////////////////////////////////////
/// HashTable Test (char & string)
////////////////////////////////////////////////////////////////////////////////

TEST(HashTable_CHAR_STRING, AddData, {
	int size = 10;
	char expectedKey1 = 'a';
	char *expectedValue1 = "abc";
	JHashTablePtr table = NewJHashTable(size, CharType, StringType);
	EXPECT_NOT_NULL(JHashTableAddData(table, &expectedKey1, expectedValue1));

	EXPECT_NULL(JHashTableAddData(NULL, &expectedKey1, expectedValue1));
	EXPECT_NULL(JHashTableAddData(NULL, &expectedKey1, NULL));
	EXPECT_NULL(JHashTableAddData(NULL, NULL, expectedValue1));
	EXPECT_NULL(JHashTableAddData(table, NULL, NULL));
	EXPECT_NULL(JHashTableAddData(table, &expectedKey1, NULL));
	EXPECT_NULL(JHashTableAddData(table, NULL, expectedValue1));
	EXPECT_NULL(JHashTableAddData(NULL, NULL, NULL));
	
	DeleteJHashTable(&table);
})

TEST(HashTable_CHAR_STRING, GetFirstData, {
	int size = 10;
	char expectedKey1 = 'a';
	char* expectedValue1 = "abc";
	char expectedKey2 = 'b';
	char* expectedValue2 = "def";
	JHashTablePtr table = NewJHashTable(size, CharType, StringType);

	JHashTableAddData(table, &expectedKey1, expectedValue1);
	JHashTableAddData(table, &expectedKey2, expectedValue2);
	EXPECT_STR_EQUAL((char*)JHashTableGetFirstData(table), expectedValue1);

	EXPECT_NULL(JHashTableGetFirstData(NULL));

	DeleteJHashTable(&table);
})

TEST(HashTable_CHAR_STRING, GetLastData, {
	int size = 10;
	char expectedKey1 = 'a';
	char* expectedValue1 = "abc";
	char expectedKey2 = 'b';
	char* expectedValue2 = "def";
	JHashTablePtr table = NewJHashTable(size, CharType, StringType);

	JHashTableAddData(table, &expectedKey1, expectedValue1);
	JHashTableAddData(table, &expectedKey2, expectedValue2);
	EXPECT_STR_EQUAL((char*)JHashTableGetLastData(table), expectedValue2);

	EXPECT_NULL(JHashTableGetLastData(NULL));

	DeleteJHashTable(&table);
})

TEST(HashTable_CHAR_STRING, DeleteData, {
	int size = 10;
	char expectedKey1 = 'a';
	char* expectedValue1 = "abc";
	char expectedKey2 = 'b';
	char* expectedValue2 = "def";
	JHashTablePtr table = NewJHashTable(size, CharType, StringType);

	JHashTableAddData(table, &expectedKey1, expectedValue1);
	JHashTableAddData(table, &expectedKey2, expectedValue2);
	//JHashTablePrintAll(table);

	EXPECT_NUM_EQUAL(JHashTableDeleteData(table, &expectedKey2, expectedValue2), DeleteSuccess);
	EXPECT_STR_EQUAL((char*)JHashTableGetLastData(table), expectedValue1);
	//JHashTablePrintAll(table);

	EXPECT_NUM_EQUAL(JHashTableDeleteData(NULL, &expectedKey1, expectedValue1), DeleteFail);
	EXPECT_NUM_EQUAL(JHashTableDeleteData(NULL, &expectedKey1, NULL), DeleteFail);
	EXPECT_NUM_EQUAL(JHashTableDeleteData(NULL, NULL, expectedValue1), DeleteFail);
	EXPECT_NUM_EQUAL(JHashTableDeleteData(table, NULL, NULL), DeleteFail);
	EXPECT_NUM_EQUAL(JHashTableDeleteData(table, &expectedKey1, NULL), DeleteFail);
	EXPECT_NUM_EQUAL(JHashTableDeleteData(table, NULL, expectedValue1), DeleteFail);
	EXPECT_NUM_EQUAL(JHashTableDeleteData(NULL, NULL, NULL), DeleteFail);

	DeleteJHashTable(&table);
})

TEST(HashTable_CHAR_STRING, DeleteFirstData, {
	int size = 10;
	char expectedKey1 = 'a';
	char* expectedValue1_1 = "abc";
	char* expectedValue1_2 = "bbb";
	char* expectedValue1_3 = "ccc";
	char expectedKey2 = 'b';
	char* expectedValue2 = "def";
	JHashTablePtr table = NewJHashTable(size, CharType, StringType);

	JHashTableAddData(table, &expectedKey1, expectedValue1_1);
	JHashTableAddData(table, &expectedKey1, expectedValue1_2);
	JHashTableAddData(table, &expectedKey1, expectedValue1_3);
	JHashTableAddData(table, &expectedKey2, expectedValue2);
	JHashTablePrintAll(table);

	EXPECT_NUM_EQUAL(JHashTableDeleteFirstData(table), DeleteSuccess);
	EXPECT_STR_EQUAL((char*)JHashTableGetFirstData(table), expectedValue1_2);
	JHashTablePrintAll(table);

	EXPECT_NUM_EQUAL(JHashTableDeleteFirstData(NULL), DeleteFail);

	DeleteJHashTable(&table);
})

TEST(HashTable_CHAR_STRING, DeleteLastData, {
	int size = 10;
	char expectedKey1 = 'a';
	char* expectedValue1 = "abc";
	char expectedKey2 = 'b';
	char* expectedValue2_1 = "def";
	char* expectedValue2_2 = "ghi";
	char* expectedValue2_3 = "jkl";
	JHashTablePtr table = NewJHashTable(size, CharType, StringType);

	JHashTableAddData(table, &expectedKey1, expectedValue1);
	JHashTableAddData(table, &expectedKey2, expectedValue2_1);
	JHashTableAddData(table, &expectedKey2, expectedValue2_2);
	JHashTableAddData(table, &expectedKey2, expectedValue2_3);
	JHashTablePrintAll(table);

	EXPECT_NUM_EQUAL(JHashTableDeleteLastData(table), DeleteSuccess);
	EXPECT_STR_EQUAL((char*)JHashTableGetLastData(table), expectedValue2_2);
	JHashTablePrintAll(table);

	EXPECT_NUM_EQUAL(JHashTableDeleteLastData(NULL), DeleteFail);

	DeleteJHashTable(&table);
})

TEST(HashTable_CHAR_STRING, FindData, {
	int size = 10;
	char expectedKey1 = 'a';
	char* expectedValue1 = "abc";
	char expectedKey2 = 'b';
	char* expectedValue2 = "def";
	JHashTablePtr table = NewJHashTable(size, CharType, StringType);

	JHashTableAddData(table, &expectedKey1, expectedValue1);
	JHashTableAddData(table, &expectedKey2, expectedValue2);
	//JHashTablePrintAll(table);

	EXPECT_NUM_EQUAL(JHashTableFindData(table, &expectedKey1, expectedValue1), FindSuccess);
	EXPECT_NUM_EQUAL(JHashTableFindData(table, &expectedKey2, expectedValue2), FindSuccess);

	EXPECT_NUM_EQUAL(JHashTableFindData(NULL, &expectedKey1, expectedValue1), FindFail);
	EXPECT_NUM_EQUAL(JHashTableFindData(NULL, &expectedKey1, NULL), FindFail);
	EXPECT_NUM_EQUAL(JHashTableFindData(NULL, NULL, expectedValue1), FindFail);
	EXPECT_NUM_EQUAL(JHashTableFindData(table, NULL, NULL), FindFail);
	EXPECT_NUM_EQUAL(JHashTableFindData(table, &expectedKey1, NULL), FindFail);
	EXPECT_NUM_EQUAL(JHashTableFindData(table, NULL, expectedValue1), FindFail);
	EXPECT_NUM_EQUAL(JHashTableFindData(NULL, NULL, NULL), FindFail);

	DeleteJHashTable(&table);
})

////////////////////////////////////////////////////////////////////////////////
/// HashTable Test (string & char)
////////////////////////////////////////////////////////////////////////////////

TEST(HashTable_STRING_CHAR, AddData, {
	int size = 10;
	char* expectedKey1 = "abc";
	char expectedValue1 = 'd';
	JHashTablePtr table = NewJHashTable(size, StringType, CharType);
	EXPECT_NOT_NULL(JHashTableAddData(table, expectedKey1, &expectedValue1));

	EXPECT_NULL(JHashTableAddData(NULL, expectedKey1, &expectedValue1));
	EXPECT_NULL(JHashTableAddData(NULL, expectedKey1, NULL));
	EXPECT_NULL(JHashTableAddData(NULL, NULL, &expectedValue1));
	EXPECT_NULL(JHashTableAddData(table, NULL, NULL));
	EXPECT_NULL(JHashTableAddData(table, expectedKey1, NULL));
	EXPECT_NULL(JHashTableAddData(table, NULL, &expectedValue1));
	EXPECT_NULL(JHashTableAddData(NULL, NULL, NULL));
	
	DeleteJHashTable(&table);
})

TEST(HashTable_STRING_CHAR, GetFirstData, {
	int size = 10;
	char *expectedKey1 = "def";
	char expectedValue1 = 'x';
	char *expectedKey2 = "abc";
	char expectedValue2 = 'y';
	JHashTablePtr table = NewJHashTable(size, StringType, CharType);

	JHashTableAddData(table, expectedKey1, &expectedValue1);
	JHashTableAddData(table, expectedKey2, &expectedValue2);
	EXPECT_NUM_EQUAL(*((char*)JHashTableGetFirstData(table)), expectedValue1);

	EXPECT_NULL(JHashTableGetFirstData(NULL));

	DeleteJHashTable(&table);
})

TEST(HashTable_STRING_CHAR, GetLastData, {
	int size = 10;
	char *expectedKey1 = "def";
	char expectedValue1 = 'x';
	char *expectedKey2 = "abc";
	char expectedValue2 = 'y';
	JHashTablePtr table = NewJHashTable(size, StringType, CharType);

	JHashTableAddData(table, expectedKey1, &expectedValue1);
	JHashTableAddData(table, expectedKey2, &expectedValue2);
	EXPECT_NUM_EQUAL(*((char*)JHashTableGetLastData(table)), expectedValue2);

	EXPECT_NULL(JHashTableGetLastData(NULL));

	DeleteJHashTable(&table);
})

TEST(HashTable_STRING_CHAR, DeleteData, {
	int size = 10;
	char *expectedKey1 = "def";
	char expectedValue1 = 'x';
	char *expectedKey2 = "abc";
	char expectedValue2 = 'y';
	JHashTablePtr table = NewJHashTable(size, StringType, CharType);

	JHashTableAddData(table, expectedKey1, &expectedValue1);
	JHashTableAddData(table, expectedKey2, &expectedValue2);
	//JHashTablePrintAll(table);

	EXPECT_NUM_EQUAL(JHashTableDeleteData(table, expectedKey2, &expectedValue2), DeleteSuccess);
	EXPECT_NUM_EQUAL(*((char*)JHashTableGetLastData(table)), expectedValue1);
	//JHashTablePrintAll(table);

	EXPECT_NUM_EQUAL(JHashTableDeleteData(NULL, expectedKey1, &expectedValue1), DeleteFail);
	EXPECT_NUM_EQUAL(JHashTableDeleteData(NULL, expectedKey1, NULL), DeleteFail);
	EXPECT_NUM_EQUAL(JHashTableDeleteData(NULL, NULL, &expectedValue1), DeleteFail);
	EXPECT_NUM_EQUAL(JHashTableDeleteData(table, NULL, NULL), DeleteFail);
	EXPECT_NUM_EQUAL(JHashTableDeleteData(table, expectedKey1, NULL), DeleteFail);
	EXPECT_NUM_EQUAL(JHashTableDeleteData(table, NULL, &expectedValue1), DeleteFail);
	EXPECT_NUM_EQUAL(JHashTableDeleteData(NULL, NULL, NULL), DeleteFail);

	DeleteJHashTable(&table);
})

TEST(HashTable_STRING_CHAR, DeleteFirstData, {
	int size = 10;
	char *expectedKey1 = "def";
	char expectedValue1_1 = 'x';
	char expectedValue1_2 = 't';
	char expectedValue1_3 = 'u';
	char *expectedKey2 = "abc";
	char expectedValue2 = 'y';
	JHashTablePtr table = NewJHashTable(size, StringType, CharType);

	JHashTableAddData(table, expectedKey1, &expectedValue1_1);
	JHashTableAddData(table, expectedKey1, &expectedValue1_2);
	JHashTableAddData(table, expectedKey1, &expectedValue1_3);
	JHashTableAddData(table, expectedKey2, &expectedValue2);
	JHashTablePrintAll(table);

	EXPECT_NUM_EQUAL(JHashTableDeleteFirstData(table), DeleteSuccess);
	EXPECT_NUM_EQUAL(*((char*)JHashTableGetFirstData(table)), expectedValue1_2);
	JHashTablePrintAll(table);

	EXPECT_NUM_EQUAL(JHashTableDeleteFirstData(NULL), DeleteFail);

	DeleteJHashTable(&table);
})

TEST(HashTable_STRING_CHAR, DeleteLastData, {
	int size = 10;
	char *expectedKey1 = "def";
	char expectedValue1 = 'x';
	char *expectedKey2 = "abc";
	char expectedValue2_1 = 'y';
	char expectedValue2_2 = 'z';
	char expectedValue2_3 = 'w';
	JHashTablePtr table = NewJHashTable(size, StringType, CharType);

	JHashTableAddData(table, expectedKey1, &expectedValue1);
	JHashTableAddData(table, expectedKey2, &expectedValue2_1);
	JHashTableAddData(table, expectedKey2, &expectedValue2_2);
	JHashTableAddData(table, expectedKey2, &expectedValue2_3);
	JHashTablePrintAll(table);

	EXPECT_NUM_EQUAL(JHashTableDeleteLastData(table), DeleteSuccess);
	EXPECT_NUM_EQUAL(*((char*)JHashTableGetLastData(table)), expectedValue2_2);
	JHashTablePrintAll(table);

	EXPECT_NUM_EQUAL(JHashTableDeleteLastData(NULL), DeleteFail);

	DeleteJHashTable(&table);
})

TEST(HashTable_STRING_CHAR, FindData, {
	int size = 10;
	char *expectedKey1 = "def";
	char expectedValue1 = 'x';
	char *expectedKey2 = "abc";
	char expectedValue2 = 'y';
	JHashTablePtr table = NewJHashTable(size, StringType, CharType);

	JHashTableAddData(table, expectedKey1, &expectedValue1);
	JHashTableAddData(table, expectedKey2, &expectedValue2);
	//JHashTablePrintAll(table);

	EXPECT_NUM_EQUAL(JHashTableFindData(table, expectedKey1, &expectedValue1), FindSuccess);
	EXPECT_NUM_EQUAL(JHashTableFindData(table, expectedKey2, &expectedValue2), FindSuccess);

	EXPECT_NUM_EQUAL(JHashTableFindData(NULL, expectedKey1, &expectedValue1), FindFail);
	EXPECT_NUM_EQUAL(JHashTableFindData(NULL, expectedKey1, NULL), FindFail);
	EXPECT_NUM_EQUAL(JHashTableFindData(NULL, NULL, &expectedValue1), FindFail);
	EXPECT_NUM_EQUAL(JHashTableFindData(table, NULL, NULL), FindFail);
	EXPECT_NUM_EQUAL(JHashTableFindData(table, expectedKey1, NULL), FindFail);
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
		// @ Common Test -----------------------------------------
		Test_Node_CreateAndDeleteNode,
		Test_LinkedList_CreateAndDeleteLinkedList,
		Test_LinkedList_GetSize,
		Test_HashTable_CreateAndDeleteHashTable,
		Test_HashTable_GetSize,
		Test_HashTable_GetType,
		Test_HashTable_ChangeHashType,

		// @ INT Test -------------------------------------------
		Test_Node_INT_SetData,
		Test_Node_INT_GetData,
		Test_LinkedList_INT_AddNode,
		Test_LinkedList_INT_GetFirstNodeData,
		Test_LinkedList_INT_GetLastNodeData,
		Test_LinkedList_INT_SetData,
		Test_LinkedList_INT_GetData,
		Test_LinkedList_INT_DeleteNodeData,
		Test_LinkedList_INT_FindNodeData,
		Test_HashTable_INT_AddData,
		Test_HashTable_INT_GetFirstData,
		Test_HashTable_INT_GetLastData,
		Test_HashTable_INT_DeleteData,
		Test_HashTable_INT_DeleteFirstData,
		Test_HashTable_INT_DeleteLastData,
		Test_HashTable_INT_FindData,

		// @ CHAR Test -------------------------------------------
		Test_Node_CHAR_SetData,
		Test_Node_CHAR_GetData,
		Test_LinkedList_CHAR_AddNode,
		Test_LinkedList_CHAR_GetFirstNodeData,
		Test_LinkedList_CHAR_GetLastNodeData,
		Test_LinkedList_CHAR_SetData,
		Test_LinkedList_CHAR_GetData,
		Test_LinkedList_CHAR_DeleteNodeData,
		Test_LinkedList_CHAR_FindNodeData,
		Test_HashTable_CHAR_AddData,
		Test_HashTable_CHAR_GetFirstData,
		Test_HashTable_CHAR_GetLastData,
		Test_HashTable_CHAR_DeleteData,
		Test_HashTable_CHAR_DeleteFirstData,
		Test_HashTable_CHAR_DeleteLastData,
		Test_HashTable_CHAR_FindData,

		// @ STRING Test -------------------------------------------
		Test_Node_STRING_SetData,
		Test_Node_STRING_GetData,
		Test_LinkedList_STRING_AddNode,
		Test_LinkedList_STRING_GetFirstNodeData,
		Test_LinkedList_STRING_GetLastNodeData,
		Test_LinkedList_STRING_SetData,
		Test_LinkedList_STRING_GetData,
		Test_LinkedList_STRING_DeleteNodeData,
		Test_LinkedList_STRING_FindNodeData,
		Test_HashTable_STRING_AddData,
		Test_HashTable_STRING_GetFirstData,
		Test_HashTable_STRING_GetLastData,
		Test_HashTable_STRING_DeleteData,
		Test_HashTable_STRING_DeleteFirstData,
		Test_HashTable_STRING_DeleteLastData,
		Test_HashTable_STRING_FindData,
		
		// @ Integrated Test -------------------------------------------
		// [Format: Test_HashTable_(Key)_(Value)_*]
		// # INT & CHAR
		Test_HashTable_INT_CHAR_AddData,
		Test_HashTable_INT_CHAR_GetFirstData,
		Test_HashTable_INT_CHAR_GetLastData,
		Test_HashTable_INT_CHAR_DeleteData,
		Test_HashTable_INT_CHAR_DeleteFirstData,
		Test_HashTable_INT_CHAR_DeleteLastData,
		Test_HashTable_INT_CHAR_FindData,
		// # CHAR & INT
		Test_HashTable_CHAR_INT_AddData,
		Test_HashTable_CHAR_INT_GetFirstData,
		Test_HashTable_CHAR_INT_GetLastData,
		Test_HashTable_CHAR_INT_DeleteData,
		Test_HashTable_CHAR_INT_DeleteFirstData,
		Test_HashTable_CHAR_INT_DeleteLastData,
		Test_HashTable_CHAR_INT_FindData,
		// # INT & STRING
		Test_HashTable_INT_STRING_AddData,
		Test_HashTable_INT_STRING_GetFirstData,
		Test_HashTable_INT_STRING_GetLastData,
		Test_HashTable_INT_STRING_DeleteData,
		Test_HashTable_INT_STRING_DeleteFirstData,
		Test_HashTable_INT_STRING_DeleteLastData,
		Test_HashTable_INT_STRING_FindData,
		// # STRING & INT
		Test_HashTable_STRING_INT_AddData,
		Test_HashTable_STRING_INT_GetFirstData,
		Test_HashTable_STRING_INT_GetLastData,
		Test_HashTable_STRING_INT_DeleteData,
		Test_HashTable_STRING_INT_DeleteFirstData,
		Test_HashTable_STRING_INT_DeleteLastData,
		Test_HashTable_STRING_INT_FindData,
		// # CHAR & STRING
		Test_HashTable_CHAR_STRING_AddData,
		Test_HashTable_CHAR_STRING_GetFirstData,
		Test_HashTable_CHAR_STRING_GetLastData,
		Test_HashTable_CHAR_STRING_DeleteData,
		Test_HashTable_CHAR_STRING_DeleteFirstData,
		Test_HashTable_CHAR_STRING_DeleteLastData,
		Test_HashTable_CHAR_STRING_FindData,
		// # STRING & CHAR
		Test_HashTable_STRING_CHAR_AddData,
		Test_HashTable_STRING_CHAR_GetFirstData,
		Test_HashTable_STRING_CHAR_GetLastData,
		Test_HashTable_STRING_CHAR_DeleteData,
		Test_HashTable_STRING_CHAR_DeleteFirstData,
		Test_HashTable_STRING_CHAR_DeleteLastData,
		Test_HashTable_STRING_CHAR_FindData
    );

    RUN_ALL_TESTS();

    CLEAN_UP_TESTSUIT();

	return 1;
}


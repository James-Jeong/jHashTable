#include "../include/ttlib.h"
#include "../include/jhashtable.h"

////////////////////////////////////////////////////////////////////////////////
/// Definitions of Test
////////////////////////////////////////////////////////////////////////////////

DECLARE_TEST();

TEST(ControlNode, CreateAndDeleteNode, {
	JNodePtr node = NewJNode();
	EXPECT_NOT_NULL(node);
	DeleteJNode(&node);
})

/*TEST(ControlNode, SetDataInNode, {
	JNodePtr node = NewJNode();

	int data = 5;
	JNodeSetData(node, data);
	EXPECT_NUM_EQUAL((int)JNodeGetData(node), data);

	DeleteJNode(&node);
})*/

TEST(ControlNode, GetDataFromNode, {
	JNodePtr node = NewJNode();

	EXPECT_NULL(JNodeGetData(node));

	DeleteJNode(&node);
})

TEST(ControlLinkedList, CreateAndDeleteLinkedList, {
	JLinkedListPtr list = NewJLinkedList();
	EXPECT_NOT_NULL(list);
	DeleteJLinkedList(&list);
})

TEST(ControlHashTable, CreateAndDeleteHashTable, {
	int size = 10;
	JHashTablePtr table = NewJHashTable(size);
	EXPECT_NOT_NULL(table);
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
//		Test_ControlNode_SetDataInNode,
		Test_ControlNode_GetDataFromNode,
		Test_ControlLinkedList_CreateAndDeleteLinkedList,
		Test_ControlHashTable_CreateAndDeleteHashTable
    );

    RUN_ALL_TESTS();

    CLEAN_UP_TESTSUIT();

	return 1;
}


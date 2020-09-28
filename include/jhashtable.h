#ifndef __JHASHTABLE_H__
#define __JHASHTABLE_H__

///////////////////////////////////////////////////////////////////////////////
/// Enums
///////////////////////////////////////////////////////////////////////////////

// 메모리 헤제 결과 열거형
typedef enum DeleteResult
{
	// 실패
	DeleteFail = -1,
	// 성공
	DeleteSuccess = 1
} DeleteResult;

// 검색 결과 열거형
typedef enum FindResult
{
	// 실패
	FindFail = -1,
	// 성공
	FindSuccess = 1
} FindResult;

// 해쉬 유형 열거형
typedef enum HashType
{
	IntType = 1,
	CharType,
	StringType
} HashType;

///////////////////////////////////////////////////////////////////////////////
/// Macros
///////////////////////////////////////////////////////////////////////////////

#ifndef MAX_CHAR_NUM
#define MAX_CHAR_NUM 256
#endif

///////////////////////////////////////////////////////////////////////////////
/// Definition
///////////////////////////////////////////////////////////////////////////////

typedef int (*_jhashInt_f)(int key, int hashSize);
typedef int (*_jhashChar_f)(char key, int hashSize);
typedef int (*_jhashString_f)(char* key, int hashSize);

// Linked List 에서 data 를 관리하기 위한 노드 구조체
typedef struct _jnode_t {
	struct _jnode_t *prev;
	struct _jnode_t *next;
	void *data;
} JNode, *JNodePtr, **JNodePtrContainer;

// Hash Table value 를 관리하는 이중 연결 리스트 구조체
typedef struct _jlinkedlist_t {
	int index;
	int size;
	JNodePtr head;
	JNodePtr tail;
	void *data;
} JLinkedList, *JLinkedListPtr, **JLinkedListPtrContainer;

// Hash Table 관리 구조체
// Chaining 방식
typedef struct _jhashtable_t {
	int size;
	HashType type;
	JLinkedListPtrContainer listContainer;
	_jhashInt_f intHashFunc;
	_jhashChar_f charHashFunc;
	_jhashString_f stringHashFunc;
} JHashTable, *JHashTablePtr, **JHashTablePtrContainer;

///////////////////////////////////////////////////////////////////////////////
// Functions for JNode
///////////////////////////////////////////////////////////////////////////////

JNodePtr NewJNode();
DeleteResult DeleteJNode(JNodePtrContainer container);
void* JNodeGetData(const JNodePtr node);
void* JNodeSetData(JNodePtr node, void *data);

///////////////////////////////////////////////////////////////////////////////
// Functions for JLinkedList
///////////////////////////////////////////////////////////////////////////////

JLinkedListPtr NewJLinkedList(int index);
DeleteResult DeleteJLinkedList(JLinkedListPtrContainer container);
int JLinkedListGetSize(const JLinkedListPtr list);
void* JLinkedListGetData(const JLinkedListPtr list);
void* JLinkedListSetData(const JLinkedListPtr list, void *data);
JLinkedListPtr JLinkedListAddNode(JLinkedListPtr list, void *data);
void* JLinkedListGetFirstNodeData(JLinkedListPtr list);
void* JLinkedListGetLastNodeData(JLinkedListPtr list);

//DeleteResult JLinkedListDeleteData(JLinkedListPtr list, void *data);
//FindResult JLinkedListFindData(JLinkedListPtr list, void *data);

///////////////////////////////////////////////////////////////////////////////
// Functions for JHashTable
///////////////////////////////////////////////////////////////////////////////

JHashTablePtr NewJHashTable(int size, HashType type);
DeleteResult DeleteJHashTable(JHashTablePtrContainer container);

int JHashTableGetSize(const JHashTablePtr table);
JHashTablePtr JHashTableAddData(JHashTablePtr table, void *data);

void* JHashTableGetFirstData(JHashTablePtr table);
void* JHashTableGetLastData(JHashTablePtr table);
//DeleteResult JHashTableDeleteData(JHashTablePtr table, void *data);
//DeleteResult JHashTableDeleteFirstData(JHashTablePtr table);
//DeleteResult JHashTableDeleteLastData(JHashTablePtr table);
//FindResult JHashTableFindData(JHashTablePtr table, void *data);

//JHashTablePtr JHashTableChangeType(JHashTablePtr table, HashType type);

///////////////////////////////////////////////////////////////////////////////
// Util Functions
///////////////////////////////////////////////////////////////////////////////

#endif


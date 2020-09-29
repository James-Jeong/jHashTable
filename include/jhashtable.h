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

// 데이터 유형 열거형
typedef enum DataType
{
	// Key
	Key = 1,
	// Value
	Value
} DataType;

// 해쉬 유형 열거형
typedef enum HashType
{
	Unknown = -1,
	IntType = 1,
	CharType,
	StringType
} HashType;

///////////////////////////////////////////////////////////////////////////////
/// Macro
///////////////////////////////////////////////////////////////////////////////

// 해싱 실패
#ifndef HASH_FAIL
#define HASH_FAIL -1
#endif

///////////////////////////////////////////////////////////////////////////////
/// Definitions
///////////////////////////////////////////////////////////////////////////////

typedef int (*_jhashInt_f)(int key, int hashSize);
typedef int (*_jhashChar_f)(char key, int hashSize);
typedef int (*_jhashString_f)(const char* key, int hashSize);

// Linked List 에서 data 를 관리하기 위한 노드 구조체
typedef struct _jnode_t {
	// 이전 노드 주소
	struct _jnode_t *prev;
	// 다음 노드 주소
	struct _jnode_t *next;
	// Value
	void *data;
} JNode, *JNodePtr, **JNodePtrContainer;

// Hash Table value 를 관리하는 이중 연결 리스트 구조체
typedef struct _jlinkedlist_t {
	// 해쉬값(Key 를 해쉬 테이블의 크기로 해싱한 값)
	int hash;
	// 연결 리스트 전체 크기
	int size;
	// Head 노드
	JNodePtr head;
	// Tail 노드
	JNodePtr tail;
	// 사용자 데이터
	void *data;
} JLinkedList, *JLinkedListPtr, **JLinkedListPtrContainer;

// Hash Table 관리 구조체
// Chaining 방식
typedef struct _jhashtable_t {
	// 해쉬 테이블의 전체 크기
	int size;
	// 저장할 Key 데이터 유형
	HashType keyType;
	// 저장할 Value 데이터 유형
	HashType valueType;
	// 해쉬 테이블에서 관리하는 Slot 들
	JLinkedListPtrContainer listContainer;
	// int 형(정수) 키 해싱 함수
	_jhashInt_f intHashFunc;
	// char 형(문자) 키 해싱 함수
	_jhashChar_f charHashFunc;
	// char* 형(문자열) 키 해싱 함수
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
void* JLinkedListSetData(JLinkedListPtr list, void *data);
JLinkedListPtr JLinkedListAddNode(JLinkedListPtr list, void *data);
void* JLinkedListGetFirstNodeData(const JLinkedListPtr list);
void* JLinkedListGetLastNodeData(const JLinkedListPtr list);

DeleteResult JLinkedListDeleteNodeData(JLinkedListPtr list, void *data);
FindResult JLinkedListFindNodeData(const JLinkedListPtr list, void *data);

///////////////////////////////////////////////////////////////////////////////
// Functions for JHashTable
///////////////////////////////////////////////////////////////////////////////

JHashTablePtr NewJHashTable(int size, HashType keyType, HashType valueType);
DeleteResult DeleteJHashTable(JHashTablePtrContainer container);

int JHashTableGetSize(const JHashTablePtr table);
int JHashTableGetType(const JHashTablePtr table);
JHashTablePtr JHashTableChangeType(JHashTablePtr table, DataType dataType, HashType hashType);
JHashTablePtr JHashTableAddData(JHashTablePtr table, void *key, void *value);

void* JHashTableGetFirstData(const JHashTablePtr table);
void* JHashTableGetLastData(const JHashTablePtr table);

DeleteResult JHashTableDeleteData(JHashTablePtr table, void *key, void *value);
DeleteResult JHashTableDeleteFirstData(JHashTablePtr table);
DeleteResult JHashTableDeleteLastData(JHashTablePtr table);
FindResult JHashTableFindData(const JHashTablePtr table, void *key, void *value);

void JHashTablePrintAll(const JHashTablePtr table);

#endif


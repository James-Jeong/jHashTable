#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/jhashtable.h"

////////////////////////////////////////////////////////////////////////////////
/// Predefinition of Static Functions
////////////////////////////////////////////////////////////////////////////////

static int HashInt(int key, int hashSize);
static int HashChar(char key, int hashSize);
static int HashString(const char* key, int hashSize);
static int JHashTableGetHash(const JHashTablePtr table, void *key);

///////////////////////////////////////////////////////////////////////////////
// Functions for JNode
///////////////////////////////////////////////////////////////////////////////

/**
 * @fn JNodePtr NewJNode()
 * @brief 새로운 노드 구조체 객체를 생성하는 함수
 * @return 성공 시 생성된 노드 구조체 객체의 주소, 실패 시 NULL 반환
 */
JNodePtr NewJNode()
{
	JNodePtr newNode = (JNodePtr)malloc(sizeof(JNode));
	if(newNode == NULL)
	{
		return NULL;
	}
	newNode->data = NULL;
	return newNode;
}

/**
 * @fn DeleteResult DeleteJNode(JNodePtrContainer container)
 * @brief 노드 구조체 객체를 삭제하는 함수
 * @param container 노드 구조체 객체의 주소를 저장한 이중 포인터, 컨테이너 변수(입력)
 * @return 성공 시 DeleteSuccess, 실패 시 DeleteFail 반환(DeleteResult 열거형 참고)
 */
DeleteResult DeleteJNode(JNodePtrContainer container)
{
	if(container == NULL || *container == NULL) return DeleteFail;
	free(*container);
	*container = NULL;
	return DeleteSuccess;
}

/**
 * @fn void* JNodeGetData(const JNodePtr node)
 * @brief 노드에 저장된 데이터의 주소를 반환하는 함수
 * @param node 노드 구조체 객체의 주소(입력, 읽기 전용)
 * @return 성공 시 저장된 데이터의 주소, 실패 시 NULL 반환
 */
void* JNodeGetData(const JNodePtr node)
{
	if(node == NULL) return NULL;
	return node->data;
}

/**
 * @fn void* JNodeSetData(JNodePtr node, void *data)
 * @brief 노드에 데이터의 주소를 저장하는 함수
 * @param node 노드 구조체 객체의 주소(출력)
 * @param data 저장할 데이터의 주소(입력)
 * @return 성공 시 저장된 데이터의 주소, 실패 시 NULL 반환
 */
void* JNodeSetData(JNodePtr node, void *data)
{
	if(node == NULL || data == NULL) return NULL;
	node->data = data;
	return node->data;
}

///////////////////////////////////////////////////////////////////////////////
// Functions for JLinkedList
///////////////////////////////////////////////////////////////////////////////

/**
 * @fn JLinkedListPtr NewJLinkedList(int index)
 * @brief 새로운 연결 리스트 구조체 객체를 생성하는 함수
 * @param index 해쉬 테이블에서 관리하는 연결 리스트의 인덱스 번호(입력)
 * @return 성공 시 생성된 연결 리스트 구조체 객체의 주소, 실패 시 NULL 반환
 */
JLinkedListPtr NewJLinkedList(int index)
{
	JLinkedListPtr newList = (JLinkedListPtr)malloc(sizeof(JLinkedList));
	if(newList == NULL)
	{
		return NULL;
	}

	newList->head = NewJNode();
	if(newList->head == NULL)
	{
		free(newList);
		return NULL;
	}

	newList->tail = NewJNode();
	if(newList->tail == NULL)
	{
		free(newList->head);
		free(newList);
		return NULL;
	}

	newList->head->next = newList->tail;
	newList->head->prev = NULL;
	newList->tail->prev = newList->head;
	newList->tail->next = NULL;

	newList->index = index;
	newList->size = 0;
	newList->data = NULL;

	return newList;
}

/**
 * @fn DeleteResult DeleteJLinkedList(JLinkedListPtrContainer container)
 * @brief 연결 리스트 구조체 객체를 삭제하는 함수
 * @param container 연결 리스트 구조체 객체의 주소를 저장한 이중 포인터, 컨테이너 변수(입력)
 * @return 성공 시 DeleteSuccess, 실패 시 DeleteFail 반환(DeleteResult 열거형 참고)
 */
DeleteResult DeleteJLinkedList(JLinkedListPtrContainer container)
{
	if(container == NULL || *container == NULL) return DeleteFail;

	int nodeIndex = 0;
	int listSize = (*container)->size;
		
	JNodePtr node = (*container)->head->next;
	JNodePtr nextNode = NULL;
	JNodePtr prevNode = NULL;

	while(node != (*container)->tail)
	{
		nextNode = node->next;
		prevNode = node->prev;
		if(DeleteJNode(&node) == DeleteFail) return DeleteFail;
		nextNode->prev = prevNode;
		prevNode->next = nextNode;
		node = nextNode;
	}

	if(DeleteJNode(&((*container)->head)) == DeleteFail) return DeleteFail;
	if(DeleteJNode(&((*container)->tail)) == DeleteFail) return DeleteFail;

	free(*container);
	*container = NULL;

	return DeleteSuccess;
}

/**
 * @fn int JLinkedListGetSize(const JLinkedListPtr list)
 * @brief 연결 리스트의 전체 크기를 반환하는 함수
 * @param list 연결 리스트 구조체 객체의 주소(입력, 읽기 전용)
 * @return 성공 시 연결 리스트의 전체 크기, 실패 시 -1 반환
 */
int JLinkedListGetSize(const JLinkedListPtr list)
{
	if(list == NULL) return -1;
	return list->size;
}

/**
 * @fn void* JLinkedListGetData(const JLinkedListPtr list)
 * @brief 연결 리스트에 저장된 데이터의 주소를 반환하는 함수
 * @param list 연결 리스트 구조체 객체의 주소(입력, 읽기 전용)
 * @return 성공 시 저장된 데이터의 주소, 실패 시 NULL 반환
 */
void* JLinkedListGetData(const JLinkedListPtr list)
{
	if(list == NULL) return NULL;
	return list->data;
}

/**
 * @fn void* JLinkedListSetData(const JLinkedListPtr list, void *data)
 * @brief 연결 리스트에 데이터의 주소를 저장하는 함수
 * @param list 연결 리스트 구조체 객체의 주소(출력)
 * @param data 저장할 데이터의 주소(입력)
 * @return 성공 시 저장된 데이터의 주소, 실패 시 NULL 반환
 */
void* JLinkedListSetData(JLinkedListPtr list, void *data)
{
	if(list == NULL || data == NULL) return NULL;
	list->data = data;
	return list->data;
}

/**
 * @fn void* JLinkedListSetData(const JLinkedListPtr list, void *data)
 * @brief 연결 리스트에 새로운 노드를 추가하는 함수
 * 중복 허용하지 않음
 * @param list 연결 리스트 구조체 객체의 주소(출력)
 * @param data 저장할 노드의 데이터 주소(입력)
 * @return 성공 시 연결 리스트 구조체의 주소, 실패 시 NULL 반환
 */
JLinkedListPtr JLinkedListAddNode(JLinkedListPtr list, void *data)
{
	if(list == NULL || data == NULL) return NULL;
	if(JLinkedListFindNodeData(list, data) == FindSuccess) return NULL;

	JNodePtr newNode = NewJNode();
	if(JNodeSetData(newNode, data) == NULL) return NULL;

	if(list->head->next == list->tail)
	{
		newNode->next = list->tail;
		newNode->prev = list->head;
		list->head->next = newNode;
		list->tail->prev = newNode;
	}
	else if((list->head->next != list->tail) && (list->tail->prev != list->head))
	{
		JNodePtr oldNode = list->tail->prev;
		newNode->prev = oldNode;
		newNode->next = list->tail;
		oldNode->next = newNode;
		list->tail->prev = newNode;
	}
	else
	{
		return NULL;
	}

	list->size++;
	return list;
}

/**
 * @fn void* JLinkedListGetFirstNodeData(const JLinkedListPtr list)
 * @brief 연결 리스트에 저장된 첫 번째 노드의 데이터를 반환하는 함수
 * @param list 연결 리스트 구조체 객체의 주소(입력, 읽기 전용)
 * @return 성공 시 첫 번째 노드의 데이터의 주소, 실패 시 NULL 반환
 */
void* JLinkedListGetFirstNodeData(const JLinkedListPtr list)
{
	if(list == NULL) return NULL;
	if(list->head->next == list->tail) return NULL;
	return JNodeGetData(list->head->next);
}

/**
 * @fn void* JLinkedListGetLastNodeData(const JLinkedListPtr list)
 * @brief 연결 리스트에 저장된 마지막 노드의 데이터를 반환하는 함수
 * @param list 연결 리스트 구조체 객체의 주소(입력, 읽기 전용)
 * @return 성공 시 마지막 노드의 데이터의 주소, 실패 시 NULL 반환
 */
void* JLinkedListGetLastNodeData(const JLinkedListPtr list)
{
	if(list == NULL) return NULL;
	if(list->tail->prev == list->head) return NULL;

	return JNodeGetData(list->tail->prev);
}

/**
 * @fn DeleteResult JLinkedListDeleteNodeData(JLinkedListPtr list, void *data)
 * @brief 연결 리스트에 저장된 데이터를 삭제하는 함수
 * @param list 연결 리스트 구조체 객체의 주소(츨력)
 * @param data 삭제할 데이터의 주소(입력)
 * @return 성공 시 DeleteSuccess, 실패 시 DeleteFail 반환(DeleteResult 열거형 참고)
 */
DeleteResult JLinkedListDeleteNodeData(JLinkedListPtr list, void *data)
{
	if(list == NULL || data == NULL) return DeleteFail;

	DeleteResult result = DeleteFail;
	JNodePtr node = list->head->next;
	JNodePtr nextNode = NULL;
	JNodePtr prevNode = NULL;

	while(node != list->tail)
	{
		nextNode = node->next;
		prevNode = node->prev;
		if(node->data == data)
		{
			if(DeleteJNode(&node) == DeleteFail) return DeleteFail;
			nextNode->prev = prevNode;
			prevNode->next = nextNode;
			list->size--;
			result = DeleteSuccess;
			break;
		}
		node = nextNode;
	}

	return result;
}

/**
 * @fn FindResult JLinkedListFindNodeData(const JLinkedListPtr list, void *data)
 * @brief 연결 리스트에 저장된 데이터를 검색하는 함수
 * 데이터 검색 후 데이터는 반환하지 않고 존재 유무만 반환한다.
 * @param list 연결 리스트 구조체 객체의 주소(입력, 읽기 전용)
 * @param data 검색할 데이터의 주소(입력)
 * @return 성공 시 FindSuccess, 실패 시 FindFail 반환(FindResult 열거형 참고)
 */
FindResult JLinkedListFindNodeData(const JLinkedListPtr list, void *data)
{
	if(list == NULL || data == NULL) return FindFail;

	FindResult result = FindFail;
	JNodePtr node = list->head->next;
	while(node != list->tail)
	{
		if(node->data == data)
		{
			result = FindSuccess;
			break;
		}
		node = node->next;
	}

	return result;
}

////////////////////////////////////////////////////////////////////////////////
/// Functions for JHashTable
////////////////////////////////////////////////////////////////////////////////

/**
 * @fn JHashTablePtr NewJHashTable(int size)
 * @brief Hash Table 관리 구조체를 새로 생성하는 함수
 * @param size 구조체에서 관리할 hash block 크기(입력)
 * @param type 등록할 해쉬 함수의 유형(입력, 열거형)
 * @return 성공 시 새로 생성된 JHashTable 객체의 주소, 실패 시 NULL 반환
 */
JHashTablePtr NewJHashTable(int size, HashType type)
{
	if(size <= 0) return NULL;

    JHashTablePtr newHashTable = (JHashTablePtr)malloc(sizeof(JHashTable));
    if(newHashTable == NULL)  return NULL;
	
	newHashTable->listContainer = (JLinkedListPtrContainer)malloc(sizeof(JLinkedListPtr) * (size_t)size);
	if(newHashTable->listContainer == NULL)
	{
		free(newHashTable);
		return NULL;
	}
	
	int listIndex = 0;
	for( ; listIndex < size; listIndex++)
	{
		newHashTable->listContainer[listIndex] = NewJLinkedList(listIndex);
		if(newHashTable->listContainer[listIndex] == NULL)
		{
			DeleteJHashTable(&newHashTable);
			return NULL;
		}
	}

	newHashTable->intHashFunc = HashInt;
	newHashTable->charHashFunc = HashChar;
	newHashTable->stringHashFunc = HashString;
	newHashTable->type = type;
	newHashTable->size = size;

    return newHashTable;
}

/**
 * @fn DeleteResult DeleteJHashTable(JHashTablePtrContainer container)
 * @brief Hash Table 관리 구조체를 삭제하는 함수
 * @param container JHashTable 구조체의 포인터(주소)들을 관리하는 이중 포인터(입력)
 * @return 성공 시 DeleteSuccess, 실패 시 DeleteFail 반환
 */
DeleteResult DeleteJHashTable(JHashTablePtrContainer container)
{
	if(container == NULL || *container == NULL) return DeleteFail;

	if((*container)->listContainer != NULL)
	{
		int listIndex = 0;
		int tableSize = (*container)->size;

		for( ; listIndex < tableSize; listIndex++)
		{
			if((*container)->listContainer[listIndex] != NULL)
			{
			    if(DeleteJLinkedList(&((*container)->listContainer[listIndex])) == DeleteFail) return DeleteFail;
			}
		}
		free((*container)->listContainer);
	}

    free(*container);
    *container = NULL;

	return DeleteSuccess;
}

/**
 * @fn int JHashTableGetSize(const JHashTablePtr table)
 * @brief 해쉬 테이블의 전체 크기를 반환하는 함수
 * @param table 해쉬 테이블 구조체 객체의 주소(입력, 읽기 전용)
 * @return 성공 시 해쉬 테이블의 전체 크기, 실패 시 -1 반환
 */
int JHashTableGetSize(const JHashTablePtr table)
{
	if(table == NULL) return -1;
	return table->size;
}

/**
 * @fn HashType JHashTableGetType(const JHashTablePtr table)
 * @brief 해쉬 테이블의 해쉬 유형을 반환하는 함수
 * @param table 해쉬 테이블 구조체 객체의 주소(입력, 읽기 전용)
 * @return 성공 시 해쉬 테이블의 해쉬 유형, 실패 시 Unknown 반환(HashType 열거형 참고)
 */
HashType JHashTableGetType(const JHashTablePtr table)
{
	if(table == NULL) return -1;
	return table->type;
}

/**
 * @fn JHashTablePtr JHashTableChangeType(JHashTablePtr table, HashType type)
 * @brief 해쉬 테이블의 해쉬 유형을 변경하는 함수
 * @param table 해쉬 테이블 구조체 객체의 주소(출력)
 * @param type 변경할 해쉬 유형(입력, HashType 열거형 참고)
 * @return 성공 시 해쉬 테이블 구조체의 주소, 실패 시 NULL 반환
 */
JHashTablePtr JHashTableChangeType(JHashTablePtr table, HashType type)
{
	if(table == NULL) return NULL;
	switch(type)
	{
		case IntType: break;
		case CharType: break; 
		case StringType: break;
		default: return NULL;
	}

	table->type = type;
	return table;
}

/**
 * @fn JHashTablePtr JHashTableAddData(JHashTablePtr table, void *key, void *value)
 * @brief 해쉬 테이블에 새로운 데이터를 추가하는 함수
 * @param table 해쉬 테이블 구조체 객체의 주소(출력)
 * @param key 저장할 키(입력)
 * @param value 저장할 데이터(입력)
 * @return 성공 시 해쉬 테이블 구조체의 주소, 실패 시 NULL 반환
 */
JHashTablePtr JHashTableAddData(JHashTablePtr table, void *key, void *value)
{
	if(table == NULL || key == NULL || value == NULL) return NULL;

	int listIndex = JHashTableGetHash(table, key);
	if(listIndex == HASH_FAIL) return NULL;

	if(JLinkedListAddNode(table->listContainer[listIndex], value) == NULL) return NULL;
	return table;
}

/**
 * @fn void* JHashTableGetFirstData(const JHashTablePtr table)
 * @brief 해쉬 테이블에 저장된 첫 번째 데이터를 반환하는 함수
 * @param table 해쉬 테이블 구조체 객체의 주소(입력, 읽기 전용)
 * @return 성공 시 첫 번째 데이터의 주소, 실패 시 NULL 반환
 */
void* JHashTableGetFirstData(const JHashTablePtr table)
{
	if(table == NULL) return NULL;

	void *data = NULL;
	int tableSize = table->size;
	int listIndex = 0;

	for( ; listIndex < tableSize; listIndex++)
	{
		data = JLinkedListGetFirstNodeData(table->listContainer[listIndex]);
		if(data != NULL) break;
	}

	return data;
}

/**
 * @fn void* JHashTableGetLastData(const JHashTablePtr table)
 * @brief 해쉬 테이블에 저장된 마지막 데이터를 반환하는 함수
 * @param table 해쉬 테이블 구조체 객체의 주소(입력, 읽기 전용)
 * @return 성공 시 마지막 데이터의 주소, 실패 시 NULL 반환
 */
void* JHashTableGetLastData(const JHashTablePtr table)
{
	if(table == NULL) return NULL;

	void *data = NULL;
	int listIndex = table->size - 1;

	for( ; listIndex >= 0; listIndex--)
	{
		data = JLinkedListGetLastNodeData(table->listContainer[listIndex]);
		if(data != NULL) break;
	}

	return data;
}

/**
 * @fn DeleteResult JHashTableDeleteData(JHashTablePtr table, void* key, void *value)
 * @brief 해쉬 테이블에 저장된 데이터를 삭제하는 함수
 * @param table 해쉬 테이블 구조체 객체의 주소(츨력)
 * @param key 삭제할 키(입력)
 * @param value 삭제할 데이터(입력)
 * @return 성공 시 DeleteSuccess, 실패 시 DeleteFail 반환(DeleteResult 열거형 참고)
 */
DeleteResult JHashTableDeleteData(JHashTablePtr table, void *key, void *value)
{
	if(table == NULL || key == NULL || value == NULL) return DeleteFail;

	DeleteResult result = DeleteFail;
	int listIndex = JHashTableGetHash(table, key);
	if(listIndex == HASH_FAIL) return DeleteFail;

	return JLinkedListDeleteNodeData(table->listContainer[listIndex], value);
}

/**
 * @fn DeleteResult JHashTableDeleteFirstData(JHashTablePtr table)
 * @brief 해쉬 테이블에 저장된 첫 번째 데이터를 삭제하는 함수
 * @param table 해쉬 테이블 구조체 객체의 주소(츨력)
 * @return 성공 시 DeleteSuccess, 실패 시 DeleteFail 반환(DeleteResult 열거형 참고)
 */
DeleteResult JHashTableDeleteFirstData(JHashTablePtr table)
{
	if(table == NULL) return DeleteFail;

	DeleteResult result = DeleteFail;
	void *data = NULL;
	int tableSize = table->size;
	int listIndex = 0;

	for( ; listIndex < tableSize; listIndex++)
	{
		data = JLinkedListGetFirstNodeData(table->listContainer[listIndex]);
		if(data != NULL)
		{
			//printf("Prev listSize:%d\n", JLinkedListGetSize(table->listContainer[listIndex]));
			result = JLinkedListDeleteNodeData(table->listContainer[listIndex], data);
			//printf("After listSize:%d\n", JLinkedListGetSize(table->listContainer[listIndex]));
			break;
		}
	}

	return result;
}

/**
 * @fn DeleteResult JHashTableDeleteLastData(JHashTablePtr table)
 * @brief 해쉬 테이블에 저장된 마지막 데이터를 삭제하는 함수
 * @param table 해쉬 테이블 구조체 객체의 주소(츨력)
 * @return 성공 시 DeleteSuccess, 실패 시 DeleteFail 반환(DeleteResult 열거형 참고)
 */
DeleteResult JHashTableDeleteLastData(JHashTablePtr table)
{
	if(table == NULL) return DeleteFail;

	DeleteResult result = DeleteFail;
	void *data = NULL;
	int listIndex = table->size - 1;

	for( ; listIndex >= 0; listIndex--)
	{
		data = JLinkedListGetLastNodeData(table->listContainer[listIndex]);
		if(data != NULL)
		{
			//printf("Prev listSize:%d\n", JLinkedListGetSize(table->listContainer[listIndex]));
			result = JLinkedListDeleteNodeData(table->listContainer[listIndex], data);
			//printf("After listSize:%d\n", JLinkedListGetSize(table->listContainer[listIndex]));
			break;
		}
	}

	return result;
}

/**
 * @fn FindResult JHashTableFindData(const JHashTablePtr table, void *key, void *value)
 * @brief 해쉬 테이블에 저장된 데이터를 검색하는 함수
 * 데이터 검색 후 데이터는 반환하지 않고 존재 유무만 반환한다.
 * @param table 해쉬 테이블 구조체 객체의 주소(입력, 읽기 전용)
 * @param key 검색할 키(입력)
 * @param value 검색할 데이터(입력)
 * @return 성공 시 FindSuccess, 실패 시 FindFail 반환(FindResult 열거형 참고)
 */
FindResult JHashTableFindData(const JHashTablePtr table, void *key, void *value)
{
	if(table == NULL || key == NULL || value == NULL) return FindFail;

	int listIndex = JHashTableGetHash(table, key);
	if(listIndex == HASH_FAIL) return FindFail;

	return JLinkedListFindNodeData(table->listContainer[listIndex], value);
}

/**
 * @fn void JHashTablePrintAll(const JHashTablePtr table)
 * @brief 해쉬 테이블에 저장된 모든 데이터들을 출력하는 함수
 * @param table 해쉬 테이블 구조체 객체의 주소(입력, 읽기 전용)
 * @return 반환값 없음
 */
void JHashTablePrintAll(const JHashTablePtr table)
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
            switch(table->type)
            {
                case IntType:
                    printf("%d ", *((int*)node->data));
                    break;
                case CharType:
                    printf("%c ", *((char*)node->data));
                    break;
                case StringType:
                    printf("%s ", ((char*)node->data));
                    break;
                default: return;
            }
            node = node->next;
        }
        if(isDataExist == 1) printf("]\n");
    }
    printf("------------------\n");
}

////////////////////////////////////////////////////////////////////////////////
/// Static Functions
////////////////////////////////////////////////////////////////////////////////

/**
 * @fn static int HashInt(int key, int hashSize)
 * @brief int 형 정수값을 해쉬 테이블의 크기로 해싱한 값을 반환하는 함수
 * @param key 해싱할 int 형 정수(입력)
 * @param hashSize 해쉬 테이블의 전체 크기(입력)
 * @return 항상 해싱된 값 반환
 */
static int HashInt(int key, int hashSize)
{
	return key % hashSize;
}

/**
 * @fn static int HashChar(char key, int hashSize)
 * @brief char 형 문자를 해쉬 테이블의 크기로 해싱한 값을 반환하는 함수
 * @param key 해싱할 char 형 문자(입력)
 * @param hashSize 해쉬 테이블의 전체 크기(입력)
 * @return 항상 해싱된 값 반환
 */
static int HashChar(char key, int hashSize)
{
	int value = 0;
	int hashIndex = 1;
	for( ; hashIndex <= (int)key; hashIndex++)
	{
		value += (hashIndex * (int)key);
	}
	return value % hashSize;
}

/**
 * @fn static int HashString(const char* key, int hashSize)
 * @brief char* 형 문자열을 해쉬 테이블의 크기로 해싱한 값을 반환하는 함수
 * @param key 해싱할 char* 형 문자열(입력, 읽기 전용)
 * @param hashSize 해쉬 테이블의 전체 크기(입력)
 * @return 항상 해싱된 값 반환
 */
static int HashString(const char* key, int hashSize)
{
	int value = 0;
	int hashIndex = 1;
	int strLength = strlen(key);
	for( ; hashIndex <= strLength; hashIndex++)
	{
		value += (hashIndex * key[hashIndex]);
	}
	return value % hashSize;
}

/**
 * @fn static int JHashTableGetHash(const JHashTablePtr table, void *key)
 * @brief 해쉬 테이블의 해쉬 유형에 따라 지정한 키에 대한 해쉬값을 반환하는 함수 
 * @param table 해쉬 테이블 구조체 객체의 주소(입력, 읽기 전용)
 * @param key 해싱할 키(입력)
 * @return 성공 시 해쉬값, 실패 시 HASH_FAIL(-1) 반환
 */
static int JHashTableGetHash(const JHashTablePtr table, void *key)
{
	int hash = 0;
	int tableSize = table->size;

	switch(table->type)
	{
		case IntType:
			hash = table->intHashFunc(*((int*)key), tableSize);
			break;
		case CharType:
			hash = table->charHashFunc(*((char*)key), tableSize);
			break;
		case StringType:
			hash = table->stringHashFunc((char*)key, tableSize);
			break;
		default: return HASH_FAIL;
	}

	return hash;
}


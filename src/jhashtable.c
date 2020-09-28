#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/jhashtable.h"

////////////////////////////////////////////////////////////////////////////////
/// Predefinition of Static Functions
////////////////////////////////////////////////////////////////////////////////

static int HashInt(int key, int hashSize);
static int HashChar(char key, int hashSize);
static int HashString(char* key, int hashSize);

///////////////////////////////////////////////////////////////////////////////
// Functions for JNode
///////////////////////////////////////////////////////////////////////////////

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

DeleteResult DeleteJNode(JNodePtrContainer container)
{
	if(container == NULL || *container == NULL) return DeleteFail;
	free(*container);
	*container = NULL;
	return DeleteSuccess;
}

void* JNodeGetData(const JNodePtr node)
{
	if(node == NULL) return NULL;
	return node->data;
}

void* JNodeSetData(JNodePtr node, void *data)
{
	if(node == NULL || data == NULL) return NULL;
	node->data = data;
	return node->data;
}

///////////////////////////////////////////////////////////////////////////////
// Functions for JLinkedList
///////////////////////////////////////////////////////////////////////////////

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

DeleteResult DeleteJLinkedList(JLinkedListPtrContainer container)
{
	if(container == NULL || *container == NULL) return DeleteFail;

	int nodeIndex = 0;
	int listSize = (*container)->size;
		
	JNodePtr node = (*container)->head->next;
	while(node != (*container)->tail)
	{
		JNodePtr tempNode = node;
		node->next->prev = node->prev;
		node->prev->next = node->next;
		node = node->next;
		if(DeleteJNode(&tempNode) == DeleteFail) return DeleteFail;
	}

	if(DeleteJNode(&((*container)->head)) == DeleteFail) return DeleteFail;
	if(DeleteJNode(&((*container)->tail)) == DeleteFail) return DeleteFail;

	free(*container);
	*container = NULL;

	return DeleteSuccess;
}

int JLinkedListGetSize(const JLinkedListPtr list)
{
	if(list == NULL) return -1;
	return list->size;
}

void* JLinkedListGetData(const JLinkedListPtr list)
{
	if(list == NULL) return NULL;
	return list->data;
}

void* JLinkedListSetData(const JLinkedListPtr list, void *data)
{
	if(list == NULL || data == NULL) return NULL;
	list->data = data;
	return list->data;
}

JLinkedListPtr JLinkedListAddNode(JLinkedListPtr list, void *data)
{
	if(list == NULL || data == NULL) return NULL;

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

void* JLinkedListGetFirstData(JLinkedListPtr list)
{
	if(list == NULL) return NULL;
	if(list->head->next == list->tail) return NULL;
	return JNodeGetData(list->head->next);
}

void* JLinkedListGetLastData(JLinkedListPtr list)
{
	if(list == NULL) return NULL;
	if(list->tail->prev == list->head) return NULL;

	return JNodeGetData(list->tail->prev);
}

DeleteResult JLinkedListDeleteData(JLinkedListPtr list, void *data)
{
	if(list == NULL || data == NULL) return DeleteFail;

	JNodePtr node = list->head->next;
	while(node != list->tail)
	{
		if(node->data == data)
		{
			node->next->prev = node->prev;
			node->prev->next = node->next;
			JNodePtr tempNode = node;
			if(DeleteJNode(&tempNode) == DeleteFail) return DeleteFail;
			break;
		}
		node = node->next;
	}

	return DeleteSuccess;
}

FindResult JLinkedListFindData(JLinkedListPtr list, void *data)
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
	
	int tableIndex = 0;
	for( ; tableIndex < size; tableIndex++)
	{
		newHashTable->listContainer[tableIndex] = NewJLinkedList(tableIndex);
		if(newHashTable->listContainer[tableIndex] == NULL)
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
		int tableIndex = 0;
		int tableSize = (*container)->size;

		for( ; tableIndex < tableSize; tableIndex++)
		{
			if((*container)->listContainer[tableIndex] != NULL)
			{
			    if(DeleteJLinkedList(&((*container)->listContainer[tableIndex])) == DeleteFail) return DeleteFail;
			}
		}
		free((*container)->listContainer);
	}

    free(*container);
    *container = NULL;

	return DeleteSuccess;
}

int JHashTableGetSize(const JHashTablePtr table)
{
	if(table == NULL) return -1;
	return table->size;
}

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

JHashTablePtr JHashTableAddData(JHashTablePtr table, void *data)
{
	if(table == NULL || data == NULL) return NULL;

	int tableIndex = 0;
	int hashSize = table->size;
	int intData = 0;
	char charData = 0;
	char* stringData = NULL;

	switch(table->type)
	{
		case IntType:
			intData = *((int*)data);
			tableIndex = table->intHashFunc(intData, hashSize);
			if(JLinkedListAddNode(table->listContainer[tableIndex], data) == NULL) return NULL;
			break;
		case CharType:
			charData = *((char*)data);
			tableIndex = table->charHashFunc(charData, hashSize);
			if(JLinkedListAddNode(table->listContainer[tableIndex], data) == NULL) return NULL;
			break;
		case StringType:
			stringData = (char*)data;
			tableIndex = table->stringHashFunc(stringData, hashSize);
			if(JLinkedListAddNode(table->listContainer[tableIndex], data) == NULL) return NULL;
			break;
		default:
			return NULL;
	}

	return table;
}

void* JHashTableGetFirstData(JHashTablePtr table)
{
	if(table == NULL) return NULL;

	void *data = NULL;
	int tableSize = table->size;
	int tableIndex = 0;

	for( ; tableIndex < tableSize; tableIndex++)
	{
		data = JLinkedListGetFirstData(table->listContainer[tableIndex]);
		if(data != NULL) break;
	}

	return data;
}

void* JHashTableGetLastData(JHashTablePtr table)
{
	if(table == NULL) return NULL;

	void *data = NULL;
	int tableIndex = table->size - 1;

	for( ; tableIndex >= 0; tableIndex--)
	{
		data = JLinkedListGetLastData(table->listContainer[tableIndex]);
		if(data != NULL) break;
	}

	return data;
}

DeleteResult JHashTableDeleteData(JHashTablePtr table, void *data)
{
	if(table == NULL || data == NULL) return DeleteFail;

	int tableSize = table->size;
	int tableIndex = 0;
	DeleteResult result = DeleteFail;

	for( ; tableIndex < tableSize; tableIndex++)
	{
		if(JLinkedListDeleteData(table->listContainer[tableIndex], data) == DeleteSuccess) {
			result = DeleteSuccess;
			break;
		}
	}

	return result;
}


////////////////////////////////////////////////////////////////////////////////
/// Static Functions
////////////////////////////////////////////////////////////////////////////////

static int HashInt(int key, int hashSize)
{
	return key % hashSize;
}

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

static int HashString(char* key, int hashSize)
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


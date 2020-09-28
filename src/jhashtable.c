#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/jhashtable.h"

////////////////////////////////////////////////////////////////////////////////
/// Static Definition
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
/// Predefinition of Static Functions
////////////////////////////////////////////////////////////////////////////////

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

void DeleteJNode(JNodePtrContainer container)
{
	free(*container);
	*container = NULL;
}

void* JNodeGetData(const JNodePtr node)
{
	return node->data;
}

///////////////////////////////////////////////////////////////////////////////
// Functions for JLinkedList
///////////////////////////////////////////////////////////////////////////////

JLinkedListPtr NewJLinkedList()
{
	JLinkedListPtr newList = (JLinkedListPtr)malloc(sizeof(JLinkedList));
	if(newList == NULL)
	{
		return NULL;
	}

	newList->index = 0;
	newList->size = 0;

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

	newList->data = NULL;

	return newList;
}

void DeleteJLinkedList(JLinkedListPtrContainer container)
{
	int nodeIndex = 0;
	int listSize = (*container)->size;
	JNodePtr node = (*container)->head;

	for( ; nodeIndex < listSize; nodeIndex++)
	{
		if(node != NULL)
		{
			DeleteJNode(&node);
		}
		node = node->next;
	}

	free(*container);
	*container = NULL;
}

int JLinkedListGetSize(const JLinkedListPtr list)
{
	return list->size;
}

void* JLinekdListGetData(const JLinkedListPtr list)
{
	return list->data;
}

////////////////////////////////////////////////////////////////////////////////
/// Functions for JHashTable
////////////////////////////////////////////////////////////////////////////////

/**
 * @fn JHashTablePtr NewJHashTable(int size)
 * @brief Hash Table 관리 구조체를 새로 생성하는 함수
 * @param size 구조체에서 관리할 hash block 크기(입력)
 * @return 성공 시 새로 생성된 JHashTable 객체의 주소, 실패 시 NULL 반환
 */
JHashTablePtr NewJHashTable(int size)
{
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
		newHashTable->listContainer[tableIndex] = NULL;
  
	newHashTable->size = size;
	newHashTable->intFunc = NULL;
	newHashTable->charFunc = NULL;
	newHashTable->stringFunc = NULL;

    return newHashTable;
}

/**
 * @fn void DeleteJHashTable(JHashTablePtrContainer container)
 * @brief Hash Table 관리 구조체를 삭제하는 함수
 * @param container JHashTable 구조체의 포인터(주소)들을 관리하는 이중 포인터(입력)
 * @return 반환값 없음
 */
void DeleteJHashTable(JHashTablePtrContainer container)
{
	if((*container)->listContainer != NULL)
	{
		int tableIndex = 0;
		int tableSize = (*container)->size;

		for( ; tableIndex < tableSize; tableIndex++)
		{
			if((*container)->listContainer[tableIndex] != NULL)
			{
			    DeleteJLinkedList(&((*container)->listContainer[tableIndex]));
			}
		}
		free((*container)->listContainer);
	}

    free(*container);
    *container = NULL;
}


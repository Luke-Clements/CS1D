
#ifndef	SKIPLIST_H_
#define SKIPLIST_H_

#include <vector>
#include <cstddef>
#include <cstdlib>
#include <iostream>

using namespace std;

template <class dt>
struct dat
{
	dt  data;
	int key;
};

template <class dt>
struct quadNode
{
	dat<dt>			data;
	quadNode<dt>*	prev = NULL;
	quadNode<dt>*	up   = NULL;
	quadNode<dt>*	next = NULL;
	quadNode<dt>*	down = NULL;
};

template <class dt>
class SkipList
{
public:
	SkipList();
	~SkipList();

	quadNode<dt>*	 AddData(	int key, dt data);
	void	         RemoveData(int key);
	dat<dt>*         GetData(	int key);
	quadNode<dt>*    GetHead();

private:
	bool CoinToss();

	void addNewLevel();
	void removeTopLevel();

	quadNode<dt>* addToLevel(quadNode<dt>* levelB, quadNode<dt>* levelE, quadNode<dt>* addNode);
	void removeFromLevel(quadNode<dt>* levelB, quadNode<dt>* levelE, quadNode<dt>* begin);
	
	int maxKeyVal = std::numeric_limits<int>::max();
	int minKeyVal = std::numeric_limits<int>::min();

	int elements;
	quadNode<dt>* headhead;
	quadNode<dt>* headtail;
	quadNode<dt>* tailhead;
	quadNode<dt>* tailtail;
};

#endif	SKIPLIST_H_

template <class dt>
SkipList<dt>::SkipList()
{
	headhead = new quadNode < dt > ;
	headtail = new quadNode < dt > ;
	tailhead = new quadNode < dt > ;
	tailtail = new quadNode < dt > ;
	elements = 0;

	headtail->data.key = headhead->data.key = minKeyVal;
	tailtail->data.key = tailhead->data.key = maxKeyVal;

	headtail->down = headhead;
	headtail->next = tailtail;
	headhead->up = headtail;
	headhead->next = tailhead;
	tailtail->down = tailhead;
	tailtail->prev = headtail;
	tailhead->up = tailtail;
	tailhead->prev = headhead;
}

template <class dt>
SkipList<dt>::~SkipList()
{
	quadNode<dt>* temp = headtail;

	while (headtail != NULL && temp != NULL)
	{		
		headtail = headtail->down;

		if (temp->next != tailhead)
		{
			quadNode<dt>* deleteNode;

			deleteNode = temp;
			temp = temp->next;
			delete deleteNode;
		}
		else
		{
			delete temp;
			temp = headtail;
		}
	}
}

template <class dt>
bool SkipList<dt>::CoinToss()
{
	if (rand() % 2 == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template <class dt>
quadNode<dt>* SkipList<dt>::addToLevel(quadNode<dt>* levelB, quadNode<dt>* levelE, quadNode<dt>* addNode)
{
	quadNode<dt>* levelPtr = levelB;
	quadNode<dt>* newNode = new quadNode<dt>;

	while (levelPtr->next->data.key != levelE->data.key && levelPtr->next->data.key < addNode->data.key)
	{
		levelPtr = levelPtr->next;
	}

	if (levelPtr->next->data.key == addNode->data.key && levelPtr->next->data.data > addNode->data.data)
	{
		levelPtr = levelPtr->next;
	}
	addNode->prev = levelPtr;
	addNode->next = levelPtr->next;
	levelPtr->next = addNode;
	addNode->next->prev = addNode;

	if (CoinToss())
	{
		if (levelB->up == headtail)
		{
			addNewLevel();
		}	
		newNode->data.data = addNode->data.data;
		newNode->data.key = addNode->data.key;
		newNode->down = addNode;
		addNode->up = addToLevel(levelB->up, levelE->up, newNode);
	}
	return addNode;
}

template <class dt>
quadNode<dt>* SkipList<dt>::AddData(int key, dt data)
{
	quadNode<dt>* newNode = new quadNode<dt>;

	newNode->data.data = data;
	newNode->data.key = key;
	
	if (elements == 0)
	{
		newNode->prev = headhead;
		newNode->next = tailtail;

		headhead->next = newNode;
		tailtail->prev = newNode;

		if (CoinToss())
		{
			quadNode<dt>* upNewNode = new quadNode<dt>;

			upNewNode->down = newNode;
			
			addNewLevel();

			newNode->up = addToLevel(headhead->up, tailtail->up, newNode);
		}
	}
	else
	{
		quadNode<dt>* levelPtr = headhead;

		while (levelPtr->next->data.key < newNode->data.key && levelPtr->next->data.key != maxKeyVal)
		{
			levelPtr = levelPtr->next;
		}

		while(levelPtr->next->data.key == newNode->data.key && levelPtr->next->data.data < newNode->data.data)
		{
			levelPtr = levelPtr->next;
		}

		newNode->next = levelPtr->next;
		newNode->prev = levelPtr;
		levelPtr->next = newNode;
		newNode->next->prev = newNode;

		if (CoinToss())
		{
			quadNode<dt>* upNewNode = new quadNode<dt>;

			upNewNode->down = newNode;
			upNewNode->data.data = newNode->data.data;
			upNewNode->data.key = newNode->data.key;

			if (headhead->up == headtail)
			{
				addNewLevel();
			}

			newNode->up = addToLevel(headhead->up, tailhead->up, upNewNode);
		}
	}

	elements++;
	return newNode;
}

template <class dt>
void SkipList<dt>::removeFromLevel(quadNode<dt>* levelB, quadNode<dt>* levelE, quadNode<dt>* begin)
{
	if (begin->down != NULL)
	{
		begin->next->prev = begin->prev;
		begin->prev->next = begin->next;
		begin->next = NULL;
		begin->prev = NULL;

		removeFromLevel(levelB->down, levelE->down, begin->down);
		delete begin;
	}

	if (&levelB->next == &levelE && &levelE->prev == &levelB)
	{
		removeTopLevel();
	}
}

template <class dt>
void SkipList<dt>::RemoveData(int key)
{
	quadNode<dt>* removeNode = headhead;

	while (removeNode->data.key != key)
	{
		removeNode = removeNode->next;
	}

	quadNode<dt>* topRemove = removeNode;

	while (topRemove->up != NULL)
	{
		topRemove = topRemove->up;
	}

	removeFromLevel(headtail->down, tailtail->down, topRemove);

	removeNode->next->prev = removeNode->prev;
	removeNode->prev->next = removeNode->next;
	removeNode->next = NULL;
	removeNode->prev = NULL;
	delete removeNode;
	elements--;
}

template <class dt>
dat<dt>* SkipList<dt>::GetData(int key)
{
	quadNode<dt>* dataNode = new quadNode<dt>;

	dataNode = headtail;
	dataNode = dataNode->down;

	while (dataNode->down != NULL || dataNode->data.key < maxKeyVal)
	{

		if (dataNode->next->data.key == key)
		{
			return &dataNode->next->data;
		}
		else if (dataNode->next->data.key < key)
		{
			dataNode = dataNode->next;
		}
		else
		{
			if (dataNode->down == NULL)
			{
				return (dat<dt>*)NULL;
			}
			else
			{
				dataNode = dataNode->down;
			}
		}
	}

	return (dat<dt>*)NULL;
}

template <class dt>
void SkipList<dt>::addNewLevel()
{
	quadNode<dt>* beginNode = new quadNode < dt > ;
	quadNode<dt>* endNode = new quadNode < dt > ;

	beginNode->data.key = minKeyVal;
	endNode->data.key = maxKeyVal;

	beginNode->up = headtail;
	beginNode->down = headtail->down;
	headtail->down->up = beginNode;
	headtail->down = beginNode;

	endNode->up = tailtail;
	endNode->down = tailtail->down;
	tailtail->down->up = endNode;
	tailtail->down = endNode;

	beginNode->next = endNode;
	endNode->prev = beginNode;
}

template <class dt>
void SkipList<dt>::removeTopLevel()
{
	quadNode<dt>* tempNode;

	tempNode = headtail->down;
	headtail->down = tempNode->down;
	tempNode->up = NULL;
	tempNode->down = NULL;
	delete tempNode;

	tempNode = tailtail->down;
	tailtail->down = tempNode->down;
	tempNode->up = NULL;
	tempNode->down = NULL;
	delete tempNode;
}

template <class dt>
quadNode<dt>*  SkipList<dt>::GetHead()
{
	return headhead;
}
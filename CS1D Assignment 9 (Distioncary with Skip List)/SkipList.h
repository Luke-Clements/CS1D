
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

private:
	bool operator!=(const quadNode<dt>& node);
	bool CoinToss();

	void addNewLevel();
	void removeTopLevel();

	quadNode<dt>* addToLevel(quadNode<dt>* levelB, quadNode<dt>* levelE, quadNode<dt>* addNode);
	void removeFromLevel(quadNode<dt>* levelB, quadNode<dt>* levelE, quadNode<dt>* base, quadNode<dt>* begin);
	
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
bool SkipList<dt>::operator!=(const quadNode<dt>& node)
{
	if (this->GetData().key != node.data.key)
	{
		return true;
	}
	else
	{
		return false;
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

	cout << "bacon" << endl;
	while (levelPtr->next->data.key != levelE->data.key && levelPtr->next->data.key < addNode->data.key)
	{
		levelPtr = levelPtr->next;
	}

	newNode->prev = levelPtr;
	newNode->next = levelPtr->next;
	
	if (&levelB != &headhead)
	{
		newNode->down = addNode;
	}
	else
	{
		newNode->down = (quadNode<dt>*)NULL;
	}
	
	levelPtr->next = newNode;
	newNode->next->prev = newNode;

	if (CoinToss())
	{
		if (levelB->up == headtail)
		{
			cout << "here" << endl;
			quadNode<dt>* tempHead = new quadNode<dt>;
			quadNode<dt>* tempTail = new quadNode<dt>;

			tempHead->data.key = minKeyVal;
			tempTail->data.key = maxKeyVal;

			tempHead->up = headtail;
			tempHead->down = levelB;
			headtail->down = tempHead;

			tempTail->up = tailtail;
			tempHead->down = levelE;
			tailtail->down = tempTail;

			tempHead->next = tempTail;
			tempTail->prev = tempHead;

			newNode->up = addToLevel(tempHead, tempTail, addNode);
		}
		else
		{
			cout << "here2" << endl;
			newNode->up = addToLevel(levelB->up, levelE->up, addNode);
		}		
	}
	return newNode;
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

		cout << "herebefore" << endl;
		if (CoinToss())
		{
			quadNode<dt>* upNewNode = new quadNode<dt>;
			quadNode<dt>* tempHead = new quadNode<dt>;
			quadNode<dt>* tempTail = new quadNode<dt>;

			tempHead->data.key = minKeyVal;
			tempTail->data.key = maxKeyVal;

			tempHead->up = headtail;
			tempHead->down = headhead;
			headhead->up = tempHead;
			headtail->down = tempHead;

			tempTail->up = tailtail;
			tempHead->down = tailhead;
			tailhead->up = tempTail;
			tailtail->down = tempTail;

			tempHead->next = tempTail;
			tempTail->prev = tempHead;

			upNewNode->down = newNode;
			
			addNewLevel();

			cout << "gothere" << endl;
			newNode->up = addToLevel(tempHead, tempTail, newNode);
		}
	}
	else
	{
		cout << "herebefore2" << endl;
		quadNode<dt>* levelPtr = headhead;

		while (levelPtr->data.key < newNode->data.key && levelPtr->next->data.key != maxKeyVal && levelPtr->next != NULL)
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
void SkipList<dt>::removeFromLevel(quadNode<dt>* levelB, quadNode<dt>* levelE, quadNode<dt>* base, quadNode<dt>* begin)
{
	if (begin != base)
	{
		begin->next->prev = begin->prev;
		begin->prev->next = begin->next;
		begin->next = NULL;
		begin->prev = NULL;

		removeFromLevel(levelB->down, levelE->down, base, begin->down);
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

	removeFromLevel(headtail->down, tailtail->down, removeNode, topRemove);

	removeNode->next->prev = removeNode->prev;
	removeNode->prev->next = removeNode->next;
	removeNode->next = NULL;
	removeNode->prev = NULL;
	delete removeNode;
}

template <class dt>
dat<dt>* SkipList<dt>::GetData(int key)
{
	quadNode<dt>* dataNode = new quadNode<dt>;

	dataNode = headhead;

	while (dataNode->data.key < key && dataNode->next != NULL)
	{
		dataNode = dataNode->next;
	}
		
	if (dataNode->data.key == key)
	{
		return &dataNode->data;
	}

	return (dat<dt>*)NULL;
}

template <class dt>
void SkipList<dt>::addNewLevel()
{
	cout << "add new level" << endl;
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
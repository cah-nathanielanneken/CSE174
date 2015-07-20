#include "IntList.h"
#include <cassert>
#include <iostream>

using namespace std;

IntListNode::IntListNode() {
	data = -1;
	prev = this;
	next = this;
}

void splice(IntListNode* sourceStart, IntListNode* sourceEnd, IntListNode* target) {
	assert(sourceStart != NULL && sourceEnd != NULL && target != NULL);
	IntListNode *sourceStartSentinel = sourceStart->prev, *sourceEndSentinel = 
		sourceEnd->prev, *tempNode = sourceStart;
	int countSourceStart = 0, countSourceEnd = 0;
	bool targetNotWithinRange = true;
	while(sourceStartSentinel->data != -1) {
		sourceStartSentinel = sourceStartSentinel->prev;
		countSourceStart++;
	}
	while(sourceEndSentinel->data != -1) {
		sourceEndSentinel = sourceEndSentinel->next;
		countSourceEnd++;
	}
	assert(sourceStartSentinel == sourceEndSentinel && countSourceStart <= countSourceEnd);
	while(tempNode->next != sourceEnd) {
		if(tempNode->next == target) {
			targetNotWithinRange = false;
		}
	}
	assert(targetNotWithinRange);
	IntListNode* pointBeforeSourceStart = sourceStart->prev;
	IntListNode* pointAfterSourceEnd = sourceEnd->next;
	pointBeforeSourceStart->next = pointAfterSourceEnd;
	pointAfterSourceEnd->prev = pointBeforeSourceStart;


	IntListNode* pointAfterTarget = target->next;
	sourceEnd->next = pointAfterTarget;
	sourceStart->prev = target;

	target->next = sourceStart;
	pointAfterTarget->prev = sourceEnd;
}

IntList::IntList() {
	sentinel = new IntListNode();
}

IntList::~IntList() {
	clear();
	delete sentinel;
	sentinel = NULL;
}

void IntList::push_back(int i) {
	IntListNode * newNode = new IntListNode();
	newNode->data = i;
	IntListNode * pointBeforeSentinel = sentinel->prev;
	pointBeforeSentinel->next = newNode;
	newNode->prev = pointBeforeSentinel;
	newNode->next = sentinel;
	sentinel->prev = newNode;
}

void IntList::pop_back() {
	if(sentinel->next == sentinel) {
		return;
	}
	IntListNode * nodeToBeRemoved = sentinel->prev;
	nodeToBeRemoved->prev->next = sentinel;
	sentinel->prev = nodeToBeRemoved->prev;
	delete nodeToBeRemoved;
	nodeToBeRemoved = NULL;
}

void IntList::clear() {
	while(!isEmpty()) {
		pop_back();
	}
}

bool IntList::isEmpty() {
	if(sentinel->next == sentinel) {
		return true;
	}
	else {
		return false;
	}
}

IntListNode* IntList::head() {
	if(isEmpty()) {
		return NULL;
	}
	return sentinel->next;
}

IntListNode* IntList::tail() {
	if(isEmpty()) {
		return NULL;
	}
	return sentinel->prev;
}

IntListNode* IntList::getSentinel() {
	return sentinel;
}

void IntList::printList() {
	if(isEmpty()) {
		return;
	}
	IntListNode * tempNode = sentinel->next;
	cout << tempNode->data << " ";
	while(tempNode->next != sentinel) {
		tempNode = tempNode->next;
		cout << tempNode->data << " ";
	}
	cout << endl;
}
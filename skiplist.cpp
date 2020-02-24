//
// Created by Melanie Palomino on 02/16/2020
//

#include <climits>
#include <cstdlib>
#include <iostream>
#include <cassert>
#include <time.h>

#include "skiplist.h"

using namespace std;

//overload << operator
ostream& operator<<(ostream& out, const SkipList& skipList) {
    //print until all levels are printed out
    for (int i= skipList.depth - 1; i >= 0; --i) {

        out << "Level: " << i <<  " -- ";

        SkipList::SNode* curr = skipList.frontGuards[i];

        while (curr != nullptr) {

            out << curr->data << ", ";

            curr = curr->next;
        }

        out << endl;
    }
    return out;
}

//set all pointers to node and set data
//constructor for SNode
SkipList::SNode::SNode(int data) {
    this-> data = data;
    next = nullptr;
    prev = nullptr;
    upLevel = nullptr;
    downLevel = nullptr;

}

//constructor for SkipList
SkipList::SkipList(int depth) {
    this -> depth = depth;
    //dynamically allocate array frontGuards and rearGuards
    frontGuards = new SNode*[depth];
    rearGuards = new SNode*[depth];
    //set up front guard and rear guard
    for (int i = 0; i < depth; i++)
    {   // for each level
        // create the front guards
        frontGuards[i] = new SNode(INT_MIN);
        frontGuards[i]->prev = NULL;
        frontGuards[i]->downLevel = (i > 0) ? frontGuards[i - 1] : NULL;
        frontGuards[i]->upLevel  = NULL;
        if (i > 0) frontGuards[i - 1]->upLevel = frontGuards[i];
        // create the rear guards
        rearGuards[i] = new SNode(INT_MAX);
        frontGuards[i]->next = rearGuards[i];
        rearGuards[i]->next = NULL;
        rearGuards[i]->prev = frontGuards[i];
        rearGuards[i]->downLevel = (i > 0) ? rearGuards[i-1] : NULL;
        rearGuards[i]->upLevel = NULL;
        if (i > 0) rearGuards[i-1]->upLevel = rearGuards[i];
    }

}



/*"flips the coin" to see if node is added to next level
 50/50 percent chance each node will be added to next level*/
//If 1, then return true and add to next level
bool SkipList::alsoHigher() const {
    return rand() % 2;
}


/*
  Takes data and add if not duplicated
  checks alsoHigher and adds to next level dependeing on result
*/
//Returns true if succesfully added
bool SkipList::add(int data) {
    //check if data is in list already
    if(contains(data)){
        cout<< "Duplicates not allowed: " << data << endl;
        return false;
    }
    //create nextNode to traverse list
    SNode* nextNode = frontGuards[0]->next;
    //while the next pointer is not null
    //if input is still greater than keep traversing going to the next node
    while(nextNode->next != nullptr && nextNode->data < data){
        nextNode = nextNode -> next;
    }

    SNode* newNode = new SNode(data);
    addBefore(newNode, nextNode);

    SNode* upper = newNode;
    int count = 1;

    while(alsoHigher()){
        while(upper->prev != nullptr){
            upper = upper->prev;
            if(upper->upLevel != nullptr){
                upper = upper->upLevel;
                upper = upper->next;
                SNode *newUpper = new SNode(data);
                addBefore(newUpper,upper);
                newUpper->upLevel = NULL;
                newUpper->downLevel = newNode;
                newNode->upLevel = newUpper;
                count++;
                newNode = newUpper;
                break;
            }
        }

        if (count == depth){
            break;
        }
        alsoHigher();
    }

    return true;
}

//Connects node added to surrounding nodes in list
void SkipList::addBefore(SNode* newNode, SNode* nextNode) {
    assert(newNode != nullptr && nextNode != nullptr  &&  newNode->data < nextNode->data );
    newNode-> next = nextNode;
    newNode-> prev = nextNode->prev;
    newNode->prev->next = newNode;
    nextNode-> prev = newNode;
    assert(newNode->prev->next = newNode);
    assert(newNode->prev->next->data == newNode->data);
    assert (newNode->next == nextNode && nextNode->prev == newNode);
    assert (newNode->prev != nullptr && newNode->prev->data < newNode->data);
}

//destructor to avoid memory leaks
SkipList::~SkipList() {
    clear();
    for(int i = 0; i < depth; i++){
        delete rearGuards[i];
        delete frontGuards[i];
    }
    delete[] rearGuards;
    delete[] frontGuards;
}

void SkipList::clear(){
    for (int i = 0; i < depth; i++)
    {        // for each level
        SNode *temp = frontGuards[i]->next;
        while (temp->next != nullptr)
        {
            SNode* del = temp;
            temp = temp->next;
            delete del;
        }
        frontGuards[i]->next = temp;
    }
}

//Returns true if succesfully removed
bool SkipList::remove(int data) {
    //start pointer at highest level
    SNode* rem = frontGuards[depth-1];
    SNode *del = nullptr;
    //check if in skiplist
    if(!contains(data)){
        return false;
    }
    while(rem != nullptr){
        //look for node to delete it
        while(rem->next->data < data){
            rem = rem->next;
        }
        if(rem->next->data == data){
            del = rem->next;
            rem->next = rem->next->next;
            rem->next->prev = rem;
            rem = rem->downLevel; continue;

        }
        else{
            rem = rem->downLevel;
        }
    }
    delete del;
    return true;
}

//returns true if succesfully located
bool SkipList::contains(int data) {
    SNode* curr = frontGuards[depth-1];
    while(curr != nullptr){
        while(curr->next->data < data){
            curr = curr->next;
        }
        if(curr->next->data == data){
            return true;
        }
        else{
            curr = curr->downLevel;
        }
    }
    return false;
}
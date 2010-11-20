#ifndef _LL_H
#define _LL_H

#include "unit.h"

class LinkedList {
    class Node {
    public:
        Unit *unit;
        Node *next, *prev;
        
        Node(Unit *_unit) : unit(_unit) {}
    };

    public:
        Node *head;
        Node *tail;
    
        void append(Unit *unit){
            Node *node = new Node(unit);
            if(tail){
                node->prev = tail;
                tail->next = node;
            }else{
                head = node;
            }
            tail = node;
        }
    
        /* Only use me initially, probably; I'm slow */
        void insert(Unit *unit){
            Node *ptr = head;
            while(ptr && ptr->unit->getTheta() > unit->getTheta() && ptr->next)
                ptr = ptr->next;

            if(ptr){
                Node *node = new Node(unit);
                node->prev = ptr;
                node->next = ptr->next;
                ptr->next = node;
                
                if(node->next)
                    node->next->prev = node;
                
            } else {
                append(unit);
            }

        }
};



#endif
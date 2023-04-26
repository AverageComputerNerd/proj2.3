#include "Sequence.h"

#include <iostream>
using namespace std;

Sequence::Sequence()
{
    head = nullptr;
    tail = nullptr;
    m_size = 0;
}

Sequence::Sequence(const Sequence& other)
{
    if(other.head == nullptr){
        head = nullptr;
        tail = nullptr;
        m_size = 0;
        return;
    }
    
    head = nullptr;
    tail = nullptr;
    m_size = 0;
    for(int i=0; i<other.size(); i++)
    {
        ItemType t;
        other.get(i, t);
        insert(i, t);
    }
}

Sequence& Sequence::operator=(const Sequence& other)
{
    if (this != &other){
        Sequence temp(other);
        swap(temp);
    }
    return *this;
}

Sequence::~Sequence(){
    Node* p = head;
    while (p != nullptr){
        Node* next = p->next;
        delete p;
        p = next; }
    
    head = nullptr;
    tail = nullptr;
    m_size = 0;
}

bool Sequence::empty() const
{
    if (head==nullptr && tail==nullptr && m_size == 0){ //simply check if theres nothing there
        return true;
    }
    return false;
}

int Sequence::size() const
{
    return m_size;
}

int Sequence::insert (int pos, const ItemType& value)
{
    if(pos > m_size || pos < 0)
    {
        return -1;
    }
    //accounting for extrenous scenarios
    if( pos == 0 && head == nullptr){
        Node* p = new Node;
        p->data = value;
        head = p;
        tail = p;
        p->next = nullptr;
        p->previous = nullptr;
    }
    if (pos == m_size)     {
        Node* p = new Node;
        p->data = value;
        p->next = nullptr;
        p->previous = tail;
        tail->next = p;
        tail = p;
    }
    if(pos == 0 && head != nullptr)
    {
        Node* p = new Node;
        p->data = value;
        p->next = head;
        p->previous = nullptr;
        head->previous = p;
        head = p;
    }
    if (pos > 0 && pos < m_size)
    {
        Node* p = new Node;
        p->data = value;
        
        int ct = 0;
        Node* move = head;
        while (ct != pos) //loop until move is at the pos
        {
            move = move->next;
            ct++;
        }
        p->next = move;
        p->previous = move->previous;
        move->previous->next = p;
        move->previous = p;
    }
    m_size++;
    return pos;
}

int Sequence::insert (const ItemType& value)
{
    Node* toMove = head;
    int pos = 0;
    if (head == nullptr && m_size == 0)
    {
        return (insert(0, value));
    }
    while(toMove != nullptr)
    {
        if(value <= toMove->data)
        {
            break;
        }
        pos++;
        toMove = toMove->next;
    }

    insert(pos, value);
    return pos;
}

bool Sequence::erase (int pos)
{
    if(head == nullptr || tail == nullptr || pos >= m_size || pos < 0 || m_size == 0){
        return false;
    }
    
    //first checking extrenous scenarios
    
    if(pos==0&&m_size!= 0){  //accounting for head when null
        Node* tmp = head;
        head = head->next;
        head->previous = nullptr;
        delete tmp;
        m_size--;
        return true;
    }
    if(pos==0 && m_size==1)  //accunting for 1 element
    {
        Node* tmp = head;
        head = nullptr;
        tail = nullptr;
        delete tmp;
        m_size--;
        return true;
    }
    if(pos == 0 && m_size != 0){  //normal middle part
        Node* tmp = head;
        head = head->next;
        head->previous = nullptr;
        delete tmp;
        m_size--;
        return true;
    }
    if(pos == (m_size - 1) && m_size != 0){ // deleting the tail ptr
        Node* tmp = tail;
        tail = tail->previous;
        tail->next = nullptr;
        delete tmp;
        m_size--;
        return true;
    }
    
    
    Node* toMove = head;
    int count = 0;
    while (count!=pos){
        toMove = toMove->next;
        count++;
    }
    toMove->previous->next = toMove->next;
    toMove->next->previous = toMove->previous;
    delete toMove;
    m_size--;
    return true;
}

int Sequence::remove(const ItemType& value)
{
    if (head == nullptr){
        return 0;}
    
    Node *p = head;
    int pos = 0;
    int count = 0;
    while (p != nullptr){
        if (p->data == value){
            p = p->next;
            erase(pos);
            count++;
            pos--;
        }
        else{
            p = p->next;
            pos++;}
    }
    return count;
}

bool Sequence::get (int pos, ItemType& value) const
{
    if (pos<0||pos>= m_size){
        return false;
    }
    Node* toMove = head;
    for (int i = 0; i != pos; i++){
        toMove = toMove->next;
    }
    value = toMove->data;
    return true;
}

bool Sequence::set (int pos, const ItemType& value)
{
    if (head == nullptr||pos<0||pos>=m_size){
        return false;
    }
    Node* toMove = head;
    int count = 0;
    while (count!=pos){
        toMove = toMove->next;
        count++;
    }
    toMove->data = value;
    return true;
}


int Sequence::find(const ItemType& value) const
{
    Node *p;
    int x = 0;
    for (p=head; p!=nullptr; p=p->next)
    {
        if (p->data == value)
            return x;
        x++;
    }
    return -1;
}

void Sequence::swap (Sequence& other)
{
    Node* tmpH = head;
    head = other.head;
    other.head = tmpH;
    
    Node* tempH = tail;
    tail = other.tail;
    other.tail = tempH;

    int tempSize = m_size;
    m_size = other.m_size;
    other.m_size = tempSize;
}


int subsequence(const Sequence& seq1, const Sequence& seq2)
{
    if(seq1.empty() || seq2.empty()|| seq2.size() > seq1.size())
    {
        return -1;
    }
    ItemType x;
    ItemType y;
    for(int i = 0; i < seq1.size(); i++){
        if ((seq1.size() - seq2.size() - i) < 0){
            break;
        }
        seq1.get(i,x);
        seq2.get(0,y);
        if(x==y){
            for(int j = 0; j<seq2.size(); j++){
                seq1.get(i+j,x);
                seq2.get(j,y);

                if(x!=y){
                    break;
                }
                else if(j==seq2.size() - 1){
                    return i;} //returning index of where the match occured

            } //for loop inner
        } // if
    } //for loop outer
    return -1;  //all else fails, return -1

}

void concatReverse(const Sequence& seq1, const Sequence& seq2, Sequence& result) {
    /*Sequence tmp;

    for (int i = seq1.size() - 1; i >= 0; i--) {
        tmp.insert(seq1[i]);
    }

    for (int i = seq2.size() - 1; i >= 0; i--) {
        tmp.insert(seq2[i]);
    }

    result = tmp; */
}



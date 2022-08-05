#include<iostream>
using namespace std;


//一个LRU需要一些什么呢？
//1. LRU(int capacity)构造函数  
//2. get(key) 获取当前的key所对应的value  
//3. put(key,value)将key value 插入到LRU中

struct Linknode{
    int key;
    int value;
    Linknode *pre;
    Linknode *next;
    Linknode(int _key,int _value):key(_key),value(_value){
        pre = nullptr;
        next = nullptr;
    }
};

class LRUCache{
private:
    unordered_map<int,Linknode*>cache;
    Linknode* head;
    Linknode* tail;
    int size,capacity;
public:
    LRU(int capacity):size(0),capacity(capacity){
        head = new Linknode();
        tail = new Linknode();
        head->next=tail;
        tail->pre =head;  
    }
    int get(int key)
    {
        if(cache.count(key)==0)
           return -1;
        Linknode* node=cache[key];
        movetohead(node);
        return node->val;
    }
    void put(int key,int val)
    {
        if(!cache.count(key))
        {
            Linknode* node = new Linknode(key,value);
            cache[key]=node;
            addtohead(node);
            size++;
            if(size>capacity)
            {
                Linknode* tail_node = tailnode();
                cache.erase(tail_node->key);
                delete tail_node;
                --size;
            }
        }
        else
        {
            cache[key]->value=val;
            movetohead(cache[key]);
        }
    }

    void movenode(Linknode* node)
    {
        node->pre->next=node->next;
        node->next->pre=node->pre;
    }
    void addtohead(Linknode* node)
    {
        node->pre=head;
        node->next=head->next;
        head->next=node;
        node->next->pre=node;
    }

    void movetohead(Linknode* node)
    {
        movenode(node);
        addtohead(node);
    }

};
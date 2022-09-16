#ifndef __HASHTABLE__
#define __HASHTABLE__

#include "HashUtils.h"

// Do not modify the public interface of this class.
// Otherwise, your code will note compile!
template <class T>
class HashTable {
    struct Entry {
        std::string Key;             // the key of the entry
        T Value;   // the value of the entry
        bool Deleted;        // flag indicating whether this entry is deleted
        bool Active;         // flag indicating whether this item is currently used

        Entry() : Key(), Value(), Deleted(false), Active(false) {}
    };

    struct Bucket {
        Entry entries[3];
    };

    int _capacity; // INDICATES THE SIZE OF THE TABLE
    int _size; // INDICATES THE NUMBER OF ITEMS IN THE TABLE

    Bucket* _table; // HASH TABLE
    
    // You can define private methods and variables
    int ssqqrrtt(int whatever);

public:
    // TODO: IMPLEMENT THESE FUNCTIONS.
    // CONSTRUCTORS, ASSIGNMENT OPERATOR, AND THE DESTRUCTOR
    HashTable();
    HashTable(const HashTable<T>& rhs);
    HashTable<T>& operator=(const HashTable<T>& rhs);
    ~HashTable();

    // TODO: IMPLEMENT THIS FUNCTION.
    // INSERT THE ENTRY IN THE HASH TABLE WITH THE GIVEN KEY & VALUE
    // IF THE GIVEN KEY ALREADY EXISTS, THE NEW VALUE OVERWRITES
    // THE ALREADY EXISTING ONE. 
    // IF LOAD FACTOR OF THE TABLE IS BIGGER THAN 0.5,
    // RESIZE THE TABLE WITH THE NEXT PRIME NUMBER.
    void Insert(std::string key, const T& value);

    // TODO: IMPLEMENT THIS FUNCTION.
    // DELETE THE ENTRY WITH THE GIVEN KEY FROM THE TABLE
    // IF THE GIVEN KEY DOES NOT EXIST IN THE TABLE, JUST RETURN FROM THE FUNCTION
    // HINT: YOU SHOULD UPDATE ACTIVE & DELETED FIELDS OF THE DELETED ENTRY.
    void Delete(std::string key);

    // TODO: IMPLEMENT THIS FUNCTION.
    // IT SHOULD RETURN THE VALUE THAT CORRESPONDS TO THE GIVEN KEY.
    // IF THE KEY DOES NOT EXIST, THIS FUNCTION MUST RETURN T()
    T Get(std::string key) const;

    // TODO: IMPLEMENT THIS FUNCTION.
    // AFTER THIS FUNCTION IS EXECUTED THE TABLE CAPACITY MUST BE
    // EQUAL TO newCapacity AND ALL THE EXISTING ITEMS MUST BE REHASHED
    // ACCORDING TO THIS NEW CAPACITY.
    // WHEN CHANGING THE SIZE, YOU MUST REHASH ALL OF THE ENTRIES FROM 0TH ENTRY TO LAST ENTRY
    void Resize(int newCapacity);
    
    // TODO: IMPLEMENT THIS FUNCTION.
    // RETURNS THE AVERAGE NUMBER OF PROBES FOR SUCCESSFUL SEARCH
    double getAvgSuccessfulProbe();
    
    // TODO: IMPLEMENT THIS FUNCTION.
    // RETURNS THE AVERAGE NUMBER OF PROBES FOR UNSUCCESSFUL SEARCH
    double getAvgUnsuccessfulProbe();

    // THE IMPLEMENTATION OF THESE FUNCTIONS ARE GIVEN TO YOU
    // DO NOT MODIFY!
    int Capacity() const;
    int Size() const;
};



template <class T>
HashTable<T>::HashTable() {
    _capacity = 0;
    _size = 0;
    _table = NULL;
}

template <class T>
HashTable<T>::HashTable(const HashTable<T>& rhs) {
    _capacity = rhs._capacity;
    _size = rhs._size;
    if(_capacity == 0){
        _table = NULL;
        return;
    }
    Bucket* niyuv = new Bucket[_capacity];
    Bucket* trv = rhs._table;
    for(int i = 0; i<_capacity; i++)
        niyuv[i] = trv[i];
    _table = niyuv;
}

template <class T>
HashTable<T>& HashTable<T>::operator=(const HashTable<T>& rhs) {
    if(_table)
        delete [] _table;
    _capacity = rhs._capacity;
    _size = rhs._size;
    _table = new Bucket[_capacity];
    Bucket* trv = rhs._table;
    for(int i = 0; i<_capacity; i++)
        _table[i] = trv[i];
    return *this;
}

template <class T>
HashTable<T>::~HashTable() {
    _capacity = 0;
    _size = 0;
    delete [] _table;
    _table = NULL;
}

template <class T>
void HashTable<T>::Insert(std::string key, const T& value) {
    if(_capacity == 0)
        Resize(NextCapacity(_capacity));
    else if( float(_size)/(3*float(_capacity)) > 0.5 )
        Resize(NextCapacity(_capacity));
    int where = Hash(key);
    int root = 1;
    where = where % _capacity;
    Bucket *trv = _table;
    Entry enTry; enTry.Key = key; enTry.Value = value; enTry.Active = true; enTry.Deleted = false;
    while(true){
        for(int i = 0; i<3; i++){
            if(trv[where].entries[i].Deleted || !trv[where].entries[i].Active){
                trv[where].entries[i] = enTry;
                ++_size;
                return;
            }
            else if(trv[where].entries[i].Key == key){
                trv[where].entries[i] = enTry;
                return;
            }
        }
        if(where+root*root>_capacity-1){
            where = (where+root*root)%_capacity;
            root++;
        }
        else
            where = (where+root*root);
    }
}

template <class T>
void HashTable<T>::Delete(std::string key) {
    if(_capacity==0)
        return;
    int where = Hash(key);
    int root = 1;
    where = where % _capacity;
    while(true){
        for(int i = 0; i<3; i++){
            if(_table[where].entries[i].Deleted)
                continue;
            else if(_table[where].entries[i].Key == key){
                _table[where].entries[i].Deleted = true;
                --_size;
                return;
            }
            else if(!_table[where].entries[i].Active)
                return;
        }
        if(where+root*root>_capacity-1){
            where = (where+root*root)%_capacity;
            root++;
        }
        else
            where = (where+root*root);
    }
}

template <class T>
T HashTable<T>::Get(std::string key) const {
    if(_capacity==0)
        return T();
    int where = Hash(key);
    int root = 1;
    where = where % _capacity;
    while(true){
        for(int i = 0; i<3; i++){
            if(_table[where].entries[i].Key == key && !_table[where].entries[i].Deleted)
                return _table[where].entries[i].Value;
            else if(_table[where].entries[i].Deleted)
                continue;
            else if(!_table[where].entries[i].Active)
                return T();
        }
        if(where+root*root>_capacity-1){
            where = (where+root*root)%_capacity;
            root++;
        }
        else
            where = (where+root*root);
    }
}

template <class T>
void HashTable<T>::Resize(int newCapacity) {
    Bucket* niyuv = new Bucket[newCapacity];
    Bucket* old = _table;
    int oldcap = _capacity;
    _size = 0;
    _capacity = newCapacity;
    _table = niyuv;
    for(int i = 0; i<oldcap; i++){
        for(int j = 0; j<3; j++)
            if(old[i].entries[j].Active && !old[i].entries[j].Deleted)
                Insert(old[i].entries[j].Key, old[i].entries[j].Value);
    }
    delete [] old;
}

template <class T>
int HashTable<T>::ssqqrrtt(int whatever){
    for(int i=0; i<whatever; i++)
        if(i*i == whatever)
            return i;
}

template <class T>
double HashTable<T>::getAvgSuccessfulProbe() {
    int proPs = 0;
    for(int i = 0; i<_capacity; i++){
        for(int j = 0; j<3; j++){
            if(_table[i].entries[j].Active && !_table[i].entries[j].Deleted && Hash(_table[i].entries[j].Key)%_capacity == i)
                proPs++;
            else if(_table[i].entries[j].Active && !_table[i].entries[j].Deleted && Hash(_table[i].entries[j].Key)%_capacity > i)
                proPs += 1 + ssqqrrtt(_capacity - Hash(_table[i].entries[j].Key)%_capacity + i);
            else if(_table[i].entries[j].Active && !_table[i].entries[j].Deleted && Hash(_table[i].entries[j].Key)%_capacity < i)
                proPs += 1 + ssqqrrtt(i - Hash(_table[i].entries[j].Key)%_capacity);
        }
    }
    return double(proPs)/double(_size);
}

template <class T>
double HashTable<T>::getAvgUnsuccessfulProbe() {
    int proPs = 0;
    int root = 1;
    int where;
    for(int i = 0 ; i<_capacity; i++){
        where = i;
        while(true){
            if(!_table[where].entries[0].Active){
                ++proPs;
                break;
            }
            else
                ++proPs;
            if(!_table[where].entries[1].Active){
                break;
            }
            if(!_table[where].entries[2].Active){
                break;
            }
            if(where+root*root>_capacity-1){
                where = (where+root*root)%_capacity;
                root++;
            }
            else
                where = (where+root*root);
        }
    }
    return double(proPs)/double(_capacity);
}

template <class T>
int HashTable<T>::Capacity() const {
    return _capacity;
}

template <class T>
int HashTable<T>::Size() const {
    return _size;
}

#endif
//DO NOT CHANGE THIS FILE
//Author: Bo Brinkman
//Date: 2013/07/24
#include "USet.h"


/*
* Note: Just above your template declaration when you use this class, you
* must define method called "hash" that takes a Key as input, and returns
* an unsigned long (which is the hash value)
*
* For example, you might do:
* unsigned long hash(char c){ return 10*((unsigned long)c)%backingArraySize; }
* HashTable<char,int> mySillyTable;
*
* If you don't define an appropriate hash function, the class won't compile.
*/

template <class Key, class T>
class HashTable : public USet < Key, T > {
private:
	class HashRecord {
	public:
		Key k;
		T x;

		//If the slot in the hash table is totally empty, set this to true.
		bool isNull;

		//If the slot used to have something in it, but doesn't now, set
		// isDel to true, and isNull to false. isNull is only for slots
		// that have never been used
		bool isDel;

		HashRecord() { isNull = true; isDel = false; };
	};

public:
	//See USet.h for documentation of these methods
	virtual unsigned long size();
	virtual void add(Key k, T x);
	virtual void remove(Key k);
	virtual T find(Key k);
	virtual bool keyExists(Key k);

	//Initialize all private member variables.
	HashTable();
	//Delete any dynamically allocated memory.
	virtual ~HashTable();

private:
	//A pointer to the array that holds the hash table data
	HashRecord* backingArray;

	//Whenever numItems + numRemoved >= backingArraySize/2, call
	// grow(). grow() should make a new backing array that is twice the
	// size of the old one, similar to what we did in the ArrayQueue
	// lab.
	//Note: You cannot just loop through the old array and copy it to the
	// new one! Since the backing array size has changed, each item will likely
	// map to a different slot in the array. You may just want to use add()
	// after initializing the new array.
	void grow();

	//This helper method should take a key, and return the index for that
	// item within the hash table. If the item already exists, return the
	// index of the existing item. If the item doesn't exist, return the index
	// where it OUGHT to be. This function can then be used as a helper method in
	// your other methods.
	unsigned long calcIndex(Key k);

	unsigned long numItems; //Number of items in the hash table
	unsigned long grows;

	//Note: Ordinarily, these OUGHT to be private. In this case I have
	// made them public for easy of testing.
public:
	unsigned long numRemoved; //Number of slots that have been removed but not re-used. Those that have isDel == true
	unsigned long backingArraySize;
};



//Code from class, myself, and from Dr.Brinkmans feedback.
//You will need this so you can make a string to throw in
//remove
#include <string>

template <class Key, class T>
HashTable<Key, T>::HashTable(){
	numItems = 0;
	numRemoved = 0;
	grows = 0;

	backingArraySize = hashPrimes[grows];
	backingArray = new HashRecord[backingArraySize];

}

template <class Key, class T>
HashTable<Key, T>::~HashTable() {
	delete[] backingArray;
	backingArray = NULL;
}

template <class Key, class T>
unsigned long HashTable<Key, T>::calcIndex(Key k){
	unsigned long i = hash(k);

	for (i; true; i++){
		if (backingArray[i % backingArraySize].k == k || backingArray[i % backingArraySize].isNull){
			return (i % backingArraySize);
		}
	}

	return numItems; //This indicates failure, since it is an impossible value
}

template <class Key, class T>
void HashTable<Key, T>::add(Key k, T x){
	if (keyExists(k)){
		throw std::string("Already exists");
	}

	if (numItems + numRemoved >= backingArraySize / 2){
		grow();
	}

	unsigned long search = hash(k) % backingArraySize;
	while (!backingArray[search].isNull && !backingArray[search].isDel) {
		search = (search + 1) % backingArraySize;
	}

	if (backingArray[search].isNull){
		numItems++;
	}

	if (backingArray[search].isDel){
		numRemoved--;
	}

	backingArray[search].k = k;
	backingArray[search].x = x;
	backingArray[search].isNull = false;
	backingArray[search].isDel = false;

}

template <class Key, class T>
void HashTable<Key, T>::remove(Key k){

	if (calcIndex(k) != numItems){
		backingArray[calcIndex(k)].isDel = true;
		numRemoved++;
		numItems--;
	}

}

template <class Key, class T>
T HashTable<Key, T>::find(Key k){
	if (keyExists(k)){
		return backingArray[calcIndex(k)].x;
	}

	throw std::string("No such key in hash table");
}

template <class Key, class T>
bool HashTable<Key, T>::keyExists(Key k){

	if (backingArray[calcIndex(k)].isNull == true){
		return false;
	}

	else if (backingArray[calcIndex(k)].isDel == false && backingArray[calcIndex(k)].k == k){
		return true;
	}

	return false;

}

template <class Key, class T>
unsigned long HashTable<Key, T>::size(){
	return numItems;
}

template <class Key, class T>
void HashTable<Key, T>::grow(){
	grows++;
	numRemoved = 0;

	backingArraySize = hashPrimes[grows];
	HashRecord* newRecord = new HashRecord[backingArraySize];

	for (unsigned int i = 0; i < hashPrimes[grows - 1]; i++)	{
		if (!backingArray[i].isNull && !backingArray[i].isDel)	{

			unsigned long search = hash(backingArray[i].k) % backingArraySize;
			while (!newRecord[search].isNull)	{
				search = (search + 1) % backingArraySize;
			}
			newRecord[search].k = backingArray[i].k;
			newRecord[search].x = backingArray[i].x;
			newRecord[search].isNull = false;
			newRecord[search].isDel = false;
		}
	}

	delete[] backingArray;
	backingArray = newRecord;
}


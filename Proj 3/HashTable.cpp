#include "HashTable.h"
#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

// comparator used to sort number of deaths in descending order
bool sortByVal(const pair<string, int>& a, const pair<string, int>& b) {
    return (a.second > b.second);
}

// Hash function that gets each character and adds getting a total sum for as a hash code
// with 51 keys, there are no collisions
unsigned int HashTable::hashFunction(const string& key) {
    unsigned int sum = 0;
    for (char i : key) {
        sum += tolower(i);
    }
    return sum;
}

// insert function takes in a key and a pair, inserts it within the hash table, by adding the values in the pair
// to the original
void HashTable::insert(const string& key, pair<int, int> value) {
    unsigned int hashCode = hashFunction(key);
    decoded[hashCode] = key;
    this->hashTable[hashCode].first += value.first;
    this->hashTable[hashCode].second += value.second;
}

// this function was used in testing to find collisions, it was used to find a hash function that would be best fit for
// this data set
int HashTable::numOfCollisions() {
    unordered_map<unsigned int, pair<int, int>>::iterator it;
    map<unsigned int, int> temp;
    int cnt = 0;
    for (it = this->hashTable.begin(); it != this->hashTable.end(); it++) {
        unsigned int hashCode = it->first;
        temp[hashCode]++;
        if (temp[hashCode] > 1) {
            cnt++;
            cout << "COLLISION with state: " << decoded[hashCode] << endl;
        }
    }
    cout << "Number of keys: " << temp.size() << endl;
    return cnt;
}

// search function searches through the hash table and returns true if a value is found for the key given
// and false otherwise
bool HashTable::search(const string& key) {
    unsigned int hashCode = hashFunction(key);
    if (this->hashTable.find(hashCode) != this->hashTable.end()) {
        return true;
    }
    else {
        return false;
    }
}

// function returns the death count given a key
int HashTable::getDeathCount(const string& key) {
    unsigned int hashCode = hashFunction(key);
    return this->hashTable[hashCode].first;
}

// function returns the underage count given a key
int HashTable::getUnderageCount(const string& key) {
    unsigned int hashCode = hashFunction(key);
    return this->hashTable[hashCode].second;
}

// prints out the entire hashtable, used for testing.
void HashTable::print() {
    unordered_map<unsigned int, pair<int, int>>::iterator it;
    for (it = this->hashTable.begin(); it != this->hashTable.end(); it++) {
        cout << "State: " << decoded[it->first] << " | Deaths: " << it->second.first << " | Underage Deaths: " << it->second.second << endl;
    }
}

// returns a vector with the top 10 states with the most gun related casualties
vector<string> HashTable::top10Deaths() {
    unordered_map<unsigned int, pair<int, int>>::iterator it;
    // string is name of state, and int is number of deaths
    vector<string> temp;
    vector<pair<string, int>> vec;
    for (it = this->hashTable.begin(); it != this->hashTable.end(); it++) {
        vec.emplace_back(decoded[it->first], it->second.first);
    }
    // sort the vector by increasing order of its pair's second value
    sort(vec.begin(), vec.end(), sortByVal);

    if (vec.size() < 10) {
        for (int i = 0; i < vec.size(); i++) {
            temp.push_back(vec[i].first);
        }
    }
    else {
        for (int i = 0; i < 10; i++) {
            temp.push_back(vec[i].first);
        }
    }

    return temp;
}

// returns a vector with the top 10 states with the most gun related underage casualties
vector<string> HashTable::top10UnderageDeaths() {
    unordered_map<unsigned int, pair<int, int>>::iterator it;
    // string is name of state, and int is number of deaths
    vector<string> temp;
    vector<pair<string, int>> vec;
    for (it = this->hashTable.begin(); it != this->hashTable.end(); it++) {
        vec.emplace_back(decoded[it->first], it->second.second);
    }
    // // sort the vector by increasing order of its pair's second value
    sort(vec.begin(), vec.end(), sortByVal);
    if (vec.size() < 10) {
        for (int i = 0; i < vec.size(); i++) {
            temp.push_back(vec[i].first);
        }
    }
    else {
        for (int i = 0; i < 10; i++) {
            temp.push_back(vec[i].first);
        }
    }

    return temp;
}
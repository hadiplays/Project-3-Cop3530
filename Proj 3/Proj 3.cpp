#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <queue>
#include <chrono>   
#include "nAry.h"
#include "node.h"
#include "HashTable.h"

using namespace std;

void printViolence(nAry root, HashTable ht);

void printUnderaged(nAry root, HashTable ht);
void searchCity(nAry root, HashTable ht);

int main()
{
    HashTable ht;
    vector<tuple<string, int, int>> d;

    //Open file
    fstream fin;
    fin.open("Gun Violence Data.csv");

    //Declare string inputs
    string row, word;
    string state;
    int underageDeaths, gunViolence;
    vector<string> ages;

    getline(fin, row);
    //While program can input rows of data
    while (getline(fin, row)) {
        underageDeaths = 0;
        ages.clear();

        //Associate string object with stream
        stringstream s(row);

        //Stores state
        getline(s, word, ',');
        state = word;
        //cout << state << endl;

        //Stores fatalities
        getline(s, word, ',');
        gunViolence = stoi(word);
        //cout << gunViolence << endl;

        //Stores ages of those involved 
        getline(s, word, ',');
        string str = word;
        string delimiter = "||";
        size_t pos = 0;
        string token;
        while ((pos = str.find(delimiter)) != std::string::npos) {
            token = str.substr(0, pos);
            //std::cout << token << std::endl;
            ages.push_back(token);
            str.erase(0, pos + delimiter.length());
        }
        //std::cout << str << std::endl;
        ages.push_back(str);


        //Stores which of those involved were killed/injured
        getline(s, word, ',');
        str = word;
        delimiter = "||";
        pos = 0;
        int count = 0;
        int ageSize = ages.size();
        while ((pos = str.find(delimiter)) != std::string::npos) {
            token = str.substr(0, pos);

            if ((count < ageSize) && (ages[count].find("Teen") != string::npos || ages[count].find("Child") != string::npos)
                && (token.find("Killed") != string::npos))
                underageDeaths++;

            count++;
            //std::cout << token << std::endl;
            str.erase(0, pos + delimiter.length());
        }
        //std::cout << str << std::endl;
        if ((ages[ageSize - 1].find("Teen") != string::npos || ages[ageSize - 1].find("Child") != string::npos) &&
            (str.find("Killed") != string::npos))
            underageDeaths++;

        //Inserts a node into nAry tree
        d.push_back(make_tuple(state, gunViolence, underageDeaths));

        // Insert into Hash Table
        pair<int, int> value(gunViolence, underageDeaths);
        ht.insert(state, value);
    }

    nAry root;

    for (int i = 0; i < root.data.size(); i++) {
        for (int j = 0; j < root.data[i].size(); j++) {
            cout << root.data[i][j].state << root.data[i][j].gunViolence << root.data[i][j].underageDeaths << endl;
        }
    }
    root.InsertData(0, d, 0);

    cout << "========================================\n";
    cout << "Welcome to the Gun Violence Indexer v1.0\n";
    cout << "    Brought to you by Team Oomi Zoomi\n";
    cout << "========================================\n";

    while (true) {
        cout << endl << "1. Print Top 10 states by most gun related violence incidents";
        cout << endl << "2. Print Top 10 states by most underaged casualties";
        cout << endl << "3. Search state";
        cout << endl << "0. Exit\n";
        cout << endl << "Select an option: ";

        int input;
        cin >> input;

        switch (input) {
            case 1:
                printViolence(root, ht);
                break;
            case 2:
                printUnderaged(root, ht);
                break;
            case 3:
                searchCity(root, ht);
                break;
            default:
                return 0;
        }
    }
}

void printViolence(nAry root, HashTable ht) {
    cout << endl << "Top 10 states by most gun related violence deaths\n";
    cout << "====================================================\n";
    int cnt = 1;
    for (auto states : ht.top10Deaths()) {
        cout << cnt << ") " << states << endl;
        cnt++;
    }


    cout << endl << "5-Ary Tree Time:\n";
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    root.TopTenStateDeaths();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "Time elapsed: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[microseconds]" << std::endl;

    cout << endl << "Hash Table Time:\n";
    begin = std::chrono::steady_clock::now();
    vector<string> temp = ht.top10Deaths();
    end = std::chrono::steady_clock::now();

    std::cout << "Time elapsed: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[microseconds]" << std::endl;

}

void printUnderaged(nAry root, HashTable ht) {
    cout << endl << "Top 10 states by most underaged deaths\n";
    cout << "==============================================\n";
    int cnt = 1;
    for (auto states : ht.top10UnderageDeaths()) {
        cout << cnt << ") " << states << endl;
        cnt++;
    }
    cout << endl << "5-Ary Tree Time:\n";
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    root.TopTenStateUnderageDeaths();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "Time elapsed: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[microseconds]" << std::endl;

    cout << endl << "Hash Table Time:\n";
    begin = std::chrono::steady_clock::now();
    vector<string> temp = ht.top10UnderageDeaths();
    end = std::chrono::steady_clock::now();

    std::cout << "Time elapsed: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[microseconds]" << std::endl;

}

void searchCity(nAry root, HashTable ht) {
    string state;
    cin >> state;
    cout << endl << "State Information\n";
    cout << "=========================\n";
    if (ht.search(state)) {
        cout << "State: " << state << endl;
        cout << "Gun related deaths: " << ht.getDeathCount(state) << endl;
        cout << "Underage deaths: " << ht.getUnderageCount(state) << endl;
    }
    else {
        cout << "Not found" << endl;
    }
    cout << endl << "5-Ary Tree Time:\n";
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    root.search(state);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "Time elapsed: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[microseconds]" << std::endl;

    cout << endl << "Hash Table Time:\n";
    begin = std::chrono::steady_clock::now();
    ht.search(state);
    end = std::chrono::steady_clock::now();

    std::cout << "Time elapsed: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[microseconds]" << std::endl;
}
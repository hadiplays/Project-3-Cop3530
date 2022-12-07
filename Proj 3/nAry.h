#pragma once
#include <vector>
#include <string>
#include <queue>
#include <tuple>
#include <map>
#include <cmath>
#include "node.h"

using namespace std;

class nAry
{
public:
    vector<vector<Node>> data;
    void InsertData(int count, vector<tuple<string, int, int>>& d, int s);
    void TopTenStateDeaths();
    void TopTenStateUnderageDeaths();
    void search(string state);
};

void nAry::InsertData(int count, vector<tuple<string, int, int>>& d, int s) {

    int c = count;
    int size = s;

    if (size < d.size()) {
        Node node;
        vector<Node> temp;
        for (int i = size; i < size + (pow(5, c)); i++) {

            int z = 0;

            if (i >= d.size()) {
                break;
            }

            for (int j = 0; j < data.size(); j++) {
                for (int k = 0; k < data[j].size(); k++) {
                    if (data[j][k].state == get<0>(d[i])) {
                        data[j][k].gunViolence += get<1>(d[i]);
                        data[j][k].underageDeaths += get<2>(d[i]);
                        z = 1;
                        break;
                    }
                }
            }

            if (z == 0) {
                node.state = get<0>(d[i]);
                node.gunViolence = get<1>(d[i]);
                node.underageDeaths = get<2>(d[i]);

                temp.push_back(node);
            }
        }
        data.push_back(temp);

        //cout << root.data.empty();

        size += pow(5, c);
        c++;
        InsertData(c, d, size);
    }
}

void nAry::TopTenStateDeaths() {
    map<int, string> topTen;
    for (int i = 0; i < data.size(); i++) {
        for (int j = 0; j < data[i].size(); j++) {
            topTen[data[i][j].gunViolence] = data[i][j].state;
        }
    }

    map<int, string>::reverse_iterator itr;
    int count = 1;
    for (itr = topTen.rbegin(); itr != topTen.rend(); itr++) {
        if (count == 11) break;
        /* cout << count << ".) ";
         cout << itr->second << " " << itr->first << endl;*/
        count++;
    }
}

void nAry::TopTenStateUnderageDeaths() {
    map<int, string> topTen;
    for (int i = 0; i < data.size(); i++) {
        for (int j = 0; j < data[i].size(); j++) {
            topTen[data[i][j].underageDeaths] = data[i][j].state;
        }
    }

    map<int, string>::reverse_iterator itr;
    int count = 1;
    for (itr = topTen.rbegin(); itr != topTen.rend(); itr++) {
        if (count == 11) break;
        /*cout << count << ".) ";
        cout << itr->second << " " << itr->first << endl;*/
        count++;
    }
}

void nAry::search(string state) {
    bool found = false;
    for (int i = 0; i < data.size(); i++) {
        for (int j = 0; j < data[i].size(); j++) {
            Node node = data[i][j];
            if ((data[i][j].state) == state) {
                /*       cout << "State: " << node.state << endl;*/
                found = true;
                /*cout << "Gun related deaths: " << node.gunViolence << endl;
                cout << "Underage deaths: " << node.underageDeaths << endl;*/
                return;
            }
        }
    }
    if (!found) {
        /*  cout << "That state does not exist :/" << endl;*/
    }
}
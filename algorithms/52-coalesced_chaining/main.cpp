#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <memory>
#include <vector>

using namespace std;

#include "hashtable.h"

int main() {

    vector<string> words = { "boom", "lessenrooster", "bedrijf", "hond", "telefoon", "laptop", "wandeling", "pennentas", "arbeid", "school", "buienradar" };
    HashTable hashtable(100);

    for (int i = 0; i < words.size(); i++) {
        hashtable.addWord(words[i]);
    }

    hashtable.print();

    return 0;
}
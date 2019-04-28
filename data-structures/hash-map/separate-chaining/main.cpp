#include <iostream>
#include <cassert>
#include "hash_map.h"

using namespace std;

int main() {
    HashMap<int, int> map;

    assert(map.Size() == 0 && "map size should be 0");
    assert(map.Empty() && "map should be empty");
    cout << "Initialization successful!\n";

    auto it = map.Insert(1, 20);
    assert(map.Size() == 1 && "map size should be 1");
    assert(!map.Empty() && "map should be non-empty");
    assert(map.Find(1)->second == 20 && "1 -> 20");
    cout << "Insertion of 1->20 successful!\n";

    it = map.Erase(it);
    assert(map.Size() == 0 && "map size should be 0");
    assert(map.Empty() && "map should be empty");
    cout << "1->20 erased successfully!\n";

    cout << "load factor on empty map: " << map.LoadFactor() << endl;

    for (int i = 0; i < 1000; ++i) {
        map[i] = i;
    }

    cout << "load factor on 1000 element map: " << map.LoadFactor() << endl;
    cout << map.Size() << " " << map.ChainCount() << endl;

    map.MaxLoadFactor(0.4);
    cout << "load factor on 1000 element map with max load factor of 0.4: " << map.LoadFactor() << endl;
    cout << map.Size() << " " << map.ChainCount() << endl;

    cout << "500 -> " << map.Find(500)->second << endl;

    assert(map.Begin() != map.End() && "map.Begin() != map.End() should be true");
    for (auto iter = map.Begin(); iter != map.End(); ++iter) {
        cout << iter->first << ' ' << iter->second <<'\n';
    }

    return 0;
}
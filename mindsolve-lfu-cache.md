# Initial thoughts in 5 mins

// still need a map to get the node references
// we can have a linked list to keep track of the recency
// we should also have buckets to move nodes between frequency

// when getting
// check if !exist if so return -1
// update recency
// move the bucket to its bucket[current frequency + 1]
// we also move use counter to always track the least used item. maybe a min-heap because we always need ordering... but nvm that's not O(1)

# Realizations

we have a LRU per frequency

```cpp
struct Node {
    int key;
    int value;
    int freq;

    // it has the iterator inside!!!!
    list<int>::iterator it;
};

int cap;
int minFreq;

// key -> node info
unordered_map<int, Node> nodes;

// frequency -> LRU list of keys
unordered_map<int, list<int>> freqList;
```

NORTH STAR:

key -> node
freq -> LRU list
minFreq = lowest non-empty frequency
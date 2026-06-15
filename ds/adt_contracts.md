# Abstract Data‐Type (ADT) Contracts for Common Data Structures

Each ADT describes *what* operations are available and how they behave — not *how* they are implemented.  The contracts below describe the behaviour a correct implementation must satisfy.  Comments about typical time‑complexity refer to well‑known implementations but are **not** part of the ADT specification unless explicitly stated.

## Priority Queue
A priority queue stores *items* with an associated *priority key* and always removes the item with extremal priority.  A *min‑priority queue* treats lower keys as higher priority; a *max‑priority queue* treats higher keys as higher priority.

**Core operations** (min‑priority queue is described; replace “minimum” with “maximum” for a max‑priority queue):

| Operation | Description (pre‑/post‑conditions) | Notes |
|---|---|---|
| `create()` | Return an empty priority queue. | Initial state has no elements and a well‑defined ordering criterion. |
| `insert(item, key)` | Add `item` with priority `key`.  After insertion the queue contains all previously stored elements plus `(item,key)`; ordering must be updated so that the minimum key can be found at any time. | For correctness, the key type must be totally ordered. |
| `top()` / `minimum()` | Return (but do not remove) an element whose key is minimal among all stored elements; error if the queue is empty. | Equivalent to `maximum()` in a max‑priority queue. |
| `extractMin()` | Remove and return an element with minimal key; error if empty.  After removal the remaining items still satisfy the priority ordering. | The ADT specifies which item is returned when there are multiple equal keys: implementations should either arbitrarily choose or document stability【794784769158816†L24-L27】. |
| `isEmpty()` | Return true if the queue contains no elements. | Convenience operation. |
| `size()` | Return the number of stored items. | Another convenience operation. |
| Optional: `changeKey(item, newKey)` | If supported, change the key of an existing item and restore the ordering. | Used in algorithms like Dijkstra’s. |
| Optional: `merge(Q)` | Combine two priority queues, returning a new queue containing all items.  Neither `Q` nor the original queue should be modified. | Some heap variants support melding efficiently. |

**Invariants and behaviour.**  A correct implementation must guarantee that `top()`/`extractMin()` always return an element whose priority is minimal.  The internal representation (heap, ordered list, etc.) is hidden from the user; the only visible guarantee is the *heap order property* (every non‑root node has a priority greater than or equal to its parent【462466034918431†L8-L13】).  Items with equal priority may be returned in any order unless a *stable* priority queue is explicitly specified【794784769158816†L24-L28】.

## Graph
A graph ADT represents a set of *vertices* and a collection of *edges* that connect pairs of vertices.  Graphs can be directed or undirected and may allow self‑loops or parallel edges.  The contract below follows typical mutable graph interfaces.

**Core operations**:

| Operation | Behaviour | Notes |
|---|---|---|
| `create(directed = false, allowSelfLoops = false)` | Return an empty graph.  Parameters determine whether edges are directed and whether self‑loops are permitted. | Default is an undirected simple graph. |
| `addNode(v)` | Add vertex `v`.  Return `true` if `v` was not already present and `false` otherwise【217215639719533†L123-L128】. | Vertex equality is determined by the key type’s equality. |
| `removeNode(v)` | Remove vertex `v` and all incident edges.  Return `true` if removal was successful; `false` if `v` was not present【217215639719533†L123-L133】. | After removal, no edges refer to `v`. |
| `nodes()` | Return a collection (e.g. set) of all vertices【217215639719533†L134-L146】. | Used to iterate and determine the number of vertices. |
| `addEdge(u, v)` | Add an edge from `u` to `v`.  In an undirected graph, also add the reverse edge【217215639719533†L152-L160】.  If `allowSelfLoops` is `false`, adding an edge from `u` to `u` raises an error. | Multiple edges may be disallowed depending on the variant. |
| `removeEdge(u, v)` | Remove the edge from `u` to `v` (and the reverse in an undirected graph).  Return `true` if an edge was removed. | Removing a non‑existent edge has no effect. |
| `hasEdge(u, v)` | Return `true` if an edge from `u` to `v` exists【217215639719533†L210-L222】. | Useful for adjacency tests. |
| `successors(v)` / `neighbors(v)` | Return a collection of vertices directly reachable from `v`【217215639719533†L210-L229】. | In undirected graphs this equals the predecessors. |
| `predecessors(v)` | In directed graphs, return vertices with edges pointing to `v`【217215639719533†L230-L234】. |
| `incidentEdges(v)` | Return a collection of edges incident to `v`【217215639719533†L236-L241】. |
| `inDegree(v)` / `outDegree(v)` | Return the number of incoming / outgoing edges of `v`【217215639719533†L249-L255】. |
| `edgeCount()` | Return the number of edges in the graph【217215639719533†L196-L200】. | Often derived from `edges().size()`. |

**Semantics and invariants.**  The graph maintains a set of vertices and edges; adding or removing vertices/edges must preserve the property that edges always connect existing vertices.  The ADT does not prescribe a particular internal representation (adjacency matrix, adjacency list, etc.)【217215639719533†L210-L234】.  In a directed graph, edges are ordered pairs; in an undirected graph, the pair is unordered.  Implementations should specify whether parallel edges or self‑loops are allowed.

## Map (Associative Array)
The map ADT (also called dictionary or associative array) stores *key–value* pairs.  Each key is unique; keys map to at most one value.  Maps differ from hash tables in that a map is an *abstract* specification, while a hash table is a particular implementation that uses hashing to achieve average \(O(1)\) access.

**Core operations**【901013867569893†L115-L127】:

| Operation | Behaviour | Notes |
|---|---|---|
| `create()` | Return an empty map. | The key and value types are specified by type parameters. |
| `put(k, v)` | Insert or update the entry `(k, v)`.  If key `k` is not present, add `(k,v)` to the map; if `k` already exists, replace its associated value with `v`【901013867569893†L115-L117】.  After the call, retrieving `k` yields `v`. | No two entries may share the same key. |
| `remove(k)` | Remove the entry with key `k` from the map and return its associated value; return `null`/signal an error if `k` is not present【901013867569893†L118-L119】. |
| `get(k)` | Return the value associated with key `k`; throw an error if `k` is absent【901013867569893†L121-L124】. | Some languages return a sentinel value instead of throwing. |
| `containsKey(k)` | Return `true` if the map contains an entry for key `k`【901013867569893†L121-L123】. |
| `size()` | Return the number of key–value pairs stored【901013867569893†L118-L121】. |
| `keys()` | Return a collection (often an iterable or list) of all keys【901013867569893†L125-L126】. | The order of keys is unspecified unless using an ordered map. |
| `values()` | Return a collection of all values【901013867569893†L125-L127】.  Multiple keys may map to the same value. |

**Semantics.**  For any key type `K` and value type `V`, a map provides a partial function \(K 	o V\).  `put` establishes or updates this function; `get` queries it; `remove` deletes it.  The ADT requires that keys be comparable for equality.  Multi‑valued mappings (e.g., multimaps) extend this contract to allow multiple values per key.

## Set
A set ADT represents an unordered collection of *distinct* elements.  Unlike a bag, it contains no duplicates, and the order of elements is irrelevant.

**Core operations**【68373382763814†L15-L37】:

| Operation | Behaviour | Notes |
|---|---|---|
| `create()` | Return an empty set. | |
| `insert(x)` | Add element `x` to the set.  If `x` is already present, the set is unchanged【68373382763814†L25-L29】. |
| `remove(x)` | Remove element `x` from the set if present; no effect otherwise. | |
| `contains(x)` | Return `true` if `x` is in the set【68373382763814†L15-L19】. |
| `size()` | Return the number of elements. | |
| `isEmpty()` | Return `true` if the set is empty. | |
| `iterator()` | Return an iterator that can traverse all elements without exposing internal representation【68373382763814†L15-L23】. | |
| `union(S)` | Return a new set containing elements that are in the current set or in `S`【68373382763814†L25-L31】. | The original sets remain unchanged (functional style); mutating union may also be provided. |
| `intersection(S)` | Return a new set containing elements present in *both* sets【68373382763814†L33-L35】. | |
| `difference(S)` | Return a new set containing elements present in the current set but not in `S`【68373382763814†L35-L36】. | |
| `subsetOf(S)` | Return `true` if every element of the current set is also in `S`【68373382763814†L37-L40】. |

**Semantics.**  A set can be thought of as representing membership in a mathematical set.  Order and multiplicity are irrelevant.  Many implementations (hash sets, balanced trees, bitsets) satisfy the contract; performance characteristics may vary.  Some languages allow duplicate elements; such a structure is a *multiset* or *bag*.

## Multiset (Bag)
A multiset (also called a bag) is an unordered collection where duplicates are allowed.  The order of insertion does not matter, and elements may occur multiple times【68373382763814†L15-L19】.

**Core operations**:

| Operation | Behaviour | Notes |
|---|---|---|
| `create()` | Return an empty multiset. | |
| `add(x)` | Add one occurrence of element `x`.  After insertion, the multiplicity of `x` increases by 1. | |
| `remove(x)` | Remove *one* occurrence of `x` if present【68373382763814†L46-L52】.  If `x` is absent, either do nothing or signal an error; both behaviours are acceptable ADT variants【68373382763814†L69-L74】. |
| `contains(x)` | Return `true` if at least one occurrence of `x` exists【68373382763814†L15-L19】. |
| `count(x)` | Return the multiplicity (number of occurrences) of `x`. | Not always provided; can be derived by iterating and counting. |
| `size()` | Return the total number of elements (sum of multiplicities)【68373382763814†L46-L56】. |
| `isEmpty()` | Return `true` if the multiset contains no elements. | |
| `iterator()` | Return an iterator that visits each occurrence. | |

**Extended operations**:

| Operation | Behaviour | Notes |
|---|---|---|
| `removeAll(x)` | Remove *all* occurrences of `x`. | Useful for batch removal. |
| `uniqueElements()` | Return a set of distinct elements. | Allows inspection of the underlying set. |

**Semantics.**  Unlike a set, a multiset tracks the multiplicity of each element.  A bag is often implemented with a dynamic array, linked list, hash table, or balanced tree.  The ADT does not prescribe the order in which iterations return elements.

## Queue
A queue is a linear collection that supports insertion at one end (the *rear*) and removal from the other end (the *front*).  It enforces the *First‑In, First‑Out* (FIFO) discipline【533506665879605†L196-L216】.

**Core operations**:

| Operation | Behaviour | Notes |
|---|---|---|
| `create()` | Return an empty queue. | |
| `enqueue(x)` | Insert element `x` at the rear【533506665879605†L206-L213】. | |
| `dequeue()` | Remove and return the element at the front of the queue; error if the queue is empty【533506665879605†L206-L214】. | |
| `peek()` | Return the front element without removing it【533506665879605†L214-L215】. | |
| `size()` | Return the number of elements in the queue【533506665879605†L216-L217】. | |
| `isEmpty()` | Return `true` if the queue contains no elements【533506665879605†L216-L217】. | |

**Semantics.**  A queue models lines in real life (e.g., waiting lines).  Elements leave in the same order they were inserted.  Implementations often use arrays (circular buffer), linked lists, or two stacks.  The ADT contract does not restrict capacity unless a bounded queue is specified.

## Stack
A stack is a linear collection in which insertion and removal occur only at one end (the *top*).  It follows the *Last‑In, First‑Out* (LIFO) discipline【533506665879605†L174-L190】.

**Core operations**:

| Operation | Behaviour | Notes |
|---|---|---|
| `create()` | Return an empty stack. | |
| `push(x)` | Insert element `x` onto the top of the stack【533506665879605†L186-L187】. | |
| `pop()` | Remove and return the top element; error if the stack is empty【533506665879605†L186-L189】. | |
| `peek()` | Return the top element without removing it【533506665879605†L189-L190】. | |
| `size()` | Return the number of elements【533506665879605†L191-L192】. | |
| `isEmpty()` | Return `true` if the stack is empty【533506665879605†L191-L193】. | |

**Semantics.**  A stack models scenarios where the most recently added item is processed first (e.g., undo operations, expression evaluation).  Many languages provide dynamic stacks; fixed‑size stacks may include an `isFull()` operation【533506665879605†L191-L194】.

## Deque (Double‑Ended Queue)
A deque generalises both stacks and queues by allowing insertion and removal at *both* ends.  Elements can be added or removed from the front and back independently【23553875089415†L2228-L2308】.

**Core operations**【23553875089415†L2228-L2308】:

| Operation | Behaviour | Notes |
|---|---|---|
| `create()` | Return an empty deque. | |
| `addFront(x)` | Insert element `x` at the front of the deque【23553875089415†L2228-L2308】. | |
| `addBack(x)` | Insert element `x` at the back of the deque【23553875089415†L2228-L2308】. | |
| `removeFront()` | Remove and return the front element; precondition: not empty【23553875089415†L2228-L2308】. | |
| `removeBack()` | Remove and return the back element; precondition: not empty【23553875089415†L2283-L2307】. | |
| `peekFront()` | Return the front element without removing it; precondition: not empty【23553875089415†L2298-L2305】. | |
| `peekBack()` | Return the back element without removing it; precondition: not empty【23553875089415†L2304-L2307】. | |
| `isEmpty()` | Return `true` if the deque contains no elements【23553875089415†L2291-L2297】. | |
| Optional: `size()` | Return the number of elements. | |

**Semantics.**  A deque can behave as a queue (`addBack`/`removeFront`) or a stack (`addFront`/`removeFront` or `addBack`/`removeBack`).  The ADT contract does not specify ordering beyond these end‑based operations.  Implementations include doubly‑linked lists and circular buffers.

## Relationship to Implementations (e.g., Hash Tables)
The operations above define the *interface* and behaviour.  Many data structures implement these ADTs:

- **Priority queue:** binary heap, binomial heap, Fibonacci heap, pairing heap, etc.  The ADT contract remains the same; performance differs.  For example, heaps maintain the heap order property【462466034918431†L8-L13】 to ensure that `top` is at the root.
- **Map:** can be implemented using hash tables, balanced search trees, tries or skip lists.  Hash tables provide average constant‑time `put`/`get`/`remove` but do not maintain key order.
- **Set:** typically uses hash tables (`HashSet`), balanced trees (`TreeSet`), or bitsets.  These maintain uniqueness and support union/intersection operations【68373382763814†L25-L37】.
- **Multiset:** sometimes implemented using hash tables mapping each element to a count, or via balanced trees; duplicates are preserved.
- **Queue/Stack/Deque:** implemented with arrays or linked lists; deques often use circular buffers or doubly linked lists.

By separating the ADT contract from the implementation, computer scientists can reason about correctness and complexity at a high level before selecting an appropriate data structure.

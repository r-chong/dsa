// TIP: mark something visited when you enqueue it, not when you dequeue it.

queue<T> q;
unordered_set<T> visited;

q.push(start);
visited.insert(start);

while (!q.empty()) {
    int levelSize = q.size();

    while (levelSize--) {
        T curr = q.front();
        q.pop();

        for (T next : neighbors(curr)) {
            if (!visited.contains(next)) {
                visited.insert(next);
                q.push(next);
            }
        }
    }
}
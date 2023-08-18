#include "../contest/template.cpp"

template<typename T> struct min_queue {
    int added = 0, removed = 0;
    deque<pair<T, int>> q;

    T max() { return q.front().first; }

    void add(T val) {
        while (!q.empty() && q.back().first > val) q.pop_back();
        q.push_back({val, added});
        added++;
    }

    void pop() {
        if (!q.empty() && q.front().second == removed) q.pop_front();
        removed++;
    }
};


#ifndef PAIR_H
#define PAIR_H

template <typename T>
class Pair {
public:
    Pair(T* first, T* second) : first(first), second(second) {}

    T* getFirst() const { return first; }
    T* getSecond() const { return second; }

    T* operator[](int index) const {
        if (index == 1) return first;
        if (index == 2) return second;
        return nullptr;
    }

private:
    T* first;
    T* second;
};

#endif // PAIR_H
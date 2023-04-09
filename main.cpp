#include <iostream>

using namespace std;

#ifndef Data
#define Data
/*
    Notes: 
        BSort doesn't work on objects without > operator support
        InverseBSort doesn't work on objects without < operator support
*/
template <class ListType>
class List {
    protected:
        ListType* listElements;
    public:
        int size, capacity;
        List() {
            size = 0;
            capacity = 1;
            listElements = new ListType[capacity];
        }
        List(int startCapacity) {
            size = 0;
            capacity = startCapacity;
            listElements = new ListType[capacity];
        }
        void Add(ListType data) {
            if (size + 1 > capacity) {
                SetCapacity(capacity + 1);
            }
            listElements[size] = data;
            size++;
        }
        ListType Pop (int index) {
            ListType removed;
            removed = listElements[index];
            Remove(index);
            return removed;
        }
        void SetCapacity(int cap) {
            capacity = cap;
            ListType* buf = new ListType[capacity];
            for (int i = 0; i < size; i++) {
                buf[i] = listElements[i];
            }
            delete listElements;
            listElements = new ListType[capacity];
            for (int i = 0; i < size; i++) {
                listElements[i] = buf[i];
            }
            delete buf;
        }
        void Remove() {
            listElements[size-1] = 0;
            size--;
        }
        void Remove(int index) {
            for (int i = index; i < size; i++) {
                listElements[i] = listElements[i+1];
            }
            listElements[size-1] = 0;
            size--;
        }
        ListType* ToArray() {
            return listElements;
        }
        void BSort() {
            int times = 0;
            ListType buf;
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size-times-1; j++) {
                    if (listElements[j] > listElements[j+1]) {
                        buf = listElements[j];
                        listElements[j] = listElements[j+1];
                        listElements[j+1] = buf;
                    }
                }
                times++;
            }
        }
        void InversedSSort() {
            int times = 0;
            ListType smallest;
            ListType biggest;
            List<ListType> sorted;
            List<ListType> unsorted = *this;
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size-times; j++) {
                    if (unsorted[j] < smallest) {
                        smallest = unsorted[j];
                    }
                    if (unsorted[j] > biggest) {
                        biggest = unsorted[j];
                    }
                }
                sorted.Add(smallest);
                cout << smallest << " - " << unsorted.Index(smallest) << endl;
                unsorted.Remove(unsorted.Index(smallest));
                smallest = biggest;
                times++;
            }
            listElements = sorted.ToArray();
        }
        void InverseBSort() {
            int times = 0;
            ListType buf;
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size-times-1; j++) {
                    if (listElements[j] < listElements[j+1]) {
                        buf = listElements[j];
                        listElements[j] = listElements[j+1];
                        listElements[j+1] = buf;
                    }
                }
                times++;
            }
        }
        void Reverse() {
            ListType* old = new ListType[size];
            for (int i = 0; i < size; i++) {
                old[i] = listElements[i];
            }
            for (int i = 0; i < size; i++) {
                listElements[i] = old[size-i-1];
            }
        }
        ListType PullFront () {
            return Pop(0);
        }
        ListType PullBack () {
            return Pop(size-1);
        }
        void Fit() {
            SetCapacity(size);
        }
        bool Contains(ListType element) {
            for (int i = 0; i < size; i++) {
                if (listElements[i] == element) {
                    return true;
                }
            }
            return false;
        }
        int Index(ListType element) {
            for (int i = 0; i < size; i++) {
                if (listElements[i] == element) {
                    return i;
                }
            }
            return -1;
        }
        int Count(ListType element) {
            int counter = 0;
            for (int i = 0; i < size; i++) {
                if (listElements[i] == element) {
                    counter++;
                }
            }
            return counter;
        }
        void Clear() {
            for (int i = 0; i < size; i++) {
                listElements[i] = 0;
            }
            SetCapacity(1);
            size = 0;
        }
        double freq(ListType element) {
            if (Count(element) == 0) {
                return -1;
            }
            return (double) Count(element) / (double) size;
        }
        ListType operator[] (int index) const {
            return listElements[index];
        }
        ListType & operator[] (int index) {
            return listElements[index];
        }
        List operator+ (ListType element) {
            List<ListType> buf(size+1);
            for (int i = 0; i < size; i++) {
                buf.Add(listElements[i]);
            }
            buf.Add(element);
            return buf;
        }
        void operator+= (ListType element) {
            Add(element);
        }
        List operator+ (List element) {
            List<ListType> buf(size+element.size);
            for (int i = 0; i < size; i++) {
                buf.Add(listElements[i]);
            }
            for (int i = 0; i < element.size; i++) {
                buf.Add(element.listElements[i]);
            }
            return buf;
        }
        void operator+= (List element) {
            for (int i = 0; i < element.size; i++) {
                Add(element.listElements[i]);
            }
        }
        void operator-= (ListType element) {
            if (!Contains(element)) {
                return;
            }
            Remove(Index(element));
        }
        List operator- (ListType element) {
            List<ListType> buf(size-2);
            buf.ToArray() = ToArray();
            if (!Contains(element)) {
                return buf;
            }
            buf.Remove(Index(element));
            return buf;
        }
};
/*
    Note: sort doesn't work on objects without > operator support 
*/
template <class ListType>
class Stack : List<ListType> {
    public:
        Stack(int startCapacity) {
            this->size = 0;
            this->capacity = startCapacity;
            this->listElements = new ListType[this->capacity];
        }
        void Add(ListType data) {
            if (this->size + 1 > this->capacity) {
                this->SetCapacity(this->capacity + 1);
            }
            ListType* old = new ListType[this->capacity];
            for (int i = 0; i < this->size; i++) {
                old[i] = this->listElements[i];
            }
            for (int i = 0; i < this->size; i++) {
                this->listElements[i+1] = old[i];
            }
            this->listElements[0] = data;
            this->size++;
        }
};
/*
    Note: sort doesn't work on objects without > operator support 
*/
template <class ListType>
class Queue : List<ListType>{
    public:
        Queue(int startCapacity) {
            this->size = 0;
            this->capacity = startCapacity;
            this->listElements = new ListType[this->capacity];
        }
        void Remove() {
            for (int i = 0; i < this->size; i++) {
                this->listElements[i] = this->listElements[i+1];
            }
            this->size--;
        }
};

template <class ListType>
struct LinkedList {
    ListType value;
    LinkedList* next = NULL;
};

template <class ListType>
struct DoubleLinkedList {
    ListType value;
    DoubleLinkedList* next = NULL;
    DoubleLinkedList* prev = NULL;
};

#endif
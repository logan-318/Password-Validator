#include "Heap.h"

void MinHeap::heapifyUp(int index) {
    while (index && heapArray[parent(index)].priority > heapArray[index].priority) {
        std::swap(heapArray[index], heapArray[parent(index)]);
        index = parent(index);
    }
}

//Default constructor for MinHeap
MinHeap::MinHeap() : heapArray() {
}

void MinHeap::heapifyDown(int index) {
    int smallest = index;
    int left = leftChild(index);
    int right = rightChild(index);

    if (left < size() && heapArray[left].priority < heapArray[smallest].priority)
        smallest = left;

    if (right < size() && heapArray[right].priority < heapArray[smallest].priority)
        smallest = right;

    if (smallest != index) {
        std::swap(heapArray[index], heapArray[smallest]);
        heapifyDown(smallest);
    }
}

void MinHeap::insert(const std::string& pwd, int position) {
    heapArray.emplace_back(pwd, position);
    int index = size() - 1;
    heapifyUp(index);
}

HeapNode MinHeap::extractMin() {
    if (size() == 0) //Check if the heap has no nodes
        std::cout << "Size 0" << std::endl;

    HeapNode root = heapArray[0];

    heapArray[0] = heapArray.back();
    heapArray.pop_back();

    if (size() > 0)
        heapifyDown(0);

    return root;
}

void MinHeap::displayHeap() const {
    std::cout << "Heap contents (password: priority):" << std::endl;
    for (const auto& node : heapArray) {
        std::cout << node.password << ": " << node.priority << std::endl;
    }
}

bool findPassword(const MinHeap& heap, const std::string& targetPassword) {
    MinHeap heapCopy = heap; //Make a copy of the heap
    bool found = false;

    //Keeps extracting Min until password matches targetPassword
    while (heapCopy.size() > 0) {
        HeapNode minNode = heapCopy.extractMin();
        if (minNode.password == targetPassword) {
            found = true;
            break;
        }
    }

    return found;
}
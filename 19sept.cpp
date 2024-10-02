// 19sept.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <memory>

template<typename T>
class LinkedList {
private:
    struct Node {
        T data;
        std::shared_ptr<Node> next;

        Node(T value) : data(value), next(nullptr) {}
    };

    std::shared_ptr<Node> head;
    std::shared_ptr<Node> tail;
    size_t list_size;

public:
    LinkedList() : head(nullptr), tail(nullptr), list_size(0) {}

    void push_front(T value) {
        auto new_node = std::make_shared<Node>(value);
        if (is_empty()) {
            head = tail = new_node;
        }
        else {
            new_node->next = head;
            head = new_node;
        }
        ++list_size;
    }

    void push_back(T value) {
        auto new_node = std::make_shared<Node>(value);
        if (is_empty()) {
            head = tail = new_node;
        }
        else {
            tail->next = new_node;
            tail = new_node;
        }
        ++list_size;
    }
    void pop_front() {
        if (is_empty()) {
            throw std::runtime_error("List is empty");
        }
        head = head->next;
        if (head == nullptr) {
            tail = nullptr; 
        }
        --list_size;
    }

    void pop_back() {
        if (is_empty()) {
            throw std::runtime_error("List is empty");
        }
        if (head == tail) {
            head = tail = nullptr;
        }
        else {
            auto current = head;
            while (current->next != tail) {
                current = current->next;
            }
            current->next = nullptr;
            tail = current;
        }
        --list_size;
    }

    bool find(T value) {
        auto current = head;
        while (current) {
            if (current->data == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void remove(T value) {
        if (is_empty()) {
            return;
        }

        if (head->data == value) {
            pop_front();
            return;
        }

        auto current = head;
        while (current->next && current->next->data != value) {
            current = current->next;
        }

        if (current->next) {
            if (current->next == tail) { 
                tail = current;
            }
            current->next = current->next->next;
            --list_size;
        }
    }


    void print() {
        auto current = head;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }


    bool is_empty() const {
        return list_size == 0;
    }

    size_t size() const {
        return list_size;
    }
};

int main() {
    LinkedList<int> list;

    list.push_front(1);
    list.push_back(2);
    list.push_back(3);
    list.push_front(0);
    list.print();

    list.pop_front();
    list.print(); 

    list.pop_back();
    list.print(); 

    std::cout << "Find 1: " << (list.find(1) ? "Found" : "Not Found") << std::endl; 
    std::cout << "Find 2: " << (list.find(2) ? "Found" : "Not Found") << std::endl; 

    list.remove(1);
    list.print();

    std::cout << "Is empty: " << (list.is_empty() ? "Yes" : "No") << std::endl;
    std::cout << "Size: " << list.size() << std::endl; 

    return 0;
}
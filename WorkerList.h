
#ifndef WORKER_LIST_H
#define WORKER_LIST_H

#include "Worker.h"
#include <cstddef>

// Класс для управления динамическим списком работников
class WorkerList {
private:
    // Узел односвязного списка с данными работника
    struct Node {
        Worker data;
        Node* next;

        // Конструктор узла с указателем на следующий элемент
        explicit Node(const Worker& worker,
            Node* nextNode = nullptr);
    };

    // Указатель на первый элемент и количество работников
    Node* head_;
    std::size_t size_;

    // Получение узла списка по индексу
    Node* nodeAt(std::size_t index);
    const Node* nodeAt(std::size_t index) const;

    void sortAlphabetically();

public:
    WorkerList();

    WorkerList(const WorkerList& other);

    WorkerList& operator=(const WorkerList& other);

    ~WorkerList();

    std::size_t size() const;

    void insert(std::size_t index,
        const Worker& worker);

    void edit(std::size_t index,
        const Worker& worker);

    void remove(std::size_t index);

    void printAll() const;

    // Поиск и вывод работников со стажем больше заданного
    void printWithExperienceGreaterThan(
        int years, int currentYear) const;

    void clear();
};

#endif
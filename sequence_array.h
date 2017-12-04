#pragma once
#include "sequence.h"


template <typename T> class SeqArray : public Sequence<T>
  {
  public:


    SeqArray();
    SeqArray(const T& element);
    SeqArray(T* const elements, unsigned int size);
    ~SeqArray();

    SeqType getType() const;
    //получить длину списка
    unsigned int getLength() const;
    bool isEmpty() const;
    //добавить новый элемент с значением value в конец списка
    void push_back( const T& value );
    //добавить новый элемент с значением value в начало списка
    void push_front( const T& value );

    //удалить последний элемент списка
    void pop_back();
    //удалить первый элемент списка
    void pop_front();

    //отчистить список, удалить данные, освободить память
    void clear();

    //удалить элемент списка с индексом i
    bool eraseItem(unsigned int i);
    //добавить элемент списка с индексом i, предыдущий элемент с индексом i сдвигается вправо 
    /// как быть если i выходит за пределы длины списка??? на текущий момент возвращает false
    bool insertItem(const T& value, unsigned int i);

    //записать значение элемента списка под индексом i в переменную ret_val
    bool getItem(T& ret_val, unsigned int i) const;
    //записать значение value в i-ый элемент списка
    bool setItem(const T& value, unsigned int i);

    //сортировка списка по возрастанию значения
    void sort(const SortMethod& method);
    //получить подмножество массива согласно заданным свойствам: 
    //[i_begin, i_end] диапазон элементов для обработки;
    void getSubSeq(Sequence<T>* sub_list, unsigned int i_begin, unsigned int i_end);

    bool clone(Sequence* seq);
    //слияние списка other с текущим
    void merge(const Sequence<T>& other );

    void fromVec(const std::vector<T>& data);
    bool compareVec(const std::vector<T>& data);

    //перегрузка конструктора копирования
    SeqArray(const SeqArray & other);
    //перегрузка оператора присваивания
    SeqArray& operator = (const SeqArray& other );
    //перегрузка бинарного оператора + конкатенация списков
    SeqArray operator + (const SeqArray &v);
    //перегрузка оператора [] для доступа к элементу списка
    T & operator [] (unsigned int i);

  private:
    void BubbleSortArray();
    void mergeSortArray();
    void RadixSortArray();
    //указатель на начало массива
    T* p_array;
    //кол-во элементов в массиве
    unsigned int n_size;
  };
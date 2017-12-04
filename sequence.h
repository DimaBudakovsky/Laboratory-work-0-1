#pragma once

#include<vector>

enum SeqType
{
  No = 0,
  LinkList=1,
  Array=2
};


enum SortMethod
{
  BubbleSort = 0,
  MergeSort = 1,
  RadixSort = 2
};

template <typename T> class Sequence
{
public:
  //получить длину списка
  virtual SeqType getType() const = 0;
  //получить длину списка
  virtual unsigned int getLength() const = 0;
  //Признак того, является ли последовательность пустой
  virtual bool isEmpty() const = 0;
  //добавить новый элемент с значением value в конец списка
  virtual void push_back( const T& value ) = 0;
  //добавить новый элемент с значением value в начало списка
  virtual void push_front( const T& value ) = 0;
  //Копирование по указателю
  virtual bool clone(Sequence* seq) = 0;

  //удалить последний элемент списка
  virtual void pop_back() = 0;
  //удалить первый элемент списка
  virtual void pop_front() = 0;

  //отчистить список, удалить данные, освободить память
  virtual void clear() = 0;

  //удалить элемент списка с индексом i
  virtual bool eraseItem(unsigned int i) = 0;
  //добавить элемент списка с индексом i, предыдущий элемент с индексом i сдвигается вправо 
  /// как быть если i выходит за пределы длины списка??? на текущий момент возвращает false
  virtual bool insertItem(const T& value, unsigned int i) = 0;

  //записать значение элемента списка под индексом i в переменную ret_val
  virtual bool getItem(T& ret_val, unsigned int i) const = 0;
  //записать значение value в i-ый элемент списка
  virtual bool setItem(const T& value, unsigned int i) = 0;

  //сортировка списка по возрастанию значения
  virtual void sort(const SortMethod& method) = 0;

  //получить подмножество последовательности согласно заданным свойствам: 
  //[i_begin, i_end] диапазон элементов для обработки;
  virtual void getSubSeq(Sequence<T>* sub_list, unsigned int i_begin, unsigned int i_end) = 0;

  virtual void fromVec(const std::vector<T>& data) = 0;
  virtual bool compareVec(const std::vector<T>& data) = 0;

  //перегрузка оператора [] для доступа к элементу списка
  virtual T & operator [] (unsigned int i) = 0;

};
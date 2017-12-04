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
  //�������� ����� ������
  virtual SeqType getType() const = 0;
  //�������� ����� ������
  virtual unsigned int getLength() const = 0;
  //������� ����, �������� �� ������������������ ������
  virtual bool isEmpty() const = 0;
  //�������� ����� ������� � ��������� value � ����� ������
  virtual void push_back( const T& value ) = 0;
  //�������� ����� ������� � ��������� value � ������ ������
  virtual void push_front( const T& value ) = 0;
  //����������� �� ���������
  virtual bool clone(Sequence* seq) = 0;

  //������� ��������� ������� ������
  virtual void pop_back() = 0;
  //������� ������ ������� ������
  virtual void pop_front() = 0;

  //��������� ������, ������� ������, ���������� ������
  virtual void clear() = 0;

  //������� ������� ������ � �������� i
  virtual bool eraseItem(unsigned int i) = 0;
  //�������� ������� ������ � �������� i, ���������� ������� � �������� i ���������� ������ 
  /// ��� ���� ���� i ������� �� ������� ����� ������??? �� ������� ������ ���������� false
  virtual bool insertItem(const T& value, unsigned int i) = 0;

  //�������� �������� �������� ������ ��� �������� i � ���������� ret_val
  virtual bool getItem(T& ret_val, unsigned int i) const = 0;
  //�������� �������� value � i-�� ������� ������
  virtual bool setItem(const T& value, unsigned int i) = 0;

  //���������� ������ �� ����������� ��������
  virtual void sort(const SortMethod& method) = 0;

  //�������� ������������ ������������������ �������� �������� ���������: 
  //[i_begin, i_end] �������� ��������� ��� ���������;
  virtual void getSubSeq(Sequence<T>* sub_list, unsigned int i_begin, unsigned int i_end) = 0;

  virtual void fromVec(const std::vector<T>& data) = 0;
  virtual bool compareVec(const std::vector<T>& data) = 0;

  //���������� ��������� [] ��� ������� � �������� ������
  virtual T & operator [] (unsigned int i) = 0;

};
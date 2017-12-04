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
    //�������� ����� ������
    unsigned int getLength() const;
    bool isEmpty() const;
    //�������� ����� ������� � ��������� value � ����� ������
    void push_back( const T& value );
    //�������� ����� ������� � ��������� value � ������ ������
    void push_front( const T& value );

    //������� ��������� ������� ������
    void pop_back();
    //������� ������ ������� ������
    void pop_front();

    //��������� ������, ������� ������, ���������� ������
    void clear();

    //������� ������� ������ � �������� i
    bool eraseItem(unsigned int i);
    //�������� ������� ������ � �������� i, ���������� ������� � �������� i ���������� ������ 
    /// ��� ���� ���� i ������� �� ������� ����� ������??? �� ������� ������ ���������� false
    bool insertItem(const T& value, unsigned int i);

    //�������� �������� �������� ������ ��� �������� i � ���������� ret_val
    bool getItem(T& ret_val, unsigned int i) const;
    //�������� �������� value � i-�� ������� ������
    bool setItem(const T& value, unsigned int i);

    //���������� ������ �� ����������� ��������
    void sort(const SortMethod& method);
    //�������� ������������ ������� �������� �������� ���������: 
    //[i_begin, i_end] �������� ��������� ��� ���������;
    void getSubSeq(Sequence<T>* sub_list, unsigned int i_begin, unsigned int i_end);

    bool clone(Sequence* seq);
    //������� ������ other � �������
    void merge(const Sequence<T>& other );

    void fromVec(const std::vector<T>& data);
    bool compareVec(const std::vector<T>& data);

    //���������� ������������ �����������
    SeqArray(const SeqArray & other);
    //���������� ��������� ������������
    SeqArray& operator = (const SeqArray& other );
    //���������� ��������� ��������� + ������������ �������
    SeqArray operator + (const SeqArray &v);
    //���������� ��������� [] ��� ������� � �������� ������
    T & operator [] (unsigned int i);

  private:
    void BubbleSortArray();
    void mergeSortArray();
    void RadixSortArray();
    //��������� �� ������ �������
    T* p_array;
    //���-�� ��������� � �������
    unsigned int n_size;
  };
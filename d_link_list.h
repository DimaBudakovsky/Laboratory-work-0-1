#pragma once
#include <vector>

//��������������� ����� ��� ���������� ������
template <typename T> class Node
{
  public:
    Node();
    Node(T obj, Node<T>* prev_data = nullptr, Node<T>* next_data = nullptr);
    ~Node();

    T& data();

    bool setData(const T obj);
    T getData();

    bool setPrev(Node* prev_data);
    Node* getPrev();

    bool setNext(Node* next_data);
    Node* getNext();

  private:
    T m_data;
    Node* p_prev;
    Node* p_next;
};

//������ ������ SequenceIter ��� ������ ����������� ������ �� �������� �����
template <typename T> class SequenceIter
{
public:
  SequenceIter();

  SequenceIter(Node<T>* item);
  //�������� �� ������� ��������
  bool isListIterNull();

  ~SequenceIter();

  SequenceIter& operator++(int); // postfix A++

  SequenceIter& operator--(int);// postfix A--

  //���������� ��������� ������������� ���������
  T& operator *();

private:
  Node<T>* p_item;
};

template <typename T> class Sequence
{
public:
  //�������� �������� �� ������ ������� ������
  virtual SequenceIter<T> begin() = 0;

  //�������� �������� �� ��������� ������� ������
  virtual SequenceIter<T> end() = 0;

  //�������� ����� ������
  virtual unsigned int getLength() const = 0;
  //�������� ����� ������� � ��������� value � ����� ������
  virtual void push_back( const T& value ) = 0;
  //�������� ����� ������� � ��������� value � ������ ������
  virtual void push_front( const T& value ) = 0;

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


};

template <typename T> class DLinkList : public Sequence<T>
{
public:
  DLinkList();
  ~DLinkList();

  //�������� �������� �� ������ ������� ������
  SequenceIter<T> begin();

  //�������� �������� �� ��������� ������� ������
  SequenceIter<T> end();

  //�������� ����� ������
  unsigned int getLength() const;
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
  void sort();
  //����� ������������ ������, ���������� ������ ������ ������������, ���� -1 ���� �� �������
  int findSubList(const DLinkList& sub_list);
  //����� ������������ ������, ���������� �������� ������ ������������, ���� �� �������, �� ������� ��������
  SequenceIter<T> findSubListIter(const DLinkList& sub_list);
  //�������� ������������ ������ �������� �������� ���������: 
  //[i_begin, i_end] �������� ��������� ��� ���������;
  DLinkList getSubList(unsigned int i_begin, unsigned int i_end);
  //������� ������ other � �������
  void merge(const DLinkList& other );

  //���������� ������������ �����������
  DLinkList(const DLinkList & other);
  //���������� ��������� ������������
  DLinkList& operator = (const DLinkList& other );
  //���������� ��������� ��������� + ������������ �������
  DLinkList operator + (const DLinkList &v);
  //���������� ��������� [] ��� ������� � �������� ������
  T & operator [] (unsigned int i);

private:
  //���������� ������ ������ ��� �������� ����������
  //�������� �������� �������, ���������, ���� revert = false, ����� ����������
  Node<T>* getNeighborElement(Node<T>* item, bool revert = false) const;
  //�������� ������� ������ �� �������
  Node<T>* getElement(const unsigned int& i) const;

  //���������� �������� ������ �� ��������� ��������� [first, last]
  DLinkList<T>* getCopyRangeList(Node<T>* first, Node<T>* last) const;
  //�������������, ��������� ������������� ������������ �������� ������ � �������� first ������� pattern_list,
  //�� ������ ������� ����� ��������������� ��������� ������, ��� == pattern_list.getLength() ������������ ������
  unsigned int getScoreMatching(Node<T>* first, const DLinkList& pattern_list) const;

private:
  //��������� �� ������ ������� ������
  Node<T>* p_first;
  //��������� �� ��������� ������� ������
  Node<T>* p_last;
  //���-�� ��������� � ������
  unsigned int n_size_list;
};

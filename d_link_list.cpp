#include "d_link_list.h"
#include "exceptionlist.h"
/**************************Node*******************************/
  template <typename T> Node<T>::Node()
  {
    p_prev = nullptr;
    p_next = nullptr;
  }

  template <typename T> Node<T>::Node(T obj, Node<T>* prev_data, Node<T>* next_data)
  {
    p_prev = prev_data;
    p_next = next_data;
    m_data = obj;
  }

  template <typename T> Node<T>::~Node()
  {
  }

  template <typename T> T& Node<T>::data()
  {
    return m_data;
  }

  template <typename T> bool Node<T>::setData(const T obj)
  {
    bool res(true);
    m_data = obj;
    return res;
  }

  template <typename T> T Node<T>::getData()
  {
    return m_data;
  }

  template <typename T> bool Node<T>::setPrev(Node* prev_data)
  {
    bool res(true);
    p_prev = prev_data;
    return res;
  }

  template <typename T> Node<T>* Node<T>::getPrev()
  {
    return p_prev;
  }

  template <typename T> bool Node<T>::setNext(Node* next_data)
  {
    bool res(true);
    p_next = next_data;
    return res;
  }

  template <typename T> Node<T>* Node<T>::getNext()
  {
    return p_next;
  }
  /**************************SequenceIter*******************************/
  template <typename T> SequenceIter<T>::SequenceIter()
  {
    p_item = nullptr;
  }

  template <typename T> SequenceIter<T>::SequenceIter(Node<T>* item)
  {
    p_item = item;
  }

  template <typename T> SequenceIter<T>::~SequenceIter()
  {
  }

  template <typename T> bool SequenceIter<T>::isListIterNull()
  {
    return (p_item == nullptr);
  }

  template <typename T> SequenceIter<T>& SequenceIter<T>::operator++(int) // postfix A++
  {
    if (p_item != nullptr && p_item->getNext())
      p_item = p_item->getNext();
    else
      p_item = nullptr;

    return *this;
  }

  template <typename T> SequenceIter<T>& SequenceIter<T>::operator--(int)// postfix A--
  {
    if (p_item != nullptr && p_item->getPrev())
      p_item = p_item->getPrev();
    else
      p_item = nullptr;

    return *this;
  }

  template <typename T> T& SequenceIter<T>::operator *()
  {
    if (p_item == nullptr)
      throw(ExseptionListIter()); //генерируем исключение

    return p_item->data();
  }

  /**************************DLinkList*******************************/
  template <typename T> DLinkList<T>::DLinkList(): p_first(nullptr), p_last(nullptr), n_size_list(0)
  {
  }

  template <typename T> DLinkList<T>::~DLinkList()
  {
    clear();
  }

  template <typename T> SequenceIter<T> DLinkList<T>::begin()
  {
    return SequenceIter<T>(p_first);
  }

  template <typename T> SequenceIter<T> DLinkList<T>::end()
  {
    return SequenceIter<T>(p_last);
  }

  template <typename T> unsigned int DLinkList<T>::getLength() const
  {
    return n_size_list;
  }

  template <typename T> void DLinkList<T>::clear()
  {
    Node<T>* it(p_first);
    while(it != nullptr)
    {
      Node<T>* it_next = it->getNext();
      delete it;
      it = it_next;
    }
    n_size_list = 0;
    p_first = nullptr;
    p_last = nullptr;
  }

  template <typename T> void DLinkList<T>::push_back( const T& value )
  {
    Node<T>* newNode = new Node<T>(value, p_last);
    if (p_last != nullptr)
    {
      p_last->setNext(newNode);
      p_last = newNode;
    }
    else
    {
      p_first = newNode;
      p_last = newNode;
    }
    n_size_list++;
  }

  template <typename T> void DLinkList<T>::push_front( const T& value )
  {
    Node<T>* newNode = new Node<T>(value, nullptr, p_first);
    if (p_first != nullptr)
    {
      p_first->setPrev(newNode);
      p_first = newNode;
    }
    else
    {
      p_first = newNode;
      p_last = newNode;
    }
    n_size_list++;
  }

  template <typename T> void DLinkList<T>::pop_back()
  {
    if (p_last != nullptr)
    {
      Node<T>* prev_last = p_last->getPrev();
      delete p_last;
      p_last = prev_last;
      if (n_size_list == 1)
        p_first = nullptr;
      if (p_last != nullptr)
        p_last->setNext(nullptr);
    }
    else
      throw(ExseptionListPopBack());

    n_size_list--;
  }

  template <typename T> void DLinkList<T>::pop_front()
  {
    if (p_first != nullptr)
    {
      Node<T>* next_first = p_first->getNext();
      delete p_first;
      p_first = next_first;
      if (n_size_list == 1)
        p_last = nullptr;
      if (p_first != nullptr)
        p_first->setPrev(nullptr);

    }
    else
      throw(ExseptionListPopFront());

    n_size_list--;
  }

  template <typename T> Node<T>* DLinkList<T>::getNeighborElement(Node<T>* item, bool revert) const
  {
    if (item == nullptr)
      return nullptr;

    if (revert)
      return item->getPrev();
    else
      return item->getNext();
  }

  template <typename T> Node<T>* DLinkList<T>::getElement(const unsigned int& i) const
  {
    Node<T>* ret_item = nullptr;
    if (i >= 0 && i < n_size_list)
    {
      bool revert(false);
      Node<T>* it_node = p_first;
      unsigned int k = i;
      if (n_size_list - i < i)
      {
        revert = true;
        it_node = p_last;
        k = n_size_list - i - 1 ;
      }
      unsigned int it(0);
      while(it <= k && it_node != nullptr)
      {
        if (it == k)
        {
          ret_item = it_node;
          it_node = nullptr;
        }
        else
        {
          it_node = getNeighborElement(it_node, revert);
          it++;
        }
      }
    }
    return ret_item;
  }

  template <typename T> bool DLinkList<T>::eraseItem(unsigned int i)
  {
    bool res(false);
    Node<T>* it_node = getElement(i);
    if (it_node != nullptr)
    {
      Node<T>* prev_it = it_node->getPrev();
      Node<T>* next_it = it_node->getNext();
      if (prev_it != nullptr) 
        prev_it->setNext(next_it);
      else
        p_first = next_it;

      if (next_it != nullptr)
        next_it->setPrev(prev_it);
      else
        p_last = prev_it;

       delete it_node;
       n_size_list--;
       res = true;
    }
       
    return res;
  }

  template <typename T> bool DLinkList<T>::insertItem(const T& value, unsigned int i)
  {
    bool res(false);
    Node<T>* it_node = getElement(i);
    if (it_node != nullptr)
    {
      Node<T>* prev_it = it_node->getPrev();
      Node<T>* next_it = it_node->getNext();
      Node<T>* newNode = new Node<T>(value, prev_it, it_node);

      if (prev_it != nullptr) 
        prev_it->setNext(newNode);
      else
        p_first = newNode;

      it_node->setPrev(newNode);
      n_size_list++;
      res = true;
    }
    return res;
  }

  template <typename T> bool DLinkList<T>::getItem(T& ret_val, unsigned int i) const
  {
    bool res(false);
    Node<T>* it_node = getElement(i);
    if (it_node != nullptr)
    {
      ret_val = it_node->getData();
      res = true;
    }
    return res;
  }

  template <typename T> bool DLinkList<T>::setItem(const T& value, unsigned int i)
  {
    bool res(false);
    Node<T>* it_node = getElement(i);
    if (it_node != nullptr)
      res = it_node->setData(value);

    return res;
  }

  /************************************************/
  template <typename T> DLinkList<T>* DLinkList<T>::getCopyRangeList(Node<T>* first, Node<T>* last) const
  {
    DLinkList<T>* copy_list = new DLinkList<T>;
    Node<T>* it(first);
    while(it != nullptr)
    {
      copy_list->push_back(it->getData());
      if (it != last)
        it = it->getNext();
      else
        it = nullptr;
    }
    return copy_list;
  }

  template <typename T> unsigned int DLinkList<T>::getScoreMatching(Node<T>* first, const DLinkList& pattern_list) const
  {
    int score_matching(0);
    Node<T>* it(first);
    Node<T>* it_pattern_list(pattern_list.p_first);
    while(it != nullptr && it_pattern_list != nullptr)
    {
      if (it->getData() == it_pattern_list->getData())
        score_matching++;

      it = it->getNext();
      it_pattern_list = it_pattern_list->getNext();
    }
    return score_matching;
  }


  template <typename T> int DLinkList<T>::findSubList(const DLinkList& sub_list)
  {
    int inxBeginSubList(-1);
    int inx = 0;
    Node<T>* it(p_first);
    while(it != nullptr)
    {
      if (getScoreMatching(it, sub_list) == sub_list.getLength())
      {
        inxBeginSubList = inx;
        break;
      }
      it = it->getNext();
      inx++;
    }
    return inxBeginSubList;
  }

  template <typename T> SequenceIter<T> DLinkList<T>::findSubListIter(const DLinkList& sub_list)
  {
    SequenceIter<T> iterBeginSubList;
    Node<T>* it(p_first);
    while(it != nullptr)
    {
      if (getScoreMatching(it, sub_list) == sub_list.getLength())
      {
        iterBeginSubList = SequenceIter<T>(it);
        break;
      }
      it = it->getNext();
    }
    return iterBeginSubList;
  }

  template <typename T> DLinkList<T>::DLinkList(const DLinkList & other) 
  {
    DLinkList<T>* newList = other.getCopyRangeList(other.p_first, other.p_last);
    p_first = newList->p_first;
    p_last = newList->p_last;
    n_size_list = newList->n_size_list;
  }

  template <typename T> DLinkList<T> DLinkList<T>::getSubList(unsigned int i_begin, unsigned int i_end)
  {
    DLinkList<T> ret_list;
    Node<T>* first(getElement(i_begin));
    Node<T>* last(getElement(i_end));
    if (first != nullptr && last != nullptr)
    {
      Node<T>* it(first);
      unsigned int i(0);
      while(it != nullptr)
      {
        ret_list.push_back(it->getData());

        if (it == last)
          it = nullptr;
        else
          it = it->getNext();

        i++;
      }
    }

    return ret_list;
  }


 
   //перегрузка оператора [] для доступа к элементу списка
   template <typename T> T& DLinkList<T>::operator [] (unsigned int i)
   {
     if (i < 0 || i >= n_size_list)
       throw(ExseptionListAccess(i)); //вбросить
     return getElement(i)->data(); //возвратить элемент
   }

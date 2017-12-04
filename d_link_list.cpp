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

  template <typename T> bool SequenceIter<T>::isIterNull()
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

  template <typename T> SeqType DLinkList<T>::getType() const
  {
    return SeqType::LinkList;
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

  template <typename T> bool DLinkList<T>::isEmpty() const
  {
    return n_size_list == 0;
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

  template <typename T> void DLinkList<T>::merge(const DLinkList<T>& other )
  {
    *this = *this + other;
  }

  template <typename T> void DLinkList<T>::fromVec(const std::vector<T>& data)
  {
    clear();
    for(std::vector<T>::const_iterator it = data.begin(); it != data.end(); it++)
      push_back(*it);
  }

  template <typename T> bool DLinkList<T>::compareVec(const std::vector<T>& data)
  {
    if (n_size_list != data.size())
      return false;

    bool res(true);
    Node<T>* jt = p_first;
    
    for(std::vector<T>::const_iterator it = data.begin(); it != data.end(); it++)
    {
      res = res && (jt->getData() == *it);
      jt = jt->getNext();
    }
    return res;
  }

  template <typename T> void DLinkList<T>::getSubSeq(Sequence<T>* sub_list, unsigned int i_begin, unsigned int i_end)
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
    sub_list->clone(&ret_list);
  }

  template <typename T> bool DLinkList<T>::clone(Sequence<T>* seq)
  {
    bool res(false);
    if (seq->getType() == LinkList)
    {
      DLinkList<T>* seq_list = dynamic_cast<DLinkList<T>*>(seq);
      DLinkList<T>* copy_list = seq_list->getCopyRangeList(seq_list->p_first, seq_list->p_last);
      clear();
      p_first = copy_list->p_first;
      p_last = copy_list->p_last;
      n_size_list = copy_list->n_size_list;
      res = true;
    }
    return res;
  }

  /*********************Шаблоны функций для сортирови списка вставкой***************************/
  //Разделение списка
  template <typename T> static void partitioning(Node<T>* source, const int& source_size, Node<T>** frontRef, int& front_size, Node<T>** backRef, int& back_size)
  {
    Node<T>* current = source;
    if (source_size < 2)
    {
      *frontRef = source;
      *backRef = nullptr;
      front_size = source_size;
      back_size = 0;
    }
    else
    {
      front_size = (source_size - 1)/2;

      for (int i(0); i < front_size; i++)
        current = current->getNext();

      front_size++;
      back_size = source_size - front_size;

      *frontRef = source;
      *backRef = current->getNext();
      current->setNext(nullptr);
    }
  }

  //объединение двух списков
  template <typename T> static Node<T>* merger (Node<T>* a, Node<T>* b)
  {
//     Node<T>* res = nullptr;     
//     if (a == nullptr)
//       return(b);
//     else if (b == nullptr)
//       return(a);
//     if (a->getData() <= b->getData())
//     {
//       res = a;
//       res->setNext(merger(a->getNext(), b));
//     }
//     else
//     {
//       res = b;
//       res->setNext(merger(a, b->getNext()));
//     }
//     return res;
    Node<T>* root = nullptr;
    Node<T>* cur = nullptr;

    if(a == nullptr)
      return b;
    else if(b == nullptr)
      return a;

    while( (a != nullptr) && (b != nullptr) )
    {
      Node<T>* tmp(new Node<T>());
      if(a->data() <= b->data())
      {
        tmp->setData(a->getData());
        tmp->setNext(nullptr);
        Node<T>* buff = a;
        a = a->getNext();
        delete buff;
      }
      else
      {
        tmp->setData(b->getData());
        tmp->setNext(nullptr);
        Node<T>* buff = b;
        b = b->getNext();
        delete buff;
      }
      if(root == nullptr)
      {
        root = tmp;
        cur = root;
      }
      else
      {
        cur->setNext(tmp);
        cur = tmp;
      }
    }


    while(a != nullptr)
    {
      Node<T>* tmp(new Node<T>());
      tmp->setData(a->getData());
      tmp->setNext(nullptr);
      cur->setNext(tmp);
      cur = tmp;
      Node<T>* buff = a;
      a = a->getNext();
      delete buff;
    }
    while(b != nullptr)
    {
      Node<T>* tmp(new Node<T>());
      tmp->setData(b->getData());
      tmp->setNext(nullptr);
      cur->setNext(tmp);
      cur = tmp;
      Node<T>* buff = b;
      b = b->getNext();
      delete buff;
    }


    return root;
  }

  //Сортировка слиянием односвязного списка рекурсивной функцией
  template <typename T> static void mergeSort(Node<T>** headRef, const int& head_size)
  {
    int a_length(0);
    int b_length(0);
    Node<T>* head = *headRef;
    Node<T>* a;
    Node<T>* b;
    if ((head == nullptr) || (head->getNext() == nullptr))
    {
      return;
    }

    partitioning(head, head_size, &a, a_length,  &b, b_length);
    mergeSort(&a, a_length);
    mergeSort(&b, b_length);
    *headRef = merger(a, b);
  }

  template <typename T> void DLinkList<T>::mergeSortList()
  {
    mergeSort(&p_first, n_size_list);
    Node<T>* it(p_first);
    Node<T>* it_prev(nullptr);
    //проставляем связи в обратном порядке
    while(it != nullptr)
    {
      it->setPrev(it_prev);
      it_prev = it;
      it = it->getNext();
      if (it == nullptr)
        p_last = it_prev;
    }
  }

  template <typename T> void DLinkList<T>::BubbleSortList()
  {
    // Сортировка массива пузырьком
    if (n_size_list > 0)
    {
      for(unsigned int i(0); i < n_size_list - 1; i++)
      {
        unsigned int j(0);
        Node<T>* j_cycle = p_first;
        while (j < n_size_list - i - 1)
        {
          if (j_cycle->data() > j_cycle->getNext()->data())
          {
            // меняем элементы местами
            Node<T>* j_node = j_cycle;
            Node<T>* j_next = j_cycle->getNext();
            Node<T>* prev_j = j_cycle->getPrev();
            Node<T>* next_j_next = j_cycle->getNext()->getNext();
            j_node->setPrev(j_next);
            j_node->setNext(next_j_next);
            j_next->setPrev(prev_j);
            j_next->setNext(j_node);
            if (prev_j == nullptr)
              p_first = j_next;
            else
              prev_j->setNext(j_next);

            if (next_j_next == nullptr)
              p_last = j_node;
            else
              next_j_next->setPrev(j_node);

            j_cycle = j_node; // j++
          }
          else
            j_cycle = j_cycle->getNext();

          j++;
        }
      }
    }

  }

  //Сортировка двусвязного списка
  template <typename T> void DLinkList<T>::sort(const SortMethod& method)
  {
    switch (method)
    {
      case SortMethod::BubbleSort:
        BubbleSortList();
        break;
      case SortMethod::MergeSort:
        mergeSortList();
        break;
      case SortMethod::RadixSort:
        RadixSort();
        break;
      default:
        throw(ExseptionSortError()); //вбросить
        break;
    }
  }

  // функция сортировки возвращает указатель на начало отсортированного списка
  //  t - разрядность (максимальная длина числа) 
  template <typename T> static Node<T>* radix_list(Node<T>* l, int t) 
  {
    int i, j, d, m = 1;
    Node<T>* temp, *head[10], *tail[10];
    Node<T>* out;

    for (j=1; j <= t; j++) 
    { 
      for (i=0; i<=9; i++)
        head[i] = (tail[i]=nullptr);

      while ( l != nullptr ) 
      {
        d = ((int)(l->data()/m))%(int)10;
        temp = tail[d];
        if ( head[d]==nullptr ) 
          head[d] = l;
        else 
          temp->setNext(l);

        temp = tail[d] = l;
        l = l->getNext();
        temp->setNext(nullptr);
      }
      for (i = 0; i <= 9; i++)
        if ( head[i] != nullptr ) break;
      l = head[i];
      temp = tail[i];
      for (d = i+1; d <= 9; d++) 
      {
        if ( head[d] != nullptr) 
        { 
          temp->setNext(head[d]);
          temp = tail[d];
        }
      }
      m *= 10;
    }
    if (l != nullptr)
      l->setPrev(nullptr);

    out = l;
    return out;
  }

  template <typename T> int max_razr(T value)
  {
    int max=0;
    while(value > 1)
    {
      value/=10;
      max++;
    }
    return max + 1;
  }

  template <typename T> void DLinkList<T>::RadixSort()
  {
    int max_plus = 0;
    int max_minus = 0;
    Node<T>* minus_list = nullptr;
    Node<T>* minus_list_head = nullptr;
    Node<T>* plus_list = nullptr;
    Node<T>* plus_list_head = nullptr;
    Node<T>* current = p_first;
    while(current != nullptr)
    {
      if (current->getData() >= 0)
      {
        if (plus_list != nullptr)
        {
          plus_list->setNext(current);
          plus_list = current;
          current = current->getNext();
          plus_list->setNext(nullptr);
        }
        else
        {
          plus_list = current;
          current = current->getNext();
          plus_list->setNext(nullptr);
          plus_list_head = plus_list;
        }
        int current_razr = max_razr(plus_list->getData());
        if (max_plus < current_razr)
          max_plus = current_razr;
      }
      else
      {
        if (minus_list != nullptr)
        {
          minus_list->setNext(current);
          minus_list = current;
          current = current->getNext();
          minus_list->setNext(nullptr);
          minus_list->setData(-minus_list->getData());
        }
        else
        {
          minus_list = current;
          current = current->getNext();
          minus_list->setNext(nullptr);
          minus_list_head = minus_list;
          minus_list->setData(-minus_list->getData());
        }
        int current_razr = max_razr(minus_list->getData());
        if (max_minus < current_razr)
          max_minus = current_razr;
      }
    }

    minus_list_head = radix_list(minus_list_head, max_minus);
    plus_list_head = radix_list(plus_list_head, max_plus);
    p_first = plus_list_head;
    current = minus_list_head;
    while (current != nullptr)
    {
      Node<T>* buff = current;
      current = current->getNext();
      buff->setData(-buff->getData());
      buff->setNext(p_first);
      p_first  = buff;
    }
    //rsort(p_first, 1);
    Node<T>* it(p_first);
    Node<T>* it_prev(nullptr);
    //проставляем связи в обратном порядке
    while(it != nullptr)
    {
      it->setPrev(it_prev);
      it_prev = it;
      it = it->getNext();
      if (it == nullptr)
        p_last = it_prev;
    }
  }

  //перегрузка оператора присваивания
  template <typename T> DLinkList<T>& DLinkList<T>::operator = (const DLinkList<T>& other )
  {
    if (this != &other) // защита от неправильного самоприсваивания
    {
      // 1: освобождаем "старую" память
      clear();
      // 2: выделяем новую память
      DLinkList<T>* clone_list = getCopyRangeList(other.p_first, other.p_last);
      // 3: присваиваем значения 
      p_first = clone_list->p_first;
      p_last = clone_list->p_last;
      n_size_list = clone_list->n_size_list;
    }
    return *this;
  }

  //перегрузка бинарного оператора + конкатенация списков
  template <typename T> DLinkList<T> DLinkList<T>::operator + (const DLinkList<T> &v)
  {
    DLinkList newList;

    for (unsigned int i(0); i < this->getLength(); i++)
    {
      T ret_val;
      if (this->getItem(ret_val, i))
        newList.push_back( ret_val );
    }

    for (unsigned int i(0); i < v.getLength(); i++)
    {
      T ret_val;
      if (v.getItem(ret_val, i))
        newList.push_back( ret_val );
    }

    return newList;
  }

   //перегрузка оператора [] для доступа к элементу списка
   template <typename T> T& DLinkList<T>::operator [] (unsigned int i)
   {
     if (i < 0 || i >= n_size_list)
       throw(ExseptionListAccess(i)); //вбросить
     return getElement(i)->data(); //возвратить элемент
   }

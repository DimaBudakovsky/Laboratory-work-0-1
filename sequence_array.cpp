#include "sequence_array.h"
#include <algorithm>

template <typename T> SeqArray<T>::SeqArray() : p_array(nullptr), n_size(0)
{
}

template <typename T> SeqArray<T>::SeqArray(const T& element) : p_array(new T[1]), n_size(1)
{
  p_array[0] = element;
}

template <typename T> SeqArray<T>::SeqArray(T* const elements, unsigned int size) : p_array(new T[size]), n_size(size)
{
  for (unsigned int i(0); i < size; i++)
    p_array[i] = elements[i];
}


template <typename T> SeqArray<T>::~SeqArray()
{
  if (p_array != nullptr)
    delete [] p_array;
}

template <typename T> SeqType SeqArray<T>::getType() const
{
  return SeqType::Array;
}


//получить длину списка
template <typename T> unsigned int SeqArray<T>::getLength() const
{
  return n_size;
}

template <typename T> bool SeqArray<T>::isEmpty() const
{
  return (n_size == 0);
}

//добавить новый элемент с значением value в конец списка
template <typename T> void SeqArray<T>::push_back( const T& value )
{
  T* new_array = new T[n_size + 1];
  if (p_array != nullptr)
  {
    for (unsigned int i (0); i < n_size; i++)
      new_array[i] = p_array[i];

    delete [] p_array;
  }
  new_array[n_size] = value;
  p_array = new_array;
  n_size++;
}
//добавить новый элемент с значением value в начало списка
template <typename T> void SeqArray<T>::push_front( const T& value )
{
  T* new_array = new T[n_size + 1];
  new_array[0] = value;
  if (p_array != nullptr)
  {
    for (unsigned int i (0); i < n_size; i++)
      new_array[i+1] = p_array[i];

    delete [] p_array;
  }
  p_array = new_array;
  n_size++;
}
//удалить последний элемент списка
template <typename T> void SeqArray<T>::pop_back()
{
  if (n_size > 0)
  {
    delete &p_array[n_size-1];
    n_size--;
  }
}
//удалить первый элемент списка
template <typename T> void SeqArray<T>::pop_front()
{
  if (n_size > 0)
  {
    delete &p_array[0];
    n_size--;
    p_array = &p_array[1];
  }
}

//отчистить список, удалить данные, освободить память
template <typename T> void SeqArray<T>::clear()
{
  if (n_size > 0 && p_array != nullptr)
    delete [] p_array;

  p_array = nullptr;
  n_size = 0;
}

//удалить элемент списка с индексом i
template <typename T> bool SeqArray<T>::eraseItem(unsigned int i)
{
  bool res (true);
  if (i < n_size)
  {
    T* new_array = new T[n_size - 1];
    if (p_array != nullptr)
    {
      for (unsigned int j (0); j < i; j++)
        new_array[j] = p_array[j];

      for (unsigned int j (i+1); j < n_size; j++)
        new_array[j-1] = p_array[j];

      delete [] p_array;
    }
    p_array = new_array;
    n_size--;
  }
  else
    res = false;

  return res;
}
//добавить элемент списка с индексом i, предыдущий элемент с индексом i сдвигается вправо 
/// как быть если i выходит за пределы длины списка??? на текущий момент возвращает false
template <typename T> bool SeqArray<T>::insertItem(const T& value, unsigned int i)
{
  bool res (true);
  if (i < n_size)
  {
    T* new_array = new T[n_size + 1];
    if (p_array != nullptr)
    {
      for (unsigned int j (0); j < i; j++)
        new_array[j] = p_array[j];

      new_array[i] = value;
      for (unsigned int j (i); j < n_size; j++)
        new_array[j+1] = p_array[j];

      delete [] p_array;
    }
    p_array = new_array;
    n_size++;
  }
  else 
    res = false;

  return res;
}


//записать значение элемента списка под индексом i в переменную ret_val
template <typename T> bool SeqArray<T>::getItem(T& ret_val, unsigned int i) const
{
  bool res (true);
  if (i < n_size)
    ret_val = p_array[i];
  else
    res = false;

  return res;
}
//записать значение value в i-ый элемент списка
template <typename T> bool SeqArray<T>::setItem(const T& value, unsigned int i)
{
  bool res (true);
  if (i < n_size)
    p_array[i] = value;
  else
    res = false;

  return res;
}

//сортировка списка по возрастанию значения
template <typename T> void SeqArray<T>::sort(const SortMethod& method)
{
  switch (method)
  {
  case SortMethod::BubbleSort:
    BubbleSortArray();
    break;
  case SortMethod::MergeSort:
    mergeSortArray();
    break;
  case SortMethod::RadixSort:
    RadixSortArray();
    break;
  default:
    throw(ExseptionSortError()); //вбросить
    break;
  }
}

//получить подмножество списка согласно заданным свойствам: 
//[i_begin, i_end] диапазон элементов для обработки;
template <typename T> void SeqArray<T>::getSubSeq(Sequence<T>* sub_array, unsigned int i_begin, unsigned int i_end)
{
  SeqArray<T> res_array;
  if (i_begin <= i_end && i_end < n_size)
  {
    res_array.p_array = new T[i_end - i_begin + 1];
    if (p_array != nullptr)
    {
      unsigned int k (0);
      for (unsigned int j (i_begin); j <= i_end; j++)
      {
        res_array.p_array[k] = p_array[j];
        k++;
      }
    }
    res_array.n_size = i_end - i_begin + 1;
  }
  sub_array->clone(&res_array);
}

template <typename T> bool SeqArray<T>::clone(Sequence<T>* seq)
{
  bool res(false);
  if (seq->getType() == Array)
  {
    SeqArray<T>* seq_array = dynamic_cast<SeqArray<T>*>(seq);
    clear();
    p_array = new T[seq_array->n_size];
    n_size = seq_array->n_size;
    for (unsigned int i(0); i < n_size; i++)
      p_array[i] = seq_array->p_array[i];

    res = true;
  }
  return res;
}

//слияние списка other с текущим
template <typename T> void SeqArray<T>::merge(const Sequence<T>& other )
{
  return (*this + other);
}

template <typename T> void SeqArray<T>::fromVec(const std::vector<T>& data)
{
  if (p_array != nullptr)
    delete [] p_array;

  n_size = data.size();
  T* new_array = new T[n_size];

  for(unsigned int i (0); i < n_size; i++)
    new_array[i] = data[i];

  p_array = new_array;
}

template <typename T> bool SeqArray<T>::compareVec(const std::vector<T>& data)
{
  if (data.size() != n_size)
    return false;

  bool res(true);
  for(unsigned int i (0); i < n_size; i++)
    res = res && (p_array[i] == data[i]);

  return res;
}

template <typename T> void SeqArray<T>::BubbleSortArray()
{
  T temp;
  if (n_size > 0)
  {
    for (unsigned int i(0); i < n_size - 1; i++) 
      for (unsigned int j(0); j < n_size - i - 1; j++)
        if (p_array[j] > p_array[j + 1]) 
        {
          // меняем элементы местами
          temp = p_array[j];
          p_array[j] = p_array[j + 1];
          p_array[j + 1] = temp;
        }
  }

}

template <typename T> static void merge(T *A, int first, int last, int size)
{
  int middle, start, final, j;
  T *mas = new T[size];
  middle=(first + last)/2; //вычисление среднего элемента
  start = first; //начало левой части
  final = middle + 1; //начало правой части

  for(j = first; j <= last; j++) //выполнять от начала до конца
    if ((start <= middle) && ((final > last) || (A[start] < A[final])))
    {
      mas[j] = A[start];
      start++;
    }
    else
    {
      mas[j] = A[final];
      final++;
    }
    //возвращение результата в список
    for (j = first; j <= last; j++) 
      A[j] = mas[j];

    delete [] mas;
};

//рекурсивная процедура сортировки
template <typename T> static void mergeSort(T *A, int first, int last, int size)
{
  if (first < last)
  {
    mergeSort(A, first, (first + last)/2, size); //сортировка левой части
    mergeSort(A, (first + last)/2 + 1, last, size); //сортировка правой части
    merge(A, first, last, size); //слияние двух частей
  }
}

template <typename T> void SeqArray<T>::mergeSortArray()
{
  mergeSort(p_array, 0, n_size - 1, n_size);
}

// Создать счетчики.
// data-сортируемый массив, counters-массив для счетчиков, N-число элементов в data
template<class T> void createCounters(T *data, long *counters, long N) 
{
  // i-й массив count расположен, начиная с адреса counters+256*i
  //memset( counters, 0, 256*sizeof(T)*sizeof(long) );
  for (int i(0); i < sizeof(T)*256; i++)
    counters[i] = 0;

  unsigned char *bp = reinterpret_cast<unsigned char*>(data);
  unsigned char *dataEnd = reinterpret_cast<unsigned char*>(data + N);
  unsigned short i;

  while ( bp != dataEnd ) 
  {
    // увеличиваем количество байт со значением *bp
    // i - текущий массив счетчиков
    for (i=0; i<sizeof(T);i++)
      counters[256*i + *bp++]++;
  }
}


// Функция radixPass принимает в качестве параметров
// номер байта Offset,
// число элементов N, 
// исходный массив source, 
// массив dest, куда будут записываться числа, отсортированные по байту Offset
// массив счетчиков count, соответствующий текущему проходу.

template<class T> void radixPass (short Offset, long N, T *source, T *dest, long *count) 
{
  // временные переменные
  T *sp;
  long s, c, i, *cp;
  unsigned char *bp;


  // шаг 3
  s = 0; 	// временная переменная, хранящая сумму на данный момент
  cp = count;
  for (i = 256; i > 0; --i, ++cp) 
  {
    c = *cp;
    *cp = s;
    s += c;
  }

  // шаг 4
  bp = reinterpret_cast<unsigned char *>(source) + Offset;
  sp = source;
  for (i = N; i > 0; --i, bp += sizeof(T) , ++sp) 
  {
    cp = count + *bp;
    dest[*cp] = *sp;
    ++(*cp);
  }
}
/*
//   // сортируется массив in из N элементов
//   // T - любой беззнаковый целый тип
template<class T> void radixSort (T* &in, long N) 
{
  T *out = new T[N];
  long *counters = new long[sizeof(T)*256], *count;
  createCounters(in, counters, N);
  unsigned short i;

  for (i = 0; i < sizeof(T) - 1; i++) 
  {
    count = counters + 256*i;         // count - массив счетчиков для i-го разряда

    if ( count[0] == N ) continue;    // (*** см ниже)

    radixPass (i, N, in, out, count); // после каждого шага входной и 
    std::swap(in, out);                    // выходной массивы меняются местами
  }
  count = counters + 256*i;
  
  long pos_minus(N);
  long j(0);
  for(long i(0);i < N; i++)
  {
    if (in[i] < 0)
      pos_minus = i;
    if (pos_minus < N)
    {
      out[j] = in[i];
      j++;
    }
  }

  for(long i(0);i < pos_minus; i++)
    out[j + i] = in[i];


  // по окончании проходов
  delete [] in;           // вся информация остается во входном массиве.
  in = out;
  delete [] counters;
}
*/
template<class T> void signedRadixLastPass (short Offset, long N, T *source, T *dest, long *count) {
  T *sp;
  long s, c, i, *cp;
  unsigned char *bp;

  // подсчет количества отрицательных чисел
  long numNeg=0;
  for(i=128;i<256;i++) 
    numNeg += count[i];

  // первые 128 элементов count относятся к положительным числам.
  // отсчитываем номер первого числа, начиная от numNeg 
  s = numNeg;
  cp = count;
  for (i = 0; i < 128; ++i, ++cp) 
  {
    c = *cp;
    *cp = s;
    s += c;
  }

  // номера для отрицательных чисел отсчитываем от начала массива
  s = 0;
  cp = count + 128;
  for (i = 0; i < 128; ++i, ++cp) 
  {
    c = *cp;
    *cp = s;
    s += c;
  }


  bp = (unsigned char *)source + Offset;
  sp = source;
  for (i = N; i > 0; --i, bp += sizeof(T) , ++sp) {
    cp = count + *bp;
    dest[*cp] = *sp;
    ++(*cp);
  }
}

template<class T> void signedRadixSort (T* &in, long N) 
{
  T *out = new T[N];
  unsigned short i;

  long *counters = new long[sizeof(T)*256], *count;
  createCounters(in, counters, N);

  for (i=0; i<sizeof(T)-1; i++) 
  {
    count = counters + 256*i;
    if ( count[0] == N ) continue;
    radixPass (i, N, in, out, count);
    std::swap(in, out);
  }
  count = counters + 256*i;
  signedRadixLastPass (i, N, in, out, count);

  delete in;
  in = out;
  delete counters;
} 

template <typename T> void SeqArray<T>::RadixSortArray()
{
  signedRadixSort(p_array, n_size); 
}

//перегрузка конструктора копирования
template <typename T> SeqArray<T>::SeqArray(const SeqArray & other)
{
  clear();
  p_array = new T [other.n_size];
  for (unsigned int i (0); i < other.n_size; i++)
    p_array[i] = other.p_array[i];

  n_size = other.n_size;
}

//перегрузка бинарного оператора + конкатенация списков
template <typename T> SeqArray<T> SeqArray<T>::operator + (const SeqArray &v)
{
  SeqArray<T> res;
  res.p_array = new T[n_size + v.n_size];
  for (unsigned int i(0); i < n_size; i++)
    res.p_array[i] = p_array[i];

  unsigned int k(n_size);
  for (unsigned int i(0); i < n_size; i++)
  {
    res.p_array[k] = v.p_array[i];
    k++;
  }
  res.n_size = n_size + v.n_size;
  return res;
}

//перегрузка оператора [] для доступа к элементу списка
template <typename T> T & SeqArray<T>::operator [] (unsigned int i)
{
  if (i < 0 || i >= n_size)
    throw(ExseptionListAccess(i)); //вбросить
  return p_array[i]; //возвратить элемент 
}
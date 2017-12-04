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


//�������� ����� ������
template <typename T> unsigned int SeqArray<T>::getLength() const
{
  return n_size;
}

template <typename T> bool SeqArray<T>::isEmpty() const
{
  return (n_size == 0);
}

//�������� ����� ������� � ��������� value � ����� ������
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
//�������� ����� ������� � ��������� value � ������ ������
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
//������� ��������� ������� ������
template <typename T> void SeqArray<T>::pop_back()
{
  if (n_size > 0)
  {
    delete &p_array[n_size-1];
    n_size--;
  }
}
//������� ������ ������� ������
template <typename T> void SeqArray<T>::pop_front()
{
  if (n_size > 0)
  {
    delete &p_array[0];
    n_size--;
    p_array = &p_array[1];
  }
}

//��������� ������, ������� ������, ���������� ������
template <typename T> void SeqArray<T>::clear()
{
  if (n_size > 0 && p_array != nullptr)
    delete [] p_array;

  p_array = nullptr;
  n_size = 0;
}

//������� ������� ������ � �������� i
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
//�������� ������� ������ � �������� i, ���������� ������� � �������� i ���������� ������ 
/// ��� ���� ���� i ������� �� ������� ����� ������??? �� ������� ������ ���������� false
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


//�������� �������� �������� ������ ��� �������� i � ���������� ret_val
template <typename T> bool SeqArray<T>::getItem(T& ret_val, unsigned int i) const
{
  bool res (true);
  if (i < n_size)
    ret_val = p_array[i];
  else
    res = false;

  return res;
}
//�������� �������� value � i-�� ������� ������
template <typename T> bool SeqArray<T>::setItem(const T& value, unsigned int i)
{
  bool res (true);
  if (i < n_size)
    p_array[i] = value;
  else
    res = false;

  return res;
}

//���������� ������ �� ����������� ��������
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
    throw(ExseptionSortError()); //��������
    break;
  }
}

//�������� ������������ ������ �������� �������� ���������: 
//[i_begin, i_end] �������� ��������� ��� ���������;
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

//������� ������ other � �������
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
          // ������ �������� �������
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
  middle=(first + last)/2; //���������� �������� ��������
  start = first; //������ ����� �����
  final = middle + 1; //������ ������ �����

  for(j = first; j <= last; j++) //��������� �� ������ �� �����
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
    //����������� ���������� � ������
    for (j = first; j <= last; j++) 
      A[j] = mas[j];

    delete [] mas;
};

//����������� ��������� ����������
template <typename T> static void mergeSort(T *A, int first, int last, int size)
{
  if (first < last)
  {
    mergeSort(A, first, (first + last)/2, size); //���������� ����� �����
    mergeSort(A, (first + last)/2 + 1, last, size); //���������� ������ �����
    merge(A, first, last, size); //������� ���� ������
  }
}

template <typename T> void SeqArray<T>::mergeSortArray()
{
  mergeSort(p_array, 0, n_size - 1, n_size);
}

// ������� ��������.
// data-����������� ������, counters-������ ��� ���������, N-����� ��������� � data
template<class T> void createCounters(T *data, long *counters, long N) 
{
  // i-� ������ count ����������, ������� � ������ counters+256*i
  //memset( counters, 0, 256*sizeof(T)*sizeof(long) );
  for (int i(0); i < sizeof(T)*256; i++)
    counters[i] = 0;

  unsigned char *bp = reinterpret_cast<unsigned char*>(data);
  unsigned char *dataEnd = reinterpret_cast<unsigned char*>(data + N);
  unsigned short i;

  while ( bp != dataEnd ) 
  {
    // ����������� ���������� ���� �� ��������� *bp
    // i - ������� ������ ���������
    for (i=0; i<sizeof(T);i++)
      counters[256*i + *bp++]++;
  }
}


// ������� radixPass ��������� � �������� ����������
// ����� ����� Offset,
// ����� ��������� N, 
// �������� ������ source, 
// ������ dest, ���� ����� ������������ �����, ��������������� �� ����� Offset
// ������ ��������� count, ��������������� �������� �������.

template<class T> void radixPass (short Offset, long N, T *source, T *dest, long *count) 
{
  // ��������� ����������
  T *sp;
  long s, c, i, *cp;
  unsigned char *bp;


  // ��� 3
  s = 0; 	// ��������� ����������, �������� ����� �� ������ ������
  cp = count;
  for (i = 256; i > 0; --i, ++cp) 
  {
    c = *cp;
    *cp = s;
    s += c;
  }

  // ��� 4
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
//   // ����������� ������ in �� N ���������
//   // T - ����� ����������� ����� ���
template<class T> void radixSort (T* &in, long N) 
{
  T *out = new T[N];
  long *counters = new long[sizeof(T)*256], *count;
  createCounters(in, counters, N);
  unsigned short i;

  for (i = 0; i < sizeof(T) - 1; i++) 
  {
    count = counters + 256*i;         // count - ������ ��������� ��� i-�� �������

    if ( count[0] == N ) continue;    // (*** �� ����)

    radixPass (i, N, in, out, count); // ����� ������� ���� ������� � 
    std::swap(in, out);                    // �������� ������� �������� �������
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


  // �� ��������� ��������
  delete [] in;           // ��� ���������� �������� �� ������� �������.
  in = out;
  delete [] counters;
}
*/
template<class T> void signedRadixLastPass (short Offset, long N, T *source, T *dest, long *count) {
  T *sp;
  long s, c, i, *cp;
  unsigned char *bp;

  // ������� ���������� ������������� �����
  long numNeg=0;
  for(i=128;i<256;i++) 
    numNeg += count[i];

  // ������ 128 ��������� count ��������� � ������������� ������.
  // ����������� ����� ������� �����, ������� �� numNeg 
  s = numNeg;
  cp = count;
  for (i = 0; i < 128; ++i, ++cp) 
  {
    c = *cp;
    *cp = s;
    s += c;
  }

  // ������ ��� ������������� ����� ����������� �� ������ �������
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

//���������� ������������ �����������
template <typename T> SeqArray<T>::SeqArray(const SeqArray & other)
{
  clear();
  p_array = new T [other.n_size];
  for (unsigned int i (0); i < other.n_size; i++)
    p_array[i] = other.p_array[i];

  n_size = other.n_size;
}

//���������� ��������� ��������� + ������������ �������
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

//���������� ��������� [] ��� ������� � �������� ������
template <typename T> T & SeqArray<T>::operator [] (unsigned int i)
{
  if (i < 0 || i >= n_size)
    throw(ExseptionListAccess(i)); //��������
  return p_array[i]; //���������� ������� 
}
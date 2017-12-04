#include "d_link_list.h"
#include "d_link_list.cpp"//подключаем для избежания проблемы с линковкой (для шаблонов)

#include "sequence_array.h"
#include "sequence_array.cpp"//подключаем для избежания проблемы с линковкой (для шаблонов)
#include <iostream>
#include <functional>
#include <array>
#include <vector>
#include <Windows.h>
#include <stdint.h> 
#include <sys/timeb.h>

int gettimeofday(struct timeval * tp, struct timezone * tzp) 
{ 
  // Note: some broken versions only have 8 trailing zero's, the correct epoch has 9 trailing zero's 
  static const uint64_t EPOCH = ((uint64_t)116444736000000000ULL); 

  SYSTEMTIME system_time; 
  FILETIME file_time; 
  uint64_t time; 

  GetSystemTime(&system_time); 
  SystemTimeToFileTime(&system_time, &file_time); 
  time = ((uint64_t)file_time.dwLowDateTime); 
  time += ((uint64_t)file_time.dwHighDateTime) << 32; 

  tp->tv_sec = (long)((time - EPOCH) / 10000000L); 
  tp->tv_usec = (long)(system_time.wMilliseconds * 1000); 
  return 0; 
} 

double wtime() 
{ 
  double t(.0);
  static int sec = -1; 
  struct timeval tv; 
  gettimeofday(&tv, 0); 
  if (sec < 0) sec = tv.tv_sec; 
  t = (tv.tv_sec - sec) + 1.0e-6*tv.tv_usec; 

  return t;
}

void sortAtom(Sequence<int>* seq, const std::vector<int>& vec, const std::vector<int>& vec_sorted, const SortMethod& method)
{
  seq->clear();

  seq->fromVec(vec);

  double start_time = wtime();
  seq->sort(method);
  double end_time = wtime();

  bool res = seq->compareVec(vec_sorted);

  switch (method)
  {
  case SortMethod::BubbleSort:
    std::cout << "Time for method BubbleSort:";
    break;
  case SortMethod::MergeSort:
    std::cout << "Time for method MergeSort:";
    break;
  case SortMethod::RadixSort:
    std::cout << "Time for method RadixSort:";
    break;
  }
  std::cout << end_time - start_time << " sec. ";

  if (res)
    std::cout << "Sorted of sequence is correct!" << std::endl;
  else
    std::cout << "Attention! Sorted of sequence is uncorrect!"  << std::endl;

}

void CTestSort(Sequence<int>* seq)
{
  unsigned int n_elements;
  std::cout << "Enter amount of elements for sort:" << std::endl;
  std::cin >> n_elements;
  std::cout << "Amount of elements for sort is " << n_elements << std::endl;

  std::vector<int> rand_vec;// массив в случайном порядке
  for (unsigned int i(0); i < n_elements; i++)
  {
    int value = rand()%1000; 
    if (rand()%7 == 0) 
      value *= -1;
    rand_vec.push_back(std::abs(value));
  }

  std::vector<int> rand_vec_sorted = rand_vec;// отсортированный массив
  std::sort(rand_vec_sorted.begin(), rand_vec_sorted.end());

  std::vector<int> rand_vec_sorted_rev = rand_vec;// отсортированный в обратном порядке массив
  std::sort(rand_vec_sorted_rev.begin(), rand_vec_sorted_rev.end(), std::greater<int>());


  if (seq != nullptr)
  {
    std::cout << "Sorting random sequence:" << std::endl;
    sortAtom(seq, rand_vec, rand_vec_sorted, SortMethod::BubbleSort);
    sortAtom(seq, rand_vec, rand_vec_sorted, SortMethod::MergeSort);
    sortAtom(seq, rand_vec, rand_vec_sorted, SortMethod::RadixSort);

    std::cout << "Sorting sorted sequence:" << std::endl;
    sortAtom(seq, rand_vec_sorted, rand_vec_sorted, SortMethod::BubbleSort);
    sortAtom(seq, rand_vec_sorted, rand_vec_sorted, SortMethod::MergeSort);
    sortAtom(seq, rand_vec_sorted, rand_vec_sorted, SortMethod::RadixSort);

    std::cout << "Sorting sorted sequence in reverse order:" << std::endl;
    sortAtom(seq, rand_vec_sorted_rev, rand_vec_sorted, SortMethod::BubbleSort);
    sortAtom(seq, rand_vec_sorted_rev, rand_vec_sorted, SortMethod::MergeSort);
    sortAtom(seq, rand_vec_sorted_rev, rand_vec_sorted, SortMethod::RadixSort);

  }
}

bool UnitTest(Sequence<int>* seq, Sequence<int>* sub)
{
  bool res(true);

  if (seq->getLength() != 0)
    res = false;

  seq->push_back(23);

  if (seq->getLength() != 1)
    res = false;

  try
  {
    if ((*seq)[0] != 23 || (*seq)[seq->getLength() - 1] != 23)
      res = false;
  }
  catch (ExseptionList& e)
  {
    std::cout << e.about_error() << std::endl;
    res = false;
  }
  catch (...)
  {
    std::cout << "Unknown exseption" << std::endl;
    res = false;
  }

  try
  {
    int var1 = (*seq)[1];
    int var2 = (*seq)[-1];
  }
  catch (ExseptionList& e)
  {
    std::cout << e.about_error() << std::endl;
  }
  catch (...)
  {
    std::cout << "Unknown exseption" << std::endl;
    res = false;
  }

  try
  {
    int var2 = (*seq)[-1];
  }
  catch (ExseptionList& e)
  {
    std::cout << e.about_error() << std::endl;
  }
  catch (...)
  {
    std::cout << "Unknown exseption" << std::endl;
    res = false;
  }

  seq->push_back(43);

  if (seq->getLength() != 2)
    res = false;

  try
  {
    if ((*seq)[0] != 23 || (*seq)[seq->getLength() - 1] != 43)
      res = false;
  }
  catch (ExseptionList& e)
  {
    std::cout << e.about_error() << std::endl;
    res = false;
  }
  catch (...)
  {
    std::cout << "Unknown exseption" << std::endl;
    res = false;
  }

  try
  {
    int var1 = (*seq)[-1];
  }
  catch (ExseptionList& e)
  {
    std::cout << e.about_error() << std::endl;
  }
  catch (...)
  {
    std::cout << "Unknown exseption" << std::endl;
    res = false;
  }

  try
  {
    int var2 = (*seq)[2];
  }
  catch (ExseptionList& e)
  {
    std::cout << e.about_error() << std::endl;
  }
  catch (...)
  {
    std::cout << "Unknown exseption" << std::endl;
    res = false;
  }

  seq->push_front(53);

  if (seq->getLength() != 3)
    res = false;

  try
  {
    if ((*seq)[0] != 53 || (*seq)[seq->getLength() - 1] != 43)
      res = false;
  }
  catch (ExseptionList& e)
  {
    std::cout << e.about_error() << std::endl;
    res = false;
  }
  catch (...)
  {
    std::cout << "Unknown exseption" << std::endl;
    res = false;
  }

  try
  {
    if ((*seq)[0] != 53) 
      res = false;
  }
  catch (ExseptionList& e)
  {
    std::cout << e.about_error() << std::endl;
    res = false;
  }
  catch (...)
  {
    std::cout << "Unknown exseption" << std::endl;
    res = false;
  }

  try
  {
    if ((*seq)[1] != 23) 
      res = false;
  }
  catch (ExseptionList& e)
  {
    std::cout << e.about_error() << std::endl;
    res = false;
  }
  catch (...)
  {
    std::cout << "Unknown exseption" << std::endl;
    res = false;
  }


  try
  {
    int var1 = (*seq)[-1];
  }
  catch (ExseptionList& e)
  {
    std::cout << e.about_error() << std::endl;
  }
  catch (...)
  {
    std::cout << "Unknown exseption" << std::endl;
    res = false;
  }


  try
  {
    int var2 = (*seq)[3];
  }
  catch (ExseptionList& e)
  {
    std::cout << e.about_error() << std::endl;
  }
  catch (...)
  {
    std::cout << "Unknown exseption" << std::endl;
    res = false;
  }

  seq->getSubSeq(sub, 1, 1);
  if (sub->getLength() != 1)
    res = false;

  try
  {
    if ((*sub)[0] != 23 || (*sub)[sub->getLength() - 1] != 23)
      res = false;
  }
  catch (ExseptionList& e)
  {
    std::cout << e.about_error() << std::endl;
    res = false;
  }
  catch (...)
  {
    std::cout << "Unknown exseption" << std::endl;
    res = false;
  }


  return res;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////

enum COMMANDS 
{ 
  PushBack = 0, 
  PushFront = 1, 
  PopBack = 2, 
  PopFront = 3, 
  Clear = 4, 
  EraseItem = 5, 
  InsertItem = 6, 
  GetItem = 7, 
  SetItem = 8, 
  Sort = 9, 
  TestSort = 10,
  GetSubSeq = 11, 
  Test = 12,
  Help = 13,
  End = 14
};

void CPushBack(Sequence<int>* p_seq)
{
  int value;
  std::cout << "PushBack: <int> params" << std::endl;
  std::cin >> value;
  p_seq->push_back(value);
  std::cout << "Seq: ";
  for (unsigned int i(0); i < p_seq->getLength(); i++)
    std::cout << "\"" << (*p_seq)[i] << "\"" << " ";

  std::cout << std::endl;
}

void CPushFront(Sequence<int>* p_seq)
{
  int value;
  std::cout << "PushFront: <int> params" << std::endl;
  std::cin >> value;
  p_seq->push_front(value);
  std::cout << "Seq: ";
  for (unsigned int i(0); i < p_seq->getLength(); i++)
    std::cout << "\"" << (*p_seq)[i] << "\"" << " ";

  std::cout << std::endl;
}

void CPopBack(Sequence<int>* p_seq)
{
  std::cout << "PopBack:" << std::endl;
  try
  {
    p_seq->pop_back();
  }
  catch (ExseptionList& e)
  {
    std::cout << e.about_error() <<std::endl;
  }
  catch (...)
  {
    std::cout << "Unknown exseption" << std::endl;
  }

  std::cout << "Seq: ";
  for (unsigned int i(0); i < p_seq->getLength(); i++)
    std::cout << "\"" << (*p_seq)[i] << "\"" << " ";

  std::cout << std::endl;
}

void CPopFront(Sequence<int>* p_seq)
{
  std::cout << "PopFront:" << std::endl;
  try
  {
    p_seq->pop_front();
  }
  catch (ExseptionList& e)
  {
    std::cout << e.about_error() <<std::endl;
  }
  catch (...)
  {
    std::cout << "Unknown exseption" << std::endl;
  }

  std::cout << "Seq: ";
  for (unsigned int i(0); i < p_seq->getLength(); i++)
    std::cout << "\"" << (*p_seq)[i] << "\"" << " ";

  std::cout << std::endl;
}

void CClear(Sequence<int>* p_seq)
{
  std::cout << "Clear:" << std::endl;
  p_seq->clear();

  std::cout << "Seq: ";
  for (unsigned int i(0); i < p_seq->getLength(); i++)
    std::cout << "\"" << (*p_seq)[i] << "\"" << " ";

  std::cout << std::endl;
}

void CEraseItem(Sequence<int>* p_seq)
{
  int inx(-1);
  std::cout << "EraseItem: <int> item's index param" << std::endl;
  std::cin >> inx;
  std::cout << "Result: ";
  if (p_seq->eraseItem(inx))
    std::cout << "True\n";
  else
    std::cout << "False\n";

  std::cout << "Seq: ";
  for (unsigned int i(0); i < p_seq->getLength(); i++)
    std::cout << "\"" << (*p_seq)[i] << "\"" << " ";

  std::cout << std::endl;
}

void CInsertItem(Sequence<int>* p_seq)
{
  int inx(-1);
  int value;
  std::cout << "InsertItem: <int> item's index and <string> value params" << std::endl;
  std::cin >> inx;
  std::cin >> value;
  std::cout << "Result: ";
  if (p_seq->insertItem(value, inx))
    std::cout << "True\n";
  else
    std::cout << "False\n";

  std::cout << "Seq: ";
  for (unsigned int i(0); i < p_seq->getLength(); i++)
    std::cout << "\"" << (*p_seq)[i] << "\"" << " ";

  std::cout << std::endl;
}

void CGetItem(Sequence<int>* p_seq)
{
  int inx(-1);
  int value(0);
  std::cout << "GetItem: <int> item's index param" << std::endl;
  std::cin >> inx;
  std::cout << "Result: ";
  if (p_seq->getItem(value, inx))
  {
    std::cout << "True, Value: \"" << value << "\"\n";
  }
  else
    std::cout << "False\n";
}

void CSetItem(Sequence<int>* p_seq)
{
  int inx(-1);
  int value(0);
  std::cout << "SetItem: <int> item's index and <int> value params" << std::endl;
  std::cin >> inx;
  std::cin >> value;
  std::cout << "Result: ";
  if (p_seq->setItem(value, inx))
  {
    std::cout << "True\n";
  }
  else
    std::cout << "False\n";

  std::cout << "Seq: ";
  for (unsigned int i(0); i < p_seq->getLength(); i++)
    std::cout << "\"" << (*p_seq)[i] << "\"" << " ";

  std::cout << std::endl;
}

void CSort(Sequence<int>* p_seq)
{
  int n_method(0);
  SortMethod method;
  std::cout << "Sort: Enter index of sort method: 1-BubbleSort; 2-MergeSort; 3-RadixSort;" << std::endl;
  std::cin >> n_method;
  switch (n_method)
  {
    case 1:
      method = SortMethod::BubbleSort;
      std::cout << "Method BubbleSort:";
      break;
    case 2:
      method = SortMethod::MergeSort;
      std::cout << "Method MergeSort:";
      break;
    case 3:
      method = SortMethod::RadixSort;
      std::cout << "Method RadixSort:";
      break;
    default:
      std::cout << "Unknown Method!";
      break;
  }
  std::cout << std::endl;
  if (n_method > 0 && n_method < 4)
  {
    p_seq->sort(method);
    std::cout << "Seq: ";
    for (unsigned int i(0); i < p_seq->getLength(); i++)
      std::cout << "\"" << (*p_seq)[i] << "\"" << " ";

    std::cout << std::endl;
  }

}

void CGetSubSeq(Sequence<int>* p_seq, Sequence<int>* p_sub_seq)
{
  int inx_begin(-1), inx_end(-1);
  std::cout << "GetSubSeq: <int> is first index of sub_seq, <int> is last index of sub_seq" << std::endl;
  std::cin >> inx_begin;
  std::cin >> inx_end;
  
  p_seq->getSubSeq(p_sub_seq, inx_begin, inx_end);

  std::cout << "SubSeq: ";
  for (unsigned int i(0); i < p_sub_seq->getLength(); i++)
    std::cout << "\"" << (*p_sub_seq)[i] << "\"" << " ";

  std::cout << std::endl;
}


void CHelp()
{
  std::string str_command[15] = 
  { 
    "PushBack",
    "PushFront",
    "PopBack",
    "PopFront",
    "Clear",
    "EraseItem",
    "InsertItem",
    "GetItem",
    "SetItem",
    "Sort",
    "TestSort",
    "GetSubSeq",
    "Test",
    "Help",
    "End"
  };
  for (int i(0); i < 15; i++)
    std::cout << "Command numer <" << i << "> is func " << str_command[i] << std::endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{

  SeqArray<int> list;
  list.push_back(7777);
  list.push_back(-34);
  list.push_back(10765);
  list.push_back(-25);
  list.push_back(7);
  list.push_back(-19);
  list.push_back(124);
  list.push_back(17);
  try
  {
    list.sort(SortMethod::RadixSort);
  }
  catch (...)
  {
    std::cout << "ERROR" << std::endl;
  }

  for (unsigned int i(0); i < list.getLength(); i++)
    std::cout << list[i] << std::endl;
  
  SeqArray<int> seq_array;
  SeqArray<int> sub_array;
  if (UnitTest(&seq_array, &sub_array))
    std::cout << "UnitTest for SeqArray success!\n";
  else
    std::cout << "UnitTest for SeqArray very very bad!!!!!\n";

  DLinkList<int> seq_list;
  DLinkList<int> sub_list;
  if (UnitTest(&seq_list, &sub_list))
    std::cout << "UnitTest for DLinkList success!\n";
  else
    std::cout << "UnitTest for DLinkList is very very bad!!!!!\n";

  Sequence<int>* p_seq = nullptr;
  Sequence<int>* p_sub_seq = nullptr;
  Sequence<int>* p_seq_test = nullptr;
  Sequence<int>* p_sub_seq_test = nullptr;
  bool isEnd(false);
  int int_type(0);
  SeqType type = No;

  while (type == No)
  {
    std::cout << "Enter type of Sequence: 1 - DLinkList, 2 - Array; " << std::endl;
    std::cin >> int_type;
    switch (int_type)
    {
    case 1:
      type = SeqType::LinkList;
      std::cout << "DLinkList" << std::endl;;
      break;
    case 2:
      type = SeqType::Array;
      std::cout << "Array" << std::endl;;
      break;
    default:
      std::cout << "Unknown Type!" << std::endl;;
      break;
    }
    std::cout << std::endl;
  }
  if (type == LinkList)
  {
    p_seq = new DLinkList<int>();
    p_sub_seq  = new DLinkList<int>();
  }
  else if (type == Array)
  {
    p_seq = new SeqArray<int>();
    p_sub_seq  = new SeqArray<int>();
  }

  CHelp();
  while(!isEnd)
  {
    int inx_command(-1);
    std::cin >> inx_command;
    COMMANDS command = (COMMANDS)inx_command;
    switch (command)
    {
    case PushBack:
      CPushBack(p_seq);
      break;
    case PushFront:
      CPushFront(p_seq);
      break;
    case PopBack:
      CPopBack(p_seq);
      break;
    case PopFront:
      CPopFront(p_seq);
      break;
    case Clear:
      CClear(p_seq);
      break;
    case EraseItem:
      CEraseItem(p_seq);
      break;
    case InsertItem:
      CInsertItem(p_seq);
      break;
    case GetItem:
      CGetItem(p_seq);
      break;
    case SetItem:
      CSetItem(p_seq);
      break;
    case Sort:
      CSort(p_seq);
      break;
    case GetSubSeq:
      CGetSubSeq(p_seq, p_sub_seq);
      break;
    case TestSort:
      
      if (type == LinkList)
        p_seq_test = new DLinkList<int>();
      else if (type == Array)
        p_seq_test = new SeqArray<int>();

      CTestSort(p_seq_test);

      if (p_seq_test  != nullptr)
      {
        if (type == LinkList)
        {
          delete dynamic_cast<DLinkList<int>*>(p_seq_test);
          p_seq_test = nullptr;
        }
        else if (type == Array)
        {
          delete dynamic_cast<SeqArray<int>*>(p_seq_test);
          p_seq_test = nullptr;
        }
      }
      break;
    case Test:
      if (type == LinkList)
      {
        p_seq_test = new DLinkList<int>();
        p_sub_seq_test  = new DLinkList<int>();
      }
      else if (type == Array)
      {
        p_seq_test = new SeqArray<int>();
        p_sub_seq_test  = new SeqArray<int>();
      }
      if (UnitTest(p_seq_test, p_sub_seq_test))
        std::cout << "Tests were passed successfully\n";
      else
        std::cout << "ERROR: Tests were passed unsuccessfully\n";

      if (p_seq_test  != nullptr && p_sub_seq_test != nullptr)
      {
        if (type == LinkList)
        {
          delete dynamic_cast<DLinkList<int>*>(p_seq_test);
          delete dynamic_cast<DLinkList<int>*>(p_sub_seq_test);
          p_seq_test = nullptr;
          p_sub_seq_test = nullptr;
        }
        else if (type == Array)
        {
          delete dynamic_cast<SeqArray<int>*>(p_seq_test);
          delete dynamic_cast<SeqArray<int>*>(p_sub_seq_test);
          p_seq_test = nullptr;
          p_sub_seq_test = nullptr;
        }
      }
      break;
    case Help:
      CHelp();
      break;
    case End:
      isEnd = true;
      break;
    default:
      isEnd = true;
      std::cout << "Unknown command! Delete brain\n";
      break;
    }
  }

  if (p_seq != nullptr && p_sub_seq != nullptr)
  {
    if (type == LinkList)
    {
      delete dynamic_cast<DLinkList<int>*>(p_seq);
      delete dynamic_cast<DLinkList<int>*>(p_sub_seq);
    }
    else if (type == Array)
    {
      delete dynamic_cast<SeqArray<int>*>(p_seq);
      delete dynamic_cast<SeqArray<int>*>(p_sub_seq);
    }
  }

  int a(0);
  std::cin >> a;

  return 0;
}
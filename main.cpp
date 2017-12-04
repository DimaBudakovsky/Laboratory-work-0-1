#include "d_link_list.h"
#include "d_link_list.cpp"//подключаем для избежания проблемы с линковкой (для шаблонов)
#include <iostream>
#include <string>
#include <vector>

bool UnitTest()
{
  bool res(true);
  DLinkList<int> list;
  if (list.getLength() != 0)
    res = false;

  list.push_back(23);

  if (list.getLength() != 1)
    res = false;

  try
  {
    if (list[0] != 23 || list[list.getLength() - 1] != 23)
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
    int var1 = list[1];
    int var2 = list[-1];
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
    int var2 = list[-1];
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

  list.push_back(43);

  if (list.getLength() != 2)
    res = false;

  try
  {
    if (list[0] != 23 || list[list.getLength() - 1] != 43)
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
    int var1 = list[-1];
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
    int var2 = list[2];
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

  list.push_front(53);

  if (list.getLength() != 3)
    res = false;

  try
  {
    if (list[0] != 53 || list[list.getLength() - 1] != 43)
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
    if (list[0] != 53) 
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
    if (list[1] != 23) 
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
    int var1 = list[-1];
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
    int var2 = list[3];
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

  DLinkList<int> sub = list.getSubList(1, 1);
  if (sub.getLength() != 1)
    res = false;

  try
  {
    if (sub[0] != 23 || sub[sub.getLength() - 1] != 23)
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

int main()
{
  if (UnitTest())
    std::cout << "UnitTest success!\n";
  else
    std::cout << "It's very very bad!!!!!\n";

  int a(0);
  std::cin >> a;

  return 0;
}
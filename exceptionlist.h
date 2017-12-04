#pragma once
#include <string>
#include <sstream>

class ExseptionList
{
  public:
    virtual std::string about_error() = 0;
};

class ExseptionListIter: public ExseptionList
{
public:
  ExseptionListIter()
  {

  }
  ~ExseptionListIter()
  {

  }

  std::string about_error()
  {
    return std::string("ExsepsionListIter: Error operator *, incorrected iterator");
  }
};

class ExseptionListPopBack: public ExseptionList
{

public:
    ExseptionListPopBack()
    {

    }
    ~ExseptionListPopBack()
    {

    }

    std::string about_error()
    {
      return std::string("ExsepsionListIter: Error function pop_back");
    }
};

class ExseptionListPopFront: public ExseptionList
{

public:
  ExseptionListPopFront()
  {

  }
  ~ExseptionListPopFront()
  {

  }

  std::string about_error()
  {
    return std::string("ExsepsionListIter: Error function pop_front");
  }
};

class ExseptionListAccess: public ExseptionList
{
public:
  ExseptionListAccess(const int& inx)
  {
    m_error_inx = inx;
  }
  ~ExseptionListAccess()
  {

  }

  std::string about_error()
  {
    std::ostringstream oss;
    oss << m_error_inx;
    std::string str_message("ExsepsionListIter: Error operator [] ");
    str_message += "Index " + oss.str() + " is out of length list!";
    return str_message;
  }

private:
  int m_error_inx;
};
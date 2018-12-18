// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : bitField(mp)
{
  if (mp < 0)
  {
    throw(1);
  }
  maxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : bitField(s.maxPower)
{
  bitField = s.bitField;
  maxPower = s.maxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : bitField(bf.GetLength())
{
  maxPower = bf.GetLength();
  bitField = bf;
}

TSet::operator TBitField()
{
  TBitField ResField(maxPower);
  ResField = bitField;
  return ResField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
  return maxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{

  return bitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
  bitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
  bitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
  bitField = s.bitField;
  maxPower = s.maxPower;
  return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{

  if (s.maxPower == maxPower)
  {
    return (bitField == s.bitField);
  }
  return 0;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
  if (s.maxPower == maxPower)
  {
    return (bitField != s.bitField);
  }
  return 1;
}

TSet TSet::operator+(const TSet &s) // объединение
{
  if (maxPower > s.maxPower)
  {
    TSet res(maxPower);
    res.bitField = bitField | s.bitField;
    return res;
  }
  else
  {
    TSet res(s.maxPower);
    res.bitField = bitField | s.bitField;
    return res;
  }
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
  bitField.SetBit(Elem);
  return *this;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
  bitField.ClrBit(Elem);
  return *this;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
  if (maxPower > s.maxPower)
  {
    TSet res(maxPower);
    res.bitField = bitField & s.bitField;
    return res;
  }
  else
  {
    TSet res(s.maxPower);
    res.bitField = bitField & s.bitField;
    return res;
  }
}

TSet TSet::operator~(void) // дополнение
{
  TSet res(maxPower);
  res.bitField = ~bitField;
  return res;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
  istr >> s.bitField;
  return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
  ostr << s.bitField;
  return ostr;
}

// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
  if (len < 0)
  {
    throw(1);
  }
  bitLen = len;
  memLen = bitLen / (sizeof(TELEM) * 8) + 1;
  pMem = new TELEM[memLen];
  for (int i = 0; i < memLen; i++)
    pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{

  if (bf.pMem != pMem)
  {
    bitLen = bf.bitLen;
    memLen = bf.memLen;
    pMem = new TELEM[memLen];
    for (int i = 0; i < memLen; i++)
      pMem[i] = bf.pMem[i];
  }
}

TBitField::~TBitField()
{
  if (pMem)
    delete[]pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
  if ((n < 0) || (n > bitLen))
    throw (1);
  return  n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
  if ((n < 0) || (n > bitLen))
    throw (1);
  return (1 << (n % (8 * sizeof(TELEM))));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return bitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
  pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
  pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
  return (pMem[GetMemIndex(n)] & GetMemMask(n)) != 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
  if (bf.pMem != pMem)
  {
    if (pMem)
      delete[] pMem;
    bitLen = bf.bitLen;
    memLen = bf.memLen;
    pMem = new TELEM[memLen];
    for (int i = 0; i < memLen; i++)
      pMem[i] = bf.pMem[i];
  }
  return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
  if (bf.bitLen == bitLen)
  {
    int res = 0;
    for (int i = 0; i < memLen; i++)
      res |= (pMem[i] ^ bf.pMem[i]);
    return (res == 0);
  }
  return 0;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  if (bf.bitLen == bitLen)
  {
    int res = 0;
    for (int i = 0; i < memLen; i++)
      res |= (pMem[i] ^ bf.pMem[i]);
    return (res > 0);
  }
  return 1;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
  if (bitLen >= bf.bitLen)
  {
    TBitField ResField(bitLen);
    for (int i = 0; i < memLen; i++)
      ResField.pMem[i] = pMem[i] | bf.pMem[i];
    for (int i = bf.memLen; i < memLen; i++)
      ResField.pMem[i] = pMem[i];
    return ResField;
  }
  else
  {
    TBitField ResField(bf.bitLen);
    for (int i = 0; i < memLen; i++)
      ResField.pMem[i] = pMem[i] | bf.pMem[i];
    for (int i = memLen; i < bf.memLen; i++)
      ResField.pMem[i] = bf.pMem[i];
    return ResField;
  }

}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
  if (bitLen >= bf.bitLen)
  {
    TBitField ResField(bitLen);
    for (int i = 0; i < bf.memLen; i++)
      ResField.pMem[i] = pMem[i] & bf.pMem[i];
    for (int i = bf.memLen; i < memLen; i++)
      ResField.pMem[i] = 0;
    return ResField;
  }
  else
  {
    TBitField ResField(bf.bitLen);
    for (int i = 0; i < memLen; i++)
      ResField.pMem[i] = pMem[i] & bf.pMem[i];
    for (int i = memLen; i < bf.memLen; i++)
      ResField.pMem[i] = 0;
    return ResField;
  }
}

TBitField TBitField::operator~(void) // отрицание
{
  TBitField ResField(bitLen);
  int i;
  TELEM buf = ~((TELEM)0);
  for (i = 0; i < memLen; i++)
    ResField.pMem[i] = ~pMem[i];
  ResField.pMem[memLen - 1] &= buf >> (memLen * sizeof(TELEM) * 8 - bitLen);
  return ResField;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
  char ch;
  for (int i = 0; i < bf.bitLen; i++)
  {
    istr >> ch;
    if (ch == '0')
      bf.ClrBit(i);
    else if (ch == '1')
      bf.SetBit(i);
    else break;
  }
  return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
  for (int i = 0; i < bf.bitLen; i++)
    cout << bf.GetBit(i);
  cout << endl;
  return ostr;
}


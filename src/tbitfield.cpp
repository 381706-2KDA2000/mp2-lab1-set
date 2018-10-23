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
	BitLen = len;
	MemLen = BitLen / (sizeof(TELEM) * 8) + 1;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	if(pMem)
		delete[]pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if ((n < 0) || (n > BitLen))
		throw (1);
	return  n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{	
	if ((n < 0) || (n > BitLen))
		throw (1);
	return (1 << (n % (8 * sizeof(TELEM))));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
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
  return (pMem[GetMemIndex(n)] & GetMemMask(n));
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (bf.pMem != pMem)
	{
		if (pMem)
			delete[] pMem;
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
			pMem[i] = bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (bf.BitLen == BitLen)
	{
		int res = 0;
		for (int i = 0; i < MemLen; i++)
			res |= (pMem[i] ^ bf.pMem[i]);
		return (res == 0);
	}
	return 0;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (bf.BitLen == BitLen)
	{
		int res = 0;
		for (int i = 0; i < MemLen; i++)
			res |= (pMem[i] ^ bf.pMem[i]);
		return (res > 0);
	}
	return 1;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	if (BitLen >= bf.BitLen)
	{
		TBitField ResField(BitLen);
		for (int i = 0; i < MemLen; i++)
			ResField.pMem[i] = pMem[i] | bf.pMem[i];
		for (int i = bf.MemLen; i < MemLen; i++)
			ResField.pMem[i] = pMem[i];
		return ResField;
	}
	else
	{
		TBitField ResField(bf.BitLen);
		for (int i = 0; i < MemLen; i++)
			ResField.pMem[i] = pMem[i] | bf.pMem[i];
		for (int i = MemLen; i < bf.MemLen; i++)
			ResField.pMem[i] = pMem[i];
		return ResField;
	}

}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	if (BitLen >= bf.BitLen)
	{
		TBitField ResField(BitLen);
		for (int i = 0; i < bf.MemLen; i++)
			ResField.pMem[i] = pMem[i] & bf.pMem[i];
		for (int i = bf.MemLen; i < MemLen; i++)
			ResField.pMem[i] = 0;
		return ResField;
	}
	else
	{
		TBitField ResField(bf.BitLen);
		for (int i = 0; i < MemLen; i++)
			ResField.pMem[i] = pMem[i] & bf.pMem[i];
		for (int i = MemLen; i < bf.MemLen; i++)
			ResField.pMem[i] = 0;
		return ResField;
	}
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField ResField(BitLen);
	int i;
	TELEM buf = ~((TELEM)0);
	for (i = 0; i < MemLen; i++)
		ResField.pMem[i] = ~pMem[i];
	ResField.pMem[MemLen - 1] &= buf >> (MemLen * sizeof(TELEM) * 8 - BitLen);
	return ResField ;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	return ostr;
}

// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
	if (mp < 0)
	{
		throw(1);
	}
	MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.MaxPower)
{
	BitField = s.BitField;
	MaxPower = s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf.GetLength())
{
	MaxPower = bf.GetLength();
	BitField = bf;
}

TSet::operator TBitField()
{
	TBitField ResField(MaxPower);
	ResField = BitField;
	return ResField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{

    return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	BitField = s.BitField;
	MaxPower = s.MaxPower;
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	
	if (s.MaxPower == MaxPower)
	{
		return (BitField == s.BitField);
	}
	return 0;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	if (s.MaxPower == MaxPower)
	{
		return (BitField != s.BitField);
	}
	return 1;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	if (MaxPower > s.MaxPower)
	{
		TSet res(MaxPower);
		res.BitField = BitField | s.BitField;
		return res;
	}
	else
	{
		TSet res(s.MaxPower);
		res.BitField = BitField | s.BitField;
		return res;
	}
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	BitField.SetBit(Elem);
	return *this;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	BitField.ClrBit(Elem);
	return *this;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	if (MaxPower > s.MaxPower)
	{
		TSet res(MaxPower);
		res.BitField = BitField & s.BitField;
		return res;
	}
	else
	{
		TSet res(s.MaxPower);
		res.BitField = BitField & s.BitField;
		return res;
	}
}

TSet TSet::operator~(void) // дополнение
{
	TSet res(MaxPower);
	res.BitField = ~BitField;
	return res;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	return ostr;
}

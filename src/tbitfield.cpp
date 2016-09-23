// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	MemLen = len / (sizeof(TELEM)* 8) + 1;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = 0;
	BitLen = len;
	if (BitLen<0)
		throw "Negative value";
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	if (BitLen != bf.BitLen)
	{
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
	}
	pMem = new TELEM[bf.MemLen];
	for (int i = 0; i < bf.MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete[]pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n<0 || n>(BitLen - 1))
		throw "Negative value";
	return (n / (sizeof(TELEM)* 8));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if (n<0 || n>(BitLen - 1))
		throw "Negative value";
	return 1 << (n - (sizeof (TELEM)* 8 * GetMemIndex(n)));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n<0 || n>(BitLen - 1))
		throw "Negative value";
	pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] | GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n<0 || n>(BitLen - 1))
		throw "Negative value";
	pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] & (~GetMemMask(n));
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n<0 || n>(BitLen - 1))
		throw "Negative value";
	int number;
	number = GetMemIndex(n);
	return (pMem[number] & GetMemMask(n)) >> (n - (sizeof (TELEM)* 8 * GetMemIndex(n)));
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (this != &bf) //сравнение указателей
	{
		if (BitLen != bf.BitLen)
		{
			BitLen = bf.BitLen;
			MemLen = bf.MemLen;
			delete[]pMem;
		}
		pMem = new TELEM[bf.MemLen];
		for (int i = 0; i < bf.MemLen; i++)
			pMem[i] = bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen)
      return 0;
	else
	for (int i = 0; i < MemLen; i++)
	if (pMem[i] != bf.pMem[i])
		return 0;
	return 1;
  }

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen)
		return 1;
	else
	for (int i = 0; i < MemLen; i++)
	if (pMem[i] != bf.pMem[i])
		return 1;
  return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{

	return *this;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	return *this;
}

TBitField TBitField::operator~(void) // отрицание
{
	for (int i = 0; i < MemLen; i++)
		pMem[i] = ~pMem[i];
	for (int i = (BitLen - sizeof(TELEM)* 8 * (MemLen - 1)); i < sizeof(TELEM)* 8; i++)
		pMem[MemLen - 1] = pMem[MemLen - 1] & (~(1 << i));
	return *this;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	istr >> bf.BitLen;
	if (bf.BitLen<0)
		throw "Negative value";
	for (int i = 0; i < bf.BitLen; i++)
		istr >> bf.pMem[i];
		bf.MemLen = bf.BitLen / (sizeof(TELEM)* 8) + 1;

	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{

	for (int i = 0; i < bf.BitLen; i++)
		ostr << bf.GetBit(i);
	return ostr;
}

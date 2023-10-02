// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);

TBitField::TBitField(int len) {
    this->BitLen = len;
    this->pMem = new TELEM[this->BitLen];
    this->MemLen = (this->BitLen - 1) / (sizeof(TELEM) * 8) + 1;
}

TBitField::TBitField(const TBitField& bf) { // конструктор копирования
    this->BitLen = bf.BitLen;
    this->MemLen = bf.MemLen;
    this->pMem = new TELEM[this->BitLen];
    for (int i = 0; i < this->BitLen; i++) {
        this->pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField() {
    delete[this->BitLen] pMem;
    this->pMem = nullptr;
}

int TBitField::GetMemIndex(const int n) const { // индекс Мем для бита n
    if (n > this->BitLen - 1) {
        throw std::out_of_range("Bit index more than BitLen");
    }
    return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const {    // битовая маска для бита n
    if (n > this->BitLen - 1) {
        throw std::out_of_range("Bit index more than BitLen");
    }
    return pow(2, n % 8);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const {  // получить длину (к-во битов)
    return this->BitLen;
}

void TBitField::SetBit(const int n) {   // установить бит
    if (n > this->BitLen - 1) {
        throw std::out_of_range("Bit index more than BitLen");
    }
    this->pMem[n] = 1;
}

void TBitField::ClrBit(const int n) {   // очистить бит
    if (n > this->BitLen - 1) {
        throw std::out_of_range("Bit index more than BitLen");
    }
    this->pMem[n] = 0;
}

int TBitField::GetBit(const int n) const {  // получить значение бита
    if (n > this->BitLen - 1) {
        throw std::out_of_range("Bit index more than BitLen");
    }
    return this->pMem[n];
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) {  // присваивание
    delete[this->BitLen] this->pMem;
    this->BitLen = bf.BitLen;
    this->MemLen = bf.MemLen;
    this->pMem = new TELEM[this->BitLen];
    for (int i = 0; i < this->BitLen; i++) {
        this->pMem[i] = bf.pMem[i];
    }

    return *this;
}

int TBitField::operator==(const TBitField& bf) const {  // сравнение
    if ((this->BitLen != bf.BitLen) or (this->MemLen != bf.MemLen)) {
        return 0;
    }

    for (int i = 0; i < this->BitLen; i++) {
        if (this->pMem[i] != bf.pMem[i]) {
            return 0;
        }
    }

    return 1;
}

int TBitField::operator!=(const TBitField& bf) const {  // сравнение
    if (*this == bf) {
        return 0;
    }
    return 1;
}

TBitField TBitField::operator|(const TBitField& bf) {   // операция "или"
    if (this->BitLen != bf.BitLen) {
        throw std::length_error("Diffrent sizes of fields");
    }

    TBitField bf_new(this->BitLen);
    for (int i = 0; i < this->BitLen; i++) {
        bf_new.pMem[i] = this->pMem[i] | bf.pMem[i];
    }

    return bf_new;
}

TBitField TBitField::operator&(const TBitField& bf) {   // операция "и"
    if (this->BitLen != bf.BitLen) {
        throw std::length_error("Diffrent sizes of fields");
    }

    TBitField bf_new(this->BitLen);
    for (int i = 0; i < this->BitLen; i++) {
        bf_new.pMem[i] = this->pMem[i] & bf.pMem[i];
    }

    return bf_new;
}

TBitField TBitField::operator~(void) {  // отрицание
    TBitField bf_new(this->BitLen);
    for (int i = 0; i < this->BitLen; i++) {
        bf_new.pMem[i] = !this->pMem[i];
    }

    return bf_new;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) { // ввод
    int temp;
    for (int i = 0; i < bf.GetLength(); i++) {
        istr >> temp;
        if (temp == 1) {
            bf.SetBit(i);
        }
        else if (temp == 0) {
            bf.ClrBit(i);
        }
        else {
            throw std::invalid_argument("Argument must be '1' or '0'");
        }
    }
    return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) {   // вывод
    for (int i = 0; i < bf.GetLength(); i++) {
        ostr << bf.GetBit(i);
    }
    return ostr;
}

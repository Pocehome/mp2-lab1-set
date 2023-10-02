// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);
static TSet FAKE_SET(1);

TSet::TSet(int mp) : MaxPower(mp), BitField(mp) {}

// конструктор копирования
TSet::TSet(const TSet& s) : MaxPower(s.MaxPower), BitField(s.BitField) {}

// конструктор преобразования типа
TSet::TSet(const TBitField& bf) : MaxPower(bf.GetLength()), BitField(bf) {}

TSet::operator TBitField() {
    return this->BitField;
}

int TSet::GetMaxPower(void) const { // получить макс. к-во эл-тов
    return this->MaxPower;
}

int TSet::IsMember(const int Elem) const {  // элемент множества?
    return this->BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) {    // включение элемента множества
    this->BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) {    // исключение элемента множества
    this->BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet& s) {  // присваивание
    this->MaxPower = s.MaxPower;
    this->BitField = s.BitField;
    return *this;
}

int TSet::operator==(const TSet& s) const { // сравнение
    if (this->BitField != s.BitField) {
        return 0;
    }
    return 1;
}

int TSet::operator!=(const TSet& s) const { // сравнение
    if (this->BitField != s.BitField) {
        return 1;
    }
    return 0;
}

TSet TSet::operator+(const TSet& s) {   // объединение
    TSet temp(*this);
    temp.BitField = this->BitField | s.BitField;
    return temp;
}

TSet TSet::operator+(const int Elem) {  // объединение с элементом
    TSet temp(*this);
    temp.InsElem(Elem);
    return temp;
}

TSet TSet::operator-(const int Elem) {  // разность с элементом
    TSet temp(*this);
    temp.DelElem(Elem);
    return temp;
}

TSet TSet::operator*(const TSet& s) {   // пересечение
    TSet temp(*this);
    temp.BitField = this->BitField & s.BitField;
    return temp;
}

TSet TSet::operator~(void) {    // дополнение
    TSet temp(*this);
    temp.BitField = ~this->BitField;
    return temp;
}

// перегрузка ввода/вывода

istream& operator>>(istream& istr, TSet& s) {   // ввод
    int temp;
    for (int i = 0; i < s.GetMaxPower(); i++) {
        istr >> temp;
        if (temp == 1) {
            s.InsElem(i);
        }
        else if (temp == 0) {
            s.DelElem(i);
        }
        else {
            throw std::invalid_argument("Argument must be '1' or '0'");
        }
    }
    return istr;
}

ostream& operator<<(ostream& ostr, const TSet& s) { // вывод
    for (int i = 0; i < s.GetMaxPower(); i++) {
        ostr << s.BitField.GetBit(i);
    }
    return ostr;
}

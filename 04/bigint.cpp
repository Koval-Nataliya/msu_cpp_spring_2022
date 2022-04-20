#include <string>
#include <iostream>
#include <cstddef>
#include "bigint.hpp"

void BigInt::setDataSize(int32_t n){
    dataSize = n;
    data = new int32_t[n]();
}

BigInt::BigInt(){
    dataSize = 0;
    data = nullptr;
    neg = 0;
}

BigInt::~BigInt(){
    if(data)
        delete[] data;
}
//Конструктор из строки
BigInt::BigInt(std::string str){
    neg = str[0] == '-';
    size_t n = str.size() - neg;
    setDataSize(n);
    for(size_t i = 0; i < n; ++i)
        data[i] = str[n - i - 1 + neg] - '0';
}

//Конструктор из числа
BigInt::BigInt(int32_t x){
    int32_t t = x;
    size_t n = 0;
    while(t){
        t /= 10;
        ++n;
    }
    
    if(x == 0){
        n = 1;
    }

    neg = x < 0;
    if(neg)
        x = -x;
    
    setDataSize(n);

    for(size_t i = 0; i < n; ++i){
        data[i] = x % 10;
        x /= 10;
    }
}

//Конструктор копирования
BigInt::BigInt(const BigInt &bigInt){
    size_t n = bigInt.dataSize;
    setDataSize(n);
    neg = bigInt.neg;
    
    for(size_t i = 0; i < n; ++i)
        data[i] = bigInt.data[i];
}

//Конструктор из массива
BigInt::BigInt(int32_t *arr, size_t n, bool negativ){
    setDataSize(n);
    neg = negativ;
    for(size_t i = 0; i < n; ++i)
        data[i] = arr[i];
}

//Оператор копирования
BigInt& BigInt::operator= (const BigInt &bigInt){
    if(data)
        delete[] data;
    size_t n = bigInt.dataSize;
    setDataSize(n);

    for(size_t i = 0; i < n; ++i)
        data[i] = bigInt.data[i];
    
    return *this;
}

//Конструктор перемещения
BigInt::BigInt(BigInt &&bigInt): dataSize(bigInt.dataSize), data(bigInt.data), neg(bigInt.neg){
	bigInt.dataSize = 0;
	bigInt.data = nullptr;
}
 
//Оператор присваивания перемещением
BigInt& BigInt::operator=(BigInt &&bigInt){
	if (&bigInt == this)
		return *this;
 
	delete[] data;
 
	dataSize = bigInt.dataSize;
	data = bigInt.data;
    neg = bigInt.neg;
	bigInt.neg = 0;
	bigInt.data = nullptr;
    bigInt.dataSize = 0;
 
	return *this;
}

//Арифметические/логические операторы

BigInt BigInt::operator-() const {
    BigInt a(this->data, this->dataSize, this->neg ^ 1);
    return a;
}

BigInt operator*(const BigInt left, const BigInt right){
    if(left == 0 || right == 0)
        return 0;
    size_t n = left.dataSize, m = right.dataSize;
    size_t max = n + m + 1;
    int32_t* res = new int32_t[max]();
    for (size_t i = 0; i < n; ++i){
        int32_t dopValue = 0;
        for (size_t j = 0; j < m || dopValue; ++j) {
            int32_t cur = res[i+j] + left.data[i]*(j < m ? right.data[j] : 0) + dopValue;
            res[i+j] = cur % 10;
            dopValue = cur / 10;
        }
    }

    while (max > 0 && res[max - 1] == 0) --max;
    BigInt ans(res, max, left.neg ^ right.neg);
    delete[] res;
    return ans;
}


bool operator== (const BigInt &b1, const BigInt &b2){
    if(b1.neg != b2.neg || b1.dataSize != b2.dataSize)
        return false;
    size_t n = b1.dataSize;
    for(size_t i = 0; i < n; ++i)
        if(b1.data[i] != b2.data[i])
            return false;
    return true;
}

bool operator!= (const BigInt &b1, const BigInt &b2){
    return !(b1 == b2);
}

bool operator> (const BigInt &b1, const BigInt &b2){
    if(b1 == b2)
        return false;
    if(b1.neg != b2.neg)
        return !b1.neg;

    size_t n = b1.dataSize, m = b2.dataSize;
    if(n > m)
        return !b1.neg;
    if(n < m)
        return b1.neg;

    size_t i = n - 1;
    while(b1.data[i] == b2.data[i]){
        if(i == 0)
            break;
        --i;
    }

    if(b1.neg)
        return !(b1.data[i] > b2.data[i]);
    
    return b1.data[i] > b2.data[i];
}

bool operator<= (const BigInt &b1, const BigInt &b2){
    return !(b1 > b2);
}

bool operator< (const BigInt &b1, const BigInt &b2){
    if(b1 == b2)
        return false;
    if(b1.neg != b2.neg)
        return b1.neg;

    size_t n = b1.dataSize, m = b2.dataSize;
    if(n > m)
        return b1.neg;
    if(n < m)
        return !b1.neg;

    size_t i = n - 1;
    while(b1.data[i] == b2.data[i]){
        if(i == 0)
            break;
        --i;
    }

    if(b1.neg)
        return (b1.data[i] > b2.data[i]);
    
    return !(b1.data[i] > b2.data[i]);
}

bool operator>= (const BigInt &b1, const BigInt &b2) {
    return !(b1 < b2);
}

BigInt operator+(const BigInt left, const BigInt right){
    if(left.neg != right.neg){
        if(left.neg){
            return right- (-left);
        } else {
            return left - (-right);
        }
    }

    bool dopValue = 0;
    int32_t *a = left.data, *b = right.data;
    size_t n = left.dataSize, m = right.dataSize;
    size_t max = n > m ? n : m;
    ++max;
    int32_t* res = new int32_t[max]();
    bool neg = left.neg && right.neg;

    for (size_t i = 0; i < max || dopValue; ++i) {
        res[i] = (i < n ? a[i] : 0) + (i < m ? b[i] : 0) + dopValue;
        dopValue = res[i] >= 10;
        if (dopValue)
            res[i] -= 10;
    }
    if(res[max - 1] == 0)
        --max;
    BigInt ans(res, max, neg);
    delete[] res;
    return ans;
}

BigInt operator-(const BigInt left, const BigInt right){
    if(left.neg && right.neg)
        return -((-left) - (-right));
    if(left.neg && !right.neg)
        return -((-left) + right);
    if(!left.neg && right.neg)
        return left + (-right);
    if(left == right)
        return 0;

    bool dopValue = 0;
    size_t n = left.dataSize, m = right.dataSize;
    if(left > right) {
        int32_t* res = new int32_t[n]();
        for(size_t i = 0; i < n; ++i)
            res[i] = left.data[i];
        
        for (size_t i = 0; i < m || dopValue; ++i) {
            res[i] -= dopValue + (i < m ? right.data[i] : 0);
            dopValue = res[i] < 0;
            if (dopValue)  res[i] += 10;
        }
        while (n > 0 && res[n - 1] == 0) --n;
        BigInt ans(res, n, 0);
        delete[] res;
        return ans;
    } else {
        int32_t* res = new int32_t[m]();
        for(size_t i = 0; i < m; ++i)
            res[i] = right.data[i];

        for (size_t i = 0; i < n || dopValue; ++i) {
            res[i] -= dopValue + (i < n ? left.data[i] : 0);
            dopValue = res[i] < 0;
            if (dopValue)  res[i] += 10;
        }
        while (m > 0 && res[m - 1] == 0) --m;
        BigInt ans(res, m, 1);
        delete[] res;
        return ans;
    }
}


//Вывод
std::ostream& operator<< (std::ostream &out, const BigInt &bigInt){
    if(bigInt.neg)
        out << "-";
    for(int32_t i = bigInt.dataSize - 1; i >= 0; --i)
        out << bigInt.data[i];
 
    return out;
}

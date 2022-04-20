#pragma once

class BigInt {
    private:

    size_t dataSize;

    int32_t* data;

    bool neg;

    void setDataSize(int32_t n);

    public:

    BigInt();

    BigInt(std::string str);

    BigInt(int32_t x);

    BigInt(int32_t *arr, size_t n, bool negativ);

    BigInt(const BigInt &bigInt);

    BigInt(BigInt &&bigInt);

    ~BigInt();

    BigInt& operator= (const BigInt &bigInt);

    BigInt& operator= (BigInt &&bigInt);

    BigInt operator-() const;

    friend BigInt operator+ (const BigInt left, const BigInt right);

    friend BigInt operator- (const BigInt left, const BigInt right);

    friend BigInt operator* (const BigInt left, const BigInt right);

    friend bool operator== (const BigInt &b1, const BigInt &b2);

    friend bool operator!= (const BigInt &b1, const BigInt &b2);

    friend bool operator> (const BigInt &b1, const BigInt &b2);

    friend bool operator<= (const BigInt &b1, const BigInt &b2);

    friend bool operator< (const BigInt &b1, const BigInt &b2);
    
    friend bool operator>= (const BigInt &b1, const BigInt &b2);

    friend std::ostream& operator<< (std::ostream &out, const BigInt &bigInt);

    bool empty(){
        return dataSize == 0 && data == nullptr;
    }
};

#pragma once
namespace OxygenMath
{
    using real = double;
    // NumberField
    // T belongs to any number field, that is, it is closed to addition, subtraction, multiplication and division
    // For example:
    // For any T_1 T_2 belongs to P
    // T_1+T_2 also belongs to P; T_1-T_2 also belongs to P ; T_1*T_2 also belongs to P ; T_1/T_2 also belongs to P ;
    template <typename T>
    class NumberField
    {
    private:
        T value;

    public:
        NumberField() : value(T{}) {}
        NumberField(const T& val) : value(val) {}
        NumberField(T&& val) : value(std::move(val)) {}
        NumberField(const NumberField&) = default;
        NumberField(NumberField&&) = default;
        NumberField& operator=(const NumberField&) = default;
        NumberField& operator=(NumberField&&) = default;
        ~NumberField() = default;

        T get() const {
            return value;
        }
        
        void set(const T& t) {
            value = t;
        }
        
        static T zero() {
            return T{};
        }
        
        T inverse() const {
            return T{1} / value;
        }
        
        NumberField operator+(const NumberField& other) const {
            return NumberField(value + other.value);
        }
        
        NumberField operator-(const NumberField& other) const {
            return NumberField(value - other.value);
        }
        
        NumberField operator*(const NumberField& other) const {
            return NumberField(value * other.value);
        }
        
        NumberField operator/(const NumberField& other) const {
            return NumberField(value / other.value);
        }
        
        NumberField& operator+=(const NumberField& other) {
            value += other.value;
            return *this;
        }
        
        NumberField& operator-=(const NumberField& other) {
            value -= other.value;
            return *this;
        }
        
        NumberField& operator*=(const NumberField& other) {
            value *= other.value;
            return *this;
        }
        
        NumberField& operator/=(const NumberField& other) {
            value /= other.value;
            return *this;
        }
        
        bool operator==(const NumberField& other) const {
            return value == other.value;
        }
        
        bool operator!=(const NumberField& other) const {
            return value != other.value;
        }
        
        // Conversion operator to allow implicit conversion to T
        operator T() const {
            return value;
        }
    };

}
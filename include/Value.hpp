#ifndef _VALUE_HPP
#define _VALUE_HPP

#include <vector>

#include "Type.hpp"

class Value;

class ValueHandle {
    Value * v_;
public:
    explicit ValueHandle(std::nullptr_t) = delete;
    explicit ValueHandle(Value * v);
    ValueHandle(const ValueHandle & v);
    ValueHandle(ValueHandle && v);

    Value & operator* ();
    const Value & operator* () const;

    Value * operator-> ();
    const Value * operator-> () const;

    ValueHandle & operator= (const ValueHandle & v);
    ValueHandle & operator= (ValueHandle && v);

    void swap(ValueHandle & v);

    ~ValueHandle();
};

class Value {
public:
    virtual TypeHandle GetType() const = 0;
    virtual ValueHandle Clone() const = 0;
    virtual ~Value() = default;
};

class FPValue : public Value {
    double val_;
public:
    FPValue(double val);
    FPValue(const FPValue & v);

    virtual TypeHandle GetType() const;
    virtual ValueHandle Clone() const;
    virtual ~FPValue() = default;
};

class BoolValue : public Value {
    bool val_;
public:
    BoolValue(bool val);
    BoolValue(const BoolValue & v);

    virtual TypeHandle GetType() const;
    virtual ValueHandle Clone() const;
    virtual ~BoolValue() = default;
};

class VectorValue : public Value {
    TypeHandle t_;
    std::vector<ValueHandle > vals_;

public:
    VectorValue(TypeHandle && t, std::vector<ValueHandle > && vals);
    VectorValue(const VectorValue & v);

    virtual TypeHandle GetType() const;
    virtual ValueHandle Clone() const;

    size_type Size() const;
    
    virtual ~VectorValue() = default;
};

#endif // _VALUE_HPP

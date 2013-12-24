#ifndef _VALUE_HPP
#define _VALUE_HPP

#include <vector>

#include "Type.hpp"

class Value {
public:
    virtual Handle<Type> GetType() const = 0;
    virtual Handle<Value> Clone() const = 0;
    virtual ~Value() = default;
};

class FPValue : public Value {
    double val_;
public:
    FPValue(double val);
    FPValue(const FPValue & v);

    virtual Handle<Type> GetType() const;
    virtual Handle<Value> Clone() const;
    virtual ~FPValue() = default;
};

class BoolValue : public Value {
    bool val_;
public:
    BoolValue(bool val);
    BoolValue(const BoolValue & v);

    virtual Handle<Type> GetType() const;
    virtual Handle<Value> Clone() const;
    virtual ~BoolValue() = default;
};

class VectorValue : public Value {
    Handle<Type> t_;
    std::vector<Handle<Value> > vals_;

public:
    VectorValue(Handle<Type> && t, std::vector<Handle<Value> > && vals);
    VectorValue(const VectorValue & v);

    virtual Handle<Type> GetType() const;
    virtual Handle<Value> Clone() const;

    size_type Size() const;
    
    virtual ~VectorValue() = default;
};

#endif // _VALUE_HPP

#ifndef _TYPE_HPP
#define _TYPE_HPP

#include <iostream>
#include <map>
#include <string>
#include <exception>
#include <stdexcept>
#include <memory>

template <typename T>
using Handle = std::unique_ptr<T>;

using size_type = std::size_t;

class Type {
    virtual bool Equal(const Type & other) const = 0;
public:
    bool operator== (const Type & other) const;

    virtual Handle<Type> Clone() const = 0;
    virtual std::string ToString() const = 0;

    virtual ~Type() = default;
};

class SimpleType : public Type { 
    virtual bool Equal(const Type & other) const = 0;
public:
    virtual Handle<Type> Clone() const = 0;
    virtual std::string ToString() const = 0;

    virtual ~SimpleType() = default;
};

class CompositeType : public Type {
    virtual bool Equal(const Type & other) const = 0;
public:
    virtual Handle<Type> Clone() const = 0;
    virtual std::string ToString() const = 0;

    virtual ~CompositeType() = default;
};

class FPType : public SimpleType {
    virtual bool Equal(const Type & other) const;
public:
    virtual Handle<Type> Clone() const;
    virtual std::string ToString() const;

    virtual ~FPType() = default;
};

class BoolType : public SimpleType {
    virtual bool Equal(const Type & other) const;
public:
    virtual Handle<Type> Clone() const;
    virtual std::string ToString() const;

    virtual ~BoolType() = default;
};

class VectorType : public CompositeType {
    Handle<Type> t_;
    size_type n_;

    virtual bool Equal(const Type & other) const;
public:
    VectorType(Handle<Type> && t, size_type n);

    virtual Handle<Type> Clone() const;
    virtual std::string ToString() const;

    virtual ~VectorType() = default;
};

class IncompatibileTypesException : virtual public std::exception {
    std::string msg_;
public:
    IncompatibileTypesException(Handle<Type> && expected, Handle<Type> && actual);
    IncompatibileTypesException(IncompatibileTypesException && e) noexcept;
    IncompatibileTypesException(const IncompatibileTypesException & e);

    virtual const char * what() const noexcept;

    virtual ~IncompatibileTypesException() = default;
};

#endif // _TYPE_HPP

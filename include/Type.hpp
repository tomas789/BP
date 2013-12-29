#ifndef _TYPE_HPP
#define _TYPE_HPP

#include <iostream>
#include <map>
#include <string>
#include <exception>
#include <stdexcept>
#include <memory>
#include <vector>

template <typename T>
using Handle = std::unique_ptr<T>;

using size_type = std::size_t;

class Type;

class TypeHandle {
    Type * t_;
public:
    explicit TypeHandle(std::nullptr_t) = delete;
    explicit TypeHandle(Type * t);
    TypeHandle(const TypeHandle & t);
    TypeHandle(TypeHandle && t);
    TypeHandle(std::unique_ptr<Type> && t);        // Deprecated

    TypeHandle & operator= (const TypeHandle & t);
    TypeHandle & operator= (TypeHandle && t);
    bool operator== (const TypeHandle & other) const;
    bool operator!= (const TypeHandle & other) const;
    operator std::string() const;

    Type * operator-> ();
    const Type * operator-> () const;

    Type & operator* ();
    const Type & operator* () const;

    ~TypeHandle();
};

class Type {
    virtual bool Equal(const Type & other) const = 0;
public:
    bool operator== (const Type & other) const;

    virtual TypeHandle Clone() const = 0;
    virtual std::string ToString() const = 0;

    virtual ~Type() = default;
};

class SimpleType : public Type { 
    virtual bool Equal(const Type & other) const = 0;
public:
    virtual TypeHandle Clone() const = 0;
    virtual std::string ToString() const = 0;

    virtual ~SimpleType() = default;
};

class CompositeType : public Type {
    virtual bool Equal(const Type & other) const = 0;
public:
    virtual TypeHandle Clone() const = 0;
    virtual std::string ToString() const = 0;

    virtual ~CompositeType() = default;
};

class FunctionType : public Type {
    TypeHandle RetVal_;
    std::vector<TypeHandle> Args_;

    virtual bool Equal(const Type & other) const;
public:
    FunctionType(TypeHandle && RetVal, std::vector<TypeHandle> && Args);

    virtual TypeHandle Clone() const;
    virtual std::string ToString() const;

    static TypeHandle get(TypeHandle && RetVal, std::vector<TypeHandle> && Args);
    static TypeHandle get(const TypeHandle & RetVal, const std::vector<TypeHandle> & Args);

    ~FunctionType() = default;
};

class FPType : public SimpleType {
    virtual bool Equal(const Type & other) const;
public:
    virtual TypeHandle Clone() const;
    virtual std::string ToString() const;

    static TypeHandle get();

    virtual ~FPType() = default;
};

class BoolType : public SimpleType {
    virtual bool Equal(const Type & other) const;
public:
    virtual TypeHandle Clone() const;
    virtual std::string ToString() const;

    static TypeHandle get();

    virtual ~BoolType() = default;
};

class VectorType : public CompositeType {
    TypeHandle t_;
    size_type n_;

    virtual bool Equal(const Type & other) const;
public:
    VectorType(TypeHandle && t, size_type n);

    virtual TypeHandle Clone() const;
    virtual std::string ToString() const;

    static TypeHandle get(TypeHandle && t, size_type n);

    virtual ~VectorType() = default;
};

class IncompatibileTypesException : virtual public std::exception {
    std::string msg_;
public:
    IncompatibileTypesException(TypeHandle && expected, TypeHandle && actual);
    IncompatibileTypesException(IncompatibileTypesException && e) noexcept;
    IncompatibileTypesException(const IncompatibileTypesException & e);

    virtual const char * what() const noexcept;

    virtual ~IncompatibileTypesException() = default;
};

#endif // _TYPE_HPP

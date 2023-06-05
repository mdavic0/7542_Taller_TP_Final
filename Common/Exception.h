#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include <exception>
#include <string>

class Exception : public std::exception {
    private:
        std::string msgError;
    public:
        explicit Exception(const char* fmt, ...) noexcept;
        Exception() = delete;
        virtual const char* what() const noexcept;
        virtual ~Exception() noexcept = default; 
};

#endif

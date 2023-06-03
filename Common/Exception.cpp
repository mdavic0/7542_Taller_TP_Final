#include "Exception.h"
#include <cstdarg>
#include <sstream>

Exception::Exception(const char* fmt, ...) noexcept {
    va_list args, argsCopy;
    va_start(args, fmt);
    va_copy(argsCopy, args);
    size_t size = std::vsnprintf(nullptr, 0, fmt, args) + 1;

    this->msgError.reserve(size);
    std::vsnprintf(&this->msgError.front(), size, fmt, argsCopy);

    va_end(argsCopy);
    va_end(args);
}

const char* Exception::what() const noexcept {
    return this->msgError.c_str();
}

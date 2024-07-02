#include "value.h"

#include <algorithm>

#include "utils_p.h"

namespace SysCmdLine {

    static constexpr const char True_Literal[] = "true";
    static constexpr const char False_Literal[] = "false";

    Value::Value(Value::Type type) : _type(type) {
        switch (type) {
            case Bool:
                data.b = false;
                break;
            case Int:
                data.i = 0;
                break;
            case Int64:
                data.l = 0;
                break;
            case Double:
                data.d = 0;
                break;
            case String:
                data.s = new std::string();
                break;
            default:
                break;
        }
    }

    Value::~Value() {
        if (_type == String)
            delete data.s;
    }

    Value::Value(const Value &other) {
        _type = other._type;
        switch (_type) {
            case Bool:
                data.b = other.data.b;
                break;
            case Int:
                data.i = other.data.i;
                break;
            case Int64:
                data.l = other.data.l;
                break;
            case Double:
                data.d = other.data.d;
                break;
            case String:
                data.s = new std::string(*other.data.s);
                break;
            default:
                break;
        }
    }

    Value::Value(Value &&other) noexcept {
        _type = other._type;
        std::swap(data, other.data);
        other._type = Null;
    }

    Value &Value::operator=(const Value &other) {
        if (this == &other) {
            return *this;
        }

        if (_type == String) {
            delete data.s;
        }
        _type = other._type;
        switch (_type) {
            case Bool:
                data.b = other.data.b;
                break;
            case Int:
                data.i = other.data.i;
                break;
            case Int64:
                data.l = other.data.l;
                break;
            case Double:
                data.d = other.data.d;
                break;
            case String:
                data.s = new std::string(*other.data.s);
                break;
            default:
                break;
        }
        return *this;
    }

    Value &Value::operator=(Value &&other) noexcept {
        if (this == &other) {
            return *this;
        }
        std::swap(data, other.data);
        std::swap(_type, other._type);
        return *this;
    }

    bool Value::isEmpty() const {
        switch (_type) {
            case Bool:
                return !data.b;
            case Int:
                return data.i == 0;
            case Int64:
                return data.l == 0;
            case Double:
                return data.d == 0;
            case String:
                return data.s->empty();
            default:
                break;
        }
        return true;
    }

    bool Value::toBool() const {
        return _type == Bool && data.b;
    }

    int Value::toInt() const {
        switch (_type) {
            case Bool:
                return data.b;
            case Int:
                return data.i;
            case Int64:
                return int(data.l);
            case Double:
                return int(data.d);
            default:
                break;
        }
        return 0;
    }

    int64_t Value::toInt64() const {
        switch (_type) {
            case Bool:
                return data.b;
            case Int:
                return data.i;
            case Int64:
                return data.l;
            case Double:
                return int64_t(data.d);
            default:
                break;
        }
        return 0;
    }

    double Value::toDouble() const {
        switch (_type) {
            case Bool:
                return data.b;
            case Int:
                return data.i;
            case Int64:
                return double(data.l);
            case Double:
                return data.d;
            default:
                break;
        }
        return 0;
    }

    std::string Value::toString() const {
        switch (_type) {
            case Bool:
                return data.b ? True_Literal : False_Literal;
            case Int:
                return std::to_string(data.i);
            case Int64:
                return std::to_string(data.l);
            case Double:
                return std::to_string(data.d);
            case String:
                return *data.s;
            default:
                break;
        }
        return {};
    }

    bool Value::operator==(const Value &other) const {
        if (_type != other._type)
            return false;
        switch (_type) {
            case Bool:
                return data.b == other.data.b;
            case Int:
                return data.i == other.data.i;
            case Int64:
                return data.l == other.data.l;
            case Double:
                return data.d == other.data.d;
            case String:
                return *data.s == *other.data.s;
            default:
                break;
        }
        return true;
    }

    bool Value::operator!=(const Value &other) const {
        return !(*this == other);
    }

    static void determineBase(std::string &s, int &base, int &f) {
        if (s.front() == '+') {
            s = s.substr(1);
        } else if (s.front() == '-') {
            f = -1;
            s = s.substr(1);
        }
        if (s.size() > 2 && s.front() == '0') {
            switch (s.at(1)) {
                case 'x':
                case 'X':
                    s = s.substr(2);
                    base = 16;
                    break;
                case 'b':
                case 'B':
                    s = s.substr(2);
                    base = 2;
                    break;
                case 'o':
                case 'O':
                    s = s.substr(2);
                    base = 8;
                    break;
                case 'd':
                case 'D':
                    s = s.substr(2);
                    break;
                default:
                    break;
            }
        }
    }

    Value Value::fromString(const std::string &s, Value::Type type) {
        Value res;
        switch (type) {
            case Bool: {
                if (Utils::toLower(s) == True_Literal) {
                    res = true;
                } else if (Utils::toLower(s) == False_Literal) {
                    res = false;
                }
                break;
            }

            case Int: {
                std::string::size_type idx;
                try {
                    std::string s1 = s;
                    int base = 10;
                    int f = 1;
                    determineBase(s1, base, f);
                    res = std::stoi(s1, &idx, base) * f;
                    if (idx < s1.size()) {
                        res = {};
                    }
                } catch (...) {
                }
                break;
            }

            case Int64: {
                std::string::size_type idx;
                try {
                    std::string s1 = s;
                    int base = 10;
                    int f = 1;
                    determineBase(s1, base, f);
                    res = (int64_t) std::stoll(s1, &idx, base) * f;
                    if (idx < s1.size()) {
                        res = {};
                    }
                } catch (...) {
                }
                break;
            }

            case Double: {
                std::string::size_type idx;
                try {
                    res = std::stod(s, &idx);
                    if (idx < s.size()) {
                        res = {};
                    }
                } catch (...) {
                }
                break;
            }

            case String: {
                if (!s.empty()) {
                    res = s;
                }
                break;
            }
            default:
                break;
        }
        return res;
    }

    std::vector<std::string> Value::toStringList(const std::vector<Value> &values) {
        std::vector<std::string> res(values.size());
        std::transform(values.begin(), values.end(), res.begin(), [](const Value &val) {
            return val.toString(); //
        });
        return res;
    }

    const char *Value::typeName(Value::Type type) {
        const char *expected;
        switch (type) {
            case Value::Bool: {
                expected = "boolean";
                break;
            }
            case Value::Int: {
                expected = "int";
                break;
            }
            case Value::Int64: {
                expected = "long";
                break;
            }
            case Value::Double: {
                expected = "double";
                break;
            }
            case Value::String: {
                expected = "string";
                break;
            }
            default:
                expected = "null";
                break;
        }
        return expected;
    }

}
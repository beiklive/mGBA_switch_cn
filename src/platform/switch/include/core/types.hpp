#pragma once



#include <cmath>
#include <array>
#include <iostream>
#include <type_traits>

namespace beiklive {


// 主模板声明
template<size_t N, typename T = double>
class Vector;

// 2D向量特化
template<typename T>
class Vector<2, T> {
public:
    T x, y;
    
    // 构造函数
    Vector() : x(0), y(0) {}
    Vector(T x, T y) : x(x), y(y) {}
    
    // 拷贝构造函数
    Vector(const Vector<2, T>& other) : x(other.x), y(other.y) {}
    
    // 基本运算
    Vector<2, T> operator+(const Vector<2, T>& other) const {
        return Vector<2, T>(x + other.x, y + other.y);
    }
    
    Vector<2, T> operator-(const Vector<2, T>& other) const {
        return Vector<2, T>(x - other.x, y - other.y);
    }
    
    Vector<2, T> operator*(T scalar) const {
        return Vector<2, T>(x * scalar, y * scalar);
    }
    
    Vector<2, T> operator/(T scalar) const {
        return Vector<2, T>(x / scalar, y / scalar);
    }
    
    // 点积
    T dot(const Vector<2, T>& other) const {
        return x * other.x + y * other.y;
    }
    
    // 模长
    T magnitude() const {
        return std::sqrt(x * x + y * y);
    }
    
    // 归一化
    Vector<2, T> normalize() const {
        T mag = magnitude();
        if (mag != 0) {
            return *this / mag;
        }
        return *this;
    }
    
    // 访问元素
    T& operator[](size_t index) {
        if (index == 0) return x;
        else if (index == 1) return y;
        throw std::out_of_range("Index out of range");
    }
    
    const T& operator[](size_t index) const {
        if (index == 0) return x;
        else if (index == 1) return y;
        throw std::out_of_range("Index out of range");
    }
    
    // 输出
    friend std::ostream& operator<<(std::ostream& os, const Vector<2, T>& vec) {
        os << "Vector2(" << vec.x << ", " << vec.y << ")";
        return os;
    }
};

// 3D向量特化
template<typename T>
class Vector<3, T> {
public:
    T x, y, z;
    
    // 构造函数
    Vector() : x(0), y(0), z(0) {}
    Vector(T x, T y, T z) : x(x), y(y), z(z) {}
    
    // 基本运算
    Vector<3, T> operator+(const Vector<3, T>& other) const {
        return Vector<3, T>(x + other.x, y + other.y, z + other.z);
    }
    
    Vector<3, T> operator-(const Vector<3, T>& other) const {
        return Vector<3, T>(x - other.x, y - other.y, z - other.z);
    }
    
    Vector<3, T> operator*(T scalar) const {
        return Vector<3, T>(x * scalar, y * scalar, z * scalar);
    }
    
    Vector<3, T> operator/(T scalar) const {
        return Vector<3, T>(x / scalar, y / scalar, z / scalar);
    }
    
    // 点积
    T dot(const Vector<3, T>& other) const {
        return x * other.x + y * other.y + z * other.z;
    }
    
    // 叉积
    Vector<3, T> cross(const Vector<3, T>& other) const {
        return Vector<3, T>(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        );
    }
    
    // 模长
    T magnitude() const {
        return std::sqrt(x * x + y * y + z * z);
    }
    
    // 归一化
    Vector<3, T> normalize() const {
        T mag = magnitude();
        if (mag != 0) {
            return *this / mag;
        }
        return *this;
    }
    
    // 访问元素
    T& operator[](size_t index) {
        if (index == 0) return x;
        else if (index == 1) return y;
        else if (index == 2) return z;
        throw std::out_of_range("Index out of range");
    }
    
    const T& operator[](size_t index) const {
        if (index == 0) return x;
        else if (index == 1) return y;
        else if (index == 2) return z;
        throw std::out_of_range("Index out of range");
    }
    
    // 输出
    friend std::ostream& operator<<(std::ostream& os, const Vector<3, T>& vec) {
        os << "Vector3(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
        return os;
    }
};

// 4D向量特化
template<typename T>
class Vector<4, T> {
public:
    T x, y, z, w;
    
    // 构造函数
    Vector() : x(0), y(0), z(0), w(0) {}
    Vector(T x, T y, T z, T w = 1) : x(x), y(y), z(z), w(w) {}
    
    // 从3D向量构造（齐次坐标）
    Vector(const Vector<3, T>& vec3, T w = 1) : x(vec3.x), y(vec3.y), z(vec3.z), w(w) {}
    
    // 基本运算
    Vector<4, T> operator+(const Vector<4, T>& other) const {
        return Vector<4, T>(x + other.x, y + other.y, z + other.z, w + other.w);
    }
    
    Vector<4, T> operator-(const Vector<4, T>& other) const {
        return Vector<4, T>(x - other.x, y - other.y, z - other.z, w - other.w);
    }
    
    Vector<4, T> operator*(T scalar) const {
        return Vector<4, T>(x * scalar, y * scalar, z * scalar, w * scalar);
    }
    
    Vector<4, T> operator/(T scalar) const {
        return Vector<4, T>(x / scalar, y / scalar, z / scalar, w / scalar);
    }
    
    // 点积
    T dot(const Vector<4, T>& other) const {
        return x * other.x + y * other.y + z * other.z + w * other.w;
    }
    
    // 模长
    T magnitude() const {
        return std::sqrt(x * x + y * y + z * z + w * w);
    }
    
    // 归一化
    Vector<4, T> normalize() const {
        T mag = magnitude();
        if (mag != 0) {
            return *this / mag;
        }
        return *this;
    }
    
    // 转换为3D向量（透视除法）
    Vector<3, T> to3D() const {
        if (w != 0) {
            return Vector<3, T>(x / w, y / w, z / w);
        }
        return Vector<3, T>(x, y, z);
    }
    
    // 访问元素
    T& operator[](size_t index) {
        if (index == 0) return x;
        else if (index == 1) return y;
        else if (index == 2) return z;
        else if (index == 3) return w;
        throw std::out_of_range("Index out of range");
    }
    
    const T& operator[](size_t index) const {
        if (index == 0) return x;
        else if (index == 1) return y;
        else if (index == 2) return z;
        else if (index == 3) return w;
        throw std::out_of_range("Index out of range");
    }
    
    // 输出
    friend std::ostream& operator<<(std::ostream& os, const Vector<4, T>& vec) {
        os << "Vector4(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
        return os;
    }
};


// 类型别名
using Vector2 = Vector<2, double>;
using Vector2f = Vector<2, float>;
using Vector2i = Vector<2, int>;

using Vector3 = Vector<3, double>;
using Vector3f = Vector<3, float>;
using Vector3i = Vector<3, int>;

using Vector4 = Vector<4, double>;
using Vector4f = Vector<4, float>;
using Vector4i = Vector<4, int>;



enum class Button : u64 {
    A = static_cast<u64>(HidNpadButton_A),
    B = static_cast<u64>(HidNpadButton_B),
    X = static_cast<u64>(HidNpadButton_X),
    Y = static_cast<u64>(HidNpadButton_Y),
    L = static_cast<u64>(HidNpadButton_L),
    R = static_cast<u64>(HidNpadButton_R),
    L2 = static_cast<u64>(HidNpadButton_ZL),
    R2 = static_cast<u64>(HidNpadButton_ZR),
    L3 = static_cast<u64>(HidNpadButton_StickL),
    R3 = static_cast<u64>(HidNpadButton_StickR),
    START = static_cast<u64>(HidNpadButton_Plus),
    SELECT = static_cast<u64>(HidNpadButton_Minus),

    SL_LEFT = static_cast<u64>(HidNpadButton_LeftSL),
    SR_LEFT = static_cast<u64>(HidNpadButton_LeftSR),
    SL_RIGHT = static_cast<u64>(HidNpadButton_RightSL),
    SR_RIGHT = static_cast<u64>(HidNpadButton_RightSR),
    SL_ANY = SL_LEFT | SL_RIGHT,
    SR_ANY = SR_LEFT | SR_RIGHT,

    // todo:
    DPAD_LEFT = static_cast<u64>(HidNpadButton_Left),
    DPAD_RIGHT = static_cast<u64>(HidNpadButton_Right),
    DPAD_UP = static_cast<u64>(HidNpadButton_Up),
    DPAD_DOWN = static_cast<u64>(HidNpadButton_Down),

    LS_LEFT = static_cast<u64>(HidNpadButton_StickLLeft),
    LS_RIGHT = static_cast<u64>(HidNpadButton_StickLRight),
    LS_UP = static_cast<u64>(HidNpadButton_StickLUp),
    LS_DOWN = static_cast<u64>(HidNpadButton_StickLDown),
    LS_ANY = LS_LEFT | LS_RIGHT | LS_UP | LS_DOWN,

    RS_LEFT = static_cast<u64>(HidNpadButton_StickRLeft),
    RS_RIGHT = static_cast<u64>(HidNpadButton_StickRRight),
    RS_UP = static_cast<u64>(HidNpadButton_StickRUp),
    RS_DOWN = static_cast<u64>(HidNpadButton_StickRDown),
    RS_ANY = RS_LEFT | RS_RIGHT | RS_UP | RS_DOWN,

    ANY_LEFT = static_cast<u64>(HidNpadButton_AnyLeft),
    ANY_RIGHT = static_cast<u64>(HidNpadButton_AnyRight),
    ANY_UP = static_cast<u64>(HidNpadButton_AnyUp),
    ANY_DOWN = static_cast<u64>(HidNpadButton_AnyDown),

    // todo: remove these old buttons
    LEFT = static_cast<u64>(HidNpadButton_AnyLeft),
    RIGHT = static_cast<u64>(HidNpadButton_AnyRight),
    UP = static_cast<u64>(HidNpadButton_AnyUp),
    DOWN = static_cast<u64>(HidNpadButton_AnyDown),

    NONE = 0,
    ANY_BUTTON = A | B | X | Y | L | R | L2 | R2 | L3 | R3 | START | SELECT,
    ANY_HORIZONTAL = LEFT | RIGHT,
    ANY_VERTICAL = UP | DOWN,
    ANY_DIRECTION = ANY_HORIZONTAL | ANY_VERTICAL,
    ANY = ANY_BUTTON | ANY_DIRECTION
};

inline Button operator|(Button a, Button b) {
    return static_cast<Button>(static_cast<u64>(a) | static_cast<u64>(b));
}


}
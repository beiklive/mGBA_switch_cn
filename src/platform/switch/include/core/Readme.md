types.hpp 使用
```C++
    Vector2 v2a(1.0, 2.0);
    Vector2 v2b(3.0, 4.0);
    
    Vector3 v3a(1.0, 2.0, 3.0);
    Vector3 v3b(4.0, 5.0, 6.0);
    
    Vector4 v4a(1.0, 2.0, 3.0, 1.0);
    
    std::cout << "2D Vector Example:" << std::endl;
    std::cout << "v2a: " << v2a << std::endl;
    std::cout << "v2b: " << v2b << std::endl;
    std::cout << "v2a + v2b: " << v2a + v2b << std::endl;
    std::cout << "v2a dot v2b: " << v2a.dot(v2b) << std::endl;
    std::cout << "v2a magnitude: " << v2a.magnitude() << std::endl;
    std::cout << "v2a normalized: " << v2a.normalize() << std::endl;
    
    std::cout << "\n3D Vector Example:" << std::endl;
    std::cout << "v3a: " << v3a << std::endl;
    std::cout << "v3b: " << v3b << std::endl;
    std::cout << "v3a cross v3b: " << v3a.cross(v3b) << std::endl;
    
    std::cout << "\n4D Vector Example:" << std::endl;
    std::cout << "v4a: " << v4a << std::endl;
    std::cout << "v4a to 3D: " << v4a.to3D() << std::endl;
```
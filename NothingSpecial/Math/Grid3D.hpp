//
//  Grid3D.hpp
//  NothingSpecial
//
//  Created by Pascal Spörri on 03/01/16.
//  Copyright © 2016 Pascal Spörri. All rights reserved.
//

#ifndef Grid3D_hpp
#define Grid3D_hpp

#include <cstring>
#include <memory>

namespace Math {
    template<typename T>
    class Grid3D
    {
    public:
        Grid3D(size_t x, size_t y, size_t z);
        Grid3D(const Grid3D& other);
        Grid3D(Grid3D&& other);
        Grid3D& operator=(const Grid3D& other);
        Grid3D& operator=(Grid3D&& other);
        
        // Typecasting constructor
        template<typename From>
        Grid3D(const Grid3D<From>* other):Grid3D(other->dimX(), other->dimY(), other->dimZ())
        {
            for (size_t i=0; i<count(); ++i)
            {
                operator[](i) = (T) (*other)[i];
            }
        }
        
        const T& operator()(size_t i, size_t j, size_t k) const
        {
            return operator[](i + m_x * j + m_xy * k);
        }
        
        T& operator()(size_t i, size_t j, size_t k)
        {
            return operator[](i + m_x * j + m_xy * k);
        }
        
        const T& operator[](size_t i) const
        {
            return *(m_data.get()+i);
        }
        
        T& operator[](size_t i)
        {
            return *(m_data.get()+i);
        }
        
        const T* raw() const
        {
            return m_data.get();
        }
        
        T* raw()
        {
            return m_data.get();
        }
        
        size_t count() const
        {
            return dimX() * dimY() * dimZ();
        }
        
        size_t dimX() const
        {
            return m_x;
        }
        
        size_t dimY() const
        {
            return m_y;
        }
        
        size_t dimZ() const
        {
            return m_z;
        }
        
        void resize(size_t x, size_t y, size_t z)
        {
            resize(x, y, z, true);
        }
        
    private:
        void resize(size_t x, size_t y, size_t z, bool copy);
        
        size_t m_x;
        size_t m_y;
        size_t m_z;
        size_t m_xy;
        
        size_t m_allocatedSize;
        std::unique_ptr<T[]> m_data;
    };
    
    template<typename T>
    Grid3D<T>::Grid3D(size_t x, size_t y, size_t z):
        m_x(x), m_y(y), m_z(z), m_xy(x*y),
        m_allocatedSize(count()),
        m_data(new T[m_x*m_y*m_z])
    {
    }
    
    template<typename T>
    Grid3D<T>::Grid3D(const Grid3D<T>& other):
        m_x(other.m_x), m_y(other.m_y), m_z(other.m_z), m_xy(other.m_xy),
        m_allocatedSize(count()),
        m_data(new T[m_x*m_y*m_z])
    {
        std::memcpy(m_data.get(), other.m_data.get(), count()*sizeof(T));
    }

    template<typename T>
    Grid3D<T>::Grid3D(Grid3D&& other):
        m_x(std::move(other.m_x)),
        m_y(std::move(other.m_y)),
        m_z(std::move(other.m_z)),
        m_xy(std::move(other.m_xy)),
        m_allocatedSize(std::move(other.m_allocatedSize)),
        m_data(std::move(other.m_data))
    {
        
    }
    
    template<typename T> Grid3D<T>&
    Grid3D<T>::operator=(const Grid3D<T>& other)
    {
        if (this != other)
        {
            resize(other.m_x, other.m_y, other.m_z, false);
            std::memcpy(m_data.get(), other.m_data.get(), count()*sizeof(T));
        }
        return *this;
    }
    
    template<typename T> Grid3D<T>&
    Grid3D<T>::operator=(Grid3D<T>&& other)
    {
        if (this != other)
        {
            m_x = std::move(other.m_x);
            m_y = std::move(other.m_y);
            m_z = std::move(other.m_z);
            m_xy = std::move(other.m_xy);
            m_allocatedSize = std::move(other.m_allocatedSize);
            m_data = std::move(other.m_data);
        }
        return *this;
    }
    
    template<typename T> void
    Grid3D<T>::resize(size_t x, size_t y, size_t z, bool copy)
    {
        size_t newCount = x*y*z;
        size_t oldCount = count();
        
        m_x = x;
        m_y = y;
        m_z = z;
        m_xy = x*y;
        
        if (newCount > m_allocatedSize)
        {
            auto newData = std::make_unique<T[]>(new T[newCount]);
            if (copy)
            {
                std::memcpy(newData.get(),
                            m_data.get(),
                            std::min(newCount, oldCount)*sizeof(T));
            }
            m_data = std::move(newData);
            m_allocatedSize = newCount;
        }
    }
}

#endif /* Grid3D_hpp */

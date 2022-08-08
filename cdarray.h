#ifndef _CDARRAY_H_
#define _CDARRAY_H_

template< class T >
class CDArray
{
    T *m_pData;
    int m_Number;
    int m_Size;

public:
    CDArray() : m_Number(0), m_Size (1) {
    }

    CDArray( int size ) : m_Number( 0 ), m_Size ( size ) {
    }

    virtual ~CDArray() {
    }

    int Add( const T &t ) {
        *( m_pData + m_Number ) = t;
        m_Number++;
        if( m_Number == m_Size ) {
            m_pData = (T*) realloc( m_pData, sizeof( T ) * m_Size * 2 );
            m_Size *= 2;
        }
        return m_Number;
    }

    int Delete( int number ) {
    }

    int Modify( int n, const T &t ) {
        *( m_pData + n ) = t;
        return 0;
    }

    int Resize( int size ){
    }

    void Clear() { 
        m_Number = 0; 
    }

    T &operator[]( int i ) const {
    }

    int Number() { 
        return m_Number; 
    }

    int Size() { 
        return m_Size; 
    }

    T *Ptr() { 
        return m_pData;
    };

};

#endif
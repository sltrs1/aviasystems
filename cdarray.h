#ifndef _CDARRAY_H_
#define _CDARRAY_H_

#include <cstring>

template< class T >
class CDArray
{
    T *m_pData;
    int m_Number;
    int m_Size;

public:
    CDArray() : m_Number(0), m_Size (1) {
        m_pData = new T[1];
    };

    CDArray( int size ) : m_Number(0) {

        // Поскольку тут int, а не size_t, то надо проверять на отрицательное значение
        // и как-то отдельно обрабатывать этот случай,
        // либо бросать исключение. Но исключения в конструкторе - очень спорное решение,
        // так что лучше так не делать.
        if (size <= 0) {
            m_Size = 1;
        }
        else {
            m_Size = size;
        }
        m_pData = new T[m_Size];
    };

    virtual ~CDArray() {
        free(m_pData);
    };

    int Add( const T &t ) {
        
        *( m_pData + m_Number ) = t;
        m_Number++;
        if( m_Number == m_Size ) {
            m_pData = (T*)realloc(m_pData, sizeof(T)*m_Size*2);
            m_Size *= 2;
        }
        
        return m_Number;
    };

    int Delete(int number) {

        if (number < 0) {
            return 1;
        }

        // Невозможно удалить элемент с индексом больше максимального
        if (number > m_Number - 1) {
            return 1;
        }

        // Если требуется удалить последний элемент, то просто сдвигаем счетчик
        if (number == m_Number - 1) {
            m_Number--;
            return 0;
        }

        memmove(m_pData+number, m_pData+number+1, sizeof(T)*( m_Number - 1 - number ) );
        m_Number--;

        return 0;
    };

    int Modify( int n, const T &t ) {

        if (n < 0) {
            return 1;
        }

        // Если попытка изменить элемент с индексом больше максимального
        // то вренуть ошибку
        if (n > m_Number - 1) {
            return 1;
        }

        *( m_pData + n ) = t;
        return 0;
    };

    int Resize( int size ) {
        
        // Если попытаться уменьшить размер зарезервированного места, 
        // то уменьшение должно произойти до количества имеющихся элементов
        if (size < m_Number) {
            m_Size = m_Number + 1;
        }
        else {
            m_Size = size;
        }

        return 0;
    };

    void Clear() { 
        m_Number = 0; 
    };

    T &operator[]( int i ) const {

        // Если попытаться обратиться к несуществующему индексу,
        // то приходится бросать исключение,
        // потому что сигнатура метода требует возврата объекта,
        // а не кода ошибки, так что вернуть в этом случае нечего.
        if (i > m_Number - 1) {
            throw "Index too big";
        }
        else {
            return *(m_pData + i);
        }

    };

    int Number() const { 
        return m_Number;
    };

    int Size() const { 
        return m_Size; 
    };

    T *Ptr() const { 
        return m_pData;
    };

};

#endif
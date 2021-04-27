#ifndef MATRIX_H
#define MATRIX_H

//TODO: Vektoreinbindung | Inverse Matrix

#include <cassert>
#include <QDebug>
#include <QList>

namespace msp
{

enum Table
{
    Column = 0,
    Row
};

//Struct to assure that only predefined types can be used as valid template arguments
template <typename T> struct validType
{
    static const bool isValid = false;
};
template <> struct validType<int>
{
    static const bool isValid = true;
};
template <> struct validType<float>
{
    static const bool isValid = true;
};
template <> struct validType<double>
{
    static const bool isValid = true;
};

template<typename T>
class MatrixRow
{
public:
    /*! Constructs a list with a certain length filled with zeros.
     * \brief MatrixRow
     * \param entries
     */
    MatrixRow(int entries)
    {
        assert(validType<T>::isValid);
        int i = 0;
        while(i < entries)
        {
            m_entries.append((T)0);
            i++;
        }
    }

    //OPERATORS
    const T& operator[](int j) const {return m_entries[j];}
    T& operator[](int j) {return m_entries[j];}

private:
    QList<T> m_entries;
};

/*!
 * \class A simple matrix class based on linked lists with basic matrix operations
 */
template<typename T>
class Matrix
{
public:
    /*! Creates a matrix with the user-defined amount of rows and columns
     * \brief Matrix
     * \param rows Amount of rows
     * \param cols Amount of columns
     */
    Matrix(int rows, int cols) :
        m_cols(cols),
        m_rows(rows)
    {
        assert(validType<T>::isValid);
        int i = 0;
        while(i < rows)
        {
            m_firstCol.append(cols);
            i++;
        }
    }
    /*! Creates a matrix based on a user-defined linked list. In contrast to the simple constructor,
     *  this one also applies the values in the list to the corresponding index. Length of the lists
     *  within the main list define the amount of rows while the amount of lists within the main list
     *  define the amount of columns.
     * \brief Matrix
     * \param multiList Linked list
     */
    Matrix(QList<QList<T>> multiList) :
        m_cols(multiList.size()),
        m_rows(multiList[0].size())
    {
        assert(validType<T>::isValid);
        int i = 0;
        while(i < multiList[0].size())
        {
            m_firstCol.append(multiList.size());
            i++;
        }
        for(int i = 0; i < m_rows; i++)
        {
            for(int j = 0; j < m_cols; j++)
            {
                m_firstCol[i][j] = multiList[j][i];
            }
        }
    }
    int columns() const {return m_cols;}
    int rows() const {return m_rows;}
    /*! Returns the transponed matrix based on the rows and columns of the current matrix.
     * \brief transponed
     * \return Transponed Matrix
     */
    Matrix<T> transponed()
    {
        Matrix<T> m(m_cols, m_rows);
        for(int i = 0; i < m_rows; i++)
        {
            for(int j = 0; j < m_cols; j++)
            {
                m[j][i] = m_firstCol[i][j];
            }
        }
        return m;
    }
    /*! Returns the  value of the element in the bottom left of the matrix.
     * \brief bottomLeft
     * \return Value
     */
    T bottomLeft() const
    {
        return m_firstCol[m_rows - 1][0];
    }
    /*! Returns the value of the element in the bottom right of the matrix.
     * \brief bottomRight
     * \return Value
     */
    T bottomRight() const
    {
        return m_firstCol[m_rows - 1][m_cols - 1];
    }
    /*! Returns the value of the element in the top left of the matrix.
     * \brief topLeft
     * \return Value
     */
    T topLeft() const
    {
        return m_firstCol[0][0];
    }
    /*! Returns the value of the element in the top right of the matrix.
     * \brief topRight
     * \return Value
     */
    T topRight() const
    {
        return m_firstCol[0][m_cols - 1];
    }
    /*! Swaps the column or row of the first given index with the corresponding other of the second given index. Note that the index starts at 0.
     * \brief swap
     * \param first Index to be swapped
     * \param second Index to be swapped with
     * \param type If rows or columns should be swapped
     */
    void swap(int first, int second, Table type = Row)
    {
        (type == Row) ? swapRow(first, second) : swapCol(first, second);
    }
    /*! Transforms the current matrix into its transponed matrix.
     * \brief transpone
     */
    void transpone()
    {
        Matrix<T> m(transponed());
        *this = m;
    }

    //OPERATORS
    Matrix<T> operator+(const Matrix<T>& other)
    {
        Matrix<T> m(m_rows, m_cols);
        if(!(m_rows == other.rows() && m_cols == other.columns())) return m;
        for(int i = 0; i < m_rows; i++)
        {
            for(int j = 0; j < m_cols; j++)
            {
                m[i][j] = m_firstCol[i][j] + other[i][j];
            }
        }
        return m;
    }
    Matrix<T> operator-(const Matrix<T>& other)
    {
        Matrix<T> m(m_rows, m_cols);
        if(!(m_rows == other.rows() && m_cols == other.columns())) return m;
        for(int i = 0; i < m_rows; i++)
        {
            for(int j = 0; j < m_cols; j++)
            {
                m[i][j] = m_firstCol[i][j] - other[i][j];
            }
        }
        return m;
    }
    Matrix<T> operator*(const Matrix<T>& other)
    {
        Matrix<T> m(m_rows, m_rows);
        if(!m_cols == other.rows()) return m;
        T sum = (T)(0);
        for(int i = 0; i < m_rows; i++)
        {
            for(int j = 0; j < m_rows; j++)
            {
                for(int k = 0; k < m_cols; k++)
                {
                    sum += m_firstCol[i][k] * other[k][j];
                }
                m[i][j] = sum;
                sum = (T)(0);
            }
        }
        return m;
    }
    Matrix<T> operator*(T s) const
    {
        assert(validType<T>::isValid);
        Matrix<T> m(m_rows, m_cols);
        for(int i = 0; i < m_rows; i++)
        {
            for(int j = 0; j < m_cols; j++)
            {
                m[i][j] = s * m_firstCol[i][j];
            }
        }
        return m;
    }
    Matrix<T>& operator*=(T s)
    {
        assert(validType<T>::isValid);
        for(int i = 0; i < m_rows; i++)
        {
            for(int j = 0; j < m_cols; j++)
            {
                m_firstCol[i][j] *= s;
            }
        }
        return *this;
    }
    Matrix<T> operator^(int n) const
    {
        Matrix<T> m(*this);
        Matrix<T> temp(*this);
        for(int i = 0; i < n - 1; i++)
        {
            m = m * temp;
        }
        return m;
    }
    const MatrixRow<T>& operator[](int i) const {return m_firstCol[i];}
    MatrixRow<T>& operator[](int i) {return m_firstCol[i];}
    const MatrixRow<T>& operator()(int row, int col) const {return m_firstCol[row][col];}
    friend Matrix<T> operator*(T s, const Matrix<T>& m)
    {
        return m * s;
    }

    inline double getDet() const
       {
           return m_det;
       }

       inline void setDet(double det)
       {
           this->m_det = det;
       }


   private:
       int m_cols;
       int m_rows;
       double m_det = 0;

    QList<MatrixRow<T>> m_firstCol;
    /*! Swappes two columns with each other. For further information see swap().
     * \brief swapCol
     * \param first Index to be swapped
     * \param second Index to be swapped with
     */
    void swapCol(int first, int second)
    {
        if(first >= m_cols || second >= m_cols || first < 0 || second < 0) return;
        Matrix<T> m = *this;
        int list[2] = {first, second};
        for(int i = 0; i < 2; i++)
        {
            int other;
            (i == 0) ? other = second : other = first;
            for(int j = 0; j < m_rows; j++)
            {
                m_firstCol[j][list[i]] = m[j][other];
            }
        }
    }
    /*! Swappes two rows with each other. For further information see swap().
     * \brief swapRow
     * \param first Index to be swapped
     * \param second Index to be swapped with
     */
    void swapRow(int first, int second)
    {
        if(first >= m_rows || second >= m_rows || first < 0 || second < 0) return;
        Matrix<T> m = *this;
        int list[2] = {first, second};
        for(int i = 0; i < 2; i++)
        {
            int other;
            (i == 0) ? other = second : other = first;
            for(int j = 0; j < m_rows; j++)
            {
                m_firstCol[list[i]][j] = m[other][j];
            }
        }
    }
};

template<typename T> QDebug& operator<<(QDebug dbg, const Matrix<T>& m)
{
    QString str = "***********************************\n";
    for(int i = 0; i < m.rows(); i++)
    {
        str += "[{";
        for(int j = 0; j < m.columns(); j++)
        {
            str += QString::number(m[i][j]);
            (j < m.columns() - 1) ? str += ", " : str += "";
        }
        (i < m.rows() - 1) ? str += "}]\n" : str += "}]";
    }
    return dbg.noquote() << str;
}

template<typename T> extern double det(const Matrix<T>& m, int n)
{
    int r = m.rows();
    int c = m.columns();
    double deter = 0;
    if(r == c)
    {
        auto hlpmat = Matrix<double>(10,10);
        if(n == 2)
        {
            return ((m[0][0] * m[1][1]) - (m[1][0] * m[0][1]));
        }
        else
        {
            for(int a = 0; a < n; a++)
            {

              int hlpi = 0;

              for(int i = 1; i < n; i++)
              {

                  int hlpj = 0;

                  for(int j = 0; j < n; j++)
                  {

                      if(j == a)
                      {
                          continue;
                      }

                      hlpmat[hlpi][hlpj] = m[i][j];
                      hlpj++;
                  }
                hlpi++;
              }
            deter = deter + (pow(-1,a) * m[0][a] * det(hlpmat,n-1));
            }
        }
        return deter;
    }
}

template<typename T> extern double rank(Matrix<T>& m)
{
    int rank = m.rows();
    for(int row = 0; row < rank; row++)
    {
        if(m[row][row])
        {
            for(int col = 0; col < m.rows(); col++)
            {
                auto mult = m[col][row]/m[row][row];
                for(int i = 0; i < rank; i++)
                {
                    m[col][i] -= mult * m[row][i];
                }
            }

        }
        else
        {
            bool reduce = true;
            for(int i = row; i < m.rows(); i++)
            {
               if(m[i][row])
               {
                m.swap(row,i);
                reduce = false;
                break;
               }
               if(reduce)
               {
                 rank--;
                 for(int i = 0; i <m.rows(); i++)
                 {
                    m[i][row] = m[i][rank];
                 }
               }
               row--;
          }
        }

    }
  return rank;
}



}
 //namespace

#endif // MATRIX_H

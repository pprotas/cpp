// mandelbrot.cpp
// compile with: g++ -std=c++11 mandelbrot.cpp -o mandelbrot
// view output with: eog mandelbrot.ppm

#include <fstream>
#include <iostream>
#include <complex> // if you make use of complex number facilities in C++

template <class T>
struct RGB
{
    T r, g, b;
};

template <class T>
class Matrix
{
  public:
    Matrix(const size_t rows, const size_t cols) : _rows(rows), _cols(cols)
    {
        _matrix = new T *[rows];
        for (size_t i = 0; i < rows; ++i)
        {
            _matrix[i] = new T[cols];
        }
    }
    Matrix(const Matrix &m) : _rows(m._rows), _cols(m._cols)
    {
        _matrix = new T *[m._rows];
        for (size_t i = 0; i < m._rows; ++i)
        {
            _matrix[i] = new T[m._cols];
            for (size_t j = 0; j < m._cols; ++j)
            {
                _matrix[i][j] = m._matrix[i][j];
            }
        }
    }
    ~Matrix()
    {
        for (size_t i = 0; i < _rows; ++i)
        {
            delete[] _matrix[i];
        }
        delete[] _matrix;
    }
    T *operator[](const size_t nIndex)
    {
        return _matrix[nIndex];
    }
    size_t width() const { return _cols; }
    size_t height() const { return _rows; }

  protected:
    size_t _rows, _cols;
    T **_matrix;
};

// Portable PixMap image
class PPMImage : public Matrix<RGB<unsigned char>>
{
  public:
    PPMImage(const size_t height, const size_t width) : Matrix(height, width) {}
    void save(const std::string &filename)
    {
        std::ofstream out(filename, std::ios_base::binary);
        out << "P6" << std::endl
            << _cols << " " << _rows << std::endl
            << 255 << std::endl;
        for (size_t y = 0; y < _rows; y++)
            for (size_t x = 0; x < _cols; x++)
                out << _matrix[y][x].r << _matrix[y][x].g << _matrix[y][x].b;
    }
};

const void calculateImage(PPMImage &image, const unsigned &width, const unsigned &height)
{
    double MinRe = -2.0;
    double MaxRe = 1.0;
    double MinIm = -1.2;
    double MaxIm = MinIm + (MaxRe - MinRe) * height / width;
    double Re_facor = (MaxRe - MinRe) / (width - 1);
    double Im_factor = (MaxIm - MinIm) / (height - 1);
    unsigned MaxIterations = 30;

    std::cout << "Calculating...\n";
    for (unsigned y = 0; y < height; ++y)
    {
        double c_im = MaxIm - y * Im_factor;
        for (unsigned x = 0; x < width; ++x)
        {
            double c_re = MinRe + x*Re_facor;

            double Z_re = c_re, Z_im = c_im;
            bool isInside = true;
            for(unsigned n = 0; n < MaxIterations;++n){
                double Z_re2 = Z_re*Z_re, Z_im2 = Z_im*Z_im;
                if(Z_re2 + Z_im2 > 4){
                    isInside = false;
                    break;
                }
                Z_im = 2 * Z_re *Z_im + c_im;
                Z_re = Z_re2-Z_im2 + c_re;
            }
            if(isInside){
                image[y][x].r = 255;
                image[y][x].g = 0;
                image[y][x].b = 0;
            }
        }
    }
    std::cout << "Done.\n";
}

int main()
{
    const unsigned width = 100000;
    const unsigned height = 100000;

    PPMImage image(height, width);

    calculateImage(image, width, height);

    image.save("mandelbrot.ppm");
    return 0;
}

// mandelbrot.cpp
// compile with: g++ -std=c++11 mandelbrot.cpp -o mandelbrot
// view output with: eog mandelbrot.ppm

#include <fstream>
#include <iostream>
#include <complex> // if you make use of complex number facilities in C++
#include <thread>
#include <vector>

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

const void calculateImage(PPMImage &image, unsigned &width, unsigned &height, unsigned minX, unsigned maxX, unsigned minY, unsigned maxY)
{
    double MinRe = -2.0;
    double MaxRe = 1.0;
    double MinIm = -1.2;
    double MaxIm = MinIm + (MaxRe - MinRe) * width / height;
    double Re_facor = (MaxRe - MinRe) / (width - 1);
    double Im_factor = (MaxIm - MinIm) / (height - 1);
    unsigned MaxIterations = 30;

    for (unsigned y = minY; y < maxY; ++y)
    {
        double c_im = MaxIm - y * Im_factor;
        for (unsigned x = minX; x < maxX; ++x)
        {
            double c_re = MinRe + x * Re_facor;

            double Z_re = c_re, Z_im = c_im;
            bool isInside = true;
            for (unsigned n = 0; n < MaxIterations; ++n)
            {
                double Z_re2 = Z_re * Z_re, Z_im2 = Z_im * Z_im;
                if (Z_re2 + Z_im2 > 4)
                {
                    isInside = false;
                    break;
                }
                Z_im = 2 * Z_re * Z_im + c_im;
                Z_re = Z_re2 - Z_im2 + c_re;
            }
            if (isInside)
            {
                image[y][x].r = 255;
                image[y][x].g = 0;
                image[y][x].b = 0;
            }
        }
    }
}

int main()
{
    unsigned width = 1600;
    unsigned height = 1600;
    unsigned minX = 0;
    unsigned minY = 0;
    unsigned maxX = width / 2;
    unsigned maxY = height / 2;

    std::cout << "Creating image...\n";
    PPMImage image(height, width);

    std::vector<std::thread> workers;
    for (int i = 0; i < 4; i++)
    {
        workers.push_back(std::thread(calculateImage, std::ref(image), std::ref(width), std::ref(height), minX, maxX, minY, maxY));
        std::cout << "Thread #" << i << " created. Calculating (" << minX << "," << minY << ") to (" << maxX << "," << maxY << ").\n";

        if (i == 0)
        {
            minY = height / 2;
            maxY = height;
        }
        else if (i == 1)
        {
            minX = width / 2;
            maxX = width;
            minY = 0;
            maxY = height / 2;
        }
        else if (i == 2)
        {
            minX = width / 2;
            maxX = width;
            minY = height / 2;
            maxY = height;
        }
    }

    for (auto &th : workers)
    {
        th.join();
    }

    std::cout << "Saving to image...\n";
    image.save("mandelbrot.ppm");

    std::cout << "Finished.\n";
    return 0;
}

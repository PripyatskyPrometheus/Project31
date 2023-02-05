#include<iostream>
#include <math.h>
#include <string>
#include <typeinfo>
#include <limits>
#include <vector>

using namespace std;

template <class T>
class Image {
private:
    vector<vector<T>>matrix;
    int _maxX, _maxY;

public:

    Image(int x, int y);

    Image(const Image& img) = default;

    ~Image() = default;

    Image<T> operator+(const Image<T>& img);

    Image<T> operator*(const Image<T>& img);

    Image<T> operator+(T value);

    Image<T> operator*(T value);

    friend Image operator*(T value, Image<T>& img) {
        return (img * value);
    }

    friend Image operator+(T value, Image<T>& img) {
        return (img + value);
    }

    Image<T> operator!();

    void set(int x, int y, T value);

    T get(int x, int y);

    double fill_ratio();

    friend Image<T> cret_circle(Image<T>& img, int x, int y, int r, T value) {
        Image<T> tmp(img._maxX, img._maxY);
        for (int i = 0; i < img.matrix.size(); i++) {
            for (int j = 0; j < img.matrix[i].size(); j++) {
                if ((i - x) * (i - x) + (j - y) * (j - y) <= r * r)
                    tmp.matrix[i][j] = value;
            }
        }
        return tmp;
    }

    Image<T>& operator=(const Image<T>& img) = default;

    void change();

    T operator()(int x, int y) const;

    T& operator()(int x, int y);

    auto begin() {
        return matrix.begin();
    }

    auto end() {
        return matrix.end();
    }
};

template<class T>
Image<T>::Image(int x, int y) {
    _maxX = x;
    _maxY = y;

    matrix.resize(_maxX);
    for (auto& i : matrix)
    {
        i.resize(_maxY);
        for (auto& j : i)
        {
            j = 0;
        }
    }
}

template<>
Image<bool>::Image(int x, int y) {
    _maxX = x;
    _maxY = y;

    matrix.resize(_maxX);

    for (int i = 0; i < matrix.size(); i++)
    {
        matrix[i].resize(_maxY);
        for (int j = 0; j < matrix[i].size(); j++)
        {
            matrix[i][j] = false;
        }
    }
}

template<>
Image<char>::Image(int x, int y) {
    _maxX = x;
    _maxY = y;

    matrix.resize(_maxX);
    for (auto& i : matrix) {
        i.resize(_maxY);
        for (auto& j : i) {
            j = '0';
        }
    }
}

template<class T>
void Image<T>::set(int x, int y, T value) {
    matrix[x][y] = value;
}

template<class T>
T Image<T>::get(int x, int y) {
    return matrix[x][y];
}

template<class T>
ostream& operator<<(ostream& out, Image<T>& img) {
    for (auto i : img) {
        for (auto j : i) {
            out << j << " ";
        }
        out << endl;
    }
    return out;
}

template<class T>
Image<T> Image<T>::operator+(const Image<T>& img) {
    Image<T> result(_maxX, _maxY);

    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {

            if (matrix[i][j] + img.matrix[i][j] > numeric_limits<T>::max() || matrix[i][j] + img.matrix[i][j] < numeric_limits<T>::min())
                resultmatrix[i][j] = 0;
            else
                result.matrix[i][j] = matrix[i][j] + img.matrix[i][j];
        }
    }
    return result;
}

template<class T>
Image<T>  Image<T>::operator*(const Image<T>& img) {
    Image<T> result(_maxX, _maxY);

    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            if (matrix[i][j] * img.matrix[i][j] > numeric_limits<T>::max() || matrix[i][j] * img.matrix[i][j] < numeric_limits<T>::min())
                result.matrix[i][j] = 0;
            else
                result.matrix[i][j] = matrix[i][j] * img.matrix[i][j];
        }
    }

    return result;
}

template<class T>
Image<T> Image<T>::operator+(T value) {
    Image<T> result(_maxX, _maxY);

    for (int i = 0; i < _maxX; i++) {

        for (int j = 0; j < _maxY; j++) {
            if (matrix[i][j] + value > numeric_limits<T>::max() || matrix[i][j] + value < numeric_limits<T>::min())
                result.matrix[i][j] = 0;
            else
                result.matrix[i][j] = matrix[i][j] + value;
        }
    }
    return result;
}

template<class T>
Image<T> Image<T>::operator*(T value) {
    Image<T> result(_maxX, _maxY);

    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            if (matrix[i][j] * value > numeric_limits<T>::max() || matrix[i][j] * value < numeric_limits<T>::min())
                result.matrix[i][j] = 0;
            else
                result.matrix[i][j] = matrix[i][j] * value;
        }
    }
    return result;
}

template<>
Image<char> Image<char>::operator+(const Image<char>& img) {
    Image<char> result(_maxX, _maxY);

    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {

            if (matrix[i][j] + img.matrix[i][j] > numeric_limits<char>::max() || matrix[i][j] + img.matrix[i][j] < numeric_limits<char>::min())
                result.matrix[i][j] = '0';
            else
                result.matrix[i][j] = matrix[i][j] + img.matrix[i][j];
        }
    }
    return result;
}

template<>
Image<char> Image<char>::operator*(const Image<char>& img) {
    Image<char> result(_maxX, _maxY);

    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            if (matrix[i][j] * img.matrix[i][j] > numeric_limits<char>::max() || matrix[i][j] * img.matrix[i][j] < numeric_limits<char>::min())
                result.matrix[i][j] = '0';
            else
                result.matrix[i][j] = matrix[i][j] * img.matrix[i][j];
        }
    }

    return result;
}

template<>
Image<char> Image<char>::operator+(char value) {
    Image<char> result(_maxX, _maxY);

    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            if (matrix[i][j] + value > numeric_limits<char>::max() || matrix[i][j] + value < numeric_limits<char>::min())
                result.matrix[i][j] = '0';
            else
                result.matrix[i][j] = matrix[i][j] + value;
        }
    }
    return result;
}

template<>
Image<char> Image<char>::operator*(char value) {
    Image<char> result(_maxX, _maxY);
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            if (matrix[i][j] * value > numeric_limits<char>::max() || matrix[i][j] * value < numeric_limits<char>::min())
                result.matrix[i][j] = '0';
            else {
                result.matrix[i][j] = matrix[i][j] * value;
            }
        }
    }
    return result;
}

template<class T>
Image<T> Image<T>::operator!() {
    for (auto& i : matrix) {
        for (auto& j : i) {
            if (j == 0) {
                j = numeric_limits<T>::max();
            }
            else {
                j = 0;
            }
        }
    }
    return *this;
}

template<>
Image<char> Image<char>::operator!() {

    for (auto& i : matrix) {
        for (auto& j : i) {
            if (j == '0')
                j = numeric_limits<char>::max();
            else
                j = '0';
        }
    }
    return *this;
}

template<>
Image<bool> Image<bool>::operator!() {

    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            if (matrix[i][j] == false)
                matrix[i][j] = true;
            else
                matrix[i][j] = false;
        }
    }
    return *this;
}

template<class T>
double  Image<T>::fill_ratio() {
    int count = 0;
    for (auto& i : matrix)
        for (auto& j : i)
            if (j != 0)
                count++;

    return (double)count / (double)(_maxX * _maxY);
}

template<>
double Image<char>::fill_ratio() {
    int count = 0;

    for (auto& i : matrix)
        for (auto& j : i)
            if (j != '0')
                count++;

    return (double)count / (double)(_maxX * _maxY);
}

template<>
double Image<bool>::fill_ratio() {
    int count = 0;

    for (int i = 0; i < matrix.size(); i++)
        for (int j = 0; j < matrix[i].size(); j++)
            if (matrix[i][j] != false)
                count++;

    return (double)count / (double)(_maxX * _maxY);
}

template<class T>
T  Image<T>::operator()(int x, int y) const {
    return matrix[x][y];
}

template<class T>
T& Image<T>::operator()(int x, int y) {
    return matrix[x][y];
}

template<>
bool Image<bool>::operator()(int x, int y) const {
    bool tmp = matrix[x][y];
    return tmp;
}

template<>
bool& Image<bool>::operator()(int x, int y) {
    bool tmp = matrix[x][y];
    return tmp;
}

template<class T>
void Image<T>::change() {
    T value;
    for (int i = 0; i < _maxX; i++) {
        for (int j = 0; j < _maxY; j++) {
            cin >> value;
            matrix[i][j] = value;
        }
        cout << endl;
    }
}

template<>
void Image<char>::change() {
    char value;
    for (int i = 0; i < _maxX; i++) {
        for (int j = 0; j < _maxY; j++) {
            cin >> value;
            matrix[i][j] = value;
        }
        cout << endl;
    }
}

template<class T>
void menu(Image<T>& img1, Image<T>& img2, int X, int Y) {
    while (true) {
        int i;
        cout << "1. Create a circle" << endl;
        cout << "2. Print a image" << endl;
        cout << "3. Invert a image" << endl;
        cout << "4. Sum two images" << endl;
        cout << "5. Sum image with bool" << endl;
        cout << "6. Multiply two images" << endl;
        cout << "7. Multiply image with bool" << endl;
        cout << "8. Fill ratio" << endl;
        cout << "9. Change the composition" << endl;
        cout << "10. Index: replace" << endl;
        cout << "11.Index: browse" << endl;
        cout << "12. Complete" << endl;
        cin >> i;

        switch (i) {
        case 1: {
            int x, y, radius;
            cout << "Enter the coordinates of the center and the radius of the circle" << endl;
            cin >> x >> y >> radius;
            while ((x - radius) < 0 || (y - radius) < 0 || (x + radius) > X || (y + radius) > Y) {
                cout << "Error" << endl;
                cout << "Enter the coordinates of the center and the radius of the circle" << endl;
                cin >> x >> y >> radius;
            }
            cout << "Enter the value of the pixel" << endl;
            T value;
            cin >> value;
            Image<T> tmp = cret_circle(img1, x, y, radius, value);
            cout << tmp;
            break;
        }
        case 2: {
            cout << img1;
            break;
        }
        case 3: {
            !img1;
            break;
        }
        case 4: {
            img1 = img1 + img2;
            break;
        }
        case 5: {
            T value;
            cout << "Enter a value" << endl;
            cin >> value;
            img1 = img1 + value;
            break;
        }
        case 6: {
            img1 = img1 * img2;
            break;
        }
        case 7: {
            T value;
            cout << "Enter a value" << endl;
            cin >> value;
            img1 = img1 * value;
            break;
        }
        case 8: {

            cout << img1.fill_ratio() << endl;
            break;
        }
        case 9: {
            cout << "Enter a value" << endl;
            img1.change();
            break;
        }
        case 10: {
            T value;
            int x, y;
            cout << "enter the X and Y values" << endl;
            cin >> x >> y;
            if (x < 0 || x > X || y < 0 || y > Y) {
                while (x < 0 || x > X || y < 0 || y > Y) {
                    cout << "Error" << endl;
                    cout << "enter the X and Y values" << endl;
                    cin >> x >> y;
                }
            }
            cout << "Enter a value" << endl;
            cin >> value;
            img1(x, y) = value;
            break;
        }
        case 11: {
            int x, y;
            cout << "enter the X and Y values" << endl;
            cin >> x >> y;
            if (x < 0 || x > X || y < 0 || y > Y) {
                while (x < 0 || x > X || y < 0 || y > Y) {
                    cout << "Error" << endl;
                    cout << "enter the X and Y values" << endl;
                    cin >> x >> y;

                }
            }
            cout << img1(x, y) << endl;
            break;
        }
        case 12: {
            return;
            break;
        }
        default: {
            cout << "Error" << endl;
            cin >> i;
            break;
        }
        }
    }
}

template<class T>
void select_img(Image<T>& img1, Image<T>& img2, int x, int y) {
    int num;
    while (true) {
        cout << "Select image" << endl;
        cout << "1. First Image" << endl;
        cout << "2. Second Image" << endl;
        cout << "3. Complete" << endl;
        cin >> num;
        switch (num) {
        case 1:
            menu(img1, img2, x, y);
            break;
        case 2:
            menu(img2, img1, x, y);
            break;
        case 3:
            return;
        default:
            cout << "Error" << endl;
            break;
        }
    }
}

void create_by_type(int type) {
    int x, y;
    cout << "Enter X and Y of the image" << endl;
    cin >> x >> y;

    while (x < 0 || y < 0) {
        cout << "Enter X and Y of the image" << endl;
        cin >> x >> y;
    }
    if (type == 1) {
        Image<bool> img1(x, y);
        Image<bool> img2(x, y);
        select_img<bool>(img1, img2, x, y);
    }
    if (type == 2) {
        Image<char> img1(x, y);
        Image<char> img2(x, y);
        select_img<char>(img1, img2, x, y);
    }
    if (type == 3) {
        Image<short> img1(x, y);
        Image<short> img2(x, y);
        select_img<short>(img1, img2, x, y);
    }
    if (type == 4) {
        Image<float> img1(x, y);
        Image<float> img2(x, y);
        select_img<float>(img1, img2, x, y);
    }
}

void select_type() {
    while (true) {
        int i;
        cout << "Select type" << endl;
        cout << "1. bool" << endl;
        cout << "2. char" << endl;
        cout << "3. short" << endl;
        cout << "4. float" << endl;
        cout << "5. complete" << endl;
        cin >> i;
        switch (i) {
        case 1: {
            create_by_type(1);
            break;
        }
        case 2: {
            create_by_type(2);
            break;
        }
        case 3: {
            create_by_type(3);
            break;
        }
        case 4: {
            create_by_type(4);
            break;
        }
        case 5: {
            return;
        }
        default: {
            cout << "Error" << endl;
            break;
        }
        }
    }
}

int main() {
    select_type();
    return 0;
}
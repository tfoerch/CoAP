// g++-12 --std=c++17 -o ./Inheritance-c++17.gcc Inheritance-c++17.cpp; clang++-14 --std=c++17  -o ./Inheritance-c++17.clang Inheritance-c++17.cpp
#include <vector>
#include <iostream>
#include <array>
#include <memory>
#include <numeric>
#include <chrono>
#include <valgrind/callgrind.h>

class Canvas;

template <std::size_t  dimension>
using Coordinate = std::array<double, dimension>;

using Coordinate2D = Coordinate<2>;

class Shape
{
public:
  virtual ~Shape() = default;
  inline void draw(Canvas&  canvas) const
  { doDraw(canvas); }
  inline std::pair<Coordinate2D, Coordinate2D> getSurroundingRectangleCorners() const
  { return doGetSurroundingRectangleCorners(); }
  inline const Coordinate2D& getPosition() const
  { return doGetPosition(); }
  inline double calcSurfaceArea() const
  { return doCalcSurfaceArea(); }
  inline double calcCircumference() const
  { return doCalcCircumference(); }
private:
  virtual void doDraw(Canvas&  canvas) const = 0;
  virtual std::pair<Coordinate2D, Coordinate2D> doGetSurroundingRectangleCorners() const = 0;
  virtual const Coordinate2D& doGetPosition() const = 0;
  virtual double doCalcSurfaceArea() const = 0;
  virtual double doCalcCircumference() const = 0;
};

class Circle : public Shape
{
public:
  Circle(
    const Coordinate2D&  position,
    const double&        radius)
  : m_position(position),
    m_radius(radius)
  {}
  inline double getRadius() const { return m_radius; }
private:
  const Coordinate2D& doGetPosition() const override { return m_position; }
  std::pair<Coordinate2D, Coordinate2D> doGetSurroundingRectangleCorners() const override
  {
    return
      std::pair{Coordinate2D{m_position[0] - m_radius,  m_position[1] - m_radius},
                Coordinate2D{m_position[0] + m_radius,  m_position[1] + m_radius}};
  }
  void doDraw(Canvas&  canvas) const override;
  double doCalcSurfaceArea() const override
  {
    return ( pi * m_radius * m_radius );
  }
  double doCalcCircumference() const override
  {
    return
      ( 2 * pi * m_radius );
  }
  Coordinate2D  m_position; // center
  double        m_radius;
  static constexpr double pi = 3.14159265358979323846;
};

class Square : public Shape
{
public:
  Square(
    const Coordinate2D&  position,
    const double&        sideLength)
  : m_position(position),
    m_sideLength(sideLength)
  {}
  inline double getSideLength() const { return m_sideLength; }
private:
  const Coordinate2D& doGetPosition() const override { return m_position; }
  std::pair<Coordinate2D, Coordinate2D> doGetSurroundingRectangleCorners() const override
  {
    return std::pair{m_position, Coordinate2D{m_position[0] + m_sideLength,  m_position[1] + m_sideLength}};
  }
  void doDraw(Canvas&  canvas) const override;
  double doCalcSurfaceArea() const override
  {
    return (m_sideLength  * m_sideLength );
  }
  double doCalcCircumference() const override
  {
    return ( 4 * m_sideLength );
  }
  Coordinate2D  m_position; // lower left corner
  double        m_sideLength;
};

class Canvas
{
public:
  explicit Canvas(
    std::ostream&             os);
  void draw(const Circle& cirlce);
  void draw(const Square& square);
private:
  std::ostream&             m_os;
};

void Circle::doDraw(Canvas&  canvas) const
{ canvas.draw(*this); }

void Square::doDraw(Canvas&  canvas) const
{ canvas.draw(*this); }

template<class CharT, class Traits, typename Array, std::size_t... Is>
constexpr void printArray(
  std::basic_ostream<CharT,Traits>&  os,
  const Array&                       a,
  std::index_sequence<Is...>)
{
  ((os << (Is == 0? "" : ", ") << a[Is]), ...);
}

template<class CharT, class Traits, typename T, std::size_t N, typename Indices = std::make_index_sequence<N>>
auto& operator<<(
    std::basic_ostream<CharT,Traits>&  os,
    const std::array<T, N>&            a)
{
  os << '<';
  printArray(os, a, Indices{});
  os << '>';
  return os;
}

Canvas::Canvas(
  std::ostream&             os)
: m_os(os)
{}

void Canvas::draw(const Circle& cirlce) {
  m_os << "draw Circle(" << cirlce.getPosition() << ", " << cirlce.getRadius() << ")\n";
}
void Canvas::draw(const Square& square) {
  m_os << "draw Square(" << square.getPosition() << ", " << square.getSideLength() << ")\n";
}

using ShapePtr = std::unique_ptr<Shape>;
using ShapeVector = std::vector<ShapePtr>;

// utilities to generate test data
template <std::size_t  number>
struct FibonacciCalculator
{
  static constexpr unsigned long value =
    ( FibonacciCalculator<number - 2>::value +
      FibonacciCalculator<number - 1>::value );
};

template <>
struct FibonacciCalculator<1>
{
  static constexpr unsigned long value = 1;
};

template <>
struct FibonacciCalculator<2>
{
  static constexpr unsigned long value = 1;
};

template<std::size_t  number>
ShapePtr indexToData()
{
  const std::size_t maxFib = 50;
  const std::size_t maxValue = 20000;
  constexpr unsigned long firstValue =
    FibonacciCalculator<number % maxFib + 1>::value +
    FibonacciCalculator<(number + maxFib/2) % maxFib + 1>::value + number/maxFib;
  constexpr unsigned long secondValue =
    FibonacciCalculator<(number + 5) % maxFib + 1>::value +
    FibonacciCalculator<(number + maxFib/2 + 7) % maxFib + 1>::value + number/maxFib;
  constexpr unsigned long thirdValue =
    FibonacciCalculator<(number + 11) % maxFib + 1>::value +
    FibonacciCalculator<(number + maxFib/2 + 13) % maxFib + 1>::value + number/maxFib;
  std::cout << firstValue << ", " << secondValue << ", " << thirdValue << '\n';
  constexpr double firstFloatValue = static_cast<double>(static_cast<int>(firstValue % maxValue) - static_cast<int>(maxValue/2)) / 1000;
  constexpr double secondFloatValue = static_cast<double>(static_cast<int>(secondValue % maxValue) - static_cast<int>(maxValue/2)) / 1000;
  constexpr double thirdFloatValue = static_cast<double>(static_cast<int>(thirdValue % maxValue) - static_cast<int>(maxValue/2)) / 1000;
  return
    ( (number % 2) ?
      static_cast<ShapePtr>(std::make_unique<Square>(Coordinate2D{firstFloatValue, secondFloatValue}, thirdFloatValue)) :
      static_cast<ShapePtr>(std::make_unique<Circle>(Coordinate2D{firstFloatValue, secondFloatValue}, thirdFloatValue)) );
}

template<typename T, T... ints>
void fillShapeVector(ShapeVector&  shapeVector, std::integer_sequence<T, ints...> int_seq)
{
  (shapeVector.emplace_back(indexToData<ints>()), ...);
}

int main(){
  const std::size_t numShapes = 100;
  Canvas  canvas(std::cout);
  ShapeVector  shapeVector(numShapes);
  fillShapeVector(shapeVector, std::make_index_sequence<numShapes>{});
  auto start = std::chrono::high_resolution_clock::now();
  CALLGRIND_START_INSTRUMENTATION;
  CALLGRIND_TOGGLE_COLLECT;
  for (const auto& shapePtr : shapeVector){
    if (shapePtr){
      shapePtr->draw(canvas);
    }
  }
  double sumOfSurfaceAreas = 0;
  sumOfSurfaceAreas =
    std::accumulate(shapeVector.begin(), shapeVector.end(),
                    sumOfSurfaceAreas,
                    [](
                      double      value,
                      const auto& shapePtr)
                    {
                      if (shapePtr) {
                        return
                          std::move(value) + shapePtr->calcSurfaceArea();
                      }
                      else {
                        return std::move(value);
                      }
                    });
  std::cout << "sum of surface areas : " << sumOfSurfaceAreas << '\n';
  CALLGRIND_TOGGLE_COLLECT;
  CALLGRIND_STOP_INSTRUMENTATION;
  auto finish = std::chrono::high_resolution_clock::now();
  std::cout << "execution time: " << std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count() << " us\n";
  auto minmax = [](std::pair<Coordinate2D, Coordinate2D> curCorner, const ShapePtr& shapePtr)
    {
      auto result = std::move(curCorner);
      if (shapePtr){
        const auto& corners = shapePtr->getSurroundingRectangleCorners();
        result.first[0] = std::min(result.first[0], corners.first[0]);
        result.first[1] = std::min(result.first[1], corners.first[1]);
        result.second[0] = std::max(result.second[0], corners.second[0]);
        result.second[1] = std::max(result.second[1], corners.second[1]);
      }
      return result;
    };
}

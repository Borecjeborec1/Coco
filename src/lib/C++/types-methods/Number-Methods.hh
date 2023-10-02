#include <string>
#include <cmath>
#include <sstream>
#include <iomanip>

double JS_valueOf(double value) { return static_cast<double>(value); }
std::string JS_toFixed(double value, int decimalPlaces) {
  std::ostringstream stream;
  stream.precision(decimalPlaces);
  stream << std::fixed << value;
  return stream.str();
}

std::string JS_toExponential(double value, int decimalPlaces) {
  std::ostringstream stream;
  stream.precision(decimalPlaces);
  stream << std::scientific << value;
  return stream.str();
}
std::string JS_toPrecision(double value, int precision) {
  std::ostringstream stream;

  if (value == 0.0) {
    stream << std::fixed << std::setprecision(precision) << value;
  } else {
    int intPartLength = static_cast<int>(std::log10(std::abs(value))) + 1;
    int significantDigits = precision - intPartLength;

    if (significantDigits <= 0) {
      stream << std::fixed << std::setprecision(precision) << value;
    } else {
      stream << std::fixed << std::setprecision(significantDigits) << value;
    }
  }

  return stream.str();
}
std::string JS_toString(double value) {
  std::ostringstream stream;
  if (std::fmod(value, 1.0) == 0.0) {
    stream << static_cast<int>(value);
  } else {
    stream << value;
  }
  return stream.str();
}

std::string JS_toLocaleString(double value) { return std::to_string(value); }

bool JS_isFinite(double value) { return std::isfinite(value); }

bool JS_isNaN(double value) { return std::isnan(value); }

int JS_valueOf(int value) { return static_cast<int>(value); }
std::string JS_toString(int value) {
  std::ostringstream stream;
  if (std::fmod(value, 1.0) == 0.0) {
    stream << static_cast<int>(value);
  } else {
    stream << value;
  }
  return stream.str();
}

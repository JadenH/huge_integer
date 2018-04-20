// Jaden Holladay
// U0772519
// .h is for declaring the class and including any system libraries.
// There should be no "using" here.

#include <iostream>
#include <string>

/*
 * The huge_integer class is used to build and compute large numbers to avoid integer overflow.
 * It uses a private string (value) that represents an integer and can perform any Arithmetic operators.
 * At any point get_value() may be called to retrieve the current value of the huge_integer.
 */
class huge_integer
{
  private:
    std::string value;
    std::string add(const std::string left, const std::string right) const;
    std::string multiply(const std::string left, const std::string right) const;
    std::string subtract(const std::string left, const std::string right) const;
    std::string divide(const std::string left, const std::string right) const;
    std::string modulo(const std::string left, const std::string right) const;
    std::string trim_zeros(std::string left) const;
    bool leftIsLarger(std::string left, std::string right) const;

  public:
    huge_integer();
    huge_integer(std::string val);
    huge_integer(const huge_integer & other); // Copy constructor

    std::string get_value() const;

    // Allows for setting one huge_integer class equal to another.
    huge_integer & operator= (const huge_integer & rhs);

    // Overload the Arithmetic operators.
    // const ensures that "this" object does not get modified.
    huge_integer operator+ (const huge_integer & rhs) const;
    huge_integer operator- (const huge_integer & rhs) const;
    huge_integer operator* (const huge_integer & rhs) const;
    huge_integer operator/ (const huge_integer & rhs) const;
    huge_integer operator% (const huge_integer & rhs) const;
};

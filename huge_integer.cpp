// Jaden Holladay
// U0772519
// .cpp is for all class function and friend function definitions.

#include "huge_integer.h"

using namespace std;

// ======================== PRIVATE ========================================

/*
 * Trims any leading zeros given a string that represents an integer.
 */
string huge_integer::trim_zeros(string s) const
{
  // Cited: This while loop is from the class example code.
  // Strip out any leading 0's from our result (but leave at least one digit).
  // (Only useful for subtraction, but I'm giving it to you here.)
  while (s.length() > 1 && s[0] == '0')
    s.erase(0, 1);
  return s;
}

// Cited:  This code taken from the class example. ======================

/*
 * Adds two integers stored in strings, building a string result.
 */
string huge_integer::add (const string left, const string right) const
{
  // Build up a string to contain the result.
  string result = "";

  // Work right to left.
  int left_pos  = left.length()  - 1;
  int right_pos = right.length() - 1;

  int carry = 0;
  // Loop, adding columns until no more digits remain.

  while (left_pos >= 0 || right_pos >= 0 || carry > 0)
  {
    // Get the digit from each string, or 0 if none.
    int left_digit  = left_pos  >= 0 ? left[left_pos--]   - '0' : 0;
    int right_digit = right_pos >= 0 ? right[right_pos--] - '0' : 0;

    // Calcuate the sum of the digits.
    int sum = left_digit + right_digit + carry;
    carry = sum / 10;
    sum   = sum % 10;

    // Put the sum into the new string (at the left side)

    result.insert (0, 1, (char)(sum+'0') );
  }

  return trim_zeros(result);
}

/*
 * Multiplies two integers stored in strings, building a string result.
 * The algorithm is long multiplication, starting with the most significant
 * digit of the multiplier.
 */
string huge_integer::multiply (const string left, const string right) const
{
  string result = "0";

  int right_pos = 0;

  while (right_pos < right.length())
  {
    result.append("0");  // Multiply the product by 10.

    int right_digit = right[right_pos++] - '0';

    for (int i = 0; i < right_digit; i++)
      result = add(result, left);
  }

  return result;
}

// End Cited Code ======================================================

/*
 * Subtracts two integers stored in strings, building a string result.
 */
string huge_integer::subtract (const string left, const string right) const
{
  // Build up a string to contain the result.
  string result = "";

  // Work right to left.
  int left_pos  = left.length()  - 1;
  int right_pos = right.length() - 1;

  int carry = 0;

  // Loop, subtracting columns until no more digits remain.
  while (left_pos >= 0 || right_pos >= 0 || carry > 0)
  {
    // Get the digit from each string, or 0 if none.
    int left_digit  = left_pos  >= 0 ? left[left_pos--]   - '0' : 0;
    int right_digit = right_pos >= 0 ? right[right_pos--] - '0' : 0;

    // Calcuate the difference of the digits.
    // If our difference is less than zero then we should carry.
    // Set the difference to the positive value of difference % 10.
    int difference = (left_digit - carry) - right_digit;
    carry        = difference < 0 ? 1 : 0;
    difference   = (difference % 10 + 10) % 10;

    // Put the difference into the new string (at the left side)
    result.insert (0, 1, (char)(difference + '0'));

    // If we have a carry but we are out of bounds on our left number
    // then our result is negative and we should return 0.
    if (left_pos < 0 && carry == 1)
    {
      result = '0';
      break;
    }
  }

  return trim_zeros(result);
}

/*
 * Divides two integers stored in strings, building a string result.
 * Uses long division method.
 */
string huge_integer::divide (const string left, const string right) const
{
  // Trim any leading zeros from the strings passed in.
  string left_string = trim_zeros(left);
  string right_string = trim_zeros(right);

  // Setup some strings for us to use in the algorithm.
  string result = "0";
  string carry = "0";

  // Iterate through the left string digit by digit.
  for (int index = 0; index < left.length(); index++)
  {
    // Set our count to zero when we move to the next digit.
    string count = "0";

    // Multiply the carry by a factor of 10.
    carry = multiply(carry, "10");

    // Get the current digit we are iterating on.
    string current_digit(1, left_string[index]);
    // Add the carry to our current digit.
    current_digit = add(carry, current_digit);

    // While left digit string is larger than or equal to the right string.
    while (!leftIsLarger(right_string, current_digit))
    {
      // Subtract the right_string from our left digit and
      // increment the count by 1.
      current_digit = subtract(current_digit, right_string);
      count = add(count, "1");
    }

    // Set our carry as the the remainder after subtracting as much as possible.
    carry = current_digit;

    // We add the amount of times we were able to subtract to our result.
    result.append(count);
  }

  // Return the result after trimming any leading zeros.
  return trim_zeros(result);
}

/*
 * Computes Modulo of two integers stored in strings, building a string result.
 * This is like the division algorithm, but takes the result to be the final carry.
 */
string huge_integer::modulo (const string left, const string right) const
{
  // Trim any leading zeros from the strings passed in.
  string left_string = trim_zeros(left);
  string right_string = trim_zeros(right);

  // Setup some strings for us to use in the algorithm.
  string carry = "0";

  // Iterate through the left string digit by digit.
  for (int index = 0; index < left.length(); index++)
  {
    // Multiply the carry by a factor of 10.
    carry = multiply(carry, "10");

    // Get the current digit we are iterating on.
    string current_digit(1, left_string[index]);
    // Add the carry to our current digit.
    current_digit = add(carry, current_digit);

    // While left digit string is larger than or equal to the right string.
    while (!leftIsLarger(right_string, current_digit))
    {
      // Subtract the right_string from our left digit and
      current_digit = subtract(current_digit, right_string);
    }

    // Set our carry as the left digit (or the remainder).
    carry = current_digit;
  }

  // Return the carry after trimming any leading zeros.
  // Carry is the remainder after dividing as much as possible.
  return trim_zeros(carry);
}

/*
 * Takes two integers stored in strings and returns true if the left string is
 * larger than the right, otherwise false.
 */
bool huge_integer::leftIsLarger (const string left, const string right) const
{
  // If the lengths of our digits are the same we need
  // to check digit by digit from the left to compare.
  if (left.length() == right.length())
  {
    // Start left and work right.
    for (int i = 0; i < left.length(); i++)
    {
      int left_digit = left[i] - '0';
      int right_digit = right[i] - '0';
      if (left_digit > right_digit)
      {
        return true;
      }
      else if (left_digit < right_digit)
      {
        return false;
      }
    }
  }
  // If the lengths aren't the same we can compare lengths to get the result.
  return left.length() > right.length();
}
// ======================== /PRIVATE ========================================

// ======================== PUBLIC ==========================================

// Constructor that initializes the huge_integer with a default value of zero.
huge_integer::huge_integer()
{
  value = '0';
}

// Constructor that initializes the huge_integer with the string value passed in.
// string: val -> The value that the huge_integer object is initialized with.
huge_integer::huge_integer(string val)
{
  value = val;
}

// Constructor that initializes the huge_integer with the string value passed in.
// string: val -> The value that the huge_integer object is initialized with.
huge_integer::huge_integer(const huge_integer & other)
{
  value = other.value;
}

// Method that returns the current value of the huge_integer class.
string huge_integer::get_value() const
{
  return value;
}

// Overloads the = operator to set the huge_integer class equal to another huge integer class.
// This copies the value and does not point to the same object.
huge_integer & huge_integer::operator= (const huge_integer & rhs)
{
  value = rhs.value;
  return *this;
}

// Overloads the + (add) operator to add two huge_integer classes.
// Uses the string add function provided in the class example code.
huge_integer huge_integer::operator+ (const huge_integer & rhs) const
{
  huge_integer result (add(value, rhs.value));
  return result;
}

// Overloads the * (multiply) operator to multiply two huge_integer classes.
// Uses the string multiply function provided in the class example code.
huge_integer huge_integer::operator* (const huge_integer & rhs) const
{
  huge_integer result (multiply(value, rhs.value));
  return result;
}

// Overloads the - (subtract) operator to subtract two huge_integer classes.
// Uses the private string subtract function of the huge_integer class.
huge_integer huge_integer::operator- (const huge_integer & rhs) const
{
  huge_integer result (subtract(value, rhs.value));
  return result;
}

// Overloads the - (subtract) operator to subtract two huge_integer classes.
// Uses the private string subtract function of the huge_integer class.
huge_integer huge_integer::operator/ (const huge_integer & rhs) const
{
  huge_integer result (divide(value, rhs.value));
  return result;
}

// Overloads the - (subtract) operator to subtract two huge_integer classes.
// Uses the private string subtract function of the huge_integer class.
huge_integer huge_integer::operator% (const huge_integer & rhs) const
{
  huge_integer result (modulo(value, rhs.value));
  return result;
}

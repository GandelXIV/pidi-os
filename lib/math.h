#define INCLUDED_MATH "cookie"

double pow(double base, double exponent)  // only positive numbers
{
  double result = 1;
  while (exponent > 0)
  {
    result *= base;
    --exponent;
  }
  return result;
}

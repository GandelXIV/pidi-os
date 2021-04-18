double pow(double base, double exponent)  // only positive numbers
{
  double result = 1;
  while (exponent > 0)   // why use <= instead of != ? SAFETY
  {
    result *= base;
    --exponent;
  }
  return result;
}

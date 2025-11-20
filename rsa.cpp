#include <bits/stdc++.h>
using namespace std;

long long gcd(long long a, long long b)
{
  while (b)
  {
    long long temp = b;
    b = a % b;
    a = temp;
  }
  return a;
}

long long modinv(long long a, long long m)
{
  // eea
  long long m0 = m, x0 = 0, x1 = 1;
  while (a > 1)
  {
    long long q = a / m;
    long long temp_m = m;
    m = a % m;
    a = temp_m;

    long long temp_x = x0;
    x0 = x1 - q * x0;
    x1 = temp_x;
  }
  if (x1 < 0)
    x1 += m0;
  return x1;
}

long long modpow(long long base, long long exp, long long mod)
{

  long long result = 1;
  base = base % mod;
  while (exp > 0)
  {
    if (exp % 2 == 1)
      result = (result * base) % mod;
    exp = exp / 2;
    base = (base * base) % mod;
  }
  return result;
}

long long rsa_encrypt(long long m, long long e, long long n)
{
  if (!(0 <= m && m < n))
  {
    cout << "Error: Message out of valid range\n";
    exit(1);
  }
  return modpow(m, e, n);
}

long long rsa_decrypt(long long c, long long d, long long n)
{
  return modpow(c, d, n);
}

int main()
{
  try
  {
    long long p, q;
    cout << "Enter prime p: ";
    cin >> p;
    cout << "Enter prime q (!=p): ";
    cin >> q;

    long long n = p * q;
    long long phi = (p - 1) * (q - 1);
    cout << "n = " << n << ", phi = " << phi << "\n";

    // 1 < e < phi and gcd(e, phi) == 1
    long long e;
    cout << "Enter public exponent e (1 < e < " << phi << ", gcd(e," << phi << ")=1): ";
    cin >> e;

    if (!(1 < e && e < phi && gcd(e, phi) == 1))
    {
      cout << "Error: Invalid e! e must be >1 and <phi, coprime to phi.\n";
      return 1;
    }

    long long d = modinv(e, phi);

    cout << "\nPublic key: (e=" << e << ", n=" << n << ")\n";
    cout << "Private key: (d=" << d << ", n=" << n << ")\n";

    long long m;
    cout << "Enter message integer m (0 <= m < " << n << "): ";
    cin >> m;

    if (!(0 <= m && m < n))
    {
      cout << "Error: Invalid message! m must be in range 0 to n-1.\n";
      return 1;
    }

    cout << "\nOriginal message: " << m << "\n";
    long long c = rsa_encrypt(m, e, n);
    cout << "Encrypted ciphertext: " << c << "\n";

    long long m_recovered = rsa_decrypt(c, d, n);
    cout << "Decrypted message: " << m_recovered << "\n";
  }
  catch (exception &ex)
  {
    cout << "Error: " << ex.what() << "\n";
    return 1;
  }

  return 0;
}

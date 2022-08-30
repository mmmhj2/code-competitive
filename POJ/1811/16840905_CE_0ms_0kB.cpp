// C++ includes used for precompiling -*- C++ -*-

// Copyright (C) 2003-2018 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// Under Section 7 of GPL version 3, you are granted additional
// permissions described in the GCC Runtime Library Exception, version
// 3.1, as published by the Free Software Foundation.

// You should have received a copy of the GNU General Public License and
// a copy of the GCC Runtime Library Exception along with this program;
// see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
// <http://www.gnu.org/licenses/>.

/** @file stdc++.h
 *  This is an implementation file for a precompiled header.
 */

// 17.4.1.2 Headers

// C
#ifndef _GLIBCXX_NO_ASSERT
#include <cassert>
#endif
#include <cctype>
#include <cerrno>
#include <cfloat>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#if __cplusplus >= 201103L
#include <ccomplex>
#include <cfenv>
#include <cinttypes>
#include <cstdalign>
#include <cstdbool>
#include <cstdint>
#include <ctgmath>
#include <cuchar>
#include <cwchar>
#include <cwctype>
#endif

// C++
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>

#if __cplusplus >= 201103L
#include <array>
#include <atomic>
#include <chrono>
#include <codecvt>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#endif

#if __cplusplus >= 201402L
#include <shared_mutex>
#endif

#if __cplusplus >= 201703L
#include <charconv>
#include <filesystem>
#endif


#if RAND_MAX <= 0x7FFF
#define getRand() rand() * rand() * rand() * rand()
#else
#define getRand() rand() * rand()
#endif

using namespace std;
typedef long long i64;

template<class T>
T templateAbs(T x)
{
	if (x < 0)
		return -x;
	return x;
}

i64 modularMul(i64 a, i64 b, i64 mod)
{
	i64 ret = 0;
	a %= mod, b %= mod;

	while (b)
	{
		if (b & 1)
			ret = (ret + a) % mod;
		a = (a + a) % mod;
		b = b >> 1;
	}
	return ret;
}

i64 modularExp(i64 base, i64 exp, i64 mod)
{
	i64 ret = 1;
	base %= mod;
	while (exp)
	{
		if (exp & 1)
			ret = modularMul(ret, base, mod);
		base = modularMul(base, base, mod);
		exp = exp >> 1;
	}
	return ret;
}

namespace MR_PrimeTest
{
	vector<int> primeList = { 1, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41,
			43 };

	bool miller_rabin(i64 d, i64 n, i64 a)
	{
		i64 x = modularExp(a, d, n);
		if (x == 1 || x == n - 1)
			return true;
		while (d != n - 1)
		{
			x = modularMul(x, x, n), d *= 2;
			if (x == 1)
				return false;
			if (x == n - 1)
				return true;
		}
		return true;
	}

	bool isPrime(i64 n)
	{
		if (n == 2 || n == 3)
			return true;
		if (((n & 1) == 0) || n <= 1)
			return false;

		i64 d = n - 1;
		while ((d & 1) == 0)
			d = d >> 1;
		for (vector<int>::iterator itr = primeList.begin();
				itr != primeList.end(); ++itr)
			if (*itr >= n)
				break;
			else if (!miller_rabin(d, n, *itr))
				return false;
		return true;
	}

}

namespace pollar_rho
{
	using namespace MR_PrimeTest;

	i64 rng(i64 x, i64 offset, i64 mod)
	{
		return (modularMul(x, x, mod) + offset + mod) % mod;
	}

	i64 pollard_rho(i64 n)
	{
		if(n == 1)
			return 1;
		if((n & 1) == 0)
			return 2;

		i64 x, y, offset, d;
		x = y = (1LL * getRand() % (n - 2)) + 2;
		offset = (1LL * getRand() % (n - 1)) + 1;
		d = 1;

		while(d == 1)
		{
			x = rng(x, offset, n);
			y = rng(rng(y, offset, n), offset, n);
			d = __gcd(templateAbs(x - y), n);
			if(d == n)
				return n;
		}
		return d;
	}
}

void getAllFactors(i64 n, vector<i64> & fac)
{
	if(MR_PrimeTest::isPrime(n))
		return fac.push_back(n), (void) NULL;
	i64 p = n;
	while(p >= n)
		p = pollar_rho::pollard_rho(n);
	getAllFactors(p, fac);
	getAllFactors(n / p, fac);
}

int main()
{
	int T;
	scanf("%d", &T);

	while (T--)
	{
		i64 N;
		scanf("%lld", &N);
		if (MR_PrimeTest::isPrime(N))
			printf("Prime\n");
		else
		{
			vector<i64> fac;
			fprintf(stderr, "Not a prime\n");
			getAllFactors(N, fac);
			printf("%lld\n", *min_element(fac.begin(), fac.end()));
		}
	}

	return 0;
}

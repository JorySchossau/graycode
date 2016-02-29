/* Copyright (c) 2014, Jory Schossau
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 * 
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

// Description
// Conversion functions between integers and graycode
//
// Features
// * Convert an integer to graycode
// * Convert a graycode number to integer
// 
// To Do
//
// Usage
// simply include this header file in your c++ project. #include "graycode.h"
// Use methods int:graycode(int) and int:ungraycode(int) to perform conversions
//
// Notes
//
// Example:

#pragma once

namespace Graycode {

	namespace priv {
		int getHighestBitPosition(unsigned x) {
			// modified from Hacker's Delight: /* Julius Goryavsky's version of Harley's algorithm.  // 17 elementary ops plus an indexed load, if the machine // has "and not." */
			// Returns -1 if there is no highest bit
			const char u = 99;
			static char table[64] =
			{32,31, u,16, u,30, 3, u,  15, u, u, u,29,10, 2, u,
				u, u,12,14,21, u,19, u,   u,28, u,25, u, 9, 1, u,
				17, u, 4, u, u, u,11, u,  13,22,20, u,26, u, u,18,
				5, u, u,23, u,27, u, 6,   u,24, 7, u, 8, u, 0, u};

			x = x | (x >> 1);    // Propagate leftmost
			x = x | (x >> 2);    // 1-bit to the right.
			x = x | (x >> 4);
			x = x | (x >> 8);
			x = x | (x >>16);
			x = x*0x06EB14F9;    // Multiplier is 7*255**3.
			return 32 - table[x >> 26] - 1;
		}
	}

	// Broken for some reason
	//template<class T>
	//static T* ungraycode(T* x) {
	//	unsigned int* n = reinterpret_cast<unsigned int*>(x);
	//	unsigned int* r = new unsigned int;
	//	unsigned short highPosition = priv::getHighestBitPosition(*n);
	//	if (highPosition < 0) {
	//		*r = 0;
	//		return reinterpret_cast<T*>(r);
	//	}
	//	*r |= *n & (1<<highPosition);
	//	for (int i=highPosition-1; i>=0; --i) {
	//		(*r) |= (((*r)>>1) ^ *n) & (1<<i);
	//	}
	//	T* result = reinterpret_cast<T*>(r);
	//	return result;
	//}
	template<class T>
	static T& ungraycode(T x) {
		unsigned int* n = reinterpret_cast<unsigned int*>(&x);
		unsigned int* r = new unsigned int;
		unsigned short highPosition = priv::getHighestBitPosition(*n);
		if (highPosition < 0) {
			*r = 0;
			return *reinterpret_cast<T*>(r);
		}
		*r |= *n & (1<<highPosition);
		for (int i=highPosition-1; i>=0; --i) {
			(*r) |= (((*r)>>1) ^ *n) & (1<<i);
		}
		T* result = reinterpret_cast<T*>(r);
		return *result;
	}

	// Broken for some reason
	//template<class T>
	//static T* graycode(T* x) {
	//	unsigned int* n = reinterpret_cast<unsigned int*>(x);
	//	unsigned int* r = new unsigned int;
	//	(*r) = (*n) ^ ((*n)>>1);
	//	T* result = reinterpret_cast<T*>(r);
	//	return result;
	//}
	template<class T>
	static T& graycode(T x) {
		unsigned int* n = reinterpret_cast<unsigned int*>(&x);
		unsigned int* r = new unsigned int;
		(*r) = (*n) ^ ((*n)>>1);
		T* result = reinterpret_cast<T*>(r);
		return *result;
	}
}


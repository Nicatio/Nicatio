/*
 * io.h
 *
 *  Created on: 2013. 1. 28.
 *      Author: Nicatio
 */

#ifndef IO_H_
#define IO_H_

#include <sys/types.h>
#if defined (__GNUC__)
		// There is also __GNUG__ macro which is equivalent with (__GNUC__ && __cplusplus)
		#include <dirent.h>
#else
		#include "../dirent/dirent.h"
#endif

#include <errno.h>
#include "vector"
#include "string"
#include "cstring"
#include "iostream"
#include "fstream"
#include "sstream"

using namespace std;

namespace nicatio {
class StringTokenizer
{
public:
	static vector<string> getTokens(const string& str, const string& delimiters = " ");
};

int getdir (
		string 							dir,
		vector<string> 					&files);
int getdirType (
		string 							dir,
		string 							type,
		vector<string> 					&files,
		const int&						abLoca);
vector<string> &split(
		const string 					&s,
		char 							delim,
		vector<string>					&elems);

vector<string> split(
		const string 					&s,
		char 							delim);

vector<double> readFileSingleLine(												// read a file and convert it into a dMatrix
		const char						*filename);
};

#endif /* IO_H_ */

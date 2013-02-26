/*
 * io.h
 *
 *  Created on: 2013. 1. 28.
 *      Author: HDSP
 */

#ifndef IO_H_
#define IO_H_

#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include "vector"
#include "string"
#include "cstring"
#include "iostream"

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


}


#endif /* IO_H_ */

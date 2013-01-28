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

int getdir (
		string 							dir,
		vector<string> 					&files);
int getdirType (
		string 							dir,
		string 							type,
		vector<string> 					&files);


}


#endif /* IO_H_ */

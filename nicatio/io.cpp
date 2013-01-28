/*
 * io.cpp
 *
 *  Created on: 2013. 1. 28.
 *      Author: HDSP
 */

#include "io.h"

using namespace std;

namespace nicatio {

int getdir (
		string 							dir,
		vector<string> 					&files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}

int getdirType (
		string 							dir,
		string 							type,
		vector<string> 					&files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {

    	char *token = strtok(dirp->d_name,".");
    	token = strtok(NULL,".");
		string to = token;
    	if (to.compare(type)) files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}

}



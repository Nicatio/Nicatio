/*
 * io.cpp
 *
 *  Created on: 2013. 1. 28.
 *      Author: Nicatio
 */

#include "io.h"

using namespace std;

namespace nicatio {

vector<string> StringTokenizer::getTokens(const string& str, const string& delimiters)
{
	string::size_type lastPos = str.find_first_not_of(delimiters, 0);
	string::size_type pos     = str.find_first_of(delimiters, lastPos);
	vector<string> tokens;
	while (string::npos != pos || string::npos != lastPos)
	{
		tokens.push_back(str.substr(lastPos, pos - lastPos));
		lastPos = str.find_first_not_of(delimiters, pos);
		pos = str.find_first_of(delimiters, lastPos);
	}
	return tokens;
}

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
		vector<string> 					&files,
		const int&						abLoca)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }
	if (abLoca){
		while ((dirp = readdir(dp)) != NULL) {

			vector<string> tokens = StringTokenizer::getTokens(dirp->d_name,".");
			if (tokens.size()>1) {
				if (!tokens[1].compare(type)) files.push_back(dir + "\\" + string(dirp->d_name));
			}

		}
	} else {
		while ((dirp = readdir(dp)) != NULL) {
			vector<string> tokens = StringTokenizer::getTokens(dirp->d_name,".");
			if (tokens.size()>1) {
				if (!tokens[1].compare(type)) files.push_back(string(dirp->d_name));
			}

		}
	}
    closedir(dp);
    return 0;
}


vector<string> &split(const string &s, char delim, vector<string> &elems) {
    stringstream ss(s);											// split function used for parsing PSF
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

vector<string> split(const string &s, char delim) {
    vector<string> elems;										// split function wrapper
    return split(s, delim, elems);
}

vector<double> readFileSingleLine(												// read a file and convert it into a dMatrix
		const char							*filename)
{
	ifstream FileI;
	FileI.open(filename,ios::in | ios::app);
	FileI.seekg (0, FileI.beg);
	vector<double> a;
	int i=0;
	char buffer[256];											// use limited buffer


	FileI.getline(buffer,256);								// get the entire line
	stringstream temp(buffer);
	vector<string> b = split(temp.str(),' ');				// split a line with tap
	int c = b.size();
	for(int j=0; j<c; j++) {
		stringstream tok(b[j]);
		double tok2;
		tok>>tok2;											// char to string and string to double
		a.push_back(tok2);									// push it into vector
	}



	FileI.close();

	return a;									// return dMatrix
}



};

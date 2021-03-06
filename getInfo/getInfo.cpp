// getInfo.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
//#include <Windows.h>
#include<vector>
#include <boost\filesystem\path.hpp>
#include<boost\filesystem\operations.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost\algorithm\string.hpp>
namespace fs = boost::filesystem;
namespace al = boost::algorithm;
using namespace std;

//bool dirExists(const string& dirName_in)
//{
//	DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
//	if (ftyp == INVALID_FILE_ATTRIBUTES)
//		return false;  //something is wrong with your path!  
//
//	if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
//		return true;   // this is a directory!  
//
//	return false;    // this is not a directory!  
//}

bool dirExists(const string dir_path) {
	fs::path dir(dir_path);
	if (fs::exists(dir) and fs::is_directory(dir)) {
		return true;
	}
	else {
		return false;
	}
}

vector<string>list_file_in_folder(const string folder,const bool & isFullPath) {
	if (dirExists(folder)) {
		vector<string> fileList;
		fs::directory_iterator end_iter;

		for (auto& entry : boost::make_iterator_range(fs::recursive_directory_iterator(fs::path(folder)), {}))
			
			if(fs::is_regular_file(entry.status()))
				if (isFullPath) {
					fileList.push_back(entry.path().string());
				}
				else
				{
					fileList.push_back(entry.path().filename().string());
				}
				
					
		return fileList;
	}
	
}

//bool endWith(const string &origin, const string &substring) {
//	return origin.compare(origin.size() - substring.size(), substring.size(), substring) == 0;
//}



//支持-f -tex
int main(int   argc, char*   argv[])
{	

	if (argc != 3) {
		cout << "参数错误" << endl;
		cout << "支持两个参数[-f ,-tex]" << endl;
		return 1;
	}
	string flag = argv[1];
	string folder = argv[2];

	if (flag =="-h") {
	
		cout << "支持两个参数[-f, -tex]" << endl;
		return 0;
	}

	if (dirExists(folder)) {
		//cout << "folder exist!" << endl;
		if (flag == "-f") {
			//list files in folder
			vector<string> files(list_file_in_folder(folder,true));
	
			for (auto &f : files) {
				cout << f << endl;
				
			}
		}
		if (flag == "-tex") {
			//list texture in folder
			// texture .jpg,.png,.tif
			vector<string> files(list_file_in_folder(folder,false));
			for (auto &f : files) {
				if (al::ends_with(f, ".jpg") ||al::ends_with(f, ".png")|| al::ends_with(f, ".tif")||al::ends_with(f,".tga")) {
					cout << f << endl;
					
				}
			}

		}
		
	}

    return 0;
}


//substance not working, only one argv works.
//int main(int   argc, char*   argv[])
//{
//
//	if (argc != 2) {
//		cout << "参数错误" << endl;
//		return 1;
//	}
//	
//	string folder = argv[1];
//
//
//	if (dirExists(folder)) {
//		//cout << "folder exist!" << endl;
//
//		//list texture in folder
//		// texture .jpg,.png,.tif
//		vector<string> files(list_file_in_folder(folder, false));
//		for (auto &f : files) {
//			if (al::ends_with(f, ".jpg") || al::ends_with(f, ".png") || al::ends_with(f, ".tif") || al::ends_with(f, ".tga")) {
//				cout << f << endl;
//
//			}
//		}
//	}
//			
//
//	return 0;
//}

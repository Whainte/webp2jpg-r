// webp2jpg.cpp
//
#include "stdafx.h"
#include<Magick++.h>
#include<filesystem>
#include<iostream>
#include<regex>
#include<queue>
#include<string>

using std::string;
using std::queue;
using std::cin;
using std::cout;
using std::endl;
using namespace Magick;
namespace fs = std::experimental::filesystem;
using fs::current_path;
using fs::path;
using fs::directory_entry;
using fs::directory_iterator;
//Possible alternative
//using fs::recursive_directory_iterator;

//This Program utilizes ImageMagick++ and the ImageMagick libraries for conversion
//This Program utilizes <filesystem> and must be built with C++

int main(int argc, char** argv)
{
	InitializeMagick(*argv);
	path p = current_path();
	string f;
	char confirm;

	//Confirm

	cout << "All webp files under the directory convert to jpeg format:";
	cout << endl << p.u8string() << endl;
	while (1) {
		cout << "Please confirm(confirm with y)";
		confirm = getchar();
		if (confirm != 'y' && confirm != '\n')return 1;
		if (confirm == 'y')break;
	}
	getchar();

	queue<path> tasks;
	tasks.push(p);
	directory_iterator end;
	Image i;
	try {
		while (!tasks.empty()) {
			p = tasks.front();
			tasks.pop();
			if (fs::is_directory(p)) {
				for (directory_iterator iter(p); iter != end; iter++) {
					tasks.push(iter->path());
				}
			}
			else {
				f = p.u8string();
				if (std::regex_match(f, std::regex("(.*)(.webp)"))) {
					cout << "Converting:" << f << endl;//Comment this if you seek performance
					i.read(f);
					//cout<<"    " << f << " read, converting format..." << endl;
					i.magick("JPEG");
					f = f.replace(f.length() - 4, f.length(), "jpg");
					//cout << "    Converion success, writing to disk..." << endl;
					i.write(f);
					//cout << "Finished" << endl;
				}
			}

		}
	}
	catch (Exception e) {
		cout << e.what();
	}
	cout << "Done" << endl;
	return 0;
}


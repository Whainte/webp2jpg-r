// webp2jpg.cpp
//
#include "stdafx.h"
#include<Magick++.h>
#include<filesystem>
#include<iostream>
#include<regex>
#include<stack>
#include<string>
#include "func_def.h"

using std::string;
using std::stack;
using std::cin;
using std::cout;
using std::endl;
using namespace Magick;
namespace fs = std::experimental::filesystem;
using fs::current_path;
using fs::path;
using fs::directory_entry;
using fs::directory_iterator;
using fs::exists;
using fs::is_regular_file;
using fs::is_symlink;
using fs::absolute;
using fs::canonical;
//Possible alternative
//using fs::recursive_directory_iterator;

//This Program utilizes ImageMagick++ and the ImageMagick libraries for conversion
//This Program utilizes <filesystem> and must be built with C++


int main(int argc, char** argv)
{
	if (argc == 1) {
		showHelp();
		return 1;
	}
	try {
		InitializeMagick(*argv);
		path p;
		bool rec = false;
		for (int i = 1; i < argc;i++) {
			if (string(argv[i]) == "-h") {
				showHelp();
				return 0;
			}
			else if (string(argv[i]) == "-r") {
				if (rec) {
					cout << "Error: webp2jpg .. -r <path> ..\n";
					return 2;
				}
				else {
					rec = true;
				}
			}
			else if (rec) {
				p = canonical(path(argv[i]));
				if (!exists(p)) {
					cout << "Warning: " << p.u8string() << " does not exist.\n";
				}
				else {
					conv_recursive(p);
				}
				rec = false;
			}
			else {
				p = canonical(path(argv[i]));
				if (!(is_regular_file(p) || is_symlink(p))) {
					cout << "Warning: " << p.u8string() << " is not a valid file.\n";
				}
				else {
					conv(p);
				}
			}
		}
		cout << "Done" << endl;
	}
	catch (Exception e) {
		cout << e.what();
		return 3;
	}
	return 0;
}

inline void showHelp() {
	cout << "webp2jpg -- Utility for converting WEBP files into JPEG format.\nUsage:\n webp2jpg -h\n webp2jpg [-r] <filepath> ..\nOptions:\n -h: show help\n -r: recursively traverse the following filepath\nExamples:\n webp2jpg -r . ./a.webp -r ./path\n";
	return;
}

void conv(path p) {
	Image i;
	if (p.extension().u8string() == ".webp") {
		cout << "Converting:" << p.u8string() << endl;//Comment this if you seek performance
		i.read(p.u8string());
		//cout<<"    " << f << " read, converting format..." << endl;
		i.magick("JPEG");
		p.replace_extension(".jpg");
		//cout << "    Converion success, writing to disk..." << endl;
		i.write(p.u8string());
		//cout << "Finished" << endl;
	}
	else {
		cout << "Warning: " << p.u8string() << " is not a .webp file, skipping.\n";
	}
}

void conv_recursive(path pa) {//TODO: add depth check
	path p;
	char confirm;
	cout << "Traversing:";
	cout << pa.u8string() << endl;
	stack<path> tasks;
	tasks.push(pa);
	directory_iterator end;
	Image i;
	while (!tasks.empty()) {
		p = tasks.top();
		tasks.pop();
		if (fs::is_directory(p)) {
			for (directory_iterator iter(p); iter != end; iter++) {
				tasks.push(iter->path());
			}
		}
		else {
			if (p.extension().u8string() == ".webp") {
				cout << "Converting:" << p.u8string() << endl;//Comment this if you seek performance
				i.read(p.u8string());
				//cout<<"    " << f << " read, converting format..." << endl;
				i.magick("JPEG");
				p.replace_extension(".jpg");
				//cout << "    Converion success, writing to disk..." << endl;
				i.write(p.u8string());
				//cout << "Finished" << endl;
			}
		}
	}
	cout << "Traversal complete: " << pa.u8string() << endl;
}
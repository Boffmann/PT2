#include <iostream>
#include <dirent.h>
#include <string>
#include <fstream>
#include <vector>
#if defined _WIN32
#include <direct.h>
#elif defined __GNUC__
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#endif

std::ofstream output;
bool fsize = false;
bool fnum = false;
bool file_w = false;
bool saveinformation = false;
bool flat = false;
std::string flat_dir;
typedef struct file_data {
	std::string ending;
	int size;
	int number;
	std::string files;
} file_data;
std::vector<file_data> file_list;
std::vector<std::string> name_list;

// Beware: this function only works when the directory is empty..
void removeDirectory(std::string dir)
{
#if defined _WIN32
    _rmdir(dir.data());
#elif defined __GNUC__
    rmdir(dir.data());
#endif
}

void createDirectory(std::string dir)
{
#if defined _WIN32
    _mkdir(dir.data());
#elif defined __GNUC__
    mkdir(dir.data(), 0777);
#endif
}

bool checkName(std::string name) {
	int suc = 0;
	for(unsigned int i = 0; i < name_list.size(); i++) {
		if(name.compare(name_list[i]) == 0) {
			suc = 1;
		} 
	}
	if(suc == 0) return true;
	else return false;
}

std::string underscorePath(std::string path) {
	std::string underscore = path;
	for(int i = 0; i < underscore.length(); i++) {
		if(underscore[i] == '/') {
			underscore[i] = '_';
		}
	}
	if(underscore[0] == '.') underscore = underscore.substr(1, underscore.length() - 1);
	while(underscore[0] == '_') {
		underscore = underscore.substr(1, underscore.length() - 1);
	}
	return underscore;
}


void traverseDirectory(std::string path)
{
	DIR *dir;
	struct dirent *ent;

	dir = opendir(path.c_str());
	
	if (dir != NULL)
	{
		while ((ent = readdir(dir)) != NULL)
		{
			std::string name = ent->d_name;
			if (ent->d_type == DT_DIR)
			{
				std::cout << "Dir: " << name << std::endl;
				//ToDo recursive
				if(name.compare(".") != 0 && name.compare("..") != 0)
					traverseDirectory("./" + name);
			}
			else
			{
				std::cout << "File: " << name << std::endl;
				struct stat fileinfo;
				std::string fullpath = path + "/" + name;
				std::cout << "Fullpath: " << fullpath << std::endl;
				if (!stat(fullpath.c_str(), &fileinfo))
				{
					std::cout << (unsigned int)fileinfo.st_size << " bytes" << std::endl;
					int tmp = name.find_last_of(".");
					std::string end;
					if(tmp >= 0 && tmp < name.length()) end = name.substr(tmp + 1, name.length() - tmp - 1);
					else end = " ";
					std::cout << name << std::endl;
					if(saveinformation) {
						int suc = 0;
						for(unsigned int i = 0; i < file_list.size(); i++) {
							if(end.compare(file_list[i].ending) == 0) {
								suc = 1;
								if(fsize) file_list[i].size += (unsigned int)(fileinfo.st_size % 1000);
								if(fnum) file_list[i].number += 1;
								if(file_w) {
									std::string tmp2 = file_list[i].files + "," + name;
									file_list[i].files = tmp2;
								}
							} 
						}
						if(suc == 0) {
							file_data tmp;
							tmp.ending = end;
							if(fsize) tmp.size = (unsigned int)(fileinfo.st_size % 1000);
							if(fnum) tmp.number = 1;
							if(file_w) tmp.files = "," + name;
							file_list.push_back(tmp);
						}
					} 
					if(flat) {
						std::string tmp_name = name;
						int count = 2;
						while(!checkName(tmp_name)) {
							tmp_name = name + std::to_string(count);
							count++;
						}
						tmp_name = underscorePath(path + "/") + tmp_name;
						std::string tmp_path = flat_dir + tmp_name;
						//std::cout << "path " << tmp_path << " name " << tmp_name << std::endl;
						std::ifstream src(name, std::ios::binary);
     					std::ofstream dst(tmp_path, std::ios::binary);
    			 		dst << src.rdbuf();
					}
				}
				else
				{
					std::cout << "(stat() failed for this file)\n" << std::endl;
				}
			}
		}
		closedir(dir);
	}
	else
	{
		std::cout << "Failed to read directory" << std::endl;
	}
}

void writetocsv() {
	output << "file ending";
	if(fsize) output << ",size";
	if(fnum) output << ",number of files";
	if(file_w) output << ",list of files";
	output << std::endl;
	for(unsigned int i = 0; i < file_list.size(); i++) {
		output << file_list[i].ending;;
		if(fsize) output << "," << file_list[i].size << "KB";
		if(fnum) output << "," << file_list[i].number;
		if(file_w) output << file_list[i].files;
		output << std::endl;
	}
}

int main(int argc, char * argv[])
{
	if (argc < 2)
	{
		std::cout << "not enough arguments - USAGE: dirinfo [DIR] -o [OUTPUT.csv] COLUMNS -flat [OUTPUTDIR]" << std::endl;
		std::cout << "possible COLUMNS are:" << std::endl;
		std::cout << "-fsize\t\t\tSummarized file size for files with same extension will be exported" << std::endl;
        std::cout << "-fnum\t\t\tSummarized number of files with same extension will be exported" << std::endl;
		std::cout << "-files\t\t\tRelative path of files with same extension will be exported" << std::endl;
		return -1;	// invalid number of parameters
	}
	std::string file;
	int directory_index[argc];
	for(int i = 0; i < argc; i++) {
		std::string tmp = argv[i];
		if(tmp.compare("-fsize") == 0) {
			fsize = true;
			directory_index[i] = 0;
		} else if(tmp.compare("-fnum") == 0) {
			fnum = true;
			directory_index[i] = 0;
		} else if(tmp.compare("-files") == 0) {
			file_w = true;
			directory_index[i] = 0;
		} else if(tmp.compare("-o") == 0) {
			file = argv[i+1];
			//createDirectory(file.substr(0,file.find_last_of("/", 0)));
			output.open(file);
			saveinformation = true;
			directory_index[i] = 0;
			directory_index[i+1] = 2;
		} else if(tmp.compare("-flat") == 0) {
			flat = true;
			directory_index[i] = 0;
			directory_index[i+1] = 2;
			flat_dir = argv[i+1];
			flat_dir = flat_dir + "/";
			createDirectory(flat_dir);
		} else if (directory_index[i] != 2) directory_index[i] = 1;
	}
	for(int i = 0; i < argc; i++) {
		if(directory_index[i] == 1)
			traverseDirectory(argv[i]);
	}
	if(saveinformation) writetocsv();
}
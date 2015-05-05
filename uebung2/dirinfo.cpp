#include <iostream>
#include <dirent.h>
#include <string>
#include <fstream>
#if defined _WIN32
#include <direct.h>
#elif defined __GNUC__
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#endif

std::ofstream output;
int fsize = 0;
int filesize = 0;
int fnum = 0;
int filepath = 0;
int saveinformation = 0;
typedef struct file_list {
	file_list* next;
	int size;
	int number;
	std::string path;
	std::string ending;
} file_list;
file_list* list;

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

file_list* lastelement(file_list* tmp_list) {
	while(tmp_list->next != NULL) {
		tmp_list = tmp_list->next;
	}	
	return tmp_list;
}

void addtolist(int size, std::string path, std::string ending) {
	file_list* add;
	if(fsize) add->size = size; else add->size = 0;
	if(fnum) add->number = 1; else add->number = 0;
	if(filepath) add->path = path;
	add->ending = ending;
	add->next = NULL;
	lastelement(list)->next = add;
}

void checklist(std::string ending, uint size, std::string path) {
	int suc = 0;
	file_list* tmp = list;
	while(tmp != NULL) {
		if(ending.compare(tmp->ending) == 0) {
			if(fsize) tmp->size += size;
			if(fnum) tmp->number++;
			if(filepath) tmp->path = path + "\n";
			suc = 1;
		}
		tmp = tmp->next;
	}
	if(!suc) addtolist(size, path, ending);
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
					if(saveinformation) {
						//std::string tmp = "";
						//if(tmp.compare(name.substr(name.find_last_of(".", 5) != 0) tmp = name.substr(name.find_last_of(".", 5);
						//checklist(tmp, (unsigned int)(fileinfo.st_size % 1000), path);
						//std::cout << name.substr(name.find_last_of(".", name.length() - name.find_last_of(".", 0))) << std::endl;
						std::string tmp;
						tmp = name.substr(0,1);
						if(tmp.compare(".") == 0) tmp = ""; else tmp = name.substr(name.find_last_of(".", name.length()));
						std::cout << name << " "<< name.find_last_of(".", name.length()) << " " << tmp << std::endl;

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
	file_list* tmp = list;
	while(tmp != NULL) {
		output << tmp->ending << "," << tmp->size << "KB," << tmp->number << "," << tmp->path << std::endl;
		tmp->next = tmp->next->next;
	}
}

int main(int argc, char * argv[])
{
	if (argc < 2)
	{
		std::cout << "not enough arguments - USAGE: dirinfo [DIR] -o [OUTPUT.csv] COLUMNS" << std::endl;
		std::cout << "possible COLUMNS are:" << std::endl;
		std::cout << "-fsize\t\t\tSummarized file size for files with same extension will be exported" << std::endl;
        std::cout << "-fnum\t\t\tSummarized number of files with same extension will be exported" << std::endl;
		std::cout << "-files\t\t\tRelative path of files with same extension will be exported" << std::endl;


		return -1;	// invalid number of parameters
	}
	std::string file;
	int directory_index[argc];
	for(int i = 0; i < argc; i++) {
		directory_index[i] = 1;
		std::string tmp = argv[i];
		if(tmp.compare("-fsize") == 0) {
			fsize = 1;
			directory_index[i] = 0;
		}

		if(tmp.compare("-fnum") == 0) {
			fnum = 1;
			directory_index[i] = 0;
		}
		if(tmp.compare("-files") == 0) {
			filepath = 1;
			directory_index[i] = 0;
		}
		if(tmp.compare("-o") == 0) {
			file = argv[i+1];
			//createDirectory(file.substr(0,file.find_last_of("/", 0)));
			output.open(file);
			saveinformation = 1;
			directory_index[i] = 0;
			directory_index[i+1] = 0;
		}
	}
	list = {NULL};
	for(int i = 0; i < argc; i++) {
		if(directory_index[i] == 1)
			traverseDirectory(argv[i]);
	}
	if(saveinformation) writetocsv();
}
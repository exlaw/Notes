#define _POSIX_SOURCE
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>
#include <dirent.h>
#include <sys/types.h>
#include <limits.h>
#include<sstream>
#include<vector>
#include<map>
#include <stdio.h>
#include <cstring>
#include <string>

using namespace std;

struct message{
    int lines;
    int words;
    int size;
}message;

map<char, bool > ls_param;
map<char, bool > wc_param;
char global_pwd[PATH_MAX];
string date[] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};

struct stat getInfo(string cwd, string name) {
    struct stat info{};
    string current = cwd + "/" + name;
    char file_pos[PATH_MAX];
    strcpy(file_pos, current.c_str());
    stat(file_pos, &info);
    return info;
}

void read(string filename){
    message.lines = 0, message.words = 0;

    char file_pos[PATH_MAX];
    strcpy(file_pos, filename.c_str());

    FILE *fp;
    fp = fopen(file_pos,"r");
    char ch;
    int flag = 0;
    while((ch = fgetc(fp))!=EOF){

        if(ch == '\n'){
            message.lines ++;	//行数加1 wc -l
        }
        if(ch == '\t' || ch == ' ' || ch == '\n'){
            flag = 0;		//计算单词数 wc -w
            continue;
        }
        else{
            if(flag == 0){
                message.words++;	//计算单词数 wc -w
                flag = 1;
            }
        }
    }
    message.size = getInfo(global_pwd,filename).st_size;	//文件字节大小 wc -c
    fclose(fp);
}

string build_authorize(struct stat info){
    string result = "";
    if (S_ISREG(info.st_mode))
        result += "-";
    else if (S_ISDIR(info.st_mode))
        result += 'd';
    else if (S_ISBLK(info.st_mode))
        result += 'b';
    else if (S_ISCHR(info.st_mode))
        result += 'c';
    else if (S_ISFIFO(info.st_mode))
        result += 'p';
    else if (S_ISLNK(info.st_mode))
        result += 'l';
    else if (S_ISSOCK(info.st_mode))
        result += 's';
    else {
        result += '?';
    }
    result += (info.st_mode & S_IRUSR) ? "r" : "-";
    result += (info.st_mode & S_IWUSR) ? "w" : "-";
    result += (info.st_mode & S_IXUSR) ? "x" : "-";
    result += (info.st_mode & S_IRGRP) ? "r" : "-";
    result += (info.st_mode & S_IWGRP) ? "w" : "-";
    result += (info.st_mode & S_IXGRP) ? "x" : "-";
    result += (info.st_mode & S_IROTH) ? "r" : "-";
    result += (info.st_mode & S_IWOTH) ? "w" : "-";
    result += (info.st_mode & S_IXOTH) ? "x" : "-";
    return result;
}

void print_file(vector<string> filenames, string cwd){
    vector<struct stat> stats;

    int total = 0;
    for (const auto &filename : filenames) {
        struct stat info = getInfo(cwd, filename);
        stats.push_back(info);
        total += info.st_blocks;
    }
    if(ls_param['l'] && !filenames.empty())
        cout << "total "<< total << endl;

    for(int i = 0; i < filenames.size() ; i++){

        struct stat info = stats[i];

        if(ls_param['i']){
            cout << info.st_ino << "\t";
        }

        if(ls_param['l']){
            struct tm *tmp_time = localtime(&info.st_ctime);
            cout << build_authorize(info);
            cout << "\t" << info.st_nlink << "\t" << info.st_uid << "\t" << info.st_gid << "\t" << info.st_size;
            cout << "\t" << date[tmp_time -> tm_mon] << "\t" << tmp_time -> tm_mday << "\t" <<tmp_time -> tm_hour << ":" << tmp_time -> tm_min<<"\t";
        }

        cout << filenames[i];
        if(i != filenames.size() -1) {
            if (ls_param['l']) cout << endl;
            else cout << "    ";
        }else cout << endl;
    }
}


vector<string> filter(vector<string> filenames){
    vector<string> vec;
    for(int i = 0; i < filenames.size(); i++){
        if(filenames[i][0] != '.'){
            vec.push_back(filenames[i]);
        }
    }
    return vec;
}

vector<string> getName(string path){
    vector<string> result;
    DIR* target = opendir(path.c_str());
    struct dirent * dp;
    while ((dp = readdir(target)) != NULL) {
        result.push_back(dp->d_name);
    }
    if(!ls_param['a']){
        result = filter(result);
    }
    return result;
}


void recursive_method(string cwd){
    vector <string> next, result;
    vector<string> names = getName(cwd);
    for(int i = 0; i < names.size() ; i++){
        struct stat info = getInfo(cwd, names[i]);
        if(S_ISDIR(info.st_mode) && names[i] != "." && names[i] !=".."){
            next.push_back(cwd + "/" + names[i]);
        }
        result.push_back(names[i]);
    }
    cout << cwd << endl;
    print_file(result, cwd);
    cout << endl;
    for(int i = 0; i < next.size() ;i++ ){
        recursive_method(next[i]);
    }
}


void ls(vector<string> params){
    ls_param['a'] = 0, ls_param['d'] = 0, ls_param['l'] =0,ls_param['R'] = 0,ls_param['i'] = 0;
    for(int i = 1; i< params.size(); i++){
        char *p = (char*)params[i].c_str();
        int j = 0;
        if(*p == '-') {
            while (*(p + j) != '\0') {
                ls_param[*(p+j)] = 1;
                j++;
            }
        }else{
            cout <<"ls " << " illegal param"<< endl;
            return;
        }
    }
    vector<string> vec;
    if(ls_param['d']){
        vec.push_back(".");
        print_file(vec,global_pwd);
    } else if(ls_param['R']){
        recursive_method(global_pwd);
    } else{
        vec = getName(global_pwd);
        print_file(vec, global_pwd);
    }
}


void wc(vector<string> params){
    wc_param['w'] = 0, wc_param['l'] = 0, wc_param['c'] =0;
    string fileName = "";
    for(int i = 1; i< params.size(); i++){
        char *p = (char*)params[i].c_str();
        int j = 0;
        if(*p == '-') {
            while (*(p + j) != '\0') {
                wc_param[*(p+j)] = 1;
                j++;
            }
        }else{
            fileName = params[i];
            if(i!=params.size() -1){
                cout << params[i+1] << "no such file " << endl;
            }
            break;
        }
    }
    read(fileName);

    bool all = false;
    if(!wc_param['l'] &&  !wc_param['w'] && !wc_param['c']){
        all = true;
    }

    if(wc_param['l'] || all)
        cout <<  message.lines << "\t";
    if(wc_param['w'] || all)
        cout << message.words << "\t" ;
    if(wc_param['c'] || all)
        cout << message.size << "\t";

    cout << fileName<<endl;
}

void handleCommand(string command){

    vector<string> vec;
    string result;
    stringstream input(command);
    while(input>>result)
        vec.push_back(result);

    if(vec[0] == "ls"){
        ls(vec);
    }else if(vec[0] == "wc"){
        wc(vec);
    }else{
        cout << vec[0] << " command not found!" << endl;
        return;
    }
}

int main() {
    if (getcwd(global_pwd, sizeof(global_pwd)) == nullptr) {
        perror("getcwd() error");
        return 1;
    }
    while(true){
        string command;
        getline(cin, command);

        command.erase(0,command.find_first_not_of(" "));
        command.erase(command.find_last_not_of(" ") + 1);

        if(command.length() > 0)
            handleCommand(command);
        if(command == "exit"){
            return 1;
        }
    }
}
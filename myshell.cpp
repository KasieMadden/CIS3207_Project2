#include "myshell.h"
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <sys/types.h>
#include <dirent.h>
#include <libgen.h>
#include <vector>
#include <regex>
#include <string>
#include <bits/stdc++.h>

using namespace std;

//extern char **environ;


void directory(string dirname);
void changeDir(char *dir);
void clear();
void environment(char *envp[]);
void echo(string);
void help();
void Pause();
void quit();
vector<string> parse(string in);
bool internalCMD(struct command *cmd);




//**************************************************************************MAIN()

int main(int argc, char *argv[],char *envp[]) {
    char temp[100];
    string user;
    vector<string> command;
    string input;

    while(true){
        cout << "myshell:~";
        user = (string)getcwd(temp, 1000);
        user = user + ">";

        getline(cin, input);
        command = parse(input);
    }




    // directory(".");
    //changeDir("..");
    // Pause();
    //clear();
    // environment(envp);
    // echo("hi hello how are you ");
    //help();
    // quit();






}// end of myshell()*******************************************************

vector<string> parse(string ss){
    vector <string> token;
    stringstream check1(ss);
    string inter;

    while(getline(check1, inter, ' ')){
        token.push_back(inter);
    }

    for (int i = 0; i < token.size(); i++){
        cout << token[i-1] << '\n';
    }

    return token;
}//end of parse

/**
void pipe(){

}


void redirection(){


}



void external(){

}

**/
//***********INTERNAL COMMANDS


//This functio will change  directories
// only takes in one arg, any thing else will be error
//using the chdir() to help with this. This is a system function
// used to change the current directory. When arg == 1
//it will get the prompted directory and then print.
//https://pubs.opengroup.org/onlinepubs/009695399/functions/opendir.html
void changeDir(char *dir){
    char i[100];
    if(dir == NULL){
        printf("%s\n", getcwd(i, 100) );
    }
    else if(chdir(dir) < 0){
        cerr<< "Directory not found."<< endl;
    }
    //printf("%s\n", getcwd(i, 100) );

}

//This function will show all the directories
//if the pointer to directory is not null it wlll read thought
//the directories print them and close. else error.
//https://www.tutorialspoint.com/How-can-I-get-the-list-of-files-in-a-directory-using-C-Cplusplus
void directory(string dirname){

    struct dirent *entry;
    DIR *dir;
    if ((dir = opendir(dirname.c_str())) == NULL) {
        perror ("Cannot open directory.");
        exit (1);
    }//end of if
    while((entry = readdir(dir))) {
        if (entry != NULL) {
            cout << entry->d_name << endl;
            entry = readdir(dir);
        }//end of if
        else{
            cout << "Error: Cannot read directory." << endl;
        }//end of else
    }//end of while
    closedir(dir);

}//end of dir


//This function is used to clear the screen
//Using regex to clear the screen
//https://www.geeksforgeeks.org/clear-console-c-language
void clear(){
    int i;
    for(i = 0;i < 200; i++) {
        cout << "\n";

    }
    cout<<"Screen has been cleared"<< '\n';
}//end of clr


//This function will list all the environment strings*
void environment(char *envp[]){
    int i;

    for(i=0; envp[i]!= NULL; i++){
        cout << envp[i] << endl;
    }

}//end of environ

void echo(string string){

    cout<< string<< '\n';
}
//help() runs though ifs  and prints what a command does
//https://www.w3schools.com/cpp/cpp_files.asp
void help(){
    string helpText;
    ifstream readFile("readme_doc.txt");

    while(getline(readFile, helpText)){
        cout<<helpText<<'\n';

    }//end of while
    readFile.close();

}//end of help


//will pause shell until user hits enter
void Pause(){
    cout << "\nPress Enter to Continue Program. ";
    cin.get();



}//end of pause


//will exit shell
void quit(){
    cout << "\nExiting myshell" << endl;
    exit(0);
}//end of quit

/**
// checks commands to see if they match the interal ones
//if true returns that matching function
bool internalCMD(char *cmd){
    const char *intcmd[] = { "cd", "dir", "clr", "envoron", "echo", "help", "pause", "quit"};

    if(strcmp(cmd->name, "cd") == 0){
        changeDir();
        return true;
    }
    else if(strcmp(cmd->name, "directory") == 0){
        directory();
        return true;
    }
    else if(strcmp(cmd->name, "clr") == 0){
        clear();
        return true;
    }
    else if(strcmp(cmd->name, "envoron") == 0){
        environment();
        return true;
    }
    else if(strcmp(cmd->name, "echo") == 0){
        echo(cmd->args);
        return true;
    }
    else if(strcmp(cmd->name, "help") == 0){
        help();
        return true;
    }
    else if(strcmp(cmd->name, "pause") == 0){
        pause();
        return true;
    }
    else if(strcmp(cmd->name, "quit") == 0){
        quit();
        return true;
    }
    else{
        return false;
    }
}//end of  internalCo
**/
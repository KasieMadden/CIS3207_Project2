#define _CRT_SECURE_NO_WARNINGS
#include "myshell.h"
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <libgen.h>
#include <string>

using namespace std;

extern char **environ;


void directory(char *dirname)
string prompt = "";

int main(int argc, char *argv[],char *envp[]) {

    directory("./");


}


//***********INTERNAL COMMANDS

//This functio will change  directories
// only takes in one arg, any thing else will be error
//using the chdir() to help with this. This is a system function
// used to change the current directory. When arg == 1
//it will get the prompted directory and then print.
//https://pubs.opengroup.org/onlinepubs/009695399/functions/opendir.html
void changeDir(char *dir){

    if(dir == NULL){
      cerr<< "Enter directory."<< std::endl;
    }
    else if(chdir(dir) == 0){
    }
    std::cerr<< "Directory not found."<< std::endl;


}

//This function is used to clear the screen
//Using regex to clear the screen
//https://www.geeksforgeeks.org/clear-console-c-language
void clear(){
    int i;
    for(i=0;i < 1000; i++) {
        system("clr");
    }

}//end of clr


//This function will show all the directories
//if the pointer to directory is not null it wlll read thought
//the directories print them and close. else error.
//https://www.tutorialspoint.com/How-can-I-get-the-list-of-files-in-a-directory-using-C-Cplusplus
void directory(char *dirname){

    struct dirent *entry;
    DIR *dir;
    if ((dir = opendir ("./")) == NULL) {
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

//This function will list all the environment strings*
void environment(char *envp[]){
    int i;

    for (i=0;i<sizeof(envp)-1;i++){
       cout << envp[i] << endl;
    }


}//end of environ

//This function will show what is typed after the command  followed by a new line.
//so while the args are not null will print string
void echo(char *string){


}//end of echo


//help() runs though ifs  and prints what a command does
//https://www.w3schools.com/cpp/cpp_files.asp
void help(char* cmd){

    ifstream readFile("readme_doc.txt");


}//end of help




//will pause shell until user hits enter
void Pause(){


}//end of pause





//will exit shell
int quit(){
    cout << "Exiting myshell" << endl;
    exit(0);
}//end of quit



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

void directory(string dirname);
void changeDir(const char *dir);
void clear();
void environment(char *envp[]);
void echo(string);
void help();
void Pause();
void quit();
vector<string> parse(string in);

//**************************************************************************MAIN()

int main(int argc, char *argv[],char *envp[]) {
   char temp[100];
    string user;
    vector<string> command;
    string input;

    while(true){
        //name of shell + cwd
        cout << "myshell:~";
        user = (string)getcwd(temp, 1000);
        user = user + ">";
        cout<<user;
        // user input
        getline(cin, input);
        command = parse(input);

        //call
       if(command[0].compare("cd")==0){
           changeDir(command[1].c_str());
           command.clear();
       }
       else if(command[0].compare("dir") ==0){
           directory(command[1].c_str());
           command.clear();
       }
        else if(command[0].compare("clr") ==0){
            clear();
            command.clear();
       }
        else if(command[0].compare("environ") ==0){
            environment(envp);
            command.clear();
       }
        else if(command[0].compare("echo") ==0){
            string t;
            for(int i = 1; i < command.size(); i++){
                t = t + command[i] + " " ;
            }
            echo(t);
            command.clear();
       }
        else if(command[0].compare("help") ==0){
            help();
            command.clear();
       }
        else if(command[0].compare("pause") ==0){
            Pause();
            command.clear();
       }
        else if(command[0].compare("quit") ==0){
            quit();
            command.clear();
       }

    }//end of while()




   // directory(".");
   //changeDir("..");
   // Pause();
    //clear();
   // environment(envp);
   // echo("hi hello how are you ");
    //help();
   // quit();



}// end of myshell()*******************************************************

//parser to pass the string though
//https://www.geeksforgeeks.org/tokenizing-a-string-cpp/
vector<string>parse(string ss){
    vector <string> token;
    stringstream check1(ss);
    string inter;

    while(getline(check1, inter, ' ')){
        token.push_back(inter);
    }

   // for (int i = 0; i < token.size(); i++){
   // cout << token[i-1] << '\n';
    //command}

    return token;
}//end of parse


void pipe(){

}

//link to code valut that  helps understand refirection
//https://youtu.be/5fnVr-zH-SE
void redirection(string input){
/**    pid =fork(input);




    if(){

    }
**/


}


void external(){

}


//***********INTERNAL COMMANDS
void path(){

}

//This functio will change  directories
// only takes in one arg, any thing else will be error
//using the chdir() to help with this. This is a system function
// used to change the current directory. When arg == 1
//it will get the prompted directory and then print.
//https://pubs.opengroup.org/onlinepubs/009695399/functions/opendir.html
void changeDir(const char *dir){
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

    cout<< string<< endl;
}
//help() runs though ifs  and prints what a command does
//https://www.w3schools.com/cpp/cpp_files.asp
void help(){
    string helpText;
    ifstream readFile("readme_doc.txt");

    while(getline(readFile, helpText)){
        cout<<helpText<<endl;

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

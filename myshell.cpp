#include "myshell.h"
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <sys/types.h>
#include <dirent.h>
#include <libgen.h>
#include <vector>
#include <string>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <bits/stdc++.h>

using namespace std;

//*********************************************************PROTOTYPES
void directory(string dirname);
void changeDir(const char *dir);
void clear();
void environment(char *envp[]);
void echo(string);
void help();
void Pause();
void quit();
vector<string> parse(string in);
void redirection(char *flag, string fileName);
vector<char *> convertS( vector<string> s);
//*************************************************************MAIN()

int main(int argc, char *argv[],char *envp[]) {
   char temp[100];
    string user;
    vector<string> command;
    string input;
    int in1 = dup(fileno(stdin));
    int out1 = dup(fileno(stdout) );


    while(true){
        //name of shell + cwd
        cout << "myshell:~";
        user = (string)getcwd(temp, 1000);
        user = user + ">";
        cout<<user;
        // user input
        getline(cin, input);
        if(input == ""){
            input = " ";
        }
        command = parse(input);
        vector<char *> car = convertS(command);
         char **command3 = &car[0];

         int status = execvp(command3[0], command3);

/**
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
            for(unsigned int i = 1; i < command.size(); i++){
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

       dup2(out1, 1);
       dup2(in1, 0);
    **/

    }//end of while()




   // directory(".");
   //changeDir("..");
   // Pause();
    //clear();
   // environment(envp);
   // echo("hi hello how are you ");
    //help();
   // quit();



}// end of main**********************************************




//parser to pass the string though
//https://www.geeksforgeeks.org/tokenizing-a-string-cpp/
vector<string>parse(string ss){
    vector <string> token;
    stringstream check1(ss);
    string inter;
    char a[1];
    string file;


    while(getline(check1, inter, ' ')){
     if(inter.compare("<") == 0||inter.compare(">")==0 || inter.compare(">>")==0){

        strcpy(a, inter.c_str());
       // printf("%s a", a);

        getline(check1, file, ' ');
       // printf("%s file", file);

        redirection(a, file);
     }
   /**  else if( inter.compare("&")==0){
        // call & handler
     }
     else if( inter.compare("|")==0){
        // call  for piping
     }**/
     else{
         token.push_back(inter);
     }

    }
    return token;
}//end of parse



//https://stackoverflow.com/questions/42493101/how-to-convert-a-vectorstring-to-a-vectorchar#comment72126556_42493563
//conver vector<string> to vector<char*
vector<char *> convertS( vector<string> s){
 vector<char *> temp(s.size(), nullptr);

 for(int i = 0; i< s.size(); i++){
     temp[i] = &s[i][0];
 }
temp.push_back(NULL);
return temp;
}

//call in and run external commands
void runexe(){

pid_t child;
child = fork();



}






void pipe(){
   /*
    int pfileDes[2];
    pid_t pid1;
    pid_t pid2;
*/


}//end of pipe

//https://youtu.be/5fnVr-zH-SE
void redirection(char *flag, string fileName){
    //printf("%s flag ", flag);
   // printf("%s flag ", fileName);

    if(strcmp(flag, ">")==0){
        int nstd= open(fileName.c_str(), O_WRONLY| O_CREAT, 0777);
        if(nstd < 0){
            cout<<" can't open file."<<endl;
        }
        if(dup2(nstd, STDOUT_FILENO)== -1){
            cout<<" dup2 fail."<<endl;
            }
        close(nstd);
    }//end of if >
    else if(strcmp(flag, "<")==0){
        int nstd= open(fileName.c_str(), O_RDONLY, 0777);
        if(nstd < 0){
            cout<<" can't open file."<<endl;
        }
        if(dup2(nstd, STDOUT_FILENO)== -1){
            cout<<" dup2 fail."<<endl;
        }
          close(nstd);
    }//end of if <
    else if(strcmp(flag, ">>")==0){
        int nstd= open(fileName.c_str(), O_WRONLY| O_CREAT|O_APPEND, 0777);
        if(nstd < 0){
            cout<<" can't open file."<<endl;
        }
        if(dup2(nstd, STDOUT_FILENO)== -1){
            cout<<" dup2 fail."<<endl;
        }
          close(nstd);

    }
}

//**************************************************INTERNAL COMMANDS
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
cout<<"Screen has been cleared"<< endl;
}//end of clr


//This function will list all the environment strings*
void environment(char *envp[]){
    int i;
    char curdir[100];
    string myshell;
    getcwd(curdir, 100);

    cout<< "shell=" <<curdir<< "/myshell"<<endl;
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
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
bool gchild = false;
//*********************************************************PROTOTYPES
void directory(string dirname);
void changeDir(const char *dir);
void clear1();
void environment(char *envp[]);
void echo(string);
void help();
void Pause();
void quit();
vector<string> parse(string in);
void redirectionIO(char *flag, string fileName);
vector<char *> convertS( vector<string> s);
void runexe(vector<string> ch);
void errorMes();
//*************************************************************MAIN()

int main(int argc, char *argv[],char *envp[]) {
    char temp[100];
    string user;
    vector<string> command;
    string input;
    int in1 = dup(STDIN_FILENO); //the o
    int out1 = dup(STDOUT_FILENO );


    //read file for batch
    ifstream readFile;
    if (argc == 2){
        readFile.open(argv[1]);
    }



    while(true){
        if(argc == 1){
            cout << "myshell:~";
            user = (string)getcwd(temp, 1000);
            user = user + ">";
            cout<<user;
            // user input
            getline(cin, input);
            if(input == ""){
                input = " ";
            }
        }// end of if argc1

        if(argc == 2){
            getline(readFile, input);
        }



        //redirection
        dup2(out1, STDOUT_FILENO);
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
            clear1();
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
        else{
            /**
             for(int i = 0; i < command.size(); i++){
                 cout<< command[i] << endl;
             }**/
            runexe(command);
            //command.clear();
        }


        dup2(in1, STDIN_FILENO);
        if(gchild){
            quit();
        }

    }//end of while()

}// end of main**********************************************

void errorMes(){
    char error_mess[30] = "An error has occurred\n";

    write(STDERR_FILENO,error_mess, strlen(error_mess));
}

//parser to pass the string though
//https://www.geeksforgeeks.org/tokenizing-a-string-cpp/
vector<string>parse(string ss){
    vector <string> token;
    stringstream check1(ss);
    string inter;
    char a[1];
    string file;


    while(getline(check1, inter, ' ')){
        if(inter.compare("<") == 0 || inter.compare(">")==0 || inter.compare(">>")==0){

            strcpy(a, inter.c_str());
            // printf("%s a", a);
            getline(check1, file, ' ');
            // printf("%s file", file);
            redirectionIO(a, file);
        }
        else if( inter.compare("&")==0){
            pid_t pid;
            pid= fork();

            if(pid < 0){
                cout<<"error"<<endl;
            }
            if(pid == 0){
                gchild = true;
            }

        }


            //https://code-vault.net/course/46qpfr4tkz:1603732431896/lesson/oxyoxbvnak:1603732432935
        else if(inter.compare("|")==0){
            int fileDes[2];
            pid_t pid;


            if(pipe(fileDes)== -1){
                cout<< "error"<<endl;
            }
            pid = fork();
            if(pid < 0){
                cout<<" error." << endl;
            }
            if(pid ==0){
                /** cout<<"this is a child"<<endl;
                 for(int i = 0; i <token.size(); i++ ){
                     cout << token[i] <<endl;
                 }**/
                dup2(fileDes[1], STDOUT_FILENO);
                close(fileDes[0]);
                close(fileDes[1]);
                gchild = true;
                return token;
            }

            wait(NULL);
            token.clear();
            dup2(fileDes[0], STDIN_FILENO);
            close(fileDes[0]);
            close(fileDes[1]);

        }
        else{
            token.push_back(inter);
        }

    }//end of while

    return token;
}//end of parse


//https://stackoverflow.com/questions/42493101/how-to-convert-a-vectorstring-to-a-vectorchar#comment72126556_42493563
//conver vector<string> to vector<char*
vector<char *> convertS( vector<string> s){
    vector<char *> temp(s.size(), nullptr);

    for(unsigned  int i = 0; i< s.size(); i++){
        temp[i] = &s[i][0];
    }
    temp.push_back(NULL);
    return temp;
}

//call in and run external commands
void runexe(vector<string> ch){
    pid_t child;
    child = fork();
    vector<char *> carconv;

    if ( child < 0 ){

        cout<<" Forking Error"<<endl;
    }
    else if(child == 0){
        carconv = convertS(ch);
        char **cmd = &carconv[0];
        if(execvp(cmd[0], cmd) ==-1){
            quit();
        }
    }
    else{
        wait(NULL);
    }
}// end of runexe()


//https://youtu.be/5fnVr-zH-SE
void redirectionIO(char *flag, string fileName){
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
void clear1(){
    int i;
    for(i = 0;i < 200; i++) {
        cout << "\n";

    }
    //cout<<"Screen has been cleared"<< endl;
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

//echo
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
    exit(0);
}//end of quit
Kasie Madden , tuk33450 - OS Project 2
Professor John Fiore
TA Blake Patterson

Overview:
The purpose of this assignment was is to generate a shell program that will allow
a user to execute several commands as listed in the README. The objective of this
assignment is to understand how child/parent processes work.

This program compiles from a makefile. It runs within a while loop which remains true
until the user quits the shell. This program consists of Built-in Commands,
Background Execution, I/O Redirection, Pipes, External Command Execution, and Batch files.

The shell looks for the amount of arguments. Within the main while loop, the program takes
in either one or two arguments (argc). If the input contains only one argc, it will run the command prompt and
allow the user to execute commands. If two argc, (./myshell batch.txt) will run the
commands from the batch.txt file.

Built in Commands:
Below is list of the built in commands and a description of how they are implemented within myshell.
cd - This is used to change directories. It is accomplished by using the getcdw() command.
dir - This will print the current working directory. It is accomplished by using the the readdir().
clr - This is used to clear the screen. This is done by printing a new line 200 times.
environ - This is used to display all the enviroments variable. This was accomplished by uing *envp[].
echo - This is used to output strings. It is accomplished by parsing the string and printing it.
pause - This will pause the program by calling by using cin.get(). This will wait for the user to press enter.
help - This will print the readme_doc but reading in the file and printing the contents.
quit - This will quit the program by using exit code 0.

Parsing: Parsiong the string is accomplished by creating a vector of strings. I did this by splitting the string
         and tokenizing it and using a space as the delimiter.

External Command Execution: To be able to call external comamnds I used execvp(). Because this function doesn't take string
                            vectors I had to creat a another function to convert the string vector to a char* vector. I
                            was then able to pass my pointer though the exevp().

I/O Redirection: The I/O redirection handles within the string parser, it runs a while loop that comapares the string to the
                 I/O flags <, > and  >>. When the loop catches a flag, it will pass though the passthough redirectionIO().
                 depending on what flag was caught in the parser it will either write and create, read only, or write,
                 create and append.

Pipes: The pipe handling in within the string parser. With in the loop it comapares the string to the pipe flag  | and
        open the pipe and check to make sure it is not == -1. If everything is fine it will then create a chid procees.
        It then checks to see if the child is < 0, if this is true then it would retrn an errror. If the child is
        == 0 it uses dup2() STDOUT_FILENO to to write over the child. To stop the process the file descriptor are closed
        and bool varriable that is global is set to true. It then returns the token. While the child process is happening
        I use the wait() then close the file descriptors.

Background Execution: For background execution I used the same logic as pipes. The  this piece of the code was not
                      implemented correctly and is stuck with in the child process. But for this to be implement correctly
                      there needs to be two shell processs, one to excute the command and another to  return the comamnd.
                      for the program to run in the background the chid must not do anything using the bool varriable to
                      break from the look. To allow both processes to run you don't wait in the parent and clear the argument
                      and letting it read the rest of the line.

Testing: For this assignment, I broke the coding up into sections and tested each section little by little.
         I first worked on the built in commands and tested to see if each command worked corrrectly. To do this, I
         called each function into the main() and added print statements in the funtions to understand what
         was happening within the function itself. To test the external commands I would run the shell and call
         different commands such as ls, cat or grep. These are basic functions that I am very familiar
         with and would be able to see immediately if they were called correctly. To test for I/O redirection I
         used my built in command echo to write a string to a file, or to append the file. I used the cat
         command to see if I was able to read from the file. To test piping I used ls -la | grep to how
         it ran. For the piping I had some difficulty getting it to work correctly. For this I kept getting stuck
         within the child process and then my IDE would crash on me. While testing for this, I used a lot of print
         statments to understad what was being forked, what the token was holding and how it was being redirected.
         To test the background functions I would run the ping command with a website. I didn't sucessfully implement
         this redirection. I believe my process is getting stuck with in the child and I did not know how to clear the
         parent. To test the batchfile I made use that I was reading in the file correctly and put a mix on internal commands
        and external commands into the file and ran the program.




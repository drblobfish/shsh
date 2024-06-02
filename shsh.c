#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

char **parse_line(size_t arg_num,char* line){
        char* start = line;
        for(;;line++){
                if (*line == ' '){
                        *line = '\0';
                        char** words = parse_line(arg_num+1,line+1);
                        words[arg_num] = start;
                        return words;
                }
                if (*line == '\0'){
                        char**words = (char**) calloc(arg_num+2,sizeof(char*));
                        words[arg_num+1] = '\0';
                        words[arg_num] = start;
                        return words;
                }
        }
}

void print_args(char** args){
        for(char** word = args;*word;word++){
                printf("%s\n",*word);
        }
}


int main(int argc, char** argv){
        char *line = NULL;
        size_t line_buffer_length;
        size_t line_length;
        char **args;
        int wstatus;
        // init

        while(1){
                printf("$ ");
                if ((line_length = getline(&line,&line_buffer_length,stdin)) == -1){
                        fprintf(stderr,"error getting line");
                }
                line[line_length-1] = '\0';
                
                args = parse_line(0,line);

                if (fork() == 0){
                        execvp(args[0],args);
                }
                else{
                        wait(&wstatus);
                }

        }

        // end
}

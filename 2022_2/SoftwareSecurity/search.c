#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int exploit();
int main(int argc, char** argv) {
    char command[256];
    int commandCheck;
    char temp[100];
    MYSQL_ROW row;
    MYSQL* conn = mysql_init(NULL);
    char* ret;

    //connect to database
    if (mysql_real_connect(conn, "localhost", "root", "1111", "Wiki", 0, NULL, 0) == NULL) {
        printf("Connection Failed\n");
        exit(1);
    }
    strcat(temp, argv[1]);
    ret = getenv("PWD");
    int z = 2;
    char blank[] = " ";
    while(true){
        if(argv[z] == NULL){
            break;
	}
	strcat(temp, blank);
	strcat(temp, argv[2]);
	z++;
    } 
    // construct query
    commandCheck = snprintf(command, sizeof command, "SELECT description FROM Information WHERE word = \'%s\';", temp);

    if (mysql_real_query(conn, command, 250) != 0) { //check information
        printf("Search is Empty\n");
	sprintf(temp, "You searched for the word: %s in %s", temp, ret);
	printf("%s\n", temp);
        return 0;
    }
    else {
        MYSQL_RES* result = mysql_store_result(conn);
        if (mysql_num_rows(result) != 0) {
            row = mysql_fetch_row(result);
            printf("%s\n", row[0]);
            mysql_close(conn);
        }
        else {
            mysql_close(conn);
            printf("No description exists for the word %s. To add a description, please edit the word description.\n", temp);
        }
        return 0;
    }
}

int exploit() {
    printf("[Team Ate] Dummy Function for PoC\n");
    return 0;
}

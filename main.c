#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

static int list_callback(void* data, int argc, char** argv, char** azColName) {
    static int index = 1;
    printf("%d. Name: %s, Height: %s, Info: %s\n",
        index++,
        //Ternary Operator
        argv[0] ? argv[0] : "NULL",
        argv[1] ? argv[1] : "NULL",
        argv[2] ? argv[2] : "NULL");
    return 0;
}

static int search_callback(void* data, int argc, char** argv, char** azColName) {
    if (argc > 0) {
        printf("Found user - Name: %s, Height: %s, Info: %s\n",
        //Ternary Operator
        argv[0] ? argv[0] : "NULL",
        argv[1] ? argv[1] : "NULL",
        argv[2] ? argv[2] : "NULL");
    }
    return 0;
}

int main() {
    sqlite3* db;
    char* err_msg = 0;
    int rc = sqlite3_open("people.db", &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    const char* sql = "CREATE TABLE IF NOT EXISTS People ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "name TEXT NOT NULL,"
        "height REAL,"
        "info TEXT);";
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    }

    int choice;
    printf("1. Add new user\n2. List users\n3. Search user by name\n4. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar();

    if (choice == 1) {
        char name[128];
        float height;
        char info[256];

        printf("Enter name: ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = 0;

        printf("Enter height (in meters): ");
        scanf("%f", &height);
        getchar();

        printf("Enter information: ");
        fgets(info, sizeof(info), stdin);
        info[strcspn(info, "\n")] = 0;

        char sql_insert[512];
        snprintf(sql_insert, sizeof(sql_insert),
            "INSERT INTO People (name, height, info) VALUES ('%s', %f, '%s');",
            name, height, info);

        rc = sqlite3_exec(db, sql_insert, 0, 0, &err_msg);

        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL insert error: %s\n", err_msg);
            sqlite3_free(err_msg);
        }
        else {
            printf("\033[32mData inserted successfully!\033[0m\n");
        }
    }
    else if (choice == 2) {
        const char* sql_select = "SELECT name, height, info FROM People;";
        rc = sqlite3_exec(db, sql_select, list_callback, 0, &err_msg);

        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL select error: %s\n", err_msg);
            sqlite3_free(err_msg);
        }
    }
    else if (choice == 3) {
        char search_name[128];
        printf("Enter name to search: ");
        fgets(search_name, sizeof(search_name), stdin);
        search_name[strcspn(search_name, "\n")] = 0;

        char sql_search[256];
        snprintf(sql_search, sizeof(sql_search),
            "SELECT name, height, info FROM People WHERE name = '%s';",
            search_name);

        rc = sqlite3_exec(db, sql_search, search_callback, 0, &err_msg);

        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL search error: %s\n", err_msg);
            sqlite3_free(err_msg);
        }
    }
    else if (choice == 4) {
        printf("Exiting...\n");
        sqlite3_close(db);
        return 0;
    }
    else {
        printf("Invalid choice!\n");
    }

    sqlite3_close(db);
    return 0;
}

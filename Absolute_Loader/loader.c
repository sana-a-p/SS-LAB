#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    FILE *fp, *fp1;
    int i, j, staddr1;
    char name[10], line[50], name1[10], staddr[10];

    printf("Enter Program Name: ");
    scanf("%s", name);

    fp = fopen("input.txt", "r");
    fp1 = fopen("output.txt", "w");

    if (!fp || !fp1) {
        printf("Error opening file.\n");
        return 1;
    }

    fscanf(fp, "%s", line);
    for (i = 2, j = 0; i < 8 && j < 6; i++, j++)
        name1[j] = line[i];
    name1[j] = '\0';

    printf("Name from Input File: %s\n", name1);

    if (strcmp(name, name1) == 0) {
        do {
            fscanf(fp, "%s", line);

            if (line[0] == 'T') {
                for (i = 2, j = 0; i < 8 && j < 6; i++, j++)
                    staddr[j] = line[i];
                staddr[j] = '\0';

                staddr1 = strtol(staddr, NULL, 16);
                i = 12;

                while (line[i] != '$' && line[i] != '\0') {
                    if (line[i] != '^') {
                        printf("%06X\t%c%c\n", staddr1, line[i], line[i + 1]);
                        fprintf(fp1, "%06X\t%c%c\n", staddr1, line[i], line[i + 1]);
                        staddr1++;
                        i += 2;
                    } else {
                        i++;
                    }
                }
            }
            else if (line[0] == 'E') {
                fclose(fp);
                fclose(fp1);
                exit(0);
            }
        } while (!feof(fp));
    } else {
        printf("Program name does not match.\n");
    }

    fclose(fp);
    fclose(fp1);
    return 0;
}

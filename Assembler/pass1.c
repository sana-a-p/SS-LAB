#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int start, locctr, length;
    char opcode[20], operand[20], label[20], code[20], mnemonic[20];

    FILE *fp_in = fopen("input.txt", "r");
    FILE *fp_op = fopen("optab.txt", "r");
    FILE *fp_sy = fopen("symtab.txt", "w");
    FILE *fp_ou = fopen("output.txt", "w");
    FILE *fp_len = fopen("length.txt", "w");

    if (!fp_in || !fp_op || !fp_sy || !fp_ou || !fp_len) {
        printf("Error opening file(s).\n");
        exit(1);
    }

    printf("\nLoc\tLabel\tOpcode\tOperand\n");
    printf("___\t____\t____\t____\n\n");
    fprintf(fp_ou, "Loc\tLabel\tOpcode\tOperand\n");
    fprintf(fp_ou, "___\t____\t____\t____\n");

    fscanf(fp_in, "%s\t%s\t%s", label, opcode, operand);

    if (strcmp(opcode, "START") == 0) {
        start = atoi(operand);
        locctr = start;
        fprintf(fp_ou, "%04X\t%s\t%s\t%s\n", locctr, label, opcode, operand);
        printf("%04X\t%s\t%s\t%s\n", locctr, label, opcode, operand);
        fscanf(fp_in, "%s\t%s\t%s", label, opcode, operand);
    } else {
        locctr = 0;
        start = 0;
    }

    while (strcmp(opcode, "END") != 0) {
        fprintf(fp_ou, "%04X\t", locctr);
        printf("%04X\t", locctr);

        if (label[0] != '*') {
            fprintf(fp_sy, "%s\t%04X\n", label, locctr);
        }

        int found = 0;
        fseek(fp_op, 0, SEEK_SET);
        while (fscanf(fp_op, "%s\t%s", mnemonic, code) != EOF) {
            if (strcmp(opcode, mnemonic) == 0) {
                locctr += 3;
                found = 1;
                break;
            }
        }
        if (!found) {
            if (strcmp(opcode, "WORD") == 0) {
                locctr += 3;
            } else if (strcmp(opcode, "RESW") == 0) {
                locctr += 3 * atoi(operand);
            } else if (strcmp(opcode, "RESB") == 0) {
                locctr += atoi(operand);
            } else if (strcmp(opcode, "BYTE") == 0) {
                if (operand[0] == 'C')
                    locctr += strlen(operand) - 3;
                else if (operand[0] == 'X')
                    locctr += (strlen(operand) - 3) / 2;
            }
        }

        fprintf(fp_ou, "%s\t%s\t%s\n", label, opcode, operand);
        printf("%s\t%s\t%s\n", label, opcode, operand);
        fscanf(fp_in, "%s\t%s\t%s", label, opcode, operand);
    }

    fprintf(fp_ou, "%04X\t%s\t%s\t%s\n", locctr, label, opcode, operand);
    printf("%04X\t%s\t%s\t%s\n", locctr, label, opcode, operand);

    length = locctr - start;
    fprintf(fp_len, "%d\n", length);
    printf("\nStarting address: %d\n", start);
    printf("Program length: %X\n\n", length);

    fclose(fp_len);
    fclose(fp_in);
    fclose(fp_op);
    fclose(fp_sy);
    fclose(fp_ou);

    return 0;
}

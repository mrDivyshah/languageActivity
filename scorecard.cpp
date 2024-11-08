#include <stdio.h>
#include <string.h>



int main() {
    char gameName[50] = "GameWord"; 
    int level = 25615565;
    int totalScore = 251;
    int currentPlayScore = 5622;

    const char* headers[] = { "Game Name", "Level", "Total Score", "Current Play Game Score" };
    int numCols = sizeof(headers) / sizeof(headers[0]);

    int widths[numCols];
    widths[0] = strlen(headers[0]) > strlen(gameName) ? strlen(headers[0]) : strlen(gameName);
    widths[1] = strlen(headers[1]) > snprintf(NULL, 0, "%d", level) ? strlen(headers[1]) : snprintf(NULL, 0, "%d", level);
    widths[2] = strlen(headers[2]) > snprintf(NULL, 0, "%d", totalScore) ? strlen(headers[2]) : snprintf(NULL, 0, "%d", totalScore);
    widths[3] = strlen(headers[3]) > snprintf(NULL, 0, "%d", currentPlayScore) ? strlen(headers[3]) : snprintf(NULL, 0, "%d", currentPlayScore);

    printLine('+', '+', '+', widths, numCols, '=');

    printf("|");
    for (int i = 0; i < numCols; i++) {
        printCenteredText(headers[i], widths[i]);
        printf("|");
    }
    printf("\n");

    printLine('+', '+', '+', widths, numCols, '-');

    printf("|");
    for (int i = 0; i < numCols; i++) {
        printf("%*s|", widths[i] + 2, ""); 
    }
    printf("\n");

    printf("|");
    printCenteredText(gameName, widths[0]);
    printf("|");
    char levelStr[10];
    sprintf(levelStr, "%d", level);
    printCenteredText(levelStr, widths[1]);
    printf("|");
    char totalScoreStr[10];
    sprintf(totalScoreStr, "%d", totalScore);
    printCenteredText(totalScoreStr, widths[2]);
    printf("|");
    char currentPlayScoreStr[10];
    sprintf(currentPlayScoreStr, "%d", currentPlayScore);
    printCenteredText(currentPlayScoreStr, widths[3]);
    printf("|\n");

    printf("|");
    for (int i = 0; i < numCols; i++) {
        printf("%*s|", widths[i] + 2, "");
    }
    printf("\n");

    printLine('+', '+', '+', widths, numCols, '=');

    return 0;
}

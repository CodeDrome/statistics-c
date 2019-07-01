
#include<stdio.h>
#include<stdlib.h>

#include"statistics.h"
#include"data.h"

int main(void)
{
    puts("-----------------");
    puts("| codedrome.com |");
    puts("| Statistics    |");
    puts("-----------------\n");

    double data138[138];
    double data9[9];
    double data10[10];
    double data11[11];
    double data12[12];

    statistics s;

    populate_data(data138, 138);
    puts("data138\n--------");
    calculate_statistics(data138, 138, &s);
    output_statistics(&s);

    populate_data(data9, 9);
    puts("\ndata9\n--------");
    calculate_statistics(data9, 9, &s);
    output_statistics(&s);

    populate_data(data10, 10);
    puts("\ndata10\n--------");
    calculate_statistics(data10, 10, &s);
    output_statistics(&s);

    populate_data(data11, 11);
    puts("\ndata11\n--------");
    calculate_statistics(data11, 11, &s);
    output_statistics(&s);

    populate_data(data12, 12);
    puts("\ndata12\n------");
    calculate_statistics(data12, 12, &s);
    output_statistics(&s);

    return EXIT_SUCCESS;
}

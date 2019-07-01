
#include<stdlib.h>
#include<stdbool.h>
#include<stdio.h>
#include<string.h>
#include<math.h>

#include"statistics.h"

//--------------------------------------------------------
// FUNCTION compare_doubles
//--------------------------------------------------------
static int compare_doubles(const void* a, const void* b)
{
    if(*(double*)a < *(double*)b)
        return -1;
    else if(*(double*)a > *(double*)b)
        return 1;
    else
        return 0;
}

//--------------------------------------------------------
// FUNCTION is_even
//--------------------------------------------------------
static bool is_even(int n)
{
    return n % 2 == 0;
}

// --------------------------------------------------------
// FUNCTION output_data
// --------------------------------------------------------
void output_data(double* data, int size)
{
    for(int i = 0; i < size; i++)
    {
        printf("%d\t%lf\n", i, data[i]);
    }
}

//--------------------------------------------------------
// FUNCTION output_statistics
//--------------------------------------------------------
void output_statistics(statistics* stats)
{
    printf("%-33s%12d\n", "Count", stats->count);
    printf("%-33s%12.4lf\n", "Total", stats->total);
    printf("%-33s%12.4lf\n", "Arithmetic Mean", stats->arithmetic_mean);
    printf("%-33s%12.4lf\n", "Minimum", stats->minimum);
    printf("%-33s%12.4lf\n", "Lower Quartile", stats->lower_quartile);
    printf("%-33s%12.4lf\n", "Median", stats->median);
    printf("%-33s%12.4lf\n", "Upper Quartile", stats->upper_quartile);
    printf("%-33s%12.4lf\n", "Maximum", stats->maximum);
    printf("%-33s%12.4lf\n", "Range", stats->range);
    printf("%-33s%12.4lf\n", "Inter-Quartile Range", stats->inter_quartile_range);
    printf("%-33s%12.4lf\n", "Standard Deviation of Population", stats->standard_deviation_population);
    printf("%-33s%12.4lf\n", "Standard Deviation of Sample", stats->standard_deviation_sample);
    printf("%-33s%12.4lf\n", "Variance of Population", stats->variance_population);
    printf("%-33s%12.4lf\n", "Variance of Sample", stats->variance_sample);
    printf("%-33s%12.4lf\n", "Skew", stats->skew);
}

//--------------------------------------------------------
// FUNCTION calculate_statistics
//--------------------------------------------------------
void calculate_statistics(double* data, int size, statistics* stats)
{
    double sum_of_squares = 0;
    int lower_quartile_index_1;
    int lower_quartile_index_2;

    // data needs to be sorted for median etc
    qsort(data, size, sizeof(double), compare_doubles);

    output_data(data, size);

    // count is just the size of the data set
    stats->count = size;

    // initialize total to 0, and then iterate data
    // calculating total and sum of squares
    stats->total = 0;
    for(int i = 0; i < size; i++)
    {
        stats->total += data[i];

        sum_of_squares += pow(data[i], 2);
    }

    // the arithmetic mean is simply the total divided by the count
    stats->arithmetic_mean = stats->total / stats->count;

    // method of calculating median and quartiles is different for odd and even count
    if(is_even(stats->count))
    {
        stats->median = (data[((stats->count) / 2) - 1] + data[stats->count / 2]) / 2;

        // even / even
        if(is_even(stats->count / 2))
        {
            lower_quartile_index_1 = (stats->count / 2) / 2;
            lower_quartile_index_2 = lower_quartile_index_1 - 1;

            stats->lower_quartile = (data[lower_quartile_index_1] + data[lower_quartile_index_2]) / 2;
            stats->upper_quartile = (data[stats->count - 1 - lower_quartile_index_1] + data[stats->count - 1 - lower_quartile_index_2]) / 2;
        }
        // even / odd
        else
        {
            lower_quartile_index_1 = ((stats->count / 2) - 1) / 2;

            stats->lower_quartile = data[lower_quartile_index_1];
            stats->upper_quartile = data[stats->count - 1 - lower_quartile_index_1];
        }
    }
    else
    {
        stats->median = data[((stats->count + 1) / 2) - 1];

        // odd / even
        if(is_even((stats->count - 1) / 2))
        {
            lower_quartile_index_1 = ((stats->count - 1) / 2) / 2;
            lower_quartile_index_2 = lower_quartile_index_1 - 1;

            stats->lower_quartile = (data[lower_quartile_index_1] + data[lower_quartile_index_2]) / 2;
            stats->upper_quartile = (data[stats->count - 1 - lower_quartile_index_1] + data[stats->count - 1 - lower_quartile_index_2]) / 2;
        }
        // odd / odd
        else
        {
            lower_quartile_index_1 = (((stats->count - 1) / 2) - 1) / 2;

            stats->lower_quartile = data[lower_quartile_index_1];
            stats->upper_quartile = data[stats->count - 1 - lower_quartile_index_1];
        }
    }

    // the data is sorted so the mimimum and maximum are the first and last values
    stats->minimum = data[0];
    stats->maximum = data[size - 1];

    // the range is difference between the minimum and the maximum
    stats->range = stats->maximum - stats->minimum;
    // and the inter-quartile range is the difference between the upper and lower quartiles
    stats->inter_quartile_range = stats->upper_quartile - stats->lower_quartile;

    // this is the formula for the POPULATION variance
    stats->variance_population = (sum_of_squares - ((pow(stats->total, 2)) / stats->count)) / stats->count;
    // the standard deviation is the square root of the variance
    stats->standard_deviation_population = sqrt(stats->variance_population);

    // the formula for the sample variance is slightly different in that it use count -1
    stats->variance_sample = (sum_of_squares - ((pow(stats->total, 2)) / stats->count)) / (stats->count - 1);
    // the sample standard deviation is the square root of the sample variance
    stats->standard_deviation_sample = sqrt(stats->variance_sample);

    // this is Pearson's second skewness coefficient, one of many measures of skewness
    stats->skew = (3.0 * (stats->arithmetic_mean - stats->median)) / stats->standard_deviation_population;
}

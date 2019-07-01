
// --------------------------------------------------------
// STRUCT statistics
// --------------------------------------------------------
typedef struct
{
    int count;
    double total;
    double arithmetic_mean;
    double minimum;
    double lower_quartile;
    double median;
    double upper_quartile;
    double maximum;
    double range;
    double inter_quartile_range;
    double standard_deviation_population;
    double standard_deviation_sample;
    double variance_population;
    double variance_sample;
    double skew;
} statistics;

// --------------------------------------------------------
// FUNCTION PROTOTYPES
// --------------------------------------------------------
void calculate_statistics(double* data, int size, statistics* stats);
void output_data(double* data, int size);
void output_statistics(statistics* stats);


#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double rand_range(double min, double max);

long long int number_of_tosses;

int num_threads;

int number_in_circle = 0;

// int number_in_circle_final;

double pi_estimate;


int main (int argc, char* argv[])
{
    printf("Enter Total #of tosses: \n");
    scanf("%lld", &number_of_tosses);

    num_threads = strtol(argv[1], NULL, 10);

    #pragma omp parallel reduction(+ : number_in_circle) num_threads(num_threads)
    {
        long my_rank = (long) num_threads;
        long long my_n = number_of_tosses/num_threads;
        long long my_first_toss = my_n * my_rank;
        long long my_last_toss = my_first_toss + my_n;

        srand ( time (0));

        for (int toss = my_first_toss; toss < my_last_toss; toss++) {
        double x = rand_range(-1.0, 1.0);
        // printf("x = %f \n", x);
        double y = rand_range(-1.0, 1.0);
        // printf("y = %f \n", y);
        double distance_squared = x*x + y*y;
        // printf("distance_squared = %f \n", distance_squared);
        
        if(distance_squared <= 1){
            number_in_circle++;
        }
    }
        
    }

    printf("Number of Circle = %d \n", number_in_circle);

    pi_estimate = 4 * number_in_circle / ((double) number_of_tosses);
    printf("pi = %f \n", pi_estimate);

    double estimate = number_in_circle / (double) number_of_tosses;
    printf("Estimate = %f \n", estimate);
    
    return 0;
}

// random double generator function
double rand_range(double min, double max){
    double range = (max - min); 
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

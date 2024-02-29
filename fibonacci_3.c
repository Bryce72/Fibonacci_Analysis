#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#define MAX 50010
#define PRINT_SINGLE 1
#define PRINT_ALL 2

typedef uint64_t ull;

// don't forget to allocate space for your table (multi-demi arrayof MAX x MAX)
static ull table[MAX]; //only one need linear space

void printSingleRow(ull *row, int size)
{
    for (int i = 0; i <= size; i++)
    {
        printf("%llu ", row[i]);
    }
    printf("\n");
}

ull fibonacci_dp(int n, ull *ops)
{
    if (n <= 1)
    {
        return n;
    }
    if (table[n] == 0) // if the element in array has not been calculated, it will go ahead and do so, via recursively... but this is memoization. it checks if it was calculated first
    {
        (*ops)++;
        table[n] = fibonacci_dp(n - 1, ops) + fibonacci_dp(n - 2, ops);
    }

    return table[n]; 
    
}

ull *fibonaccidp_full(int n, ull *ops)
{
    ull *row = calloc(n, sizeof(ull)); // changed this to calloc so it obliges by my function to check if element is 0
    for(int i = 0; i <= n; i++)
    {
        row[i] = fibonacci_dp(i, ops);
    }
    return row;
}

// changed this to fib
ull fibonacci_r(int n, ull *ops)
{
    if (n <= 0) 
    {
        return 0;
    }
    else if(n == 1)
    {
        return 1;
    }
    else
    {
        (*ops)++;
        return fibonacci_r(n - 1, ops) + fibonacci_r(n - 2, ops);
    }
}

ull *fibonaccir_full(int n, ull *ops)
{
    ull *row = malloc((sizeof(ull)) * n);
    for (int i = 0; i <= n; i++)
    {
        row[i] = fibonacci_r(i, ops);
    }
    return row;
}

ull *fibonacci_iterative(int n, ull *ops)
{
    ull *row = malloc((sizeof(ull)) * n);
    //set base numbers
    if(n >= 0)
    {
        row[0] = 0;
    }
    if(n >= 1)
    {
        row[1] = 1;
    }

    for(int i = 2; i <= n; i++)
    {
        row[i] = row[i-1] + row[i-2];
        (*ops)++;
    }
    return row;
}

double time_function(ull *(*func)(int, ull *), int n, ull *ops, bool print)
{
    // Setup timers
    struct timespec begin, end;
    // Get the time before we start
    clock_gettime(CLOCK_MONOTONIC, &begin);
    ull *row = func(n, ops);
    clock_gettime(CLOCK_MONOTONIC, &end);
    if (print)
    {
        printSingleRow(row, n);
    }
    free(row);
    return (end.tv_nsec - begin.tv_nsec) / 1000000000.0 +
           (end.tv_sec - begin.tv_sec);
}




void help()
{
    printf("./pascal.out N [Type] [Print Level]\n");
    printf("\tN is the number of rows in the pascal triangle, required.\n");
    printf("\t[Type] is 4 for dp and iterative only, 3 for all three, 2 for dynamic programming version, 1 for recursive version, 0 for iterative version, defaults to 3.\n");
    printf("\t[Print Level] leave blank for speed compare only, or print to print row\n");
}

int main(int argc, char *argv[])
{
    ull *row;
    if (argc < 2)
    {
        printf("at least two arguments needed!\n");
        help();
        return 1;
    }

    const int n = atoi(argv[1]);
    int type = 3;
    int print = 0;
    if (argc > 2)
    {
        type = atoi(argv[2]);
    }
    if (argc > 3)
    {
        print = true;
    }

    ull ops;
    double time;
    switch (type)
    {
    case 0:
        printf("iterative version\n");
        ops = 0;
        time = time_function(fibonacci_iterative, n, &ops, print);
        printf("time: %f(%llu)\n", time, ops);
        break;
    case 1:
        printf("recursive version\n");
        ops = 0;
        time = time_function(fibonaccir_full, n, &ops, print);
        printf("time: %f(%llu)\n", time, ops);
        break;
    case 2:
        printf("dynamic programming version\n");
        ops = 0;
        time = time_function(fibonaccidp_full, n, &ops, print);
        printf("time: %f(%llu)\n", time, ops);
        break;
    case 4:

        ops = 0;
        time = time_function(fibonacci_iterative, n, &ops, print);
        printf("%f,%llu,", time, ops);
        ops = 0;
        time = time_function(fibonaccidp_full, n, &ops, print);
        printf("%f,%llu,-,-", time, ops);

        break;
    default:

        ops = 0;
        time = time_function(fibonacci_iterative, n, &ops, print);
        printf("%f,%llu,", time, ops);
        
        ops = 0;
        time = time_function(fibonaccidp_full, n, &ops, print);
        printf("%f,%llu,", time, ops);
        
        ops = 0;
        time = time_function(fibonaccir_full, n, &ops, print);
        printf("%f,%llu", time, ops);

        break;
    }
}
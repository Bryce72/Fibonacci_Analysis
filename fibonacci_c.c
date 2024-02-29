//Writing my own fib functions because I could not understand the sample code

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

//CLocks_PER_SEC is a constant which is declared in <time.h>


typedef int (*timedFunc)(int, int*, int*);

//Dynamically porgrammed with memoization
int fib_memoization(int n, int *memo, int *ops)
{
    if(memo[n] != -1)
    {
        return memo[n];

    }
    if(n <= 1)
    {
        return n;
    }
    else
    {
        (*ops)++; // operarions should now only increment when new calculations are calculated
        memo[n] = fib_memoization(n - 1, memo, ops) + fib_memoization(n-2, memo, ops);
        return memo[n];
    }
}
void store_fib_dp(int n, int *sequence, int *ops)
{
    int *memo = (int *)malloc(n * sizeof(int));

    for(int i = 0; i < n; i++)
    {
        memo[i] = -1;
    }
    *ops = 0;
    for(int i = 0; i < n; i++)
    {
        sequence[i] = fib_memoization(i, memo, ops);
    }
    free (memo);
}

//iteration function
int fib_iteration(int n, int *sequence, int *ops)
{

    int amountofIterations = 0;
    int a = 0, b = 1, c, i;
    *ops = 0;
    if (n >= 1){
        sequence[0] = a; // first element is 0
    }

    if(n >= 2){
        sequence[1] = b; // second element is 0
    }
    for (i = 2; i < n; i++) {
        c = a + b;
        a = b;
        b = c;

        sequence[i] = b;
        (*ops)++;
    }
    return n; // dont really need to return this.. just had it programmed before to return operations.
}





//recursive functions
int fib_recursive(int n, int *ops)
{
    (*ops)++; //each time this function is used the ops will go up
    if (n <= 1){
        return n;
    }
    else
    {
        return fib_recursive(n - 1, ops) + fib_recursive(n - 2, ops);
    }

}
void store_fib_recursive(int n, int *sequence, int *ops){
    *ops = 0; //ops needs to start at 0
    if (n >= 1) 
    {
        sequence[0] = fib_recursive(0, ops);
    }
    if (n >= 2) 
    {
        sequence[1] = fib_recursive(1, ops);
    }
    for (int i = 2; i < n; i++) {
        sequence[i] = fib_recursive(i, ops);
    }
}


 



//print helper
void print(int *sequence, int n){
    for(int i = 0; i < n; i++){
        printf("%d", sequence[i]);
        if (i < n - 1){
            printf(", ");
        }
    }
    printf("\n");
}




double time_calc_iteration(timedFunc func, int n, int *sequence, int *ops)
{
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    //function to time
    func(n, sequence, ops);
    
    
    clock_gettime(CLOCK_MONOTONIC, &end);
    double times = (end.tv_nsec - start.tv_nsec) / 1000000000.0 + (end.tv_sec - start.tv_sec);
    return times;    
}



double time_calc_recursive(int(*func)(int, int*), int n, int* ops){
    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);

    //function to time
    func(n, ops);

    clock_gettime(CLOCK_MONOTONIC, &end);
    double times = (end.tv_nsec - start.tv_nsec) / 1000000000.0 + (end.tv_sec - start.tv_sec);
    return times;    
}

int main(){

    int n;
    int printer;
    int choice;
    int ops;

    // gather what the user wants
    printf("How long should the sequence be: \n");
    scanf("%d", &n);
    printf("Would you like the sequence to be printed? type 1 for yes, 0 for no: ");
    scanf("%d", &printer);
    printf("\nWould you like to use the Iterative function(1) or the Recursive function(2) or Dynammically Programmed Function(3)?\n OR why not print both iteration and dynamically programmed (4)\n");
    scanf("%d", &choice);    

    int sequence[n];
    

    if (choice == 1) {
        double times = time_calc_iteration(fib_iteration, n, sequence, &ops);
        if(printer == 1)
        {
            print(sequence, n);
        }
        printf("The time is takes for fibonacci, ITERATTION VERSION is: %.50f seconds\n", times);
    } 
    else if(choice ==2)
    {
        store_fib_recursive(n, sequence, &ops);
        double timeRecursive = time_calc_recursive(fib_recursive, n, &ops);
        if(printer == 1)
        {
            print(sequence, n);
        }
        printf("The time is takes for fibonacci, RECURSIVE VERSION is: %.50f seconds\n", timeRecursive);
        printf("The amount of operations is:  %d", ops);
    }
    else if(choice == 3)
    {
        struct timespec start, end;
        clock_gettime(CLOCK_MONOTONIC, &start);
        store_fib_dp(n, sequence, &ops);
        clock_gettime(CLOCK_MONOTONIC, &end);

        double timeDynamicallyP = (end.tv_nsec - start.tv_nsec) / 1000000000.0 + (end.tv_sec - start.tv_sec);
        if(printer == 1)
        {
            print(sequence, n);
        }
        printf("The time is takes for fibonacci, DYNAMMICALLY PROGRAMMED VERSION is: %.50f seconds\n", timeDynamicallyP);
        printf("The amount of operations is:  %d", ops);
    }
    else if(choice == 4){
        double times = time_calc_iteration(fib_iteration, n, sequence, &ops);
        struct timespec start, end;
        clock_gettime(CLOCK_MONOTONIC, &start);
        store_fib_dp(n, sequence, &ops);
        clock_gettime(CLOCK_MONOTONIC, &end);

        double timeDynamicallyP = (end.tv_nsec - start.tv_nsec) / 1000000000.0 + (end.tv_sec - start.tv_sec);
        printf("DP: %.50f seconds\n", timeDynamicallyP);
        printf("IT: %.50f seconds\n", times);


        if(timeDynamicallyP > times){
            printf("Iteration is faster then DP");
        }
        if(timeDynamicallyP < times){
            printf("Dynamically programmed is faster than iteration");
        }
    }
    else
    {
        printf("Wrong entry...");
    }
    return 0;
}




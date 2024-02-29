"""
Example file solving the fibonacci sequence using python.
Author: Bryce Dunlap
Semester: Spring 2024
"""
from enum import Enum
from functools import lru_cache
import argparse
from typing import Callable
import sys
import time

STACK_LIMIT = 50100
sys.setrecursionlimit(100000)

OPS = 0


class PascalType(Enum):
    ITERATIVE_DP_TOGETHER = 4
    ALL = 3
    DP = 2
    RECURSIVE = 1
    ITERATIVE = 0


#@lru_cache(maxsize=None)
fib_table = [-1] * STACK_LIMIT
def fibonaci_dp(n: int) -> int:
    global OPS
    if (n <= 0):
        return fib_table[0]
    elif(n==1):
        return fib_table[1]
    elif(fib_table[n] != -1):
        return fib_table[n]
    OPS += 1
    fib_table[n] = fibonaci_dp(n - 1) + fibonaci_dp(n - 2)
    return fib_table[n]





def recursive_fiboncai(n: int):
    global OPS
    if (n <= 0):
        return 0
    elif(n == 1):
        return 1
    else:
        OPS += 1
        return recursive_fiboncai(n - 1) + recursive_fiboncai(n - 2)



def iterative_fibonacci(n: int) -> list:
    """
    Generates the nth row in the fibonacci sequence based on the
    method requested

    Args:
        n: the row to generate
        print_it:  print out all rows as being generated
        version:  the type/method of generation

    Returns:
        array of fib sequence to the n
    """
    global OPS
    arr = []

    if(n >= 1):
        arr.append(0)
    if(n >= 2):
        arr.append(1)
    for i in range(2,n):
        OPS += 1
        arr.append(arr[i - 1] + arr[i - 2])
    return arr







def run_and_time(func: Callable, n: int, print_it: bool = False):
    """
    Runs the pascal triangle generation, prints the row if requested
    and returns both the time and OPS used.

    Args:
        n (int): _description_
        algo (PascalType): _description_
        print (bool): _description_
    """
    global OPS
    OPS = 0  # reset it
    start = time.perf_counter()
    result = func(n)
    end = time.perf_counter()
    if print_it:
        print(result)
    return end - start, OPS


def main(n: int, algo: PascalType, print_it: bool):

    

    if algo == PascalType.RECURSIVE:
        print("Recursive Version")
        time, ops = run_and_time(recursive_fiboncai, n, print_it)
        print(f"Time: {time}({ops})")
    elif algo == PascalType.DP:
        print("Dynamic Programming Version")
        time, ops = run_and_time(fibonaci_dp, n, print_it)
        print(f"Time: {time}({ops})")
    elif algo == PascalType.ITERATIVE_DP_TOGETHER:
        time, ops = run_and_time(iterative_fibonacci, n)
        time2, ops2 = run_and_time(fibonaci_dp, n)
        print(f"{time:0.6f},{ops},{time2:0.6f},{ops2},-,-")
    elif algo == PascalType.ALL:
        time, ops = run_and_time(iterative_fibonacci, n)
        time2, ops2 = run_and_time(fibonaci_dp, n)
        time3, ops3 = run_and_time(recursive_fiboncai, n)
        print(f"{time:0.6f},{ops},{time2:0.6f},{ops2},{time3:0.6f},{ops3}")
    else:
        print("Iterative Version")
        time, ops = run_and_time(iterative_fibonacci, n, print_it)
        print(f"Time: {time}({ops})")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Pascal Triangle")
    parser.add_argument("n", type=int, help="The nth row to generate")
    parser.add_argument(
        "--print", action="store_true", default=False, help="Print the nth row"
    )
    parser.add_argument(
        "algo",
        type=int,
        choices=[0, 1, 2, 3, 4],
        default=PascalType.ITERATIVE.value,
        help="The type of algorithm to use: 0 = iterative, 1 = recursive, 2 = dp, 3 = all, 4 = iterative and dp together",
    )

    args = parser.parse_args()
    algo = PascalType(args.algo)
    main(args.n, algo, args.print)
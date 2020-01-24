# Assignment 1 - Optimizations


## Getting started


### clock_gettime()

#### Usage

```c
# include<time.h>
int clock_gettime(clockid_t clk_id, struct timespec *tp);
```

#### What it does
The functions clock_gettime() retrieves the time of the specified clock clk_id. 

#### How it works

- The function fills in a structure containing two fields: a seconds and nanoseconds count of the time since the Epoch (00:00 1 January, 1970 UTC). 

- We must include the *time.h* header file to use this function.

- The **structure** (pun unintended) of `struct timespec` is as follows:

```c
struct timespec {
        time_t   tv_sec;        /* seconds */
        long     tv_nsec;       /* nanoseconds */
};
```
- The second parameter *clk_id* is the identifier of the particular clock on which to act. A clock may be system-wide and hence visible for all processes, or per-process if it measures time only within a single process.

    There are multitude of clocks and we can specify which one to use:
    - CLOCK_REALTIME
    - CLOCK_MONOTONIC
    - CLOCK_PROCESS_CPUTIME_ID
    - CLOCK_THREAD_CPUTIME_ID

#### How we used it

This function can be used to measure the runtime of our programs.
For measuring elapsed time, **CLOCK_MONOTONIC** is recommended. So our code looks as follows:
```c
    clock_gettime(CLOCK_MONOTONIC, &start);
    //function call here
    clock_gettime(CLOCK_MONOTONIC, &end);
```

#### Fun facts!

It is a successor to *gettimeoftheday* system call but with *higher precision* and the ability to request *specific clocks*. 

## Matrix Multiplication

We use matrices of size p * q and  q * r with MAXSIZE being 1000 * 1000.


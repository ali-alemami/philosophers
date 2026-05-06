*This project has been created as part of the 42 curriculum by aalemami.*

## Description

Philosophers is a concurrency project implementing the classic **Dining Philosophers Problem**. N philosophers sit at a round table with a bowl of spaghetti in the middle. Each philosopher has one fork, and needs **two forks** to eat. Philosophers cycle between three states: **eating**, **sleeping**, and **thinking**. The simulation ends either when a philosopher dies of starvation, or when all philosophers have eaten a required number of times.

The goal is to manage philosopher threads without data races, deadlocks, or starvation, using **mutexes** to protect shared resources (forks).

## Instructions

**Compilation:**
```bash
cd philo
make
```

**Usage:**
```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

| Argument | Description |
|---|---|
| `number_of_philosophers` | Number of philosophers (and forks) at the table |
| `time_to_die` (ms) | Time before a philosopher dies if they haven't started eating |
| `time_to_eat` (ms) | Time it takes to eat (holds two forks during this) |
| `time_to_sleep` (ms) | Time spent sleeping after eating |
| `number_of_times_each_philosopher_must_eat` | Optional — simulation stops when all philosophers reach this count |

**Examples:**
```bash
./philo 5 800 200 200          # 5 philosophers, should not die
./philo 1 800 200 200          # 1 philosopher, dies (only one fork available)
./philo 4 410 200 200          # tight timing, should not die
./philo 5 800 200 200 7        # stops after each philosopher eats 7 times
./philo 5 100 200 200          # time_to_die too short, philosopher dies
```

## Resources

- [POSIX Threads Programming — Lawrence Livermore National Laboratory](https://hpc-tutorials.llnl.gov/posix/) — comprehensive pthreads reference covering thread creation, joining, and mutex usage
- [The Dining Philosophers Problem — Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem) — problem background, classic solutions, and deadlock analysis
- [pthread_mutex_lock(3) — Linux man page](https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html)
- [gettimeofday(2) — Linux man page](https://man7.org/linux/man-pages/man2/gettimeofday.2.html)
- [Multithreading in C — GeeksForGeeks](https://www.geeksforgeeks.org/c/multithreading-in-c/)

**AI usage:**
Claude (claude.ai) was used in the following parts of the project:
- Explaining `pthread` functions (`pthread_create`, `pthread_join`, `pthread_detach`) and their expected behavior
- Clarifying mutex initialization and cleanup patterns (`pthread_mutex_init`, `pthread_mutex_destroy`)
- Understanding precise sleep implementation using `gettimeofday` to avoid drift
- Discussing data race scenarios and how to reason about shared state between threads

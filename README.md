# Philosophers

Work in process. This project is about learning the basics of threading in a process.

Started working on this with my MacOS on Saturday 25th of Jan.
- Makefile
- header
- getting familiar with the assignment and learning about threads and mutexes.

Going to continue working with Linux on 1st of Feb and do possible necessary 
adjustments then.

PS. ISNT ACTUALLY LIBFT AUTHORIZED SO GONNA REMOVE LIBFT LATER

PPS. Just started to play with gettimeofday so nothing makes sense yet.

---------------------------------------------------------------
5th of February (Was supposed to continue on 1st, but got sick)
---------------------------------------------------------------

- Continued working on the project after going on holiday and being sick
- mostly trying to get familiar with the requirements again
- totally misusing gettimeofday now
- Removed Libft cause it's not allowed
- Scrapped up new ft_atoi_err, because my older custom ft_atoi was way
too liberal in terms of characters it allowed in. 
- The struct is just a doodle, not gonna utilize it this way

----------------------------------------------------------------
6th of February
----------------------------------------------------------------

- Finally started to search for the most simple and efficient
data struct, and decided to use (atleast) two structs: t_data data
and t_philo philo.
- t_data: general data struct that contains the info that's shared between all the philos.
Started to initialize it today and it's done for now.
- t_philo: individual struct for every philo. Didn't start to initialize
it yet, and there might be more mutexes incoming (like a mutex for printing)
as my comprehension evolves and the needs are identified.
- It makes/compiles.
----------------------------------------------------------------
7th of February
----------------------------------------------------------------

New functions:
- free_data(), which succesfully removes any memory allocated in
data struct and destroys fork mutexes.
- init_philos(), which initializes t_philo struct and assigns all values possible at the moment,
and creates pthreads (so the routine starts running there).

- I also sketched up monitoring(), thinking() and sleeping(), to see if the program is running
at all at this point. It runs succesfully.

Next:
- I need to figure out whether I need more mutex lock to avoid printing the thinking part too oten OR
is the upcoming eating() function with it's fork locks taking care of it for me. Will the philos wait
patiently until the fork is unlocked...?
- I need to figure out logic so that philos will avoid dying; the even numbers could start eating first... maybe...?
OR is it necessary...?

----------------------------------------------------------------
8th of February 1st commit (huge progression fast without AI)
----------------------------------------------------------------

New functions:
- eating(): I sketched up this first version in 10 minutes and I'm proud of it - there's just something about a
fresh morning brain.
- I also added checks to the beginning of every action functions beginning to check, whether philo_died flag
is true, or whether too much time has passed since the last meal, so the while loop inside the routine doesn't
get delays until monitoring is checked again.
- The program works on a basic level, philos think (only if they aren't already thinking), sleep and die when they starve
that is.

Need to do:
- further testing
- to make that nothing happens after a philo has died
- separate last_meal checks and meals_eaten checks to a separate function to save space
- see whether is leaks - I've heard there can be difficulties running philos with valgrind

----------------------------------------------------------------
8th of February 2nd commit
----------------------------------------------------------------

PROBLEM:

./philo 2 50 500 50
0 1 is thinking
1 1 has taken a fork
1 1 is eating
0 2 is thinking
501 1 is sleeping.
501 2 died

Should behave like:
./philo 2 50 500 50
0 1 is thinking
1 1 has taken a fork
1 1 is eating
0 2 is thinking
50 2 died

Right now my program and monitoring logic is in trouble, because philo 2 try's to unlock a fork mutex and waits
until nro1 unlocks the fork - by the time it has happened it's been 500ms, because it's the time to eat. But nro 2 should die
while waiting for the fork. We can't use pthread_mutex_trylock, and unlocking wait's until it succeeds. So I need to
change my logic.

----------------------------------------------------------------
10th of February
----------------------------------------------------------------

Don't want to jinx anything but I seem to be on fire!

Ran philo today for the first time with:
valgrind --tool=helgrind 
Which checks for possible data races and reports them as errors.

Managed to get from over 30 errors to 0 errors when running with
100 philos. To achieve this:
- I added one more mutex called "lock".
- I use this lock whenever I'm reading or writing into a struct that's also possibly inspected by other threads.

- In addition to this I needed to exted the usage of printf being protected by the same pthread_mutex_t print that is guarding the "xx philo x died" printing.

There were also some bigger logical issues with my program. I previously had the monitoring inside the thread's routine loop, but now it's in the main and it's tracking philos' deaths. I need to still add the meals_eaten into the conditions, so the simumlation/routine stops if all the philos are full.

----------------------------------------------------------------
11th of February
----------------------------------------------------------------

- Implemented the logic for checking philos' fullness and ending simulation when complete fullness is achieved.
- Starting to split some bigger functions into smaller ones and also putting sleep functions into ft_sleeps that sleeps in bits and
checks whether we should end running the simulation.
- Thinking of making a custom print function aswell.
----------------------------------------------------------------
					TO DO
----------------------------------------------------------------

 [✔️] Argument value check for 0 - not running the program when set for time of death, philos, or num_must_eat
 
 [❌] ft_sleep
 
 [✔️] split bigger functions
 
 [✔️] data races
 
 [✔️] **philo -> *philo (no point in having a double array anymore)

- It's Norminetted, but header file needs the rest of the definitions/explanations for functions.
- Doesnt leak or leave data races
- 95% done, will probably evaluate tomorrow?

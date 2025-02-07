# Philosophers

This project is about learning the basics of threading in a process.

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
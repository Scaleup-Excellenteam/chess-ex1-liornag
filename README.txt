The algorithm send every time one piece to the pool
to be checked.
Wait for the all threads to finish to calculate the
best moves.
Take the first move of the best moves and run it.

The results are (for 8 moves):
For 2 threads, it took: 7331 microseconds
For 4 threads, it took: 5502 microseconds
For 8 threads, it took: 6109 microseconds

We can see that 4 threads are better than 2
but 8 are not better than 4.
This is because there is overhead of creating threads.

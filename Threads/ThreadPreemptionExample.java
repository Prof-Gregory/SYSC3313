/**
 * ThreadPreemptionExample.java - this application demonstrates how a higher
 * priority thread will preempt a lower priority thread.
 */
class ThreadPreemptionExample
{
    public static void main(String[] args) {

        /* Create a factorial thread and a fibonacci thread with lower
         * priority than the factorial thread.
         * In order to ensure that none of these threads run until this thread
         * has terminated, the priority of the two threads is set lower than
         * this thread's priority (Thread.NORM_PRIORITY).
         * Both threads write to System.out, so that you can see when the
         * higher priority thread preempts the lower priority one.
         */

        Thread factorialThread = new Thread(
                 new Factorial(), "Factorial calculator");
        factorialThread.setPriority(Thread.NORM_PRIORITY - 1);
        System.out.print("Created: " + factorialThread + '\n');

        Thread fibonacciThread = new Thread(
                 new Fibonacci(), "Fibonacci calculator");
        fibonacciThread.setPriority(Thread.NORM_PRIORITY - 2);
        System.out.print("Created: " + fibonacciThread + '\n');

        System.out.print("Starting threads\n");
        factorialThread.start();
        fibonacciThread.start();
    }
}

/**
 * This thread calculates 0! through 20!, where
 *  0! = 1
 *  n! = n * (n-1)!, n > 0
 */
class Factorial implements Runnable
{
    public void run() {
        // 0! = 1
        long factorial = 1;
        System.out.print(Thread.currentThread() + ": 0! = " + factorial + '\n');
        for (int n = 1; n <= 20; n++) {
            // Sleep for 2 ms before calculating n!
            try {
                Thread.sleep(2);
            } catch (InterruptedException e) {}

            // n! = n * (n-1)!
            factorial = n * factorial;
            System.out.print(Thread.currentThread() + ": "
                              + n + "! = " + factorial + '\n');
        }
        System.out.print(Thread.currentThread() + " finished\n");
    }
}

/**
 * This thread calculates fib(1) through fib(10), where
 * fib(1) = 1
 * fib(2) = 1
 * fib(n) = fib(n-1) + fib(n-2), n >2
 */
class Fibonacci implements Runnable
{
    public void run() {
        // fib(1) = 1
        long firstFib = 1;
        System.out.print(Thread.currentThread() +
                          ": fib(1) = " + firstFib + '\n');

        long secondFib = 1;
        System.out.print(Thread.currentThread() +
                          ": fib(2) = " + secondFib + '\n');

        for (int n = 3; n <= 10; n++) {
                    
            // fib(n) = fib(n-1) + fib(n-2)
            long fibN = firstFib + secondFib;
            System.out.print(Thread.currentThread()  +
                              ": fib("+ n + ") = " + fibN + '\n');
            secondFib = firstFib;
            firstFib = fibN;
        }
        System.out.print(Thread.currentThread() + " finished\n");
    }
}


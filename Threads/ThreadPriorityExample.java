/**
 * ThreadPriorityExample.java - this application demonstrates how to create
 * threads with different scheduling priorities.
 */
class ThreadPriorityExample
{
    public static void main(String[] args) {

        /* Create three threads, each with a different priority.
         * To ensure that none of these threads run until this thread has sent
         * the start() message to all of them and terminated, the priority of
         * all three threads is set lower than this thread's priority
         * (Thread.NORM_PRIORITY).
         * These threads write to System.out, so that you can see how a higher
         * priority thread that does not relinquish the processor will starve
         * lower priority threads.
         */

        Thread factorialThread = new Thread(
                 new Factorial(), "Factorial calculator");
        factorialThread.setPriority(Thread.NORM_PRIORITY - 1);
        System.out.print("Created: " + factorialThread + '\n');

        Thread secondFactorialThread = new Thread(
                 new Factorial(), "Second factorial calculator");
        secondFactorialThread.setPriority(Thread.NORM_PRIORITY - 3);
        System.out.print("Created: " + secondFactorialThread + '\n');

        Thread fibonacciThread = new Thread(
                 new Fibonacci(), "Fibonacci calculator");
        fibonacciThread.setPriority(Thread.NORM_PRIORITY - 2);
        System.out.print("Created: " + fibonacciThread + '\n');

        System.out.print("Starting threads\n");
        factorialThread.start();
        secondFactorialThread.start();
        fibonacciThread.start();
    }
}

/**
 * This thread calculates 0! through 10!, where
 *  0! = 1
 *  n! = n * (n-1)!, n > 0
 */
class Factorial implements Runnable
{
    public void run() {
        // 0! = 1
        long factorial = 1;
        System.out.print(Thread.currentThread() +
                          ": 0! = " + factorial + '\n');
        for (int n = 1; n <= 10; n++) {

            // n! = n * (n-1)!
            factorial = n * factorial;
            System.out.print(Thread.currentThread() +
                              ": " + n + "! = " + factorial + '\n');
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

        // fib(2) = 1
        long secondFib = 1;
        System.out.print(Thread.currentThread() +
                          ": fib(2) = " + secondFib + '\n');

        for (int n = 3; n <= 10; n++) {

            // fib(n) = fib(n-1) + fib(n-2)
            long fibN = firstFib + secondFib;
            System.out.print(Thread.currentThread() +
                              ": fib(" + n + ") = " + fibN + '\n');
            secondFib = firstFib;
            firstFib = fibN;
        }
        System.out.print(Thread.currentThread() + " finished\n");
    }
}


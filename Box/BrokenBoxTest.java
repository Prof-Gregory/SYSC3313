/** BoxTest.java
 *
 * Testing Box by creating a producer and consumer.
 * 
 * @author Lynn Marshall
 * @version 1.00
 * 
 */

public class BrokenBoxTest
{
    public static void main(String[] args)
    {
        Thread producer1, producer2, producer3, consumer1, consumer2, consumer3;
        BrokenBox box;

        box = new BrokenBox(); // shared by producer and consumer

        // Create the producer and consumer threads, passing each thread
        // a reference to the shared BoundedBuffer object.
        producer1 = new Thread(new Producer(box),"Producer1");
        consumer1 = new Thread(new Consumer(box),"Consumer1");
        producer1.start();
        consumer1.start();
        producer2 = new Thread(new Producer(box),"Producer2");
        consumer2 = new Thread(new Consumer(box),"Consumer2");
        producer2.start();
        consumer2.start();
        producer3 = new Thread(new Producer(box),"Producer3");
        consumer3 = new Thread(new Consumer(box),"Consumer3");
        producer3.start();
        consumer3.start();
    }
}

/**
 * Producer is the class for the producer thread.
 */
class Producer implements Runnable
{ 
    private BrokenBox box;

    public Producer(BrokenBox box)
    {
        this.box = box;
    }

    public void run()
    {
        for(int i = 0; i < 20; i++) {
            Integer item = new Integer(i);
            System.out.println(Thread.currentThread().getName() + " produced " + item);
            while ( !box.put(item) ) {
		try {
		    Thread.sleep(500);
		} catch (InterruptedException e) {}
	    } 
	    System.out.println(Thread.currentThread().getName() + " put in box " + item);
	    try {
		Thread.sleep(500);
	    } catch (InterruptedException e) {}
        }
    }
}

/**
 * Consumer is the class for the consumer thread.
 */
class Consumer implements Runnable
{
    private BrokenBox box;
    
    public Consumer(BrokenBox box)
    {
        this.box = box;
    }

    public void run()
    {
        for(int i = 0; i < 10; i++) {
            System.out.println(Thread.currentThread().getName() + " ready to consume.");
            Object item = box.get();
            System.out.println(Thread.currentThread().getName() + " consumed " + item);
            try {
                Thread.sleep(100); // change to 100 to see difference
            } catch (InterruptedException e) {}
        }
    }
}


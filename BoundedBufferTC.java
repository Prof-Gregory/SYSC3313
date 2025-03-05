/**
 * BoundedBufferTC.java
 * 
 * Thread compatible version of BoundedBuffer
 *
 * @author Lynn Marshall
 * @version May 2015
 */

public class BoundedBufferTC
{  
    // A simple ring buffer is used to hold the data

    // buffer capacity
    public static final int SIZE = 5;
    private Object[] buffer = new Object[SIZE];
    private int inIndex = 0, outIndex = 0, count = 0;

    // If true, there is room for at least one object in the buffer.
    private boolean writeable = true;

    // If true, there is at least one object stored in the buffer.    
    private boolean readable = false;

    public void addLast(Object item)
    {
        if (!writeable) {
            return;
        }
        
        buffer[inIndex] = item;
        //readable = true;

        inIndex = (inIndex + 1) % SIZE;
        count++;
        if (count == SIZE)
            writeable = false;
            
        if (count == 1) {
            readable = true;
        }
    }

    public Object removeFirst()
    {
        Object item;
        
        if (!readable) {
            return null;
        }

        item = buffer[outIndex];
        //writeable = true;

        outIndex = (outIndex + 1) % SIZE;
        count--;
        if (count == 0)
            readable = false;
            
        if (count == SIZE-1) {
            writeable = true;
        }

        return item;
    }
    
    //public boolean isReadable() {
    //    return readable;
    //}
    
    //public boolean isWriteable() {
    //    return writeable;
    //}
    
    public int getCount() {
        return count;
    }
}
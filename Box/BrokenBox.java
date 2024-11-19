/**
 * The basic Box class to show mutual exclusion and 
 * condition synchronization.  Broken here.
 * 
 * @author Lynn Marshall 
 * @version 1.1
 */

public class BrokenBox
{
    private Object contents = null; // contents
    private boolean empty = true; // empty?
    
    /**
     * Puts an object in the box.  This method returns when
     * the object has been put into the box.
     * 
     * @param item The object to be put in the box.
     */
    public boolean put(Object item) {
	if ( !empty ) return false;
        contents = item;
	try {
	    Thread.sleep( 0 );
	} catch (InterruptedException e) {}
        empty = false;
	return true;
    }
    
    /**
     * Gets an object from the box.  This method returns once the
     * object has been removed from the box.
     * 
     * @return The object taken from the box.
     */
    public Object get() {
        Object item = contents;

	try {
	    Thread.sleep( 0 );
	} catch (InterruptedException e) {}
        contents = null;
        empty = true;
        return item;
    }

}

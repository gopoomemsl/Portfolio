import java.util.Arrays;

/**
 * This class creates a runnable SortingThread. Each SortingThread will run a thread to 
 * sort an array twice, first unsynchronized, then synchronized together with the other 
 * SortingThread objects. The synchronization is handled by a SortingBuffer object.
 * @author Paul Szyller
 */
public class SortingThread implements Runnable
{
	/**
	 * The number representing the current thread.
	 */
	private final int threadNumber;
	
	/**
	 * The array of integer to sort.
	 */
	private final int []numArray;
	
	/**
	 * The SortingBuffer object to synchronize this thread with the others.
	 */
	private final SortingBuffer sortingBuffer;
	
	/**
	 * This very simple constructor only remembers the parameters in instance variables.
	 * @param num		Thread number.
	 * @param array		Int array to sort.
	 * @param buffer	Buffer object to synchronize the sorting.
	 */
	public SortingThread(int num, int []array, SortingBuffer buffer)
	{
		threadNumber = num;
		numArray = array;
		sortingBuffer = buffer;
	}
	
	/**
	 * This run function sorts the int array, prints every sorted element unsynchronized 
	 * once, then a second time synchronized using a SortingBuffer.
	 */
	public void run()
	{
		Arrays.sort(numArray);
		for (int i : numArray)
		{
			System.out.printf("%d unsynchronized %d\n", threadNumber, i);
		}
		
		for (int i : numArray)
		{
			try
			{
				sortingBuffer.waitUntilMinimum(threadNumber, i);
				System.out.printf("%d synchronized %d\n", threadNumber, i);
				sortingBuffer.finished(threadNumber);
			}
			catch (InterruptedException e)
			{
				System.out.printf(
						"Sorting thread %d terminated prematurely due to interruption", 
						threadNumber);
			}			
		}
	}
}

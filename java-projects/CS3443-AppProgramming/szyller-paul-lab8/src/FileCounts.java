import java.io.*;
import java.util.*;

/**
 * This class opens a file in a FileCounts object, then counts the number of lines, 
 * tokens, chars, and bytes in the file through its methods.
 * 
 * @author Paul Szyller
 */
public class FileCounts 
{
    private File file;
    
    /**
     * This constructor only register the file from the arguments in the object.
     * @param file
     */
    public FileCounts(File file) 
    {
        this.file = file;
    }
 
    /**
     * Counts the number of lines in the file and throws appropriate 
     * exceptions if needed.
     * @return a count of lines in the file.
     * @throws FileNotFoundException
     */
    public int lineCount() throws FileNotFoundException 
    {
    	int count = 0;
    	Scanner scan = null;
    	
    	try
    	{
    		scan = new Scanner(file);
    		while (scan.hasNextLine())
        	{
        		count++;
        		scan.nextLine();
        	}
        	
        	scan.close();
    	}
    	catch (FileNotFoundException e)
		{
    		throw new FileNotFoundException("Failed to open file");
		}
    	
        return count;
    }
    
    /**
     * Counts the number of tokens in the file and throws appropriate 
     * exceptions if needed.
     * @return a count of tokens in the file.
     * @throws FileNotFoundException
     */
    public int tokenCount() throws FileNotFoundException 
    {
    	int count = 0;
    	Scanner scan = null;
    	
    	try
    	{
    		scan = new Scanner(file);
    		while (scan.hasNext())
        	{
        		count++;
        		scan.next();
        	}
        	
        	scan.close();
    	}
    	catch (FileNotFoundException e)
		{
    		throw new FileNotFoundException("Failed to open file");
		}
    	
        return count;
    }
    
    /**
     * Counts the number of characters in the file and throws appropriate 
     * exceptions if needed.
     * @return a count of chars in the file.
     * @throws IOException
     */
    public int charCount() throws IOException 
    {
    	int count = 0;
    	FileReader reader = null;
    	
    	try
    	{
    		reader = new FileReader(file);
    		while (reader.read() != -1)
    		{
    			count++;
    		}
    		reader.close();
    		
    	}
    	catch (FileNotFoundException e)
		{
    		throw new FileNotFoundException("Failed to open file");
		}
    	catch (IOException e)
		{
    		throw new IOException("IO Exception encountered");
		}
    	
        return count;
    }
    
    /**
     * Counts the number of bytes in the file and throws appropriate 
     * exceptions if needed.
     * @return a count of bytes in the file.
     * @throws IOException
     */
    public int byteCount() throws IOException 
    {
        int count = 0;
        FileInputStream stream = null;
    	
    	try
    	{
    		stream = new FileInputStream(file);
    		while (stream.read() != -1)
    		{
    			count++;
    		}
    		stream.close();
    		
    	}
    	catch (FileNotFoundException e)
		{
    		throw new FileNotFoundException("Failed to open file");
		}
    	catch (IOException e)
		{
    		throw new IOException("IO Exception encountered");
		}
    	
        return count;
    }
}

package core;
import java.util.*;
/**
 * This class will allow us to create a Grades object, each student will be represented by a Grades object.
 * <br>
 * A Grades object contains a list of grades for the student, the student's name, the number of grades in the array,
 * and the sum, average, median, maximum, and minimum of all grades.
 * @author Paul Szyller
 */
public class Grades 
{
	private int[] grades; //array of grades
	private String name; //student's name
	private int length; //number of grades in array
	private int sum;
	private float average;
	private float median;
	private int maximum;
	private int minimum;
	
	/**
	 * Constructor method for the class Grades.
	 * @param newName The student's name for the new Grades object.
	 */
	public Grades (String newName)
	{
		name = newName;
		length = 0;	
		grades = new int[2];
	}
	
	/**
	 * This method inputs a new grade in the grades array for the student and updates all calculations for sum, avg, median, etc...
	 * <br>
	 * The method also resizes the grades array if necessary to input more data.
	 * @param newGrade The grade to be added to the grades array.
	 */
	public void insertGrade(int newGrade)
	{		
		//resize________________________________________________
		if (length >= grades.length) //If the array is full
		{
			int[] newArray = new int[grades.length * 2]; //create a new array twice the size of existing one
			
			for (int i = 0; i < grades.length; i++)
			{
				newArray[i] = grades[i]; //puts all the existing values from old array to new array
			}
			
			grades = newArray; //replaces the old array with the new one
		}
		//______________________________________________________
		
		grades[length++] = newGrade; //adds the new grade to array and increment length by 1
	}
	
	/**
	 * This method formats the grades array in a string to print.
	 */
	public String toString()
	{
		String gradeList = name + " [";
		
		for (int i = 0; i < length; i++)
		{
			gradeList += grades[i];
			
			if (i != length - 1)
			{
				gradeList += ", ";
			}
		}
		
		gradeList += "]";
		
		return gradeList;
	}
	
	/**
	 * @return The student's name.
	 */
	public String getName()
	{
		return name;
	}
	
	/**
	 * @return The length of the grades array/ the number of grades for the student.
	 */
	public int length()
	{
		return length;
	}
	
	/**
	 * @return The student's average grade.
	 */
	public float average()
	{	
		if (length == 0)
		{
			throw new NullPointerException();
		}
		
		sum = 0;
		average = 0;
		
		for (int i = 0; i < length; i++)
		{
			if (grades[i] < 0)
			{
				throw new IndexOutOfBoundsException();
			}
			sum += grades[i];
		}
		average = (float)sum / length;
		
		return average;
	}
	
	/**
	 * @return The student's median grade.
	 */
	public float median()
	{
		if (length == 0)
		{
			throw new NullPointerException();
		}
		
		for (int g : grades)
		{
			if (g < 0)
			{
				throw new IndexOutOfBoundsException();
			}
		}
		
		int[] tempArray = Arrays.copyOf(grades, length); //temp array to be able to sort without messing with the original
		Arrays.sort(tempArray); //sorts the temp array of grades	
		int midIndex = tempArray.length / 2; //mark the middle index of the array
		
		if (tempArray.length % 2 == 0) //if there is an even number of grades
		{
		    median = (float)(tempArray[midIndex] + tempArray[midIndex-1]) / 2;//median = the average of the two grades in the middle of the sorted array
		}
		else //else if there is an odd number of grades
		{
		    median = (float)tempArray[midIndex]; //median = grade in the middle of the sorted array
		}
		
		return median;
	}
	
	/**
	 * @return The student's maximum grade.
	 */
	public int maximum()
	{
		if (length == 0)
		{
			throw new NullPointerException();
		}
		
		maximum = 0;
		for (int i = 0; i < length; i++)
		{
			if (grades[i] < 0)
			{
				throw new IndexOutOfBoundsException();
			}
			
			if (grades[i] > maximum) //replace max with the new grade if it is greater
			{
				maximum = grades[i];
			}
		}		
		
		return maximum;
	}
	
	/**
	 * @return The student's minimum grade.
	 */
	public int minimum()
	{
		if (length == 0)
		{
			throw new NullPointerException();
		}
		
		for (int i = 0; i < length; i++)
		{
			if (grades[i] < 0)
			{
				throw new IndexOutOfBoundsException();
			}
			
			if (grades[i] < minimum || i == 0) //replace min with the new grade if it is lesser or if it is the first grade
			{
				minimum = grades[i];
			}
		}
		
		return minimum;
	}
}

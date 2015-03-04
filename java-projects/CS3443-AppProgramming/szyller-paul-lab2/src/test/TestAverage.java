package test;
import core.Grades;
import static org.junit.Assert.*;
import org.junit.Test;
/**
 * This is a JUnit test class. Its goal is to test the method average() from the Grades class.
 * @author Paul Szyller
 */
public class TestAverage 
{
	/**
     * Test case using null grade array. The correct behavior is
     * a runtime error.
     */
	@Test
	public void testNull() 
	{
		Grades testStudent = new Grades ("Test Student");
		boolean error = false;
		try
		{
			testStudent.average();
		}
		catch (NullPointerException e)
		{
			error = true;
		}
		assertTrue("should be a NullPointerException", error);
	}
	
	/**
     * Test case using 100 elements. The correct behavior is the
     * average of the numbers plus or minus roundoff.
     */
	@Test
	public void testManyElem()
	{
		Grades testStudent = new Grades ("Test Student");
		double average = 0;
		
		for (int i = 1; i <= 100; i++)
		{
			testStudent.insertGrade(i);
			average += i;
		}
		
		average /= 100;
		assertEquals("100 element test failed", average, testStudent.average(), 0.000001);
	}
	
	/**
     * Test case using only one element. The correct behavior is to
     * return the one grade as the average.
     */
	@Test
	public void testOneElem()
	{
		Grades testStudent = new Grades ("Test Student");
		int grade = 86;
		testStudent.insertGrade(grade);
		assertEquals("One element test failed", grade, testStudent.average(), 0.000001);
	}
	
	/**
     * Test case using at least one negative (invalid) grade. The correct behavior is
     * a runtime error.
     */
	@Test
	public void testNegElem()
	{
		Grades testStudent = new Grades ("Test Student");
		boolean error = false;
		int [] grades = { 80, 85, 76, 93, -49 };
		
		for (int g : grades)
		{
			testStudent.insertGrade(g);
		}
		
		try
		{
			testStudent.average();
		}
		catch (IndexOutOfBoundsException e)
		{
			error = true;
		}
		assertTrue("should be a IndexOutOfBoundsException", error);
	}
	
	
}

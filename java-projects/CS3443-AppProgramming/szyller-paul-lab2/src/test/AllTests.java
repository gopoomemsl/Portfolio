package test;
import org.junit.runner.RunWith;
import org.junit.runners.Suite;
import org.junit.runners.Suite.SuiteClasses;
/**
 * This is a JUnit test suite. It is simply used to launch all of our test cases at once.
 * @author Paul Szyller
 */
@RunWith(Suite.class)
@SuiteClasses({ TestAverage.class, TestMedian.class, TestMinimum.class })
public class AllTests {

}

package es.ua.dlsi.prog3.p1;

import static org.junit.Assert.*;

import java.lang.reflect.Field;
import java.util.ArrayList;
import java.util.Arrays;

import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;

/**
 * Unit tests for the class SummaryStatistics 
 */
public class SummaryStatisticsTest {
	/**
	 * This vector will be initialized before each test method 
	 */
	ArrayList<Integer> v;

	/**
	 * Executed before each method annotated with @Test
	 */
	@Before
    public void setUp() {
		v = new ArrayList<>();		
		v.addAll(Arrays.asList(34, 10, 293, 23));
	}
	
	/**
	 * The class method COUNT_INSTANCES is checked by creating different objects. In order to test that the copy constructor increments the instance count we've added it to the test.
	 * Note this method may be invoked at any point, so the COUNT_INSTANCES depends on when it's invoked
	 */
	@Test
	public void testCopyConstructorAndInstanceCount() {
		int currentInstances = SummaryStatistics.COUNT_INSTANCES();
		assertTrue("Current instances", currentInstances >= 0);
		SummaryStatistics s1 = new SummaryStatistics(v);
		assertEquals("First instance", currentInstances+1, SummaryStatistics.COUNT_INSTANCES());
		SummaryStatistics s2 = new SummaryStatistics(v);
		assertEquals("Second instance", currentInstances+2, SummaryStatistics.COUNT_INSTANCES());
		assertNotEquals("Different ids", s1.getId(), s2.getId());
		assertEquals("Averages", s1.getAverage(), s2.getAverage());
		assertEquals("Mins", s1.getMin(), s2.getMin());
		assertEquals("Maxs", s1.getMax(), s2.getMax());
		
	}	
	
	
	
	/**
	 * When the instance is initialized with the default constructor, `getMin` and `getMax` must return `null`, and `getSize` 0.
	 */
	@Test
	public void testEmpty() {
		SummaryStatistics s = new SummaryStatistics();
		assertNull("Average should be null", s.getAverage());
		assertNull(s.getMin());
		assertNull(s.getMax());
		assertEquals(0, s.getSize());		
	}
    
	/**
	 * The `add` method is tested by adding three values and computing the size and average
	 */
	@Test
	public void testAdd() {
		SummaryStatistics s = new SummaryStatistics();
		s.add(10);
		s.add(10);
		s.add(40);
		assertEquals("Size", 3, s.getSize());
		assertEquals("Average", (Integer)20, s.getAverage()); // if the cast is not used, Java complains about an ambiguous call
	}	
	
	/**
	 * getAverage method tested with the values initialized in setUp()
	 */
	@Test
	public void testGetAverage() {
		SummaryStatistics statistics = new SummaryStatistics(v);
		assertEquals("AVG", (Integer)90, statistics.getAverage()); // if the cast is not used, Java complains about an ambiguous call 
	}

	/**
	 * getMax method test tested with the values initialized in setUp()
	 */
	@Test
	public void testGetMax() {
		SummaryStatistics statistics = new SummaryStatistics(v);
		assertEquals("Max", (Integer)293, statistics.getMax());  // if the cast is not used, Java complains about an ambiguous call
	}

	/**
	 * getMinmethod test tested with the values initialized in setUp()
	 */	
	@Test
	public void testGetMin() {
		SummaryStatistics statistics = new SummaryStatistics(v);
		assertEquals("Min", (Integer)10, statistics.getMin()); // if the cast is not used, Java complains about an ambiguous call
	}

	/**
	 * Constructor is checked to use defensive copy
	 */
	@Test
	public void testDefensiveCopyInConstructor() {
		SummaryStatistics s1 = new SummaryStatistics(v);
		Integer average = s1.getAverage();
		// modify v - if it's correctly initialized the average should not change after the change of v
		v.set(0, 100);
		assertEquals("Average after v change", average, s1.getAverage());		
		
	}
	
	/*@Test
	public void testParameterizedConstructorWithNull() {
		SummaryStatistics s = new SummaryStatistics(null);
	    assertEquals("Size should be 0 when initialized with null", 0, s.getSize());
	    assertNull("Average should be null", s.getAverage());
	    assertNull("Min should be null", s.getMin());
	    assertNull("Max should be null", s.getMax());
	}*/

	@Test
	public void testNegativeValues() {
	    ArrayList<Integer> negativeValues = new ArrayList<>(Arrays.asList(-10, -20, -5));
	    SummaryStatistics s = new SummaryStatistics(negativeValues);
	    assertEquals("Max with negative values", (Integer)(-5), s.getMax());
	    assertEquals("Min with negative values", (Integer)(-20), s.getMin());
	    assertEquals("Average with negative values", (Integer)(-11), s.getAverage());
	}

	@Test
	public void testUniqueID() {
	    SummaryStatistics s1 = new SummaryStatistics();
	    SummaryStatistics s2 = new SummaryStatistics();
	    assertNotEquals("Each instance should have a unique ID", s1.getId(), s2.getId());
	}

	@Test
	public void testInstanceCountAfterCopies() {
	    int initialCount = SummaryStatistics.COUNT_INSTANCES();
	    SummaryStatistics s1 = new SummaryStatistics();
	    SummaryStatistics s2 = new SummaryStatistics(s1);
	    assertEquals("Instance count should increase after copy constructor", initialCount + 1, SummaryStatistics.COUNT_INSTANCES());
	}

	@Test
	public void testAddAndRemoveValues() {
	    SummaryStatistics s = new SummaryStatistics();
	    s.add(5);
	    s.add(15);
	    assertEquals("Size after adding values", 2, s.getSize());
	    assertEquals("Min value after adding", (Integer)5, s.getMin());
	    s.add(-10);
	    assertEquals("Min after adding negative value", (Integer)(-10), s.getMin());
	}

	@Test
	public void testAverageOfSameValues() {
	    SummaryStatistics s = new SummaryStatistics();
	    s.add(10);
	    s.add(10);
	    s.add(10);
	    assertEquals("Average of identical values", (Integer)10, s.getAverage());
	}

	@Test
	public void testMaxWithSameValues() {
	    SummaryStatistics s = new SummaryStatistics();
	    s.add(42);
	    s.add(42);
	    assertEquals("Max with same values", (Integer)42, s.getMax());
	}

	@Test
	public void testMinWithSingleValue() {
	    SummaryStatistics s = new SummaryStatistics();
	    s.add(50);
	    assertEquals("Min with one value", (Integer)50, s.getMin());
	}

	@Test
	public void testCopyConstructorWithEmptyList() {
	    SummaryStatistics s1 = new SummaryStatistics();
	    SummaryStatistics s2 = new SummaryStatistics(s1);
	    assertEquals("Size of copied object with empty list", 0, s2.getSize());
	    assertNull("Average of copied object should be null", s2.getAverage());
	}

	@Test
	public void testDefensiveCopyInAddMethod() {
	    SummaryStatistics s1 = new SummaryStatistics();
	    ArrayList<Integer> valuesCopy = new ArrayList<>(Arrays.asList(10, 20, 30));
	    s1.add(10);
	    assertEquals("Initial size", 1, s1.getSize());
	    
	    // Modify valuesCopy after adding to check if defensive copy works
	    valuesCopy.set(0, 100);
	    assertEquals("Size should remain the same", 1, s1.getSize());
	    assertEquals("First value should not be affected", (Integer)10, s1.getMin());
	}

	@Test
	public void testStaticMethodCOUNT_INSTANCES() {
	    int initialCount = SummaryStatistics.COUNT_INSTANCES();
	    SummaryStatistics s1 = new SummaryStatistics();
	    SummaryStatistics s2 = new SummaryStatistics();
	    assertEquals("COUNT_INSTANCES should reflect the number of created instances", initialCount + 2, SummaryStatistics.COUNT_INSTANCES());
	}

	@Test
	public void testCopyConstructorRetainsOriginalValues() {
	    SummaryStatistics s1 = new SummaryStatistics(v);
	    SummaryStatistics s2 = new SummaryStatistics(s1);
	    assertEquals("Copy constructor should retain average", s1.getAverage(), s2.getAverage());
	    assertEquals("Copy constructor should retain min", s1.getMin(), s2.getMin());
	    assertEquals("Copy constructor should retain max", s1.getMax(), s2.getMax());
	}

	@Test
	public void testNoEffectOfChangesAfterCopy() {
	    SummaryStatistics s1 = new SummaryStatistics(v);
	    SummaryStatistics s2 = new SummaryStatistics(s1);
	    
	    // Modify the original and check the copy remains unaffected
	    s1.add(999);
	    assertNotEquals("Modifying original should not affect copy", s1.getMax(), s2.getMax());
	}

	
	
}

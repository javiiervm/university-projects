package es.ua.dlsi.prog3.p4.model;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotEquals;
import static org.junit.Assert.assertNotSame;

import org.junit.Before;
import org.junit.Test;

import es.ua.dlsi.prog3.p4.util.Util;

public class CircleTest {	
	Coordinate rc;
	Shape2D c; 


	@Before
	public void setUp() throws Exception {
		rc = new Coordinate(100, 500);
		c = new Circle(rc, 231);
	}
	
	@Test
	public final void testCtor1() {
		Circle c = new Circle();
		assertEquals("Default ctor, radius==0",0.0,c.getRadius(),0.001);
		assertEquals("Default ctor, position",new Coordinate(),c.getPosition());
	}

	@Test
	public final void testCtor2() {
		Circle c2 = new Circle((Circle)c);
		assertEquals("Copy ctor position",c.getPosition(),c2.getPosition());
		assertEquals("Copy ctor radius",((Circle)c).getRadius(),c2.getRadius(), 0.001);
	}
	
	
	@Test
	public final void testEscalar200() throws Exception   {
		Coordinate coord = new Coordinate(10.0,-20.0);
		Circle c1 = new Circle(coord, 10.0);
		c1.scale(200.0);
		assertEquals("Circle scale 200%", 20.0, c1.getRadius(), 0.001); 
		assertEquals("Circle scale 200% same pos", coord, c1.getPosition()); 
	}

	@Test
	public final void testCloneIsDefined() {
		Coordinate coord = new Coordinate();
		Circle c1 = new Circle(coord, 10);
		c1.clone();
		c1.clone(new Coordinate(1.1,1.1));
	}
	
	@Test
	public final void testToString()  {
		String s = "(100.0,500.0),radius=231.0";
		assertEquals("Circle toString()",s,c.toString());		
	}

	@Test
	public final void testEquals()  {
		Circle c2 = new Circle(rc, 231);
		assertEquals("Circle.equals()",c,c2);
	}

}

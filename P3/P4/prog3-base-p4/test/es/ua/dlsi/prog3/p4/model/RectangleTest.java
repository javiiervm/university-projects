package es.ua.dlsi.prog3.p4.model;

import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;


public class RectangleTest {	
	Coordinate rc;
	Shape2D c; 


	@Before
	public void setUp() throws Exception {
		rc = new Coordinate(100, 500);
		c = new Rectangle(rc, 45, 231, 99);
	}
	
	@Test
	public final void testCtor1() {
		Rectangle c = new Rectangle();
		assertEquals("Default ctor, length==0",0.0,c.getLength(),0.001);
		assertEquals("Default ctor, width==0",0.0,c.getWidth(),0.001);
		assertEquals("Default ctor, position",new Coordinate(),c.getPosition());
	}

	@Test
	public final void testCtor2() {
		Rectangle c2 = new Rectangle((Rectangle)c);
		assertEquals("Copy ctor",c.getPosition(),c2.getPosition());
	}

	
	
	@Test
	public final void testEscalar200()  {
		Coordinate coord = new Coordinate();
		Rectangle c1 = new Rectangle(coord, 0, 10, 100);
		Shape2D rect = c1;
		rect.scale(200);
		assertEquals("Escalar 200", 20, c1.getLength(), 0.001);
		assertEquals("Escalar 200", 200, c1.getWidth(), 0.001);
		assertEquals("Rectangle scale 200% same pos", coord, c1.getPosition()); 
	}

	@Test
	public final void testCloneIsDefined() {
		Coordinate coord = new Coordinate();
		Rectangle c1 = new Rectangle(coord, 0, 10,100);
		c1.clone();
		c1.clone(new Coordinate(1.1,1.1));
	}
	
	@Test
	public final void testToString()  {
		String s = "(100.0,500.0),angle=45.0,length=231.0,width=99.0";
		assertEquals("Rectangle toString()",s,c.toString());		
	}

	@Test
	public final void testEquals()  {
		Shape2D c2 = new Rectangle(rc, 45, 231, 99);
		assertEquals("Rectangle.equals()",c,c2);
	}


	
}

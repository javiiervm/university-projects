package es.ua.dlsi.prog3.p4.model;

import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;

public class SquareTest {	
	Coordinate position;
	Shape2D square; 


	@Before
	public void setUp() throws Exception {
		position = new Coordinate(100, 500);
		square = new Square(position, 45, 99);
	}
	
	@Test
	public final void testCtor1() {
		Square c = new Square();
		assertEquals("Default ctor, side==0",0.0,c.getSide(),0.001);
	}


	@Test(expected=IllegalArgumentException.class)
	public final void testConstructorLengthKO() throws Exception   {
		new Square(position, 0, -1.0);
	}


	@Test
	public final void testEscalar200()  {
		Coordinate coord = new Coordinate();
		Square c1 = new Square(coord, 10, 100);
		Shape2D rect = c1;
		rect.scale(200);
		assertEquals("Escalar 200", 200, c1.getSide(), 0.001); 
	}
			
	@Test
	public final void testToString()  {
		String s = "(100.0,500.0),angle=45.0,side=99.0";
		assertEquals("Square toString()",s,square.toString());		
	}

	@Test
	public final void testEquals()  {
		Shape2D c2 = new Square(position, 45, 99);
		assertEquals("Square.equals()",square,c2);
	}

}

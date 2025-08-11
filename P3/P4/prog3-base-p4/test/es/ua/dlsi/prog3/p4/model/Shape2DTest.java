package es.ua.dlsi.prog3.p4.model;



import static org.junit.Assert.*;


import org.junit.Before;
import org.junit.Test;

import es.ua.dlsi.prog3.p4.util.Util;

/**
 * @author pierre
 *
 */
public class Shape2DTest {
	class NewShape2D extends Shape2D {
		NewShape2D() {
		}

		NewShape2D(Coordinate pos) {
			super(pos);
		}
		
		NewShape2D(NewShape2D other) { 
			super(other);
		}
		
		@Override
		public void scale(double porcentaje)  {
		}
		
		@Override
		public NewShape2D clone() {
			return null;
		}
	}

	Shape2D default_shape,red_shape, copy_shape;
	Coordinate position;
	/**
	 * @throws java.lang.Exception
	 */
	@Before
	public void setUp() throws Exception {
		position = new Coordinate(1,1);
		default_shape = new NewShape2D();
		red_shape = new NewShape2D(position);
		copy_shape = new NewShape2D((NewShape2D)red_shape);
	}

	/**
	 * Test method for {@link es.ua.dlsi.prog3.p4.model.Shape2D#Shape2D()}.
	 */
	@Test
	public final void testShape2D() {
		Coordinate pos = default_shape.getPosition();
		assertEquals("Shape2D position",new Coordinate(),pos);
	}

	/**
	 * Test method for {@link es.ua.dlsi.prog3.p4.model.Shape2D#Shape2D(es.ua.dlsi.prog3.p4.model.Coordinate, es.ua.dlsi.prog3.p4.model.Color)}.
	 */
	@Test
	public final void testShape2DCoordinate() {
		Coordinate pos = red_shape.getPosition();
		assertEquals("Shape2D position",position,pos);
	}




	
	/**
	 * Test method for {@link es.ua.dlsi.prog3.p4.model.Shape2D#move(es.ua.dlsi.prog3.p4.model.Coordinate)}.
	 */
	@Test
	public final void testMove() {
		Coordinate newpos=new Coordinate(3.2,-2.3);
		red_shape.move(newpos);
		Coordinate pos = red_shape.getPosition();
		assertEquals("Shape2D move",newpos, pos);
	}



	/**
	 * Test method for {@link es.ua.dlsi.prog3.p4.model.Shape2D#toString()}.
	 */
	@Test
	public final void testToString() {
		String result = "(1.0,1.0)";
		assertEquals("Shape2D toString",result,red_shape.toString());
	}

	/**
	 * Test method for {@link es.ua.dlsi.prog3.p4.model.Shape2D#clone()}.
	 * Just checks it is defined
	 */
	@Test
	public final void testClone() {
		Shape2D shape = red_shape.clone();
		assertNull("NewShape2D clone is null",shape);
	}
	
	/**
	 * Test method for {@link es.ua.dlsi.prog3.p4.model.Shape2D#clone(Coordinate)}.
	 * Just checks Shape2D.move(Coordinate) is defined
	 */
	public final void testClone2() {
		try {
			Shape2D shape = red_shape.clone(new Coordinate(2.0,3.4));
		} catch (Exception ex) {
			// if the method is correctly implemented, it will throw a NullPointerException,
			// because of the clone() implementation in NewShape2D
			
			// do nothing with 'ex' 
		}
	}

	/**
	 * Test method for {@link es.ua.dlsi.prog3.p4.model.Shape2D#scale(double)}.
	 * Just checks it is defined
	 */
	@Test
	public final void testScale() {
		red_shape.scale(50.0);
		// NewShape2D.scale() does nothing, so no assertions here
	}

}

package es.ua.dlsi.prog3.p4.model;

import static org.junit.Assert.*;

import java.lang.reflect.Constructor;
import java.lang.reflect.Modifier;

import org.junit.Before;
import org.junit.Test;

public class AbstractPolygonTest {

	class NewPolygon extends AbstractPolygon {
		NewPolygon() {
		}

		NewPolygon(Coordinate pos, double angle) {
			super(pos,angle);
		}
		
		NewPolygon(NewPolygon other) { 
			super(other);
		}

		@Override
		public NewPolygon clone() {
			return null;
		}

		@Override
		public void scale(double percentage) {
		}
	}

	AbstractPolygon default_polygon, polygon, copy_polygon;
	Coordinate position = new Coordinate(1,2);
	double angle;
	
	/**
	 * @throws java.lang.Exception
	 */
	@Before
	public void setUp() throws Exception {
		angle = 45;
		default_polygon = new NewPolygon();
		polygon = new NewPolygon(position,angle);
		copy_polygon = new NewPolygon((NewPolygon)polygon);
	}	
	

	@Test
	public final void testAbstractPolygon() {
		double ang = default_polygon.getAngle();
		assertEquals("AbstractPolygon angle", 0.0, ang, 0.001);
	}
	
	@Test
	public final void testAbstractPolygonCoordinateAngle() {
		double ang = polygon.getAngle();
		assertEquals("AbstractPolygon angle",angle,ang, 0.001);
	}

	@Test
	public final void testAbstractPolygonCopyCtr() {
		double ang2 = polygon.getAngle();
		double ang3 = copy_polygon.getAngle();
		assertEquals("AbstractPolygon angle",ang2,ang3,0.001);
	}
	
		
	
	@Test(expected=IllegalArgumentException.class)
	public final void testRotateWrong2() {
		polygon.rotate(360);
	}

	@Test
	public final void testToString() {
		String result = "(1.0,2.0),angle=45.0";
		assertEquals("AbstractPolygon toString",result,polygon.toString());
	}

	
	@Test
	public final void testEqualsObject() {
		AbstractPolygon p2 = new NewPolygon(position,angle);
		assertEquals("AbstractPolygon equals",polygon,p2);
			
		AbstractPolygon p3 = new NewPolygon(new Coordinate(2.3,6.2),angle);
		assertNotEquals("AbstractPolygon not equals",polygon,p3);
		
		AbstractPolygon p4 = new NewPolygon(position, 90);
		assertNotEquals("AbstractPolygon not equals",polygon,p4);
	}
	
}

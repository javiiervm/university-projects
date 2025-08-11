package es.ua.dlsi.prog3.p4.model;

import static org.junit.Assert.*;

import java.util.ArrayList;

import org.junit.Before;
import org.junit.Test;

import es.ua.dlsi.prog3.p4.util.Util;

public class CanvasTest {

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
			return new NewShape2D(this);
		}
	}

	Canvas lienzo;
	
	@Before
	public void setUp() throws Exception {
		lienzo = new Canvas();
		lienzo.addShape(new NewShape2D());
		lienzo.addShape(new NewShape2D());
	}

	@Test
	public final void testDefaultCtor()  {
		Canvas l = new Canvas();
		
		assertEquals("Alto por defecto", Canvas.DEFAULT_SIZE, l.getHeight(), 0.001);
		assertEquals("Ancho por defecto", Canvas.DEFAULT_SIZE, l.getWidth(), 0.001);
		assertEquals("No figures in new Canvas",0,l.getNumShapes());
	}

	@Test
	public final void testCanvasStringFloatFloat()  {
		
		Canvas l = new Canvas("Prueba", 10, 20);
		assertEquals("Height 20", 20, l.getHeight(), 0.001);
		assertEquals("Width 10", 10, l.getWidth(), 0.001);
		assertEquals("No figures in new Canvas",0,l.getNumShapes());
	}	
	
	@Test(expected=IllegalArgumentException.class)
	public final void testBadCanvas() {
		new Canvas("Bad Canvas dimensions", -10, -20);
	}

	@Test(expected=IndexOutOfBoundsException.class)
	public final void testLienzoGetMalCero() {
		lienzo.getShape(0);
	}

	@Test
	public final void testLienzoGetShapeOK() throws Exception {
		Shape2D c = new NewShape2D();
		assertEquals(c, lienzo.getShape(2));
	}

	@Test(expected=IndexOutOfBoundsException.class)
	public final void testLienzoRemoveMalCero() {
		lienzo.removeShape(0);
	}

	@Test
	public  final void testCloneIsDefined() {
		lienzo.clone();
	}

	@Test
	public final void testGetNumShapesIsDefined() {
		lienzo.getNumShapes();
	}

	@Test
	public  final void testToString() {
		String s = "default canvas (1000.0,1000.0) with 2 shapes";
		assertEquals("Canvas.toString()",s,lienzo.toString());
	}

}

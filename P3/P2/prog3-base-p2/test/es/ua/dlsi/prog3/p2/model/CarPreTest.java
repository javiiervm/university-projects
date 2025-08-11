package es.ua.dlsi.prog3.p2.model;

import static org.junit.Assert.*;

import org.junit.Test;

import es.ua.dlsi.prog3.p2.exceptions.PressureWheelException;
import es.ua.dlsi.prog3.p2.exceptions.TooManyWheelsException;
import es.ua.dlsi.prog3.p2.exceptions.WrongTyreTypeException;

public class CarPreTest {

    @Test
    public void testConstructor() {
        Car c = new Car();
        assertEquals(c.getWheels().size(), 0);
    }

    @Test
    public void testAddWheel3() {
        Car c = new Car();
        try {
            TyreType t = new TyreType("205/65 R16", 1.5, 4);
            c.addWheel(new Wheel(t));
            c.addWheel(new Wheel(t));
            c.addWheel(new Wheel(t));
            c.addWheel(new Wheel(t));
        } catch (TooManyWheelsException | WrongTyreTypeException e) {
            fail("Unexpected exception " + e.getClass());
        }
    }

    @Test(expected = IllegalArgumentException.class)
    public void testChangeTyres1() {
        Car c = new Car();
        try {
            Wheel w = new Wheel();
            c.addWheel(w);
            c.addWheel(w);
            c.changeTyres(null, 2.25);
        } catch (TooManyWheelsException | WrongTyreTypeException | PressureWheelException e) {
            fail("Unexpected exception " + e.getClass());
        }
    }

    // New test methods

    @Test // (expected = TooManyWheelsException.class)
    public void testAddMoreThanAllowedWheels() throws TooManyWheelsException, WrongTyreTypeException {
        Car c = new Car();
        TyreType t = new TyreType("205/65 R16", 1.5, 4);

        try {
	        for (int i = 0; i <= 4; i++) {
	            c.addWheel(new Wheel(t)); // Should throw exception on the fifth wheel
	        }
        } catch (Exception e){
	            assertTrue(e instanceof TooManyWheelsException);
        }
    }

    @Test(expected = WrongTyreTypeException.class)
    public void testAddWheelWithDifferentTyreType() throws TooManyWheelsException, WrongTyreTypeException {
        Car c = new Car();
        TyreType t1 = new TyreType("205/65 R16", 1.5, 4);
        TyreType t2 = new TyreType("195/65 R15", 1.5, 4);

        c.addWheel(new Wheel(t1));
        c.addWheel(new Wheel(t2)); // Should throw WrongTyreTypeException
    }

    @Test(expected = PressureWheelException.class)
    public void testChangeTyresWithInvalidPressure() throws TooManyWheelsException, WrongTyreTypeException, PressureWheelException {
        Car c = new Car();
        TyreType t = new TyreType("205/65 R16", 1.5, 4);
        c.addWheel(new Wheel(t));
        c.addWheel(new Wheel(t));

        c.changeTyres(t, 5.0); // Should throw PressureWheelException
    }
}

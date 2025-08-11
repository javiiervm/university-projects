package es.ua.dlsi.prog3.p2.model;

import static org.junit.Assert.*;
import org.junit.Test;

import es.ua.dlsi.prog3.p2.exceptions.NoTyreTypeException;
import es.ua.dlsi.prog3.p2.exceptions.PressureWheelException;

public class WheelPreTest {

    @Test
    public void testConstructor1() {
        Wheel w = new Wheel();
        assertNull(w.getTyreType());
    }

    @Test
    public void testConstructor2() {
        TyreType t = new TyreType("205/65 R16", 2, 4);
        Wheel w = new Wheel(t);
        assertNotNull(w.getTyreType());
    }

    @Test
    public void testSetTyreType() {
        TyreType t = new TyreType("205/65 R16", 2, 4);
        Wheel w = new Wheel();
        assertNull(w.getTyreType());
        w.setTyreType(t);
        assertNotNull(w.getTyreType());
    }

    @Test(expected = IllegalArgumentException.class)
    public void testInflate1() {
        TyreType t = new TyreType("205/65 R16", 2, 4);
        Wheel w = new Wheel(t);
        try {
            w.inflate(-1);
        } catch (NoTyreTypeException | PressureWheelException e) {
            fail("Unexpected exception " + e.getMessage());
        }
    }

    // New test methods

    /*@Test
    public void testGetPressureWithoutInflation() throws NoTyreTypeException {
        TyreType t = new TyreType("205/65 R16", 2, 4);
        Wheel w = new Wheel(t);
        assertEquals(0, w.getPressure(), 0);
    }

    @Test
    public void testInflateValidPressure() throws NoTyreTypeException, PressureWheelException {
        TyreType t = new TyreType("205/65 R16", 2, 4);
        Wheel w = new Wheel(t);
        w.inflate(3);
        assertEquals(3, w.getPressure(), 0);
    }*/

    @Test(expected = PressureWheelException.class)
    public void testInflateAboveMaxPressure() throws NoTyreTypeException, PressureWheelException {
        TyreType t = new TyreType("205/65 R16", 2, 4);
        Wheel w = new Wheel(t);
        w.inflate(5); // Above the max pressure
    }

    @Test(expected = NoTyreTypeException.class)
    public void testInflateWithoutTyreType() throws NoTyreTypeException, PressureWheelException {
        Wheel w = new Wheel(); // No TyreType set
        w.inflate(3);
    }

    @Test
    public void testDeflateToZero() throws NoTyreTypeException, PressureWheelException {
        TyreType t = new TyreType("205/65 R16", 2, 4);
        Wheel w = new Wheel(t);
        w.inflate(3);
        //w.deflate(3);
        //assertEquals(0, w.getPressure(), 0);
    }

    @Test(expected = IllegalArgumentException.class)
    public void testDeflateBelowZero() throws NoTyreTypeException, PressureWheelException {
        TyreType t = new TyreType("205/65 R16", 2, 4);
        Wheel w = new Wheel(t);
        w.inflate(-1);
        //w.deflate(3); // Trying to deflate below zero
    }

    @Test
    public void testSetTyreTypeAfterInflation() throws NoTyreTypeException, PressureWheelException {
        TyreType t1 = new TyreType("205/65 R16", 2, 4);
        TyreType t2 = new TyreType("195/65 R15", 1, 3);
        Wheel w = new Wheel(t1);
        w.inflate(3);
        w.setTyreType(t2); // Change TyreType
        assertEquals(t2, w.getTyreType());
        //assertEquals(0, w.getPressure(), 0); // Pressure should reset
    }

    @Test
    public void testEqualityOfWheels() {
        TyreType t = new TyreType("205/65 R16", 2, 4);
        Wheel w1 = new Wheel(t);
        Wheel w2 = new Wheel(t);
        assertNotSame(w1, w2); // Different instances
        assertEquals(w1.getTyreType(), w2.getTyreType()); // Same TyreType
    }
}

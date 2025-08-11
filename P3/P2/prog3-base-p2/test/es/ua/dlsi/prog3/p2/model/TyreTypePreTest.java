package es.ua.dlsi.prog3.p2.model;

import static org.junit.Assert.*;
import org.junit.Test;

public class TyreTypePreTest {

    @Test(expected = IllegalArgumentException.class)
    public void testConstructor1() {
        new TyreType(null, -1, 0);
    }

    @Test
    public void testConstructor4() {
        new TyreType("185/65 R15", 1, 4);
    }

    @Test
    public void testToString() {
        TyreType t = new TyreType("185/65 R15", 1, 4);
        String s = "TyreType 185/65 R15 [1.0,4.0]";
        assertEquals(s, t.toString());
    }

    @Test
    public void testEquals() {
        TyreType t1 = new TyreType("185/65 R15", 1, 4);
        TyreType t2 = new TyreType("185/65 R15", 1, 4);
        assertEquals(t1, t2);
    }

    @Test
    public void testGetMinMaxPressure() {
        TyreType t = new TyreType("185/65 R15", 1, 4);
        assertEquals(t.getMinPressure(), 1, 0);
        assertEquals(t.getMaxPressure(), 4, 0);
    }

    // New test methods

    @Test
    public void testConstructorWithValidValues() {
        TyreType t = new TyreType("195/55 R16", 1.5, 3.5);
        assertNotNull(t);
        //assertEquals("195/55 R16", t.getName());
        assertEquals(1.5, t.getMinPressure(), 0);
        assertEquals(3.5, t.getMaxPressure(), 0);
    }

    @Test(expected = IllegalArgumentException.class)
    public void testConstructorWithReversedPressureValues() {
        new TyreType("185/65 R15", 4, 1); // max pressure less than min pressure
    }

    @Test
    public void testNotEqualsDifferentName() {
        TyreType t1 = new TyreType("185/65 R15", 1, 4);
        TyreType t2 = new TyreType("195/65 R15", 1, 4);
        assertNotEquals(t1, t2);
    }

    @Test
    public void testNotEqualsDifferentPressure() {
        TyreType t1 = new TyreType("185/65 R15", 1, 4);
        TyreType t2 = new TyreType("185/65 R15", 1.5, 4.5);
        assertNotEquals(t1, t2);
    }

    /*@Test
    public void testHashCode() {
        TyreType t1 = new TyreType("185/65 R15", 1, 4);
        TyreType t2 = new TyreType("185/65 R15", 1, 4);
        assertEquals(t1.hashCode(), t2.hashCode());
    }*/

    @Test
    public void testHashCodeDifferentObjects() {
        TyreType t1 = new TyreType("185/65 R15", 1, 4);
        TyreType t2 = new TyreType("195/65 R15", 1, 4);
        assertNotEquals(t1.hashCode(), t2.hashCode());
    }

    /*@Test
    public void testGetName() {
        TyreType t = new TyreType("185/65 R15", 1, 4);
        assertEquals("185/65 R15", t.getName());
    }*/

    @Test
    public void testPressureBoundaries() {
        TyreType t = new TyreType("185/65 R15", 1, 4);
        assertTrue(t.getMinPressure() <= 1);
        assertTrue(t.getMaxPressure() >= 4);
    }
}

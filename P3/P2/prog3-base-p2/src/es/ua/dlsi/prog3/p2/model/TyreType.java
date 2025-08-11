package es.ua.dlsi.prog3.p2.model;

import java.util.Objects;

/** 
 * TyreType class from practice 2 (Subject: Programming 3)
 * @author 
 */

/**
 * This class represents the trye of a wheel. It uses a description property to define the tyre's 
 * characteristics, as well as a minimum and maximum pressure definition to know which pressure
 * values are valid for it. Apart from the constructors, it has methods that return the values of
 * pressure or the description, as well as an equals() method that allows to know if two objects from
 * this class are equal or not.
 * In order to make this class immutable, it is declared as 'final', all its attributes are private
 * and it doesn't have any setter method, so once you create an object it can't be changed. In addition,
 * it uses defensive copy when an object returns its components.
 */
final class TyreType {
    /**
     * Instance attribute.
     * It stores a string with the description of the tyre, which follows a format like "185/65 R16". It is declared
     * as final to avoid any modification in the future.
     */
    private final String description;

    /**
     * Instance attribute.
     * It stores the minimum pressure allowed for this tyre type. Any value below this one would lead to an error, which
     * is properly handled in the corresponding method. It is declared as final to avoid any modification in the future.
     */
    private final double min_pressure;

    /**
     * Instance attribute.
     * It stores the maximum pressure allowed for this tyre type. Any value above this one would lead to an error, which
     * is properly handled in the corresponding method. It is declared as final to avoid any modification in the future.
     */
    private final double max_pressure;

    /**
     * Constructor.
     * It receives a parameter for the description and for the minimum and maximum pressures. It first makes sure that
     * these parameters are valid (the description can't be null and the minimum and maximum must be positive since we
     * are talking about pressure, also the maximum must be greater than the minimum). After that, it assigns the value of
     * these parameters to the corresponding attributes.
     * @param s It contains the description of the tyre.
     * @param d1 It contains the minimum pressure.
     * @param d2 It contains the maximum pressure.
     */
    public TyreType(String s, double d1, double d2) {
        if (s == null || d1 < 0 || d2 < 0 || d1 > d2)
            throw new IllegalArgumentException("The variables have not valid values\n");
        this.description = s;
        this.min_pressure = d1;
        this.max_pressure = d2;
    }

    /**
     * Copy constructor.
     * It receives as parameter an object of the same class and then it assigns the values of this objects' attributes to the
     * corresponding attributes in the one that is being created. Since when we create a new object with data parameters we check
     * that this parameters are correct, as we saw in the previous constructor, when we receive an object in this method we assume
     * that its data has no errors, so it is not necessary to check it again.
     * @param tyre It contains the object that we are going to copy.
     */
    public TyreType(TyreType tyre) {
    	this(tyre.description, tyre.min_pressure, tyre.max_pressure);
    }

    /**
     * Instance method.
     * It returns the value of the minimum pressure of the tyre. Since there is no way to modify this value once the object is
     * created, it is not necessary to return a copy, so it just accesses the value directly.
     * @return Minimum pressure value allowed.
     */
    public double getMinPressure() {
        return min_pressure;		
    }

    /**
     * Instance method.
     * It returns the value of the maximum pressure of the tyre. Since there is no way to modify this value once the object is
     * created, it is not necessary to return a copy, so it just accesses the value directly.
     * @return Maximum pressure value allowed.
     */
    public double getMaxPressure() {
        return max_pressure;		
    }

    /**
     * Instance method.
     * It prints a message displaying the information of the tyre, following the format "TyreType description [min,max]", where
     * description, min and max correspond to the three attributes of the class. In order to simplify the syntax of this method,
     * it uses a return followed by the string containing the message in the mentioned format.
     * @return The message with the information of the tyre.
     */
    public String toString() {
        return "TyreType " + description + " [" + min_pressure + "," + max_pressure + "]";
    }

    /**
     * Instance method.
     * Its objective is to compare the current object with another one, which is passed as parameter, in order to figure out if
     * they are equal or not, that is, if all their attributes (description, min_pressure and max_pressure) are equal. For that,
     * it first checks out if the objects are the same, which would mean that the one passed as parameter is just a copy. Next, it
     * checks out if the object passed as parameter is null, in that case it wouldn't be equal to ours. Then it checks if they are
     * from the same class or not, and finally it compares their attributes.
     * @param obj The object that is going to be compared with the current one.
     * @return true if the objects are equal, false otherwise.
     */
    public boolean equals(Object obj) {
        if (this == obj)
            return true;
        if (obj == null)
            return false;
        if (getClass() != obj.getClass())
            return false;
        TyreType other = (TyreType) obj;
        return Objects.equals(description, other.description)
                && Double.doubleToLongBits(max_pressure) == Double.doubleToLongBits(other.max_pressure)
                && Double.doubleToLongBits(min_pressure) == Double.doubleToLongBits(other.min_pressure);
    }
}





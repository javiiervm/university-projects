package es.ua.dlsi.prog3.p2.model;

import es.ua.dlsi.prog3.p2.exceptions.NoTyreTypeException;
import es.ua.dlsi.prog3.p2.exceptions.PressureWheelException;

/** Wheel class from practice 2 (Subject: Programming 3)
 * @author 
 */

/**
 * This class represents a wheel of the car. It stores the pressure of the tyre, as well as its type, which is an object of class
 * TyreType. Apart from the constructors, it has a method that can set a new tyretype to the wheel, as well as change its pressure.
 * It also has a method that returns the tyretype of the wheel.
 * Unlike TyreType, this class doesn't need to be immutable, so it is not declared as final. The pressure attribute is modifiable, so
 * it is accessed directly instead of doing so through defensive copy. Since the tyreType attribute is an object of class TyreType and
 * this class is immutable, it is not necessary to take any caution like defensive copy because this class is already designed to avoid
 * any modification, so this attribute can be accessed directly too.
 */
class Wheel {
	/**
	 * Instance attribute.
	 * It stores the pressure of the wheel, which is a double value that must follow the minimum and maximum restrictions established
	 * by the corresponding tyreType attribute.
	 */
    private double pressure;
    
    /**
     * Instance attribute.
     * This attribute is an object of class tyreType that stores the information about the wheel's tyre. As we saw before, this
     * information includes a description of the tyre and its pressure limits.
     */
    private TyreType tyreType;

    /**
     * Default constructor.
     * This constructor doesn't receive any parameter, so it initializes the new object with some default values, which are zero for
     * the pressure and null for the tyreType. These attributes can be modified later by the corresponding methods.
     */
    public Wheel() {
        this.pressure = 0;
        this.tyreType = null;
    }

    /**
     * Parameterized constructor.
     * This constructor receives a tyre parameter, so it initializes the new object's TyreType assigning the same value as the one
     * received as parameter. As well as the default constructor, it assigns 0 as initial value for the pressure. The attributes 
     * can be modified later by the corresponding methods.
     * @param tyre The TyreType that is going to be copied in the attribute of the new object.
     */
    public Wheel(TyreType tyre) {
        this.pressure = 0;
        this.tyreType = tyre;
    }

    /**
     * Copy constructor.
     * It receives as parameter an object of the same class and then it assigns the values of this objects' attributes to the
     * corresponding attributes in the one that is being created. Since when we create a new object with data parameters or modify
     * the values of the attributes we check those values are correct, when we receive an object in this method we assume that its
     * data has no errors, so it is not necessary to check it again.
     * @param wheel The object that is going to be copied.
     */
    public Wheel(Wheel wheel) {
        this.pressure = wheel.pressure;
        this.tyreType = wheel.tyreType;
    }


    /**
     * Instance method.
     * It receives a new TyreType as parameter and assigns it to the corresponding attribute of our objects. This allows to change
     * properties such as the minimum and maximum pressure allowed for the wheel. Since the parameter is an object of class
     * TyreType and we already check its data in the constructors of its class, we assume that this parameter's data is correct so
     * we don't check it again.
     * @param tyre The TyreType object that is going to be copied in the corresponding parameter of our wheel.
     */
    public void setTyreType(TyreType tyre) {
        this.tyreType = tyre;
    }

    /**
     * Instance method.
     * It returns the tyre type of our wheel object. Since the TyreType class is immutable, we can access it directly, there's no
     * need to use a defensive copy because there is no way to modify its values. 
     * @return The tyre type of our wheel object.
     */
    public TyreType getTyreType() {
    	return this.tyreType;
    }

    /**
     * Instance method.
     * This method changes the pressure of the wheel, but first it makes sure that the value of this new pressure is correct. For
     * that, it checks out some conditions and throws an exception if it detects any error.
     * First, it checks that the new pressure is above zero, because it is impossible to have a negative pressure. In case the
     * parameter is negative, it throws an IllegalArgumentException.
     * Then, it checks if the tyreType of our wheel is null. Since the pressure of the wheel must be inside a rank of values, we need
     * to know the information about which is the minimum and maximum value allowed. If tyreType is null we don't have this information,
     * so the pressure can't be modified and it throws NoTyreTypeException.
     * Finally, it checks it the pressure is inside the valid values rank of the tyre type, and throws PressureWheelException if not.
     * If everything is correct, it asssigns the new pressure to the corresponding attribute of the wheel object.
     * @param d New pressure that we want to assign to the pressure attribute of the wheel.
     * @throws NoTyreTypeException Means that tyreType is null so we can't check if the new pressure is valid.
     * @throws PressureWheelException Means that the pressure passed as parameter is not valid.
     */
    public void inflate(double d) throws NoTyreTypeException, PressureWheelException {
        if (d < 0)
            throw new IllegalArgumentException("Pressure can't be negative!\n");
        else if (this.tyreType == null)
            throw new NoTyreTypeException("This wheel has no Tyre Type assigned!\n");
        else if (d < this.tyreType.getMinPressure() || d > this.tyreType.getMaxPressure())
            throw new PressureWheelException(d);
        this.pressure = d;
    }
}





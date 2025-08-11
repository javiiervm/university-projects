package es.ua.dlsi.prog3.p2.model;

import java.util.ArrayList;

import es.ua.dlsi.prog3.p2.exceptions.NoTyreTypeException;
import es.ua.dlsi.prog3.p2.exceptions.PressureWheelException;
import es.ua.dlsi.prog3.p2.exceptions.TooManyWheelsException;
import es.ua.dlsi.prog3.p2.exceptions.WrongTyreTypeException;

/** Car class from practice 2 (Subject: Programming 3)
 * @author 
 */

/**
 * This class represents a a car. It stores all its wheels in an arraylist and has methods that allow to add a new wheel to the car,
 * change the tyres of the car's wheels, or get a full list of this wheels. Since a car cannot have more than four wheels, a constant
 * with this value is created to make sure that the arraylist doesn't surpass that number of wheels. 
 * Unlike TyreType, this class doesn't need to be immutable, so it is not declared as final. The arraylist is modifiable but just in some
 * particular cases, so it is mostly accessed through defensive copy in order to protect its data.
 */
class Car {
	/**
	 * Class attribute.
	 * It defines the maximum number of wheels the car can have, that is, the maximum size the arraylist can get. Since it is a constant,
	 * its name is in uppercase, according to Java's conventions.
	 */
    private final static int MAX = 4;
    
    /**
     * Instance attribute.
     * It stores a list of all the car's wheels. It can't have more than four wheels, that is managed using the MAX attribute.
     */
    private ArrayList<Wheel> wheels;

    /**
     * Default constructor.
     * This constructor doesn't receive any parameter, so it initializes the new object's wheel list with an empty arraylist of
     * type Wheel, since it is going to store objects of the wheel class. We can add items to this list later through the corresponding
     * methods as well as we don't surpass the limit established in the MAX attribute.
     */
    public Car() {
        this.wheels = new ArrayList<Wheel>();
    }

    /**
     * Copy constructor.
     * It receives as parameter an object of the same class and then it assigns the values of this objects' attributes to the
     * corresponding attributes in the one that is being created. Since when we create a new object with data parameters or modify
     * the values of the attributes we check those values are correct, when we receive an object in this method we assume that its
     * data has no errors, so it is not necessary to check it again.
     * In order to protect the data and avoid errors when copying values, we first assign an empty arraylist to the wheels attribute
     * of the car, and then we use a for loop to copy every wheel of the parameter object in the new arraylist, for that we use
     * defensive copy.
     * @param car The object that is going to be copied.
     */
    public Car(Car car) {
        this.wheels = new ArrayList<Wheel>();
        for (Wheel wheel : car.wheels)
            this.wheels.add(new Wheel(wheel));
    }

    /**
     * Instance method.
     * It adds to the arraylist the wheel passed as parameter, as wheel as there are less than 4 wheels and the wheel in the parameter
     * is correct. It first checks if the wheel is null and rejects it, then it checks that there is enough space in the arraylist
     * comparing its size with the MAX attribute. In case there is no space for a new wheel, it throws TooManyWheelsException.
     * Then it checks if the wheel passed as parameter is the same type as the first one in the arraylist (we assume that every wheel
     * in the arraylist is equal to the rest of them so should be enough to compare the first one). In case they are different, it throws
     * WrongTyreTypeException.
     * If everything is correct, it adds the wheel to the list using defensive copy to avoid any error with the data.
     * @param wheel The wheel that is going to be added to the arraylist.
     * @throws TooManyWheelsException Means that the arraylist has already the maximum amount of wheels allowed.
     * @throws WrongTyreTypeException Means that the wheel passed as parameter has a different tyre than the ones that are already in the
     * arraylist.
     */
    public void addWheel(Wheel wheel) throws TooManyWheelsException, WrongTyreTypeException {
    	if(wheel==null)
    		return;
        if(wheels.size() == MAX)
            throw new TooManyWheelsException("Can't add more wheels to the car! Maximum number of wheels is " + ((Integer)MAX).toString());
        if(!this.wheels.isEmpty())
	        if(this.wheels.get(0).getTyreType() != wheel.getTyreType())
	        		throw new WrongTyreTypeException("Tyre type mismatch! All wheels must have the same tyre type!");
        this.wheels.add(new Wheel(wheel));
    }

    /**
     * Instance method.
     * It has to return the wheel arraylist of the car, but in order to protect the data it uses defensive copy, that is, it returns
     * a copy of this array. For that, it first creates an empty arraylist, and then uses a for loop to iterate over the object's arraylist,
     * and adds to the new one a copy of each object stored. All of that after checking out that there are items inside the arraylist.
     * It then returns the copied arraylist.
     * @return An arraylist which is a copy of the wheel arraylist of the car.
     */
    public ArrayList<Wheel> getWheels() {
        ArrayList<Wheel> copylist = new ArrayList<Wheel>();
        if(!(this.wheels.isEmpty()))
	        for(Wheel wheel : this.wheels)
	        	copylist.add(new Wheel(wheel));
        return copylist;
    }

    /**
     * Instance method.
     * Its objective is to change the tyres of every wheel stored in the car's arraylist. For that, it receives two parameters, a tyre type
     * and a pressure, which are the new values the wheels are going to have. It first has to make sure that the tyre passed as parameter
     * is not null, otherwise it throws IllegalArgumentException. Then, it iterates over every wheel in the arraylist and sets the tyre type
     * and pressure to the values from the parameters. For that, it uses the methods setTyreType() and inflate(). If we remember, these
     * methods can throw exceptions, so we must catch them, that's why this method has a catch for every possible exception. Each catch
     * throws the exception again so it can be treated properly in the corresponding client code.
     * @param tyre The new tyre type for the wheels.
     * @param pressure The new pressure for the wheels.
     * @throws PressureWheelException Means that the pressure is invalid.
     * @throws RuntimeException It is any other exception that can be thrown.
     */
    public void changeTyres(TyreType tyre, double pressure) throws PressureWheelException, RuntimeException {
        if (tyre == null)
            throw new IllegalArgumentException("The tyre parameter can't be null\n");
        try {
            for (Wheel wheel : wheels) {
            	wheel.setTyreType(tyre);
                wheel.inflate(pressure);
            }
        } catch (PressureWheelException e) {
            throw new PressureWheelException(pressure);
        } catch (NoTyreTypeException e) {
            throw new IllegalArgumentException("ERROR");
        } catch (IllegalArgumentException e) {
        	throw new RuntimeException("ERROR");
        }
    }

}







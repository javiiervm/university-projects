package es.ua.dlsi.prog3.p2.exceptions;

/**
 * This class is created to manage an exception declared by the user, that means, it doesn't exist outside this project.
 * This exception is thrown when the pressure parameter is not valid. It prints an error
 * message, which is managed by the corresponding method with a catch function.
 */
public class PressureWheelException extends Exception {
	/**
	 * Instance attribute.
	 * It stores a pressure value.
	 */
    private double pressure;
    
    /**
	 * Constructor.
	 * It receives as a parameter a pressure value and it assigns it to the pressure attribute.
	 * @param pressure The value that has to be stored.
	 */
    public PressureWheelException(double pressure) {
        this.pressure = pressure;
    }
    
    /**
	 * Instance method.
	 * It returns an error message that includes the value of the pressure attribute.
	 * @return The error message.
	 */
    public String getMessage() {
        return "Pressure of " + pressure + " BAR";
    }
}

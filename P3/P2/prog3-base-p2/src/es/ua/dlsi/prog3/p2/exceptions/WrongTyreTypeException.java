package es.ua.dlsi.prog3.p2.exceptions;

/**
 * This class is created to manage an exception declared by the user, that means, it doesn't exist outside this project.
 * This exception is thrown when a tyre type is different from the one expected.
 * It prints an error message, which is managed by the corresponding method with a catch function.
 */
public class WrongTyreTypeException extends Exception {
	/**
	 * Instance attribute.
	 * It stores the error message that is going to be printed when this exception appears in the code.
	 */
	private String msg;

	/**
	 * Constructor.
	 * It receives as a parameter an string with the error message that the method where the exception is thrown passes, prints it
	 * and then stores this message in the msg attribute.
	 * @param msg Error message that is going to be printed.
	 */
	public WrongTyreTypeException(String msg) {
		super(msg);
		this.msg = msg;
	}

	/**
	 * Instance method.
	 * It returns the error message stored in the msg attribute. There is no need to perform defensive copy so it accesses it directly.
	 * @return The error message.
	 */
	public String getMessage() {
		return msg;
	}
}
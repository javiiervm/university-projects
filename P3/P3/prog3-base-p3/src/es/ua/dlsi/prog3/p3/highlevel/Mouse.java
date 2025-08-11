package es.ua.dlsi.prog3.p3.highlevel;

import java.nio.BufferOverflowException;

import es.ua.dlsi.prog3.p3.lowlevel.InputDevice;

/**
 * This class represents an Mouse device, which is an InputDevice, so it extends the InputDevice class and inherits
 * all its attributes and methods. 
 * It also implements some methods to manage the device's properties.
 * @author 
 */
public class Mouse extends InputDevice {
	/**
	 * Constructor.
	 * It creates a new Mouse instance.
	 * For that, it calls the constructor of the parent class, InputDevice.
	 */
	public Mouse() {
		super();
	}
	
	/**
	 * Instance method.
	 * This method receives two bytes as parameters that represent coordinates, and sends them to the channel, that is, we want to add
	 * the data passed as parameters. In order to do that, it creates a byte array which stores x and y and then calls the put(byte[])
	 * method of the parent class and sends it the array.
	 * @param x Coordinate x.
	 * @param y Coordinate y.
	 * @throws IllegalStateException If the device has no associated channel.
	 * @throws BufferOverflowException If the chhanel is already full.
	 */
	public void put(byte x, byte y) throws IllegalStateException, BufferOverflowException {
		byte[] bytes = {x, y};
		put(bytes);
	}
}
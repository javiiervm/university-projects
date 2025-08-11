package es.ua.dlsi.prog3.p3.highlevel;

import java.nio.BufferOverflowException;

import es.ua.dlsi.prog3.p3.lowlevel.InputDevice;

/**
 * This class represents a Keyboard device, which is an InputDevice, so it extends the InputDevice class and inherits
 * all its attributes and methods. 
 * It also implements some methods to manage the device's properties.
 * @author 
 */
public class Keyboard extends InputDevice {
	/**
	 * Constructor.
	 * It creates a new Keyboard instance.
	 * For that, it calls the constructor of the parent class, InputDevice.
	 */
	public Keyboard() {
		super();
	}
	
	/**
	 * Instance method.
	 * This method receives a character as parameter and sends them to the channel, that is, we want to add the data passed as 
	 * parameters. In order to do that, it calls the sendToChannel() method of the parent class, but it has to convert the character 
	 * into a byte, because the channel has the data stored in bytes.
	 * @param c The character we want to add to the channel data.
	 * @throws IllegalStateException If the device has no associated channel.
	 * @throws BufferOverflowException If the channel is already full.
	 */
	public void put(char c) throws IllegalStateException, BufferOverflowException {
		sendToChannel((byte)c);
	}
}
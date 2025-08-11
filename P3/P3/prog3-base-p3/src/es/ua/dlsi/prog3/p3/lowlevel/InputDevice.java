package es.ua.dlsi.prog3.p3.lowlevel;

/**
 * This class represents an input device.
 * It also implements some methods to be able to manage the channels
 * this device is connected to, as well as insert new bytes of data.
 * @author 
 */
public class InputDevice extends IODevice {
	/**
	 * Constructor.
	 * It creates a new InputDevice instance.
	 * For that, it calls the constructor of the parent class, IODevice.
	 */
	protected InputDevice() {
		super();
	}
	
	/**
	 * Instance method.
	 * This method receives a byte as a parameter, and its objective is to send it to the channel associated
	 * to the input device object. For that, it first creates a channel variable that stores the corresponding channel by
	 * calling the getChannel() method (from the IODevice class) to obtain it, and after that it sends the byte to the channel
	 * by calling input(byte), a method from the superparent class Channel.
	 * @param b The byte that is going to be sent to the channel.
	 */
	public void sendToChannel(byte b) {
		Channel channel = getChannel();
		channel.input(b);
	}
	
	/**
	 * Instance method.
	 * This method receives a byte array as a parameter, and its objective is to send it to the channel associated
	 * to the input device object. For that, it first creates a channel variable that stores the corresponding channel by
	 * calling the getChannel() method (from the IODevice class) to obtain it, and after that it sends the bytes to the channel
	 * by calling input(byte), a method from the superparent class Channel.
	 * @param b The array of bytes that are going to be sent to the channel.
	 */
	public void put(byte b[]) {
		Channel channel = getChannel();
		for(byte bb : b)
			channel.input(bb);
	}
}
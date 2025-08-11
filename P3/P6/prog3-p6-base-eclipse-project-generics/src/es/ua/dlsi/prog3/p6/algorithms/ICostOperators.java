package es.ua.dlsi.prog3.p6.algorithms;

public interface ICostOperators<T> {
	public T add(T t1, T t2);
	public T zero();
	public T maximumValue();
}
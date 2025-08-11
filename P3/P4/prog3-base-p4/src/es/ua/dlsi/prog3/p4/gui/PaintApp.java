package es.ua.dlsi.prog3.p4.gui;

import java.util.ArrayList;
import java.util.List;

import es.ua.dlsi.prog3.p4.model.Canvas;
import es.ua.dlsi.prog3.p4.model.Circle;
import es.ua.dlsi.prog3.p4.model.Coordinate;
import es.ua.dlsi.prog3.p4.model.Rectangle;
import es.ua.dlsi.prog3.p4.model.Shape2D;
import es.ua.dlsi.prog3.p4.model.Shape2DFactory;

/** 
 * This class is a small program that acts as client code for 
 * es.ua.dlsi.prog3.p4.model.*
 * @author pierre
 * @date 24/10/2022
 **/
public class PaintApp {
	
	private Canvas lienzo;
	
	/**
	 * Executes some code using the Shape2D hierarchy
	 */
	public void ejecutar() {
		lienzo = new Canvas("Prog 3", 1024.0,768.0);
		List<Circle> circles = new ArrayList<>();
		circles.add(new Circle());
		circles.add(new Circle(new Coordinate(10.0, 20.0), 5.0));
		circles.add(new Circle(new Coordinate(15.0, 25.0), 7.0));
		circles.add(new Circle((Circle)circles.get(2)));
		
		List<Rectangle> rectangles = new ArrayList<>();
		rectangles.add(new Rectangle());
		rectangles.add(new Rectangle(new Coordinate(10.0, 20.0), 0, 5.0, 2.5));
		rectangles.add(new Rectangle(new Coordinate(15.0, 25.0), 0, 7.0, 3.5));
		rectangles.add(new Rectangle((Rectangle)rectangles.get(2)));

		List<Shape2D> shapes = new ArrayList<>();
		shapes.add(Shape2DFactory.createShape2D("Circle", new Coordinate(20.0,30.0), 3.0));
		shapes.add(Shape2DFactory.createShape2D("Rectangle", new Coordinate(20.0,30.0), 45.0, 3.0, 5.0));

		for (Shape2D c : circles) 
			lienzo.addShape(c);
		for (Shape2D c : rectangles) 
			lienzo.addShape(c);
		for (Shape2D c : shapes) 
			lienzo.addShape(c);
		
		System.out.println(lienzo.toString());
		System.out.println(circles);
		System.out.println(rectangles);
		System.out.println(shapes);
	}	
	
	/**
	 * Main program
	 * @param args no args are needed
	 */
	public static void main(String args[])  {
		new PaintApp().ejecutar();
	}
}

package es.ua.dlsi.prog3.p5.model;

import es.ua.dlsi.prog3.p5.export.IExporter;

public class StrikeThroughDecorator extends AbstractTextDecorator {
	public StrikeThroughDecorator(IText text) {
		super(text);
	}

	@Override
	public String export(IExporter exporter) {
		return exporter.export(this);
	}
}
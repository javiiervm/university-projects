package es.ua.dlsi.prog3.p5.model;

import es.ua.dlsi.prog3.p5.export.IExporter;

import java.util.List;

public class Quote extends Paragraph {
    public Quote(List<IParagraphContent> paragraphContentList) {
        super(paragraphContentList);
    }

    public Quote(IParagraphContent ... paragraphContents) {
        super(paragraphContents);
    }

    @Override
    public String export(IExporter exporter) {
        return exporter.export(this);
    }
}

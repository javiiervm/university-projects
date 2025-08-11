package es.ua.dlsi.prog3.p5.client;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

import java.io.IOException;
import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.net.URISyntaxException;
import java.net.URL;
import java.nio.file.Files;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.junit.Before;
import org.junit.Test;

import es.ua.dlsi.prog3.p5.export.html.HTMLExporter;
import es.ua.dlsi.prog3.p5.export.markdown.MarkdownExporter;
import es.ua.dlsi.prog3.p5.model.AbstractTextDecorator;
import es.ua.dlsi.prog3.p5.model.BoldTextDecorator;
import es.ua.dlsi.prog3.p5.model.CodeBlock;
import es.ua.dlsi.prog3.p5.model.Document;
import es.ua.dlsi.prog3.p5.model.Heading;
import es.ua.dlsi.prog3.p5.model.HorizontalRule;
import es.ua.dlsi.prog3.p5.model.IDocumentElement;
import es.ua.dlsi.prog3.p5.model.IParagraphContent;
import es.ua.dlsi.prog3.p5.model.Image;
import es.ua.dlsi.prog3.p5.model.ItalicsTextDecorator;
import es.ua.dlsi.prog3.p5.model.LinkParagraphContentDecorator;
import es.ua.dlsi.prog3.p5.model.OrderedListBlock;
import es.ua.dlsi.prog3.p5.model.Paragraph;
import es.ua.dlsi.prog3.p5.model.Quote;
import es.ua.dlsi.prog3.p5.model.StrikeThroughDecorator;
import es.ua.dlsi.prog3.p5.model.Text;

/**
 * This test evaluates the correct creation of an object hierarchy to represent a document
 * @author David Rizo - drizo@dlsi.ua.es
 * @created 31/10/22
 * @modified 11/11/24 - new test suite ExampleDocumentCreatorExportTest, export tests only
 */
public class ExampleDocumentCreatorExportTest {
    private Document document;
    

    private void compareResults(String fileWithExpectedContent, String result) {
        try {
            URL url = this.getClass().getResource(fileWithExpectedContent);
            if (url == null) {
                throw new RuntimeException("Cannot find file '" + fileWithExpectedContent + "'");
            }
            java.nio.file.Path path = java.nio.file.Paths.get(url.toURI());
            List<String> lines = Files.readAllLines(path);
            StringBuilder stringBuilder = new StringBuilder();
            for (String line : lines) {
                stringBuilder.append(line);
                stringBuilder.append('\n');
            }
            String fileContent = stringBuilder.toString().trim(); // trim to remove trailing spaces
            assertEquals(fileContent, result.trim());
        } catch (URISyntaxException | IOException e) {
            throw new RuntimeException("This should not fail", e);
        }
    }

    @Before
    public void setup()  {
        ExampleDocumentCreator exampleDocumentCreator = new ExampleDocumentCreator();
        document = exampleDocumentCreator.createExample();

    }

       
    @Test
    public void testHTML() {
        String html = document.export(new HTMLExporter());
        compareResults("example_document.html", html);
    }

    @Test
    public void testMarkdown() {
        String md = document.export(new MarkdownExporter());
        compareResults("example_document.md", md);
    }


}

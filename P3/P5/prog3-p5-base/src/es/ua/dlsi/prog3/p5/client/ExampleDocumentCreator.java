package es.ua.dlsi.prog3.p5.client;

import java.util.ArrayList;
import java.util.List;

import es.ua.dlsi.prog3.p5.model.*;

/**
 * This class is used for the evaluation of the assignment
 * @author David Rizo - drizo@dlsi.ua.es
 * @created 31/10/22
 */
public class ExampleDocumentCreator  {
    /**
     * --- IMPLEMENT this method ---
     * 
     * @return Document object
     */
    public Document createExample() {
        // Create new document
    	Document document = new Document();
    	
        try {
        	// <h1>Heading</h1>
        	document.add(new Heading("Heading", 1));
        	
        	// <p>Some text to introduce the article</p>
        	document.add(new Paragraph(new Text("Some text to introduce the article")));
        	
        	// <a href='https://www.somesite.edu'>original cite site</a>
        	LinkParagraphContentDecorator link = new LinkParagraphContentDecorator(new Text("original cite site"), "https://www.somesite.edu");
        	// <blockquote>Something someone said:link</blockquote>
        	document.add(new Quote(new Text("Something someone said:"), link));
        	
        	// <h2>First section</h2>
        	document.add(new Heading("First section", 2));
        	
        	// <p>Example of text decorators:</p>
        	document.add(new Paragraph(new Text("Example of text decorators:")));
        	
        	// <ol>
        	List<IBlock> list = new ArrayList<>();
        	// <li>Raw text</li>
        	list.add(new Text("Raw text"));
        	// <li><em>Italics</em></li>
        	list.add(new ItalicsTextDecorator(new Text("Italics")));
        	// <li><strong>Bold</strong></li>
        	list.add(new BoldTextDecorator(new Text("Bold")));
        	// <li><del>Strike through</del></li>
        	list.add(new StrikeThroughDecorator(new Text("Strike through")));
        	// <li><em><strong><del>The three above</del></strong></em></li>
        	list.add(new ItalicsTextDecorator(new BoldTextDecorator(new StrikeThroughDecorator(new Text("The three above")))));
        	// <li><p>Raw text inside a paragraph</p></li>
        	list.add(new Paragraph(new Text("Raw text inside a paragraph")));
        	// </ol>
        	document.add(new OrderedListBlock(list));

        	// <h3>Code block</h3>
        	document.add(new Heading("Code block", 3));
        	
        	// <pre>class PROG3 {}</pre>
        	document.add(new CodeBlock("class PROG3 {}", "java"));
        	
        	// <hr>
        	document.add(new HorizontalRule());
        	
        	// <img src='https://web.ua.es/secciones-ua/images/layout/logo-ua.jpg' alt='UA logo'/>
        	Image image = new Image("https://web.ua.es/secciones-ua/images/layout/logo-ua.jpg", "UA logo");
        	// <p>image</p>
        	document.add(new Paragraph(image));
        	
        	// Return the created document
        	return document;
        } catch (EditorException e) {
        	// Catch EditorException and throw as RuntimeException
        	throw new RuntimeException();
        }
    }
}

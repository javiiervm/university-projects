package es.ua.dlsi.prog3.p5.client;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.junit.Before;
import org.junit.Test;

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
 */
public class ExampleDocumentCreatorTest {
    private Document document;
	private List<IDocumentElement> items;

	private static Object item_contents[][] = {
			{"Heading","Heading",1},
			{"Paragraph","Some text to introduce the article"},
			{"Quote","Text","Something someone said:","LinkParagraphContentDecorator","original cite site","https://www.somesite.edu"},
			{"Heading","First section", 2},
			{"Paragraph","Example of text decorators:"},
			{"Heading","Code block", 3},
			{"Paragraph","Image", "https://web.ua.es/secciones-ua/images/layout/logo-ua.jpg", "UA logo"}
	};
		
	private static Map<String, Constructor<?>> ctors= new HashMap<>();
	private static List<IDocumentElement> expected_items = new ArrayList<>();
	
    private void setup_ctors() {
    	try {
    		Class<Heading> classh = (Class<Heading>) Class.forName("es.ua.dlsi.prog3.p5.model.Heading");
    		ctors.put("Heading", classh.getConstructor(String.class, int.class));
    		Class<Paragraph> classp = (Class<Paragraph>) Class.forName("es.ua.dlsi.prog3.p5.model.Paragraph");
    		ctors.put("Paragraph",  classp.getConstructor(List.class));
    		Class<Quote> classq = (Class<Quote>) Class.forName("es.ua.dlsi.prog3.p5.model.Quote");
    		ctors.put("Quote",  classq.getConstructor(List.class));
    		Class<Text> classt = (Class<Text>) Class.forName("es.ua.dlsi.prog3.p5.model.Text");
    		ctors.put("Text", classt.getConstructor(String.class));
    		Class<Image> classi = (Class<Image>) Class.forName("es.ua.dlsi.prog3.p5.model.Image");
    		ctors.put("Image",  classi.getConstructor(String.class,String.class));
    		Class<LinkParagraphContentDecorator> classl = (Class<LinkParagraphContentDecorator>) Class.forName("es.ua.dlsi.prog3.p5.model.LinkParagraphContentDecorator");
    		ctors.put("LinkParagraphContentDecorator",  classl.getConstructor(IParagraphContent.class,String.class));
    	} catch(Exception e) {
			e.printStackTrace();
            throw new RuntimeException("This exception should never happen", e);    		
    	}
	}
    
    private boolean compareHeadings(Heading h1, Heading h2) {
    	return h1.getLevel() == h2.getLevel() && h1.getText().equals(h2.getText());    	
    }
    
    private boolean compareParagraphs(Paragraph p1, Paragraph p2) {
    	return p1.getItems().length==p2.getItems().length;
    }

    private boolean compareTexts(Text t1, Text t2) {
    	return t1.getText().equals(t2.getText());
    }

	private boolean compareQuotes(Quote q1, Quote quote2) {
		return q1.getItems().length==quote2.getItems().length;
	}


    @Before
    public void setup()  {
        ExampleDocumentCreator exampleDocumentCreator = new ExampleDocumentCreator();
        document = exampleDocumentCreator.createExample();

        try {
        	Class<?> clazz = document.getClass().getSuperclass();
        	
        	Field itemsField = clazz.getDeclaredField("items");
        	itemsField.setAccessible(true);
        	items = (List<IDocumentElement>) itemsField.get(document);

        	setup_ctors(); 
        	Constructor<?> ctor1 = null;
        	Constructor<?> ctor2 = null;
        	Constructor<?> ctor3 = null;
        	for (Object[] content : item_contents) {
        		switch (content.length) {
        		case 2:
        			ctor1 = ctors.get(content[0]);
        			ctor2 = ctors.get("Text");
        			List<IParagraphContent> args = new ArrayList<>();
        			args.add((Text)ctor2.newInstance((String)content[1]));
        			expected_items.add((IDocumentElement)ctor1.newInstance(args));
        			break;
        		case 3:
        			ctor1 = ctors.get(content[0]);
        			expected_items.add((IDocumentElement)ctor1.newInstance((String)content[1], (int)content[2]));
        			break;
        		case 4:
        			ctor1 = ctors.get(content[0]);
        			ctor2 = ctors.get("Image");
        			args = new ArrayList<>();
        			args.add((Image)ctor2.newInstance((String)content[2],(String)content[3]));
        			expected_items.add((IDocumentElement)ctor1.newInstance(args));
        			break;
        		case 6:
        			ctor1 = ctors.get(content[0]);
        			ctor2 = ctors.get("Text");
        			ctor3 = ctors.get("LinkParagraphContentDecorator");
        			args = new ArrayList<>();
        			args.add((Text)ctor2.newInstance((String)content[2]));
        			args.add((LinkParagraphContentDecorator)ctor3.newInstance(new Text((String)content[4]), (String)content[5]));

        			expected_items.add((IDocumentElement)ctor1.newInstance(args));
        			break;
        		}	
        	}
            
        } catch (Exception e) {
			e.printStackTrace();
            throw new RuntimeException("This exception should never happen", e);
		}
    }

    

    /*
     * Tests '#Heading'
     */
	@Test
    public void testHeading1() throws NoSuchFieldException, SecurityException, IllegalArgumentException, IllegalAccessException {
    	assertTrue("Heading 1",compareHeadings((Heading)expected_items.get(0), (Heading)items.get(0)));
    	
    }
    
	/*
	 * Tests paragraph 'Some text to introduce the article'
	 */	
    @Test
    public void testParagraph1() {
    	Paragraph par1 = (Paragraph) items.get(1);
    	Paragraph expected_par = (Paragraph)expected_items.get(1);
    	assertTrue(compareParagraphs(par1, expected_par));
    	Text t1 = (Text) par1.getItems()[0];
    	Text t2 = (Text) expected_par.getItems()[0];
    	assertTrue(compareTexts(t1, t2));
    }
   
    /*
     * Tests quote '>Something someone said:[original cite site](https://www.somesite.edu)'
     */
    @Test
    public void testQuote() {
    	Quote q1 = (Quote) items.get(2);
    	Quote expected_quote = (Quote)expected_items.get(2);
    	assertTrue(compareQuotes(q1, expected_quote));
    	IDocumentElement[] elements = q1.getItems();
    	assertTrue(elements[0] instanceof Text);
    	assertTrue(elements[1] instanceof LinkParagraphContentDecorator);
    	Text t1 = (Text) elements[0];
    	Text t2 = (Text) expected_quote.getItems()[0];
    	assertTrue(compareTexts(t1, t2));
    }

    /*
     * Tests heading '##First section'
     */
    @Test
    public void testHeading2() throws NoSuchFieldException, SecurityException, IllegalArgumentException, IllegalAccessException {
    	assertTrue("Heading 2",compareHeadings((Heading)expected_items.get(3), (Heading)items.get(3)));
    }

    /*
     * Tests paragraph 'Example of text decorators:'
     */
    @Test
    public void testParagraph2() {
    	Paragraph par1 = (Paragraph) items.get(4);
    	Paragraph expected_par = (Paragraph)expected_items.get(4);
    	assertTrue(compareParagraphs(par1, expected_par));
    	Text t1 = (Text) par1.getItems()[0];
    	Text t2 = (Text) expected_par.getItems()[0];
    	assertTrue(compareTexts(t1, t2));
    }
    
    /*
     * Tests ordered list:
     * 1. Raw text
	 * 2. *Italics*
	 * 3. **Bold**
	 * 4. ~~Strike through~~
	 * 5. ***~~The three above~~***
	 * 6. Raw text inside a paragraph
     */
    @Test
    public void testOrderedListBlock() {
    	OrderedListBlock olb = (OrderedListBlock) items.get(5);
    	IDocumentElement[] elements = olb.getItems();
    	assertTrue(elements[0] instanceof Text);
    	assertTrue(elements[1] instanceof ItalicsTextDecorator);
    	assertTrue(elements[2] instanceof BoldTextDecorator);
    	assertTrue(elements[3] instanceof StrikeThroughDecorator);
    	assertTrue(elements[4] instanceof ItalicsTextDecorator);
    	assertTrue(elements[5] instanceof Paragraph);
    	
    	ItalicsTextDecorator italics = (ItalicsTextDecorator) elements[4];
    	assertTrue(italics.getDecoratedElement() instanceof BoldTextDecorator);
    	AbstractTextDecorator decorator = (AbstractTextDecorator) italics.getDecoratedElement();
    	assertTrue(decorator.getDecoratedElement() instanceof StrikeThroughDecorator);
    	decorator = (AbstractTextDecorator) decorator.getDecoratedElement();
    	assertTrue(decorator.getDecoratedElement() instanceof Text);

    }

    /*
     * Tests heading '###Code block'
     */
    @Test
    public void testHeading3() throws NoSuchFieldException, SecurityException, IllegalArgumentException, IllegalAccessException {
    	assertTrue("Heading 3",compareHeadings((Heading)expected_items.get(5), (Heading)items.get(6)));
    }

    /*
     * Tests code block:
     * ```java
	 * class PROG3 {}
	 * ```
     */
    @Test
    public void testCodeblock() {
    	assertTrue(items.get(7) instanceof CodeBlock);
    	CodeBlock cb = (CodeBlock) items.get(7);
    	assertEquals("CodeBlock","java",cb.getLanguage());
    }
    
    /*
     * Tests horizontal rule
     */
    @Test
    public void testHRule() {
    	assertTrue(items.get(8) instanceof HorizontalRule);    	
    }
    
    /*
     * Tests paragraph '![UA logo](https://web.ua.es/secciones-ua/images/layout/logo-ua.jpg)'
     */
    @Test
    public void testParagraph3() {
    	Paragraph par1 = (Paragraph) items.get(9);
    	Paragraph expected_par = (Paragraph)expected_items.get(6);
    	assertTrue(compareParagraphs(par1, expected_par));
    	assertTrue(par1.getItems()[0] instanceof Image);
    	Image img = (Image) par1.getItems()[0];
    	assertTrue(img.hasAlt());
    }


}

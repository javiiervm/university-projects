package es.ua.dlsi.prog3.p5.client;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

import org.junit.Test;

import es.ua.dlsi.prog3.p5.model.AbstractTextContent;
import es.ua.dlsi.prog3.p5.model.EditorException;
import es.ua.dlsi.prog3.p5.model.Heading;
import es.ua.dlsi.prog3.p5.model.Image;
import es.ua.dlsi.prog3.p5.modifiers.ITextCaseModifiable;
import es.ua.dlsi.prog3.p5.modifiers.ITextCaseModifier;

/**
 * @author David Rizo - drizo@dlsi.ua.es
 * @created 31/10/22
 */
public class TextsToUpperCaseTest {

    @Test
    public void testImageImplementsITextCaseModifiable() {
        Class<?> clazz = Image.class;
        assertTrue(ITextCaseModifiable.class.isAssignableFrom(clazz));
    }

    @Test
    public void testAbstractTextContentImplementsITextCaseModifiable() {
        Class<?> clazz = AbstractTextContent.class;
        assertTrue(ITextCaseModifiable.class.isAssignableFrom(clazz));
    }

    @Test
    public void changeTextsInImage() {
        Image image = new Image("img/dlsi.png", "Departamento de lenguajes y sistemas informáticos");
        TextsToUpperCase textsToUpperCase = new TextsToUpperCase();
        textsToUpperCase.changeTexts(image);
        assertEquals("DEPARTAMENTO DE LENGUAJES Y SISTEMAS INFORMÁTICOS", image.getAlt());
    }

    @Test
    public void changeTextsInAbstractTextContent() throws EditorException {
        Heading text = new Heading("This is a test", 1);
        TextsToUpperCase textsToUpperCase = new TextsToUpperCase();
        textsToUpperCase.changeTexts(text);
        assertEquals("THIS IS A TEST", text.getText());
    }

    @Test
    public void textAnonymousClass() {
        TextsToUpperCase textsToUpperCase = new TextsToUpperCase();
        ITextCaseModifier textModifier = textsToUpperCase.createTextModifier();
        assertTrue("Anonymous class", textModifier.getClass().isAnonymousClass());
    }
}

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cardreader;

import java.io.File;
import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import org.w3c.dom.Document;
import org.xml.sax.SAXException;

/**
 *
 * @author Stefan
 */
public class CardReader {

    public static void main(String argv[]) throws SAXException, IOException {

        try {
            File file = new File(System.getProperty("user.dir") + File.separator + "res"+ File.separator + "deck.xml");
            DocumentBuilderFactory documentBuilderFactory = DocumentBuilderFactory.newInstance();
            DocumentBuilder documentBuilder = documentBuilderFactory.newDocumentBuilder();
            Document document = documentBuilder.parse(file);
            
            
            String name = document.getElementsByTagName("Nme").item(0).getTextContent();
          //  String pwd = document.getElementsByTagName("password").item(0).getTextContent();
            
            
            System.out.println(name);
            
        } catch (ParserConfigurationException ex) {
            Logger.getLogger(CardReader.class.getName()).log(Level.SEVERE, null, ex);
        }

    }

}

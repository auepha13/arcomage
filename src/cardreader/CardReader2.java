/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cardreader;

import java.io.File;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import org.w3c.dom.Document;

/**
 *
 * @author Stefan
 */
public class CardReader2 {
    
    
    public static void main(String[] args) {
        
        
        try {

            File file = new File(System.getProperty("user.dir") + File.separator + "res"+ File.separator + "deck.xml");
            
            DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
            DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
            Document doc = dBuilder.parse(file);
            doc.getDocumentElement().normalize();

         String typevalue =  doc.getDocumentElement().getChildNodes().item(0).getFirstChild().getChildNodes().item(0).getAttributes().getNamedItem("value").getNodeValue();

            System.out.println(typevalue);
            
        } catch (Exception e) 
        {
            e.printStackTrace();
        }
    }
    
    
}

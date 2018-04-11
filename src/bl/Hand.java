/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package bl;

import beans.Card;
import java.util.Random;

/**
 *
 * @author Philipp
 */
public class Hand {
    
    Card[] hand = new Card[5];
    
    
    
    public Hand(){
     generatehand();
    }
    
    public void generatehand()
    {
        for (int i = 0; i < 6; i++) {
            hand[i] = generatecard();
        }
        
        
    }
    
    public void use(int slot)
    {
        
        
        hand[slot] = draw();
        
        
    }
    
    public Card draw()
    {
        Card c = null;
        
        c = generatecard();
        
        return c;
    }
    
    public Card generatecard()
    {
        Card card=null;
        
        
        Random rand = new Random();
        
        rand.nextInt(10 - 0 +1); //og ist anzahl der verschiedenen karten aus db auslesen
        
        
        
        return card;
    }
    
  
}

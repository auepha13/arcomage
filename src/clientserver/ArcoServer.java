/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package clientserver;

import beans.Card;
import beans.Player;
import beans.Playercard;
import database.DB_Access;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JTextArea;
import javax.swing.text.JTextComponent;

/**
 *
 * @author Philipp
 */
public class ArcoServer extends BasicServer
{
    private DB_Access dba = DB_Access.getInstance();
    //private HashMap<Integer, Integer> playercardMap = new HashMap<Integer, Integer>();
    //private Player p1;
    //private Player p2;
    private Gamestate gs;
    //private int actualplayer = 1;
    @Override
    protected Object processRequest(Object request) {

        if(request instanceof Playercard)
        {
            Playercard pc = (Playercard)request;
            try {
                gs.usecard(pc.getCardplace(),pc.getPlayernr());
            } catch (Gamestate.Notusableerror ex) {
                Logger.getLogger(ArcoServer.class.getName()).log(Level.SEVERE, null, ex);
            }
            
            
            
            return gs;
        }
        
        if(request instanceof Integer)
        {
            return gs;
        }
        
        
        
        
        
        
        
        //karte ziehen
        
        //gespielte karte für gegner zurückgeben
        
        return null;
    }
   
    public ArcoServer(int i, JTextComponent t) {
        super(i,t);
    }

    @Override
    public void startServer() {
        gs = new Gamestate();
        
        super.startServer(); //To change body of generated methods, choose Tools | Templates.
        
    }

    

    
    

    @Override
    public void stopServer() {
        super.stopServer(); //To change body of generated methods, choose Tools | Templates.
    }

    

  
    
    
    
}

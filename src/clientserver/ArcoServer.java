/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package clientserver;

import javax.swing.JTextArea;
import javax.swing.text.JTextComponent;

/**
 *
 * @author Philipp
 */
public class ArcoServer extends BasicServer
{

    @Override
    protected Object processRequest(Object request) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
   
    public ArcoServer(int i, JTextComponent t) {
        super(i,t);
    }

    @Override
    public void startServer() {
        super.startServer(); //To change body of generated methods, choose Tools | Templates.
    }

    

    
    

    @Override
    public void stopServer() {
        super.stopServer(); //To change body of generated methods, choose Tools | Templates.
    }

    

  
    
    
    
}

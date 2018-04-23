/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package clientserver;

import java.io.IOException;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author Philipp
 */
public class ArcoClient {
    private  InetAddress ADDR ;  
    private Socket socket;
    private String user="";
    
    public ArcoClient()
    {
     
        try {
            ADDR = InetAddress.getLocalHost();
        } catch (UnknownHostException ex) {
            Logger.getLogger(ArcoClient.class.getName()).log(Level.SEVERE, null, ex);
        }
        try {
            socket = new Socket(ADDR, 1337);
        } catch (IOException ex) {
            Logger.getLogger(ArcoClient.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        
    }
}

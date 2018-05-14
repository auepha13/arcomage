/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package clientserver;

import static com.sun.corba.se.spi.presentation.rmi.StubAdapter.request;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
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
    private  InetAddress ADDR = null ;  
    private Socket socket = null;
    private String userid="";
    
    public ArcoClient()
    {
     
        try {
            ADDR = InetAddress.getLocalHost();
        } catch (UnknownHostException ex) {
            Logger.getLogger(ArcoClient.class.getName()).log(Level.SEVERE, null, ex);
        }
        try {
            socket = new Socket(ADDR, 9999);
        } catch (IOException ex) {
            Logger.getLogger(ArcoClient.class.getName()).log(Level.SEVERE, null, ex);
        }
        

    }
            public void sendRequest(Object request) throws IOException, ClassNotFoundException {
     
            ObjectOutputStream oos = new ObjectOutputStream(socket.getOutputStream());
            ObjectInputStream ois = new ObjectInputStream(socket.getInputStream());
            oos.writeObject(request); //an server schicken und lesen
            ois.readObject().toString();
            
            System.out.println(ois.readObject().toString());
            oos.close();
            ois.close();
            socket.close();
    
             }
}

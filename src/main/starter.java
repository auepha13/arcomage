/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package main;

import gui.ClientGUI;
import gui.ServerGUI;

/**
 *
 * @author Philipp
 */
public class starter {
    
    public static void main(String[] args) {
        ServerGUI server =new ServerGUI();
        server.setVisible(true);
        server.btstart();
        
//        ClientGUI c1=new ClientGUI();
//        c1.setplayernr(1);
//        ClientGUI c2=new ClientGUI();    
//        c2.setplayernr(2);
//        c1.setVisible(true);
//        c2.setVisible(true);
    }
    
    
}

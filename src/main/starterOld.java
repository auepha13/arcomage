/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package main;

import gui.ArcomageGUI;
import gui.ClientGUI;
import gui.ServerGUI;
import java.util.logging.Level;
import java.util.logging.Logger;
import javafx.application.Application;

/**
 *
 * @author
 */
public class starterOld {

    public static void main(String[] args) {

        ServerGUI server = new ServerGUI();
        server.setVisible(true);
        server.btstart();

        ClientGUI gui1 = new ClientGUI(1);
        ClientGUI gui2 = new ClientGUI(2);
        
        gui1.setLocation(0, 0);
        gui1.setSize(1500,500);
         gui2.setLocation(0, 500);
          gui2.setSize(1500,500);

        gui1.setVisible(true);

        gui2.setVisible(true);

//        ArcomageGUI gui = new ArcomageGUI(1);
//        ArcomageGUI gui2 = new ArcomageGUI(2);
//        try {
//            gui.start(gui.classStage);
//            gui2.start(gui2.classStage);
//        } catch (Exception ex) {
//            Logger.getLogger(starter.class.getName()).log(Level.SEVERE, null, ex);
//        }
    }

}

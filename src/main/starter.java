/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package main;

import gui.ArcomageGUI;
import old.ClientGUI;
import gui.ServerGUI;
import java.util.logging.Level;
import java.util.logging.Logger;
import javafx.application.Application;

/**
 *
 * @author
 */
public class starter {

    public static void main(String[] args) {

        ServerGUI server = new ServerGUI();
        server.setVisible(true);
        server.btstart();
        ArcomageGUI gui = new ArcomageGUI();
        Application.launch(ArcomageGUI.class, args);
        
    }

}

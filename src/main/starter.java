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

/**
 *
 * @author Philipp
 */
public class starter {
    
    
    
    public static void main(String[] args) {
        ArcomageGUI gui = new ArcomageGUI(1);
        ArcomageGUI gui2 = new ArcomageGUI(2);
        try {
            gui.start(gui.classStage);
            gui2.start(gui2.classStage);
        } catch (Exception ex) {
            Logger.getLogger(starter.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    


    
}

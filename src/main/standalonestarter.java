/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package main;

import gui.ArcomageGUI;
import gui.ArcomageGUI2;
import old.ClientGUI;
import gui.ServerGUI;
import java.util.logging.Level;
import java.util.logging.Logger;
import javafx.application.Application;

/**
 *
 * @author Philipp
 */
public class standalonestarter {

    public static void main(String[] args) {
        ArcomageGUI2 gui = new ArcomageGUI2();
        Application.launch(ArcomageGUI2.class, args);
    }

}

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package gui;

import beans.Card;
import beans.Player;
import beans.Playercard;
import clientserver.ArcoClient;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import static java.lang.Thread.interrupted;
import static java.lang.Thread.sleep;
import java.util.Random;
import java.util.logging.Level;
import java.util.logging.Logger;
import javafx.animation.AnimationTimer;
import javafx.animation.TranslateTransition;
import javafx.application.Application;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.event.EventHandler;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.image.Image;
import javafx.scene.input.MouseButton;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.Pane;
import javafx.scene.layout.Region;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;
import javafx.scene.text.Font;
import javafx.scene.text.TextAlignment;
import javafx.scene.transform.Scale;
import javafx.stage.Stage;
import javafx.util.Duration;

/**
 *
 * @author Stefan
 */
public class ArcomageGUI2 extends Application{

    //Sehr viele wichtige Variablen
    private int[] canvasSize = {1024, 768};
    private static String path = System.getProperty("user.dir") + File.separator + "src" + File.separator + "res" + File.separator;
    private double[] x = {0, 0, 0, 0, 0, 0};
    private double[] y = {0, 0, 0, 0, 0, 0};
    private Image[] tower = new Image[4];
    private Image[] wall = new Image[2];
    private Image[] template = new Image[6];
    private Image[] card = new Image[6];
    private Rectangle[] selCard = new Rectangle[6];
    private static Image background;
    private static Image selected;
    private static Image unavailable;
    private static Image discarded;
    private int selectedCard = -1;
    private TranslateTransition tt;
    
    
    
    private Card[] cards = new Card[6];
    private int[] healthTower = {25, 25};
    private int[] healthWall = {10, 10};
    private int[] cardCosts = {6, 2, 12, 35, 3, 2};
    private int[] resources = {2, 2, 2, 2, 2, 2};
    private int[] changes = {2, 2, 2, 2, 2, 2};
    private boolean[] cardDiscard = {false, false, false, false, false, false};
    private boolean[] cardUnavailable = {false, false, false, false, false, false};
    
    
    
    private ArcoClient c;
    private int playernr =0;
    private Player  p = null;
    private ArcomageGUI2.ClientThread ct;
    
    
    
    public ArcomageGUI2()
    {
//        Application.launch(ArcomageGUI2.class, "");
        
        setplayernr(2);
        
        
        c= new ArcoClient();
        try {
           actplayer(c.sendRequest(playernr));
        } catch (IOException ex) {
            Logger.getLogger(ArcomageGUI2.class.getName()).log(Level.SEVERE, null, ex);
        } catch (ClassNotFoundException ex) {
            Logger.getLogger(ArcomageGUI2.class.getName()).log(Level.SEVERE, null, ex);
        }
         ct = new ArcomageGUI2.ClientThread();
         ct.start();
    }
    
    public void setplayernr(int nr)
    {
        playernr= nr;
//        lbplayer.setText("Player "+playernr);
    }
    
    private void actplayer(Player p)
    {
        for (int j = 0; j < cards.length; j++) {
            cards[j] = p.getHand()[j];
            
            //template[j] = p.getHand()[j].getPicture();
            String type = "";
            switch(p.getHand()[j].getType())
            {
                case 0: type = "red"; break;
                case 1: type = "blue"; break;
                case 2: type = "green"; break;
            }
            try {
                card[j] = new Image(new FileInputStream(path + type + ".png"));
                template[j] = new Image(new FileInputStream(path + p.getHand()[j].getCard_id() + ".png"));
            } catch (FileNotFoundException ex) {
                Logger.getLogger(ArcomageGUI2.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
        healthTower[0] = p.getTower();
        healthTower[1] = p.getTower2();
        healthWall[0] = p.getWall();
        healthWall[1] = p.getWall();
        resources[0] = p.getBricks();
        resources[3] = p.getBricks2();
        resources[1] = p.getGems();
        resources[4] = p.getGems2();
        resources[2] = p.getBeasts();
        resources[5] = p.getBeasts2();
        changes[0] = p.getQuarry();
        changes[3] = p.getQuarry2();
        changes[1] = p.getMagic();
        changes[4] = p.getMagic2();
        changes[2] = p.getBestiary();
        changes[5] = p.getBestiary2();
        if(playernr!=p.getActualplayer())
        {
            for (int i = 0; i < cards.length; i++) {
                cardUnavailable[i] = true;
            }
        }
        else
        {
            for (int i = 0; i < cards.length; i++) {
                cardUnavailable[i] = false;
            }
        }
    }
    
    //thread machen!!!
    class ClientThread extends Thread {

        @Override
        public void run() {
            while (!interrupted()) {
                try {
                    sleep(100);
                } catch (InterruptedException ex) {
                    System.out.println("wait fehler");
                }
              
                try {
                    p = c.sendRequest(playernr);
                } catch (IOException ex) {
                    Logger.getLogger(ArcomageGUI2.class.getName()).log(Level.SEVERE, null, ex);
                } catch (ClassNotFoundException ex) {
                    Logger.getLogger(ArcomageGUI2.class.getName()).log(Level.SEVERE, null, ex);
                }
                actplayer(p);
                //System.out.println(p.getPlayernr());
                if(playernr!=p.getActualplayer())
                {
                    for (int j = 0; j < cards.length; j++) {
                        cardUnavailable[j] = true;
                    }
                }
                else
                {
                    for (int j = 0; j < cards.length; j++) {
                        cardUnavailable[j] = false;
                    }
                }
            }
        }
    }
    
//    public static void main(String[] args) {
//        launch(args);
//    }
    
    @Override
    public void start(Stage stage) throws Exception {
        background = new Image(new FileInputStream(path + "00_gamescreen.jpg"));
        selected = new Image(new FileInputStream(path + "card_mouseover.png"));
        unavailable = new Image(new FileInputStream(path + "card_darkened.png"));
        discarded = new Image(new FileInputStream(path + "discard_overlay.png"));
        Font text = Font.loadFont(getClass().getResourceAsStream("/fonts/Archtura.ttf"), 18);
        Font cost = Font.loadFont(getClass().getResourceAsStream("/fonts/Archtura.ttf"), 16);
        Font desc = Font.loadFont(getClass().getResourceAsStream("/fonts/Archtura.ttf"), 12);
        Font numberTiny = Font.loadFont(getClass().getResourceAsStream("/fonts/Kingthings_Exeter.ttf"), 22);
        Font numberLarge = Font.loadFont(getClass().getResourceAsStream("/fonts/Kingthings_Exeter.ttf"), 66);
        
        stage.setTitle("Arcomage");
        
        Pane root = new Pane();
        Scene scene = new Scene(root);
        stage.setScene(scene);
        
        //Größe sollte man irgendwann vor Spielstart noch festegen können
        Canvas canvas = new Canvas(canvasSize[0], canvasSize[1]);
        root.getChildren().add(canvas);
        GraphicsContext gc = canvas.getGraphicsContext2D();
        
        //Türme, Turmspitze und Wall speichern
        tower[0] = new Image(new FileInputStream(path + "01_tower_enemy.png"));
        tower[1] = new Image(new FileInputStream(path + "01_tower_player.png"));
        tower[2] = new Image(new FileInputStream(path + "enemy_tower_top.png"));
        tower[3] = new Image(new FileInputStream(path + "player_tower_top.png"));
        wall[0] = new Image(new FileInputStream(path + "01_wall_enemy.png"));
        wall[1] = new Image(new FileInputStream(path + "01_wall_player.png"));
        
        //Erstellen aller Karten sollte mit entsprechenden Anfangskarten gemacht werden
        for (int j = 0; j < cards.length; j++) {
            card[j] = new Image(new FileInputStream(path + "red.png"));
            selCard[j] = new Rectangle((int)x[j], (int)y[j], (int)card[j].getWidth(), (int)card[j].getHeight());
            template[j] = new Image(new FileInputStream(path + "1.png"));
            x[j] = (canvasSize[0] - card[j].getWidth()) / 5 * j;
            y[j] = canvasSize[1] - card[j].getHeight();
        }
        
        //SelectedCanvas wie oben
        Canvas selCanvas = new Canvas( canvasSize[0], canvasSize[1] );
        root.getChildren().add(selCanvas);
        
        Scale scale = new Scale(1, 1, 0, 0);
        scale.xProperty().bind(root.widthProperty().divide(canvasSize[0]));
        scale.yProperty().bind(root.heightProperty().divide(canvasSize[1]));
        root.getTransforms().add(scale);
        
        GraphicsContext selGc = selCanvas.getGraphicsContext2D();
        
        scene.rootProperty().addListener(new ChangeListener<Parent>(){
            @Override public void changed(ObservableValue<? extends Parent> arg0, Parent oldValue, Parent newValue){
                scene.rootProperty().removeListener(this);
                scene.setRoot(root);
                ((Region)newValue).setPrefWidth(canvasSize[0]);
                ((Region)newValue).setPrefHeight(canvasSize[1]);
                root.getChildren().clear();
                root.getChildren().add(newValue);
                scene.rootProperty().addListener(this);
            }
        });
        
        //Font
        gc.setFill( Color.WHITE );
        gc.setFont(numberTiny);
        selGc.setFill( Color.WHITE );
        selGc.setFont(numberTiny);
        
        //Methode spielt Animation bei Klick ab, Discard sollte auf Secondary erscheinen
        selCanvas.addEventHandler(MouseEvent.MOUSE_CLICKED, new EventHandler<MouseEvent>() {
            @Override
            public void handle(MouseEvent e) {
                for (int j = 0; j < cards.length; j++) {
                    if (selCard[j].contains(e.getX(), e.getY()))
                    {
                        if (e.getButton() == MouseButton.PRIMARY)
                        {
                            int ownRes = 0;
                            switch(p.getHand()[j].getType())
                            {
                                case 0: ownRes = p.getBricks();
                                case 1: ownRes = p.getGems();
                                case 2: ownRes = p.getBeasts();
                            }
                            if (ownRes > p.getHand()[j].getRequirement() && !cardUnavailable[j])
                            {
                                tt = new TranslateTransition(Duration.millis(500), selCard[j]);
                                tt.setToX(selCanvas.getWidth() / 2 - x[j] - card[j].getWidth() / 2);
                                tt.setToY(selCanvas.getHeight() / 2 - y[j] - card[j].getHeight() / 2);
                                tt.play();
                            }
                        }
                        
                        if (e.getButton() == MouseButton.SECONDARY)
                        {
                            if (!cardUnavailable[j])
                            {
                                cardDiscard[j] = true;
                                tt = new TranslateTransition(Duration.millis(500), selCard[j]);
                                tt.setToX(selCanvas.getWidth() / 2 - x[j] - card[j].getWidth() / 2);
                                tt.setToY(selCanvas.getHeight() / 2 - y[j] - card[j].getHeight() / 2);
                                tt.play();
                            }
                        }
                    }
                }
            }
        });
        
        //Methode fragt Mausposition ab, hover über Karte j
        selCanvas.addEventHandler(MouseEvent.MOUSE_MOVED, new EventHandler<MouseEvent>() {
            @Override
            public void handle(MouseEvent e) {
                selectedCard = -1;
                for (int j = 0; j < cards.length; j++) {
                    if (selCard[j].contains(e.getX(), e.getY()))
                    {
                        selectedCard = j;
                    }
                }
            }
        });
        
        final long startNanoTime = System.nanoTime();
        
        new AnimationTimer()
        {
            public void handle(long currentNanoTime)
            {
                selGc.clearRect(0, 0, selCanvas.getWidth(), selCanvas.getHeight());
                
                //Wird sicher noch wichtig
                double t = (currentNanoTime - startNanoTime) / 1000000000.0;
                
                //Background wird geladen
                gc.drawImage(background, 0, 0, canvasSize[0], canvasSize[1]);
                
                //Laden von Gamestate-Infos
                    //Player/Enemy-Name
                    gc.setFont(numberTiny);
                    gc.setFill(Color.WHITE);
                    gc.fillText("Player", 20, 25, 105);
                    gc.fillText("Enemy", canvasSize[0] - 132, 25, 105);
                    
                    //Player/Enemy-Resources
                    gc.fillText(resources[0] + "", 25, 151);
                    gc.fillText(resources[1] + "", 25, 279);
                    gc.fillText(resources[2] + "", 25, 407);
                    gc.fillText(resources[3] + "", canvasSize[0] - 127, 151);
                    gc.fillText(resources[4] + "", canvasSize[0] - 127, 279);
                    gc.fillText(resources[5] + "", canvasSize[0] - 127, 407);
                    
                    //Player/Enemy-Health
                    gc.setTextAlign(TextAlignment.CENTER);
                    gc.fillText(healthTower[0] + "", 200, 505);
                    gc.fillText(healthWall[0] + "", 400, 505);
                    gc.fillText(healthTower[1] + "", canvasSize[0] - 200, 505);
                    gc.fillText(healthWall[1] + "", canvasSize[0] - 400, 505);
                    gc.setTextAlign(TextAlignment.LEFT);
                    
                    //Player/Enemy-Changes
                    gc.setFont(numberLarge);
                    gc.setFill(Color.YELLOW.darker().darker().darker());
                    
                    gc.fillText(changes[0] + "", 28, 113);
                    gc.fillText(changes[1] + "", 28, 241);
                    gc.fillText(changes[2] + "", 28, 369);
                    gc.fillText(changes[3] + "", canvasSize[0] - 124, 113);
                    gc.fillText(changes[4] + "", canvasSize[0] - 124, 241);
                    gc.fillText(changes[5] + "", canvasSize[0] - 124, 369);
                
                //Türme und Walls werden geladen
                selGc.drawImage(tower[0], canvasSize[0] - 250 - tower[0].getWidth(), canvasSize[1] - card[0].getHeight() - 3 - tower[0].getHeight() * healthTower[1] / 100);
                selGc.drawImage(tower[2], canvasSize[0] - 250 - tower[0].getWidth() - (tower[2].getWidth() - tower[0].getWidth()) / 2, canvasSize[1] - card[0].getHeight() - 3 - tower[0].getHeight() * healthTower[1] / 100 - tower[2].getHeight());
                selGc.drawImage(tower[1], 250, canvasSize[1] - card[0].getHeight() - 3 - tower[1].getHeight() * healthTower[0] / 100);
                selGc.drawImage(tower[3], 250 - (tower[3].getWidth() - tower[1].getWidth()) / 2, canvasSize[1] - card[0].getHeight() - 3 - tower[1].getHeight() * healthTower[0] / 100 - tower[3].getHeight());
                selGc.drawImage(wall[0], canvasSize[0] - 350 - wall[0].getWidth(), canvasSize[1] - card[0].getHeight() - 3 - wall[0].getHeight() * healthWall[1] / 100);
                selGc.drawImage(wall[1], 350, canvasSize[1] - card[0].getHeight() - 3 - wall[1].getHeight() * healthWall[0] / 100);
                selGc.clearRect(0, canvasSize[1] - card[0].getHeight() - 3, canvasSize[0], canvasSize[1]);
                
                //Jede Karte wird neu gedrawed, wenn selektiert, wenn geklickt
                for (int j = 0; j < cards.length; j++) {
                    if (selCard[j].getTranslateX() == selCanvas.getWidth() / 2 - x[j] - card[j].getWidth() / 2 &&
                            selCard[j].getTranslateY() == selCanvas.getHeight() / 2 - y[j] - card[j].getHeight() / 2)
                    {
                        selCard[j].setTranslateX(0);
                        selCard[j].setTranslateY(0);
                        
                        if (!cardDiscard[j])
                        {
                            useCard(j);
                        }
                        else
                        {
                            discardCard(j);
                        }
                        
                        cardDiscard[j] = false;
                    }
                    selCard[j].setX(x[j] + selCard[j].getTranslateX());
                    selCard[j].setY(y[j] + selCard[j].getTranslateY());
                    selGc.drawImage( card[j], selCard[j].getX(), selCard[j].getY());
//                    selCard[j] = new Rectangle((int)x[j], (int)y[j], (int)card[j].getWidth(), (int)card[j].getHeight());
//                    selCard[j].setLocation((int)x[j], (int)y[j]);
                    selGc.drawImage( template[j], selCard[j].getX() + 21, selCard[j].getY() + 55, 136, 80 );
                    selGc.setFont(text);
                    selGc.fillText(p.getHand()[j].getName(), selCard[j].getX() + 15, selCard[j].getY() + 33, selCard[0].getWidth() - 30);
                    selGc.setFont(desc);
                    String[] splits = p.getHand()[j].getDescription().split("_n");
                    int dist = 165;
                    for (String split : splits) {
                        //System.out.println(split);
                        selGc.fillText(split, selCard[j].getX() + 13, selCard[j].getY() + dist, selCard[0].getWidth() - 26);
                        dist += 14;
                    }
                    selGc.setFont(cost);
                    selGc.setTextAlign(TextAlignment.CENTER);
                    selGc.fillText(p.getHand()[j].getRequirement() + "", selCard[j].getX() + 147, selCard[j].getY() + 232);
                    selGc.setTextAlign(TextAlignment.LEFT);
                    if (j == selectedCard)
                    {
                        selGc.drawImage(selected, selCard[selectedCard].getX(), selCard[selectedCard].getY());
                    }
                    int ownRes = 0;
                    switch(p.getHand()[j].getType())
                    {
                        case 0: ownRes = p.getBricks();
                        case 1: ownRes = p.getGems();
                        case 2: ownRes = p.getBeasts();
                    }
                    if (ownRes < p.getHand()[j].getRequirement() || cardUnavailable[j])
                    {
                        selGc.drawImage(unavailable, selCard[j].getX(), selCard[j].getY());
                    }
                    if (cardDiscard[j] == true)
                    {
                        selGc.drawImage(discarded, selCard[j].getX(), selCard[j].getY());
                    }
                }
            }
        }.start();
        
        stage.show();
    }
    
    public void useCard(int location)
    {
        try {
            c.sendRequest(new Playercard(location, playernr));
        } catch (IOException ex) {
            Logger.getLogger(ArcomageGUI2.class.getName()).log(Level.SEVERE, null, ex);
        } catch (ClassNotFoundException ex) {
            Logger.getLogger(ArcomageGUI2.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    public void discardCard(int location)
    {
        try {
            c.sendRequest(new Playercard(location, playernr));
        } catch (IOException ex) {
            Logger.getLogger(ArcomageGUI2.class.getName()).log(Level.SEVERE, null, ex);
        } catch (ClassNotFoundException ex) {
            Logger.getLogger(ArcomageGUI2.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
}

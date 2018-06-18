/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package gui;

import beans.Card;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
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
import javafx.scene.text.FontWeight;
import javafx.scene.text.TextAlignment;
import javafx.scene.transform.Scale;
import javafx.stage.Stage;
import javafx.util.Duration;

/**
 *
 * @author Florian
 */
public class ArcomageGUI extends Application{

    //Sehr viele wichtige Variablen
    private int[] canvasSize = {1024, 768};
    private static String path = System.getProperty("user.dir") + File.separator + "src" + File.separator + "res" + File.separator;
    private int[] i = {1, 1, 1, 1, 1, 1};
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
    private int[] healthTower = {25, 25};
    private int[] healthWall = {10, 10};
    private int[] cardCosts = {6, 2, 12, 35, 3, 2};
    private int[] resources = {2, 2, 2, 2, 2, 2};
    private int[] changes = {2, 2, 2, 2, 2, 2};
    private boolean[] cardDiscard = {false, false, false, false, false, false};
    
    public static void main(String[] args) {
        
        //Background
        try {
            background = new Image(new FileInputStream(path + "00_gamescreen.jpg"));
            selected = new Image(new FileInputStream(path + "card_mouseover.png"));
            unavailable = new Image(new FileInputStream(path + "card_darkened.png"));
            discarded = new Image(new FileInputStream(path + "discard_overlay.png"));
        } catch (FileNotFoundException ex) {
            Logger.getLogger(ArcomageGUI.class.getName()).log(Level.SEVERE, null, ex);
        }
        launch(args);
    }
    
    @Override
    public void start(Stage stage) throws Exception {
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
        for (int j = 0; j < i.length; j++) {
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
        
        Random rand = new Random();
        
        //Methode spielt Animation bei Klick ab, Discard sollte auf Secondary erscheinen
        selCanvas.addEventHandler(MouseEvent.MOUSE_CLICKED, new EventHandler<MouseEvent>() {
            @Override
            public void handle(MouseEvent e) {
                for (int j = 0; j < i.length; j++) {
                    if (selCard[j].contains(e.getX(), e.getY()))
                    {
                        if (e.getButton() == MouseButton.PRIMARY)
                        {
                            if (cardCosts[j] < 10)
                            {
                                tt = new TranslateTransition(Duration.millis(500), selCard[j]);
                                tt.setToX(selCanvas.getWidth() / 2 - x[j] - card[j].getWidth() / 2);
                                tt.setToY(selCanvas.getHeight() / 2 - y[j] - card[j].getHeight() / 2);
                                tt.play();
                                
                                healthTower[0] = rand.nextInt(101);
                                healthTower[1] = rand.nextInt(101);
                                healthWall[0] = rand.nextInt(101);
                                healthWall[1] = rand.nextInt(101);
                            }
                        }
                        
                        if (e.getButton() == MouseButton.SECONDARY)
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
        });
        
        //Methode fragt Mausposition ab, hover über Karte j
        selCanvas.addEventHandler(MouseEvent.MOUSE_MOVED, new EventHandler<MouseEvent>() {
            @Override
            public void handle(MouseEvent e) {
                selectedCard = -1;
                for (int j = 0; j < i.length; j++) {
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
                for (int j = 0; j < i.length; j++) {
                    if (selCard[j].getTranslateX() == selCanvas.getWidth() / 2 - x[j] - card[j].getWidth() / 2 &&
                            selCard[j].getTranslateY() == selCanvas.getHeight() / 2 - y[j] - card[j].getHeight() / 2)
                    {
                        selCard[j].setTranslateX(0);
                        selCard[j].setTranslateY(0);
                        
                        if (!cardDiscard[j])
                        {
                            useCard(new Card(i[j], "", "", 0, 0, false, false, 0, 0), j);
                        }
                        else
                        {
                            discardCard(new Card(i[j], "", "", 0, 0, false, true, 0, 0), j);
                        }
                        
                        cardDiscard[j] = false;
                        i[j] = rand.nextInt(87) + 1;
                        try {
                            card[j] = new Image(new FileInputStream(path + ((i[j] < 30) ? "red.png" : (i[j] < 59) ? "blue.png" : "green.png")));
                            template[j] = new Image(new FileInputStream(path + i[j] + ".png"));
                        } catch (FileNotFoundException ex) {
                            Logger.getLogger(ArcomageGUI.class.getName()).log(Level.SEVERE, null, ex);
                        }
                        
                    }
                    selCard[j].setX(x[j] + selCard[j].getTranslateX());
                    selCard[j].setY(y[j] + selCard[j].getTranslateY());
                    selGc.drawImage( card[j], selCard[j].getX(), selCard[j].getY());
//                    selCard[j] = new Rectangle((int)x[j], (int)y[j], (int)card[j].getWidth(), (int)card[j].getHeight());
//                    selCard[j].setLocation((int)x[j], (int)y[j]);
                    selGc.drawImage( template[j], selCard[j].getX() + 21, selCard[j].getY() + 55, 136, 80 );
                    selGc.setFont(text);
                    selGc.fillText("Sample Text", selCard[j].getX() + 15, selCard[j].getY() + 33, selCard[0].getWidth() - 30);
                    selGc.setFont(desc);
                    selGc.fillText("Sample Text Sample Text", selCard[j].getX() + 13, selCard[j].getY() + 165, selCard[0].getWidth() - 26);
                    selGc.fillText("Sample", selCard[j].getX() + 13, selCard[j].getY() + 179, selCard[0].getWidth() - 26);
                    selGc.fillText("Sample Text", selCard[j].getX() + 13, selCard[j].getY() + 193, selCard[0].getWidth() - 26);
                    selGc.setFont(cost);
                    selGc.setTextAlign(TextAlignment.CENTER);
                    selGc.fillText(cardCosts[j] + "", selCard[j].getX() + 147, selCard[j].getY() + 232);
                    selGc.setTextAlign(TextAlignment.LEFT);
                    if (j == selectedCard)
                    {
                        selGc.drawImage(selected, selCard[selectedCard].getX(), selCard[selectedCard].getY());
                    }
                    if (cardCosts[j] > 10)
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

    // Feld mit allen KartenIDs des Players
    
    public int[] getI() {
        return i;
    }

    public void setI(int[] i) {
        this.i = i;
    }

    // Feld für TowerHealth, 0 = Player, 1 = Enemy
    
    public int[] getHealthTower() {
        return healthTower;
    }

    public void setHealthTower(int[] healthTower) {
        this.healthTower = healthTower;
    }

    // Feld für WallHealth, 0 = Player, 1 = Enemy
    
    public int[] getHealthWall() {
        return healthWall;
    }

    public void setHealthWall(int[] healthWall) {
        this.healthWall = healthWall;
    }

    // Feld für die Kosten aller Karten
    
    public int[] getCardCosts() {
        return cardCosts;
    }
    
    public void setCardCosts(int[] cardCosts) {
        this.cardCosts = cardCosts;
    }

    // Feld für die Resourcen, 0-2 Player, 3-5 Enemy
    
    public int[] getResources() {
        return resources;
    }

    public void setResources(int[] resources) {
        this.resources = resources;
    }

    // Feld für Changes, 0-2 Player, 3-5 Enemy
    
    public int[] getChanges() {
        return changes;
    }

    public void setChanges(int[] changes) {
        this.changes = changes;
    }

    //Feld für Discard Karte des Players
    
    public boolean[] getCardDiscard() {
        return cardDiscard;
    }

    public void setCardDiscard(boolean[] cardDiscard) {
        this.cardDiscard = cardDiscard;
    }
    
    public void useCard(Card card, int location)
    {
        System.out.println("Used: " + card.getCard_id() + " an der Stelle: " + location);
    }
    
    public void discardCard(Card card, int location)
    {
        System.out.println("Discarded: " + card.getCard_id() + " an der Stelle: " + location);
    }
    
}

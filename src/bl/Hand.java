/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package bl;

import beans.Card;
import database.DB_Access;
import java.util.Random;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * manages everything about the 6 cards in your hand
 * @author Philipp
 */
public class Hand {

    public Card[] hand = new Card[6];
    private DB_Access dba = DB_Access.getInstance();

    public Hand() {
        generatehand();
    }

    public void generatehand() {
        for (int i = 0; i < 6; i++) {
            hand[i] = generatecard();
        }

    }

    public void use(int slot) {
        hand[slot] = draw();
    }

  
    /**
     * 
     * 
     * @return new Card object
     */
    public Card draw() {
        Card c = null;

        c = generatecard();

        return c;
    }

    /**
     * 
     * @return new CARD OBJECT
     */
    public Card generatecard() {
        Card card = null;
       // System.out.println("generate");

        do {

            try {
                card = dba.getRandomCard();
            } catch (Exception ex) {
                Logger.getLogger(Hand.class.getName()).log(Level.SEVERE, null, ex);
            }
            //not implemented yet
           // System.out.println(card.getDescription());
        } while (card.getDescription().toLowerCase().contains("additional turn")|| card.getDescription().toLowerCase().contains("if")|| card.getDescription().toLowerCase().contains("adjusts") );

       // System.out.println("");
        
//         private int card_id;         //von der datenbank genierierte id
//    private String name;              //name der karte
//    private String bild_pfad;         //pfad zum bild
//    private int type;                 //type der karte (1 = 
//    private int requirement;          //
//    private int damage_self;          //
//    private int mod_enemy_bestiary;   //verändert bestiary am gegner
//    private int mod_enemy_quarry;     //--;--
//    private int mod_enemy_magic;      //--;--
//    private int mod_player_bestiary;  //--;--
//    private int mod_player_quarry;    //--;-- beim player
//    private int mod_player_magic;     //--;--
//    private int changes_enemy_beats;  //gleiche mit beasts
//    private int changes_enemy_bricks;
//    private int changes_enemy_gems;
//    private int changes_player_beats;
//    private int changes_player_bricks;
//    private int changes_player_gems;
//    private String description;
        return card;
    }

    public Card[] getHand() {
        return hand;
    }

    public void setHand(Card[] hand) {
        this.hand = hand;
    }

}

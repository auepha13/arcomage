/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cardreader;

import beans.Card;
import database.DB_Access;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.sql.SQLException;
import java.util.LinkedList;
import java.util.concurrent.ThreadLocalRandom;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import org.w3c.dom.Document;
import org.xml.sax.SAXException;

/**
 *
 * @author Stefan
 */
public class CardReader {

    //XML hat nicht funktioniert, wird ugestellt in csv
    public static void main(String argv[]) throws SAXException, IOException {

        try {
            DB_Access access = DB_Access.getInstance();

//            access.getRandomCard();
            // Card card = access.getRandomCard();
            // System.out.println(card.toString());
            LinkedList<Card> cards = new LinkedList<Card>();
            File file = new File(System.getProperty("user.dir") + File.separator + "res" + File.separator + "deck.csv");

            BufferedReader reader = new BufferedReader(new InputStreamReader(new FileInputStream(file), "UTF-8"));
            String zeile = "";

            reader.readLine();

            while ((zeile = reader.readLine()) != null) {

                String[] f = zeile.split(";");

                // int card_id,    String name, int type, String bild_pfad, int requirement, int damage_enemy, int damage_self, int mod_enemy_bestiary, int mod_enemy_quarry, int mod_enemy_magic, int mod_player_bestiary, int mod_player_quarry, int mod_player_magic, int changes_enemy_beasts, int changes_enemy_bricks, int changes_enemy_gems, int changes_enemy_tower, int changes_enemy_wall, int changes_player_beasts, int changes_player_bricks, int changes_player_gems, int changes_player_tower, int changes_player_wall, String description, boolean additional_turn, boolean discardable) {
//
                for (int i = 0; i < f.length; i++) {
                    if (f[i].equals("X")) {
                        f[i] = "0";
                    }
                    //System.out.print(f[i] +" "+i +"; ");
                }

                //nur gewisse attribute
                //                  card_id,                name, description, type,             requirement,            additional_turn,                discardable, damage_enemy,           damage_self             
                //cards.add(new Card(Integer.parseInt(f[23]), f[0], f[22], Integer.parseInt(f[1]), Integer.parseInt(f[3]), Integer.parseInt(f[24]) == 1, Integer.parseInt(f[26]) == 1, Integer.parseInt(f[4]), Integer.parseInt(f[5])));
                //ab 6
                //PlayerMod/_beasts;PlayerMod/_bricks;PlayerMod/_gems;EnemyMod/_beasts;EnemyMod/_bricks;EnemyMod/_gems;PlayerChanges/_beasts;PlayerChanges/_bricks;PlayerChanges/_gems;PlayerChanges/_tower;PlayerChanges/_wall;EnemyChanges/_beasts;EnemyChanges/_bricks;EnemyChanges/_gems;EnemyChanges/_tower;EnemyChanges/_wall;Description;_id;AdditionalTurn/_value;Script/_value;DiscardCard/_value
                //int card_id, int mod_enemy_bestiary, int mod_enemy_quarry, int mod_enemy_magic, int mod_player_bestiary, int mod_player_quarry, int mod_player_magic, int changes_enemy_beasts, int changes_enemy_bricks, int changes_enemy_gems, int changes_enemy_tower, int changes_enemy_wall, int changes_player_beasts, int changes_player_bricks, int changes_player_gems, int changes_player_tower, int changes_player_wall) {
                /*
                 6  PlayerMod/_beasts;PlayerMod/_bricks;PlayerMod/_gems;EnemyMod/_beasts;EnemyMod/_bricks;EnemyMod/_gems;
                12  PlayerChanges/_beasts;PlayerChanges/_bricks;PlayerChanges/_gems;PlayerChanges/_tower;PlayerChanges/_wall;
                17 EnemyChanges/_beasts;EnemyChanges/_bricks;EnemyChanges/_gems;EnemyChanges/_tower;EnemyChanges/_wall;
                               
                 */
                //int card_id,              int mod_enemy_bestiary, int mod_enemy_quarry,       int mod_enemy_magic, int mod_player_bestiary, int mod_player_quarry, int mod_player_magic,      int changes_enemy_beasts, int changes_enemy_bricks, int changes_enemy_gems, int changes_enemy_tower, int changes_enemy_wall, int changes_player_beasts, int changes_player_bricks, int changes_player_gems, int changes_player_tower, int changes_player_wall) {
                cards.add(new Card(Integer.parseInt(f[23]), Integer.parseInt(f[9]), Integer.parseInt(f[10]), Integer.parseInt(f[11]), Integer.parseInt(f[6]), Integer.parseInt(f[7]), Integer.parseInt(f[8]), Integer.parseInt(f[17]), Integer.parseInt(f[18]), Integer.parseInt(f[19]), Integer.parseInt(f[20]), Integer.parseInt(f[21]), Integer.parseInt(f[12]), Integer.parseInt(f[13]), Integer.parseInt(f[14]), Integer.parseInt(f[15]), Integer.parseInt(f[16])));
                //cards.add(new Card(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
                //Name;Type/_value;Picture/_value;Requirements/_value;Damage/_enemy;Damage/_self;PlayerMod/_beasts;PlayerMod/_bricks;PlayerMod/_gems;EnemyMod/_beasts;EnemyMod/_bricks;EnemyMod/_gems;PlayerChanges/_beasts;PlayerChanges/_bricks;PlayerChanges/_gems;PlayerChanges/_tower;PlayerChanges/_wall;EnemyChanges/_beasts;EnemyChanges/_bricks;EnemyChanges/_gems;EnemyChanges/_tower;EnemyChanges/_wall;Description;_id;AdditionalTurn/_value;Script/_value;DiscardCard/_value

                // Brick Shortage;0;1.png;0;0;0;0;0;0;0;0;0;0;-8;0;0;0;0;-8;0;0;0;All Players lose 8 bricks_n;1;;;
                // cards.add(new Card(Integer.parseInt(f[23]), f[0], f[22], Integer.parseInt(f[1]), Integer.parseInt(f[3]), Integer.parseInt(f[24]) == 1, Integer.parseInt(f[26]) == 1, Integer.parseInt(f[4]), Integer.parseInt(f[5]), Integer.parseInt(f[6]), Integer.parseInt(f[7]), Integer.parseInt(f[8]), Integer.parseInt(f[9]), Integer.parseInt(f[10]), Integer.parseInt(f[11]), Integer.parseInt(f[12]), Integer.parseInt(f[13]), Integer.parseInt(f[14]), Integer.parseInt(f[15]), Integer.parseInt(f[16]), Integer.parseInt(f[17]), Integer.parseInt(f[18]), Integer.parseInt(f[19]), Integer.parseInt(f[20]), Integer.parseInt(f[21])));
                // Integer.parseInt(f[24]) == 1, Integer.parseInt(f[26]) == 1
            }
            for (Card c : cards) {
                try {
                    //System.out.println(c.toString());
                    //access.insertCard(c);
                    //access.insertCardPicture(c);
                    //access.insertVa(c);
                    //  System.out.println(c.toString());
                    // access.CardUpdate(c);
                    //   access.insertCardPicture(c);
                    //access.CardUpdate(c);

                    //System.out.println(c.toString());
                } catch (Exception ex) {
                    Logger.getLogger(CardReader.class.getName()).log(Level.SEVERE, null, ex);
                }

            }
        } catch (Exception ex) {
            Logger.getLogger(CardReader.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
}

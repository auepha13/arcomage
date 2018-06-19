/*

 */
package database;

import beans.Card;
import java.awt.Image;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.FileInputStream;
import java.io.InputStream;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.LinkedList;
import java.util.List;
import java.util.concurrent.ThreadLocalRandom;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.imageio.ImageIO;

/**
 *
 * @author Stefan
 */

//Database access
public class DB_Access {


    private static DB_Access theInstance = null;
    private DB_ConnectionPool connections = DB_ConnectionPool.getInstance();
    private DB_StatementPool statementPool = DB_StatementPool.getInstance();

    public static DB_Access getInstance() {
        if (theInstance == null) {
            theInstance = new DB_Access();
        }
        return theInstance;
    }

    private DB_Access() {
    }

    /**
     * Inserts the base information of a card
     * @param card
     * @throws SQLException
     * @throws InterruptedException 
     */
    public void insertCard(Card card) throws SQLException, InterruptedException {

        try {

            Connection conn = connections.getConnection();
            PreparedStatement stat = statementPool.getPrepStatement(conn, DB_Stmt_Type.InsertCard);

            stat.setString(1, card.getName());
            stat.setString(2, card.getDescription());
            stat.setInt(3, card.getType());
            stat.setInt(4, card.getRequirement());
            stat.setBoolean(5, card.isAdditional_turn());
            stat.setBoolean(6, card.isDiscardable());
            stat.setInt(7, card.getDamage_enemy());
            stat.setInt(8, card.getDamage_self());

            stat.executeUpdate();

            connections.releaseConnection(conn);

        } catch (Exception ex) {
            Logger.getLogger(DB_Access.class.getName()).log(Level.SEVERE, null, ex);
        }

    }

    /**
     * Fills the other 2 Tables
     * @param card 
     */
    public void insertVa(Card card) {
        try {
            insertChangesE(card);
            insertChangesP(card);
            insertModE(card);
            insertModP(card);
            insertCardPicture(card);
        } catch (SQLException ex) {
            Logger.getLogger(DB_Access.class.getName()).log(Level.SEVERE, null, ex);
        } catch (InterruptedException ex) {
            Logger.getLogger(DB_Access.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    /**
     * inserts the Enemy Changes
     * @param card
     * @throws SQLException
     * @throws InterruptedException 
     */
    public void insertChangesE(Card card) throws SQLException, InterruptedException {

        try {

            Connection conn = connections.getConnection();
            PreparedStatement stat = statementPool.getPrepStatement(conn, DB_Stmt_Type.InsertChanges);
            stat.setInt(1, card.getChanges_enemy_beasts());
            stat.setInt(2, card.getChanges_enemy_bricks());
            stat.setInt(3, card.getChanges_enemy_gems());
            stat.setInt(4, card.getChanges_enemy_tower());
            stat.setInt(5, card.getChanges_enemy_wall());
            stat.executeUpdate();

            connections.releaseConnection(conn);

        } catch (Exception ex) {
            Logger.getLogger(DB_Access.class.getName()).log(Level.SEVERE, null, ex);
        }

    }

    /**
     * inserts the Player Changes
     * @param card
     * @throws SQLException
     * @throws InterruptedException 
     */
    public void insertChangesP(Card card) throws SQLException, InterruptedException {

        try {

            Connection conn = connections.getConnection();
            PreparedStatement stat = statementPool.getPrepStatement(conn, DB_Stmt_Type.InsertChanges);
            stat.setInt(1, card.getChanges_player_beasts());
            stat.setInt(2, card.getChanges_player_bricks());
            stat.setInt(3, card.getChanges_player_gems());
            stat.setInt(4, card.getChanges_player_tower());
            stat.setInt(5, card.getChanges_player_wall());
            stat.executeUpdate();

            connections.releaseConnection(conn);

        } catch (Exception ex) {
            Logger.getLogger(DB_Access.class.getName()).log(Level.SEVERE, null, ex);
        }

    }

 
    /**
     * inserts the Enemy mod
     * @param card
     * @throws SQLException
     * @throws InterruptedException 
     */
    public void insertModE(Card card) throws SQLException, InterruptedException {

        try {

            Connection conn = connections.getConnection();
            PreparedStatement stat = statementPool.getPrepStatement(conn, DB_Stmt_Type.InsertMod);
            stat.setInt(1, card.getMod_enemy_bestiary());
            stat.setInt(2, card.getMod_enemy_quarry());
            stat.setInt(3, card.getMod_enemy_magic());
            stat.executeUpdate();

            connections.releaseConnection(conn);

        } catch (Exception ex) {
            Logger.getLogger(DB_Access.class.getName()).log(Level.SEVERE, null, ex);
        }

    }

 
    /**
     * inserts the Player Mod
     * @param card
     * @throws SQLException
     * @throws InterruptedException 
     */
    public void insertModP(Card card) throws SQLException, InterruptedException {

        try {

            Connection conn = connections.getConnection();
            PreparedStatement stat = statementPool.getPrepStatement(conn, DB_Stmt_Type.InsertMod);
            stat.setInt(1, card.getMod_player_bestiary());
            stat.setInt(2, card.getMod_player_quarry());
            stat.setInt(3, card.getMod_player_magic());
            stat.executeUpdate();

            connections.releaseConnection(conn);

        } catch (Exception ex) {
            Logger.getLogger(DB_Access.class.getName()).log(Level.SEVERE, null, ex);
        }

    }

  
    /**
     * inserts the Card Picture
     * @param card
     * @throws SQLException
     * @throws InterruptedException 
     */
    public void insertCardPicture(Card card) throws SQLException, InterruptedException {

        try {

            Connection conn = connections.getConnection();
            PreparedStatement stat = statementPool.getPrepStatement(conn, DB_Stmt_Type.SetPicture);
            String pfad = System.getProperty("user.dir") + File.separator + "res" + File.separator + "images" + File.separator + card.getCard_id() + ".png";

            // System.out.println(pfad);
            File imgfile = new File(pfad);
            FileInputStream fin = new FileInputStream(imgfile);

            stat.setBinaryStream(1, (InputStream) fin, (int) imgfile.length());
            stat.setInt(2, card.getCard_id());

            stat.executeUpdate();
            //System.out.println("Successfully inserted the file into the database!");
            connections.releaseConnection(conn);
            fin.close();

        } catch (Exception ex) {
            Logger.getLogger(DB_Access.class.getName()).log(Level.SEVERE, null, ex);
        }

    }

  
    /**
     * Updates the Card with the correct foreign keys
     * @param card
     * @throws SQLException
     * @throws InterruptedException 
     */
    
    public void CardUpdate(Card card) throws SQLException, InterruptedException {

        try {

            int modPid = 0;
            int modEid = 0;
            int changesPid = 0;
            int changesEid = 0;
            Connection conn = connections.getConnection();
            PreparedStatement stat = statementPool.getPrepStatement(conn, DB_Stmt_Type.GetModID);
            stat.setInt(1, card.getMod_player_bestiary());
            stat.setInt(2, card.getMod_player_quarry());
            stat.setInt(3, card.getMod_player_magic());
            ResultSet rs = stat.executeQuery();

            // System.out.println(card.getMod_player_bestiary() + " " + card.getMod_player_quarry() + " " + card.getMod_player_magic());
            while (rs.next()) {
                modPid = rs.getInt(1);
                //System.out.print(" " + modPid);

            }

            stat = statementPool.getPrepStatement(conn, DB_Stmt_Type.GetModID);
            stat.setInt(1, card.getMod_enemy_bestiary());
            stat.setInt(2, card.getMod_enemy_quarry());
            stat.setInt(3, card.getMod_enemy_magic());
            rs = stat.executeQuery();

            while (rs.next()) {
                modEid = rs.getInt(1);
                //System.out.print(" " + modEid);

            }

            stat = statementPool.getPrepStatement(conn, DB_Stmt_Type.GetChangesID);
            stat.setInt(1, card.getChanges_enemy_beasts());
            stat.setInt(2, card.getChanges_enemy_bricks());
            stat.setInt(3, card.getChanges_enemy_gems());
            stat.setInt(4, card.getChanges_enemy_tower());
            stat.setInt(5, card.getChanges_enemy_wall());
            rs = stat.executeQuery();

            while (rs.next()) {
                changesEid = rs.getInt(1);
                //System.out.print(" " + changesEid);

            }

            stat = statementPool.getPrepStatement(conn, DB_Stmt_Type.GetChangesID);
            stat.setInt(1, card.getChanges_player_beasts());
            stat.setInt(2, card.getChanges_player_bricks());
            stat.setInt(3, card.getChanges_player_gems());
            stat.setInt(4, card.getChanges_player_tower());
            stat.setInt(5, card.getChanges_player_wall());
            rs = stat.executeQuery();

            while (rs.next()) {
                changesPid = rs.getInt(1);
                //System.out.print(" " + changesPid);

            }

            stat = statementPool.getPrepStatement(conn, DB_Stmt_Type.CardUpdate);
            stat.setInt(1, modEid);
            stat.setInt(2, modPid);
            stat.setInt(3, changesEid);
            stat.setInt(4, changesPid);
            stat.setInt(5, card.getCard_id());

            stat.executeUpdate();

            connections.releaseConnection(conn);

        } catch (Exception ex) {
            Logger.getLogger(DB_Access.class.getName()).log(Level.SEVERE, null, ex);
        }

    }

    /**
     * 
     * @return random card object
     * @throws SQLException
     * @throws Exception 
     */
    
    public Card getRandomCard() throws SQLException, Exception {

        int cardcount = 0;

        Connection conn = connections.getConnection();
        PreparedStatement stat = statementPool.getPrepStatement(conn, DB_Stmt_Type.GetCardCount);
        ResultSet rs = stat.executeQuery();
        Card card = null;

        while (rs.next()) {
            cardcount = rs.getInt(1);
        }
        int rnd = ThreadLocalRandom.current().nextInt(1, cardcount + 1);
        //System.out.println(rnd);

        card = getCard(rnd);

        connections.releaseConnection(conn);
        return card;
        

    }

    /**
     * 
     * returns a specific Card object
     * @param card_id uebergabe der card id
     * @return the card object
     * @throws SQLException
     * @throws Exception 
     */
    public Card getCard(int card_id) throws SQLException, Exception {

        Card card = null;
        Connection conn = connections.getConnection();
        PreparedStatement stat = statementPool.getPrepStatement(conn, DB_Stmt_Type.GetCardCount);

        stat = statementPool.getPrepStatement(conn, DB_Stmt_Type.GetCard);
        stat.setInt(1, card_id);
        ResultSet rs = stat.executeQuery();

        rs = stat.executeQuery();

        while (rs.next()) {

            String name = rs.getString(2);
            String description = rs.getString(3);
            Image picture = null;
            int type = rs.getInt(5);
            int requirement = rs.getInt(6);
            boolean additional_turn = rs.getBoolean(7);
            boolean discardable = rs.getBoolean(8);
            int damage_enemy = rs.getInt(9);
            int damage_self = rs.getInt(10);
            int mod_enemy_bestiary = rs.getInt(16);
            int mod_enemy_quarry = rs.getInt(17);
            int mod_enemy_magic = rs.getInt(18);
            int mod_player_bestiary = rs.getInt(20);
            int mod_player_quarry = rs.getInt(21);
            int mod_player_magic = rs.getInt(22);
            int changes_enemy_beasts = rs.getInt(24);
            int changes_enemy_bricks = rs.getInt(25);
            int changes_enemy_gems = rs.getInt(26);
            int changes_enemy_tower = rs.getInt(27);
            int changes_enemy_wall = rs.getInt(28);
            int changes_player_beast = rs.getInt(30);
            int changes_player_bricks = rs.getInt(31);
            int changes_player_gems = rs.getInt(32);
            int changes_player_tower = rs.getInt(33);
            int changes_player_wall = rs.getInt(33);

            BufferedImage imBuff = ImageIO.read(rs.getBinaryStream(4));
            picture = (Image) imBuff;

            card = new Card(card_id, name, description, picture, type, requirement, additional_turn, discardable, damage_enemy, damage_self, mod_enemy_bestiary, mod_enemy_quarry, mod_enemy_magic, mod_player_bestiary, mod_player_quarry, mod_player_magic, changes_enemy_beasts, changes_enemy_bricks, changes_enemy_gems, changes_enemy_tower, changes_enemy_wall, changes_player_beast, changes_player_bricks, changes_player_gems, changes_player_tower, changes_player_wall);
        }

        connections.releaseConnection(conn);
        return card;

    }

// Main to test the connection    
//    public static void main(String[] args) {
//        try {
//            DB_Access access = DB_Access.getInstance();
//
//            // Card card = access.getCard(1);
//            //Card card = access.getRandomCard();
//            // System.out.println(card.toString());
//            //System.out.println(card.getPicture().toString());
//        } catch (Exception ex) {
//            Logger.getLogger(DB_Access.class.getName()).log(Level.SEVERE, null, ex);
//        }
//
//    }
}




//Statements used in pgadmin
/*
SELECT *
FROM card
ORDER BY card_id DESC;

UPDATE card
SET mod_enemy = 1, mod_player = 1, changes_enemy = 1, changes_player = 1
WHERE card_id = 20000

SELECT changes_id
FROM changes
WHERE beasts = 0 AND bricks = 0 AND gems = 0;





SELECT *
FROM mod;

SELECT *
FROM changes

SELECT *
FROM card c INNER JOIN changes che ON c.changes_enemy = che.changes_id

SELECT changes_id
FROM changes
WHERE beasts = 0 AND bricks = 0 AND gems = 0;



DELETE FROM changes
WHERE  changes_id NOT IN (SELECT MAX(changes_id)
                  FROM   changes
                  GROUP  BY beasts,
                            bricks,
                            gems
                 
                  HAVING MAX(changes_id) IS NOT NULL);
				  
				  
DELETE  FROM changes;
DELETE  FROM mod;
DELETE FROM card;



 */
 /*
Class.forName(driverName);
       con = DriverManager.getConnection(url+dbName,userName,password);
       Statement st = con.createStatement();
       File imgfile = new File("pic.jpg");

      FileInputStream fin = new FileInputStream(imgfile);

       PreparedStatement pre =
       con.prepareStatement("insert into Image values(?,?,?)");

       pre.setString(1,"test");
       pre.setInt(2,3);
       pre.setBinaryStream(3,(InputStream)fin,(int)imgfile.length());
       pre.executeUpdate();
       System.out.println("Successfully inserted the file into the database!");

       pre.close();
       con.close(); 
    }catch (Exception e1){
        System.out.println(e1.getMessage());








 System.out.println("Retrive Image Example!");
    String driverName = "com.mysql.jdbc.Driver";
    String url = "jdbc:mysql://localhost:3306/";
    String dbName = "test";
    String userName = "root";
    String password = "root";
    Connection con = null;
    try{
        Class.forName(driverName);
        con = DriverManager.getConnection(url+dbName,userName,password);
        Statement stmt = con.createStatement();
        ResultSet rs = stmt.executeQuery("select image from image");
        int i = 0;
        while (rs.next()) {
            InputStream in = rs.getBinaryStream(1);
            OutputStream f = new FileOutputStream(new File("test"+i+".jpg"));
            i++;
            int c = 0;
            while ((c = in.read()) > -1) {
                f.write(c);
            }
            f.close();
            in.close();
        }
    }catch(Exception ex){
        System.out.println(ex.getMessage());
    }
}


 */

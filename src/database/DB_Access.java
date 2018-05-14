/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package database;

import beans.Card;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.LinkedList;
import java.util.List;

/**
 *
 * @author Stefan
 */



//hier werden die Daten eingelesen
public class DB_Access {
    
    
    // create DB_Access as Singleton
   private static DB_Access theInstance = null;
   private DB_ConnectionPool connections = DB_ConnectionPool.getInstance();
   private DB_StatementPool statementPool = DB_StatementPool.getInstance();

  public static DB_Access getInstance()
  {
    if (theInstance == null)
    {
      theInstance = new DB_Access();
    }
    return theInstance;
  }

  private DB_Access()
  {
  }

  public List<Card> getAllCards() throws SQLException, Exception
  {
    Connection conn = connections.getConnection();
    PreparedStatement stat = statementPool.getPrepStatement(conn, DB_Stmt_Type.GetAllCards);
    ResultSet rs = stat.executeQuery();
    List<Card> cardlist = new LinkedList<>();
    while (rs.next())
    {
      // ToDo: fill list with Book-data from resultset
            String name = rs.getString("name");
            String bild_pfad = rs.getString("bild_pfad");
            double preis = rs.getDouble("bild_pfad");
            
            //cardlist.add(new Card(titel, ...));
    }
    connections.releaseConnection(conn);
    return cardlist;
  }
  
  public List<Card> getChange() throws SQLException, Exception
  {
    Connection conn = connections.getConnection();
    PreparedStatement stat = statementPool.getPrepStatement(conn, DB_Stmt_Type.GetAllCards);
    ResultSet rs = stat.executeQuery();
    List<Card> cardlist = new LinkedList<>();
    while (rs.next())
    {
      // ToDo: fill list with Book-data from resultset
            String titel = rs.getString("name");
            double preis = rs.getDouble("...");
            //cardlist.add(new Card(titel, ...));
    }
    connections.releaseConnection(conn);
    return cardlist;
  }
  
  public Card getRandomCard() throws SQLException, Exception
  {
    Connection conn = connections.getConnection();
    PreparedStatement stat = statementPool.getPrepStatement(conn, DB_Stmt_Type.GetRandomCard);
    ResultSet rs = stat.executeQuery();
    Card card = null;
    while (rs.next())
    {
      // ToDo: fill list with Book-data from resultset
            int card_id = rs.getInt("card_id");
            String name = rs.getString("name");
            String bild_pfad = rs.getString("bild_pfad");
            int type = rs.getInt("type");
            int requirement = rs.getInt("requirement");
            int damage_self = rs.getInt("damage_self");
            //int mod_enemy_bestiary 
            
            //card = new card(card_id...);            
    }
    connections.releaseConnection(conn);
    return card;
  }
    
    /*
   private int card_id;
    private String name;
    private String bild_pfad;
    private int type;
    private int requirement;
    private int damage_self;
    private int mod_enemy_bestiary;
    private int mod_enemy_quarry;
    private int mod_enemy_magic;
    private int mod_player_bestiary;
    private int mod_player_quarry;
    private int mod_player_magic;
    private int changes_enemy_beats;
    private int changes_enemy_bricks;
    private int changes_enemy_gems;
    private int changes_player_beats;
    private int changes_player_bricks;
    private int changes_player_gems;
    private String description;
  */
    
}

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
            String titel = rs.getString("name");
            double preis = rs.getDouble("...");
            //cardlist.add(new Card(titel, ...));
    }
    connections.releaseConnection(conn);
    return cardlist;
  }
    
    
    
}

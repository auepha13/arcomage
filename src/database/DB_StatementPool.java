/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package database;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.util.HashMap;
import java.util.Map;

/**
 *
 * @author Stefan
 */
public class DB_StatementPool {
  
  private static DB_StatementPool theInstance;
  public static DB_StatementPool getInstance()
  {
    if (theInstance == null)
    {
      theInstance = new DB_StatementPool();
    }
    return theInstance;
  }

  private Map<Connection, Map<DB_Stmt_Type, PreparedStatement>> map = new HashMap<>();
  
  private DB_StatementPool()
  {
  }
  
  public PreparedStatement getPrepStatement(Connection connection, DB_Stmt_Type type) throws SQLException
  {
    Map<DB_Stmt_Type, PreparedStatement> connMap = map.get(connection);
    if (connMap == null)
    {
      connMap = new HashMap<>();
    }
    PreparedStatement pStat = connMap.get(type);
    if (pStat == null)
    {
      pStat = connection.prepareStatement(type.getpStatString());
      connMap.put(type, pStat);
    }
    return pStat;
  }

}

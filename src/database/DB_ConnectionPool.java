/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package database;

import static database.DB_Config.DB_DBNAME;
import static database.DB_Config.DB_DRIVER;
import static database.DB_Config.DB_PASSWD;
import static database.DB_Config.DB_URL;
import static database.DB_Config.DB_USER;
import java.sql.Connection;
import java.sql.DriverManager;
import java.util.LinkedList;

/**
 *
 * @author Stefan
 */



public class DB_ConnectionPool implements DB_Config
{
  private final LinkedList<Connection> CONN_POOL = new LinkedList<>();
  private final int MAX_CONNECTIONS = 100;
  private int current_conn = 0;

  private static DB_ConnectionPool theInstance;

  private DB_ConnectionPool()
  {
    try
    {
      Class.forName(DB_DRIVER);
    } catch (Exception ex)
    {
      throw new RuntimeException();
    }
  }

  public static DB_ConnectionPool getInstance()
  {
    if (theInstance == null)
    {
      theInstance = new DB_ConnectionPool();
    }
    return theInstance;
  }

  public Connection getConnection() throws Exception
  {
    synchronized (CONN_POOL)
    {
      if (CONN_POOL.isEmpty())
      {
        if (MAX_CONNECTIONS == current_conn)
        {
//          long start = System.currentTimeMillis();
          CONN_POOL.wait();
//          throw new Exception("Connection-limit reached - try again later");
        }
        Connection conn = DriverManager.getConnection(DB_URL + DB_DBNAME,
            DB_USER,
            DB_PASSWD);
        current_conn++;
        return conn;
      } else
      {
        return CONN_POOL.poll();
      }
    }
  }

  public void releaseConnection(Connection conn)
  {
    synchronized (CONN_POOL)
    {
      CONN_POOL.offer(conn);
      CONN_POOL.notify();
    }
  }
}


/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package database;

/**
 *
 * @author Stefan
 */
public enum DB_Stmt_Type {
    GetAllCards("SELECT * FROM card;"),
    GetRandomCard("SELECT * FROM card"   //inner join für alle werte.
            + " ORDER BY RAND()"
            + " LIMIT 1;");
  
  
  private String pStatString;

  private DB_Stmt_Type(String pStat)
  {
    this.pStatString = pStat;
  }

  public String getpStatString()
  {
    return pStatString;
  }
  
  

}

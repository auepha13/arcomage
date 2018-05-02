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
    GetAllCards("SELECT * FROM card");
  
  
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

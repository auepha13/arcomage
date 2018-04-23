/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package beans;

/**
 *
 * @author Philipp
 */
public enum Types {// die 6 typen beast ...
    
    Quarry(""),
    Bricks(""),
    Magic(""),
    Gems(""),
    Bestiary(""),
    Beast("");

    
    String str;

    public String getStr() {
        return str;
    }

    public void setStr(String str) {
        this.str = str;
    }

    private Types(String str) {
        this.str = str;
    }
    
    
    
}

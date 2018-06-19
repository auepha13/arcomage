/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package beans;

import java.io.Serializable;

/**
 *
 * @author Philipp
 */
public class Playercard implements Serializable{
    private int cardplace;
    private int playernr;

    public Playercard(int cardplace, int playernr) {
        this.cardplace = cardplace;
        this.playernr = playernr;
    }

    public int getCardplace() {
        return cardplace;
    }

    public void setCardplace(int cardplace) {
        this.cardplace = cardplace;
    }

    public int getPlayernr() {
        return playernr;
    }

    public void setPlayernr(int playernr) {
        this.playernr = playernr;
    }

   
    
    
}

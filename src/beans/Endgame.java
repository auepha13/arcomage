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
public class Endgame {
    private Boolean endgame=false;
    private int winnernr =0;

    public Endgame() {
    }

    public Boolean getEndgame() {
        return endgame;
    }

    public void setEndgame(Boolean endgame) {
        this.endgame = endgame;
    }

    public int getWinnernr() {
        return winnernr;
    }

    public void setWinnernr(int winnernr) {
        this.winnernr = winnernr;
    }
    
    
    
}

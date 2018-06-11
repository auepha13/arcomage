/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package clientserver;

import beans.Card;
import beans.Player;
import bl.Hand;

/**
 *
 * @author Philipp
 */
public class Gamestate {
    //alles wichtige für beide spieler von Palyer holen

    private Hand h;
    private int tower;
    private int wall;

    private int bestiary = 1;
    private int quarry = 1;
    private int magic = 1;

    private int beasts = 0;
    private int bricks = 0;
    private int gems = 0;

    private Hand h2;
    private int tower2;
    private int wall2;

    private int bestiary2 = 1;
    private int quarry2 = 1;
    private int magic2 = 1;

    private int beasts2 = 0;
    private int bricks2 = 0;
    private int gems2 = 0;

    private boolean win;

    private int wintowerval = 0;

    private int actualplayer;

    public Gamestate() {  //win value
        h = new Hand();
        tower = 50;
        wall = 0;
        wintowerval = 100;
        
        h2 = new Hand();
        tower2 = 50;
        wall2 = 0;

        h.generatehand();
        h2.generatehand();
    }

//    public Player(int tower, int wall) {
//        this.tower = tower;
//        this.wall = wall;
//        wintowerval = 100;
//    }
//
//    public Player(int tower, int wall, int wintowerval) {
//        this.tower = tower;
//        this.wall = wall;
//        this.wintowerval = wintowerval;
//    }
    public void usecard(int handplace, int player) throws Notusableerror {
        //karte von spieler holen
        Card c = null;
        if (player == actualplayer) {
            if (player == 1) {
                c = h.getHand()[handplace];
                //schaun ob einsetzbar
                switch (c.getType()) {
                    case 1:
                        if (beasts >= c.getRequirement()) {
                            beasts -= c.getRequirement();
                        }
                        break;
                    case 2:
                        if (bricks >= c.getRequirement()) {
                            bricks -= c.getRequirement();
                        }
                        break;
                    case 3:
                        if (gems >= c.getRequirement()) {
                            gems -= c.getRequirement();
                        }
                        ;
                        break;
                    default:
                        throw new Notusableerror();
                }

                if (c.getChanges_player_beasts()!= 0) {
                    beasts += c.getChanges_player_beasts();
                    if (beasts < 0) {
                        beasts = 0;
                    }
                }

                if (c.getChanges_player_bricks() != 0) {
                    bricks += c.getChanges_player_bricks();
                    if (bricks < 0) {
                        bricks = 0;
                    }
                }

                if (c.getChanges_player_gems() != 0) {
                    gems += c.getChanges_player_gems();
                    if (gems < 0) {
                        gems = 0;
                    }
                }

                if (c.getChanges_enemy_beasts() != 0) {
                    beasts2 += c.getChanges_enemy_beasts();
                    if (beasts2 < 0) {
                        beasts2 = 0;
                    }
                }

                if (c.getChanges_enemy_bricks() != 0) {
                    bricks2 += c.getChanges_enemy_bricks();
                    if (bricks2 < 0) {
                        bricks2 = 0;
                    }
                }

                if (c.getChanges_enemy_gems() != 0) {
                    gems2 += c.getChanges_enemy_gems();
                    if (gems2 < 0) {
                        gems2 = 0;
                    }
                }

                if (c.getMod_player_bestiary() != 0) {
                    beasts += c.getMod_player_bestiary();
                    if (beasts < 1) {
                        beasts = 1;
                    }
                }

                if (c.getMod_player_magic() != 0) {
                    magic += c.getMod_player_magic();
                    if (magic < 1) {
                        magic = 1;
                    }
                }

                if (c.getMod_player_quarry() != 0) {
                    quarry += c.getMod_player_quarry();
                    if (quarry < 1) {
                        quarry = 1;
                    }
                }

                if (c.getMod_enemy_bestiary() != 0) {
                    quarry2 += c.getChanges_enemy_gems();
                    if (quarry2 < 1) {
                        quarry2 = 1;
                    }
                }

                if (c.getMod_enemy_magic() != 0) {
                    magic2 += c.getMod_enemy_magic();
                    if (magic2 < 1) {
                        magic2 = 1;
                    }
                }

                if (c.getMod_enemy_quarry() != 0) {
                    quarry2 += c.getMod_enemy_quarry();
                    if (quarry2 < 1) {
                        quarry2 = 1;
                    }
                }

                if (c.getDamage_self() != 0) {
                    healthchangetower(c.getDamage_self());
                }

                //add. turn
                h.draw();

            } else {
                c = h2.getHand()[handplace];

                switch (c.getType()) {
                    case 1:
                        if (beasts2 >= c.getRequirement()) {
                            beasts2 -= c.getRequirement();
                        }
                        break;
                    case 2:
                        if (bricks2 >= c.getRequirement()) {
                            bricks2 -= c.getRequirement();
                        }
                        break;
                    case 3:
                        if (gems2 >= c.getRequirement()) {
                            gems2 -= c.getRequirement();
                        }
                        ;
                        break;
                    default:
                        throw new Notusableerror();
                }
                
                
                
                 if (c.getChanges_player_beasts()!= 0) {
                    beasts2 += c.getChanges_player_beasts();
                    if (beasts2 < 0) {
                        beasts2 = 0;
                    }
                }

                if (c.getChanges_player_bricks() != 0) {
                    bricks2 += c.getChanges_player_bricks();
                    if (bricks2 < 0) {
                        bricks2 = 0;
                    }
                }

                if (c.getChanges_player_gems() != 0) {
                    gems2 += c.getChanges_player_gems();
                    if (gems2 < 0) {
                        gems2 = 0;
                    }
                }

                if (c.getChanges_enemy_beasts() != 0) {
                    beasts += c.getChanges_enemy_beasts();
                    if (beasts < 0) {
                        beasts = 0;
                    }
                }

                if (c.getChanges_enemy_bricks() != 0) {
                    bricks += c.getChanges_enemy_bricks();
                    if (bricks < 0) {
                        bricks = 0;
                    }
                }

                if (c.getChanges_enemy_gems() != 0) {
                    gems += c.getChanges_enemy_gems();
                    if (gems < 0) {
                        gems = 0;
                    }
                }

                if (c.getMod_player_bestiary() != 0) {
                    beasts2 += c.getMod_player_bestiary();
                    if (beasts2 < 1) {
                        beasts2 = 1;
                    }
                }

                if (c.getMod_player_magic() != 0) {
                    magic2 += c.getMod_player_magic();
                    if (magic2 < 1) {
                        magic2 = 1;
                    }
                }

                if (c.getMod_player_quarry() != 0) {
                    quarry2 += c.getMod_player_quarry();
                    if (quarry2 < 1) {
                        quarry2 = 1;
                    }
                }

                if (c.getMod_enemy_bestiary() != 0) {
                    quarry += c.getChanges_enemy_gems();
                    if (quarry < 1) {
                        quarry = 1;
                    }
                }

                if (c.getMod_enemy_magic() != 0) {
                    magic += c.getMod_enemy_magic();
                    if (magic < 1) {
                        magic = 1;
                    }
                }

                if (c.getMod_enemy_quarry() != 0) {
                    quarry += c.getMod_enemy_quarry();
                    if (quarry < 1) {
                        quarry = 1;
                    }
                }

                if (c.getDamage_self() != 0) {
                    healthchangetower(c.getDamage_self());
                }
                
                h2.draw();
            }
        } else {
            throw new Notusableerror();
        }

//    private int mod_enemy_bestiary;
//    private int mod_enemy_quarry;
//    private int mod_enemy_magic;
//    private int mod_player_bestiary;
//    private int mod_player_quarry;
//    private int mod_player_magic;
//    private int changes_enemy_beasts;
//    private int changes_enemy_bricks;
//    private int changes_enemy_gems;
//    private int changes_player_beasts;
//    private int changes_player_bricks;
//    private int changes_player_gems;
//hand von slot verwenden und neue ziehen
        endturn();
    }

    public void healthchangetower(int value) {

        tower += value;
        if (tower >= wintowerval) {
            endgame(true);
        }
        if (tower <= 0) {
            endgame(false);
        }
    }

    public void healthchangewall(int value) {

        if (wall >= value) {
            wall -= value;

        } else {
            if (wall < value && wall > 0) {

            } else {
                tower += value;
                if (tower >= wintowerval) {
                    endgame(true);
                }
                if (tower <= 0) {
                    endgame(false);
                }
            }

        }

    }

    public void healthchange(int value) {
        tower += value;
        if (tower >= wintowerval) {
            endgame(true);
        }
        if (tower <= 0) {
            endgame(false);
        }
    }

    public void endturn() {
        if (this.actualplayer == 1) {
            beasts +=bestiary;
            bricks +=quarry;
            gems +=magic;
                    
            actualplayer = 2;
        } else {
            beasts2 +=bestiary2;
            bricks2 +=quarry2;
            gems2 +=magic2;
            actualplayer = 1;
        }
        
        //last played
    }
    
//    public Player getplayer(int playernr)
//    {
//        Player p = null;
//        
////        private Hand h;
////    private int tower;
////    private int  wall;
////    
////    private int bestiary;
////    private int quarry;
////    private int magic;
////    
////    private int beasts;
////    private int bricks;
////    private int gems;
////    
////    private int bestiary2;
////    private int quarry2;
////    private int magic2;
////    
////    private int beasts2;
////    private int bricks2;
////    private int gems2;
//        
//        
//        if(playernr == 1)
//        {
//            p = new Player(h,tower,wall,bestiary,quarry,magic,beasts,bricks,gems,bestiary2,quarry2,magic2,beasts2,bricks2,gems2,win);
//        }else{
//            
//        }
//        return p;
//    }
    
    

    public void endgame(boolean w) {
        win = w;//... todo falls gewonnen
    }

    public Hand getH() {
        return h;
    }

    public void setH(Hand h) {
        this.h = h;
    }

    public int getTower() {
        return tower;
    }

    public void setTower(int tower) {
        this.tower = tower;
    }

    public int getWall() {
        return wall;
    }

    public void setWall(int wall) {
        this.wall = wall;
    }

    public int getBestiary() {
        return bestiary;
    }

    public void setBestiary(int bestiary) {
        this.bestiary = bestiary;
    }

    public int getQuarry() {
        return quarry;
    }

    public void setQuarry(int quarry) {
        this.quarry = quarry;
    }

    public int getMagic() {
        return magic;
    }

    public void setMagic(int magic) {
        this.magic = magic;
    }

    public int getBeasts() {
        return beasts;
    }

    public void setBeasts(int beasts) {
        this.beasts = beasts;
    }

    public int getBricks() {
        return bricks;
    }

    public void setBricks(int bricks) {
        this.bricks = bricks;
    }

    public int getGems() {
        return gems;
    }

    public void setGems(int gems) {
        this.gems = gems;
    }

    public Hand getH2() {
        return h2;
    }

    public void setH2(Hand h2) {
        this.h2 = h2;
    }

    public int getTower2() {
        return tower2;
    }

    public void setTower2(int tower2) {
        this.tower2 = tower2;
    }

    public int getWall2() {
        return wall2;
    }

    public void setWall2(int wall2) {
        this.wall2 = wall2;
    }

    public int getBestiary2() {
        return bestiary2;
    }

    public void setBestiary2(int bestiary2) {
        this.bestiary2 = bestiary2;
    }

    public int getQuarry2() {
        return quarry2;
    }

    public void setQuarry2(int quarry2) {
        this.quarry2 = quarry2;
    }

    public int getMagic2() {
        return magic2;
    }

    public void setMagic2(int magic2) {
        this.magic2 = magic2;
    }

    public int getBeasts2() {
        return beasts2;
    }

    public void setBeasts2(int beasts2) {
        this.beasts2 = beasts2;
    }

    public int getBricks2() {
        return bricks2;
    }

    public void setBricks2(int bricks2) {
        this.bricks2 = bricks2;
    }

    public int getGems2() {
        return gems2;
    }

    public void setGems2(int gems2) {
        this.gems2 = gems2;
    }

    public boolean isWin() {
        return win;
    }

    public void setWin(boolean win) {
        this.win = win;
    }

    public int getWintowerval() {
        return wintowerval;
    }

    public void setWintowerval(int wintowerval) {
        this.wintowerval = wintowerval;
    }

    class Notusableerror extends Exception {

        Notusableerror() {
            super("Diese karte kann nicht gespielt werden");
        }
    }

}

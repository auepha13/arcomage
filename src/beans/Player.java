/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package beans;

import bl.Hand;

/**
 *
 * @author Philipp
 */
public class Player {

    private Hand h;
    private int tower;
    private int  wall;
    
    private int bestiary;
    private int quarry;
    private int magic;
    
    private int beasts;
    private int bricks;
    private int gems;
    
    private int bestiary2;
    private int quarry2;
    private int magic2;
    
    private int beasts2;
    private int bricks2;
    private int gems2;
    
    private boolean win;
        
    private int playernr;

    public Player(int nr, Hand h, int tower, int wall, int bestiary, int quarry, int magic, int beasts, int bricks, int gems, int bestiary2, int quarry2, int magic2, int beasts2, int bricks2, int gems2, boolean win) {
        this.playernr = nr;
        this.h = h;
        this.tower = tower;
        this.wall = wall;
        this.bestiary = bestiary;
        this.quarry = quarry;
        this.magic = magic;
        this.beasts = beasts;
        this.bricks = bricks;
        this.gems = gems;
        this.bestiary2 = bestiary2;
        this.quarry2 = quarry2;
        this.magic2 = magic2;
        this.beasts2 = beasts2;
        this.bricks2 = bricks2;
        this.gems2 = gems2;
        this.win = win;
    }

    
    
    
    

class Notusableerror extends Exception
{
    Notusableerror()
    {
        super("Diese karte kann nicht gespielt werden");
    }
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

    public boolean isWin() {
        return win;
    }

    public void setWin(boolean win) {
        this.win = win;
    }

    public int getPlayernr() {
        return playernr;
    }

    public void setPlayernr(int playernr) {
        this.playernr = playernr;
    }


}

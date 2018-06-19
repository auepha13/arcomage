/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package beans;

import bl.Hand;
import java.io.Serializable;

/**
 *This class manages all the data from a Player
 * @author Philipp
 */
public class Player implements Serializable{

    public Card[] hand = new Card[6];
    private int tower;
    private int  wall;
    
    private int tower2;
    private int  wall2;
    
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
        
    private int actualplayer;

    public Player(Card[] h,int tower, int wall, int tower2, int wall2, int bestiary, int quarry, int magic, int beasts, int bricks, int gems, int bestiary2, int quarry2, int magic2, int beasts2, int bricks2, int gems2, boolean win, int actualplayer) {
        hand = h;
        this.tower = tower;
        this.wall = wall;
        this.tower2 = tower2;
        this.wall2 = wall2;
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
        this.actualplayer = actualplayer;
    }

    public Card[] getHand() {
        return hand;
    }

    public void setHand(Card[] hand) {
        this.hand = hand;
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

    public int getActualplayer() {
        return actualplayer;
    }

    public void setActualplayer(int actualplayer) {
        this.actualplayer = actualplayer;
    }

    
    

    

 


}

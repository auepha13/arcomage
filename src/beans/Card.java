package beans;

import java.io.File;

//Alle attribute der Karten, wird vom Server aus Datenbank gelesen 
public class Card {

    public Card(int card_id, int mod_enemy_bestiary, int mod_enemy_quarry, int mod_enemy_magic, int mod_player_bestiary, int mod_player_quarry, int mod_player_magic, int changes_enemy_beasts, int changes_enemy_bricks, int changes_enemy_gems, int changes_enemy_tower, int changes_enemy_wall, int changes_player_beasts, int changes_player_bricks, int changes_player_gems, int changes_player_tower, int changes_player_wall) {
        this.card_id = card_id;
        this.mod_enemy_bestiary = mod_enemy_bestiary;
        this.mod_enemy_quarry = mod_enemy_quarry;
        this.mod_enemy_magic = mod_enemy_magic;
        this.mod_player_bestiary = mod_player_bestiary;
        this.mod_player_quarry = mod_player_quarry;
        this.mod_player_magic = mod_player_magic;
        this.changes_enemy_beasts = changes_enemy_beasts;
        this.changes_enemy_bricks = changes_enemy_bricks;
        this.changes_enemy_gems = changes_enemy_gems;
        this.changes_enemy_tower = changes_enemy_tower;
        this.changes_enemy_wall = changes_enemy_wall;
        this.changes_player_beasts = changes_player_beasts;
        this.changes_player_bricks = changes_player_bricks;
        this.changes_player_gems = changes_player_gems;
        this.changes_player_tower = changes_player_tower;
        this.changes_player_wall = changes_player_wall;
    }

    private int card_id;
    private String name;
    private String description;
    private File picture;
    private int type;
    private int requirement;
    private boolean additional_turn;
    private boolean discardable;
    private int damage_enemy;
    private int damage_self;
    private int mod_enemy_bestiary;
    private int mod_enemy_quarry;
    private int mod_enemy_magic;
    private int mod_player_bestiary;
    private int mod_player_quarry;
    private int mod_player_magic;
    private int changes_enemy_beasts;
    private int changes_enemy_bricks;
    private int changes_enemy_gems;
    private int changes_enemy_tower;
    private int changes_enemy_wall;
    private int changes_player_beasts;
    private int changes_player_bricks;
    private int changes_player_gems;
    private int changes_player_tower;
    private int changes_player_wall;

    public Card(int card_id, String name, String description, File picture, int type, int requirement, boolean additional_turn, boolean discardable, int damage_enemy, int damage_self, int mod_enemy_bestiary, int mod_enemy_quarry, int mod_enemy_magic, int mod_player_bestiary, int mod_player_quarry, int mod_player_magic, int changes_enemy_beasts, int changes_enemy_bricks, int changes_enemy_gems, int changes_enemy_tower, int changes_enemy_wall, int changes_player_beasts, int changes_player_bricks, int changes_player_gems, int changes_player_tower, int changes_player_wall) {
        this.card_id = card_id;
        this.name = name;
        this.description = description;
        this.picture = picture;
        this.type = type;
        this.requirement = requirement;
        this.additional_turn = additional_turn;
        this.discardable = discardable;
        this.damage_enemy = damage_enemy;
        this.damage_self = damage_self;
        this.mod_enemy_bestiary = mod_enemy_bestiary;
        this.mod_enemy_quarry = mod_enemy_quarry;
        this.mod_enemy_magic = mod_enemy_magic;
        this.mod_player_bestiary = mod_player_bestiary;
        this.mod_player_quarry = mod_player_quarry;
        this.mod_player_magic = mod_player_magic;
        this.changes_enemy_beasts = changes_enemy_beasts;
        this.changes_enemy_bricks = changes_enemy_bricks;
        this.changes_enemy_gems = changes_enemy_gems;
        this.changes_enemy_tower = changes_enemy_tower;
        this.changes_enemy_wall = changes_enemy_wall;
        this.changes_player_beasts = changes_player_beasts;
        this.changes_player_bricks = changes_player_bricks;
        this.changes_player_gems = changes_player_gems;
        this.changes_player_tower = changes_player_tower;
        this.changes_player_wall = changes_player_wall;
    }

    public int getCard_id() {
        return card_id;
    }

    public void setCard_id(int card_id) {
        this.card_id = card_id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public File getPicture() {
        return picture;
    }

    public void setPicture(File picture) {
        this.picture = picture;
    }

    public int getType() {
        return type;
    }

    public void setType(int type) {
        this.type = type;
    }

    public int getRequirement() {
        return requirement;
    }

    public void setRequirement(int requirement) {
        this.requirement = requirement;
    }

    public boolean isAdditional_turn() {
        return additional_turn;
    }

    public void setAdditional_turn(boolean additional_turn) {
        this.additional_turn = additional_turn;
    }

    public boolean isDiscardable() {
        return discardable;
    }

    public void setDiscardable(boolean discardable) {
        this.discardable = discardable;
    }

    public int getDamage_enemy() {
        return damage_enemy;
    }

    public void setDamage_enemy(int damage_enemy) {
        this.damage_enemy = damage_enemy;
    }

    public int getDamage_self() {
        return damage_self;
    }

    public void setDamage_self(int damage_self) {
        this.damage_self = damage_self;
    }

    public int getMod_enemy_bestiary() {
        return mod_enemy_bestiary;
    }

    public void setMod_enemy_bestiary(int mod_enemy_bestiary) {
        this.mod_enemy_bestiary = mod_enemy_bestiary;
    }

    public int getMod_enemy_quarry() {
        return mod_enemy_quarry;
    }

    public void setMod_enemy_quarry(int mod_enemy_quarry) {
        this.mod_enemy_quarry = mod_enemy_quarry;
    }

    public int getMod_enemy_magic() {
        return mod_enemy_magic;
    }

    public void setMod_enemy_magic(int mod_enemy_magic) {
        this.mod_enemy_magic = mod_enemy_magic;
    }

    public int getMod_player_bestiary() {
        return mod_player_bestiary;
    }

    public void setMod_player_bestiary(int mod_player_bestiary) {
        this.mod_player_bestiary = mod_player_bestiary;
    }

    public int getMod_player_quarry() {
        return mod_player_quarry;
    }

    public void setMod_player_quarry(int mod_player_quarry) {
        this.mod_player_quarry = mod_player_quarry;
    }

    public int getMod_player_magic() {
        return mod_player_magic;
    }

    public void setMod_player_magic(int mod_player_magic) {
        this.mod_player_magic = mod_player_magic;
    }

    public int getChanges_enemy_beasts() {
        return changes_enemy_beasts;
    }

    public void setChanges_enemy_beasts(int changes_enemy_beasts) {
        this.changes_enemy_beasts = changes_enemy_beasts;
    }

    public int getChanges_enemy_bricks() {
        return changes_enemy_bricks;
    }

    public void setChanges_enemy_bricks(int changes_enemy_bricks) {
        this.changes_enemy_bricks = changes_enemy_bricks;
    }

    public int getChanges_enemy_gems() {
        return changes_enemy_gems;
    }

    public void setChanges_enemy_gems(int changes_enemy_gems) {
        this.changes_enemy_gems = changes_enemy_gems;
    }

    public int getChanges_enemy_tower() {
        return changes_enemy_tower;
    }

    public void setChanges_enemy_tower(int changes_enemy_tower) {
        this.changes_enemy_tower = changes_enemy_tower;
    }

    public int getChanges_enemy_wall() {
        return changes_enemy_wall;
    }

    public void setChanges_enemy_wall(int changes_enemy_wall) {
        this.changes_enemy_wall = changes_enemy_wall;
    }

    public int getChanges_player_beasts() {
        return changes_player_beasts;
    }

    public void setChanges_player_beasts(int changes_player_beasts) {
        this.changes_player_beasts = changes_player_beasts;
    }

    public int getChanges_player_bricks() {
        return changes_player_bricks;
    }

    public void setChanges_player_bricks(int changes_player_bricks) {
        this.changes_player_bricks = changes_player_bricks;
    }

    public int getChanges_player_gems() {
        return changes_player_gems;
    }

    public void setChanges_player_gems(int changes_player_gems) {
        this.changes_player_gems = changes_player_gems;
    }

    public int getChanges_player_tower() {
        return changes_player_tower;
    }

    public void setChanges_player_tower(int changes_player_tower) {
        this.changes_player_tower = changes_player_tower;
    }

    public int getChanges_player_wall() {
        return changes_player_wall;
    }

    public void setChanges_player_wall(int changes_player_wall) {
        this.changes_player_wall = changes_player_wall;
    }

    @Override
    public String toString() {
        return "Card{" + "card_id=" + card_id + ", name=" + name + ", description=" + description + ", picture=" + picture + ", type=" + type + ", requirement=" + requirement + ", additional_turn=" + additional_turn + ", discardable=" + discardable + ", damage_enemy=" + damage_enemy + ", damage_self=" + damage_self + ", mod_enemy_bestiary=" + mod_enemy_bestiary + ", mod_enemy_quarry=" + mod_enemy_quarry + ", mod_enemy_magic=" + mod_enemy_magic + ", mod_player_bestiary=" + mod_player_bestiary + ", mod_player_quarry=" + mod_player_quarry + ", mod_player_magic=" + mod_player_magic + ", changes_enemy_beasts=" + changes_enemy_beasts + ", changes_enemy_bricks=" + changes_enemy_bricks + ", changes_enemy_gems=" + changes_enemy_gems + ", changes_enemy_tower=" + changes_enemy_tower + ", changes_enemy_wall=" + changes_enemy_wall + ", changes_player_beasts=" + changes_player_beasts + ", changes_player_bricks=" + changes_player_bricks + ", changes_player_gems=" + changes_player_gems + ", changes_player_tower=" + changes_player_tower + ", changes_player_wall=" + changes_player_wall + '}';
    }

    public Card(int card_id, String name, String description, int type, int requirement, boolean additional_turn, boolean discardable, int damage_enemy, int damage_self) {
        this.card_id = card_id;
        this.name = name;
        this.description = description;
        this.type = type;
        this.requirement = requirement;
        this.additional_turn = additional_turn;
        this.discardable = discardable;
        this.damage_enemy = damage_enemy;
        this.damage_self = damage_self;
    }

}

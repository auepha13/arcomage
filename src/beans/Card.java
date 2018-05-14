package beans;


//XML stuff with jaxb sooon 

public class Card {

    private int card_id;
    private String name;
    private String bild_pfad;
    private int type;
    private int requirement;
    private int damage_self;
    private int mod_enemy_bestiary;
    private int mod_enemy_quarry;
    private int mod_enemy_magic;
    private int mod_player_bestiary;
    private int mod_player_quarry;
    private int mod_player_magic;
    private int changes_enemy_beats;
    private int changes_enemy_bricks;
    private int changes_enemy_gems;
    private int changes_player_beats;
    private int changes_player_bricks;
    private int changes_player_gems;
    private String description;

    public Card(int card_id, String name, String bild_pfad, int type, int requirement, int damage_self, int mod_enemy_bestiary, int mod_enemy_quarry, int mod_enemy_magic, int mod_player_bestiary, int mod_player_quarry, int mod_player_magic, int changes_enemy_beats, int changes_enemy_bricks, int changes_enemy_gems, int changes_player_beats, int changes_player_bricks, int changes_player_gems, String description) {
        this.card_id = card_id;
        this.name = name;
        this.bild_pfad = bild_pfad;
        this.type = type;
        this.requirement = requirement;
        this.damage_self = damage_self;
        this.mod_enemy_bestiary = mod_enemy_bestiary;
        this.mod_enemy_quarry = mod_enemy_quarry;
        this.mod_enemy_magic = mod_enemy_magic;
        this.mod_player_bestiary = mod_player_bestiary;
        this.mod_player_quarry = mod_player_quarry;
        this.mod_player_magic = mod_player_magic;
        this.changes_enemy_beats = changes_enemy_beats;
        this.changes_enemy_bricks = changes_enemy_bricks;
        this.changes_enemy_gems = changes_enemy_gems;
        this.changes_player_beats = changes_player_beats;
        this.changes_player_bricks = changes_player_bricks;
        this.changes_player_gems = changes_player_gems;
        this.description = description;
    }
    
    public Card(int card_id, String name) { //testen
        this.card_id = card_id;
        this.name = name;
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

    public String getBild_pfad() {
        return bild_pfad;
    }

    public void setBild_pfad(String bild_pfad) {
        this.bild_pfad = bild_pfad;
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

    public int getChanges_enemy_beats() {
        return changes_enemy_beats;
    }

    public void setChanges_enemy_beats(int changes_enemy_beats) {
        this.changes_enemy_beats = changes_enemy_beats;
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

    public int getChanges_player_beats() {
        return changes_player_beats;
    }

    public void setChanges_player_beats(int changes_player_beats) {
        this.changes_player_beats = changes_player_beats;
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

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    
}
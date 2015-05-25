//
//  PlayerInfo.h
//  Boids
//
//  Created by Yanjie Chen on 3/3/15.
//
//

#ifndef __Boids__PlayerInfo__
#define __Boids__PlayerInfo__

#include "cocos2d.h"

#define LEVEL_UP_SUCCESS 0
#define LEVEL_UP_ERROR_NOT_FOUND 1
#define LEVEL_UP_ERROR_NOT_ENOUGH_GOLD 2
#define LEVEL_UP_ERROR_REACH_LEVEL_LIMIT 3

class PlayerInfo {
private:
    cocos2d::ValueMap _player_info;
    
private:
    static PlayerInfo* _instance;
    
    PlayerInfo();
    
public:
    virtual ~PlayerInfo();
    
    static PlayerInfo* getInstance();
    
    void loadPlayerInfo();
    void recordPlayerInfo();
    
    const cocos2d::ValueMap& getAllUnitsInfo();
    
    const cocos2d::ValueMap& getPlayerDeployedUnitsSlotIds();
    
    cocos2d::ValueVector getPlayerDeployedUnitsInfo();
    
    cocos2d::ValueVector getPlayerDeployedUnitNames();
    
    void setDeployUnit( const std::string& slot_id, const std::string& hero_id );
    void setDeployUnits( const cocos2d::ValueMap& data );
    
    cocos2d::ValueMap updateUnitEquip( const std::string& hero_id, const std::string& type, const std::string& obj_id );
    void updateEquip( const std::string& obj_id, bool in_use );
    void addEquip( const std::string& obj_id, const std::string& equip_id );
    void removeEquip( const std::string& obj_id );
    
    cocos2d::ValueVector getEquipsByRange( int type, int from, int size, int order );
    
    cocos2d::ValueMap upgradeHero( const std::string& hero_id, int level );
    
    const cocos2d::ValueMap& getAllEquipsInfo();
    
    void gainGold( int gain );
    int getGold();
    
    void gainDiamond( int gain );
    int getDiamond();
    
    void gainTeamExp( int exp );
    void setTeamLevel( int level );
    int getTeamLevel();
    
    void gainTeamSkillLevel( int lvl_up, const std::string& skill_name );
    cocos2d::ValueMap& getTeamSkill( const std::string& skill_name );
    
    int getLevelUpCost( const std::string& slot );
    int unitLevelUpByOne( const std::string& slot );
};

#endif /* defined(__Boids__PlayerInfo__) */
